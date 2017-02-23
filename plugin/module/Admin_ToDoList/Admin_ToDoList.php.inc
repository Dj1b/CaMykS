<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Apr 2007
 * Last Modif Date	: May 2008
 * History :
 * * 07-04-xx : Initial files
 * * 08-05-28 : Disable admin menu for data I/O modes
 *
 * Admin_ToDoList Module
 * Allow admin user to share thing to be done and comment 
 */

class Admin_ToDoList extends Module {
  /* variables */
  var $item;
  var $comment;
  var $todolist;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_ToDoList ( $path_type ) {
    parent::Module('Admin_ToDoList', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'helpers';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';

    /* load plugin libraries */
    $this->libs[] = 'Admin_ToDoItem.php.inc';
    $this->libs[] = 'Admin_ToDoComment.php.inc';
    $this->get_PHPLibs();

    /* initialise plugin libraries */
    $this->item = new Admin_ToDoItem( 0, $this );
    $this->comment = new Admin_ToDoComment( 0, $this );
  }

  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->item->install( ) and $this->comment->install( ) ) {
      return parent::install();
    }
    return false;
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    parent::uninstall();
    /* TO DO */
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    return $this->comment->is_installed();
  }

  /*
   * get module rights
   * @return void
   * @access private
   */
  function get_rights ( ) {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> true);
    $this->rights[1] = array( 'name'=>'write',
			      'title'=> $camyks->get_translation('write'),
			      'default'=> true);
  }

  /*
   * update description in control panel
   * @return void
   * @access private
   */
  function get_adminControlPanelAction ( ) {
    global $camyks;
    $n = $this->item->get_objectCount('to_user="" or to_user="'.
				      $camyks->adminUser->login.
				      '" or from_user="'.
				      $camyks->adminUser->login.'"');
    $camyks->trads['mod_admin_todolist_desc'] = vsprintf($camyks->trads['mod_admin_todolist_desc_'], $n );
  }

  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check read rights */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied();
    }
    
    /* get mode */
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
    case 'savecomment':
      /* mode == savecomment */
      $this->init_admin_savecomment();
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
   * init module object in display mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /* specific admin mode methods */

  /*
   * init module object in admin/list mode
   * @return void
   * @access private
   */
  function init_admin_list ( ) {
    global $camyks;
    /* get to-do-items list */
    $this->todolist = $this->item->get_objectList(false,
						  'to_user="" or to_user="'.
						  $camyks->adminUser->login.
						  '" or from_user="'.
						  $camyks->adminUser->login.'"');
    /* get tabs engine */
    $this->get_admin_tabs ( );
  }

  /*
   * init module object in admin/edit mode
   * @return void
   * @access private 
   */
  function init_admin_edit ( ) {
    global $camyks;
    if ( $this->check_right ( 1 )===false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* get user profile to modify */
    if ( $this->item->id == -1 ) {
      $this->item->id = isset ( $_REQUEST['todo'] ) ? $_REQUEST['todo'] : 0;
      $this->item->get();
    }
    
    /* get form */
    $this->form = new HTMLForm( 'admintodolist',
				$camyks->get_adminLink($this->name),
				'POST');
    $this->form->add_hidden('mode', 'save' );
    $this->form->add_hidden('todo', $this->item->id );
    $this->form->add_hidden('from_user', $this->item->vars['from_user'] );
    $this->form->add_hidden('creation_date', $this->item->vars['creation_date'] );
    
    /* get list( and tabs engine ) */
    $this->init_admin_list();
    
    /* select tabs */
    $this->add_JSLoadScript('admin_todolist_tabObject.mouseclick("edit");');
  }
  
  /*
   * init module object in admin/view mode
   * @return void
   * @access private
   */
  function init_admin_view ( ) {
    global $camyks;
    /* get user profile to view */
    $this->item->id = isset ( $_REQUEST['todo'] ) ? $_REQUEST['todo'] : 0;
    $this->item->get();
    
    /* get comment form */
    $this->form = new HTMLForm( 'admintodolist',
				$camyks->get_adminLink($this->name),
				'POST');
    $this->form->add_hidden('mode', 'savecomment' );
    $this->form->add_hidden('todo', $this->item->id );
    $this->form->add_hidden('from_user', $camyks->adminUser->login );
    $this->form->add_hidden('creation_date', -1 );
    
    /* select tabs */
    $this->add_JSLoadScript('admin_todolist_tabObject.mouseclick("view");');
    
    /* get list( and tabs engine ) */
    $this->init_admin_list();
  }

  /*
   * init module object in admin/delete mode
   * @return void
   * @access private
   */
  function init_admin_delete ( ) {
    global $camyks;

    /* check rights */
    if ( $this->check_right(1)=== false ) {
      return $this->init_admin_actionNotAllowed();
    }
     
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get item */
    $this->item->id = isset ( $_REQUEST['todo'] ) ? $_REQUEST['todo'] : 0;
    if ( $this->item->delete_fromDatabase( ) ) {
      $this->text = $camyks->get_translation('deletedone');
      $this->selected_layout = 'admin_message.html.inc';
      $this->selected_layout_location = 'camyks';
	$this->set_redirect( 4, $camyks->get_adminLink( $this->name, array('mode'=>'list'))); 
    } else {
      $this->init_admin_edit();
    }
  }
  
  /*
   * init module object in admin/save mode
   * @return void
   * @access private
   */
  function init_admin_save ( ) {
    global $camyks;
    /* check rights */
    if ( $this->check_right(1)===false ) {
      return $this->init_admin_actionNotAllowed();
    }
     
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get item */    
    $this->item->id = isset ( $_REQUEST['todo'] ) ? $_REQUEST['todo'] : 0;
    $this->item->get_fromHeader(  );
    if ( $this->item->save( ) ) {
      $this->text = $camyks->get_translation('savedone');
      $this->selected_layout = 'admin_message.html.inc';
      $this->selected_layout_location = 'camyks';
      $this->set_redirect( 4, $camyks->get_adminLink( $this->name, array('mode'=>'view', 
									 'todo'=> $this->item->id))); 
    } else {
      $this->init_admin_edit();
    }
  }

  /*
   * init module object in admin/savecomment mode
   * @return void
   * @access private
   */
  function init_admin_savecomment ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get comment item */
    $this->comment->id = 0;
    $this->comment->get_fromHeader(  );
    if ( $this->comment->save( ) ) {
      $this->text = $this->get_translation('commentsaved');
    } else {
      $this->text = $this->get_translation('commentnotsaved');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect( 4, $camyks->get_adminLink( $this->name, 
						    array('mode'=>'view', 
							  'todo'=> $this->comment->_libItems['todo']->value))); 
  }

  /* specific tool methods */

  /*
   * get javascript for tabs
   * @return void
   * @access private
   */
  function get_admin_tabs ( ) {
    global $camyks;
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript('admin_todolist_tabObject = new CTab();');
    $this->add_JSScript('admin_todolist_tabObject.init("general", "'
			.$camyks->theme->parts['boxTabCSSStandart'].'","'
			.$camyks->theme->parts['boxTabCSSSelected'].'","'
			.$camyks->theme->parts['boxTabCSSRollover'].'");');
  }
}

?>