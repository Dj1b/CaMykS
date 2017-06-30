<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	        : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Jan 2015
 * Last Modif Date  : Jan 2015
 * History :
 * * 15-01-02 : Initial files
 * 
 * Admin_SystemUniqueIDManager
 */

class Admin_SystemUniqueIDManager extends Module {
  /* variables */
  var $uniqueIDItem;
  var $uniqueIDList;
   
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_SystemUniqueIDManager ( $path_type ) {
    parent::Module('Admin_SystemUniqueIDManager', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'configuration';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load plugin libraries */
    $this->libs[] = 'Admin_SystemUniqueIDManagerKey.php.inc';
    $this->libs[] = 'Admin_SystemUniqueIDManagerConfig.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->keyItem = new Admin_SystemUniqueIDManagerKey(0, $this);
    $this->config = new Admin_SystemUniqueIDManagerConfig('config', $this);


    /* initialise plugin variables */
    $this->keyList = null;
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ( $this->keyItem->install()
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
    return $this->keyItem->is_installed();
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
    case 'create_key':
      /* mode == create_key */
      $this->init_admin_create_key();
      break;
    case 'delete_key':
      /* mode == delete_key */
      $this->init_admin_delete_key();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
    }
    
    parent::init_admin();
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

    /* build uniqueID tab */
    $this->load_file('lib/Admin_SystemUniqueIDManagerKeyListParams.php.inc');
    $this->keyList = &$camyks->inputs['AdminItemListViewer'];
    $this->keyList->set_params($this->keyListParams);
    $this->keyList->initialise();
    
    /* load data */
    $this->generatingMethodList = $this->get_keyGeneratingMethodList();
    $this->totalGeneratedKeys = $this->count_keys();
    $this->freeGeneratedKeys = $this->count_keys(array('status'=>0));
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(
                   array('name'=>'Summary',
				     'title'=>$this->get_translation('formtitle_summary')),
                   array('name'=>'Keys',
				     'title'=>$this->get_translation('keys')),
    ));
				     
	if ( $this->help != null )
	  $this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'Keys'));
    
    /* get buttons */
    $this->buttons = array(array(
        'link'=>$camyks->get_adminLink(),
		'title'=>$camyks->get_translation('back'),
	));
  }

  /*
   * init module object in admin/edit_config mode
   * @return void
   * @access private
   */
  function init_admin_edit_config() {
    global $camyks;
         
    /* get help */
    $this->get_help();
        
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array(
        'name'=>'Configuration',
		'title'=>$this->get_translation('formtitle_configuration'))
    );
  
	if ( $this->help != null )
	 	$this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
	
    $this->tabBuilder->initialise(array('default'=>'Configuration'));
    
     /* load data */
    $this->generatingMethodList = $this->get_keyGeneratingMethodList();
    
    /* build form */
    $this->editform = new HTMLForm(
        'edit_config',
		$this->get_adminlink(array('mode'=>'save_config')),
		'POST');
    $this->editform->set_object($this->config);
     
    /* get buttons */
    $this->buttons = array(
      array(
        'link'=>$this->get_adminLink(),
		'title'=>$camyks->get_translation('back'),
	  ),
	  array(
	    'link'=>$this->editform->get_HTMLSubmitLink(),
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
  function init_admin_save_config() {
    global $camyks;

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
    $this->set_redirect($this->get_adminLink());
  }
  
  /* 
   * init module object in admin/create_key mode
   * @return void
   * @access private
   */
  function init_admin_create_key() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* delete object */
    $this->keyItem->initialise();
    if ( $this->keyItem->save() ) {
      $this->text = $this->get_translation('key_created');
    } else {
      $this->text = $this->get_translation('key_notcreated');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'uniqueIDs')));
  }
  
  /* 
   * init module object in admin/delete_key mode
   * @return void
   * @access private
   */
  function init_admin_delete_key() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* delete object */
    $this->keyItem->id = isset($_REQUEST['key_id'])?(int)$_REQUEST['key_id']:0;
    $this->keyItem->get();
    $this->keyItem->get_fromItems();
    if ($this->keyItem->is_deletable() and $this->keyItem->delete()) {
      $this->text = $this->get_translation('key_deleted');
    } else {
      $this->text = $this->get_translation('key_notdeleted');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'uniqueIDs')));
  }
  
  /* specific content management methods */

  /*
   * return single uniqueID list
   * @return array
   * @access public
   */
  function get_keyStatusList() {
	return $this->keyItem->get_statusList();
  }

  /*
   * return uniqueIDs status list
   * @param boolean $more
   * @return array
   * @access private
   */
  function get_keysStatusList($more=false) {
   	return $this->keyItem->get_multiStatusList($more);
  }
  
  /*
   * return unique ID generating method list
   * @return array
   * @access private
   */
  function get_keyGeneratingMethodList() {
    return $this->keyItem->get_generatingMethodList();
  }
  
  /*
   * return uniqueID count
   * @param array $params
   * @return integer
   * @access private
   */
  function count_keys($params=array()) {
    return $this->keyItem->count($params);
  }
  
  /*
   * return uniqueID list
   * @param array $params
   * @return array
   * @access private
   */
  function get_keyList($params=array()) {
    return $this->keyItem->get_list($params);
  }
  
  /* external request methods */
  
  /*
   * return new unique ID
   * @param string $plugin
   * @param string $object
   * @return mixed // unique ID on success, false on failure
   * @access public
   */
  function get_newUniqueID($plugin, $object) {
    if (!$this->keyItem->load_freeItem())
      $this->keyItem->initialise();
    $this->keyItem->_libItems['plugin']->value = $plugin;
    $this->keyItem->_libItems['object']->value = $object;
    if ($this->keyItem->save()) {
      $this->keyItem->get_fromItems();
      return $this->keyItem->vars['uniqueID'];
    }
    return false;
  }
  
  /*
   * return given config item value
   * @param string $item
   * @return mixed
   * @access private
   */
  function get_configValue($item) {
    if (!isset($this->config->vars))
      $this->config->get();
    if (isset($this->config->vars[$item]))
      return $this->config->vars[$item];
    return false;
  }
}
?>