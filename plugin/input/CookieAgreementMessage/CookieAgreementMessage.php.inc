<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date	: May 2017
 * Last Modif Date	: Feb 2018
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
    global $camyks;
    parent::Input('CookieAgreementMessage', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load configuration library */
    $this->load_library('CookieAgreementMessageConfig');
    
    /* register plugin as Admin_Site extension */
    $this->register_asExtension('Admin_Site');
    
    /* load config */
    $this->config = new CookieAgreementMessageConfig('config', $this);
    $this->config->get();
    
    /* check for automatique adding */
    if ($camyks->mode == CAMYKS_MODE_SITE and $this->config->vars['insertion'] == 1) {
      $this->register_asCaMykSEventHandler('onPageLoad');
      $this->register_asCaMykSEventHandler('onBodyClose');
    }
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
    $this->add_JSLoadScript('CookieAgreementMessage.set_param("cookieTTL", '.$this->params['remindTTL'].');');
    $this->add_JSLoadScript('CookieAgreementMessage.initialise();');
    
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
  
  /*
   * execute handler on body closing
   * @return string
   * @access public
   */
  public function execute_onCaMykSPageLoad() {
    $this->initialise();
  }
  
  /*
   * execute handler on body closing
   * @return string
   * @access public
   */
  public function execute_onCaMykSBodyClose() {
    $this->display();
    return '';
  }
  
  /* specific tool methods */
  
  /*
   * check params
   * @param array $params
   * @return void
   * @access private
   */
  function check_params($params=array()) {
    global $camyks;
    
    /* build default params list */
    $this->dParams = array(
        'status'        => 'enabled',   // enabled / disabled
	);
			   
    /* build internal params list */
    $this->params = array_merge($this->dParams, $this->config->vars);
    
    /* check for single language message */
    if (is_array($this->params['message'])) {
      if (isset($this->params['message'][$camyks->current_language]))
        $this->params['message'] = $this->params['message'][$camyks->current_language];
      else {
        if (count($this->params['message']) > 0)
          foreach ($this->params['message'] as $l => $m) {
            $this->params['message'] = $m;
            break;
          }
        else
          $this->params['message'] = '';
      }
    }
       
    /* merge params */
    $this->params = array_merge($this->params, $params);
    
    /* check params */
    if ($this->params['message'] == '') $this->params['message'] = $this->get_translation('defaultmessage');
    
    if ($this->params['aboutCookie'] === true or $this->params['aboutCookie'] === 'true') $this->params['aboutCookie'] = $this->get_translation('aboutcookieurl');
  }
  
  /* Admin_Site extension configuration methods */
  
  /*
   * initialise object in Admin_Site / view configuration mode
   * @return void
   * @access public
   */
  public function initialise_configDisplay() {
  }
  
  /*
   * display object in Admin_Site / view configuration mode
   * @return void
   * @access public
   */
  public function display_configDisplay() {
    $this->load_file('html/configuration/view.html.inc');
  }
  
  /*
   * initialise object in Admin_Site / edit configuration mode
   * @param Object $form
   * @return void
   * @access public
   */
  public function initialise_configEdition($form) {
    
    /* update form */
    $this->form = &$form;
    $this->form->set_object($this->config);
  
    /* add scripts */
    $this->add_JSFile('CookieAgreementMessageConfig.js');
    $this->add_JSLoadScript('CookieAgreementMessageConfig.set_param("form", '.$this->form->name.');');
    $this->add_JSLoadScript('CookieAgreementMessageConfig.initialise();');
  }
  
  /*
   * display object in Admin_Site / edit configuration mode
   * @return void
   * @access public
   */
  public function display_configEdition() {
    $this->load_file('html/configuration/edit.html.inc');
  }
    
  /*
   * execute object in Admin_Site / save configuration mode
   * @return void
   * @access public
   */
  public function save_configuration() {
    $this->config->get_fromHeader();
    return $this->config->save();
  }
}
?>