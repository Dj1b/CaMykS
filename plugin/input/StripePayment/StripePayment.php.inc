<?php
/**
 * @brief StripePayment Input
 * <br /> Interface to Stripe payment system.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2020
 * @date Modification: Jul 2024
 * @copyright 2020 - 2024 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @note Stripe version 7.54.0
 */

/**
 * StripePayment Input class.
 */
final class StripePayment extends Input {
    /**
     * var integer $_lastErrorCode
     * @brief Last error code.
     */
    private $_lastErrorCode = 0;

    /**
     * var string $_lastErrorMsg
     * @brief Last error message.
     */
    private $_lastErrorMsg = '';

    /**
     * var array $params
     * @brief Input parameters.
     */
    public $params = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('StripePayment', $path_type);

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

    /* Override input methods */

    /**
     * Install input
     * @return boolean success
     */
    public function install() {
        return $this->install_htaccessRules() and parent::install();
    }

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

    /**
     * Execute input in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        $camyks->get_siteInit();

        $action = isset($_REQUEST['action']);

        switch ($action) {
            case 'create-payment-intent': return $this->execute_request_createPaymentIntent();
        }

    }

    /* Request mode methods */

    /**
     * Execute input in create payment intent mode.
     * @return void
     */
    private function execute_request_createPaymentIntent() {
        global $camyks;

        /* load plugin configuration */
        $this->load_configuration();

        /* Get back amount */
        $data = $camyks->get_sessionValue('StripePaymentData');

        /* Load stripe */
        $this->load_file('stripe-php/init.php');

        /* Load API keys */
        if ($this->get_configValue('runningMode') == 'production') {
            $privateAPIKey = $this->get_configValue('productionAPIKey_private');
            $publicAPIKey = $this->get_configValue('productionAPIKey_public');
        } else {
            $privateAPIKey = $this->get_configValue('testAPIKey_private');
            $publicAPIKey = $this->get_configValue('testAPIKey_public');
        }

        $stripe = new \Stripe\StripeClient(array(
            'api_key' => $privateAPIKey,
            'stripe_version' => '2020-08-27',
        ));

        /* Create intent */
        $intent = $stripe->paymentIntents->create(array(
            'amount'    => $data['amount']*100,
            'currency'  => $data['currency'],
            // Verify your integration in this guide by including this parameter
            'metadata'  => array('integration_check' => 'accept_a_payment'),
        ));

        /* Create output */
        $output = array(
            'publishableKey'    => $publicAPIKey,
            'clientSecret'      => $intent->client_secret,
        );

        /* Output result */
        header('Content-Type: application/json');
        echo json_encode($output);
    }

    /* execution methods */

    /**
     * Prepare for payment.
     * @param array $params
     * @return boolean result
     */
    public function prepare_forPayment($params=array()) {
        global $camyks;

        $defaultParams = array('amount' => 0, 'currency'=> 'eur', 'orderId' => '', 'backURL_Response' => '', 'backURL_OK' => '');
        $params = array_merge($defaultParams, $params);

        /* Save amount value in session */
        $camyks->set_sessionValue('StripePaymentData', array(
            'amount'    => $params['amount'],
            'currency'  => $params['currency'],
        ));

        /* Add Stripe JS File */
        $camyks->HTMLPage->add_JSFile('https://js.stripe.com/v3/');

        /* Add Stripe JS scripts */
        if ($this->get_configValue('runningMode') == 'production')
            $this->add_JSScript('var stripe = Stripe("'.$this->get_configValue('productionAPIKey_public').'");');
        else
            $this->add_JSScript('var stripe = Stripe("'.$this->get_configValue('testAPIKey_public').'");');

        $this->add_JSScript('var elements = stripe.elements();');

        /* Add some data */
        $this->add_JSScript('var orderId = "'.$params['orderId'].'";');
        $this->add_JSScript('var createIntentURL = "stripe.create-payment-intent";');
        $this->add_JSScript('var backURL_OK = "'.$params['backURL_OK'].'";');
        $this->add_JSScript('var backURL_Response = "'.$params['backURL_Response'].'";');

        /* Add Stripe CSS */
        $this->add_styleFile('global.css?v=1.0.1');
        $this->add_styleFile('normalize.css');
    }

    /* data query methods */

    /**
     * Load confirmation data Payzen instant notification.
     * @return void
     */
    public function load_paymentConfirmation() {
        global $camyks;

        $this->confirmationData = $_REQUEST;

        $camyks->log('Dev', 'Post Data', json_encode($this->confirmationData));
    }

    /**
     * Check if payment is confirmed.
     * @return boolean result
     */
    public function is_paymentConfirmed() {
        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();

        if (!isset($this->confirmationData['status']))
            return false;

        if ($this->confirmationData['status'] === 'succeeded')
            return true;

        return false;
    }

    /**
     * Check if payment is cancelled.
     * @return boolean result
     */
    public function is_paymentCancelled() {
        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();

        if (!isset($this->confirmationData['status']))
            return false;

        if ($this->confirmationData['status'] !== 'succeeded')
            return true;

        return false;
    }

    /**
     * Return response data from confirmation request.
     * @return array
     */
    public function get_paymentConfirmationData() {
        $data = array();
        $data['uniqueId'] = isset($this->confirmationData['orderId']) ? $this->confirmationData['orderId'] : '';
        $data['transaction'] = isset($this->confirmationData['client_secret']) ? $this->confirmationData['client_secret'] : '';
        $data['response'] = isset($this->confirmationData['status']) ? $this->confirmationData['status'] : '';
        return $data;
    }

    /**
     * Execute check out.
     * @return array
     */
    public function execute_checkout() {
        $this->_transactionId = isset($_REQUEST['client_secret'])?$_REQUEST['client_secret']:'';
        if (isset($_REQUEST['status']) and $_REQUEST['status'] === 'succeeded')
            return true;
        return false;
    }

    /**
     * Return transaction ID.
     * @return string
     */
    public function get_transactionId() {
        return $this->_transactionId;
    }

    /* display methods */

    /**
     * Return manual transfer link.
     * @return string
     */
    public function get_manualTransferLink() {
        if (isset($this->paymentForm))
            return $this->paymentForm->get_HTMLSubmitLink();
        return '';
    }

    /* error handling methods */

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

    /* Configuration related methods */

    /**
     * Load plugin configuration
     * @return void
     */
    public function load_configuration() {
        /* load configuration library */
        $this->load_library('StripePaymentConfig');

        /* load config */
        $this->config = new StripePaymentConfig('config', $this);
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

    /* Specific tool methods */

    /**
     * Install .htaccess rules.
     * @return boolean success
     */
    private function install_htaccessRules() {
        return $this->add_toHtaccess('RewriteRule ^stripe.([a-z0-9\-]*)$ request.php?input='.$this->name.'&action=$1');
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
