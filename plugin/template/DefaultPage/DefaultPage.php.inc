<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template
 * Create Date             : Sep 2005
 * Last Modif Date         : Jan 2008
 * History :
 * * 05-09-xx : Initial File
 * * 08-01-07 : Rebuild template as an object
 *
 * Template Informations : Default
*/

class DefaultPage extends Template {
  /*
   * constructor
   * @param string $path_type
   */
  function DefaultPage ( $path_type ) {
    parent::Template('DefaultPage', $path_type);
    /* set tempalte title */
    $this->title = 'Default';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise template variable */
    $this->modules = 1;
  }
}
?>