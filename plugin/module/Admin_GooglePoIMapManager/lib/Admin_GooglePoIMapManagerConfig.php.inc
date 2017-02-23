<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date    : Jun 2010
 * Last Modif Date  : Jun 2010
 *
 * Admin_GooglePoIMapManager configuration file
 */

class Admin_GooglePoIMapManagerConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_GooglePoIMapManagerConfig ( $name, &$parent ) {
    parent::ModuleConfig($name, $parent);

    /* site configuration */
    $this->add_newItem('google_mapapikey', 'string', '');

    /* generic initialisation */
    parent::init_config();
  }
}
?>