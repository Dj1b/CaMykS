<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	        : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Jul 2017
 * Last Modif Date  : Jul 2017
 * History :
 * * 15-07-03 : Initial files
 * 
 * Admin_SystemNotifications
 */

class Admin_SystemNotifications extends Module {
  /* variables */
  var $websiteItem;
  var $websiteList;
   
  /*
   * constructor
   * @param string $path_type
   * @access public
   */
  public function Admin_SystemNotifications ( $path_type ) {
    parent::Module('Admin_SystemNotifications', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'monitoring';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load plugin libraries */
    $this->libs[] = 'Admin_SystemNotificationsWebsite.php.inc';
    $this->libs[] = 'Admin_SystemNotificationsConfig.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->websiteItem = new Admin_SystemNotificationsWebsite(0, $this);
    $this->config = new Admin_SystemNotificationsConfig('config', $this);


    /* initialise plugin variables */
    $this->websiteList = null;
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access public
   */
  public function install() {
    return ($this->websiteItem->install() and parent::install());
  }
  
  /*
   * unintall module
   * @return boolean success
   * @access public
   */
  public function uninstall() {
    return parent::uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access public
   */
  public function is_installed () {
    return $this->websiteItem->is_installed();
  }
  
  /*
   * get module rights
   * @return void
   * @access public
   */
  public function get_rights() {
    global $camyks;
    
    $this->rights[0] = array(
    	'name'=>'read',
		'title'=> $camyks->get_translation('read'),
		'default'=> false,
	);
	$this->rights[1] = array(
    	'name'=>'write',
		'title'=> $camyks->get_translation('write'),
		'default'=> false,
	);
  }
  
  /*
   * update description in control panel
   * @return void
   * @access private
   */
  function get_adminControlPanelAction ( ) {
    global $camyks;
    $this->config->get();
    if (date_isToday($this->config->vars['running_lastCheck']))
      $camyks->trads['mod_admin_systemnotifications_desc'] = $this->get_translation('descdate', strtolower($camyks->get_translation('today')));
    elseif (date_isYesterday($this->config->vars['running_lastCheck']))
      $camyks->trads['mod_admin_systemnotifications_desc'] = $this->get_translation('descdate', strtolower($camyks->get_translation('yesterday')));
    elseif ($this->config->vars['running_lastCheck'] > 0)
      $camyks->trads['mod_admin_systemnotifications_desc'] = $this->get_translation('descdatethe', date_displayLongDate($this->config->vars['running_lastCheck']));
  }
  
  /*
   * init module object in admin mode
   * @return void
   * @access public
   */
  public function init_admin () {
    global $camyks;

    /* check read rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();

    /* check dependencies */
    if (!isset($camyks->inputs['TabBuilder']))
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
    case 'edit_website':
      /* mode == edit_website */
      $this->init_admin_edit_website();
      break;
    case 'save_website':
      /* mode == save_website */
      $this->init_admin_save_website();
      break;
    case 'delete_website':
      /* mode == delete_website */
      $this->init_admin_delete_website();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
    }
    
    parent::init_admin();
  }
  
  /*
   * execute module object in request mode
   * @return void
   * @access private
   */
  public function execute_request() {
    global $camyks;
    
    /* build error message */
    $error = array(
        'title'=>$this->get_translation('requesterror_requestfailed'),
		'description'=>$this->get_translation('requesterror_undefinedaction'),
	);
    
    /* load mode to execute */
    $mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    
    /* execute mode */
    switch ($mode) {
      case 'loadNotifications':
        return $this->execute_request_loadNotifications();
      default :
	    /* throw fatal error */
	    $camyks->throwFatalError( $error );
    }    
  }

  /* specific admin mode methods */

  /*
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  private function init_admin_main() {
    global $camyks;    
    
    /* get help */
    $this->get_help();

    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();
    
    /* load current website modules data */
    $modules = array();
    foreach ($camyks->modules as $module)
      $modules = array_merge($modules, $module->get_adminInternalNotifications());
    
    /* initialise follow up list with current website */
    $this->followUpList = array(
      array(
      	'title' 	=> $camyks->get_confValue('site_title'),
      	'url'		=> $camyks->get_confValue('url'),
      	'modules'	=> $modules,
      	'error'     => '',
      ),
    );
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array(
    	'name'	=> 'FollowUp',
		'title'	=> $this->get_translation('tabfollowup'),
	));
	
	/* check for write rights */
	if ($this->check_right(1) == true) {
	
	  /* check for master mode */
	  if ($this->config->vars['module_mode'] == 1) {
	  
	    /* add website tab */
	    $this->tabBuilder->add_tab(array(
		  'name'	=> 'Websites',
          'title'	=> $this->get_translation('websites'),
	    ));
	  
	    /* build websites tab */
    	$this->load_file('lib/Admin_SystemNotificationsWebsiteListParams.php.inc');
    	$this->websiteList = &$camyks->inputs['AdminItemListViewer'];
    	$this->websiteList->set_params($this->websiteListParams);
    	$this->websiteList->initialise();
	  }
	  
	  /* add configuration tab */
	  $this->tabBuilder->add_tab(array(
		  'name'	=> 'Configuration',
          'title'	=> $this->get_translation('tabconfiguration'),
	  ));
	  
	  /* add configuration data */
	  $this->moduleModeList = $this->get_configurationModuleModeList();
	  $this->accessStatusList = $this->get_configurationAccessStatusList();
	  $this->accessAuthenticationList = $this->get_configurationAccessAuthenticationList();
	  $this->adminList = $this->get_adminUserList(array('addAll'=>true));
	}
	
	/* load all sites data if master mode */
	if ($this->config->vars['module_mode'] == 1) {
	
	  if ($this->config->vars['running_lastCheck'] + $this->config->vars['module_checkDelay']*60 < time()) {
	
	    /* load full website list */
	    $wsList = $this->get_websiteList(array('status'=>1));
	  
	    foreach ($wsList as $website) {
	    
	      /* build request */
	      $request = array(
	        'url' => $website->vars['baseURL'].'/'.$website->vars['pageURL'].'?module='.$this->name.'&mode=loadNotifications',
	      );
	  
	      /* check for post values */
	      if ($website->vars['login'] != '') {
	        $request['values'] = array('login' => $website->vars['login'], 'password' => $website->vars['password']);
	        $request['method'] = 'POST';
	      }
	    
	      /* execute request */
	      $result = http_getContents($request);

          /* check request result */
	      if ($result === false) continue;
	      $result = json_decode($result, true);
	      if (isset($result['data']))
	        $this->followUpList[] = $result['data'];
	      
	      /* update last check value */
	      $this->config->vars['running_lastCheck'] = time();
	      $this->config->vars['running_cache'] = $this->followUpList;
	      $this->config->save();
	    }
	  } else {
	    /* load from cache */
	    $this->followUpList = $this->config->vars['running_cache'];
	  }
	}
	
	/* finalise tabs */			     
	if ( $this->help != null )
	  $this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'FollowUp'));
    
    /* get buttons */
    $this->buttons = array(array(
        'link'	=> $camyks->get_adminLink(),
		'title'	=> $camyks->get_translation('back'),
	));
  }

  /*
   * init module object in admin/edit_config mode
   * @return void
   * @access private
   */
  private function init_admin_edit_config() {
    global $camyks;
    
    /* check admin write rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_accessDenied();
         
    /* get help */
    $this->get_help();
        
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array(
        'name'=>'Configuration',
		'title'=>$this->get_translation('tabconfiguration'))
    );
  
	if ( $this->help != null )
	 	$this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
	
    $this->tabBuilder->initialise(array('default'=>'Configuration'));
    
    /* load data */
    $this->moduleModeList = $this->get_configurationModuleModeList();
	$this->accessStatusList = $this->get_configurationAccessStatusList();
	$this->accessAuthenticationList = $this->get_configurationAccessAuthenticationList();
    $this->adminList = $this->get_adminUserList(array('addAll'=>true));
    
    /* build form */
    $this->editForm = new HTMLForm(
        'edit_config',
		$this->get_adminlink(array('mode'=>'save_config')),
		'POST');
    $this->editForm->set_object($this->config);
    $this->editForm->add_hidden('running_lastCheck', $this->config->vars['running_lastCheck']);
    
    /* add scripts */
    $this->add_JSFile('ConfigEditor.js');
    $this->add_JSScript('var ce = new ConfigEditor("ce");');
    $this->add_JSScript('ce.set_param("form", "'.$this->editForm->name.'");');
    $this->add_JSLoadScript('ce.initialise();');
     
    /* get buttons */
    $this->buttons = array(
      array(
        'link'=>$this->get_adminLink(array('openTab'=>'Configuration')),
		'title'=>$camyks->get_translation('back'),
	  ),
	  array(
	    'link'=>$this->editForm->get_HTMLSubmitLink(),
		'title'=>$camyks->get_translation('valid'),
	  ),
    );
    
    /* update layout */
    $this->selected_layout = 'admin_edit_config.html.inc';
  }
  
  /* 
   * init module object in admin/save_config mode
   * @return void
   * @access private
   */
  private function init_admin_save_config() {
    global $camyks;
    
    /* check admin write rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_accessDenied();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save config object */
    $this->config->get_fromHeader();
    if ( $this->config->save() ) {
      $this->text = $this->get_translation('config_saved');
    } else {
      $this->text = $this->get_translation('config_notsaved');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'Configuration')));
  }
  
  /*
   * init module object in admin/edit_website mode
   * @return void
   * @access private
   */
  private function init_admin_edit_website() {
    global $camyks;
    
    /* check admin write rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_accessDenied();
         
    /* get help */
    $this->get_help();
        
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array(
        'name'=>'Properties',
		'title'=>$this->get_translation('tabproperties'))
    );
  
	if ( $this->help != null )
	 	$this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
	
    $this->tabBuilder->initialise(array('default'=>'Properties'));
    
    /* load website object */
    $this->websiteItem->id = isset($_REQUEST['website_id'])?(int)$_REQUEST['website_id']:0;
    $this->websiteItem->get();
    $this->websiteItem->get_fromItems();
    
    /* build form */
    $this->editForm = new HTMLForm(
        'edit_website',
		$this->get_adminlink(array('mode'=>'save_website')),
		'POST');
    $this->editForm->set_object($this->websiteItem);
    $this->editForm->add_hidden('website_id', $this->websiteItem->id);
     
    /* get buttons */
    $this->buttons = array(
      array(
        'link'=>$this->get_adminLink(array('openTab'=>'Websites')),
		'title'=>$camyks->get_translation('back'),
	  ),
	  array(
	    'link'=>$this->editForm->get_HTMLSubmitLink(),
		'title'=>$camyks->get_translation('valid'),
	  ),
    );
    
    /* update layout */
    $this->selected_layout = 'admin_edit_website.html.inc';
  }
  
  /* 
   * init module object in admin/save_website mode
   * @return void
   * @access private
   */
  private function init_admin_save_website() {
    global $camyks;
    
    /* check admin write rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* save object */
    $this->websiteItem->id = isset($_REQUEST['website_id'])?(int)$_REQUEST['website_id']:0;
    $this->websiteItem->get_fromHeader();
    if ($this->websiteItem->save())
      $this->text = $this->get_translation('website_saved');
    else
      $this->text = $this->get_translation('website_notsaved');
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'Websites')));
  }
  
  /* 
   * init module object in admin/delete_website mode
   * @return void
   * @access private
   */
  private function init_admin_delete_website() {
    global $camyks;
    
    /* check admin write rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* delete object */
    $this->websiteItem->id = isset($_REQUEST['website_id'])?(int)$_REQUEST['website_id']:0;
    $this->websiteItem->get();
    $this->websiteItem->get_fromItems();
    if ($this->websiteItem->delete())
      $this->text = $this->get_translation('website_deleted');
    else
      $this->text = $this->get_translation('website_notdeleted');
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'Websites')));
  }
  
  /* request mode methods */
  
  /*
   * execute module object in request/load notifications mode
   * @return void
   * @access private
   */
  private function execute_request_loadNotifications() {
    global $camyks;
    
    /* initialise CaMykS in site mode */
    $camyks->get_siteInit();
    
    /* load configuration */
    $this->config->get();
    
    /* initialise answer */
    $answer = new CRequestAnswer();
    
    /* initialise follow up list with current website */
    $data = array(
        'title' 	=> $camyks->get_confValue('site_title'),
      	'url'		=> $camyks->get_confValue('url'),
      	'modules'	=> array(),
      	'error'     => '',
    );
    
    
    /* check service is enabled */
    if ($this->config->vars['access_status'] == 0) {
      $answer->set_asFailure();
      $data['error'] = $this->get_translation('requesterror_accessdisabled');
      $answer->update_param('data', $data);
      return $answer->send_asJSON();
    }
    
    /* check authentication with credentials */
    if ($this->config->vars['access_authentication'] == 1) {
      $login = isset($_REQUEST['login'])?$_REQUEST['login']:'';
      $password = isset($_REQUEST['password'])?$_REQUEST['password']:'';
      
      if ($this->config->vars['access_authLogin'] != '' and $login != $this->config->vars['access_authLogin']) {
        $answer->set_asFailure();
        $data['error'] = $this->get_translation('requesterror_authenticationfailed');
        $answer->update_param('data', $data);
        return $answer->send_asJSON();
      }
      
      $user = new AdminUser($login);
      if (!$user->can_login($password)) {
        $answer->set_asFailure();
        $data['error'] = $this->get_translation('requesterror_authenticationfailed');
        $answer->update_param('data', $data);
        return $answer->send_asJSON();
      }
    }
    
    /* check authentication with IP address */
    if ($this->config->vars['access_authentication'] == 2) {
      if ($this->config->vars['access_authIP'] == '' and !client_isServerClient()) {
        $answer->set_asFailure();
        $data['error'] = $this->get_translation('requesterror_authenticationfailed');
        $answer->update_param('data', $data);
        return $answer->send_asJSON();
      }
      
      if ($this->config->vars['access_authIP'] != '' and $this->config->vars['access_authIP'] != client_getIP()) {
        $answer->set_asFailure();
        $data['error'] = $this->get_translation('requesterror_authenticationfailed');
        $answer->update_param('data', $data);
        return $answer->send_asJSON();
      }
    }
    
    /* load current website modules data */
    $modules = array();
    foreach ($camyks->modules as $module)
      $modules = array_merge($modules, $module->get_adminInternalNotifications());
    $data['modules'] = $modules;
    
    /* send request result as success */    
    $answer->set_asSuccess();
    $answer->update_param('data', $data);
    return $answer->send_asJSON();
  }
  
  /* configuration specific methods */
  
  /* 
   * return configuration module mode list
   * @return array
   * @access private
   */
  private function get_configurationModuleModeList() {
    return $this->config->get_moduleModeList();
  }
  
  /* 
   * return configuration access status list
   * @return array
   * @access private
   */
  private function get_configurationAccessStatusList() {
    return $this->config->get_accessStatusList();
  }
  
  /* 
   * return configuration access authentication list
   * @return array
   * @access private
   */
  private function get_configurationAccessAuthenticationList() {
    return $this->config->get_accessAuthenticationList();
  }
  
  /* website specific management methods */

  /*
   * return single website list
   * @return array
   * @access public
   */
  public function get_websiteStatusList() {
	return $this->websiteItem->get_statusList();
  }

  /*
   * return websites status list
   * @param boolean $more
   * @return array
   * @access public
   */
  public function get_websitesStatusList($more=false) {
   	return $this->websiteItem->get_multiStatusList($more);
  }
  
  /*
   * return website count
   * @param array $params
   * @return integer
   * @access public
   */
  public function count_websites($params=array()) {
    return $this->websiteItem->count($params);
  }
  
  /*
   * return website list
   * @param array $params
   * @return array
   * @access public
   */
  public function get_websiteList($params=array()) {
    return $this->websiteItem->get_list($params);
  }
  
  /* specific tool methods */
  
  /*
   * return given config item value
   * @param string $item
   * @return mixed
   * @access private
   */
  public function get_configValue($item) {
    if (!isset($this->config->vars))
      $this->config->get();
    if (isset($this->config->vars[$item]))
      return $this->config->vars[$item];
    return false;
  }
  
  /*
   * return admin user list
   * @param params $params
   * @return array
   * @access private
   */
  private function get_adminUserList($params=array()) {
  	global $camyks;
  	
  	$defaultParams = array('addAll'=>false);
  	$params = array_merge($defaultParams, $params);
  	
  	$admins = $camyks->modules['Admin_User']->get_activeUserList(true);
    $menu = array();
   	if ($params['addAll'])
    	$menu[''] = $this->get_translation('credentials_all');
    foreach($admins as $admin)
    	$menu[$admin->login] = $admin->get_nameDisplay();
   	return $menu;
  }
}
?>