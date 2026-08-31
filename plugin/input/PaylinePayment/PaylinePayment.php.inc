<?php
/**
 * @brief PaylinePayment Input
 * <br /> Interface to Payline platform payment system.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2026
 * @date Modification: Apr 2026
 * @copyright 2026 CaMykS Team
 */

/**
 * PaylinePayment Input class.
 */
final class PaylinePayment extends Input {
    /**
     * @var integer $_lastErrorCode
     * @brief Last error code.
     */
    private $_lastErrorCode = 0;

    /**
     * @var string $_lastErrorMsg
     * @brief Last error message.
     */
    private $_lastErrorMsg = '';

    /**
     * @var array $params
     * @brief Input parameters.
     */
    public $params = array();

    /**
     * @var object $paylineClient
     * @brief Loaded PaylineClient object.
     */
    private $paylineClient = null;

    /**
     * @var string $transactionId
     * @brief Created transaction Id.
     */
    private $transactionId = '';

    /**
     * @var string $redirectURL
     * @brief Payline redirect URL.
     */
    protected $redirectURL = '';

    /**
     * @var string $confirmationData
     * @brief Payline feedback data token.
     */
    private $confirmationData = null;

    /**
     * @var string $responseData
     * @brief Payline response data.
     */
    private $responseData = null;

    /**
     * @var integer paylineSDKVersion
     * @brief Payline SDK version.
     */
    private $paylineSDKVersion = 34;


    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('PaylinePayment', $path_type);

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

    /* Mark: Override input methods */

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

    /* Mark: Payline loading methods */

    /**
     * Load Payline SDK and initialize client.
     * @return void
     */
    public function load_PaylineClient() {
        /* Check client is already loaded */
        if (!is_null($this->paylineClient))
            return;

        /* Load Payline SDK *
        include_once('Psr/autoloader.php');
        include_once('Symfony/Contracts/autoloader.php');
        include_once('Symfony/Cache/autoloader.php');
        include_once('Monolog/autoloader.php');
        $this->load_file('Payline/Cache/CacheInterface.php');
        $this->load_file('Payline/Cache/CacheTrait.php');
        $this->load_file('Payline/Cache/File.php');
        $this->load_file('Payline/Cache/Apc.php');
        $this->load_file('Payline/autoloader.php');
        */

        $this->load_file('Payline/autoloader.php');

        /* Initialize Payline SDK */
        $env = ($this->get_configValue('runningMode') === 'PRODUCTION') ? Payline\PaylineSDK::ENV_PROD : Payline\PaylineSDK::ENV_HOMO;

        $this->paylineClient = new Payline\PaylineSDK(
            $this->get_configValue('merchantId'),
            $this->config->get_accessKey(),
            '', '', '', '',
            $env
        );
    }

    /* Mark: Payment methods */

    /**
     * Prepare for payment.
     * @param array $params
     * @return boolean result
     */
    public function prepare_forPayment($params=array()) {
        global $camyks;

        $defaultParams = array(
            'amount'            => 0,
            'currency'          => '978',
            'orderId'           => '',
            'email'             => '',
            'billing'           => array(
                'civility'          => null,
                'firstName'         => null,
                'lastName'          => null,
                'address1'          => null,
                'address2'          => null,
                'address3'          => null,
                'city'              => null,
                'zipcode'           => null,
                'country'           => null,
                'state'             => null,
                'email'             => null,
                'phone'             => null,
                'mobile'            => null,
            ),
            'shipping'          => array(
                'civility'          => null,
                'firstName'         => null,
                'lastName'          => null,
                'address1'          => null,
                'address2'          => null,
                'address3'          => null,
                'city'              => null,
                'zipcode'           => null,
                'country'           => null,
                'state'             => null,
                'email'             => null,
                'phone'             => null,
                'mobile'            => null,
            ),
            'client'            => array(
                'civility'          => null,
                'firstName'         => null,
                'lastName'          => null,
                'address1'          => null,
                'address2'          => null,
                'address3'          => null,
                'city'              => null,
                'zipcode'           => null,
                'country'           => null,
                'state'             => null,
                'email'             => null,
                'phone'             => null,
                'mobile'            => null,
                'birthCity'         => null,
                'birthZipcode'      => null,
                'birthCountry'      => null,
                'birthDate'         => null,
            ),
            'backURL_Cancel'    => '',
            'backURL_OK'        => '',
            'backURL_Response'  => ''
        );
        $params = array_merge($defaultParams, $params);

        /* Load client */
        $this->load_PaylineClient();

        /* Set Payment details */
        $payment = array();
        $payment['amount'] = (int)($params['amount'] * 100);
        $payment['currency'] = $params['currency'];
        $payment['action'] = 101; // 100 for Authorization only, 101 for Auth + Capture
        $payment['mode'] = 'CPT'; // CPT = Cash/Full Payment
        $payment['contractNumber'] = $this->get_configValue('contractNumber');

        /* Set Order details */
        $order = array();
        $order['ref'] = $params['orderId'];
        $order['amount'] = $payment['amount'];
        $order['currency'] = $payment['currency'];

        // Ensure date is according to Payline format 'd/m/Y H:i'
        $order['date'] = date('d/m/Y H:i');

        /* Prepare Buyer details */
        $billingCountry = is_null($params['billing']['country']) ? $params['client']['country'] : $params['billing']['country'];
        $shippingCountry = is_null($params['shipping']['country']) ? $params['client']['country'] : $params['shipping']['country'];

        /* Set Buyer details */
        $buyer = array();
        $buyer['title'] = !empty($params['client']['civility']) ? $params['client']['civility'] : '';
        $buyer['lastName'] = !empty($params['client']['lastName']) ? $params['client']['lastName'] : '';
        $buyer['firstName'] = !empty($params['client']['firstName']) ? $params['client']['firstName'] : '';
        $buyer['email'] = !empty($params['client']['email']) ? $params['client']['email'] : $params['email'];


        /* Set Buyer Shipping Address details */
        $buyer['shippingAddress'] = array();
        $buyer['shippingAddress']['title']      = empty($params['shipping']['civility']) ? $buyer['title'] : $params['shipping']['civility'];
        $buyer['shippingAddress']['firstName']  = empty($params['shipping']['firstName']) ? $params['client']['firstName'] : $params['shipping']['firstName'];
        $buyer['shippingAddress']['lastName']   = empty($params['shipping']['lastName']) ? $params['client']['lastName'] : $params['shipping']['lastName'];
        $buyer['shippingAddress']['street1']    = empty($params['shipping']['address1']) ? $params['client']['address1'] : $params['shipping']['address1'];
        $buyer['shippingAddress']['street2']    = empty($params['shipping']['address2']) ? $params['client']['address2'] : $params['shipping']['address2'];
        $buyer['shippingAddress']['cityName']   = empty($params['shipping']['city']) ? $params['client']['city'] : $params['shipping']['city'];
        $buyer['shippingAddress']['zipCode']    = empty($params['shipping']['zipcode']) ? $params['client']['zipcode'] : $params['shipping']['zipcode'];
        $buyer['shippingAddress']['country']    = strToUpper($shippingCountry);
        $buyer['shippingAddress']['state']      = empty($params['shipping']['state']) ? (empty($params['client']['state']) ? '' : $params['client']['state']) : $params['shipping']['state'];
        $buyer['shippingAddress']['email']      = empty($params['shipping']['email']) ? (empty($params['client']['email']) ? $params['email'] : $params['client']['email']) : $params['shipping']['email'];
        $buyer['shippingAddress']['phone']      = $this->format_phoneNumber(empty($params['shipping']['mobile']) ? $params['client']['mobile'] : $params['shipping']['mobile'], $shippingCountry);

        /* Set Buyer Billing Address details */
        $buyer['billingAddress'] = array();
        $buyer['billingAddress']['title']       = empty($params['billing']['civility']) ? $buyer['title'] : $params['billing']['civility'];
        $buyer['billingAddress']['firstName']   = empty($params['billing']['firstName']) ? $params['client']['firstName'] : $params['billing']['firstName'];
        $buyer['billingAddress']['lastName']    = empty($params['billing']['lastName']) ? $params['client']['lastName'] : $params['billing']['lastName'];
        $buyer['billingAddress']['street1']     = empty($params['billing']['address1']) ? $params['client']['address1'] : $params['billing']['address1'];
        $buyer['billingAddress']['street2']     = empty($params['billing']['address2']) ? $params['client']['address2'] : $params['billing']['address2'];
        $buyer['billingAddress']['cityName']    = empty($params['billing']['city']) ? $params['client']['city'] : $params['billing']['city'];
        $buyer['billingAddress']['zipCode']     = empty($params['billing']['zipcode']) ? $params['client']['zipcode'] : $params['billing']['zipcode'];
        $buyer['billingAddress']['country']     = strToUpper($billingCountry);
        $buyer['billingAddress']['state']       = empty($params['billing']['state']) ? (empty($params['client']['state']) ? '' : $params['client']['state']) : $params['billing']['state'];
        $buyer['billingAddress']['email']       = empty($params['billing']['email']) ? (empty($params['client']['email']) ? $params['email'] : $params['client']['email']) : $params['billing']['email'];
        $buyer['billingAddress']['phone']       = $this->format_phoneNumber(empty($params['billing']['mobile']) ? $params['client']['mobile'] : $params['billing']['mobile'], $billingCountry);

        /* Array data for doWebPayment */
        $doWebPaymentRequest = array();
        $doWebPaymentRequest['version'] = $this->paylineSDKVersion;
        $doWebPaymentRequest['payment'] = $payment;
        $doWebPaymentRequest['order'] = $order;
        $doWebPaymentRequest['buyer'] = $buyer;
        $doWebPaymentRequest['selectedContractList'] = array();
        $doWebPaymentRequest['returnURL'] = $params['backURL_OK'];
        $doWebPaymentRequest['cancelURL'] = $params['backURL_Cancel'];
        $doWebPaymentRequest['notificationURL'] = $params['backURL_Response'];
        $doWebPaymentRequest['securityMode'] = 'SSL';
        $doWebPaymentRequest['languageCode'] = 'fr';

        $response = $this->paylineClient->doWebPayment($doWebPaymentRequest);

        if (isset($response['result']['code']) && $response['result']['code'] === '00000') {
            $this->redirectURL = $response['redirectURL'];

            /* Add JS redirect */
            $camyks->HTMLPage->add_JSLoadScript('setTimeout(function(){ window.location.href="'.$this->redirectURL.'"; }, 1500);');

            return true;
        } else {
            if (isset($response['result']['longMessage'])) {
                $this->set_lastError((int)$response['result']['code'], $response['result']['longMessage']);
                $camyks->log_executionerror($this, 'Bank connection failed.', '['.$response['result']['code'].'] '.$response['result']['longMessage']);
            }

            /* Update layout */
            $this->redirectURL = $params['backURL_Cancel'];
            $this->set_selectedLayout('input_error.html.inc');

            return false;
        }
    }

    /**
     * Load confirmation data Payline instant notification.
     * @return void
     */
    public function load_paymentConfirmation() {
        if (isset($_REQUEST['token'])) {
            $this->confirmationData = $_REQUEST['token'];
        }
    }

    /**
     * Get payment details from Payline.
     * @return array
     */
    private function get_paymentDetails() {
        if ($this->responseData !== null)
            return $this->responseData;

        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();

        if (empty($this->confirmationData))
            return null;

        $this->load_PaylineClient();

        $this->responseData = $this->paylineClient->getWebPaymentDetails(array(
            'version' => $this->paylineSDKVersion,
            'token' => $this->confirmationData,
        ));

        return $this->responseData;
    }

    /**
     * Check if payment is confirmed.
     * @return boolean result
     */
    public function is_paymentConfirmed() {
        $response = $this->get_paymentDetails();

        if ($response === null || !isset($response['result']['shortMessage']))
            return false;

        if ($response['result']['shortMessage'] === 'ACCEPTED')
            return true;

        return false;
    }

    /**
     * Check if payment is cancelled.
     * @return boolean result
     */
    public function is_paymentCancelled() {
        $response = $this->get_paymentDetails();

        if ($response === null || !isset($response['result']['shortMessage']))
            return false;

        /* Payment can be Cancelled or Refused */
        if ($response['result']['shortMessage'] === 'CANCELLED' || $response['result']['shortMessage'] === 'REFUSED')
            return true;

        return false;
    }

    /**
     * Return response data from confirmation request.
     * @return array
     */
    public function get_paymentConfirmationData() {
        $response = $this->get_paymentDetails();
        $data = array();

        if ($response !== null) {
            $data['uniqueId'] = isset($response['order']['ref']) ? $response['order']['ref'] : '';
            $data['transaction'] = isset($response['transaction']['id']) ? $response['transaction']['id'] : '';
            $data['response'] = isset($response['result']['shortMessage']) ? $response['result']['shortMessage'] : '';
            if (isset($response['payment']['amount'])) {
                $data['amount'] = $response['payment']['amount'] / 100;
            }
        } else {
            $data['uniqueId'] = '';
            $data['transaction'] = '';
            $data['response'] = '';
        }
        return $data;
    }

    /* Mark: Display methods */

    /**
     * Return manual transfer link.
     * @return string
     */
    public function get_manualTransferLink() {
        if (isset($this->paymentForm))
            return $this->paymentForm->get_HTMLSubmitLink();
        elseif ($this->redirectURL !== '')
            return '<a href="'.$this->redirectURL.'">'.$this->get_translation('manualtransfer').'</a>';
        return '';
    }

    /* Mark: Error handling methods */

    /**
     * Define last error.
     * @param integer $errorCode
     * @param string $errorMsg
     */
    private function set_lastError($errorCode, $errorMsg) {
        $this->_lastErrorCode = $errorCode;
        $this->_lastErrorMsg = $errorMsg;
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

    /* Mark: Configuration related methods */

    /**
     * Load plugin configuration
     * @return void
     */
    public function load_configuration() {
        /* load configuration library */
        $this->load_library('PaylinePaymentConfig');

        /* load config */
        $this->config = new PaylinePaymentConfig('config', $this);
        $this->config->get();
    }

    /**
     * Return configuration value
     * @param string $name
     * @param mixed $default
     * @return mixed
     */
    private function get_configValue($name, $default=null) {
        return $this->config->get_value($name, $default);
    }

    /* Mark: Private tool methods */

    /**
     * Format phone number.
     * @param string $phoneNumber
     * @param string $countryCode
     * @return string
     */
    public function format_phoneNumber($phoneNumber, $countryCode) {
        global $camyks;

        /* Check values */
        if (is_null($phoneNumber) or is_null($countryCode))
            return null;

        /* Clean phone number */
        $phoneNumber = preg_replace('/[^0-9]/', '', $phoneNumber);

        /* Load country phone index */
        $index = countries_getPhonePrefix($countryCode);

        /* Format with initial index */
        if (strpos($phoneNumber, $index) === 0)
            return '+00'.$index.substr($phoneNumber, 2);

        /* Format with initial 0 */
        elseif (strpos($phoneNumber, '0') === 0)
            return '+00'.$index.substr($phoneNumber, 1);

        /* By default return number */
        return $phoneNumber;
    }

    /* Mark: Admin_Site extension configuration methods */

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
        $this->load_file('html/Configuration/View.html.inc');
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
        $this->load_file('html/Configuration/Edit.html.inc');
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
