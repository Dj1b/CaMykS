<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version  	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date    	: Jun 2005
 * Last Modif Date	: May 2008
 * History : 
 * * 05-06-xx : Initial files
 * * 08-02-xx : English localisation
 * * 08-05-28 : Update menu
 * * 08-07-02 : Rebuild main layout
 * * 08-07-31 : New category : Configuration
 *
 * ControlPanel Module
*/

class Tool_ControlPanel extends Module {
  /* variables */
  var $admin_modules;
  var $cols;

  /*
   * Constructor
   * @param string $path_type
   */
  function Tool_ControlPanel ( $path_type ) {
    /* get Module generic init */
    parent::Module('Tool_ControlPanel', $path_type);
    /* set module type */
    $this->type = 'tool';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* initialise plugin variables */
    $this->admin_modules = array();
    $this->cols = 2;

    /* create some admin group to order main modules */
    $this->admin_modules['personal'] = array();
    $this->admin_modules['content'] = array();
    $this->admin_modules['users'] = array();
    $this->admin_modules['configuration'] = array();
    $this->admin_modules['monitoring'] = array();
    $this->admin_modules['helpers'] = array();
    $this->admin_modules['devel'] = array();
    $this->admin_modules['specific'] = array();
  }
  
  /* overwrite Module methods */
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin() {
    global $camyks;
    /* list all modules to display */
    foreach ( $camyks->modules as $mod_name => $mod ) {
      /* get only admin type module */
      if ( $mod->type == 'admin' ) {
	/* check if module is installed */
	if ( $mod->is_installed()!== false ) {
	  /* check if user is able to view this module */
	  if ( $mod->check_right ( 0 ) ) {
	    /* check if an admin type is defined */
	    if ( !isset ( $mod->admin_type ) ) {
	      $mod->admin_type = 'other';
	    }
	    /* check if group already exists */
	    if ( !isset ( $this->admin_modules[$mod->admin_type] ) ) {
	      $this->admin_modules[$mod->admin_type] = array();
	    }	    
	    /* add module name in list */
	    $this->admin_modules[$mod->admin_type][] = $mod_name;
	    /* get specific init */
	    $camyks->modules[$mod_name]->get_adminControlPanelAction();
	  }
	}
      }
    }
  }
  
  /*
   * display module object in admin mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /*
   * return menu item to be registered
   * @return array
   * @access private
   */
  function get_adminEngineGenericMenuItems ( ) {
    global $camyks;
    return array(array('menu' => 'admin',
		       'name'=>'homepanel', 
		       'title' => $this->get_translation('adminhome'),
		       'url' => $camyks->get_adminLink($this->name),
		       'icon'=>$this->get_fileURL('img/icon12.gif')));
  }
}
?>