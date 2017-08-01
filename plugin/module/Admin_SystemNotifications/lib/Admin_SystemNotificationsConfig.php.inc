<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date	: Jul 2017
 * Last Modif Date	: Jul 2017
 *
 * Admin_SystemNotificationsConfig configuration file
 * Access authentication values
 * * 0 : None - Not recommended
 * * 1 : Login - Using an account (result may be restricted by user rights)
 * * 2 : IP - Limited to IP given
 */

class Admin_SystemNotificationsConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_SystemNotificationsConfig ( $name, &$parent ) {
    parent::ModuleConfig($name, $parent);
    
    /* runnings vars */
    $this->add_newItem('running_lastCheck', 'date', 0);
    $this->add_newItem('running_cache', 'array', array());
    
    /* module vars */
    $this->add_newItem('module_mode', 'integer', 0); // 0: slave | 1: master
    $this->add_newItem('module_checkDelay', 'integer', 15);
    
	/* access vars */
	$this->add_newItem('access_status', 'integer', 1);
	$this->add_newItem('access_authentication', 'integer', 2);
	$this->add_newItem('access_authLogin', 'string', '');
	$this->add_newItem('access_authIP', 'string', '');

    /* generic initialisation */
    parent::init_config();
  }
  
  /* overwrite Module Config methods */
  
  /*
   * get object from header
   * @return void
   * @access public
   */
  public function get_fromHeader() {
    /* backup running vars */
    $lastCheck = $this->vars['running_lastCheck'];
    $cache = $this->vars['running_cache'];
    
    /* load vars from header */
    parent::get_fromHeader();
    
    /* reinject running vars */
    $this->vars['running_lastCheck'] = $lastCheck;
    $this->vars['running_cache'] = $cache;  
  }
  
  /* specific methods */
  
  
  /*
   * return module mode values
   * @return array
   * @access public
   */
  public function get_moduleModeList() {
    return array(
    	0 => $this->get_translation('modulemode_slave'),
    	1 => $this->get_translation('modulemode_master'),
	);
  }
  
  /*
   * return access status values
   * @return array
   * @access public
   */
  public function get_accessStatusList() {
    return array(
    	0 => $this->get_translation('accessstatus_disabled'),
    	1 => $this->get_translation('accessstatus_enabled'),
    );
  }
  
  /*
   * return access authentication values
   * @return array
   * @access public
   */
  public function get_accessAuthenticationList() {
    return array(
    	0 => $this->get_translation('accessauthentication_none'),
    	1 => $this->get_translation('accessauthentication_credentials'),
    	2 => $this->get_translation('accessauthentication_ipaddress'),
    );
  }
}
?>