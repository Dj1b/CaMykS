<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date	: Jan 2015
 * Last Modif Date	: Jan 2015
 *
 * Admin_SystemUniqueIDManagerConfig configuration file
 */

class Admin_SystemUniqueIDManagerConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_SystemUniqueIDManagerConfig ( $name, &$parent ) {
    parent::ModuleConfig($name, $parent);
    
    /* generating */
    $this->add_newItem('generating_method', 'integer', 0);
    $this->add_newItem('generating_length', 'integer', 10);
    $this->add_newItem('generating_maxAttempts', 'integer', 25);
    

    /* generic initialisation */
    parent::init_config();
  }  
}
?>