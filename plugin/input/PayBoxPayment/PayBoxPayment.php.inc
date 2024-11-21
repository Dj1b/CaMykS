<?php
/**
 * @brief PayBoxPayment Input.
 * <br /> Interface to PayBox payment system.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: Apr 2017
 * @date Modification: Nov 2024
 * @copyright 2017 - 2024 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PayBoxPayment Input class.
 */
final class PayBoxPayment extends Input {
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
     * var array $params
     * @brief Input parameters.
     */
    public $params = array();

    /**
     * var array $confirmationData
     * @brief Confirmation data received from Paybox instant notifications.
     */
    private $confirmationData = null;

    /**
     * var array $currencies
     * @brief Currency list.
     */
    private $currencies = array(
        'EUR'   => 978,
    );

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('PayBoxPayment', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'eCommerce';

        /* Define plugin author */
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

        /* load plugin configuration */
        $this->load_configuration();

        /* define params */
        $this->params = array_merge($this->config->vars, $params);

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
        /* merge params */
        $this->transactionParams = array_recursiveMerge(array(
            'amount'            => '',
            'orderId'           => '',
            'reference'         => '',
            'email'             => '',
            'amount'            => 0,
            'devise'            => 'EUR',
            'backURL_OK'        => '',
            'backURL_Cancel'    => '',
            'backURL_Refused'   => '',
            'backURL_Response'  => '',
            'backURL_Confirm'   => '',
            'backData'          => 'Reference:R;Transaction:S;Erreur:E',
            'date'              => date('c'),
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

        /* fix params */
        $this->transactionParams['amount'] = (int)($this->transactionParams['amount']*100);
        $this->transactionParams['devise'] = $this->currencies[$this->transactionParams['devise']];

        if ($this->params['bankMode'] == 'live') {
            /* production servers */
            $serveurs = array(
                'tpeweb.paybox.com', //serveur primaire
                'tpeweb1.paybox.com', //serveur secondaire
            );

            /* production key */
            $bankKey = $this->params['bankKey_Live'];

        } else {
            /* test servers */
            $serveurs = array(
                'preprod-tpeweb.paybox.com', // test server
            );

            /* test key */
            $bankKey = $this->params['bankKey_Test'];
        }

        /* initialise server to use */
        $serveurOK = "";
        foreach($serveurs as $serveur) {
            $doc = new DOMDocument();
            $doc->loadHTMLFile('https://'.$serveur.'/load.html');
            $server_status = "";
            $element = $doc->getElementById('server_status');
            if ($element) {$server_status = $element->textContent;}
            if ($server_status == "OK") {
                // Le serveur est pret et les services operationnels
                $serveurOK = $serveur;
                break;
            }
            // else : La machine est disponible mais les services ne le sont pas.
        }

        if (!$serveurOK) {
            /* to replace */
            die("Erreur : Aucun serveur n'a été trouvé");
        }

        //Création de l'url cgi paybox
        $serveurOK = 'https://'.$serveurOK.'/cgi/MYchoix_pagepaiement.cgi';

        /* prepare data */
        $baseURL = (client_isHTTPS()?'https://':'http://').$_SERVER['HTTP_HOST'];

        /* build data */
        $params = array(
            'PBX_SITE'          => $this->params['site'],
            'PBX_RANG'          => $this->params['rang'],
            'PBX_IDENTIFIANT'   => $this->params['identifiant'],
            'PBX_CMD'           => $this->transactionParams['reference'],
            'PBX_PORTEUR'       => $this->transactionParams['email'],
            'PBX_TOTAL'         => $this->transactionParams['amount'],
            'PBX_DEVISE'        => $this->transactionParams['devise'],
            'PBX_EFFECTUE'      => $this->transactionParams['backURL_OK'],
            'PBX_ANNULE'        => $this->transactionParams['backURL_Cancel'],
            'PBX_REFUSE'        => $this->transactionParams['backURL_Refused'],
            'PBX_REPONDRE_A'    => $this->transactionParams['backURL_Response'],
            'PBX_RETOUR'        => $this->transactionParams['backData'],
            'PBX_HASH'          => $this->params['hash'],
            'PBX_TIME'          => $this->transactionParams['date'],
        );

        /* build shopping cart data */
        $shoppingCart = '<?xml version="1.0" encoding="utf-8"?>';
        if (count($this->transactionParams['shoppingCart']) >= 1) {
            $shoppingCart .= "<shoppingcart><total><totalQuantity>".count($this->transactionParams['shoppingCart'])."</totalQuantity></total></shoppingcart>";
        } else {
            $shoppingCart .= "<shoppingcart><total><totalQuantity></totalQuantity></total></shoppingcart>";
        }
        $params['PBX_SHOPPINGCART'] = preg_replace('/"/', '\'', $shoppingCart);

        /* Define phone */
        if (!is_null($this->transactionParams['billing']['mobile']))
            $phone = $this->transactionParams['billing']['mobile'];
        elseif (!is_null($this->transactionParams['billing']['phone']))
            $phone = $this->transactionParams['billing']['phone'];
        elseif (!is_null($this->transactionParams['client']['mobile']))
            $phone = $this->transactionParams['client']['mobile'];
        elseif (!is_null($this->transactionParams['client']['phone']))
            $phone = $this->transactionParams['client']['phone'];
        else
            $phone = '';

        /* build billing data */
        $billingData = '<?xml version="1.0" encoding="utf-8"?>'
            ."<Billing>"
            ."<Address>"
            ."<FirstName>".(!is_null($this->transactionParams['billing']['firstName']) ? $this->transactionParams['billing']['firstName'] : $this->transactionParams['client']['firstName'])."</FirstName>"
            ."<LastName>".(!is_null($this->transactionParams['billing']['lastName']) ? $this->transactionParams['billing']['lastName'] : $this->transactionParams['client']['lastName'])."</LastName>"
            ."<Address1>".(!is_null($this->transactionParams['billing']['address1']) ? $this->transactionParams['billing']['address1'] : $this->transactionParams['client']['address1'])."</Address1>"
            ."<ZipCode>".(!is_null($this->transactionParams['billing']['zipcode']) ? $this->transactionParams['billing']['zipcode'] : $this->transactionParams['client']['zipcode'])."</ZipCode>"
            ."<City>".(!is_null($this->transactionParams['billing']['city']) ? $this->transactionParams['billing']['city'] : $this->transactionParams['client']['city'])."</City>"
            ."<CountryCode>".countries_getSingleDataValue(!is_null($this->transactionParams['billing']['country']) ? $this->transactionParams['billing']['country'] : $this->transactionParams['client']['country'], 'NumericCode')."</CountryCode>"
            ."<CountryCodeMobilePhone>+".countries_getSingleDataValue(!is_null($this->transactionParams['billing']['country']) ? $this->transactionParams['billing']['country'] : $this->transactionParams['client']['country'], 'PhoneIndex')."</CountryCodeMobilePhone>"
            ."<MobilePhone>".$phone."</MobilePhone>"
            ."</Address>"
            ."</Billing>";
        $params['PBX_BILLING'] = preg_replace('/"/', '\'', $billingData);

        /* build shipping data */
        if (!is_null($this->transactionParams['shipping']['firstName'])) {

            if (!is_null($this->transactionParams['shipping']['mobile']))
                $phone = $this->transactionParams['shipping']['mobile'];
            elseif (!is_null($this->transactionParams['shipping']['phone']))
                $phone = $this->transactionParams['shipping']['phone'];
            else
                $phone = '';

            $shippingData = '<?xml version="1.0" encoding="utf-8"?>'
                ."<Shipping>"
                ."<Address>"
                ."<FirstName>".$this->transactionParams['shipping']['firstName']."</FirstName>"
                ."<LastName>".$this->transactionParams['shipping']['lastName']."</LastName>"
                ."<Address1>".$this->transactionParams['shipping']['address1']."</Address1>"
                ."<ZipCode>".$this->transactionParams['shipping']['zipcode']."</ZipCode>"
                ."<City>".$this->transactionParams['shipping']['city']."</City>"
                ."<CountryCode>".countries_getSingleDataValue($this->transactionParams['shipping']['country'], 'NumericCode')."</CountryCode>"
                ."<CountryCodeMobilePhone>+".countries_getSingleDataValue($this->transactionParams['shipping']['country'], 'PhoneIndex')."</CountryCodeMobilePhone>"
                ."<Phone>".$phone."</Phone>"
                ."</Address>"
                ."</Shipping>";
            $params['PBX_SHIPPING'] = preg_replace('/"/', '\'', $shippingData);
        }

        /* build params string */
        $msg = array();
        foreach ($params as $key => $value)
            $msg[] = $key.'='.$value;
        $msg = implode('&', $msg);

        // Si la clé est en ASCII, On la transforme en binaire
        $binKey = pack("H*", $bankKey);

        // On calcule l’empreinte (à renseigner dans le paramètre PBX_HMAC) grâce à la fonction hash_hmac et //
        // la clé binaire
        // On envoi via la variable PBX_HASH l'algorithme de hachage qui a été utilisé (SHA512 dans ce cas)
        // Pour afficher la liste des algorithmes disponibles sur votre environnement, décommentez la ligne //
        // suivante
        //print_r(hash_algos());
        $hmac = strtoupper(hash_hmac('sha512', $msg, $binKey));
        $params['PBX_HMAC'] = $hmac;

        /* build CB specific form */
        $this->paymentForm = new HTMLForm('paymentRequest', $serveurOK, 'POST');
        foreach ($params as $key => $value)
            $this->paymentForm->add_hidden($key, $value);

        /* add scripts */
        $this->add_JSLoadScript('setTimeout("'.$this->paymentForm->get_JSSubmitLink().'", 4000);');
    }

    /* Mark: Data query methods */

    /**
     * Load confirmation data PayBox instant notification.
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

        if (!isset($this->confirmationData['Erreur']))
            return false;

        if ($this->confirmationData['Erreur'] === '00000')
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

        if (!isset($this->confirmationData['Erreur']))
            return false;

        if ($this->confirmationData['Erreur'] === '00017')
            return true;

        return false;
    }

    /**
     * Return response data from confirmation request.
     * @return array
     */
    public function get_paymentConfirmationData() {
        $data = array();
        $data['uniqueId'] = isset($this->confirmationData['Reference']) ? $this->confirmationData['Reference'] : '';
        $data['transaction'] = isset($this->confirmationData['Transaction']) ? $this->confirmationData['Transaction'] : '';
        $data['response'] = isset($this->confirmationData['Erreur']) ? $this->confirmationData['Erreur'] : '';
        return $data;
    }

    /**
     * Return response data from confirmation request.
     * @return array
     */
    public function get_paymentConfirmation() {
        $this->load_paymentConfirmation();
        return $this->get_paymentConfirmationData();
    }

    /**
     * Execute check out.
     * @return array
     */
    public function execute_checkout() {
        $data = $this->get_paymentConfirmation();
        return ((int)$data['response'] === 0);
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

    /* Mark: Tool methods */

    /**
     * Load plugin configuration
     * @return void
     */
    public function load_configuration() {
        /* load configuration library */
        $this->load_library('PayBoxPaymentConfig');

        /* load config */
        $this->config = new PayBoxPaymentConfig('config', $this);
        $this->config->get();
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
