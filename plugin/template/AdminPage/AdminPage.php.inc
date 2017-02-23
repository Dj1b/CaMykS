<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template
 * Creation Date           : Sep 2005
 * Last Modif Date         : Jan 2008
 * History : 
 * * 05-09-xx : Initial File
 * * 08-01-07 : Rebuild template as an object
 * * 08-07-11 : Rebuild template for more compatibility
 *
 * AdminPage template object
*/

class AdminPage extends Template {
  /*
   * constructor
   * @param string $path_type
   */
  function AdminPage ( $path_type ) {
    parent::Template('AdminPage', $path_type );
    /* set template title */
    $this->title = 'Admin';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise template variables */
    $this->modules = 2;
  }
  
  
  /* specific tool methods */
  
  /*
   * return signature image URL
   * @return string
   * @access private
   */
  function get_signPicture() {
  	global $camyks;
  	$default = $this->get_fileURL('img/sign_fr.png');
  	return $this->get_fileURL('img/sign_'.$camyks->current_language.'.png', null, $default);
  }
}
?>