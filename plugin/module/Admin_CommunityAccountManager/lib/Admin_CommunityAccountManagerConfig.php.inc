<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date    : Oct 2010
 * Last Modif Date  : Oct 2010
 *
 * Admin_CommunityAccountManager configuration object
 *
 */

class Admin_CommunityAccountManagerConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_CommunityAccountManagerConfig ( $name, &$parent ) {
    global $camyks;
    parent::ModuleConfig( $name, $parent );

    /* registration params */
    $this->add_newItem('registration_status', 'int', 0);
    $this->add_newItem('registration_validation', 'int', 0);
    $this->add_newItem('registration_captcha', 'int', 0);

    /* login params */
    $this->add_newItem('login_status', 'int', 0);
    $this->add_newItem('login_method', 'int', 0);
    $this->add_newItem('login_allowcookie', 'int', 0);
    $this->add_newItem('login_cookiettl', 'int', 30);

    /* generic initialisation */
    parent::init_config();
  }

  /* overwrite ModuleConfig methods */


  /* specific methods */

  /*
   * return registration status list
   * @return array
   * @access public
   */
  function get_registrationStatusList() {
    return array(0=>$this->get_translation('config_registrationstatus_closed'),
		 1=>$this->get_translation('config_registrationstatus_invitation'),
		 2=>$this->get_translation('config_registrationstatus_opened'));
  }

  /*
   * return registration validation list
   * @return array
   * @access public
   */
  function get_registrationValidationList() {
    return array(0=>$this->get_translation('config_registrationvalidation_none'),
		 1=>$this->get_translation('config_registrationvalidation_email'),
		 2=>$this->get_translation('config_registrationvalidation_admin'));
  }

  /*
   * return registration captcha list
   * @return array
   * @access public
   */
  function get_registrationCaptchaList() {
    return array(0=>$this->get_translation('config_registrationcaptcha_none'),
		 1=>$this->get_translation('config_registrationcaptcha_securimage'));
  }

  /*
   * return login status list
   * @return array
   * @access public
   */
  function get_loginStatusList() {
    return array(0=>$this->get_translation('config_loginstatus_closed'),
		 1=>$this->get_translation('config_loginstatus_limited'),
		 2=>$this->get_translation('config_loginstatus_opened'));
  }

  /*
   * return login method list
   * @return array
   * @access public
   */
  function get_loginMethodList() {
    return array(0=>$this->get_translation('config_loginmethod_full'),
		 1=>$this->get_translation('config_loginmethod_login'),
		 2=>$this->get_translation('config_loginmethod_email'));
  }
}
?>