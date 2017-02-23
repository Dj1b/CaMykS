<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Creation Date	: Jun 2007
 * Last Modif Date	: Jun 2007
 * History :
 * * 07-06-xx : Initial files
 * 
 * Document Manager : control FileManager Input default folder.
*/

class Admin_DocumentManager extends Module {
  /* 
   * Constructor
   * @param string $path_type
   */
  function Admin_DocumentManager ( $path_type ) {
    parent::Module('Admin_DocumentManager', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author description */
    $this->author_name = 'sky';
    $this->author_mail = 'sky@mac-emu.net';
    $this->author_group = 'camyks.net';
  }

  /* overwrite module methods */
  
  /*
   * initialise module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check read rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();

    /* buttons list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink()));
				
    /* load FileManager Input object */
    if ( isset ( $camyks->inputs['FileManager'] ) ) {
      $this->fileManager = &$camyks->inputs['FileManager'];
      $this->fileManager->set_themeValues( $this->theme );
      $this->fileManager->set_engineValues('manage',
					   $camyks->get_adminLink($this->name),
					   array('add'=>$this->check_right(1)?'1':'0',
						 'remove'=>$this->check_right(2)?'1':'0'));
      $this->fileManager->initialise();
    } else {
      $this->init_admin_missingPlugin('Input', 'FileManager');
    }
    /* generic init */
    parent::init_admin();
  }
  
  /*
   * display module object in admin mode
   * @return void
   * @access private
   */
  function display_admin() {
    parent::display_admin();
  }

  /*
   * define rights for this module
   * @return void
   * @access private
   */
  function get_rights() {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> true);
    $this->rights[1] = array( 'name'=>'addfile',
			      'title'=> $this->get_translation('addfile'),
			      'default'=> false);
    $this->rights[2] = array( 'name'=>'removefile',
			      'title'=> $this->get_translation('removefile'),
			      'default'=> false);
    $this->rights[3] = array( 'name'=>'alterstructure',
			      'title'=> $this->get_translation('alterstructure'),
			      'default'=> false);
  }
}
?>