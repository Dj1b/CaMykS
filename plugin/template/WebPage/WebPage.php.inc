<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template
 * Create Date             : Nov 2007
 * Last Modif Date         : Jan 2008
 * History :
 * * 07-11-19 : Initial file
 * * 07-12-04 : Layout Update
 * * 08-01-07 : Rebuild template as an object
 *
 * WebPage template object
 */

class WebPage extends Template {
  /*
   * constructor
   * @param string $path_type
   */
  function WebPage( $path_type ) {
    parent::Template('WebPage', $path_type);
    /* set template title */
    $this->title = 'WebPage';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise template variables */
    $this->modules = 4;
  }
}
?>