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
 * PayBoxPayment (version 4.0) payment connexion
 */

class PayBoxPayment extends Input {
  /* variables */
  private $_lastErrorCode;
  private $_lastErrorMsg;
  private $_transactionId;

  /* 
   * constructor
   * @param string $path_type
   */
  function PayBoxPayment ( $path_type ) {
    parent::Input('PayBoxPayment', $path_type);
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
        'mode'            => 'test',  // live / test
        
        /* paybox keys */
        'bankKey_Test'    => '',
        'bankKey_Live'    => '',
        
        /* paybox config */
        'site'            => '',
        'rang'            => '',
        'identifiant'     => '',
        
        /* paybox fixed config */
        'hash'            => 'SHA512',
    );
        
    /* define params */
    $this->params = array_merge($dParams, $params);
    
    /* initialise transaction params */
    $this->transactionParams = array();
    
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
  
    /* */
    $dParams = array(
      'reference'           => '',
      'email'               => '',
      'amount'              => 0,
      'currency'            => 978, // 978: EUR
      'backURL_OK'          => '',
      'backURL_Cancel'      => '',
      'backURL_Refused'     => '',
      'backURL_Response'    => '',
      'backData'            => 'Reference:R;Transaction:S;Erreur:E',
      'date'                => date('c'),
    );
    
    /* merge params */
    $this->transactionParams = array_merge($dParams, $params);
    
    /* fix params */
    $this->transactionParams['amount'] = (int)($this->transactionParams['amount']*100);
  
    if ($this->params['mode'] == 'live') {
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
    // echo $serveurOK;
      
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
      'PBX_DEVISE'        => $this->transactionParams['currency'],
      'PBX_EFFECTUE'      => $this->transactionParams['backURL_OK'],
      'PBX_ANNULE'        => $this->transactionParams['backURL_Cancel'],
      'PBX_REFUSE'        => $this->transactionParams['backURL_Refused'],
      'PBX_REPONDRE_A'    => $this->transactionParams['backURL_Response'],
      'PBX_RETOUR'        => $this->transactionParams['backData'],
      'PBX_HASH'          => $this->params['hash'],
      'PBX_TIME'          => $this->transactionParams['date'],
    );
     
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
    
    $responseData['uniqueId'] = isset($_REQUEST['Reference'])?$_REQUEST['Reference']:'';
    $responseData['transaction'] = isset($_REQUEST['Transaction'])?$_REQUEST['Transaction']:'';
    $responseData['response'] = isset($_REQUEST['Erreur'])?$_REQUEST['Erreur']:'';
    
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
}
?>