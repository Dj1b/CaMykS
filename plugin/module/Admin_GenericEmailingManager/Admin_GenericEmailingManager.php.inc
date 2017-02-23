<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.1
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Dec 2012
 * Last Modif Date  : Dec 2012
 * History :
 * * 12-12-17 : Initial files
 * 
 * Admin_GenericEmailingManager
 */

class Admin_GenericEmailingManager extends Module {
  /* variables */
  var $contactItem;
  var $contactList;
  
  var $emailingItem;
  var $emailingList;
  
  var $config;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GenericEmailingManager ( $path_type ) {
    parent::Module('Admin_GenericEmailingManager', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load plugin libraries */
    $this->libs[] = 'Admin_GenericEmailingManagerConfig.php.inc';
    $this->libs[] = 'Admin_GenericEmailingManagerContact.php.inc';
    $this->libs[] = 'Admin_GenericEmailingManagerContactsImportConfig.php.inc';
    $this->libs[] = 'Admin_GenericEmailingManagerEmailing.php.inc';
    $this->libs[] = 'Admin_GenericEmailingManagerEmailingConfig.php.inc';
    $this->libs[] = 'Admin_GenericEmailingManagerEmail.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->config = new Admin_GenericEmailingManagerConfig('config', $this);
    $this->contactItem = new Admin_GenericEmailingManagerContact(0, $this);
    $this->emailingItem = new Admin_GenericEmailingManagerEmailing(0, $this);
    $this->emailItem = new Admin_GenericEmailingManagerEmail(0, $this);
    
    $this->maxFileSize = 8; // Mo
    $this->extensions = null;
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ( $this->contactItem->install() and $this->emailingItem->install()
    	and $this->emailItem->install() and parent::install());
  }
  
  /*
   * unintall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return parent::uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->emailingItem->is_installed();
  }
  
  /*
   * register a menu in admin interface
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenus( ) {
    if ( !($this->mode == 'main' and $this->check_right(1))
        and !( $this->mode == 'view_emailing' and $this->check_right(2)
        and $this->emailingItem->id > 0 and $this->emailingItem->vars['status'] == 2))
      return array();
  
    $menus = array(array('name'=>'emailingmanager',
			 'title'=>$this->get_translation('menutitle')));
    
    /* load extensions */
    $this->load_registeredExtensions();
  
    /* load extensions menus */
    foreach ($this->extensions as &$plugin) {
       $ms = $plugin->load_managerMenu();
       foreach ($ms as $m)
         if (!isset($menus[$m]))
           $menus[] = array('name'=>$m, 'title'=>$this->get_translation('ext_'.$m));
    }
    
    return $menus;
  }

  /*
   * register menu items in admin interface
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenuItems( ) {
    global $camyks;
    
    $items = array();
    
    /* set menus */
    if ( $this->mode == 'view_emailing' and $this->check_right(2)
        and $this->emailingItem->id > 0 and $this->emailingItem->vars['status'] == 2 ) {
      $items[] = array('name'=>'resultsexport',
			 'title'=>$this->get_translation('resultsexport'),
			 'icon'=>$this->get_fileURL('img/xls.gif'),
			 'menu'=>'emailingmanager',
			 'url'=>'javascript:window.open(\'request.php?module='.$this->name.'&mode=export_emailingResults&emailing='.$_REQUEST['emailing_id'].'\');void(0);');
    } elseif ($this->mode == 'main' and $this->check_right(1)) {
      $items[] = array('name'=>'contactsimport',
			 'title'=>$this->get_translation('contactsimport'),
			 'icon'=>$this->get_fileURL('img/xls.gif'),
			 'menu'=>'emailingmanager',
			 'url'=>$this->get_adminLink(array('mode'=>'import_contactsPrepare')));
      $items[] = array('name'=>'contactsexport',
			 'title'=>$this->get_translation('contactsexport'),
			 'icon'=>$this->get_fileURL('img/xls.gif'),
			 'menu'=>'emailingmanager',
			 'url'=>'javascript:window.open(\'request.php?module='.$this->name.'&mode=export_contactList\');void(0);');
    
    }
  
    /* load extensions */
    $this->load_registeredExtensions();
  
    /* load extensions menus */
    foreach ($this->extensions as &$plugin)
       $items = array_merge($items, $plugin->load_managerMenuItems());
       
    return $items;
  }
  
  /*
   * get module rights
   * @return void
   * @access private
   */
  function get_rights() {
    global $camyks;
    $this->rights[0] = array('name'=>'read_data',
			     'title'=> $this->get_translation('read_data'),
			     'default'=> false);
    $this->rights[1] = array('name'=>'edit_data',
			     'title'=> $this->get_translation('edit_data'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'read_emailings',
			     'title'=> $this->get_translation('read_emailings'),
			     'default'=> false);
    $this->rights[3] = array('name'=>'edit_emailings',
			     'title'=> $this->get_translation('edit_emailings'),
			     'default'=> false);
    $this->rights[4] = array('name'=>'send_emailings',
			     'title'=> $this->get_translation('send_emailings'),
			     'default'=> false);
    $this->rights[5] = array('name'=>'config',
			     'title'=> $this->get_translation('config'),
			     'default'=> false);
  }
 
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;

    /* check read rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();

    /* check dependencies */
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    if (!isset($camyks->inputs['AdminItemListViewer']))
      return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
      
    /* load config */
    $this->config->get();

    /* get informations */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'main' );
    
    switch ( $this->mode ) {
    case 'edit_config':
      /* mode == edit_config */
      $this->init_admin_edit_config();
      break;
    case 'save_config':
      /* mode == save_config */
      $this->init_admin_save_config();
      break;
    case 'view_emailing':
      /* mode == view_emailing */
      $this->init_admin_view_emailing();
      break;
    case 'edit_emailing':
      /* mode == edit_emailing */
      $this->init_admin_edit_emailing();
      break;
    case 'save_emailing':
      /* mode == save_emailing */
      $this->init_admin_save_emailing();
      break;
    case 'delete_emailing':
      /* mode == delete_emailing */
      $this->init_admin_delete_emailing();
      break;
    case 'send_emailing':
      /* mode == send_emailing */
      $this->init_admin_send_emailing();
      break;
    case 'reset_emailing':
      /* mode == reset_emailing */
      $this->init_admin_reset_emailing();
      break;
    case 'edit_contact':
      /* mode == edit_contact */
      $this->init_admin_edit_contact();
      break;
    case 'save_contact':
      /* mode == save_contact */
      $this->init_admin_save_contact();
      break;
    case 'delete_contact':
      /* mode == delete_contact */
      $this->init_admin_delete_contact();
      break;
    case 'delete_email':
      /* mode == delete_email */
      $this->init_admin_delete_email();
      break;
    case 'mark_email':
      /* mode == mark_email */
      $this->init_admin_mark_email();
      break;
    case 'import_contactsPrepare':
      /* mode == import_contactsPrepare */
      $this->init_admin_import_contactsPrepare();
      break;
    case 'import_contactsCheckAndConfigure':
      /* mode == import_contactsCheckAndConfigure */
      $this->init_admin_import_contactsCheckAndConfigure();
      break;
    case 'import_contactsExecute':
      /* mode = import_contactsExecute */
      $this->init_admin_import_contactsExecute();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
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
  
  /*
   * execute module object in request mode
   * @return void
   * @access private
   */
  function execute_request() {
    global $camyks;
    
    /* check action value */
    if ( isset( $_REQUEST['mode'] ) ) {
      $action = $_REQUEST['mode'];
    } else {
      /* throw fatal error */
      $error = array('title'=>$this->get_translation('fatalerror_actionundefined'),
		     'description'=>$this->get_translation('fatalerror_actionmustbeset1'),
		     'content1'=>$this->get_translation('fatalerror_actionmustbeset2'));
		  $camyks->throwFatalError( $error );
    }
    
    /* execute action */
    switch ( $action ) {
      case 'preview_emailing':
      	/* mode == preview emailing */
        $this->execute_request_previewEmailing();
        break;
      case 'withdraw_contact':
      	/* mode == withdraw_contact */
        $this->execute_request_withdrawContact();
        break;
      case 'export_emailingResults':
        /* mode == export_emailingResults */
        $this->execute_request_exportEmailingResults();
        break;
      case 'export_contactList':
        /* mode == export_contactList */
        $this->execute_request_exportContactList();
        break;
      case 'send_emailingInitialise':
      	/* mode == send_emailingInitialise */
        $this->execute_request_sendEmailingInitialise();
        break;
      case 'send_emailingExecute':
      	/* mode == send_emailingExecute */
        $this->execute_request_sendEmailingExecute();
        break;
      case 'send_emailingFinalise':
      	/* mode == send_emailingFinalise */
        $this->execute_request_sendEmailingFinalise();
        break;
      case 'import_contactInitialise':
      	/* mode == import_contactInitialise */
        $this->execute_request_importContactInitialise();
        break;
      case 'import_contactExecute':
      	/* mode == import_contactExecute */
        $this->execute_request_importContactExecute();
        break;
      case 'import_contactFinalise':
      	/* mode == import_contactFinalise */
        $this->execute_request_importContactFinalise();
        break;
      case 'email_action':
      	/* mode == email_action */
      	$params = explode('-', isset($_REQUEST['params'])?$_REQUEST['params']:'');
      	$action = array_shift($params);
      	switch ($action) {
      	    case 'check':
      	        $this->execute_request_setEmailAsOpened($params);
      	        break;
      	    case 'link':
      	        $this->execute_request_openEmailLink($params);
      	        break;
      	    case 'display':
      	        $this->execute_request_previewEmailing($params);
      	        break;
      	    case 'unsubscribe':
      	        $this->execute_request_unsubscribeContact($params);
      	        break;
      	}   
        break;
      default :
        /* throw fatal error */
        $error = array('title'=>$this->get_translation('fatalerror_actionundefined'),
		     'description'=>$this->get_translation('fatalerror_actionmustbeset1'),
		     'content1'=>$this->get_translation('fatalerror_actionmustbeset2'));
		    $camyks->throwFatalError( $error );
    }
  }
  
  /* specific admin mode methods */

  /*
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  function init_admin_main() {
    global $camyks;
    
    /* get help */
    $this->get_help();

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(array('name'=>'contacts',
				     'title'=>$this->get_translation('contacts')),
				     ));
		if ($this->check_right(2)) {
			/* complete tabs */
    	    $this->tabBuilder->add_tab(array('name'=>'emailings',
				'title'=>$this->get_translation('emailings')));
		}
		if ($this->check_right(5)) {
		    /* complete tabs */
    	    $this->tabBuilder->add_tab(array('name'=>'config',
				'title'=>$this->get_translation('configuration')));
		}
	
		if ( $this->help != null )
	  	$this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'fact'));
    
    /* build contact tab */
    $this->load_file('lib/Admin_GenericEmailingManagerContactListParams.php.inc');
    $this->contactList = new AdminItemListViewer('camyks');
    $this->contactList->set_params($this->contactListParams);
    $this->contactList->initialise();
    
    if ($this->check_right(2)) {
    	/* build emailing tabs */
    	$this->load_file('lib/Admin_GenericEmailingManagerEmailingListParams.php.inc');
    	$this->emailingList = new AdminItemListViewer('camyks');
    	$this->emailingList->set_params($this->emailingListParams);
    	$this->emailingList->initialise();
    }
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }
  
  /*
   * init module object in admin/edit_config mode
   * @return void
   * @access private
   */
  function init_admin_edit_config() {
    global $camyks;
    
    /* check edit product rights */
    if ( $this->check_right(5) === false )
      return $this->init_admin_actionNotAllowed();
                
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array('name'=>'manager',
				       'title'=>$this->get_translation('properties')));
	if ( $this->help != null )
	 	$this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));

    $this->tabBuilder->initialise(array('default'=>'manager'));
    
    /* load config form */
    $this->editform = new HTMLForm('edit_config',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_config')),
				   'POST');
    $this->editform->set_object($this->config);
    
    /* load page chooser input */
    $this->add_JSFile('configuration.js');
    if (isset($camyks->inputs['PageChooser'])) {
	  $this->pc = true;
      $camyks->inputs['PageChooser']->initialise("pagename", null, "update_selectedPage");
	} else {
	  $this->pc = false;
	}
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('configuration');
    
    /* build button list */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				        'title'=>$camyks->get_translation('back')),
				     array('link'=>$this->editform->get_HTMLSubmitLink(),
				        'title'=>$camyks->get_translation('valid')),
				    );
    
    /* update layout */
    $this->selected_layout = 'admin_edit_config.html.inc';
  }
  
  /* 
   * init module object in admin/save_config mode
   * @return void
   * @access private
   */
  function init_admin_save_config() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(5) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save object */
    $this->config->get_fromHeader();
    if ( $this->config->save() ) {
      $this->text = $this->get_translation('config_saved');
    } else {
      $this->text = $this->get_translation('config_notsaved');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'config')));
  }
  
  /*
   * init module object in admin/view_emailing mode
   * @return void
   * @access private
   */
  function init_admin_view_emailing() {
    global $camyks;
    
    /* check edit emailing rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
      
    /* get help */
    $this->get_help();

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(array('name'=>'properties',
				       'title'=>$this->get_translation('tabproperties')),
				       array('name'=>'sending',
				       'title'=>$this->get_translation('tabsending')),
				       ));
				       
	  if ( $this->help != null )
	    $this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
				         
    /* get emailing item */
    $emailing_id = isset($_REQUEST['emailing_id'])?$_REQUEST['emailing_id']:0;
    $this->emailingItem->id = $emailing_id;
    $this->emailingItem->get();
    $this->emailingItem->get_fromItems();
    
    /* load data */
    $this->emailingStatusList = $this->get_emailingStatusList();
    $this->contactSourceList = $this->get_contactSourceList();
    
    if ($this->emailingItem->vars['status'] == 0) {
        $source = explode(':', $this->emailingItem->vars['contact_source']);
        if ($source[0] == 'internal') {
     	  $this->contactCount = $this->count_contacts(array('status'=>$source[1],
    		'group'=>$this->emailingItem->vars['contact_group']));
        } elseif (isset($camyks->modules[$source[0]])) {
          $this->contactCount = $camyks->modules[$source[0]]->count_emailingManagerContacts($source[1]);
        } else {
          $this->contactCount = 0;
        }
   	} elseif ($this->emailingItem->vars['status'] == 2) {
   	  $this->contactNameList = array();
   	  $this->emailingStatisticsSummary = $this->get_emailingStatisticsSummary($this->emailingItem->id);
   	  /* build email tab */
      $this->load_file('lib/Admin_GenericEmailingManagerEmailListParams.php.inc');
      $this->emailList = &$camyks->inputs['AdminItemListViewer'];
      $this->emailList->set_params($this->emailListParams);
      $this->emailList->initialise();
      $this->tabBuilder->add_tab(array('name'=>'emails',
				       'title'=>$this->get_translation('tabdetails')));
	  
	  /* get contact list */
	  $sources = array();
	  foreach ($this->emailList->objectList as $email) {
	    if (!isset($sources[$email->vars['source']]))
	      $sources[$email->vars['source']] = array();
	    $sources[$email->vars['source']][$email->vars['contact']] = '';
	  }
	  	  	  	  
	  foreach ($sources as $source => $contacts) {
	    $src = explode(':', $source);
        if ($src[0] == 'internal') {
          $l = $this->contactItem->get_fullNameList(array('ids'=>array_keys($contacts)));
        } elseif (isset($camyks->modules[$src[0]])) {
          $l = $camyks->modules[$src[0]]->get_emailingManagerContactTitleFromIds(array_keys($contacts));
        } else {
          $l = array();
        }
        foreach ($contacts as $id => $title) {
          if (isset($l[$id]))
            $sources[$source][$id] = $l[$id];
        }
	  }
	  	  
	  foreach ($this->emailList->objectList as &$email) {
	    if (isset($sources[$email->vars['source']][$email->vars['contact']]))
	      $email->vars['title'] = $sources[$email->vars['source']][$email->vars['contact']];
	  }
   	}
   	
   	/* initialise tabs */
   	$this->tabBuilder->initialise(array('default'=>'properties'));
   	
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->emailingItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('emailingnew');
    else
      $this->adminTitle .= $this->get_translation('emailingid', $this->emailingItem->id);
     
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('openTab'=>'emailings')),
				 'title'=>$camyks->get_translation('back')));
    
    /* update layout */
    $this->selected_layout = 'admin_view_emailing.html.inc';
  }
  
  /*
   * init module object in admin/edit_emailing mode
   * @return void
   * @access private
   */
  function init_admin_edit_emailing() {
    global $camyks;
    
    /* check edit emailing rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed();
      
    /* get help */
    $this->get_help();

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(array('name'=>'properties',
				       'title'=>$this->get_translation('tabproperties')),
				       array('name'=>'advanced',
				       'title'=>$this->get_translation('tabadvanced')),
				       ));
				       
	  if ( $this->help != null )
	    $this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
				     
    $this->tabBuilder->initialise(array('default'=>'properties'));
    
    /* get emailing item */
    $emailing_id = isset($_REQUEST['emailing_id'])?$_REQUEST['emailing_id']:0;
    $this->emailingItem->id = $emailing_id;
    $this->emailingItem->get();
    $this->emailingItem->get_fromItems();
    
    /* load data */
    $this->emailingStatusList = $this->get_emailingStatusList();
    $this->contactSourceList = $this->get_contactSourceList();
    $this->contactGroupList = $this->get_contactGroupList(true);
    
    /* get form */
    $this->editform = new HTMLForm('edit_emailing',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_emailing')),
				   'POST');
		$this->editform->allow_files(true, 1024*1204);
    $this->editform->set_object($this->emailingItem);
    $this->editform->add_hidden('emailing_id', $this->emailingItem->id );
    $this->editform->add_hidden('status', $this->emailingItem->vars['status']);
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->emailingItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('emailingnew');
    else
      $this->adminTitle .= $this->get_translation('emailingid', $this->emailingItem->id);
     
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('openTab'=>'emailings')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_emailing.html.inc';
  }
  
  /* 
   * init module object in admin/save_emailing mode
   * @return void
   * @access private
   */
  function init_admin_save_emailing() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save object */
    $emailing_id = isset($_REQUEST['emailing_id'])?$_REQUEST['emailing_id']:0;    
    $this->emailingItem->id = $emailing_id;
    $this->emailingItem->get_fromHeader();
    if ( $this->emailingItem->save() ) {
      $this->text = $this->get_translation('emailing_saved');
    } else {
      $this->text = $this->get_translation('emailing_notsaved');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'emailings')));
  }
  
  /* 
   * init module object in admin/delete_emailing mode
   * @return void
   * @access private
   */
  function init_admin_delete_emailing() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed () ;
      
    /* check emailing id */
    if (!isset($_REQUEST['emailing_id']))
    	return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get object */
    $this->emailingItem->id = $_REQUEST['emailing_id'];
    
    /* delete object */
    if ( $this->emailingItem->delete() ) {
      $this->text = $this->get_translation('emailing_deleted');
    } else {
      $this->text = $this->get_translation('emailing_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'emailings')));
  }
  
  /* 
   * init module object in admin/reset_emailing mode
   * @return void
   * @access private
   */
  function init_admin_reset_emailing() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(4) === false )
      return $this->init_admin_actionNotAllowed () ;
      
    /* check emailing id */
    if (!isset($_REQUEST['emailing_id']))
    	return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get object */
    $this->emailingItem->id = $_REQUEST['emailing_id'];
    $this->emailingItem->get();
    $this->emailingItem->_libItems['status']->value = 0;
    
    /* delete object */
    if ( $this->emailingItem->save() ) {
      $this->text = $this->get_translation('emailing_reseted');
    } else {
      $this->text = $this->get_translation('emailing_notreseted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>$this->emailingItem->id)));
  }
  
  /*
   * init module object in admin/send_emailing mode
   * @return void
   * @access private
   */
  function init_admin_send_emailing() {
    global $camyks;
    
     /* check user rights */
    if ( $this->check_right(4) === false )
      return $this->init_admin_actionNotAllowed () ;
      
    /* check emailing id */
    if (!isset($_REQUEST['emailing_id']))
    	return $this->init_admin_main();
    	
    /* get object */
    $this->emailingItem->id = $_REQUEST['emailing_id'];
    $this->emailingItem->get();
    $this->emailingItem->get_fromItems();
    
    /* add javascripts */
    $this->add_JSEngineFile('tool/xml.js');
    $this->add_JSEngineFile('object/cajaxrequest.js');
    $this->add_JSFile('emailingengine.js');
    $this->add_JSScript('var ee = new EmailingEngine("ee");');
    $this->add_JSScript('ee.set_param("requestBaseURL", "'.$camyks->get_confValue('url').'/request.php?module='.$this->name.'&emailing_id='.$this->emailingItem->id.'");');
    $this->add_JSLoadScript('ee.initialise();');
    
    if ($this->emailingItem->vars['status'] == 0) {
    	$this->add_JSScript('ee.set_param("startAt", -1);');
    	$this->add_JSScript('ee.set_param("emailCount", -1);');
    } else {
    	$this->add_JSScript('ee.set_param("startAt", '.$this->emailingItem->config->vars['emailing_current'].');');
    	$this->add_JSScript('ee.set_param("emailCount", '.count($this->emailingItem->config->vars['emailing_list']).');');
    }
    $this->add_JSScript('ee.set_param("sendingInterval", '.($this->emailingItem->vars['advanced_sending_interval']*1000).');');
    
    /* add locales */
    $this->add_JSScript('ee.set_locale("continue_sending", "'.string_html2text($this->get_translation('continue_sending')).'");');
    $this->add_JSScript('ee.set_locale("initialise_emailing", "'.string_html2text($this->get_translation('initialise_emailing')).'");');
   	$this->add_JSScript('ee.set_locale("send_email", "'.string_html2text($this->get_translation('send_email')).'");');
    $this->add_JSScript('ee.set_locale("finalise_emailing", "'.string_html2text($this->get_translation('finalise_emailing')).'");');
    
   	/* update layout title */
   	$this->adminTitle = $this->title;
   	$this->adminTitle .= $camyks->get_translation('formitem_separator');
   	$this->adminTitle .= $this->get_translation('emailsending');
   
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>$this->emailingItem->id)),
				                 'title'=>$camyks->get_translation('back')));
    
    /* update layout */
    $this->selected_layout = 'admin_send_emailing.html.inc';
  }
  
  /*
   * init module object in admin/edit_contact mode
   * @return void
   * @access private
   */
  function init_admin_edit_contact() {
    global $camyks;
    
    /* check edit contact rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
      
    /* get help */
    $this->get_help();

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array('name'=>'properties',
				       'title'=>$this->get_translation('tabproperties')));
				       
	  if ( $this->help != null )
	    $this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
				     
    $this->tabBuilder->initialise(array('default'=>'properties'));
    
    /* get contact item */
    $contact_id = isset($_REQUEST['contact_id'])?$_REQUEST['contact_id']:0;
    $this->contactItem->id = $contact_id;
    $this->contactItem->get();
    $this->contactItem->get_fromItems();
    
    /* load data */
    $this->statusList = $this->get_contactStatusList();
    $this->contactGroupList = $this->get_contactGroupList(false, true);
    
    /* get form */
    $this->editform = new HTMLForm('edit_contact',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_contact')),
				   'POST');
    $this->editform->set_object($this->contactItem);
    $this->editform->add_hidden('contact_id', $this->contactItem->id );
    $this->editform->add_hidden('old_email', $this->contactItem->vars['email']);
    
    /* javascript */
    $this->add_JSFile('contacteditor.js');
    $this->add_JSScript('var ce = new ContactEditor("ce");');
    $this->add_JSLoadScript('ce.initialise();');
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->contactItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('contactnew');
    else
      $this->adminTitle .= $this->get_translation('contactid', $this->contactItem->id);
     
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_contact.html.inc';
  }
  
  /* 
   * init module object in admin/save_contact mode
   * @return void
   * @access private
   */
  function init_admin_save_contact() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save object */
    $contact_id = isset($_REQUEST['contact_id'])?$_REQUEST['contact_id']:0;    
    $this->contactItem->id = $contact_id;
    $this->contactItem->get_fromHeader();
    if ( $this->contactItem->save() ) {
      $this->text = $this->get_translation('contact_saved');
    } else {
      if (isset($this->contactItem->_libError))
        $this->text = $this->contactItem->_libError;
      else
        $this->text = $this->get_translation('contact_notsaved');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }
  
  /* 
   * init module object in admin/delete_contact mode
   * @return void
   * @access private
   */
  function init_admin_delete_contact() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed () ;
      
    /* check contact id */
    if (!isset($_REQUEST['contact_id']))
    	return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get object */
    $contact_id = $_REQUEST['contact_id'];
    $this->contactItem->id = $contact_id;
    
    /* delete object */
    if ( $this->contactItem->delete() ) {
      $this->text = $this->get_translation('contact_deleted');
    } else {
      $this->text = $this->get_translation('contact_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }
  
  /* 
   * init module object in admin/delete_email mode
   * @return void
   * @access private
   */
  function init_admin_delete_email() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed () ;
      
    /* check emailing id */
    if (!isset($_REQUEST['email_id']))
    	return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get object */
    $this->emailItem->id = $_REQUEST['email_id'];
    $this->emailItem->get();
    $this->emailItem->get_fromItems();
    $emailing = $this->emailItem->vars['emailing'];
    
    /* delete object */
    if ( $this->emailItem->delete() ) {
      $this->text = $this->get_translation('email_deleted');
    } else {
      $this->text = $this->get_translation('email_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>$emailing, 'openTab'=>'emails')));
  }
  
  /* 
   * init module object in admin/mark_email mode
   * @return void
   * @access private
   */
  function init_admin_mark_email() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed () ;
      
    /* check emailing id */
    if (!isset($_REQUEST['email_id']))
    	return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get object */
    $this->emailItem->id = $_REQUEST['email_id'];
    $this->emailItem->get();
    $this->emailItem->get_fromItems();
    $emailing = $this->emailItem->vars['emailing'];
    
    /* delete object */
    if ( $this->emailItem->mark_asInvalid() ) {
      $this->text = $this->get_translation('email_markedasinvalid');
      
      /* update contact status */
      $this->mark_contactAsInvalid($this->emailItem->vars['contact'], $this->emailItem->vars['source']);
      
    } else {
      $this->text = $this->get_translation('email_notmarkedasinvalid');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>$emailing, 'openTab'=>'emails')));
  }
  
  /* 
   * init module object in admin/import_contactsPrepare mode
   * @return void
   * @access private
   */
  function init_admin_import_contactsPrepare() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed() ;
      
    /* get form */
    $this->importform = new HTMLForm('import_contact',
				   $camyks->get_adminlink( $this->name, array('mode'=>'import_contactsCheckAndConfigure')),
				   'POST');
    $this->importform->allow_files($this->maxFileSize * 1024 *1024);
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('contacstimport');
     
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
				 array('link'=>$this->importform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('continue')));
    
    /* update layout */
    $this->selected_layout = 'admin_import_contactsPrepare.html.inc';
  }
  
  /* 
   * init module object in admin/import_contactsCheckAndConfigure mode
   * @return void
   * @access private
   */
  function init_admin_import_contactsCheckAndConfigure() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    $this->uploadResult = false;
     
    /* load file */  
    if (isset( $_FILES['file'] ) and $_FILES['file']['name'] != '') {
      folder_completePath($this->get_varFilePath().'Importations');
      
      /* get file extension */
      if ( preg_match( '/.*\.([^\.]*)/', $_FILES['file']['name'], $ext ) ) 
		$ext = '.'.$ext[1];
      else
		$ext = '';
      
      $file = strftime('%F-%H-%M-%S'.$ext);
      $path = $this->get_varFilePath().'Importations/'.$file;
      if (move_uploaded_file($_FILES['file']['tmp_name'], $path)) {
        /* load library */
        require_once 'Spreadsheet/Excel/Reader.php';
        
        /* load file */
        $this->xlsFile = new Spreadsheet_Excel_Reader($path);
      }
    }
    
    $this->importContactFieldList = array(
        'none' => $this->get_translation('none'),
        'status' => $this->get_translation('status'),
        'lastname' => $camyks->get_translation('lastname'),
        'firstname' => $camyks->get_translation('firstname'),
        'email' => $camyks->get_translation('email'),
        'group' => $this->get_translation('group'),
        'denomination' => $this->get_translation('denomination'),
    );
      
    /* get form */
    $this->importform = new HTMLForm('import_contact',
				   $camyks->get_adminlink( $this->name, array('mode'=>'import_contactsExecute')),
				   'POST');
    $this->importform->add_hidden('import_file', $file);
	$this->importform->add_hidden('colcount', $this->xlsFile->colcount());
	$this->importform->add_hidden('rowcount', $this->xlsFile->rowcount());
    
    /* build scripts */
    $this->add_JSFile('importcontactconfigure.js');
    $this->add_JSScript('var icc = new ImportContactConfiguration("icc");');
    $this->add_JSScript('icc.set_param("form", "'.$this->importform->name.'");');
    $this->add_JSLoadScript('icc.initialise();');
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('contacstimport');
     
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('mode'=>'import_contactsPrepare')),
				 'title'=>$camyks->get_translation('back')),
				 array('link'=>$this->importform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('continue')));
    
    /* update layout */
    $this->selected_layout = 'admin_import_contactsCheckAndConfigure.html.inc';
  }
  
  /* 
   * init module object in admin/import_contactsExecute mode
   * @return void
   * @access private
   */
  function init_admin_import_contactsExecute() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* get data from headers */
    $data = $_REQUEST;
    
    /* build default  */
    $this->config = new Admin_GenericEmailingManagerContactsImportConfig('contactsImport', $this);
    $this->config->initialise();
    $this->config->vars['import_file'] = $data['import_file'];
    $this->config->vars['first_line'] = $data['loadfromline'];
    $this->config->vars['import_current'] = 0;
    $this->config->vars['row_count'] = $data['rowcount'];
    $this->config->vars['col_count'] = $data['colcount'];
    $this->config->vars['cols_params'] = array();
    for($i=1; $i<$data['colcount']+1; $i++) {
      $this->config->vars['cols_params']['col'.$i.'_field'] = $data['col'.$i.'_field'];
      if ($data['col'.$i.'_field'] == 'status') {
        $this->config->vars['cols_params']['col'.$i.'_status'] = array();
        foreach ($this->contactItem->get_statusList() as $id => $name)
          if ($data['col'.$i.'_status'.$id] != '')
            $this->config->vars['cols_params']['col'.$i.'_status'][$data['col'.$i.'_status'.$id]] = $id;
      }
    }
    $this->config->save();
    
    /* add javascripts */
    $this->add_JSEngineFile('tool/xml.js');
    $this->add_JSEngineFile('object/cajaxrequest.js');
    $this->add_JSFile('importcontactengine.js');
    $this->add_JSScript('var ice = new ImportContactEngine("ice");');
    $this->add_JSScript('ice.set_param("requestBaseURL", "'.$camyks->get_confValue('url').'/request.php?module='.$this->name.'");');
    $this->add_JSLoadScript('ice.initialise();');
    
   	$this->add_JSScript('ice.set_param("startAt", -1);');
   	$this->add_JSScript('ice.set_param("contactCount", '.($data['rowcount']-$data['loadfromline']+1).');');
    
    /* add locales */
    //$this->add_JSScript('ice.set_locale("continue_sending", "'.string_html2text($this->get_translation('continue_sending')).'");');
    $this->add_JSScript('ice.set_locale("initialise_importation", "'.string_html2text($this->get_translation('initialise_importation')).'");');
   	$this->add_JSScript('ice.set_locale("import_contact", "'.string_html2text($this->get_translation('import_contact')).'");');
    $this->add_JSScript('ice.set_locale("finalise_importation", "'.string_html2text($this->get_translation('finalise_importation')).'");');
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('contacstimport');
     
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('mode'=>'import_contactsPrepare')),
				 'title'=>$camyks->get_translation('back')));
    
    /* update layout */
    $this->selected_layout = 'admin_import_contactsExecute.html.inc';
  }
  
  /* specific request mode methods */
  
  /*
   * execute module object in request / preview mode
   * @param array $params
   * @return void
   * @access private
   */
  function execute_request_previewEmailing($params=null) {
    global $camyks;
    
    /* load site context */
    $camyks->get_adminInit();

    if ($params !== null)
        $eId = $params[0];
    else if (isset($_REQUEST['emailing_id']))
        $eId = (int)$_REQUEST['emailing_id'];
    else
        return false;
    
    if ($params !== null and $params[1] == 'direct')
        $linkMode = 'direct';
    else if (isset($_REQUEST['link_mode']))
        $linkMode = $_REQUEST['link_mode'];
    else
        $linkMode = 'redirect';
    
    /* load emailing */
    $this->emailingItem->id = $eId;
    $this->emailingItem->get();
    $this->emailingItem->get_fromItems();
    
    /* load random contact */
    $this->contactItem->id = 1;
    $this->contactItem->get();
    $this->contactItem->get_fromItems();
              
    /* build email params */
    if ($params !== null)
      $params = array_merge($params, $this->contactItem->get_itemsAsMailParams());
    else
      $params = $this->contactItem->get_itemsAsMailParams();
    $params['image_path'] = $this->emailingItem->get_imageFolderURL().'/';
    
    if ($linkMode == 'redirect') 
        $params['link_([0-9]*)'] = $camyks->get_confValue('url').'/emailing-link-'.$this->emailingItem->id.'-test-$1.gnl';
    else {
        $this->emailingItem->load_config();
        foreach ($this->emailingItem->config->vars['content_links'] as $id => $link)
            $params['link_'.$id] = $link;
    }
    
    $params['opened_img'] = $this->get_fileURL('img/blank.gif', true);
    
    /* send emailing file */
    die($this->emailingItem->get_emailContent($params));
  }
  
  /*
   * execute module object in request / unsubscribe mode 
   * @return void
   * @access private
   */
  function execute_request_unsubscribeContact($params) {
  	global $camyks;
  	
  	/* load site context */
    $camyks->get_siteInit();
  	
  	/* check email value */
    if (!isset($_REQUEST['email']))
    	die('Error : no email given');
    
    /* check contact id value */
    if (count($params) < 2)
    	die('Error : no contact id given');
    	
    /* get email id */
    $this->emailItem->id = $params[1];
    
    /* update email */
    if (!$this->emailItem->update_asUnsubscribed($params[0]))
      die('Error');
    
    /* get contact id */
    $this->contactItem->id = $this->emailItem->vars['contact'];
    
    $this->config->get();
    
    /* update contact */
    if ($this->contactItem->update_asUnsubscribed($_REQUEST['email'])) {
      header('Location:'.$camyks->get_siteLink($this->config->vars['unsubscribe_backpage']));
    } else {
      die('Error');
    }
  }
  
  /*
   * execute module object in request / export emailing results mode 
   * @return void
   * @access private
   */
  function execute_request_exportEmailingResults() {
  	global $camyks;
  	
  	/* load site context */
    $camyks->get_adminInit();
  	
  	/* check email value */
    if (!isset($_REQUEST['emailing']))
    	die('Error : no emailing given');
    
    /* load excel writer library */
	require_once('Spreadsheet/Excel/Writer.php');
    
    /* load emailing */
    $this->emailingItem->id = (int)$_REQUEST['emailing'];
    $this->emailingItem->get();
    $this->emailingItem->get_fromItems();
    
    /* load emailing emails */
    $emails = $this->emailItem->get_objectList(false, 'emailing='.$_REQUEST['emailing'], -1, -1, 'send_date', 'asc');
    
    /* get contact list */
	$sources = array();
	foreach ($emails as $email) {      
	  if (!isset($sources[$email->vars['source']]))
	    $sources[$email->vars['source']] = array();
	  $sources[$email->vars['source']][$email->vars['contact']] = '';
	}

	foreach ($sources as $source => &$contacts) {
	  $src = explode(':', $source);
      if ($src[0] == 'internal') {
        $l = $this->contactItem->get_fullNameList(array('ids'=>array_keys($contacts)));
      } elseif (isset($camyks->modules[$src[0]])) {
        $l = $camyks->modules[$src[0]]->get_emailingManagerContactTitleFromIds(array_keys($contacts), $src[1]);
      } else {
        $l = array();
      }
      foreach ($contacts as $id => &$title) {
        if (isset($l[$id]))
          $sources[$source][$id] = $l[$id];
      }
	}
	  	  
	foreach ($emails as $id => $email) {
	  if (isset($sources[$email->vars['source']][$email->vars['contact']]))
	    $emails[$id]->vars['title'] = $sources[$email->vars['source']][$email->vars['contact']];
	}
	
    
    /* Creating a workbook */
    $workbook = new Spreadsheet_Excel_Writer();

	/* sending HTTP headers */
	$workbook->send('Export_'.strftime('%Y-%m-%d').'.xls');

	/* Creating a worksheet */
	$worksheet =& $workbook->addWorksheet('E-Mailing');
		
	/* creates formats */
	$workbook->setCustomColor(16, 26, 97, 169);
	$header = &$workbook->addFormat();
	$header->setBold(700);
	$header->setColor(16);
		
	/* add title line */
	$c = 0;
	$worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('contact'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('sending'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('opening'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('firstclick'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('clicks'))), $header);
    
	/* The actual data */
	$l = 1;
	foreach ($emails as $email) {
		//$this->emailItem = &$email;
		$c = 0;
		/* add details cells */
		$worksheet->write($l, $c++, utf8_decode($email->vars['title']));
		$worksheet->write($l, $c++, $email->get_sentDateValue());
		$worksheet->write($l, $c++, $email->get_openedDateValue());
		$worksheet->write($l, $c++, $email->get_firstClickDateValue());
		$worksheet->write($l, $c++, $email->vars['click_count']);
		$l++;
	}
	/* close and send XLS file */
	$workbook->close();
  }
  
  /*
   * execute module object in request / export contact list mode 
   * @return void
   * @access private
   */
  function execute_request_exportContactList() {
  	global $camyks;
  	
  	/* load site context */
    $camyks->get_adminInit();
  	
    /* load excel writer library */
	require_once('Spreadsheet/Excel/Writer.php');
        
    /* load data */
    $contactCount = $this->contactItem->count();
    $status = $this->contactItem->get_statusList();
    //$categories = $this->get_contactCategoryList();
    $groups = $this->get_contactGroupList();
    
    /* Creating a workbook */
    $workbook = new Spreadsheet_Excel_Writer();

	/* sending HTTP headers */
	$workbook->send('Export-'.strftime('%Y-%m-%d').'.xls');

	/* Creating a worksheet */
	$worksheet =& $workbook->addWorksheet('Contacts');
		
	/* creates formats */
	$workbook->setCustomColor(16, 26, 97, 169);
	$header = &$workbook->addFormat();
	$header->setBold(700);
	$header->setColor(16);
		
	/* add title line */
	$c = 0;
	$worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('status'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('lastname'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('firstname'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('email'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('group'))), $header);
    
	/* load insert data block by block */
	$l = 1; // file line
	$blockLength = 1000; // contacts block length to optimise memory usage
	$blockCurrent = 0; // current block to run, to be updated in loop
	
	while (($blockCurrent + 1)*$blockLength < $contactCount) {
	  $contacts = $this->contactItem->get_objectList(false, '' , $blockCurrent*$blockLength, $blockLength, 'lastname', 'asc');
	  foreach ($contacts as $id => $contact) {
		$c = 0;
		/* add details cells */
		$worksheet->write($l, $c++, utf8_decode(string_html2text($status[$contact->vars['status']])));
		$worksheet->write($l, $c++, utf8_decode($contact->vars['lastname']));
		$worksheet->write($l, $c++, utf8_decode($contact->vars['firstname']));
		$worksheet->write($l, $c++, $contact->vars['email']);
		$worksheet->write($l, $c++, isset($groups[$contact->vars['group']]) ? utf8_decode($groups[$contact->vars['group']]) : '' );
		$l++;
	  }
	  $blockCurrent++;
	}
	
	/* send workbook */
	$workbook->close();
  }
  
  /*
   * execute module object in request / send_emailingInitialise mode
   * @return void
   * @access private
   */
  function execute_request_sendEmailingInitialise() {
    global $camyks;
    
    /* load site context */
    $camyks->get_adminInit();
    
    /* init result */
    $result = array('result'=>'failure', 'step'=>1);
    
    /* check emailing id */
    if (!isset($_REQUEST['emailing_id']))
    	return $result;
    
    /* load emailing */
    $this->emailingItem->id = $_REQUEST['emailing_id'];
    $this->emailingItem->get();
    $this->emailingItem->get_fromItems();
    
    $source = explode(':', $this->emailingItem->vars['contact_source']);
    if ($source[0] == 'internal') {
      /* load contact list */
      $contactList = $this->get_contactIdList(array(
        'status' => $source[1],
    	'group' => $this->emailingItem->vars['contact_group'],
      ));
    } elseif ( isset($camyks->modules[$source[0]])) {
      $contactList = $camyks->modules[$source[0]]->get_emailingManagerContactList($source[1]);
    } else {
      $contactList = array();
    }
      	
    /* add list to  */
    $this->emailingItem->config->vars['emailing_list'] = array();
    foreach ($contactList as $c)
      $this->emailingItem->config->vars['emailing_list'][] = array('contactid'=>$c, 'status'=>0);
    $this->emailingItem->config->save();
    
    /* update emailing status */
    $this->emailingItem->_libItems['status']->value = 1;
    $this->emailingItem->_libItems['sdate']->value = time();
    $this->emailingItem->update_databaseSpecificItems(array('status', 'sdate'));
    
    $result['result'] = 'success';
    $result['count'] = count($contactList);
    $result['message'] = $this->get_translation('initialise_emailing_done');
    $result['message2'] = $this->get_translation('emailstobesent', count($contactList));
      
    /* send XML */
    header("Content-type: text/xml");
    echo xml_serialize2XML($result);
    die();
  }
  
  /*
   * execute module object in request / send_emailingExecute mode
   * @return void
   * @access private
   */
  function execute_request_sendEmailingExecute() {
    global $camyks;
    
    /* load site context */
    $camyks->get_adminInit();
    
    /* init result */
    $result = array('result'=>'failure', 'step'=>2);
    
    /* check emailing id */
    if (!isset($_REQUEST['emailing_id']))
    	return $result;
    
    /* check object to execute */
    if (!isset($_REQUEST['obj']))
    	return $result;
    
    $current = (int)$_REQUEST['obj'];
    
    /* load emailing */
    $this->emailingItem->id = $_REQUEST['emailing_id'];
    $this->emailingItem->get();
    $this->emailingItem->get_fromItems();
    
    /* load contact */
    $source = explode(':', $this->emailingItem->vars['contact_source']);
    if ($source[0] == 'internal') {
      $this->contactItem->id = $this->emailingItem->config->vars['emailing_list'][$current]['contactid'];
      $this->contactItem->get();
      $this->contactItem->get_fromItems();
      
    } elseif (isset($camyks->modules[$source[0]])) {
      $this->contactItem->id = $this->emailingItem->config->vars['emailing_list'][$current]['contactid'];      
      $this->contactItem->get_fromArray($camyks->modules[$source[0]]->get_emailingManagerContactInfo($this->contactItem->id, $source[1]));
      $this->contactItem->get_fromItems();
    } else {
      /* what to do ? */
    }
    
    /* create new email */
    $this->emailItem->initialise();
    $this->emailItem->_libItems['emailing']->value = $this->emailingItem->id;
    $this->emailItem->_libItems['source']->value = $this->emailingItem->vars['contact_source'];
    $this->emailItem->_libItems['contact']->value = $this->contactItem->id;
    $this->emailItem->save();
            
    /* initialise e-mail object */
  	$mail = new CMail();
  	
  	/* check and set return path */
  	if ($this->emailingItem->vars['advanced_envelope_email'] != '')
  	  $mail->set_returnPath($this->emailingItem->vars['advanced_envelope_email']);

    /* set mail sender */
    $mail->set_sender($this->emailingItem->vars['sender_email'], $this->emailingItem->vars['sender_name']);
    
    /* set mail reply to */
    $mail->add_replyTo($this->emailingItem->vars['replyto_email'], $this->emailingItem->vars['replyto_name']);
    
    /* set mail recipient */
    $mail->add_recipient($this->contactItem->vars['email'], $this->contactItem->get_fullName());
        
    /* set mail content */
    $mail->set_subject(utf8_decode($this->emailingItem->vars['email_title']));
    $mail->set_textBody('');
      
    $params = $this->contactItem->get_itemsAsMailParams();
    $params['image_path'] = $this->emailingItem->get_imageFolderPath().'/';
    $params['unsubscribe_link'] = $camyks->get_confValue('url').'/emailing-unsubscribe-'.$this->emailingItem->id.'-'.$this->emailItem->id.'.gnl?email='.$this->contactItem->vars['email'];
    $params['link_([0-9]*)'] = $camyks->get_confValue('url').'/emailing-link-'.$this->emailingItem->id.'-'.$this->emailItem->id.'-$1.gnl';
    $params['opened_img'] = $camyks->get_confValue('url').'/emailing-check-'.$this->emailingItem->id.'-'.$this->emailItem->id.'.gnl';

    /* check and set List-Unsubscribe link */
    if ( $this->emailingItem->vars['advanced_include_listunsub'] == 1 ) {
      if ($this->emailingItem->vars['advanced_envelope_email'] != '')
        $e = $this->emailingItem->vars['advanced_envelope_email'];
      elseif ($this->emailingItem->vars['replyto_email'] != '')
        $e = $this->emailingItem->vars['replyto_email'];
      elseif ($this->emailingItem->vars['sender_email'] != '')
        $e = $this->emailingItem->vars['sender_email'];
      $mail->add_header('List-Unsubscribe', '<mailto:'.$e.'>, <'.$params['unsubscribe_link'].'>');
    }

    $mail->set_HTMLBody($this->emailingItem->get_emailContent($params));
    
    /* attach embed images */                   
    $i=0;
    while (isset($this->emailingItem->vars['email_contentimage'.$i])) {
    	$mail->add_embeddedImage($this->emailingItem->vars['email_contentimage'.$i]);
    	$i++;
    }

    $name = $this->contactItem->get_fullName();
    if ($name == '')
      $name = $this->contactItem->vars['email'];
    else
      $name .= '('.$this->contactItem->vars['email'].')';

    /* send email */
    if($mail->send()) {
    	$result['result'] = 'success';
    	$result['message'] = $this->get_translation('send_email_done', htmlentities($name)); 
    
        /* update email */
        $this->emailItem->_libItems['sent_status']->value = 1;
        $this->emailItem->_libItems['sent_date']->value = time();
        $this->emailItem->save();
    } else {
        $result['message'] = $this->get_translation('send_email_failure', htmlentities($name));
        $result['error'] = isset($mail->error)?$mail->error:'Undefined';
    }
    
    /* update config */
    $this->emailingItem->config->vars['emailing_current'] = $current;
    $this->emailingItem->config->vars['emailing_list'][$current]['status'] = 1;
    $this->emailingItem->config->save();
    
    /* send XML */
    header("Content-type: text/xml");
    echo xml_serialize2XML($result);
    die();
  }
  
  /*
   * execute module object in request / send_emailingFinalise mode
   * @return void
   * @access private
   */
  function execute_request_sendEmailingFinalise() {
    global $camyks;
    
    /* load site context */
    $camyks->get_adminInit();
    
    /* init result */
    $result = array('result'=>'failure', 'step'=>3);
    
    /* check emailing id */
    if (!isset($_REQUEST['emailing_id']))
    	return $result;
    
    /* load emailing */
    $this->emailingItem->id = $_REQUEST['emailing_id'];
    $this->emailingItem->get();
    $this->emailingItem->get_fromItems();
    
    /* update emailing status */
    $this->emailingItem->_libItems['status']->value = 2;
    $this->emailingItem->_libItems['edate']->value = time();
    $this->emailingItem->update_databaseSpecificItems(array('status', 'edate'));
    
    $result['result'] = 'success';
    $result['message'] = $this->get_translation('finalise_emailing_done');
      
    /* send XML */
    header("Content-type: text/xml");
    echo xml_serialize2XML($result);
    die();
  }
  
  /*
   * execute module object in request / setEmailAsOpened mode
   * @param array $params
   * @return void
   * @access private
   */
  function execute_request_setEmailAsOpened($params) {
    global $camyks;
            
    /* load camyks */
    $camyks->get_siteInit();

    /* load blank img */
    $f = new FSFile($this->get_filePath('img/blank.gif'));

    /* check params number */
    if (count($params) != 2)
       $f->send();
    $emailing = $params[0];
    $email = $params[1];
    
    /* check for test values */
    if ($email == 'test')
        $f->send();
        
    $this->emailItem->id = (int)$email;
    $this->emailItem->get();
    $this->emailItem->get_fromItems();
    
    /* check emailing value */
    if ((int)$emailing == $this->emailItem->vars['emailing']
        and $this->emailItem->vars['opened_status'] == 0) {
        $this->emailItem->_libItems['opened_status']->value = 1;
        $this->emailItem->_libItems['opened_date']->value = time();
        $this->emailItem->save();
    }
    
    /* send image */
    $f->send();
  }
  
  /*
   * execute module object in request / openEmailLink mode
   * @param array $params
   * @return void
   * @access private
   */
  function execute_request_openEmailLink($params) {
    global $camyks;
        
    /* load camyks */
    $camyks->get_siteInit();
    
    /* load blank img */
    $f = new FSFile($this->get_filePath('img/blank.gif'));
    
    /* check params number */
    if (count($params) != 3)
       header('Location: '.$camyks->get_confValue('url').'/');
    $emailing = $params[0];
    $email = $params[1];
    $link = $params[2];
    
    /* check for test values */
    if ($email != 'test') {
        /* load email */
        $this->emailItem->id = (int)$email;
        if ($this->emailItem->get()) {
          $this->emailItem->get_fromItems();
          if ((int)$emailing == $this->emailItem->vars['emailing']) {
            if ($this->emailItem->vars['opened_status'] == 0) {
                $this->emailItem->_libItems['opened_status']->value = 1;
                $this->emailItem->_libItems['opened_date']->value = time();
            }
            if ($this->emailItem->vars['firstclick_date'] == 0)
                $this->emailItem->_libItems['firstclick_date']->value = time();
            $this->emailItem->_libItems['click_count']->value++;
            $this->emailItem->save();
          }
        }
    }
    
    /* load emailing */
    $this->emailingItem->id = (int)$emailing;
    if (!$this->emailingItem->get())
      header('Location: '.$camyks->get_confValue('url').'');
    $this->emailingItem->load_config();
    
    /* redirect visitor to the good page */
    if (isset($this->emailingItem->config->vars['content_links'][$link])) {
        header('Location: '.$this->emailingItem->config->vars['content_links'][$link]);
    } else {
        /* send default link */
        header('Location: '.$camyks->get_confValue('url').'');
    }
  }
  
  /*
   * execute module object in request / import_contactInitialise mode
   * @return void
   * @access private
   */
  function execute_request_importContactInitialise() {
    global $camyks;
    
    /* load site context */
    $camyks->get_adminInit();
    
    /* init result */
    $result = array('result'=>'failure', 'step'=>1);
    
    $this->config = new Admin_GenericEmailingManagerContactsImportConfig('contactsImport', $this);
    $this->config->get();
  
    /* build result */
    $result['result'] = 'success';
    $result['count'] = $this->config->vars['row_count'];
    $result['message'] = $this->get_translation('initialise_importation_done');
    $result['message2'] = $this->get_translation('contactstobeimported', $this->config->vars['row_count']+1-$this->config->vars['first_line']);
      
    /* send XML */
    header("Content-type: text/xml");
    echo xml_serialize2XML($result);
    die();
  }
  
  /*
   * execute module object in request / import_contactExecute mode
   * @return void
   * @access private
   */
  function execute_request_importContactExecute() {
    global $camyks;
    
    /* load site context */
    $camyks->get_adminInit();
    
    /* init result */
    $result = array('result'=>'failure', 'step'=>2);
    
    /* check object to execute */
    if (!isset($_REQUEST['obj']))
    	return $result;
    
    $current = (int)$_REQUEST['obj'];
    
    /* load configuration */
    $this->config = new Admin_GenericEmailingManagerContactsImportConfig('contactsImport', $this);
    $this->config->get();
    
    /* load XLS file */
    $path = $this->get_varFilePath().'Importations/'.$this->config->vars['import_file'];
    require_once 'Spreadsheet/Excel/Reader.php';
    $this->xlsFile = new Spreadsheet_Excel_Reader($path);
    
    /* build line to read */
    $line = $this->config->vars['first_line'] + $current;
    
    /* build contact to save */
    $this->contactItem->id = 0;
    $this->contactItem->initialise();
    $this->contactItem->_libItems['status']->value = 1;
    
    for ($i=1; $i<$this->config->vars['col_count']+1; $i++) {
        if ($this->config->vars['cols_params']['col'.$i.'_field'] === 'none')
          continue;
        if ($this->config->vars['cols_params']['col'.$i.'_field'] == 'status') {
           if ( isset($this->config->vars['cols_params']['col'.$i.'_status']) and $this->config->vars['cols_params']['col'.$i.'_status'][$this->xlsFile->value($line, $i)] >= 0 )
             $this->contactItem->_libItems['status']->value = $this->config->vars['cols_params']['col'.$i.'_status'][$this->xlsFile->value($line, $i)];
        } else {
           $this->contactItem->_libItems[$this->config->vars['cols_params']['col'.$i.'_field']]->value = $this->xlsFile->value($line, $i);
        }
    }
    $this->contactItem->get_fromItems();
    $name = $this->contactItem->get_fullName();
    if ($name == '')
      $name = $this->contactItem->vars['email'];
    else
      $name .= '('.$this->contactItem->vars['email'].')';
    $name = string_text2html($name);
    if ( $this->contactItem->save()) {
        $result['result'] = 'success';
    	$result['message'] = $this->get_translation('import_contact_done', $name); 
    } else {
        $result['message'] = $this->get_translation('import_contact_failure', $name);
        $result['error'] = $this->contactItem->_libError;
    }
    
    
    /* update config */
    $this->config->vars['import_current'] = $current+1;
    $this->config->save();
    
    /* send XML */
    header("Content-type: text/xml");
    echo xml_serialize2XML($result);
    die();
  }
  
  /*
   * execute module object in request / import_contactFinalise mode
   * @return void
   * @access private
   */
  function execute_request_importContactFinalise() {
    global $camyks;
    
    /* load site context */
    $camyks->get_adminInit();
    
    /* init result */
    $result = array('result'=>'failure', 'step'=>3);
    
    /* load configuration */
    $this->config = new Admin_GenericEmailingManagerContactsImportConfig('contactsImport', $this);
    $this->config->get();
    
    /* trash all old files  */
    folder_delete($this->get_varFilePath().'Importations');
    
    /* update result */
    $result['result'] = 'success';
    $result['message'] = $this->get_translation('finalise_importation_done');
      
    /* send XML */
    header("Content-type: text/xml");
    echo xml_serialize2XML($result);
    die();
  }
  
  /* data management & manipulation methods */
  
  /*
   * return emailing status list
   * @return array
   * @access public
   */
  function get_emailingStatusList() {
  	return $this->emailingItem->get_statusList();
  }
  
  /*
   * return emailings status list
   * @param boolean $more
   * @return array
   * @access public
   */
  function get_emailingsStatusList($more=false) {
  	return $this->emailingItem->get_multiStatusList($more);
  }
  
  /*
   * return emailing status icon list
   * @param boolean $more
   * @return array
   * @access public
   */
  function get_emailingStatusIconList($more=false) {
  	if (!isset($this->emailingStatusIconList))
  		$this->emailingStatusIconList = $this->emailingItem->get_statusIconList();
  	return $this->emailingStatusIconList;
  }
  
  /*
   * return emailing statistics summary
   * @param integer $emailing
   * @return array
   * @access private
   */
  function get_emailingStatisticsSummary($emailing) {
    return $this->emailItem->get_statisticsSummary($emailing);
  }
  
  /*
   * return contact status list
   * @return array
   * @access public
   */
  function get_contactStatusList() {
  	return $this->contactItem->get_statusList();
  }
  
  /*
   * return contacts status list
   * @param boolean $more
   * @return array
   * @access public
   */
  function get_contactsStatusList($more=false) {
  	return $this->contactItem->get_multiStatusList($more);
  }
  
  /*
   * return contact status icon list
   * @param boolean $more
   * @return array
   * @access public
   */
  function get_contactStatusIconList($more=false) {
  	if (!isset($this->contactStatusIconList))
  		$this->contactStatusIconList = $this->contactItem->get_statusIconList();
  	return $this->contactStatusIconList;
  }
  
  /*
   * return contact list
   * @param array $params
   * @return array
   * @access private
   */
  function get_contactList($params=array()) {
  	return $this->contactItem->get_list($params);
  }
  
  /*
   * return contact group list
   * @param boolean $all
   * @param boolean $other
   * @return array
   * @access private
   */
  function get_contactGroupList($all=false, $other=false) {
    return $this->contactItem->get_groupList($all, $other);
  }
  
  /*
   * return contact source list
   * @return array $params
   * @access private
   */
  function get_contactSourceList() {
    $this->load_registeredExtensions();
    $list = array('internal:1' => $this->get_translation('contactsource_internal'),
        'internal:99' => $this->get_translation('contactsource_internaltest'),);
    foreach ($this->extensions as $module) {
      $list = array_merge($list, $module->get_emailingManagerContactSourceList());
    }
    return $list;
  }
  
  /*
   * return contact count
   * @param array $params
   * @return array
   * @access private
   */
  function count_contacts($params=array()) {
  	return $this->contactItem->count($params);
  }
  
  /*
   * return contact id list
   * @param array $params
   * @return array
   * @access private
   */
  function get_contactIdList($params=array()) {
  	return $this->contactItem->get_idList($params);
  }
  
  /*
   * return contact email list
   * @param array $params
   * @return array
   * @access private
   */
  function get_contactEmailList($params=array()) {
  	return $this->contactItem->get_emailList($params);
  }
  
  /*
   * mark contact as invalid
   * @param integer $contactId
   * @param string $source
   * @return boolean success
   * @access private
   */
  function mark_contactAsInvalid($contactId, $source) {
    $source = explode(':', $source);    
    if ($source[0] == 'internal') {
      $this->contactItem->id = $contactId;
      return $this->contactItem->mark_asInvalid();
    }
  }
  
  /*
   * load site configuration
   * @return void
   * @access private
   */
  function load_configuration() {
    global $camyks;

    /* check configuration manager module */
    if(isset($camyks->modules['Admin_GenericSiteConfiguration']))
      $this->configManager = &$camyks->modules['Admin_GenericSiteConfiguration'];
    else
      $this->configManager = false;
  }

  /*
   * get config value
   * @param string $item
   * @return mixed
   * @access private
   */
  function get_configValue($item) {
    /* load configuration if needed */
    if (!isset($this->configManager))
      $this->load_configuration();

    /* check configuration manager */
    if ($this->configManager === false)
      return false;

    /* get configuration value */
    return $this->configManager->get_configValue($item);
  }
  
  /*
   * load extensions list
   * @return void
   * @access private
   */
  function load_registeredExtensions() {
    if (is_array($this->extensions))
        return;
    $this->extensions = $this->get_registeredExtensions();
  }
  
  /*
   * add contact information
   * @param array $params
   * @return boolean success
   */
  function add_contact($params=array()) {
    return $this->contactItem->add_object($params);
  }
}
?>