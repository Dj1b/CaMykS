<?php
/**
 * @brief PayPalExpressCheckout Input
 * <br /> Interface to Paypal Express payment system.
 * @details Plugin / Input Engine
 * @file plugin/input/PayPalExpressCheckout/PayPalExpressCheckout.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2016
 * @date Modification: Jul 2018
 * @copyright 2016 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PayPalExpressCheckout Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class PayPalExpressCheckout extends Input {
    /**
     * var string $_lastErrorCode
     * @brief Last error code.
     */
    private $_lastErrorCode = '';
    
    /**
     * var string $_lastErrorMsg
     * @brief Last error message.
     */
    private $_lastErrorMsg = '';
    
    /**
     * var string $_transactionId
     * @brief Transaction id from Paypal.
     */
    private $_transactionId = '';

    /**
     * Class constructor
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('PayPalExpressCheckout', $path_type);
        /* set plugin version */
        $this->version = '1.0';
        
        /* set plugin package */
        $this->plugin_package = 'eCommerce';
        
        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';        
    }
    
    /* overwrite input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* build default params */
        $dParams = array(
            /* live user config */
            'Live_User' => '',
            'Live_Password' => '',
            'Live_Signature' => '',
            
            /* sandbox user config */
            'Sandbox_User' => '',
            'Sandbox_Password' => '',
            'Sandbox_Signature' => '',
            
            /* url config */
            'ReturnURL' => '',
            'CancelURL' => '',
            'MarkReturnURL' => '',
            
            /* mode config */
            'Mode' => 'sandbox',
            'InContext' => false,
            
            /* proxy config */
            'ProxyHost' => "127.0.0.1",
            'ProxyPort' => "808",
                
            /* other settings config */
            'ExpressMark' => true,
            'AddressOverride' => true,
            'APIVersion' => '109.0',
            'SBNCode' => '',
                
            /* Paypal urls */
            'Live_CheckoutURL' => 'https://www.paypal.com/cgi-bin/webscr?cmd=_express-checkout&token=',
            'Live_EndPointURL' => 'https://api-3t.paypal.com/nvp',
            
            'Live_InContext_CheckoutURL' => 'https://www.paypal.com/checkoutnow?token=',
            'Live_InContext_EndPointURL' => 'https://api-3t.paypal.com/nvp',
            
            'Sandbox_CheckoutURL' => 'https://www.sandbox.paypal.com/cgi-bin/webscr?cmd=_express-checkout&token=',
            'Sandbox_EndPointURL' => 'https://api-3t.sandbox.paypal.com/nvp',
            
            'Sandbox_InContext_CheckoutURL' => 'https://www.sandbox.paypal.com/checkoutnow?token=',
            'Sandbox_InContext_EndPointURL' => 'https://api-3t.sandbox.paypal.com/nvp',
        );
                
        /* define params */
        $this->params = array_merge($dParams, $params);
        
        /* build paypal config (to be loaded before functions) */
        $this->build_paypalConfig();
        
        /* load paypal library */
        require_once($this->get_filePath('lib/paypal_functions.php'));
        
        /* Input generic initialization */
        parent::initialise();
    }
    
    
    /* execution methods */
    
    /**
     * Execute set express checkout.
     * @param array $orderData
     * @return boolean success
     */
    public function execute_setCheckout($orderData=array()) {
    
        /* format some vars */
        if (isset($orderData['PAYMENTREQUEST_0_AMT']))          $orderData['PAYMENTREQUEST_0_AMT']          = string_numberFormat($orderData['PAYMENTREQUEST_0_AMT'], 2, 'en');
        if (isset($orderData['PAYMENTREQUEST_0_ITEMAMT']))      $orderData['PAYMENTREQUEST_0_ITEMAMT']      = string_numberFormat($orderData['PAYMENTREQUEST_0_ITEMAMT'], 2, 'en');
        if (isset($orderData['PAYMENTREQUEST_0_TAXAMT']))       $orderData['PAYMENTREQUEST_0_TAXAMT']       = string_numberFormat($orderData['PAYMENTREQUEST_0_TAXAMT'], 2, 'en');
        if (isset($orderData['PAYMENTREQUEST_0_SHIPPINGAMT']))  $orderData['PAYMENTREQUEST_0_SHIPPINGAMT']  = string_numberFormat($orderData['PAYMENTREQUEST_0_SHIPPINGAMT'], 2, 'en');
        if (isset($orderData['PAYMENTREQUEST_0_SHIPDISCAMT']))  $orderData['PAYMENTREQUEST_0_SHIPDISCAMT']  = string_numberFormat($orderData['PAYMENTREQUEST_0_SHIPDISCAMT'], 2, 'en');
        
        $cnt = 0;
        while (isset($orderData['L_PAYMENTREQUEST_0_AMT'.$cnt])) {
            $orderData['L_PAYMENTREQUEST_0_AMT'.$cnt] = string_numberFormat($orderData['L_PAYMENTREQUEST_0_AMT'.$cnt], 2, 'en');
            if (isset($orderData['L_PAYMENTREQUEST_0_TAXAMT'.$cnt])) $orderData['L_PAYMENTREQUEST_0_TAXAMT'.$cnt] = string_numberFormat($orderData['L_PAYMENTREQUEST_0_TAXAMT'.$cnt], 2, 'en');
            $cnt++;
        }
    
        /* execute call to PayPal */
        $resArray = CallShortcutExpressCheckout ($orderData, $this->params['ReturnURL'], $this->params['CancelURL']);
     
        $ack = strtoupper($resArray["ACK"]);
        if ($ack=="SUCCESS" || $ack=="SUCCESSWITHWARNING") {    //if SetExpressCheckout API call is successful
            RedirectToPayPal($resArray["TOKEN"]);
        } else {
            $this->set_lastError(urldecode($resArray["L_ERRORCODE0"]), '['.urldecode($resArray["L_SEVERITYCODE0"]).']'.urldecode($resArray["L_LONGMESSAGE0"]));
            return false;
        }
        return true;
    }
    
    /**
     * Execute get express checkout.
     * @param string $token 
     * @return boolean success
     */
    public function execute_getCheckout($token='') {

        $shippingResult = GetShippingDetails($token);
        $shippingAck = strtoupper($shippingResult["ACK"]);
            
        if ($shippingAck == "SUCCESS" || $shippingAck == "SUCCESSWITHWARNING") {                
            return true;
        } else {
            $this->set_lastError(urldecode($shippingResult["L_ERRORCODE0"]), '['.urldecode($shippingResult["L_SEVERITYCODE0"]).'] '.urldecode($shippingResult["L_LONGMESSAGE0"]));
            return false;
        }
    }
    
    /**
     * Execute do express checkout.
     * @param float $total
     * @param string $token
     * @return boolean success
     */
    public function execute_doCheckout($total, $token) {

        $paymentResult = ConfirmPayment ($total);
        $paymentAck = strtoupper($paymentResult["ACK"]);
                
        if ($paymentAck == "SUCCESS" || $paymentAck == "SUCCESSWITHWARNING") {
            $this->_transactionId = $paymentResult['PAYMENTINFO_0_TRANSACTIONID'];
            return true;
        } else {
            $ErrorCode = urldecode($paymentResult["L_ERRORCODE0"]);
            if ($ErrorCode == 10486) RedirectToPayPal($token);
            $this->set_lastError(urldecode($paymentResult["L_ERRORCODE0"]), '['.urldecode($paymentResult["L_SEVERITYCODE0"]).']'.urldecode($paymentResult["L_LONGMESSAGE0"]));
            return false;
        }
    }
    
    /* data query methods */
    
    /**
     * Return transaction id.
     * @return string
     */
    public function get_transactionId() {
        return $this->_transactionId;
    }
    
    
    /* error handling methods */

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
        
    /**
     * Build Paypal config.
     * @return void
     */
    private function build_paypalConfig() {
    
        //Seller Sandbox Credentials- Sample credentials already provided
        define("PP_USER_SANDBOX", $this->params['Sandbox_User']);
        define("PP_PASSWORD_SANDBOX", $this->params['Sandbox_Password']);
        define("PP_SIGNATURE_SANDBOX", $this->params['Sandbox_Signature']);

        //Seller Live credentials.
        define("PP_USER", $this->params['Live_User']);
        define("PP_PASSWORD",    $this->params['Live_Password']);
        define("PP_SIGNATURE",    $this->params['Live_Signature']);

        //Set this constant EXPRESS_MARK = true to skip review page
        define("EXPRESS_MARK",    $this->params['ExpressMark']);

        //Set this constant ADDRESS_OVERRIDE = true to prevent from changing the shipping address
        define("ADDRESS_OVERRIDE", $this->params['AddressOverride']);

        /* Set this constant USERACTION_FLAG = true to skip review page
        define("USERACTION_FLAG", false);

        //Based on the USERACTION_FLAG assign the page
        if (USERACTION_FLAG){
            $page = 'return.php';
        } else {    
            $page = 'review.php';
        }

        */
        //The URL in your application where Paypal returns control to -after success (RETURN_URL) and after cancellation of the order (CANCEL_URL) 
        define("RETURN_URL", $this->params['ReturnURL']);
        define("CANCEL_URL", $this->params['CancelURL']);

        //The URL in your application where Paypal returns control to -after success (RETURN_URL) using Express Checkout Mark Flow
        define("RETURN_URL_MARK",$this->params['MarkReturnURL']);

        //define("RETURN_URL",'http://'.$_SERVER['HTTP_HOST'].preg_replace('/paypal_ec_redirect.php/','lightboxreturn.php',$_SERVER['SCRIPT_NAME']));
        //define("CANCEL_URL",'http://'.$_SERVER['HTTP_HOST'].preg_replace('/paypal_ec_redirect.php/','cancel.php',$_SERVER['SCRIPT_NAME']));

        //Whether Sandbox environment is being used, Keep it true for testing
        define("SANDBOX_FLAG", $this->params['Mode'] != 'live');

        /*
        if (SANDBOX_FLAG){
            $merchantID=PP_USER_SANDBOX;    * Use Sandbox merchant id when testing in Sandbox *
            $env= 'sandbox';
        }
        else {
            $merchantID=PP_USER;    * Use Live merchant ID for production environment *
            $env='production';
        }
        */

        //Proxy Config
        define("PROXY_HOST", $this->params['ProxyHost']);
        define("PROXY_PORT", $this->params['ProxyPort']);
        
        if ($this->params['InContext']) {
            //In-Context in Express Checkout URLs for Sandbox
            define("PP_CHECKOUT_URL_SANDBOX", $this->params['Sandbox_InContext_CheckoutURL']);
            define("PP_NVP_ENDPOINT_SANDBOX", $this->params['Sandbox_InContext_EndPointURL']);
            //In-Context in Express Checkout URLs for Live
            define("PP_CHECKOUT_URL_LIVE", $this->params['Live_InContext_CheckoutURL']);
            define("PP_NVP_ENDPOINT_LIVE", $this->params['Live_InContext_EndPointURL']);
        } else {
            //Express Checkout URLs for Sandbox
            define("PP_CHECKOUT_URL_SANDBOX", $this->params['Sandbox_CheckoutURL']);
            define("PP_NVP_ENDPOINT_SANDBOX", $this->params['Sandbox_EndPointURL']);
            //Express Checkout URLs for Live
            define("PP_CHECKOUT_URL_LIVE", $this->params['Live_CheckoutURL']);
            define("PP_NVP_ENDPOINT_LIVE", $this->params['Live_InContext_EndPointURL']);
        }
        
        //Version of the APIs
        define("API_VERSION", "109.0");

        //ButtonSource Tracker Code
        define("SBN_CODE","PP-DemoPortal-EC-IC-php");
    }
}
?>