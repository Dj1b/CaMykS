<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Create Date		: Jun 2005
 * Last Modif Date	: Mar 2017
 * History :
 * * 05-06-xx : Initial file 
 * * 08-02-19 : layouts update
 * * 08-05-28 : Disable admin menu for data I/O modes
 * * 08-06-18 : Some HTML improvements for W3C compatibility
 * * 08-07-02 : Some minor HTML improvements
 * * 17-03-17 : Some minor Code & HTML improvements
 *
 * Admin_User module
 * Manage admin users profiles and rights
 */

class Admin_User extends Module {
  /* variables */
  var $user;
  var $user_list;
  var $mode;
  
  /*
   * constructor
   * @param strin $path_type
   */
  function Admin_User ( $path_type ) {
    parent::Module('Admin_User', $path_type);
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
    
    /* initialise plugin variables */
    $this->layout_itemsByLine = 3;
    $this->layout_cellwidth = '180px';
    
    /* load plugin libraries */
    $this->libs[] = 'AdminUser.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->user = new AdminUser ('');
  }

  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->user->install( ) ) {
      return parent::install();
    }
    return false;
  }
  
  /*
   * unsinstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return 'module_can_t_be_uninstalled';
  }

  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    return $this->user->is_installed();
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
    /* get user list */
    $this->user_list = $this->user->get_userList();

    /* button list for buttons bar */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link' =>$camyks->get_adminLink()));
    
    /* update layout */
    $this->selected_layout = 'admin_list.html.inc';
  }

  /* 
   * init module object in admin/edit mode
   * @return void
   * @access private
   */
  function init_admin_edit ( ) {
    global $camyks;
    if ( $this->check_right (1)===false ) {
      return $this->init_admin_actionNotAllowed();
    }
    
    /* get user profile to modify */
    if ( $this->user->login == '' ) {
      $this->user->login = isset ( $_REQUEST['user'] ) ? $_REQUEST['user'] : '';
      $this->user->get();
    } else {
      $this->user->initialise();
    }
    
    /* get form */
    $this->form = new HTMLForm('adminuser',
			       $this->get_adminLink(),
			       'POST');
    $this->form->add_hidden('mode', 'save' );
    $this->form->add_hidden('adminuser_full_update', 1 );
    $this->form->add_hidden('adminuser_webmaster', $this->user->webmaster );
    $this->form->add_hidden('adminuser_is_new', $this->user->is_new );  
      
    /* check if a user is modifying a webmaster */
    if ( $camyks->adminUser->webmaster == 0 and $this->user->webmaster == 1 ) {
      $this->text = $this->get_translation('usermodificationnotallowed');
      $this->selected_layout = 'admin_message.html.inc';
      $this->selected_layout_location = 'camyks';
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('mode'=>'list')));
      return;
    }
    
    /* get javascript for tabs */
    $this->tabObject = 'adminuserTabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$camyks->theme->parts['boxTabCSSStandart'].'","'
			.$camyks->theme->parts['boxTabCSSSelected'].'","'
			.$camyks->theme->parts['boxTabCSSRollover'].'");');
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('personalinfos')),
			array('name'=>'rights',
			      'title'=>$this->get_translation('rights')));
    
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=> $this->get_adminLink()),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    
    /* get javascript for new passord entries */
    if ( $this->user->is_new == 0 ) {
      $this->add_JSEngineFile('object/cmdd.js');
      $this->add_JSScript('adminuser_pwdObject = new Cmdd();' );
      $this->add_JSScript('adminuser_pwdObject.init("changepwd", "","","","");' );
    }
    
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
    /* get user profile to view */
    $this->user = new AdminUser ((isset ( $_REQUEST['user'] ) ? $_REQUEST['user'] : ''));
    $this->user->get();
    
    /* get javascript for tabs */
    $this->tabObject = 'adminuserTabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$camyks->theme->parts['boxTabCSSStandart'].'","'
			.$camyks->theme->parts['boxTabCSSSelected'].'","'
			.$camyks->theme->parts['boxTabCSSRollover'].'");');
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('personalinfos')),
			array('name'=>'rights',
			      'title'=>$this->get_translation('rights')));
    
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink($this->name, array('mode'=>'list'))));
    if ($this->check_right(1)===true)
      $this->buttons[] = array('title'=>$camyks->get_translation('edit'),
			       'link'=>$this->get_adminLink(array('mode'=>'edit', 'user'=>$this->user->login)));
    
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
   */
  function init_admin_save ( ) {
    global $camyks;

    /* check rights */
    if ( $this->check_right(1)===false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get user */
    $this->user = new AdminUser( );
    $this->user->get_fromHeader( 'adminuser_' );
    if ( $this->user->save( ) ) {
      $this->text = $camyks->get_translation('savedone');
      $this->selected_layout = 'admin_message.html.inc';
      $this->selected_layout_location = 'camyks';
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('mode'=>'view', 'user'=> $this->user->login))); 
    } else {
	  $this->init_admin_edit();
    }
  }

  /* specific tool methods */
  
  /*
   * return structured array with name and email
   * @param string $login
   * @return array
   * @access public
   */
  function get_userNameAndEmail ( $login ) {
    $user = new AdminUser( $login );
    $user->get_fromDatabase();
    return array('login'=>$user->login,
		 'firstname'=>$user->firstname,
		 'lastname'=>$user->lastname,
		 'email'=>$user->email);
  }

  /*
   * return structured array of all active users 
   * @param integer $objMode
   * @return array
   * @access public
   */
  function get_activeUserList($objMode=false) {
    return $this->user->get_activeUserList($objMode);
  }

  /*
   * return all users list
   * @param integer $objMode
   * @return array
   * @access public
   */
  function get_userList($where='', $objMode=false) {
    return $this->user->get_userList($where, $objMode);
  }

  /*
   * return status values
   * @return array
   * @access private
   */
  function get_userStatusList() {
    global $camyks;
    $list = array();
    $list[0] = $camyks->get_translation('inactive');
    $list[1] = $camyks->get_translation('active');
    return $list;
  }
}
?>