<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template
 * Create Date             : Fev 2008
 * Last Modif Date         : Fev 2008
 * History :
 * * 08-02-11 : Initial file
 *
 * WebPageUltraExtended template object
 */

class WebPageUltraExtended extends Template {
  /*
   * constructor
   * @param string $path_type
   */
  function WebPageUltraExtended( $path_type ) {
    parent::Template('WebPageUltraExtended', $path_type );
    /* set template title */
    $this->title = 'WebPage Ultra Extended';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise template variables */
    $this->modules = 6;
  }
}
?>