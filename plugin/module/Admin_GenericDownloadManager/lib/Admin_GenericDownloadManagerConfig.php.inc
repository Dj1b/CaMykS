<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Config
 * Create Date		: May 2008
 * Last Modif Date	: Apr 2009
 *
 * Admin_GenericDownloadManagerConfig Object 
 */

class Admin_GenericDownloadManagerConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_GenericDownloadManagerConfig ( $name, &$parent ) {
    parent::ModuleConfig( $name, $parent );

    /* config items */
    $this->add_newItem('main_stats', 'boolean', false);
    $this->add_newItem('file_size', 'float', 8 );
    $this->add_newItem('link_mode', 'integer', 0);

    /* generic initialisation */
    parent::init_config();
  }
}
?>