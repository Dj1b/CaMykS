<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme 
 * Create Date		: Dec 2008
 * Last Modif Date      : Dec 2008
 * History :
 * * 08-12-28 : Initial File
 *
 * Mac OS 7 Theme
 */

class MacOS7Style extends Theme {
  /* constructor */
  function MacOS7Style( $path_type ) {
    parent::Theme('MacOS7Style', $path_type);
    /* set theme title */
    $this->title = 'Mac OS 7';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Fun &amp; Games';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite theme methods */
  
  function get_boxTitleBar ( $title='' ) {
    $title = trim(preg_replace('/&nbsp;/i', '', $title));
    if ($title=='')
      return $this->get_part('boxTitleBarE');
    return $this->get_part('boxTitleBar', array($title));
  }
}
?>