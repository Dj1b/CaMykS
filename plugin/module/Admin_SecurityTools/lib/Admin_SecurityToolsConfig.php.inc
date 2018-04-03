<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date    : Oct 2007
 * Last Modif Date  : Mar 2018
 *
 * Admin_SecurityTools Config Object 
 */

final class Admin_SecurityToolsConfig extends PluginConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   * @return void
   * @access public
   */
  public function __construct($name, &$parent) {
    parent::__construct($name, $parent);
    
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