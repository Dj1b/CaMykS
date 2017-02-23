<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme 
 * Create Date		: Jul 2008
 * Last Modif Date      : Jul 2008
 * History :
 * * 08-06-03 : Initial File
 *
 * Theme : Sunny Blocks Style
 */

class SunnyBlocksStyle extends Theme {
  /*
   * constructor
   * @param string $path_type
   */
  function SunnyBlocksStyle( $path_type ) {
    parent::Theme('SunnyBlocksStyle', $path_type);
    /* set theme title */
    $this->title = 'Sunny Blocks';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
}
?>