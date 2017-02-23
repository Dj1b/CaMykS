<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme 
 * Create Date		: Jun 2008
 * Last Modif Date      : Jun 2008
 * History :
 * * 08-05-29 : Initial File
 *
 * Theme : Psionic Storm Style
 */

class PsionicStormStyle extends Theme {
  /*
   * constructor
   * @param string $path_type
   */
  function PsionicStormStyle( $path_type ) {
    parent::Theme('PsionicStormStyle', $path_type);
    /* set theme title */
    $this->title = 'Psionic Storm';
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