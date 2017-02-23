<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template
 * Create Date             : Feb 2007
 * Last Modif Date         : Jan 2008
 * History :
 * * 07-02-xx : Initial File
 * * 08-01-07 : Rebuild template as an object
 *      
 * ClassicPage template object
*/

class ClassicPage extends Template {
  /*
   * constructor
   * @param string $path_type
   */
  function ClassicPage( $path_type ) {
    parent::Template('ClassicPage', $path_type);
    /* set template title */
    $this->title = 'Classic';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise template varibles */
    $this->modules = 3;
  }
}
?>