<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme 
 * Create Date		: Dec 2008
 * Last Modif Date      : Jan 2009
 * History :
 * * 08-12-31 : Initial File
 *
 * Blue Box theme
 */

class BlueBoxStyle extends Theme {
  /* constructor */
  function BlueBoxStyle( $path_type ) {
    parent::Theme('BlueBoxStyle', $path_type);
    /* set theme title */
    $this->title = 'Blue Box';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite theme methods */
  
  /*
   * send main css to camyks object
   * @return void
   * @access private
   */
  function get_main_css() {
    global $camyks;
    parent::get_main_css();
    
    /* load IE specific CSS styles */
    if (preg_match('/msie/i', $_SERVER['HTTP_USER_AGENT'])) {
      $camyks->HTMLPage->add_styleFile($this->get_fileURL('editor_ie.css'));
    }
  }
  
  /*
   * load theme parts as included file
   * @return void
   * @access public
   */
  function get_parts() {
    global $camyks;
    if (!$this->partsLoaded) {
      parent::get_parts();
      if(preg_match('/msie/i', $_SERVER['HTTP_USER_AGENT'])) {
        /* load IE specific CSS styles */
        $camyks->HTMLPage->add_styleFile($this->get_fileURL('parts_ie.css'));
      }
    }
  }
}
?>