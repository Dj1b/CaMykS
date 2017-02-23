<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template
 * Create Date             : Dec 2007
 * Last Modif Date         : Jan 2008
 * History :
 * * 07-12-20 : Initial file
 * * 08-01-07 : Rebuild template as an object
 *
 * WebPageLight template object
 */

class WebPageLight extends Template {
  /*
   * constructor
   * @param string $path_type
   */
  function WebPageLight( $path_type ) {
    parent::Template( 'WebPageLight', $path_type );
    /* set template title */
    $this->title = 'WebPage Light';
    /* set plugin verison */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise template variables */
    $this->modules = 3;
  }
}
?>