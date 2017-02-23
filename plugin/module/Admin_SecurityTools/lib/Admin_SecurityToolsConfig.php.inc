<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Config
 * Create Date		: Oct 2007
 * Last Modif Date	: Dec 2007
 *
 * Admin SecurityTools Config Object 
 */

class Admin_SecurityToolsConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_SecurityToolsConfig ( $name, &$parent ) {
    parent::ModuleConfig( $name, $parent );
    /* object items */
    $this->add_newItem('ipfilter', 'boolean', false);
    $this->add_newItem('backup', 'boolean', false);
    $this->add_newItem('backup_method', 'string', 'manual');
    $this->add_newItem('backup_compression', 'string', 'tgz');
    $this->add_newItem('backup_nextdate', 'int', 0 );
    $this->add_newItem('backup_type', 'string', 'complete');
    $this->add_newItem('backup_temp', 'string', '');
    /* generic initialisation */
    parent::init_config();
  }
}
?>