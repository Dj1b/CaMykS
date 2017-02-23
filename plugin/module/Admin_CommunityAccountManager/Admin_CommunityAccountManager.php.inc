<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Oct 2010
 * Last Modif Date  : Oct 2010
 * History :
 * * 10-10-28 : Initial files
 * 
 * Admin_CommunityAccountManager module
 */

class Admin_CommunityAccountManager extends Module {
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_CommunityAccountManager ( $path_type ) {
    parent::Module('Admin_CommunityAccountManager', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Community';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load plugin libaries */
    $this->libs[] = 'Admin_CommunityAccountManagerAccount.php.inc';
    $this->libs[] = 'Admin_CommunityAccountManagerConfig.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    //    $this->config = new Admin_CommunityAccountManagerConfig('config', $this);
    $this->accountItem = new Admin_CommunityAccountManagerAccount(0, $this);

    /* initialise plugin variables */
    $this->accountList = null;

    /* load extended dictionnary */
    $this->add_translation('data');
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->accountItem->install() and $this->config->install()
	    and parent::install());
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
    return $this->accountItem->is_installed();
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
			     'default'=> false);
    $this->rights[1] = array('name'=>'edit_accounts',
			     'title'=> $this->get_translation('edit_accounts'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'edit_config',
			     'title'=> $this->get_translation('edit_config'),
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

    /* get informations */
    $this->mode = (isset($_REQUEST['mode'])? $_REQUEST['mode']:'main' );
    
    switch ( $this->mode ) {
    case 'edit_account':
      /* mode == edit_account */
      $this->init_admin_edit_account();
      break;
    case 'save_account':
      /* mode == save_account */
      $this->init_admin_save_account();
      break;
    case 'delete_account':
      /* mode == delete_account */
      $this->init_admin_delete_account();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
    }
    
    /* generic Module init */
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
  function init_admin_main() {
    global $camyks;
    
    /* load list parameters*/
    $this->load_file('lib/Admin_CommunityAccountManagerAccountListParams.php.inc');

    /* initialise object list input */
    $this->listObject = &$camyks->inputs['AdminItemListViewer'];
    $this->listObject->set_params($this->accountListParams); 
    $this->listObject->initialise();

    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }

  /*
   * init module object in admin/edit_account mode
   * @return void
   * @access private
   */
  function init_admin_edit_account($load_account=true) {
    global $camyks;
    
    /* check edit rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    if ($load_account === true ) {
      /* get account item */
      $account_id = isset($_REQUEST['account_id'])?$_REQUEST['account_id']:0;
      $this->accountItem->id = $account_id;
      $this->accountItem->get();
    }
    $this->accountItem->get_fromItems();

    /* load site configuration */
    if ($this->load_configuration() === false )
      return;

    /* build tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(array('name'=>'admin',
					    'title'=>$this->get_translation('tabadmininfos')),
				      array('name'=>'personal',
					    'title'=>$this->get_translation('tabpersonalinfos'))));
    $this->tabBuilder->initialise();
    
    /* get form */
    $this->editform = new HTMLForm('edit_account',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_account')),
				   'POST');
    $this->editform->add_hidden('account_id', $this->accountItem->id );
    $this->editform->add_hidden('registrationdate', $this->accountItem->vars['registrationdate']);
    $this->editform->add_hidden('connectiondate', $this->accountItem->vars['connectiondate']);
    $this->editform->add_hidden('securecode', $this->accountItem->vars['securecode']);
    $this->editform->set_object($this->accountItem);

    /* add javascripts */
    $this->add_JSFile('accounteditor.js');
    $this->add_JSScript('var accountEditor = new AccountEditor("accountEditor", "'.$this->editform->name.'");');
    $this->add_JSLoadScript('accountEditor.initialise();');
    
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ( $this->accountItem->id == 0 )
      $this->adminTitle .= $this->get_translation('accountnew');
    else
      $this->adminTitle .= $this->get_translation('accountid', $this->accountItem->id);

    /* load country list */
    $this->countries = countries_getList();
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink($this->name),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_account.html.inc';
  }
  
  /*
   * init module object in admin/save_account mode
   * @return void
   * @access private
   */
  function init_admin_save_account() {
    global $camyks;
    
    /* check rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* load site configuration */
    if ($this->load_configuration() === false )
      return;
    
    /* check item id */
    if (!isset($_REQUEST['account_id']))
      return $this->init_admin_main();

    /* try to save item */
    $this->accountItem->id = $_REQUEST['account_id'];
    $this->accountItem->get_fromHeader();
    if ( $this->accountItem->save() ) {
      $this->text = $this->get_translation('account_saved');
    } else {
      return $this->init_admin_edit_account(false);
    }

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name));
  }
  
  /*
   * init module object in admin/delete_account mode
   * @return void
   * @access private
   */
  function init_admin_delete_account(){
    global $camyks;
    
    /* check rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* check item id */
    if (!isset($_REQUEST['account_id']))
      return $this->init_admin_main();

    /* try to save item */
    $this->accountItem->id = $_REQUEST['account_id'];
    if ( $this->accountItem->delete() ) {
      $this->text = $this->get_translation('account_deleted');
    } else {
      $this->text = $this->get_translation('account_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name));
  }
  
  /* specific tool methods */

  /*
   * return status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_accountsStatusList($full=false) {
    return $this->accountItem->get_multiStatusList($full);   
  }
  
  /*
   * return status list
   * @return array
   * @access private
   */
  function get_accountStatusList() {
    return $this->accountItem->get_statusList();   
  }

  /*
   * return types list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_accountsTypeList($full=false) {
    return $this->accountItem->get_multiTypeList($full); 
  }

  /*
   * return types list
   * @return array
   * @access private
   */
  function get_accountTypeList() {
    return $this->accountItem->get_typeList(); 
  }

  /*
   * return status img definition
   * @param string $status
   * @return string
   * @access public
   */
  function get_accountStatusIconList() {
    return array(0=>'<img src="'.$this->theme->get_pictURL('empty', 12, 'std').'" alt="" border="0" />',
      1=>'<img src="'.$this->theme->get_pictURL('valid', 12, 'std').'" alt="" border="0" />',
      2=>'<img src="'.$this->theme->get_pictURL('cross', 12, 'std').'" alt="" border="0" />');
  }

  /*
   * load visitor account
   * @return boolean success
   * @access public
   */
  function load_visitorAccount() {
    global $camyks;

    /* build current logged account */
    $this->currentAccount = new Admin_CommunityAccountManagerAccount(0, $this);

    if (isset($_REQUEST['action']) and $_REQUEST['action']=='disconnect') {
      /* try disconnect */
      $id=$camyks->get_sessionValue('accountid', 0);
      $this->currentAccount->id = 0;
      $this->currentAccount->get();
      $this->currentAccount->get_fromItems();
      $this->currentAccount->save_toSession();
      if ($id > 0 )
      return false;
    } elseif (($id=$camyks->get_sessionValue('accountid', 0)) == 0 ) {
      /* try to load account from header values */
       if (isset($_REQUEST['action']) and $_REQUEST['action']=='connect' 
         and $this->currentAccount->get_fromLoginForm()) {
	      $this->currentAccount->save_toSession();
	      return true;
      }
      
      /* try to load account from cookie */
      if ($this->currentAccount->get_fromLoginCookie()) {
	      $this->currentAccount->save_toSession();
	      return true;
      }
    }
     
    /* try to load account found in the current session */
    $this->currentAccount->id = $id;
    $this->currentAccount->get();
    $this->currentAccount->get_fromItems();
    if ( $this->currentAccount->id == 0 ) {
      $this->currentAccount->save_toSession();
      return false;
    }
    return true;
  }


  /*
   * return logged account
   * @return Admin_CommunityAccountManagerAccount object
   * @access public
   */
  function get_loggedAccount() {
    if(!isset($this->currentAccount))
      $this->load_visitorAccount();
    if ($this->currentAccount->id > 0)
      return $this->currentAccount;
    return false;
  }

  /*
   * return logged account id
   * @return integer
   * @access public
   */
  function get_loggedAccountId() {
    if(!isset($this->currentAccount))
      $this->load_visitorAccount();
    return $this->currentAccount->id;
  }

  /*
   * return account from its id
   * @param integer $id
   * @return Admin_CommunityAccountManagerAccount object
   * @access public
   */
  function get_accountById( $id=0 ) {
    $this->accountItem->id = $id;
    $this->accountItem->get();
    $this->accountItem->get_fromItems();
    return $this->accountItem;
  }
  
  /*
   * confirm account
   * @param integer $id
   * @param string $sec
   * @return boolean result
   * @access public
   */
  function confirm_account($id, $sec) {
    return $this->accountItem->confirm_registration($id, $sec);
  }
  
  
  /*
   * try to connect member from email login and password
   * @param string $login
   * @param string $pwd
   * @return array
   * @access public
   */
  function connect_member($email='', $pwd='') {
    global $camyks;
    if (($user = $this->accountItem->connect_member($email, $pwd))==false)
      return false;
     
    /* update statistics */
    $camyks->update_statistic('account_connection', $this->name, 'dated' );
    return $user;
  }
  
  /*
   * try to disconnect member
   * @return array
   * @access public
   */
  function disconnect_member() {
    return $this->accountItem->disconnect_member();
  }
  
  /*
   * load site configuration
   * @return void
   * @access private
   */
  function load_configuration() {
    global $camyks;

    /* check configuration manager module */
    if(isset($camyks->modules['Admin_CommunitySiteConfiguration']))
      $this->configManager = &$camyks->modules['Admin_CommunitySiteConfiguration'];
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
   * load additional dictionnary
   * @return void
   * @access public
   */
  function get_additionalDictionnary() {
    global $camyks;
    $this->add_translation('data');
  }
  
  /*
   * send confirmation email
   * @param string 
   * @return void                                                                   
   * @access private                                                                
   */
  function send_confirmationEmail() {
    global $camyks;
       
    $this->load_configuration();
    
    /* send visitor email */
    $vMail = array('to'=>$this->accountItem->vars['email'],
                   'from'=> $this->get_configValue('email_sender'),
                   'subject'=>string_html2Text($this->get_translation('email_confirmationsubject')),
                   'content'=>$this->get_confirmationEmailContent());
    if ( $this->get_configValue('email_replyto') != '')
        $vMail['Reply-To'] = $this->get_configValue('email_replyto');
    mail_sendHTMLMail($vMail);
  }
  
  /*
   * return confirmation email content
   * @return string                                                                 
   * @access private                                                                
   */
  function get_confirmationEmailContent() {
    global $camyks;
    /* load CSS */
    $css = $camyks->themes[$camyks->_conf['site_default_theme']]->get_filePath('email.css');

    /* build html page */
    ob_start();
    $page = new HTMLPage();
    $page->add_styleIncludedFile($css);
    $page->add_HTMLHeader();
    $this->load_file('html/email_confirm_'.$camyks->current_language.'.html.inc');
    $page->add_HTMLFooter();

    $c = ob_get_contents();
    ob_end_clean();
    
    return $c;
  }
}
?>