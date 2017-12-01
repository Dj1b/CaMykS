<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Creation Date	: Mar 2007
 * Last Modif Date	: May 2008
 * History :
 * * 07-03-xx : Initial files
 * * 08-05-28 : Disable admin menu for data I/O modes
 *
 * Admin Groups Management Module
 * Contain 2 default groups : all, none
*/

class Admin_Group extends Module {
  /* variables */
  var $mode;
  var $group;
  var $groups;

  /*
   * constructor
   * @param $path_type
   */
  function Admin_Group ( $path_type ) {
    parent::Module('Admin_Group', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'users';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load libs */
    $this->libs[] = 'AdminGroup.php.inc';
    $this->get_PHPLibs();
    $this->group = new AdminGroup('', $this);
    $this->groups = null;
  }
  
  /* overwrite Module methods */

  /*
   * install module object
   * @return boolean success
   * @access private
   */
  function install ( ) {
    /* install admin group library object */
    if ( $this->group->install( ) ) {
      return parent::install();
    }
    return false;
  }

  /*
   * unsinstall module object
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return false;
  }

  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    return $this->group->is_installed();
  }

  
  /*
   * initialise module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check basic rights */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied();
    }

    /* get module mode */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'list' );

    /* get action to execute case of mode */
    switch ( $this->mode ) {
    case 'view':
      /* mode == view */
      $this->init_admin_view();
      break;
    case 'edit':
      /* mode == edit */
      $this->init_admin_edit();
      break;
    case 'save':
      /* mode == save */
      $this->init_admin_save();
      break;
    case 'delete':
      /* mode == delete */
      $this->init_admin_delete();
      break;
    case 'list':
    default:
      /* mode == list */
      $this->init_admin_list();
      break;
    }
    parent::init_admin();
  }

  /*
   * initialise module object in display mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /* specific admin mode methods */
  
  /*
   * initialise module object in admin/list mode
   * @return void
   * @access private
   */
  function init_admin_list ( ) {
    global $camyks;

    /* get group list */
    $this->group_list = $this->group->static_getAdminList();

    /* get butotns */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link' =>$camyks->get_adminLink()));
   
    /* update layout */
    $this->selected_layout = 'admin_list.html.inc';
  }

  /*
   * initialise module object in admin/edit mode
   * @return void
   * @access private
   */
  function init_admin_edit ( ) {
    global $camyks;
    /* check rights */
    if ( $this->check_right ( 1 )===false ) 
      return $this->init_admin_actionNotAllowed();
    /* check dependencies */
    if ( ! isset ( $camyks->inputs['QuickItemList'] ) )
      return $this->init_admin_missingPlugin ( 'input', 'QuickItemList');
    
    /* get group to edit */
    if ( $this->group->name == '' and isset ( $_REQUEST['group'] ) ) {
      $this->group->name = $_REQUEST['group'];
      $this->group->get();
    }

    /* get form */
    $this->form = new HTMLForm('admin_group_form',
			       $camyks->get_adminLink( $this->name, array('mode'=>'save' )),
			       'POST');
    $this->form->add_hidden('is_new', $this->group->is_new);
    $this->form->add_hidden('users', $this->group->users_);
    if ( $this->group->is_new == 0 ) {
      $this->form->add_hidden('name', $this->group->name);
    }
    
    /* get user list */
    $this->user_list = $camyks->modules['Admin_User']->user->static_getList();
    
    /* get list input object */
    $this->input = $camyks->inputs['QuickItemList'];
    $this->input->initialise('userchooser',
			     $this->get_translation('allusers'),
			     $this->user_list,
			     $this->get_translation('selusers'),
			     $this->group->users,
			     $this->form->name,
			     'users',
			     ':');

    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=> $camyks->get_adminLink($this->name, array('mode'=>'list'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));


    /* update layout */
    $this->selected_layout = 'admin_edit.html.inc'; 
  }
  
  /*
   * init module object in admin/view mode
   * @return void
   * @access private
   */
  function init_admin_view ( ) {
    global $camyks;
    /* get group */
    $n = isset ( $_REQUEST['group'] ) ? $_REQUEST['group'] : '';
    $this->group = new AdminGroup ( $n, $this );
    $this->group->get();

    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=> $camyks->get_adminLink($this->name, array('mode'=>'list'))));
    if ($this->check_right(1)===true)
      $this->buttons[] = array('title'=>$camyks->get_translation('edit'),
			       'link'=>$camyks->get_adminLink($this->name, array('mode'=>'edit', 'group'=>$this->group->name)));

    /* update layout */
    $this->selected_layout = 'admin_view.html.inc';
  }

  /*
   * init module object in admin/delete mode
   * @return void
   * @access private
   */
  function init_admin_delete ( ) {
    /* to do */
  }

  /* 
   * init module object in admin/save mode
   * @return void
   * @access private
   */
  function init_admin_save ( ) {
    global $camyks;
    if ( $this->check_right(1) === false ) {
      /* get 'action not allowed' init */
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* get group */
    $n = isset ( $_REQUEST['group'] ) ? $_REQUEST['group'] : '';
    $this->group = new AdminGroup ( $n, $this );
    $this->group->get_fromHeader();
    if ( $this->group->save() ) {
      /* automatic redirection */
      $this->set_redirect ( $camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('mode' => 'view',
									 'group' => $this->group->name )));
      /* update layout */
      $this->text = $camyks->get_translation('savedone');
      $this->selected_layout = 'admin_message.html.inc';
	$this->selected_layout_location = 'camyks';
    } else {
      $this->init_admin_edit();
    }
  }

  /* specific tool methods */

  /*
   * get all groups
   * @return array
   * @access public
   */
  function get_groups () {
    if ( $this->groups == null )
      $this->groups = $this->group->get_objectList();
    return $this->groups;
  }
}
?>