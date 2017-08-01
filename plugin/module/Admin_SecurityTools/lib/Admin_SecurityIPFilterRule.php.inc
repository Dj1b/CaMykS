<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Library
 * Create Date		: Oct 2007
 * Last Modif Date	: Oct 2007
 *
 * Admin_SecurityIPFilterRule Library Object for Admin_SecurityTools Module
 * Items :
 * - ipaddress : ip address to match ( allow * regroupment )
 * - active : if rule is active
 * - permission : define if ip rule allow or deny ipaddress
 * - mode : camyks mode where rule is set
 * - comment : admin comment for the rule
 */

class Admin_SecurityIPFilterRule extends ModuleLibrary {
  
  /*
   * constructor
   * @param integer $id
   * @param Module $parent
   */
  function Admin_SecurityIPFilterRule ( $id, &$parent ) {
    global $camyks;
    parent::ModuleLibrary( $id, $parent );
    /* library items */
    $this->add_newItem('ipaddress', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('active', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('permission', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('sitemode', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('comment', 'db', 'text', 'varchar', 255, '');
    
    /* generic library initialisation */
    parent::init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check library data
   * @return boolean result
   * @access private
   */
  function check_data() {
    /* check if ip is valid */
    if ( string_isValidIPv4( $this->_libItems['ipaddress']->value, true ) === false ) {
      $this->_libError = $this->get_translation('error_nonvalidipaddress');
      return false;
    }
    return true;
  }
  
  /* specific tool methods */

  /*
   * check IP Filter security
   * @return boolean result
   * @access private
   */
  function check_security() {
    global $camyks;
    
    
    /* init result */
    $allow = true;
    
    /* get client IP */
    $ip = client_getIp();
    
    /* get all rules */
    $this->rules = $this->get_objectList(false, 'active=1', -1, -1);
    
    /* check if IP match a rule */
    foreach ( $this->rules as $rule ) {
      $pattern = $this->update_matching_ip( $rule->vars['ipaddress']);
      if ( preg_match( $pattern, $ip  ) ) {
	/* ip match to a rule ip address */
	if ( $rule->vars['sitemode'] == 0
	     or ( $rule->vars['sitemode'] == 1 and $camyks->mode == CAMYKS_MODE_SITE )
	     or ( $rule->vars['sitemode'] == 2 and $camyks->mode == CAMYKS_MODE_ADMIN ) ) {
	  if ( $rule->vars['permission'] == 0 ) {
	    $allow = true;
	    break;
	  } else { 
	    $allow = false;
	  }
	}
      }
    }
    /* kill navigator session if ip is not allowed */
    if ( !$allow ) {
      $error = array('title'=>'Security: Access denied',
                     'description'=>'',
                     'content1'=>'This website have an active IP Filter.',
                     'content2'=>'Your IP is currently into the blacklist database.',
                     'content3'=>'Please contact the website administrator.');
      header('HTTP/1.1 403 Forbidden');
      $camyks->throwFatalError( $error );
    }
  }
  
  /*
   * transform ip to regexp matching expression
   * @param string $ip the IP to transform
   * @return string updated IP
   * @access private
   */
  function update_matching_ip( $ip ) {
    $replace = '/\*/';
    $by = '([0-9]{1,3})';
    return '/\A'.preg_replace( $replace, $by, $ip ).'\Z/';
  }
}
?>
