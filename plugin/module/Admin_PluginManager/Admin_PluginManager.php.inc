<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Engine
 * Creation Date	: Jun 2005
 * Last Modif Date	: Oct 2017
 * History :
 * * 05-06-xx : Initial files
 * * 08-05-21 : Rewrite online help (french)
 * * 08-05-28 : Disable admin menu for data I/O modes
 * 
 * Admin_PluginManager module
 * Active and install plugin into the current website
 *
 * TO DO :
 * - action when a plugin folder is removed and plugin was active
 * - action when a plugin folder is removed and plugin was inactive
 * - plugin dependencies
 *
*/

class Admin_PluginManager extends Module {
  /* vars */
  var $mode;
  /* list vars */
  var $openTab;
  var $modules;
  var $templates;
  var $themes;
  var $inputs;
  var $pluginsinfo;
  /* action vars */
  var $plugin;
  var $type;
  var $activate;
  var $unfound;
  var $text;  
  
  /* generic plugin library values */
  var $_libIsInstalled;

  /* 
   * constructor
   * @param string $path_type
   */
  function Admin_PluginManager ( $path_type ) {
    parent::Module('Admin_PluginManager', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'configuration';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set author description */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load libraries */
    $this->libs[] = 'Admin_PluginManagerItem.php.inc';
    $this->get_PHPLibs();
    
    /* init library */
    $this->pluginItem = new Admin_PluginManagerItem(0, $this);
    
    /* init running vars */
    $this->installedTables = null;
  }
  
  /* overwrite Module methods */
  
  /*
   * install module object
   * @return boolean success
   * @access private
   */
  function install() {
    return ($this->pluginItem->install() and parent::install());
  }

  /*
   * uninstall module object
   * @return boolean success
   * @access private
   */
  function uninstall() {
    return false;
  }

  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed() {
    return $this->pluginItem->is_installed();
  }

  /*
   * add menu object
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenus( ) {
    if ( $this->check_right(1)===true ) {
      return array(array('name'=>'pluginmanager',
			 'title'=>$this->get_translation('title')));
    }
    return array();
  }

  /*
   * add menu items object
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenuItems( ) {
    global $camyks;
    if ( $this->check_right(1)===true ) {
      return array(array('name'=>'cleandatabase',
			 'title'=>$this->get_translation('cleandatabase'),
			 'icon'=>$this->get_fileURL('img/clean12.gif'),
			 'menu'=>'pluginmanager',
			 'url'=> $camyks->get_adminLink ( $this->name, array('mode'=>'cleandb'))));
    }
    return array();
  }

  /*
   * init object when in admin mode
   * @return void
   * @access private 
   */
  function init_admin () {
    global $camyks;

    /* check basic rights */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied();
    }

    /* get mode value */
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'list';

    /* build unfound module list */
    $this->unfound = array();
    
    /* execute mode */
    switch ( $this->mode ) {
    case 'activate':
      /* mode == activate */
      $this->init_admin_activate();
      break;
    case 'desactivate':
      /* mode == desactivate */
      $this->init_admin_desactivate();
      break;
    case 'setAsDefault':
      /* mode == setAsDefault */
      $this->init_admin_setAsDefault();
      break;
    case 'cleandb':
      /* mode == desactivate */
      $this->init_admin_cleandb();
      break;
    case 'list':
    default:
      /* mode == list */
      $this->init_admin_list();
      break;
    }
    /* generic module admin initialisation */
    parent::init_admin();
  }

  /* specific admin mode methods */

  /*
   * init module object in admin/activate mode
   * @return void
   * @access private
   */
  function init_admin_activate() {
    global $camyks;

    /* check admin rights */
    if ( $this->check_right(1)===false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menus */
    $this->disable_adminEngineMenus();
    
    $this->pluginItem->get_fromHeader();
    $this->pluginItem->activevalue = 1;
    if ( $this->pluginItem->active_plugin() )
      $this->text = $this->get_translation ('activationdone', $this->pluginItem->pluginvalue);
    else
      $this->text = $this->get_translation ('activationfailed', $this->pluginItem->pluginvalue);

    /* add page redirection */
    $this->set_redirect($this->get_adminLink(array(
        'mode'      => 'list', 
		'openTab'   => ucwords($this->pluginItem->typevalue).'s',
	)));
	
	/* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * init module object in admin/desactivate mode
   * @return void
   * @access private
   */
  function init_admin_desactivate() {
    global $camyks;

    /* check admin rights */
    if ( $this->check_right(1)===false )
      return $this->init_admin_actionNotAllowed();
  
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* disabled plugin item */
    $this->pluginItem->get_fromHeader();
    $this->pluginItem->activevalue = 0;
    
    if ( $this->pluginItem->save_toDatabase() )
      $this->text = $this->get_translation ('desactivationdone', $this->pluginItem->pluginvalue);
    else
      $this->text = $this->get_translation ('desactivationfailed', $this->pluginItem->pluginvalue);

    /* add page redirection */
    $this->set_redirect($this->get_adminLink(array(
        'mode'      => 'list', 
        'openTab'   => ucwords($this->pluginItem->typevalue).'s',
    )));
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * init module object in admin/setAsDefault mode
   * @return void
   * @access private
   */
  function init_admin_setAsDefault() {
    global $camyks;

    /* check admin rights */
    if ( $this->check_right(1)===false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menus */
    $this->disable_adminEngineMenus();
    
    $cMode = isset($_REQUEST['cMode'])?$_REQUEST['cMode']:'site';
        
    $this->pluginItem->get_fromHeader();
    if ( $this->pluginItem->set_asDefault($cMode))
      $this->text = $this->get_translation('configurationupdated');
    else
      $this->text = $this->get_translation('configurationnotupdated');

    /* add page redirection */
    $this->set_redirect($this->get_adminLink(array(
        'mode'      => 'list', 
		'openTab'   => ucwords($this->pluginItem->typevalue).'s',
	)));
	
	/* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /* 
   * init module object in admin/cleandb mode
   * @return void
   * @access private
   */
  function init_admin_cleandb() {
    global $camyks;

    /* check rights */
    if ( $this->check_right(1)===false ) {
      return $this->init_admin_actionNotAllowed(); 
    }
    
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* clean database */
    $camyks->get_neededPlugins();
    $this->get_modules();
    $this->get_templates();
    $this->get_themes();
    $this->get_inputs();
    $this->get_pluginsFromDatabase();
    $this->check_pluginsinfo();
    if ( count ( $this->unfound ) > 0 ) {
      foreach ( $this->unfound as $p ) {
	    $this->pluginItem->delete_fromDatabase( $p );
      }
	  $this->text = $this->get_translation ('cleaningdone');
    } else {
      $this->text = $this->get_translation ('nocleaningneeded');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('mode'=>'list')));
  }
  
  /*
   * init module object admin/list mode
   * @return void
   * @access private
   */
  function init_admin_list() {
    global $camyks;

    $camyks->get_neededPlugins();
    $this->get_modules();
    $this->get_templates();
    $this->get_themes();
    $this->get_inputs();
    $this->get_pluginsFromDatabase();
    $this->check_pluginsinfo();

    /* get help */
    $this->get_help();
    
    /* build tabs */
    if (!isset($camyks->inputs['TabBuilder']))
      $this->tabBuilder = input_get('TabBuilder', 'camyks');
    else
      $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    
    /* check if TabBuilder plugin is available */
    if ($this->tabBuilder === false)
      $camyks->throwFatalError(array(
        'title'         => $this->get_translation('error_pluginmissing_title'),
        'description'   => $this->get_translation('error_pluginmissing_desc', 'TabBuilder'),
      ));
    
    $this->tabBuilder->add_tabs(array(
        array(
            'name'  => 'Modules',
			'title' => $this->get_translation('tabmodules'),
	    ),
		array(
		    'name'  => 'Themes',
			'title' => $this->get_translation('tabthemes'),
		),
		array(
		    'name'  => 'Templates',
            'title' => $this->get_translation('tabtemplates'),
        ),
		array(
		    'name'  => 'Inputs',
			'title' => $this->get_translation('tabinputs'),
		),
	));
	
	if ( $this->help != null )
	 	$this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
	
    $this->tabBuilder->initialise(array('default'=>'Modules'));
       
    /* load scripts */
    $this->add_JSEngineFile('tool/htmlelement.js');
    $this->add_JSEngineFile('tool/clientenv.js');
    $this->add_JSEngineFile('object/cmenu.js');
    $this->add_JSScript('var themeActionMenu = new CMenu("themeActionMenu", null, null, "left");');
    $this->add_JSScript('globalCMenu.registerMenu(themeActionMenu);');
    
    $this->add_JSScript('var templateActionMenu = new CMenu("templateActionMenu", null, null, "left");');
    $this->add_JSScript('globalCMenu.registerMenu(templateActionMenu);');

    $this->add_JSFile('PluginList.js');
    $this->add_JSScript('var pl = new PluginList("pl");');
    $this->add_JSLoadScript('pl.initialise();');
    
    /* prepare action menus */
    $this->themeActionMenu = array(
      array(
        'name'  => 'setSiteDefault',
        'title' => $this->get_translation('applyassitedefaulttheme'),
        'icon'  => $this->theme->get_pictURL('valid', 12, 'std'),
        'url'   => 'javascript:pl.execute_action(\'setSiteDefaultTheme\');',
      ),
      array(
        'name'  => 'setAdminDefault',
        'title' => $this->get_translation('applyasadmindefaulttheme'),
        'icon'  => $this->theme->get_pictURL('valid', 12, 'std'),
        'url'   => 'javascript:pl.execute_action(\'setAdminDefaultTheme\');',
      ),      
    );
    
    $this->templateActionMenu = array(
      array(
        'name'  => 'setSiteDefault',
        'title' => $this->get_translation('applyassitedefaulttemplate'),
        'icon'  => $this->theme->get_pictURL('valid', 12, 'std'),
        'url'   => 'javascript:pl.execute_action(\'setSiteDefaultTemplate\');',
      ),
    );
    
    $this->add_JSLoadScript('pl.set_param("actionURLs", "setSiteDefaultTheme", "'.$this->get_adminJSLink(array('mode'=>'setAsDefault', 'cMode'=>'site', 'type'=>'theme', 'plugin'=>'__PNAME__')).'");');
    $this->add_JSLoadScript('pl.set_param("actionURLs", "setAdminDefaultTheme", "'.$this->get_adminJSLink(array('mode'=>'setAsDefault', 'cMode'=>'admin', 'type'=>'theme', 'plugin'=>'__PNAME__')).'");');
    $this->add_JSLoadScript('pl.set_param("actionURLs", "setSiteDefaultTemplate", "'.$this->get_adminJSLink(array('mode'=>'setAsDefault', 'cMode'=>'site', 'type'=>'template', 'plugin'=>'__PNAME__')).'");');


    /* button list for buttons bars */
    $this->buttons = array(array(
        'title' => $camyks->get_translation('back'),
		'link'  => $camyks->get_adminLink(),
	));
  }
  
  /* specific tool methods */

  /*
   * install plugin
   * @param string $plugin
   * @param string $type
   * @param string $location
   * @param string $version
   * @return boolean success
   * @access public
   */
  function install_plugin($plugin, $type, $location='camyks', $version='1.0') {
    return $this->pluginItem->active_plugin($plugin, $type, $location, $version);
  }

  /*
   * update plugin version
   * @param string $plugin
   * @param string $type
   * @param string $version
   * @return boolean success
   * @access private
   */
  function update_pluginVersion($plugin, $type, $version) {
    return $this->pluginItem->update_pluginVersion($plugin, $type, $version);
  }

  /*
   * get modules list
   * @return array
   * @access private
   */
  function get_modules ( ) {
    global $camyks;
    $this->modules = array_merge(
        module_getList($camyks->camyks_plugin_path, 'camyks'),
		module_getList($camyks->site_plugin_path, 'site')
	);
  }
  
  /*
   * get templates list
   * @return array
   * @access private
   */
  function get_templates ( ) {
    global $camyks;
    $this->templates = array_merge(
        template_getList($camyks->camyks_plugin_path, 'camyks'),
		template_getList($camyks->site_plugin_path, 'site')
	);
  }
  
  /*
   * get themes list
   * @return array
   * @access private
   */
  function get_themes ( ) {
    global $camyks;
    $this->themes = array_merge(
        theme_getList($camyks->camyks_plugin_path, 'camyks'),
		theme_getList($camyks->site_plugin_path, 'site')
	);
  }

  /*
   * get inputs list
   * @return array
   * @access private
   */
  function get_inputs ( ) {
    global $camyks;
    $this->inputs = array_merge(
        input_getList($camyks->camyks_plugin_path, 'camyks'),
		input_getList($camyks->site_plugin_path, 'site')
	);
  }

  /*
   * check all plugins with database value
   * @return void
   * @access private
   */
  function check_pluginsinfo ( ) {
    foreach ( $this->pluginsinfo as $p ) {
      /* get active value ( while checking if plugin folder exists ) */
      switch ( $p['type'] ) {
      case 'module':
	    if (isset($this->modules[$p['plugin']])) {
	      $this->modules[$p['plugin']]->active = ( $p['active'] == 1 ? true : false );
	    } else {
	      $this->unfound[] = $p;
	    }
	    break;
      case 'theme':
	    if (isset($this->themes[$p['plugin']])) {
	      $this->themes[$p['plugin']]->active = ( $p['active'] == 1 ? true : false );
	    } else {
	      $this->unfound[] = $p;
	    }
    	break;
      case 'template':
	    if (isset($this->templates[$p['plugin']])) {
	      $this->templates[$p['plugin']]->active = ( $p['active'] == 1 ? true : false );
	    } else {
	      $this->unfound[] = $p;
	    }
	    break;
      case 'input':
	    if (isset($this->inputs[$p['plugin']])) {
	      $this->inputs[$p['plugin']]->active = ( $p['active'] == 1 ? true : false );
	    } else {
	      $this->unfound[] = $p;
	    }
	    break;
      }
    }
  }
  
  /* specific i/o methods */

  /*
   * get plugins info from database
   * @return boolean success
   * @access private
   */
  function get_pluginsFromDatabase( ) {
    $this->pluginsinfo = $this->pluginItem->get_objectList();
  }
  
  /*
   * load installed database
   * @return boolean success
   * @access private
   */
  function load_installedTables() {
    global $camyks;
    
    $this->installedTables = array();
    
    /* build sql query */
    $sql = 'show tables';
    
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) { 
      /* get data from database */
      while ($data = $camyks->db_conn->get_queryNumDataLine()) {
        $this->installedTables[] = $data[0];
      }
    }
        
    return true;
  }
  
  /*
   * check if table is installed 
   * @param string $tableName
   * @return boolean result
   * @access public
   */
  function check_tableExists($tableName='') {
    if ($this->installedTables == null)
      $this->load_installedTables();
    return (in_array($tableName, $this->installedTables));     
  }

  /* static methods */

  /*
   * ** DEPRECATED **
   * get active plugins
   * @return void
   * @access private
   */
  function static_get_activePlugins ( ) {
    global $camyks;
    /* build sql query */
    $sql = 'select * ';
    $sql .= ' from admin_pluginmanager';
    $sql .= ' where active = 1';
        
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) { 
      /* get data from database */
      while ($data = $camyks->db_conn->get_queryDataLine()) {
	    switch ( $data['type'] ) {
	    case 'module':
	      $camyks->modules[$data['plugin']] = module_get ( $data['plugin'], $data['location'] );
	      break;
	    case 'theme':
	      $camyks->themes[$data['plugin']] = theme_get ( $data['plugin'], $data['location'] );
	      break;
	    case 'template':
	      $camyks->templates[$data['plugin']] = template_get ( $data['plugin'], $data['location'] );
	      break;
	    case 'template':
	      $camyks->inputs[$data['plugin']] = input_get ( $data['plugin'], $data['location'] );
	      break;
	    }
      }
    }
  }
}
?>