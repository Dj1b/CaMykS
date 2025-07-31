<?php
/**
 * @brief MoneticoPaiement Input
 * <br /> Manage online payment with Monetico system.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.3
 * @date Creation: Apr 2017
 * @date Modification: Jul 2025
 * @copyright 2017 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MoneticoPaiement Input class.
 */
final class MoneticoPaiement extends Input {
    /**
     * var array $params
     * @brief Input parameters.
     */
    public $params = array(
        /* shop params */
        'MONETICOPAIEMENT_KEY'                  => '',
        'MONETICOPAIEMENT_EPTNUMBER'            => '',
        'MONETICOPAIEMENT_COMPANYCODE'          => '',

        /* shop URLs */
        'MONETICOPAIEMENT_URLOK'                => '',
        'MONETICOPAIEMENT_URLKO'                => '',

        /* Monetico URLs */
        'MONETICOPAIEMENT_URLSERVER'            => '',

        /* Monetico params */
        'MONETICOPAIEMENT_VERSION'              => "3.0",
        'MONETICOPAIEMENT_CTLHMAC'              => "V4.0.sha1.php--[CtlHmac%s%s]-%s",
        'MONETICOPAIEMENT_CTLHMACSTR'           => "CtlHmac%s%s",
        'MONETICOPAIEMENT_PHASE2BACK_RECEIPT'   => "version=2\ncdr=%s",
        'MONETICOPAIEMENT_PHASE2BACK_MACOK'     => "0",
        'MONETICOPAIEMENT_PHASE2BACK_MACNOTOK'  => "1\n",
        'MONETICOPAIEMENT_PHASE2BACK_FIELDS'    => "%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*",
        'MONETICOPAIEMENT_PHASE1GO_FIELDS'      => "%s*%s*%s%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s*%s",
        'MONETICOPAIEMENT_URLPAYMENT'           => "paiement.cgi",
    );

    /**
     * var integer $_lastErrorCode
     * @brief Last error code.
     */
    private $_lastErrorCode = 0;

    /**
     * var sring $_lastErrorMsg
     * @brief Last error message.
     */
    private $_lastErrorMsg = '';

    /**
     * var sring $_transactionId
     * @brief Transaction identifier.
     */
    private $_transactionId = '';

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('MoneticoPaiement', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'eCommerce';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension */
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

        /* Load configuration */
        $this->load_configuration();

        /* Input generic initialization */
        parent::initialise();
    }

    /* Mark: Execution methods */

    /**
     * Prepare for payment.
     * @param array $params
     * @return boolean result
     */
    public function prepare_forPayment($params=array()) {
        global $camyks;

        /* Set up params from given parameters */
        $paymentParams = array_recursiveMerge(array(
            'amount'            => '',
            'orderId'           => '',
            'reference'         => '',
            'email'             => '',
            'amount'            => '',
            'devise'            => 'EUR',
            'backURL_OK'        => '',
            'backURL_Cancel'    => '',
            'backURL_Refused'   => '',
            'backURL_Response'  => '',
            'backURL_Confirm'   => '',
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
            'shoppingCart'      => array(

            ),
        ), $params);

        /* Set up params urls */
        $this->params['MONETICOPAIEMENT_URLOK'] = $paymentParams['backURL_OK'];
        $this->params['MONETICOPAIEMENT_URLKO'] = $paymentParams['backURL_Refused'];

        /* Build Monetico configuration */
        $this->build_config();

        /* Load Monetico library */
        require_once($this->get_filePath('lib/MoneticoPaiement_Ept.inc.php'));

        /* Build context */
        $billingCountry = is_null($paymentParams['billing']['country']) ? $paymentParams['client']['country'] : $paymentParams['billing']['country'];
        $shippingCountry = is_null($paymentParams['shipping']['country']) ? $paymentParams['client']['country'] : $paymentParams['shipping']['country'];

        if (!is_null($paymentParams['shipping']['phone']))
            $shippingPhone = $paymentParams['shipping']['phone'];
        if (!is_null($paymentParams['shipping']['mobile']))
            $shippingPhone = $paymentParams['shipping']['mobile'];
        if (!is_null($paymentParams['client']['phone']))
            $shippingPhone = $paymentParams['client']['phone'];
        if (!is_null($paymentParams['client']['mobile']))
            $shippingPhone = $paymentParams['client']['mobile'];
        else
            $shippingPhone = null;

        $context = array(
            'billing'   => array(
                'civility'      => is_null($paymentParams['billing']['civility']) ? $paymentParams['client']['civility'] : $paymentParams['billing']['civility'],
                'firstName'     => is_null($paymentParams['billing']['firstName']) ? $paymentParams['client']['firstName'] : $paymentParams['billing']['firstName'],
                'lastName'      => is_null($paymentParams['billing']['lastName']) ? $paymentParams['client']['lastName'] : $paymentParams['billing']['lastName'],
                'addressLine1'  => is_null($paymentParams['billing']['address1']) ? $paymentParams['client']['address1'] : $paymentParams['billing']['address1'],
                'addressLine2'  => is_null($paymentParams['billing']['address2']) ? $paymentParams['client']['address2'] : $paymentParams['billing']['address2'],
                'addressLine3'  => is_null($paymentParams['billing']['address3']) ? $paymentParams['client']['address3'] : $paymentParams['billing']['address3'],
                'city'          => is_null($paymentParams['billing']['city']) ? $paymentParams['client']['city'] : $paymentParams['billing']['city'],
                'postalCode'    => is_null($paymentParams['billing']['zipcode']) ? $paymentParams['client']['zipcode'] : $paymentParams['billing']['zipcode'],
                'country'       => strToUpper($billingCountry),
                'state'         => is_null($paymentParams['billing']['state']) ? $paymentParams['client']['state'] : $paymentParams['billing']['state'],
                'email'         => is_null($paymentParams['billing']['email']) ? (is_null($paymentParams['client']['email']) ? $paymentParams['email'] : $paymentParams['client']['email']) : $paymentParams['billing']['email'],
                'phone'         => $this->format_phoneNumber(is_null($paymentParams['billing']['phone']) ? $paymentParams['client']['phone'] : $paymentParams['billing']['phone'], $billingCountry),
                'mobilePhone'   => $this->format_phoneNumber(is_null($paymentParams['billing']['mobile']) ? $paymentParams['client']['mobile'] : $paymentParams['billing']['mobile'], $billingCountry),
            ),
            'shipping'  => array(
                'civility'      => is_null($paymentParams['shipping']['civility']) ? $paymentParams['client']['civility'] : $paymentParams['shipping']['civility'],
                'firstName'     => is_null($paymentParams['shipping']['firstName']) ? $paymentParams['client']['firstName'] : $paymentParams['shipping']['firstName'],
                'lastName'      => is_null($paymentParams['shipping']['lastName']) ? $paymentParams['client']['lastName'] : $paymentParams['shipping']['lastName'],
                'addressLine1'  => is_null($paymentParams['shipping']['address1']) ? $paymentParams['client']['address1'] : $paymentParams['shipping']['address1'],
                'addressLine2'  => is_null($paymentParams['shipping']['address2']) ? $paymentParams['client']['address2'] : $paymentParams['shipping']['address2'],
                'addressLine3'  => is_null($paymentParams['shipping']['address3']) ? $paymentParams['client']['address3'] : $paymentParams['shipping']['address3'],
                'city'          => is_null($paymentParams['shipping']['city']) ? $paymentParams['client']['city'] : $paymentParams['shipping']['city'],
                'postalCode'    => is_null($paymentParams['shipping']['zipcode']) ? $paymentParams['client']['zipcode'] : $paymentParams['shipping']['zipcode'],
                'country'       => strToUpper($shippingCountry),
                'state'         => is_null($paymentParams['shipping']['state']) ? $paymentParams['client']['state'] : $paymentParams['shipping']['state'],
                'email'         => is_null($paymentParams['shipping']['email']) ? (is_null($paymentParams['client']['email']) ? $paymentParams['email'] : $paymentParams['client']['email']) : $paymentParams['shipping']['email'],
                'phone'         => $this->format_phoneNumber($shippingPhone, $shippingCountry),
            ),
        );
        $context = base64_encode(json_encode($context));

        /* define language */
        $lg = $this->config->get_value('country_code');

        $oEpt = new MoneticoPaiement_Ept($lg);
        $oHmac = new MoneticoPaiement_Hmac($oEpt);

        // Control String for support
        $CtlHmac = sprintf(MONETICOPAIEMENT_CTLHMAC, MONETICOPAIEMENT_VERSION, $oEpt->sVersion, $oEpt->sNumero, $oHmac->computeHmac(sprintf(MONETICOPAIEMENT_CTLHMACSTR, $oEpt->sVersion, $oEpt->sNumero)));

        /* merge params */
        $this->transactionParams = array(
            'date' => date("d/m/Y:H:i:s"),
            'montant' => string_numberFormat($paymentParams['amount'], 2, 'num').$paymentParams['devise'],
            'reference' => $paymentParams['orderId'],
            'lgue' => in_array(strtoupper($camyks->current_language), array('DE', 'EN', 'ES', 'FR', 'IT', 'JA', 'NL', 'PT', 'SV')) ? $lg : 'FR',
            'texte-libre' => '',
            'mail' => $paymentParams['email'],
            'version' => $oEpt->sVersion,
            'TPE' => $oEpt->sNumero,
            'MAC' => '',
            'societe' => $oEpt->sCodeSociete,
            'contexte_commande' => $context,
            'url_retour' => $oEpt->sUrlKO,
            'url_retour_ok' => $oEpt->sUrlOK,
            'url_retour_err' => $oEpt->sUrlKO,

            /* for split payment */
            'nbrech' => '',
            'dateech1' => '',
            'montantech1' => '',
            'dateech2' => '',
            'montantech2' => '',
            'dateech3' => '',
            'montantech3' => '',
            'dateech4' => '',
            'montantech4' => '',
        );

        /* Duplicate for Hmac computation */
        $fields = array(
            'TPE' => $this->transactionParams['TPE'],
            'contexte_commande' => $this->transactionParams['contexte_commande'],
            'date' => $this->transactionParams['date'],
            'lgue' => $this->transactionParams['lgue'],
            'mail' => $this->transactionParams['mail'],
            'montant' => $this->transactionParams['montant'],
            'reference' => $this->transactionParams['reference'],
            'societe' => $this->transactionParams['societe'],
            'texte-libre' => $this->transactionParams['texte-libre'],
            'url_retour' => $this->transactionParams['url_retour_err'],
            'url_retour_err' => $this->transactionParams['url_retour_err'],
            'url_retour_ok' => $this->transactionParams['url_retour_ok'],
            'version' => $this->transactionParams['version'],
        );
        if ($this->transactionParams['nbrech'] != '')
            $fields = array_merge($fields, array(
                'dateech1' => $this->transactionParams['dateech1'],
                'dateech2' => $this->transactionParams['dateech2'],
                'dateech3' => $this->transactionParams['dateech3'],
                'dateech4' => $this->transactionParams['dateech4'],
                'montantech1' => $this->transactionParams['montantech1'],
                'montantech2' => $this->transactionParams['montantech2'],
                'montantech3' => $this->transactionParams['montantech3'],
                'montantech4' => $this->transactionParams['montantech4'],
                'nbrech' => $this->transactionParams['nbrech'],
            ));
        ksort($fields);

        /* Transforming array value to : "key=value" to match the target format
        Transformation des valeurs du tableau vers : "key=value" pour respecter le format de la chaine du calcul HMAC */
        array_walk($fields, function(&$item, $key) {$item = "$key=$item";});

        /* Data to certify */
        $phase1go_fields = implode('*', $fields);

        /* MAC computation */
        $sMAC = $oHmac->computeHmac($phase1go_fields);

        /* complete transaction list */
        $this->transactionParams['MAC'] = $sMAC;

        /* check vars */
        $this->transactionParams['texte-libre'] = htmlencode($this->transactionParams['texte-libre']);

        /* build form */
        $this->paymentForm = new HTMLForm('PaymentRequest', $oEpt->sUrlPaiement, 'POST');

        /* add vars to form */
        foreach ($this->transactionParams as $name => $value) {
            if ($name == 'nbrech' and $value == '') break;
            $this->paymentForm->add_hidden($name, $value, $name);
        }

        /* add scripts */
        $this->add_JSLoadScript('setTimeout("'.$this->paymentForm->get_JSSubmitLink().'", 4000);');
    }

    /* Mark: Data query methods */

    /**
     * Return response data from confirmation request
     * @return array
     */
    public function load_paymentConfirmation() {
        global $camyks;

        /* Build Monetico configuration */
        $this->build_config();

        /* Load Monetico library */
        require_once($this->get_filePath('lib/MoneticoPaiement_Ept.inc.php'));

        /* Initialise response */
        $responseData = array('uniqueId'=>'', 'response'=>'', 'resetUniqueId'=>0);

        /* Begin Main : Retrieve Variables posted by Monetico Paiement Server */
        $MoneticoPaiement_bruteVars = getMethode();

        /* Clean vars to keep only Monetico variables */
        $MoneticoVars = array("TPE", "date", "montant", "reference", "texte-libre", "code-retour", "cvx", "vld", "brand", "numauto", "usage", "typecompte", "ecard", "originecb", "bincb", "hpancb", "ipclient", "originetr", "cbmasquee", "modepaiement", "authentification", "MAC");
        foreach ($MoneticoPaiement_bruteVars as $name => $value)
            if (!in_array($name, $MoneticoVars))
                unset($MoneticoPaiement_bruteVars[$name]);

        /* Check mandatory values */
        if (!isset($MoneticoPaiement_bruteVars['code-retour']) or !isset($MoneticoPaiement_bruteVars['reference'])) {
            $this->confirmationData = $responseData;
            return;
        }

        /* TPE init variables */
        $oEpt = new MoneticoPaiement_Ept();
        $oHmac = new MoneticoPaiement_Hmac($oEpt);

        /* Message Authentication*/
        $MAC_source = computeHmacSource($MoneticoPaiement_bruteVars, $oEpt);
        $computed_MAC = $oHmac->computeHmac($MAC_source);
        $congruent_MAC = array_key_exists('MAC', $MoneticoPaiement_bruteVars) && $computed_MAC == strtolower($MoneticoPaiement_bruteVars['MAC']);
        if (!$congruent_MAC) {
            //$camyks->log_executionerror($this, 'HMAC doesn\'t match.', "Expected HMAC: ".$MoneticoPaiement_bruteVars['MAC']."\nComputed HMAC: ".$computed_MAC);
        }

        /* Build receipt */
        $receipt = MONETICOPAIEMENT_PHASE2BACK_MACOK;

        /* Update response */
        $responseData['response'] = $MoneticoPaiement_bruteVars['code-retour'];
        $responseData['uniqueId'] = $MoneticoPaiement_bruteVars['reference'];

        /* Back up response */
        $this->confirmationData = $responseData;

        /* Print response answer from monetico server */
        printf(MONETICOPAIEMENT_PHASE2BACK_RECEIPT, $receipt);
    }

    /**
     * Check if payment is confirmed.
     * @return boolean result
     */
    public function is_paymentConfirmed() {
        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();

        if (!isset($this->confirmationData['response']))
            return false;

        if ($this->confirmationData['response'] === 'paiement')
            return true;

        if ($this->confirmationData['response'] === 'payetest')
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

        if (!isset($this->confirmationData['response']))
            return false;

        if ($this->confirmationData['response'] === 'Error')
            return true;

        if ($this->confirmationData['response'] === 'Annulation')
            return true;

        return false;
    }

    /**
     * Return response data from confirmation request.
     * @return array
     */
    public function get_paymentConfirmationData() {
        if ($this->confirmationData === null)
            $this->load_paymentConfirmation();
        return $this->confirmationData;
    }

    /**
     * Execute check out.
     * @return array
     */
    public function execute_checkout() {
        $data = $this->get_paymentConfirmation();
        return ($data['response'] === 'paiement' or $data['response'] === 'payetest');
    }

    /**
     * Return transaction id.
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

    /* Mark: Error handling methods */

    /**
     * Define last error.
     * @param string $errorCode
     * @param string $errorMsg
     */
    private function set_lastError($errorCode, $errorMsg) {
        $this->_lastErrorCode = $errorCode;
        $this->_lastErrorMsg = $errorMsg;
    }

    /**
     * Return last error as code.
     * @return string
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

    /* Mark: Internal tool methods */

    /**
     * Build Monetico configuration
     * @return void
     */
    private function build_config() {
        /* Set up params from configuration */
        $this->params['MONETICOPAIEMENT_COMPANYCODE'] = $this->config->get_value('company_code');
        if ($this->config->get_value('operation_mode') === 'live') {
            $this->params['MONETICOPAIEMENT_URLSERVER'] = "https://p.monetico-services.com/";
            $this->params['MONETICOPAIEMENT_EPTNUMBER'] =  $this->config->get_value('tpeId_live');
            $this->params['MONETICOPAIEMENT_KEY'] =  $this->config->get_value('bankKey_live');
        } else {
            $this->params['MONETICOPAIEMENT_URLSERVER'] = "https://p.monetico-services.com/test/";
            $this->params['MONETICOPAIEMENT_EPTNUMBER'] =  $this->config->get_value('tpeId_test');
            $this->params['MONETICOPAIEMENT_KEY'] =  $this->config->get_value('bankKey_test');
        }

        /* shop params */
        define("MONETICOPAIEMENT_KEY", $this->params['MONETICOPAIEMENT_KEY']);
        define("MONETICOPAIEMENT_EPTNUMBER", $this->params['MONETICOPAIEMENT_EPTNUMBER']);
        define("MONETICOPAIEMENT_COMPANYCODE", $this->params['MONETICOPAIEMENT_COMPANYCODE']);

        /* shop urls */
        define("MONETICOPAIEMENT_URLOK", $this->params['MONETICOPAIEMENT_URLOK']);
        define("MONETICOPAIEMENT_URLKO", $this->params['MONETICOPAIEMENT_URLKO']);

        /* Monetico url */
        define("MONETICOPAIEMENT_URLSERVER", $this->params['MONETICOPAIEMENT_URLSERVER']);

        /* Monetico params */
        define("MONETICOPAIEMENT_VERSION", $this->params['MONETICOPAIEMENT_VERSION']);
        define("MONETICOPAIEMENT_CTLHMAC", $this->params['MONETICOPAIEMENT_CTLHMAC']);
        define("MONETICOPAIEMENT_CTLHMACSTR", $this->params['MONETICOPAIEMENT_CTLHMACSTR']);
        define("MONETICOPAIEMENT_PHASE2BACK_RECEIPT", $this->params['MONETICOPAIEMENT_PHASE2BACK_RECEIPT']);
        define("MONETICOPAIEMENT_PHASE2BACK_MACOK", $this->params['MONETICOPAIEMENT_PHASE2BACK_MACOK']);
        define("MONETICOPAIEMENT_PHASE2BACK_MACNOTOK", $this->params['MONETICOPAIEMENT_PHASE2BACK_MACNOTOK']);
        define("MONETICOPAIEMENT_PHASE2BACK_FIELDS", $this->params['MONETICOPAIEMENT_PHASE2BACK_FIELDS']);
        define("MONETICOPAIEMENT_PHASE1GO_FIELDS", $this->params['MONETICOPAIEMENT_PHASE1GO_FIELDS']);
        define("MONETICOPAIEMENT_URLPAYMENT", $this->params['MONETICOPAIEMENT_URLPAYMENT']);
    }

    /**
     * Load plugin configuration
     * @return void
     */
    public function load_configuration() {
        /* load configuration library */
        $this->load_library('MoneticoPaiementConfig');

        /* load config */
        $this->config = new MoneticoPaiementConfig('config', $this);
        $this->config->get();
    }

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
            return '+'.$index.'-'.substr($phoneNumber, 2);

        /* Format with initial 0 */
        elseif (strpos($phoneNumber, '0') === 0)
            return '+'.$index.'-'.substr($phoneNumber, 1);

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
