<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date	: May 2017
 * Last Modif Date	: May 2017
 * History : 
 * * 17-05-03: Initial files
 * 
 * CookieAgreementMessage input : Display cookie agreement message
 */

class CookieAgreementMessage extends Input {
  /* variables */
  var $path;
  var $params;
  var $dparams;

  /* 
   * constructor
   * @param string $path_type
   */
  function CookieAgreementMessage ( $path_type ) {
    parent::Input('CookieAgreementMessage', $path_type);
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
    
    /* check params */
    $this->check_params($params);
                
    /* check if cookie message has to be displayed */
    if ($camyks->get_sessionValue('cookieAccepted', 0) == 1) {
      $this->params['status'] = 'disabled';
      return;
    } elseif ($this->params['remindTTL'] > 0 and cookie_get('cookieAccepted') == 1) {
      $this->params['status'] = 'disabled';
      return;
    }
        
    /* add styles */
    if ($this->params['styleSource'] == 'plugin') {
      $this->add_styleFile('css/styles.css');
    }
    
    /* add scripts */
    $this->add_JSFile('CookieAgreementMessage.js');
    $this->add_JSEngineFile('tool/cookie.js');
    $this->add_JSLoadScript('cookieMessage = new CookieAgreementMessage("cookieMessage");');
    $this->add_JSLoadScript('cookieMessage.set_param("cookieTTL", '.$this->params['remindTTL'].');');
    $this->add_JSLoadScript('cookieMessage.initialise();');
    
    /* remove cookie for other pages of the same session */
    $camyks->set_sessionValue('cookieAccepted', 1);
    
    /* Input generic initialization */
    parent::initialise();
  }
  
  /*
   * display input
   * @return void
   * @access public
   */
  function display() {
    if ($this->params['status'] == 'enabled')
      parent::display();
  }
  
  /* specific tool methods */
  
  /*
   * check params
   * @param array $params
   * @return void
   * @access private
   */
  function check_params($params=array()) {
    /* build default params list */
    $this->dParams = array(
        'status'        => 'enabled',   // enabled / disabled
        'message'       => '',
		'styleSource'   => 'plugin',    // plugin / theme
 		'aboutCookie'   => '',          // empty / URL / true: send to default cookie page
		'remindTTL'     => 365,         // days to remind agreement
		
		/* styleSource : input */
		'location'      => 'top',       // top / top-left / top-right / bottom / bottom-left / bottom-right
	);
			   
    /* build internal params list */
    $this->params = array_merge($this->dParams, $params);
    
    /* check params */
    if ($this->params['message'] == '') $this->params['message'] = $this->get_translation('defaultmessage');
    
    if ($this->params['aboutCookie'] === true) $this->params['aboutCookie'] = $this->get_translation('aboutcookieurl');
  }
}
?>