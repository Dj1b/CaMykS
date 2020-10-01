<?php
/**
 * @brief PayZenPayment Input
 * <br /> Interface to PayZen payment system.
 * @details Plugin / Input Engine
 * @file plugin/input/PayZenPayment/PayZenPayment.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2018
 * @date Modification: Dec 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PayZenPayment Input class.
 */
final class PayZenPayment extends Input {
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
     * var string $_transactionId
     * @brief Transaction id.
     */
    private $_transactionId = '';

    /**
     * var array $transactionParams
     * @brief Transaction params.
     */
    private $transactionParams = array(
        'action_mode'           => 'INTERACTIVE',
        'amount'                => 0,
        'currency'              => '978',
        'page_action'           => 'PAYMENT',
        'payment_config'        => 'SINGLE',
        'trans_date'            => '',
        'trans_id'              => '',
        'version'               => 'V2',
    );

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
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('PayZenPayment', $path_type);

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

        $defaultParams = array('amount' => 0, 'orderId' => '');
        $params = array_merge($defaultParams, $params);

        /* update default transaction params */
        date_default_timezone_set('UTC');
        $this->transactionParams['trans_date'] = date('YmdHis');

        /* add buildin config */
        $this->transactionParams['site_id'] = $this->config->vars['site_id'];
        $this->transactionParams['ctx_mode'] = $this->config->vars['ctx_mode'];

        /* merge params */
        $this->transactionParams['amount'] = $params['amount'];
        $this->transactionParams['trans_id'] = $params['orderId'];

        /* fix params */
        $this->transactionParams['amount'] = (int)($this->transactionParams['amount']*100);

        /* Sort keys */
        ksort($this->transactionParams);

        /* compute signature */
        if ($this->config->vars['ctx_mode'] === 'TEST')
            $signature = $this->compute_signature($this->transactionParams, $this->config->vars['bankKey_test'], $this->config->vars['hash_mode']);
        else
            $signature = $this->compute_signature($this->transactionParams, $this->config->vars['bankKey_live'], $this->config->vars['hash_mode']);

        /* build CB specific form */
        $this->paymentForm = new HTMLForm('paymentRequest', 'https://secure.payzen.eu/vads-payment/', 'POST');
        $this->paymentForm->add_hidden('signature', $signature);
        foreach ($this->transactionParams as $key => $value)
            $this->paymentForm->add_hidden('vads_'.$key, $value);

        /* add scripts */
        $this->add_JSLoadScript('setTimeout("'.$this->paymentForm->get_JSSubmitLink().'", 4000);');
    }

    /* data query methods */

    /**
     * Load confirmation data Payzen instant notification.
     * @return void
     */
    public function load_paymentConfirmation() {
        $this->confirmationData = $_REQUEST;
    }

    /**
     * Check if payment is confirmed.
     * @return boolean result
     */
    public function is_paymentConfirmed() {
        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();

        if (!isset($this->confirmationData['vads_trans_status']))
            return false;

        if ($this->confirmationData['vads_trans_status'] === 'AUTHORISED')
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

        if (!isset($this->confirmationData['vads_trans_status']))
            return false;

        if ($this->confirmationData['vads_trans_status'] === 'ABANDONED')
            return true;

        return false;
    }

    /**
     * Return response data from confirmation request.
     * @return array
     */
    public function get_paymentConfirmationData() {
        $data = array();
        $data['uniqueId'] = isset($this->confirmationData['vads_trans_id']) ? $this->confirmationData['vads_trans_id'] : '';
        $data['transaction'] = isset($this->confirmationData['vads_trans_uuid']) ? $this->confirmationData['vads_trans_uuid'] : '';
        $data['response'] = isset($this->confirmationData['vads_trans_status']) ? $this->confirmationData['vads_trans_status'] : '';
        return $data;
    }

    /**
     * Execute check out.
     * @return array
     */
    public function execute_checkout() {
        $this->_transactionId = isset($_REQUEST['vads_trans_uuid'])?$_REQUEST['vads_trans_uuid']:'';
        if (isset($_REQUEST['vads_trans_status']) and $_REQUEST['vads_trans_status'] === 'AUTHORISED')
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

    /* tool methods */

    /**
     * Load plugin configuration
     * @return void
     */
    public function load_configuration() {
        /* load configuration library */
        $this->load_library('PayZenPaymentConfig');

        /* load config */
        $this->config = new PayZenPaymentConfig('config', $this);
        $this->config->get();
    }

    /**
     * Compute signature from params and key.
     * @param array $params
     * @param string $key
     * @param string $hash
     * @return string
     */
    public function compute_signature($params, $key, $hash) {
        /* Initialise signature content */
        $cs = '';

        /* Add params to content */
        foreach ($params as $name => $value) {
            $cs .= $value.'+';
        }

        /* Add key to content */
        $cs .= $key;

        /* Return hashed signature */
        switch ($hash) {
            case 'SHA-1': return sha1($cs);
            case 'HMAC-SHA-256': return base64_encode(hash_hmac('sha256', $cs, $key, true));
        }
        return '';
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
