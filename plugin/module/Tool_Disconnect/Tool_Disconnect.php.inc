<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Oct 2005
 * Last Modif Date	: May 2008
 * History :
 * * 05-10-xx : Initial files
 * * 08-05-28 : Update menu
 *
 * Tool_Disconnect object
 */

class Tool_Disconnect extends Module {
  /*
   * constructor
   * @param string $path_type 
   */
  function Tool_Disconnect ( $path_type ) {
    parent::Module('Tool_Disconnect', $path_type);
    /* set module type */
    $this->type = 'tool';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->authors_name = 'CaMykS Team';
    $this->authors_mail = 'camyks.contact@gmail.com';
    $this->authors_group = 'camyks.net';
  }

  /* overwrite Module methods */  

  /*
   * init module object
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* disable admin menus */
    $this->disable_adminEngineMenus();
    /* kill admin user session */
    $camyks->kill_session();
    /* redirect user to login panel */
    $this->set_redirect(4, $camyks->get_adminLink());
    /* build message panel */
    $this->text = $this->get_translation('message');
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }
  
  /*
   * display module object
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
		       'name'=>'disconnect', 
		       'title' => $this->get_translation('disconnect'),
		       'url' => $camyks->get_adminLink($this->name),
		       'icon'=>$this->get_fileURL('img/icon12.gif')));
  }
}
?>