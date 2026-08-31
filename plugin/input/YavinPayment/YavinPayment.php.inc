<?php
/**
 * @brief YavinPayment Input
 * <br /> Interface to Yavin platform payment system.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: May 2026
 * @date Modification: May 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * YavinPayment Input class.
 */
final class YavinPayment extends Input {
    /**
     * @var Object $config
     * @brief Configuration library.
     */
    protected $config = null;

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
     * @var string $transactionId
     * @brief Created transaction Id.
     */
    private $transactionId = '';

    /**
     * @var array $confirmationData
     * @brief Yavin feedback data.
     */
    private $confirmationData = null;

    /**
     * @var string $redirectURL
     * @brief Yavin payment redirect URL.
     */
    protected $redirectURL = '';

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('YavinPayment', $path_type);

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
            'currency'          => 'EUR',
            'orderId'           => '',
            'backURL_Cancel'    => '',
            'backURL_OK'        => '',
            'backURL_Response'  => '' // webhook URL
        );
        $params = array_merge($defaultParams, $params);

        /* Determine API Key and Endpoint */
        $apiKey = ($this->get_configValue('runningMode') === 'production')
            ? $this->get_configValue('productionAPIKey')
            : $this->get_configValue('testAPIKey');

        /* Endpoint for Yavin API - Note: adjust according to actual doc */
        $apiUrl = ($this->get_configValue('runningMode') === 'production')
            ? 'https://api.yavin.com/api/v5/ecommerce/generate_link/'
            : 'https://api.sandbox.yavin.com/api/v5/ecommerce/generate_link/';

        /* Build Request Payload */
        $payload = array(
            'order_number' => $params['orderId'],
            'cart_id' => $params['orderId'].rand(1000,9999),
            'return_url_success' => $params['backURL_OK'],
            'return_url_cancelled' => $params['backURL_Cancel'],
            'webhook_url' => $params['backURL_Response'],
            'amount' => (int)($params['amount'] * 100), // usually in cents
            'is_instant_capture' => true,
            'capture_min_delay' => 0,
            'order_source' => 'ecommerce',
            //'datetime' => date("d/m/Y:H:i:s"),
            'currency' => $params['currency'],
            'customer' => array(
                'first_name'    => $params['client']['firstName'],
                'last_name'     => $params['client']['lastName'],
                'email'         => !empty($params['client']['email']) ? $params['client']['email'] : $params['email'],
                'phone'         => !empty($params['client']['mobile']) ? $this->format_phoneNumber($params['client']['mobile'], 'fr') : '',
            ),
            'items' => array(),
        );

        /* Build vendor data */
        $vendor = array();
        if (!empty($params['vendor'])) {
            if (!empty($params['vendor']['brandName'])) $vendor['brand_name'] = $params['vendor']['brandName'];
            if (!empty($params['vendor']['legalName'])) $vendor['legal_name'] = $params['vendor']['legalName'];
            if (!empty($params['vendor']['country'])) $vendor['country'] = $params['vendor']['country'];
            if (!empty($params['vendor']['merchantId'])) $vendor['merchant_id'] = $params['vendor']['merchantId'];
            if (!empty($params['vendor']['merchantCategoryCode'])) $vendor['merchant_category_code'] = $params['vendor']['merchantCategoryCode'];
            if (!empty($params['vendor']['softwareName'])) $vendor['software_name'] = $params['vendor']['softwareName'];
            if (!empty($params['vendor']['softwareVersion'])) $vendor['software_version'] = $params['vendor']['softwareVersion'];
        } else {
            if ($this->get_configValue('vendorBrandName') !== '') $vendor['brand_name'] = $this->get_configValue('vendorBrandName');
            if ($this->get_configValue('vendorSoftwareName') !== '') $vendor['software_name'] = $this->get_configValue('vendorSoftwareName');
            if ($this->get_configValue('vendorSoftwareVersion') !== '') $vendor['software_version'] = $this->get_configValue('vendorSoftwareVersion');
        }
        if ($vendor !== array())
            $payload['vendor'] = $vendor;

        /* Add items to Payload */
        foreach ($params['shoppingCart'] as $item) {
            $i = array(
                'eligible_titre_restaurant' => true,
                'name' => $item['articleTitle'],
                'quantity' => $item['quantity'],
                'total_amount' => (int)($item['quantity']*$item['price']*100),
                'unit_price' => $item['price']*100,
                //'items' => array(),
            );

            if ($item['parentId'] > 0 and isset($payload['items'][$item['parentId']])) {
                if (!isset($payload['items'][$item['parentId']]['items']))
                    $payload['items'][$item['parentId']]['items'] = array();
                $payload['items'][$item['parentId']]['items'][] = $i;
            } else
                $payload['items'][$item['id']] = $i;
        }
        $payload['items'] = array_values($payload['items']);

        /* Call Yavin API via http_getContents */
        $responseBody = http_getContents(array(
            'url'     => $apiUrl,
            'engine'  => 'curl',
            'method'  => 'POST',
            'values'  => json_encode($payload),
            'headers' => array(
                'Content-Type' => 'application/json',
                'Yavin-Secret' => $apiKey,
            ),
        ));

        $response = json_decode($responseBody, true);

        if ($responseBody !== false && is_array($response) && isset($response['payment_link'])) {
            $this->redirectURL = $response['payment_link'];

            /* Add JS redirect */
            $camyks->HTMLPage->add_JSLoadScript('setTimeout(function(){ window.location.href="'.$this->redirectURL.'"; }, 1500);');

            /* Provide fallback link */
            $this->paymentForm = new HTMLForm('paymentRequest', $this->redirectURL, 'GET');

            return true;
        } else {
            if (!empty($response['errors'])) {
                $errorMsg = 'Link request errors: '."\n".YavinPayment_readPayloadErrors('', $response['errors']);
            } else {
                $errorMsg = 'Unknown Yavin API error';
            }

            $this->set_lastError(0, $errorMsg);
            $camyks->log_executionerror($this, 'Bank connection failed.', $errorMsg);

            /* Update layout */
            $this->redirectURL = $params['backURL_Cancel'];
            $this->set_selectedLayout('input_error.html.inc');

            return false;
        }
    }

    /**
     * Load confirmation data Yavin instant notification (webhook or redirect).
     * @return void
     */
    public function load_paymentConfirmation() {
        global $camyks;

        // Handle webhook payload (JSON) or GET/POST parameters
        $jsonStr = file_get_contents('php://input');
        if (!empty($jsonStr)) {
            $this->confirmationData = json_decode($jsonStr, true);
        } else {
            $this->confirmationData = $_REQUEST;
        }

        //$camyks->log('Yavin', 'ConfirmationData', var_export($this->confirmationData, true));
    }

    /**
     * Check if payment is confirmed.
     * @return boolean result
     */
    public function is_paymentConfirmed() {
        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();

        // Adjust based on actual Yavin webhook format
        if (isset($this->confirmationData['status']) && $this->confirmationData['status'] === 'ok') {
            return true;
        }

        return false;
    }

    /**
     * Check if payment is cancelled.
     * @return boolean result
     */
    public function is_paymentCancelled() {
        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();

        if (isset($this->confirmationData['status']) && $this->confirmationData['status'] === 'ko') {
            return true;
        }

        return false;
    }

    /**
     * Return response data from confirmation request.
     * @return array
     */
    public function get_paymentConfirmationData() {
        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();

        $data = array();

        $data['uniqueId'] = isset($this->confirmationData['cart_id']) ? substr($this->confirmationData['cart_id'], 0, -4) : '';
        $data['transaction'] = isset($this->confirmationData['transactions'][0]['transaction_id']) ? $this->confirmationData['transactions'][0]['transaction_id'] : '';
        $data['response'] = isset($this->confirmationData['status']) ? $this->confirmationData['status'] : '';

        if (isset($this->confirmationData['amount'])) {
            $data['amount'] = $this->confirmationData['amount'] / 100;
        }

        return $data;
    }

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

    /* Mark: Refund methods */

    /**
     * Return if refund can be done.
     * @return boolean result
     */
    public function can_refundPayment() {
        return true;
    }

    /**
     * Execute refund.
     * @param array $params
     * @return boolean result
     */
    public function execute_refund($params=array()) {
        global $camyks;

        $defaultParams = array(
            'amount'            => 0,
            'transactionId'     => '',
            'userEmail'         => '',
            'prioritiseTip'     => false,
        );
        $params = array_merge($defaultParams, $params);

        /* Determine API Key and Endpoint */
        $apiKey = ($this->get_configValue('runningMode') === 'production')
            ? $this->get_configValue('productionAPIKey')
            : $this->get_configValue('testAPIKey');

        /* Endpoint for Yavin API - Note: adjust according to actual doc */
        $apiUrl = ($this->get_configValue('runningMode') === 'production')
            ? 'https://api.yavin.com/api/v5/transaction/'.$params['transactionId'].'/refund/'
            : 'https://api.sandbox.yavin.com/api/v5/transaction/'.$params['transactionId'].'/refund/';

        /* Build Request Payload */
        $payload = array(
            'amount'            => (int)($params['amount'] * 100),
            'user_email'        => empty($this->get_configValue('settingAdminEmail')) ? $params['userEmail'] : $this->get_configValue('settingAdminEmail'),
            'prioritise_tip'    => $params['prioritiseTip'],
        );

        /* Build vendor data */
        $vendor = array();
        if (!empty($params['vendor'])) {
            if (!empty($params['vendor']['brandName'])) $vendor['brand_name'] = $params['vendor']['brandName'];
            if (!empty($params['vendor']['legalName'])) $vendor['legal_name'] = $params['vendor']['legalName'];
            if (!empty($params['vendor']['country'])) $vendor['country'] = $params['vendor']['country'];
            if (!empty($params['vendor']['merchantId'])) $vendor['merchant_id'] = $params['vendor']['merchantId'];
            if (!empty($params['vendor']['merchantCategoryCode'])) $vendor['merchant_category_code'] = $params['vendor']['merchantCategoryCode'];
            if (!empty($params['vendor']['softwareName'])) $vendor['software_name'] = $params['vendor']['softwareName'];
            if (!empty($params['vendor']['softwareVersion'])) $vendor['software_version'] = $params['vendor']['softwareVersion'];
        } else {
            if ($this->get_configValue('vendorBrandName') !== '') $vendor['brand_name'] = $this->get_configValue('vendorBrandName');
            if ($this->get_configValue('vendorSoftwareName') !== '') $vendor['software_name'] = $this->get_configValue('vendorSoftwareName');
            if ($this->get_configValue('vendorSoftwareVersion') !== '') $vendor['software_version'] = $this->get_configValue('vendorSoftwareVersion');
        }
        if ($vendor !== array())
            $payload['vendor'] = $vendor;

        /* Call Yavin API via http_getContents */
        $responseBody = http_getContents(array(
            'url'     => $apiUrl,
            'engine'  => 'curl',
            'method'  => 'POST',
            'values'  => json_encode($payload),
            'headers' => array(
                'Content-Type' => 'application/json',
                'Yavin-Secret' => $apiKey,
            ),
        ));

        /* Load response status */
        $status = http_getStatusFromLastContentRequest(array(
            'engine'  => 'curl',
        ));

        /* Check status */
        if ($status === false) {
            $camyks->log_executionerror($this, 'Undefined status while receiving refund response.', $errorMsg);
            return array(
                'status'    => 'failure',
                'error'     => 'Undefined status.',
            );
        }

        /* Load response content */
        $response = json_decode($responseBody, true);

        if ($status == 201) {
            if ($response['message'] == 'ok' and $response['status'] == 'refunded')
                return array(
                    'status'        => 'success',
                    'transactionId' => $response['transaction_id'],
                );
        } elseif ($status == 202 and $response['message'] == 'ok') {
            if ($response['status'] == 'pending')
                return array(
                    'status'        => 'pending',
                    'transactionId' => $response['transaction_id'],
                );
            if ($response['status'] == 'waiting')
                return array(
                    'status'        => 'requiresApproval',
                    'transactionId' => $response['transaction_id'],
                    'approvalURL'   => $response['approval_url'],
                );
        } elseif ($status == 400) {
            if (isset($response['error']))
                return array(
                    'status'    => 'failure',
                    'error'     => $response['error'],
                );
            else
                 return array(
                    'status'    => 'failure',
                    'errors'     => $response,
                );
        } elseif ($status == 403) {
            if (isset($response['detail']))
                return array(
                    'status'    => 'failure',
                    'error'     => $response['detail'],
                );
            else
                 return array(
                    'status'    => 'failure',
                    'errors'     => $response,
                );
        } elseif ($status == 422) {
            return array(
                'status'    => 'failure',
                'error'     => $response['message'],
            );
        }

        /* Log error */
        $camyks->log_executionerror($this, 'Unknown status while receiving refund response.', var_export($response, true));

        /* By default, return failure */
        return array(
            'status'    => 'failure',
            'error'     => 'Unknown status.',
        );
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
    protected function load_configuration() {
        /* load configuration library */
        $this->load_library('YavinPaymentConfig');

        /* load config */
        $this->config = new YavinPaymentConfig('config', $this);
        $this->config->get();
    }

    /**
     * Return configuration value
     * @param string $name
     * @param mixed $default
     * @return mixed
     */
    public function get_configValue($name, $default=null) {
        if (is_null($this->config))
            $this->load_configuration();
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
            return '+'.$index.substr($phoneNumber, 2);

        /* Format with initial 0 */
        elseif (strpos($phoneNumber, '0') === 0)
            return '+'.$index.substr($phoneNumber, 1);

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

/**
 * Recursive method to read Yavin payload request errors.
 * @param string $basis
 * @param array $errors
 * @return string
 */
function YavinPayment_readPayloadErrors($basis, $errors) {
    /* Initialise message */
    $message = '';

    /* Read errors */
    foreach ($errors as $name => $value) {
        if (is_string($value))
            $message .= $basis.' - '.$name.' : '.$value."\n";
        elseif (is_array($value))
            $message .= YavinPayment_readPayloadErrors($basis.' - '.$name, $value);
    }

    /* Return message */
    return $message;
}
?>
