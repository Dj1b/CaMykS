<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Engine
 * Create Date		: May 2007
 * Last Modif Date	: Jun 2008
 * History :
 * * 07-05-xx : Initial files
 * * 08-05-28 : Disable admin menu for data I/O modes
 * * 08-06-02 : Add english dictionnary
 * * 08-06-18 : Minor improvements for W3C compatibility
 *
 * Admin_MyShortcuts Module
 * Allow admin user to add some admin page as bookmark
 */

class Admin_MyShortcuts extends Module {
  /* variables */
  var $mode;
  var $list;
  
  /* 
   * constructor
   * @param string $path_type
   */
  function Admin_MyShortcuts ( $path_type ) {
    parent::Module('Admin_MyShortcuts', $path_type);
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

    /* load plugin libraries */
    $this->libs[] = 'Admin_UserShortcut.php.inc';
    $this->get_PHPLibs();

    /* initialise plugin libraries */
    $this->sitem = new Admin_UserShortcut(0, $this);

    /* initialise plugin variables */
    $this->slist = null;
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install() {
    /* install library object */
    if ( $this->sitem->install() )
      return parent::install();
    return false;
  }
  
  /*
   * uninstall database from database
   * @return boolean success
   * @access private
   */
  function uninstall() {
    return $this->sitem->uninstall();
  }
  
  /*
   * check installation
   * @return boolean result
   * @access public
   */
  function is_installed() {
    return $this->sitem->is_installed();
  }

  /*
   * get module rights
   * @return void
   * @access private
   */
  function get_rights() {
    global $camyks;
    $this->rights[0] = array('name'=>'read',
			     'title'=> $camyks->get_translation('read'),
			     'default'=> true);
  }
  
  /*
   * register a menu in admin interface
   * @return array
   * @access private
   */
  function get_adminEngineGenericMenus( ) {
    if ( $this->check_right(0) ) {
      return array(array('name'=>'myshortcuts',
			 'title'=>$this->get_translation('menutitle')));
    }
    return array();
  }
  
  /*
   * register menu items in admin interface
   * @return array
   * @access private
   */
  function get_adminEngineGenericMenuItems( ) {
    global $camyks;
    if ( $this->check_right(0)===true ) {
      $menu = array();
      /* get user shortcuts list */
      $this->get_userShortcuts();
      /* add "add shortcuts" */
      $menu[] = array('name'=>'add_newshortcut',
		      'title'=>$this->get_translation('add_newshortcut'),
		      'icon'=>$this->get_fileURL('img/add12.gif'),
		      'menu'=>'myshortcuts',
		      'url'=>'javascript:adminengine_modalPopupOpen(\'admin_myshortcuts_addpopup\');globalCMenu.unselect(\'myshortcutsMenu\')');
      $menu[] = array('name'=>'edit_shortcuts',
		      'title'=>$this->get_translation('edit_shortcuts'),
		      'icon'=>$this->get_fileURL('img/edit12.gif'),
		      'menu'=>'myshortcuts',
		      'url'=> $this->get_adminLink());
      if ( count($this->slist) > 0 ) {
	$menu[] = array('name'=>'separator',
			'title'=>'----',
			'menu'=>'myshortcuts');
	
	/* add "shortcuts" */
	$cnt = 0;
	foreach ( $this->slist as $item ) {
	  $menu[] = array('name'=>'shortcut'.$cnt,
			  'title'=> $item->vars['name'],
			  'icon'=>$this->get_fileURL('img/favorite12.gif'),
			  'menu'=>'myshortcuts',
			  'url'=>$camyks->site_conf['admin_entry'].'?'.htmlentities($item->vars['url']));
	  $cnt++;
	}
      }
      return $menu;
    }
    return array();
  }
  
  /*
   * initialise module object adminengine mode
   * @return void
   * @access private 
   */
  function get_adminEngineGenericInit ( ) {
    global $camyks;
    /* build form */
    $this->addform = new HTMLForm('admin_myshortcut_addform',
				  $camyks->get_adminLink($this->name),
				  'POST');
    $this->addform->add_hidden('mode', 'add_new' );
    $this->addform->add_hidden('user', $camyks->adminUser->login );
    $this->addform->add_hidden('url', htmlentities($_SERVER['QUERY_STRING']));

    /* build popup buttons */
    $this->popupbuttons = array(array('title'=>$camyks->get_translation('close'),
				    'link'=>'javascript:adminengine_modalPopupClose(\'admin_myshortcuts_addpopup\')'),
			      array('title'=>$camyks->get_translation('add'),
				    'link'=>$this->addform->get_HTMLSubmitLink()));
    return;
  }

  /*
   * display module object in adminengine mode
   * @return void
   * @access private
   */
  function get_adminEngineGenericDisplay ( ) {
    $this->load_file( 'html/adminengine.html.inc' );
  }
  
  /*
   * init object when in admin mode
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
    $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'main';

    /* execute mode */
    switch ( $this->mode ) {
    case 'delete':
      $this->init_admin_delete();
      break;
    case 'add_new':
      $this->init_admin_add_new();
      break;
    case 'edit':
      $this->init_admin_edit();
      break;
    case 'save':
      $this->init_admin_save();
      break;
    case 'main':
    default:
      $this->init_admin_main();
      break;
    }

    /* generic module admin initialisation */
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
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  function init_admin_main( ) {
    global $camyks;
    /* get admin user shortcuts */
    $this->get_userShortcuts();
    
    /* add needed javascript code */
    $this->add_JSScript('var shortcutsDeleteMessage="'.string_html2Text($this->get_translation('js_deletemessage')).'";');
    $deleteLink = $camyks->get_adminJSLink($this->name,
					   array('mode'=>'delete',
						 'id'=>''));    
    $this->add_JSScript('var shortcutsDeleteLink="'.$deleteLink.'";');
    
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
			   'link'=>$camyks->get_adminLink()));
  }  
  
  /*
   * init module object in admin/delete mode
   * @return void
   * @access private
   */
  function init_admin_delete() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    $this->sitem->id = isset( $_REQUEST['id'])?$_REQUEST['id']:0; 
    if ( $this->sitem->delete() ) {
      $this->text = $camyks->get_translation('deletedone');
    } else {
      $this->text = $camyks->get_translation('deletefailed');
    }
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }
  
  /*
   * init module object in admin/add_new mode
   * @return void
   * @access private
   */
  function init_admin_add_new() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();
    
    /* get item */
    $this->sitem->get_fromHeader();
    if ( $this->sitem->save() ) {
      $this->text = $camyks->get_translation('savedone');
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->site_conf['admin_entry'].'?'.$this->sitem->_libItems['url']->value);
    } else {
      $this->text = $camyks->get_translation('savefailed');
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink() );
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * init module object in admin/edit mode
   * @return void
   * @access private
   */
  function init_admin_edit () {
    global $camyks;
    
    /* get admin user shortcuts */
    $this->get_userShortcuts();

    /* get object id */
    $this->sitem->id = isset( $_REQUEST['id'])?$_REQUEST['id']:0; 
    
    /* update layout */
    $this->selected_layout='admin_edit.html.inc';
    /* add form object */
    $this->form = new HTMLForm('admin_myshortcuts',
			       $camyks->get_adminLink($this->name, 
						      array('mode'=>'save')),
			       'POST');
    $this->form->add_hidden('id', $this->sitem->id );
    $this->form->add_hidden('user', $this->slist[$this->sitem->id]->vars['user'] );
    $this->form->add_hidden('url', $this->slist[$this->sitem->id]->vars['url'] );
    $this->form->add_hidden('_date', $this->slist[$this->sitem->id]->vars['_date'] );

    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( )));
  }

  /*
   * init module object in admin/edit mode
   * @return void
   * @access private
   */
  function init_admin_save () {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get item */
    $this->sitem->id = isset( $_REQUEST['id'])?$_REQUEST['id']:0;
    $this->sitem->get_fromHeader();
    if ( $this->sitem->save() ) {
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /* specific tool methods */

  /*
   * get current admin user shortcuts
   * @return void
   * @access private
   */
  function get_userShortcuts( ) {
    global $camyks;
    /* check if list already exist  */
    if ( isset ( $this->slist ) ) {
      return;
    }
    /* get list */
    $this->slist = $this->sitem->get_objectList(false, 'user="'.$camyks->adminUser->login.'"');
  }
}
?>