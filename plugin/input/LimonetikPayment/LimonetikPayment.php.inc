<?php
/**
 * @brief LimonetikPayment Input
 * <br /> Interface to Limonetik payment system.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2020
 * @date Modification: Jan 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * LimonetikPayment Input class.
 */
final class LimonetikPayment extends Input {
    /**
     * const array LIMONETIKAPIURLS
     * @brief Stores Limonetik API URLs
     */
    private const LIMONETIKAPIURLS = array(
        'test'  => 'https://api.limonetikqualif.com',
        'live'  => 'https://api.limonetik.com',
    );

    /**
     * const string LIMONETIKAPIVERSION
     * @brief Stores Limonerik API Version
     */
    private const LIMONETIKAPIVERSION = 'V40';

    /**
     * var integer $_lastErrorCode
     * @brief Last error code.
     */
    protected $_lastErrorCode = 0;

    /**
     * var string $_lastErrorMsg
     * @brief Last error message.
     */
    protected $_lastErrorMsg = '';

    /**
     * var string $_lastErrorDetails
     * @brief Last error details.
     */
    protected $_lastErrorDetails = '';

    /**
     * var string $_transactionId
     * @brief Transaction id.
     */
    private $_transactionId = '';

    /**
     * var array $params
     * @brief Input parameters.
     */
    public $params = array();

    /**
     * var array $confirmationData
     * @brief Confirmation data received from Payzen instant notifications.
     */
    private $confirmationData = null;

    /**
     * var Object $config
     * @brief Plugin configuration object.
     */
    protected $config = null;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('LimonetikPayment', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'eCommerce';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* load plugin configuration */
        $this->load_configuration();

        /* define params */
        $this->params = $params;

        /* Input generic initialization */
        parent::initialise();
    }

    /* execution methods */

    /**
     * Prepare for payment.
     * @param array $params
     * @return boolean result
     */
    public function prepare_forPayment($params=array()) {
        global $camyks;

        /* Load params */
        $defaultParams = array('amount' => 0, 'orderId' => '', 'paymentMode' => null);
        $this->params = array_merge($defaultParams, $params);

        /* Build request data */
        $data = array(
            "PaymentOrder" => array(
                "MerchantId" => $this->config->vars['MerchantId'],
                "PaymentPageId" => $this->config->get_paymentPageId($this->params['paymentMode']),
                "Amount" => $this->params['amount'],
                "Currency" => "EUR",
                "MerchantUrls" => array(
                    "ReturnUrl" => $this->params['backURL_Confirm'],
                    "AbortedUrl" => $this->params['backURL_Cancel'],
                    "ErrorUrl" => $this->params['backURL_Refused'],
                    "ServerNotificationUrl" => $this->params['backURL_Response'],
                ),
                "MerchantOrder" => array(
                    "Id" => $this->params['orderId'],
                    "Customer" => array(
                        "Email" => $this->params['email'],
                    ),
                ),
            ),
        );

        /* Execute request to Limonetik server */
        if (($response = $this->execute_limonetikRequest('PaymentOrder/Create', $data)) === false)
            return $this->display_error();

        /* Backup Limonetik answer in session */
        $camyks->set_sessionValue('LimonetikAnswer', array(
            'RequestId'         => $response['RequestId'],
            'PaymentOrderId'    => $response['PaymentOrderId'],
        ));

        /* Redirect user to Limonetik server */
        header('Location:'.$response['PaymentPageUrl']);
    }

    /* data query methods */

    /**
     * Load confirmation data Payzen instant notification.
     * @return void
     */
    public function load_paymentConfirmation() {

    }

    /**
     * Check if payment is confirmed.
     * @return boolean result
     */
    public function is_paymentConfirmed() {
        return false;
    }

    /**
     * Check if payment is cancelled.
     * @return boolean result
     */
    public function is_paymentCancelled() {
        return false;
    }

    /**
     * Return response data from confirmation request.
     * @return array
     */
    public function get_paymentConfirmationData() {
        return array('uniqueId' => '');
    }

    /**
     * Execute check out.
     * @return array
     */
    public function execute_checkout() {
        global $camyks;

        $paymentData = $camyks->get_sessionValue('LimonetikAnswer');

        /* Build request data */
        $data = array(
            'Id' => $paymentData['PaymentOrderId'],
        );

        /* Execute request to Limonetik server */
        if (($response = $this->execute_limonetikRequest('PaymentOrder/Detail', $data, 'GET')) === false)
            return $camyks->log_internalerror($this, $this->_lastErrorMsg, $this->_lastErrorDetails, __FILE__, __LINE__);

        /* Check order status that shouldn't append */
        if (in_array($response['PaymentOrder']['Status'], array('Charged', 'Created', 'Payment_In_Progress')))
            return false;

        /* Check order has already be cancelled/refunded/error */
        if (in_array($response['PaymentOrder']['Status'], array('Cancelled', 'Refunded', 'Error')))
            return false;

        /* Cancel order on aborted / refused */
        if (in_array($response['PaymentOrder']['Status'], array('Aborted', 'Refused'))) {
            $data = array(
                'PaymentOrderId'    => $paymentData['PaymentOrderId'],
                'CancelAmount'      => $this->params['amount'],
                'Currency'          => 'EUR',
            );
            if ($this->execute_limonetikRequest('PaymentOrder/Cancel', $data) === false)
                return $camyks->log_internalerror($this, $this->_lastErrorMsg, $this->_lastErrorDetails, __FILE__, __LINE__);
            return false;
        }

        /* Charge order if payment status is authorised */
        if ($response['PaymentOrder']['Status'] === 'Authorized') {
            $data = array(
                'PaymentOrderId'    => $paymentData['PaymentOrderId'],
                'ChargeAmount'      => $this->params['amount'],
                'Currency'          => 'EUR',
            );

            if (($response2 = $this->execute_limonetikRequest('PaymentOrder/Charge', $data)) === false)
                return $camyks->log_internalerror($this, $this->_lastErrorMsg, $this->_lastErrorDetails, __FILE__, __LINE__);

            $this->_transactionId = $response2['OperationId'];
            return true;
        }

        /* Order is authorising */
        if ($response['PaymentOrder']['Status'] === 'Authorizing') {
            /*
            $data = array(
                'PaymentOrderId'    => $paymentData['PaymentOrderId'],
                'ChargeAmount'      => $this->params['amount'],
                'Currency'          => 'EUR',
            );

            if (($response2 = $this->execute_limonetikRequest('PaymentOrder/Charge', $data)) === false)
                return $camyks->log_internalerror($this, $this->_lastErrorMsg, $this->_lastErrorDetails, __FILE__, __LINE__);

            $this->_transactionId = $response2['OperationId'];
            */
            return false;
        }
        return false;
    }

    /**
     * Return transaction ID.
     * @return string
     */
    public function get_transactionId() {

    }

    /* Limonetik related methods */

    /**
     * Execute request to Limonetik server.
     * @param string $action
     * @param array $data
     * @param string $method
     * @return array
     */
    private function execute_limonetikRequest($action, $data, $method='POST') {

        /* Load configuration */
        $this->load_configuration();

        /* Define URL to use */
        $limonetikURL = self::LIMONETIKAPIURLS[$this->config->vars['runningMode']];
        $limonetikURL = $limonetikURL.'/Rest/'.self::LIMONETIKAPIVERSION.'/'.$action;

        /* Execute request to Limonetik server */
        $options = array(
            'http' => array(
                'method'        => $method,
                'header'        => "Content-type: application/json\r\n".
                                   "Authorization: Basic ".$this->config->vars['APIKey']."\r\n.".
                                   "Accept: application/json\r\n",
                'ignore_errors' => true,
                'timeout'       => 10,
            ),
        );
        if ($method === 'GET')
            $limonetikURL .= '?'.http_build_query($data);
        else
            $options['http']['content'] = json_encode($data);

        $context  = stream_context_create($options);
        $response = file_get_contents($limonetikURL, false, $context);

        /* Trim UTF-8 bom */
        $response = preg_replace("/^\xEF\xBB\xBF/", '', $response);

        /* Read Limonetik answer */
        if (!preg_match('#^HTTP/[0-9]\.[0-9] ([0-9]{3}) (.*)$#', $http_response_header[0], $matches) or $matches[1] != '200') {
            $this->set_lastError(1, 'Invalid response from Limonetik server.', (isset($matches[0]) ? $matches[1].' '.$matches[2] : ''));
            return false;
        }

        /* Check response length */
        if (!(strlen($response) > 0)) {
            $this->set_lastError(1, 'Invalid response from Limonetik server.');
            return false;
        }

        /* Decode JSON response */
        $response = json_decode($response, true);

        /* Check decoding result */
        if (json_last_error() !== JSON_ERROR_NONE or !is_array($response)) {
            $this->set_lastError(1, 'Invalid response from Limonetik server.', json_last_error_msg());
            return false;
        }

        /* Check request answer */
        if ((int)$response['ReturnCode'] != 1000) {
            $this->set_lastError(2, 'Error from Limonetik server.', $response['ReturnCode'].'('.$response['ReturnCode'].')');
            return false;
        }

        /* Return response */
        return $response;
    }

    /* Error handling methods */

    /**
     * Define last error.
     * @param integer $errorCode
     * @param string $errorMsg
     * @param string $errorDetails
     * @return return void
     */
    private function set_lastError($errorCode, $errorMsg, $errorDetails='') {
        $this->_lastErrorCode = $errorCode;
        $this->_lastErrorMsg = $errorMsg;
        $this->_lastErrorDetails = $errorDetails;
    }

    /**
     * Return last error as code.
     * @return integer
     */
    public function get_lastError() {
        return $this->_lastErrorCode;
    }

    /**
     * Return last error as text.
     * @return string
     */
    public function get_lastErrorMessage() {
        if ($this->_lastErrorMsg == '')
            return '';
        return $this->_lastErrorMsg;
    }

    /**
     * Display error.
     * @return void
     */
    public function display_error() {
        $this->set_selectedLayout('Error.html.inc');
    }

    /* Configuration related methods */

    /**
     * Return configuration value.
     * @param string $item
     * @param mixed $default
     * @return void
     */
    public function get_configValue($item, $default=null) {
        $this->load_configuration();
        return $this->config->get_value($item, $default);
    }

    /**
     * Load plugin configuration.
     * @return void
     */
    private function load_configuration() {
        /* Check configuration is already loaded */
        if (!is_null($this->config))
            return;

        /* load configuration library */
        $this->load_library('LimonetikPaymentConfig');

        /* load config */
        $this->config = new LimonetikPaymentConfig('config', $this);
        $this->config->get();
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        $this->load_configuration();
    }

    /**
     * Display object in Admin_Site / view configuration mode.
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/configuration/view.html.inc');
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode.
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        $this->load_configuration();

        /* update form */
        $this->form = &$form;
        $this->form->set_object($this->config);
    }

    /**
     * Display object in Admin_Site / edit configuration mode.
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }

    /**
     * Execute object in Admin_Site / save configuration mode.
     * @return void
     */
    public function save_configuration() {
        $this->load_configuration();
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
