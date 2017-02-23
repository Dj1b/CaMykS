<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Creation Date	: Jun 2005
 * Last Modif Date	: May 2008
 * History :
 * 05-05-xx : Initial files
 * 07-05-xx : Add english locales
 * 08-05-18 : Add online help (french)
 * 
 * Admin_MyAccount Module
 * Allow logged admin user to modify its own account
*/

class Admin_MyAccount extends Module {
  /* variables */
  var $myAccount;
  var $form;

  /* 
   * constructor
   * @param boolean $path_type
   */
  function Admin_MyAccount ( $path_type ) {
    parent::Module('Admin_MyAccount', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'personal';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite Module methods */  

  /*
   * get rights list
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
   * initialise module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;

    /* get informations */
    $this->myAccount = &$camyks->adminUser;  
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : '' );

    /* if user has no rights for this module, make redirection to home */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied () ;
    } else if ( $this->check_right(1) === false ) {
      $this->init_admin_view();
    } else {
      switch ( $this->mode ) {
      case 'save':
	/* mode == save */
	$this->init_admin_save();
	break;
      case 'modify':
      default:
	/* mode == modify */
	$this->init_admin_modify();
	break;
      }
    }
    parent::init_admin();
  }
  
  /*
   * display module object in admin mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /* specific admin mode methods */

  /*
   * initialise module object in admin/view mode
   * @return void
   * @access private
   */
  function init_admin_view() {
    global $camyks;
   
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink()));
    
    /* update layout */
    $this->selected_layout = 'admin_r.html.inc';
  }

  /* 
   * initialise module object in admin/modify mode
   * @param 
   */
  function init_admin_modify() {
    global $camyks;

    /* get form */
    $this->form = new HTMLForm('myAccount',
			       $camyks->get_adminLink($this->name, array('mode'=>'save')),
			       'POST');
    $this->form->add_hidden('myaccount_login', $this->myAccount->login );
    $this->form->add_hidden('myaccount_fullupdate', '0' );
    
    /* update focus */
    $this->add_JSLoadScript('document.'.$this->form->name.'.myaccount_lastname.focus();');
    
    /* set password layout javascript */
    $this->add_JSEngineFile ( 'object/cmdd.js');
    $this->add_JSScript('myaccount_pwdObject = new Cmdd();' );
    $this->add_JSScript('myaccount_pwdObject.init("changepwd", "","","","");' );
    $this->add_JSLoadScript('myaccount_pwdObject.selectItem(0);');
   
    /* set button list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink()),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    
    /* update layout */
    $this->selected_layout = 'admin_rw.html.inc';
  }

  /*
   * initialise module object in admin/save mode
   * @return void
   * @access private
   */
  function init_admin_save() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get account data */
    $this->myAccount->get_fromHeader ('myaccount_');
    $this->myAccount->is_new = false;

    /* save account */
    if ( $this->myAccount->save ( ) ) {
      $this->text = $this->get_translation('savedone');
      /* update layout */
      $this->selected_layout = 'admin_message.html.inc';
      $this->selected_layout_location = 'camyks';
      $this->set_redirect(5, $camyks->get_adminLink( $this->name, array('mode'=> 'modify') ) );
    } else {
      $this->init_admin_modify();
    }

  }
}
?>