<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Create Date		: Apr 2017
 * Last Modif Date	: Apr 2017
 * History : 
 * * 16-11-25 : Initial files
 * 
 * MoneticoPaiement (version 4.0) payment connexion
 */

class MoneticoPaiement extends Input {
  /* variables */
  private $_lastErrorCode;
  private $_lastErrorMsg;
  private $_transactionId;

  /* 
   * constructor
   * @param string $path_type
   */
  function MoneticoPaiement ( $path_type ) {
    parent::Input('MoneticoPaiement', $path_type);
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

  /*
   * initialise input
   * @param array $params
   * @return void
   * @access public
   */
  function initialise($params=array()) {
    global $camyks;

    /* build default system params */
    $dParams = array(
    
        /* running mode */
        'mode'                                  => 'test',  // live / test
    
        /* shop params */
        'MONETICOPAIEMENT_KEY'                  => '',
        'MONETICOPAIEMENT_EPTNUMBER'            => '',
        'MONETICOPAIEMENT_COMPANYCODE'          => '',
        
        /* shop URLs */
        'MONETICOPAIEMENT_URLOK'                => '',
        'MONETICOPAIEMENT_URLKO'                => '',
        
        /* Monetico URLs */
        'MONETICOPAIEMENT_URLSERVER_Live'       => "https://p.monetico-services.com/",
        'MONETICOPAIEMENT_URLSERVER_Test'       => "https://p.monetico-services.com/test/",
        
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
        
    /* define params */
    $this->params = array_merge($dParams, $params);
    
    /* initialise transaction params */
    $this->transactionParams = array();
    
    /* build Monetico config */
    $this->build_config();
    
    /* load Monetico library */
    require_once($this->get_filePath('lib/MoneticoPaiement_Ept.inc.php'));
    
    /* define variables */
    $this->_lastErrorCode = '';
    $this->_lastErrorMsg = '';
    $this->_transactionId = '';
    
    /* Input generic initialization */
    parent::initialise();
  }
  
  
  /* execution methods */
  
  /*
   * prepare for payment
   * @param array $params
   * @return boolean result
   * @access public
   */
  function prepare_forPayment($params=array()) {
    
    /* build default transaction params */
    $dParams = array(
        'date' => date("d/m/Y:H:i:s"),
        'montant' => '',
        'devise' => '',
        'reference' => '',
        'lgue' => '',
        'texte-libre' => '',
        'mail' => '',
        'options' => '',
        'version' => '',
        'TPE' => '',
        'MAC' => '',
        'url_retour' => '',
        'url_retour_ok' => '',
        'url_retour_err' => '',
        'societe' => '',
        
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

    /* merge params */
    $this->transactionParams = array_merge($dParams, $params);
    
    /* execute Monetico methods */
    $oEpt = new MoneticoPaiement_Ept($this->transactionParams['lgue']);     		
    $oHmac = new MoneticoPaiement_Hmac($oEpt);      	        

        // Control String for support
    $CtlHmac = sprintf(MONETICOPAIEMENT_CTLHMAC, $oEpt->sVersion, $oEpt->sNumero, $oHmac->computeHmac(sprintf(MONETICOPAIEMENT_CTLHMACSTR, $oEpt->sVersion, $oEpt->sNumero)));
    
        // Data to certify
    $phase1go_fields = sprintf(MONETICOPAIEMENT_PHASE1GO_FIELDS, $oEpt->sNumero,
                                              $this->transactionParams['date'],
                                              $this->transactionParams['montant'],
                                              $this->transactionParams['devise'],
                                              $this->transactionParams['reference'],
                                              $this->transactionParams['texte-libre'],
                                              $oEpt->sVersion,
                                              $oEpt->sLangue,
                                              $oEpt->sCodeSociete, 
                                              $this->transactionParams['mail'],
                                              $this->transactionParams['nbrech'],
                                              $this->transactionParams['dateech1'],
                                              $this->transactionParams['montantech1'],
                                              $this->transactionParams['dateech2'],
                                              $this->transactionParams['montantech2'],
                                              $this->transactionParams['dateech3'],
                                              $this->transactionParams['montantech3'],
                                              $this->transactionParams['dateech4'],
                                              $this->transactionParams['montantech4'],
                                              $this->transactionParams['options']);    

        // MAC computation
    $sMAC = $oHmac->computeHmac($phase1go_fields);
        
    /* complete transaction list */
    $this->transactionParams['version'] = $oEpt->sVersion;
    $this->transactionParams['TPE'] = $oEpt->sNumero;
    $this->transactionParams['MAC'] = $sMAC;
    $this->transactionParams['url_retour'] = $oEpt->sUrlKO;
    $this->transactionParams['url_retour_ok'] = $oEpt->sUrlOK;
    $this->transactionParams['url_retour_err'] = $oEpt->sUrlKO;
    $this->transactionParams['lgue'] = $oEpt->sLangue;
    $this->transactionParams['societe'] = $oEpt->sCodeSociete;    
    
    /* check vars */
    $this->transactionParams['texte-libre'] = HtmlEncode($this->transactionParams['texte-libre']);
    $this->transactionParams['montant'] .= $this->transactionParams['devise'];
    unset($this->transactionParams['devise']);
    
    /* build form */
    $this->paymentForm = new HTMLForm(
      'PaymentRequest',
      $oEpt->sUrlPaiement,
      'POST'
    );
    
    /* add vars to form */
    foreach ($this->transactionParams as $name => $value) {
      if ($name == 'nbrech' and $value == '') break;
      $this->paymentForm->add_hidden($name, $value, $name);
    }
    
    /* add scripts */
    $this->add_JSLoadScript('setTimeout("'.$this->paymentForm->get_JSSubmitLink().'", 4000);');
  
  }
  
  /*
   * display input
   * @return void
   * @access public
   */
  function display() {
    
    if (count($this->transactionParams) == 0) {
      
      echo ($this->get_translation('error_transactionparamsnotdefined'));
      
    } else {
      
      echo $this->paymentForm->display_header();
      echo $this->paymentForm->display_hiddens();
      echo $this->paymentForm->display_footer();
      
    }
  }
  
  /* data query methods */
  
  /*
   * return response data from confirmation request
   * @return array
   * @access public
   */
  function get_paymentConfirmation() {
    
    $responseData = array();
  
    // Begin Main : Retrieve Variables posted by Monetico Paiement Server
    $MoneticoPaiement_bruteVars = getMethode();

    // TPE init variables
    $oEpt = new MoneticoPaiement_Ept();
    $oHmac = new MoneticoPaiement_Hmac($oEpt);

    // Message Authentication
    $phase2back_fields = sprintf(MONETICOPAIEMENT_PHASE2BACK_FIELDS, $oEpt->sNumero,
                        isset($MoneticoPaiement_bruteVars["date"])?$MoneticoPaiement_bruteVars["date"]:'',
                        isset($MoneticoPaiement_bruteVars["montant"])?$MoneticoPaiement_bruteVars["montant"]:'',
                        isset($MoneticoPaiement_bruteVars["reference"])?$MoneticoPaiement_bruteVars["reference"]:'',
                        isset($MoneticoPaiement_bruteVars["texte-libre"])?$MoneticoPaiement_bruteVars["texte-libre"]:'',
                        $oEpt->sVersion,
                        isset($MoneticoPaiement_bruteVars["code-retour"])?$MoneticoPaiement_bruteVars["code-retour"]:'',
                        isset($MoneticoPaiement_bruteVars["cvx"])?$MoneticoPaiement_bruteVars["cvx"]:'',
                        isset($MoneticoPaiement_bruteVars["vld"])?$MoneticoPaiement_bruteVars["vld"]:'',
                        isset($MoneticoPaiement_bruteVars["brand"])?$MoneticoPaiement_bruteVars["brand"]:'',
                        isset($MoneticoPaiement_bruteVars["status3ds"])?$MoneticoPaiement_bruteVars["status3ds"]:'',
                        isset($MoneticoPaiement_bruteVars["numauto"])?$MoneticoPaiement_bruteVars["numauto"]:'',
                        isset($MoneticoPaiement_bruteVars["motifrefus"])?$MoneticoPaiement_bruteVars["motifrefus"]:'',
                        isset($MoneticoPaiement_bruteVars["originecb"])?$MoneticoPaiement_bruteVars["originecb"]:'',
                        isset($MoneticoPaiement_bruteVars["bincb"])?$MoneticoPaiement_bruteVars["bincb"]:'',
                        isset($MoneticoPaiement_bruteVars["hpancb"])?$MoneticoPaiement_bruteVars["hpancb"]:'',
                        isset($MoneticoPaiement_bruteVars["ipclient"])?$MoneticoPaiement_bruteVars["ipclient"]:'',
                        isset($MoneticoPaiement_bruteVars["originetr"])?$MoneticoPaiement_bruteVars["originetr"]:'',
                        isset($MoneticoPaiement_bruteVars["veres"])?$MoneticoPaiement_bruteVars["veres"]:'',
                        isset($MoneticoPaiement_bruteVars["pares"])?$MoneticoPaiement_bruteVars["pares"]:''
					);

    if ($oHmac->computeHmac($phase2back_fields) == strtolower($MoneticoPaiement_bruteVars['MAC'])) {
        $receipt = MONETICOPAIEMENT_PHASE2BACK_MACOK;
        
        /* update response */
        $responseData['response'] = $MoneticoPaiement_bruteVars['code-retour'];
        $responseData['uniqueId'] = $MoneticoPaiement_bruteVars['reference'];

    } else {
	    // traitement en cas de HMAC incorrect
	    // your code if the HMAC doesn't match
	    $receipt = MONETICOPAIEMENT_PHASE2BACK_MACNOTOK.$phase2back_fields;
	    
	    /* update response */
	    $responseData['response'] = 'Error';
    }

    /* print response answer for monetico server */
    printf (MONETICOPAIEMENT_PHASE2BACK_RECEIPT, $receipt);
    
    /* return response */
    return $responseData;
  }
  
  /*
   * return transaction id
   * @return string
   * @access public
   */
  function get_transactionId() {
    return $this->_transactionId;
  }
  
  /* display methods */
  
  /*
   * return manual transfer link
   * @return string
   * @access public
   */
  function get_manualTransferLink() {
    if (isset($this->paymentForm))
      return $this->paymentForm->get_HTMLSubmitLink();
    return '';
  }
  
  /* error handling methods */

  /*
   * define last error
   * @param string $errorCode
   * @param string $errorMsg
   * @access private
   */
  function set_lastError($errorCode, $errorMsg) {
    $this->_lastErrorCode = $errorCode;
    $this->_lastErrorMsg = $errorMsg;
  }
  
  /*
   * return last error as code
   * @return string
   * @access public
   */
  function get_lastError() {
    return $this->_lastErrorCode;
  }
  
  /*
   * return last error as text
   * @return string
   * @access public
   */
  function get_lastErrorMessage() {
    if ($this->_lastErrorMsg == '')
      return '';
    return $this->_lastErrorMsg;
  }
  
  /* internal tool methods  */
  
  /*
   * build config
   * @return void
   * @access private
   */
  function build_config() {
    /* shop params */
    define ("MONETICOPAIEMENT_KEY", $this->params['MONETICOPAIEMENT_KEY']);
    define ("MONETICOPAIEMENT_EPTNUMBER", $this->params['MONETICOPAIEMENT_EPTNUMBER']);
    define ("MONETICOPAIEMENT_COMPANYCODE", $this->params['MONETICOPAIEMENT_COMPANYCODE']);
    
    /* shop urls */
    define ("MONETICOPAIEMENT_URLOK", $this->params['MONETICOPAIEMENT_URLOK']);
    define ("MONETICOPAIEMENT_URLKO", $this->params['MONETICOPAIEMENT_URLKO']);
    
    /* Monetico urls */
    if ($this->params['mode'] == 'live') 
      define ("MONETICOPAIEMENT_URLSERVER", $this->params['MONETICOPAIEMENT_URLSERVER_Live']);
    else
      define ("MONETICOPAIEMENT_URLSERVER", $this->params['MONETICOPAIEMENT_URLSERVER_Test']);
      
    /* Monetico params */
    define ("MONETICOPAIEMENT_VERSION", $this->params['MONETICOPAIEMENT_VERSION']);
    define ("MONETICOPAIEMENT_CTLHMAC", $this->params['MONETICOPAIEMENT_CTLHMAC']);
    define ("MONETICOPAIEMENT_CTLHMACSTR", $this->params['MONETICOPAIEMENT_CTLHMACSTR']);
    define ("MONETICOPAIEMENT_PHASE2BACK_RECEIPT", $this->params['MONETICOPAIEMENT_PHASE2BACK_RECEIPT']);
    define ("MONETICOPAIEMENT_PHASE2BACK_MACOK", $this->params['MONETICOPAIEMENT_PHASE2BACK_MACOK']);
    define ("MONETICOPAIEMENT_PHASE2BACK_MACNOTOK", $this->params['MONETICOPAIEMENT_PHASE2BACK_MACNOTOK']);
    define ("MONETICOPAIEMENT_PHASE2BACK_FIELDS", $this->params['MONETICOPAIEMENT_PHASE2BACK_FIELDS']);
    define ("MONETICOPAIEMENT_PHASE1GO_FIELDS", $this->params['MONETICOPAIEMENT_PHASE1GO_FIELDS']);
    define ("MONETICOPAIEMENT_URLPAYMENT", $this->params['MONETICOPAIEMENT_URLPAYMENT']);
  }
}
?>