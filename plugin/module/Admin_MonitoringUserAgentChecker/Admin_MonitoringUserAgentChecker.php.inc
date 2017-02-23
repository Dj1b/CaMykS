<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Dec 2014
 * Last Modif Date	: Dec 2014
 * History :
 * * 12-19-14 : Initial files
 * 
 * Admin_MonitoringUserAgentChecker
 */
class Admin_MonitoringUserAgentChecker extends Module {
  /* variables */
  var $config;
  var $recordItem;
  var $recordList;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_MonitoringUserAgentChecker ( $path_type ) {
    global $camyks;
    parent::Module('Admin_MonitoringUserAgentChecker', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'monitoring';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Monitoring';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load plugin libraries */
    $this->libs[] = 'Admin_MonitoringUserAgentCheckerRecord.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->recordItem = new Admin_MonitoringUserAgentCheckerRecord(0, $this);

    /* initialise plugin variables */
    $this->recordList = null;
    
    /* save user agent */
    if ( $camyks->mode == CAMYKS_MODE_SITE and $camyks->get_sessionValue('UAChecker', 0) == 0) {
      $this->save_visit();
      $camyks->set_sessionValue('UAChecker', 1);
    }
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->recordItem->install() and parent::install());
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
    return $this->recordItem->is_installed();
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
			     'default'=>false);
  }
  
  /*
   * update description in control panel
   * @return void
   * @access private
   */
  function get_adminControlPanelAction ( ) {
    global $camyks;
    $n = $this->count_records(array('status'=>0));
    if ($n == 1)
      $camyks->trads['mod_admin_monitoringuseragentchecker_desc'] = $this->get_translation('desc1');
    elseif ($n > 1)
      $camyks->trads['mod_admin_monitoringuseragentchecker_desc'] = $this->get_translation('descx', $n);
  }
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();

    /* check dependencies */
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    if (!isset($camyks->inputs['AdminItemListViewer']))
      return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

    /* get informations */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'main' );
    
    /* build form */    
    $this->addform = new HTMLForm('edit_record',
    		$camyks->get_adminlink( $this->name, array('mode'=>'save_record')),
    		'POST');
    $this->addform->add_hidden('record_id', 0 );
    
    
    /* build popup buttons */
    $this->popupbuttons = array(array('title'=>$camyks->get_translation('close'),
    		'link'=>'javascript:adminengine_modalPopupClose(\'admin_genericuseragentmanager_addpopup\')'),
    		array('title'=>$camyks->get_translation('add'),
    				'link'=>$this->addform->get_HTMLSubmitLink()));
    
    switch ( $this->mode ) {
    	case 'edit_record':
    		/* mode == edit_record */
    		$this->init_admin_edit_record();
    		break;
	    case 'save_record':
	      	/* mode == save_record */
	      	$this->init_admin_save_record();
	      	break;
	    case 'delete_record':
	      	/* mode == delete_record */
	      	$this->init_admin_delete_record();
	      	break;
	    case 'view_record':
	      	/* mode == view_record */
	      	$this->init_admin_view_record();
	      	break;
	    case 'update_record':
	      	/* mode == update_record */
	      	$this->init_admin_update_record();
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
    
    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();
    
    /* build record tab */
    $this->load_file('lib/Admin_MonitoringUserAgentCheckerRecordListParams.php.inc');
    $this->listRecord = new AdminItemListViewer('camyks');
    $this->listRecord->set_params($this->recordListParams);
    $this->listRecord->initialise();
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    /* add records tab */
    $this->tabBuilder->add_tab(array('name'=>'records',
				     'title'=>$this->get_translation('tabrecords')));

    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'records'));
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }
  
  /*
   * init module object in admin/view record mode
   * @return void
   * @access private
   */
  function init_admin_view_record(){
  	global $camyks;
  
  	/* get record item */
  	$this->recordItem->id = isset($_REQUEST['record_id'])?(int)$_REQUEST['record_id']:0;;
  	$this->recordItem->get();
  	$this->recordItem->get_fromItems();

  	$this->uaInfos = client_getUAInfos($this->recordItem->vars['user_agent']);
  	$new_platform_type = $this->uaInfos['platform_type'];
  	  	
  	/* get form 1 -> Redefine type*/
  	$this->editform1 = new HTMLForm('update',
  			$camyks->get_adminlink( $this->name, array('mode'=>'update_record')),
  			'POST');
  	$this->editform1->add_hidden('record_id', $this->recordItem->id );
  	$this->editform1->add_hidden('cdate', $this->recordItem->vars['cdate'] );
  	$this->editform1->add_hidden('user_agent', $this->recordItem->vars['user_agent'] );
  	if($new_platform_type != '' && $this->recordItem->vars['platform_type'] != $new_platform_type)
  		$this->editform1->add_hidden('platform_type', $new_platform_type);
  	else
  		$this->editform1->add_hidden('platform_type', $this->recordItem->vars['platform_type']);
  	$this->editform1->add_hidden('fvisit', $this->recordItem->vars['fvisit'] );
  	$this->editform1->add_hidden('lvisit', $this->recordItem->vars['lvisit'] );
  	$this->editform1->add_hidden('nvisit', $this->recordItem->vars['nvisit'] );
  	$this->editform1->add_hidden('status', $this->recordItem->vars['status'] );
  	$this->editform1->set_object($this->recordItem);
  	
  	/* get form 2 -> EDIT Status*/
  	$this->editform2 = new HTMLForm('edit_status',
  			$camyks->get_adminlink( $this->name, array('mode'=>'update_record')),
  			'POST');
  	$this->editform2->add_hidden('record_id', $this->recordItem->id );
  	$this->editform2->add_hidden('cdate', $this->recordItem->vars['cdate'] );
  	$this->editform2->add_hidden('user_agent', $this->recordItem->vars['user_agent'] );
  	//Update platform_type
  	if($new_platform_type != '' && $this->recordItem->vars['platform_type'] != $new_platform_type)
  		$this->editform2->add_hidden('platform_type', $new_platform_type);
  	else
  		$this->editform2->add_hidden('platform_type', $this->recordItem->vars['platform_type']);
  	$this->editform2->add_hidden('fvisit', $this->recordItem->vars['fvisit'] );
  	$this->editform2->add_hidden('lvisit', $this->recordItem->vars['lvisit'] );
  	$this->editform2->add_hidden('nvisit', $this->recordItem->vars['nvisit'] );
  	//Change Status
  	if($this->recordItem->vars['status'])
  		$this->editform2->add_hidden('status', 0);
  	else
  		$this->editform2->add_hidden('status', 1);
  	$this->editform2->set_object($this->recordItem);
  	
  	/* get tabs */
  	$this->tabBuilder = &$camyks->inputs['TabBuilder'];
  	/* add records tab */
  	$this->tabBuilder->add_tab(array('name'=>'properties',
  			'title'=>$this->get_translation('tabproperties')));
  				
  	/* add help tab */
  	if ( $this->help != null )
  		$this->tabBuilder->add_tab(array('name'=>'help', 'title'=>$camyks->get_translation('help')));
  					
  	/* initialise tabs */
  	$this->tabBuilder->initialise(array('default'=>'records'));
  	
  	/* load data */
  	$this->recordPlatformFormats = $this->get_recordPlatformFormatList();
  
  	/* build title */
  	$this->adminTitle = $this->title;
  	$this->adminTitle .= $camyks->get_translation('formitem_separator');
  	if ($this->recordItem->id == 0 )
  		$this->adminTitle .= $this->get_translation('recordnew');
  	else
  		$this->adminTitle .= $this->get_translation('recordid', $this->recordItem->id);  	 
  	
  	/* build button list */
  	$this->buttons = array(
  			array('link'=>$this->get_adminLink(), 'title'=>$camyks->get_translation('back')),
  			array('link'=>$this->editform1->get_HTMLSubmitLink(), 'title'=>$camyks->get_translation('update')),
  	);
    if ($this->recordItem->vars['status'] == 0)
      $this->buttons[] = array('link'=>$this->editform2->get_HTMLSubmitLink(), 'title'=>$this->get_translation('edit_status'));
  
  	/* update layout */
  	if($this->recordItem->vars['platform_type'] == 'bot')
  		$this->selected_layout = 'admin_view_bot_user_agent.html.inc';
    elseif($this->recordItem->vars['platform_type'] == 'tool')
  		$this->selected_layout = 'admin_view_tool_user_agent.html.inc';
  	else
  		$this->selected_layout = 'admin_view_user_agent.html.inc';
  }
  
  /*
   * init module object in admin/edit_record mode
   * @return void
   * @access private
   */
  function init_admin_edit_record() {
  	global $camyks;
  
  	/* get record item */
  	$record_id = isset($_REQUEST['record_id'])?(int)$_REQUEST['record_id']:0;
  	$this->recordItem->id = $record_id;
  	$this->recordItem->get();
  	$this->recordItem->get_fromItems();
  
  	/* get form */
  	$this->editform = new HTMLForm('edit_record',
  			$camyks->get_adminlink( $this->name, array('mode'=>'save_record')),
  			'POST');
  	$this->editform->add_hidden('record_id', $this->recordItem->id );
  	$this->editform->add_hidden('cdate', $this->recordItem->vars['cdate'] );
  	$this->editform->add_hidden('platform_type', $this->recordItem->vars['platform_type'] );
  	$this->editform->add_hidden('fvisit', $this->recordItem->vars['fvisit'] );
  	$this->editform->add_hidden('lvisit', $this->recordItem->vars['lvisit'] );
  	$this->editform->add_hidden('nvisit', $this->recordItem->vars['nvisit'] );
  	$this->editform->set_object($this->recordItem);
  
  	/* get tabs */
  	$this->tabBuilder = &$camyks->inputs['TabBuilder'];
  	/* add records tab */
  	$this->tabBuilder->add_tab(array('name'=>'properties',
  			'title'=>$this->get_translation('tabproperties')));
  				
  	/* add help tab */
  	if ( $this->help != null )
  		$this->tabBuilder->add_tab(array('name'=>'help', 'title'=>$camyks->get_translation('help')));
  					
  	/* initialise tabs */
  	$this->tabBuilder->initialise(array('default'=>'records'));
  
  	/* build title */
  	$this->adminTitle = $this->title;
  	$this->adminTitle .= $camyks->get_translation('formitem_separator');
  	if ($this->recordItem->id == 0 )
  		$this->adminTitle .= $this->get_translation('recordnew');
  	else
  		$this->adminTitle .= $this->get_translation('recordid', $this->recordItem->id);
  
  	/* build button list */
  	$this->buttons = array(array('link'=>$this->get_adminLink(), 'title'=>$camyks->get_translation('back')),
  			array('link'=>$this->editform->get_HTMLSubmitLink(), 'title'=>$camyks->get_translation('valid')));
  
  	/* update layout */
  	$this->selected_layout = 'admin_edit_user_agent.html.inc';
  }
  
  /*
   * init module object in admin/save_record mode
   * @return void
   * @access private
   */
  function init_admin_save_record() {
    global $camyks;
        
    $_REQUEST['platform_type'] = 'other';
    if(isset($_REQUEST['user_agent']) && $_REQUEST['user_agent'] != ''){
    	$uaInfos = client_getUAInfos($_REQUEST['user_agent']);
    	if(isset($uaInfos['platform_type']) && $uaInfos['platform_type'] != '')
    		$_REQUEST['platform_type'] = $uaInfos['platform_type'];
    }
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* check record id */
    if (!isset($_REQUEST['record_id']))
      return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save record */
    $this->recordItem->id = (int)$_REQUEST['record_id'];
    $this->recordItem->get_fromHeader();
        
    /* verify duplicate */
    if($this->recordItem->count($_REQUEST) == 0){
    	if ( $this->recordItem->save() )
    		$this->text = $this->get_translation('record_saved');
    	else
    		$this->text = $this->get_translation('record_notsaved');
    } else
    	$this->text = $this->get_translation('record_duplicated');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('mode'=>'view_record', 'record_id'=>$this->recordItem->id)));
  }
  
  /*
   * init module object in admin/update_record mode
   * @return void
   * @access private
   */
  function init_admin_update_record(){
  	global $camyks;
  	
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* check record id */
    if (!isset($_REQUEST['record_id']))
      return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save record */
    $this->recordItem->id = (int)$_REQUEST['record_id'];
    $this->recordItem->get_fromHeader();
    
    if ( $this->recordItem->save() )
    	$this->text = $this->get_translation('record_updated');
    else
    	$this->text = $this->get_translation('record_notupdated');
  	
  	/* update layout */
  	$this->selected_layout = 'admin_message.html.inc';
  	$this->selected_layout_location = 'camyks';
  	$this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('mode'=>'view_record', 'record_id'=>$this->recordItem->id)));
  	 
  }
  
  /*
   * init module object in admin/delete_record mode
   * @return void
   * @access private
   */
  function init_admin_delete_record() {
  	global $camyks;
  
  	/* check user rights */
  	if ( $this->check_right(2) === false )
  		return $this->init_admin_actionNotAllowed () ;
  
  	/* check record id */
  	if ( !isset($_REQUEST['record_id']))
  		return $this->init_admin_main();
  	$record_id = (int)$_REQUEST['record_id'];
  
  	/* disable admin menu */
  	$this->disable_adminEngineMenus();
  
  	/* delete record */
  	$this->recordItem->id = $record_id;
  	if ( $this->recordItem->delete())
  		$this->text = $this->get_translation('record_deleted');
  	else
  		$this->text = $this->get_translation('record_notdeleted');
  
  	/* update layout */
  	$this->selected_layout = 'admin_message.html.inc';
  	$this->selected_layout_location = 'camyks';
  	$this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }
    
  /* specific tool methods */
  
  /*
   * update record with given 
   * @param string $ua
   * @return void
   * @access private
   */
  function save_visit($ua=null){
    global $camyks;
    
    /* define params */
    $params = array('user_agent'=>isset($ua)?$ua : $_SERVER['HTTP_USER_AGENT']);
    
    /* initialise new object */
    $this->recordItem->initialise();
    
    /* try to load from existing user agent */
    if ($this->recordItem->get_fromUserAgent($params['user_agent'])) {
      $this->recordItem->_libItems['nvisit']->value ++;
      $this->recordItem->_libItems['lvisit']->value = time();
    } else {
      $this->recordItem->_libItems['user_agent']->value = $params['user_agent'];
      $uaInfos = client_getUAInfos($params['user_agent']);
      if($uaInfos['platform_type'] != '')
        $this->recordItem->_libItems['platform_type']->value = $uaInfos['platform_type'];
      else
        $this->recordItem->_libItems['platform_type']->value = 'undefined';
    }
    return $this->recordItem->save();
  }
  
  /*
   * return records platform type list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_multiPlatformTypesList() {
  	return $this->recordItem->get_platformTypesList(true);
  }
  
  /*
   * return record plateform type list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_singlePlatformTypesList() {
    return $this->recordItem->get_platformTypesList(false);
  }
  
  /*
   * return record status list
   * @return array
   * @access private
   */
  function get_recordStatusList() {
  	return $this->recordItem->get_statusList();
  }
  
  /*
   * return record platform format list
   * @return array
   * @access private
   */
  function get_recordPlatformFormatList() {
    return $this->recordItem->get_platformFormatList();
  }
  
  /*
   * return record count
   * @param array $params
   * @return array
   * @access private
   */
  function count_records($params=array()) {
    return $this->recordItem->count($params);
  }
  
  /*
   * return record list
   * @param array $params
   * @return array
   * @access private
   */
  function list_records($params=array()) {
    return $this->recordItem->get_list($params);
  }
}
?>