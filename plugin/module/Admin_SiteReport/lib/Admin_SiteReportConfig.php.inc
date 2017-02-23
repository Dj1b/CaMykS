<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Config
 * Create Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 *
 * Admin_SiteReport Config Object 
 */

class Admin_SiteReportConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_SiteReportConfig ( $name, &$parent ) {
    parent::ModuleConfig( $name, $parent );
    /* object items */
    $this->add_newItem('file_allowed', 'boolean', false);
    $this->add_newItem('file_maxsize', 'int', 128 );
    /* generic initialisation */
    parent::init_config();
  }
}
?>