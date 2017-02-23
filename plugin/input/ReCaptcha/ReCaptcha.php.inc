<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Create Date		: Feb 2016
 * Last Modif Date	: Feb 2016
 * History : 
 * * 16-02-03 : Initial files
 * 
 * ReCaptcha input : Generate and check captcha code
 * Website : https://www.google.com/recaptcha
 */

class ReCaptcha extends Input {
  /* variables */
  private $_lastError;

  /* 
   * constructor
   * @param string $path_type
   */
  function ReCaptcha ( $path_type ) {
    parent::Input('ReCaptcha', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
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

    /* build default params */
    $dParams = array(
        'mode' => 'display',
        'publicKey' => $camyks->get_confValue('reCaptcha_publicKey'),
        'privateKey' => $camyks->get_confValue('reCaptcha_privateKey'),
    );
        
    /* define params */
    $this->params = array_merge($dParams, $params);
    
    /* add script */
    if ($this->params['publicKey'] != false and $this->params['mode'] != 'verify')
      $this->add_JSExternFile('https://www.google.com/recaptcha/api.js');

    
    /* define variables */
    $this->_lastError = '';
    
    /* Input generic initialization */
    parent::initialise();
  }

  /* 
   * display input
   * @param string $layout
   * @return void
   * @access public
   */
  function display($layout='captcha') {
    if ( $layout == null ) $layout = 'captcha';
    if ( $layout != 'captcha')
      return;
    $this->selected_layout = 'input_'.$layout.'.html.inc';
    if ($this->params['publicKey'] != false)
      parent::display();
  }
  
  /* specific tool methods */

  /*
   * verify captcha
   * @return boolean result
   * @access private
   */
  function verify() {
  
    /* get captcha value */
    if (!isset($_POST['g-recaptcha-response'])) {
      $this->_lastError = 'error_captcha_missing';
      return false;
    }
    $captcha = $_POST['g-recaptcha-response'];

    /* send request to recaptcha */
    $result = json_decode(file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$this->params['privateKey'].'&response='.$captcha.'&remoteip='.client_getIp()), true);
        
    /* check result */
    if ($result['success'] === false) {
      /* save error */
      if (isset($result['error-codes'])) {
        foreach ($result['error-codes'] as $error) {
          $this->_lastError = 'error_'.preg_replace('/-/', '_', $error);
          break;
        }
      }
      return false;
    }
    return true;
  }
  
  /*
   * return last error code
   * @return string
   * @access public
   */
  function get_lastErrorCode() {
    return $this->_lastError;
  }
  
  /*
   * return last error as text
   * @return string
   * @access public
   */
  function get_lastError() {
    if ($this->_lastError == '')
      return '';
    return $this->get_translation($this->_lastError);
  }
}
?>