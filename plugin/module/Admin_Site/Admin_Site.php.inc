<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Jun 2005
 * Last Modif Date  : Oct 2017
 * History :
 * * 05-06-xx : Initial files
 *
 * Site configuration engine
 *
 * TO DO :
 * - complete config settings
 * - save config mode
 *
*/

final class Admin_Site extends Module {
  /* variables */
  private $conf_elements;
  private $mode;
  protected $dbSummary;
  
  /*
   * constructor
   * @param string $path_type
   */
  public function __construct ($path_type) {
    parent::Module('Admin_Site', $path_type);
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
    
    /* conf array from camyks object */
    $this->conf_elements=array(
        'cms', /* CaMykS */
		'cms_version', /* CaMykS version */
		'engine_path', /* CaMykS path */
		'site_name', /* site name ( folder name ) */
		'site_title', /* site title */
		'url', /* site url */
		'encoding', /* data encoding */
		'version', /* site version */
		'admin_entry', /* admin entry point : admin.php */
		'friendlyurls', /* is friendlyurls actived */
		'site_author', /* site author */
		'site_company', /* site company */
		'workflow', /* workflow active - not working */
		'maintenance', /* is maintenance actived - not working */
		'database_name', /* database name */
		'database_host', /* database host */
		'database_login', /* database login */
		'database_pwd', /* database pwd */
		'admin_ssl', /* ssl handling in admin mode */
		'admin_default_language', /* default language in admin mode */
		'admin_languages', /* availables languages in admin mode */
		'admin_default_theme', /* default theme in admin mode */
		'site_ssl', /* ssl handling in site mode */
		'site_default_theme', /* default theme in site mode */
		'site_default_template', /* default template in site mode */
		'site_languages', /* availables languages in site mode */
		'site_default_language', /* default language in site mode */
		'editing_languages', /* available languages in edition mode */
		'page_maxmodules', /* max modules in a page */
		'google_analytics', /* google analytics code */
		'admin_allowblockthemechange', /* allow block theme change in page editor */
		'admin_itemsbypage', /* items displayed in generic admin lists */
		'admin_maxfilesize', /* max file size in admin forms */
	);
  }
  
  /* overwrite Module methods */
  
  /*
   * get module rights
   * @return void
   * @access private
   */
  public function get_rights() {
    global $camyks;
    
    $this->rights[0] = array(
        'name'=>'read',
		'title'=> $this->get_translation('rights_read_site_config'),
		'default'=> false,
	);
			     
    /* $this->rights[1] = array(
        'name'=>'edit',
		'title'=> $camyks->get_translation('rights_edit_site_config'),
		'default'=> false,
    ); */
    
    $this->rights[2] = array(
        'name'=>'read_plugin_config',
		'title'=> $this->get_translation('rights_read_plugin_config'),
		'default'=> false,
    );
    
    $this->rights[3] = array(
        'name'=>'edit_plugin_config',
		'title'=> $this->get_translation('rights_edit_plugin_config'),
		'default'=> false,
    );
  }

  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  public function init_admin () {
    global $camyks;
    
    /* check access right */
    if ($this->check_right(0) === false)
      $this->init_admin_accessDenied();
    
    /* load mode */
    $this->mode = (isset($_REQUEST['mode'])? $_REQUEST['mode'] : 'readSiteConfig');
    
    /* check action to execute */
    switch ($this->mode) {
      case 'viewPluginConfig':
        $this->init_admin_viewPluginConfig();
        break;
      case 'editPluginConfig':
        $this->init_admin_editPluginConfig();
        break;
      case 'savePluginConfig':
        $this->init_admin_savePluginConfig();
        break;
      case 'viewSiteConfig':
      default:
        $this->init_admin_viewSiteConfig();
        break;
    }
    
    /* generic init */
    parent::init_admin();
  }
  
  /* specific admin init mode methods */ 

  /*
   * init object module in admin/viewSiteConfig mode
   * @return void
   * @access private
   */
  private function init_admin_viewSiteConfig() {
    global $camyks;
    
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
        'title'         => $camyks->get_translation('error_pluginmissing_title'),
        'description'   => $camyks->get_translation('error_pluginmissing_desc', 'TabBuilder'),
      ));
    
    $this->tabBuilder->add_tabs(array(
        array(
            'name'  => 'Properties',
			'title' => $this->get_translation('tabproperties'),
	    ),
		array(
		    'name'  => 'SiteMode',
            'title' => $this->get_translation('tabsitemode'),
        ),
		array(
		    'name'  => 'AdminMode',
			'title' => $this->get_translation('tabadminmode'),
		),
		array(
		    'name'  => 'Server',
			'title' => $this->get_translation('tabserver'),
		),
		array(
		    'name'  => 'Database',
			'title' => $this->get_translation('tabdatabase'),
		),
	));
	
	if ($this->check_right(2)) {
	    /* load extension plugin list */
        $extensions = $this->get_registeredExtensions();        
        
        /* build plugin list by type */
        $this->plugins = array('modules' => array(), 'themes' => array(), 'templates' => array(), 'inputs' => array());
        foreach ($extensions as $name => &$plugin) {
          $this->plugins[$plugin->plugin_type.'s'][$name] = $plugin->title;
        }
        unset($extensions);
	
	    /* add plugins tab */
	    $this->tabBuilder->add_tab(array(
	        'name'  => 'Plugins',
			'title' => $this->get_translation('tabplugins'),
	    ));
	}
	
	if ($this->help != null)
	 	$this->tabBuilder->add_tab(array('name'=>'help',
				     'title'=>$camyks->get_translation('help')));
	
    $this->tabBuilder->initialise(array('default'=>'Properties'));
    
    /* get database info */
    $this->dbSummary = $camyks->db_conn->database_getSummary();
        
    /* button list for buttons bar */
    $this->buttons = array(array(
        'title' => $camyks->get_translation('back'),
		'link'  => $camyks->get_adminLink(),
	));

    /* update layout */
    $this->selected_layout = 'admin_view_site_config.html.inc';   
  }

  /*
   * init object module in admin/viewPluginConfig mode
   * @return void
   * @access private
   */
  private function init_admin_viewPluginConfig() {
    global $camyks;
    
    /* check access right */
    if ($this->check_right(2) === false)
      $this->init_admin_accessDenied();
      
    /* load extension plugin list */
    $extensions = $this->get_registeredExtensions();      
    
    /* check plugin */
    if (!isset($_REQUEST['plugin']) or !isset($extensions[$_REQUEST['plugin']])) {
        $this->text = $this->get_translation('error_pluginnotfound');
        /* update layout */
        $this->selected_layout = 'admin_message.html.inc';
        $this->selected_layout_location = 'camyks';
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Plugins')));
    }
    
    $this->plugin = &$extensions[$_REQUEST['plugin']];
    $this->plugin->initialise_configDisplay();
        
    /* button list for buttons bar */
    $this->buttons = array(array(
        'title' => $camyks->get_translation('back'),
		'link'  => $this->get_adminLink(array('openTab'=>'Plugins')),
	));
	if ($this->check_right(3)) {
	  $this->buttons[] = array(
        'title' => $camyks->get_translation('modify'),
		'link'  => $this->get_adminLink(array('mode'=>'editPluginConfig', 'plugin'=>$this->plugin->name)),
	  );
	}

    /* update layout */
    $this->selected_layout = 'admin_view_plugin_config.html.inc';   
  }
    
  /*
   * init object module in admin/viewPluginConfig mode
   * @return void
   * @access private
   */
  private function init_admin_editPluginConfig() {
    global $camyks;
    
    /* check access right */
    if ($this->check_right(3) === false)
      $this->init_admin_accessDenied();
      
    /* load extension plugin list */
    $extensions = $this->get_registeredExtensions();      
    
    /* check plugin */
    if (!isset($_REQUEST['plugin']) or !isset($extensions[$_REQUEST['plugin']])) {
        $this->text = $this->get_translation('error_pluginnotfound');
        /* update layout */
        $this->selected_layout = 'admin_message.html.inc';
        $this->selected_layout_location = 'camyks';
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Plugins')));
    }
    $this->plugin = &$extensions[$_REQUEST['plugin']];

    
    /* build form */
    $this->form = new HTMLForm(
        'edit_pluginConfiguration',
		$this->get_adminlink(array('mode'=>'savePluginConfig', 'plugin'=>$this->plugin->name)),
		'POST');
    
    /* initialise plugin edition */
    $this->plugin->initialise_configEdition($this->form);
    
        
    /* button list for buttons bar */
    $this->buttons = array(
      array(
        'title' => $camyks->get_translation('back'),
		'link'  => $this->get_adminLink(array('openTab'=>'Plugins')),
      ),
	  array(
        'title' => $camyks->get_translation('valid'),
		'link'  => $this->form->get_HTMLSubmitLink(),
	  ),
	);

    /* update layout */
    $this->selected_layout = 'admin_edit_plugin_config.html.inc';   
  }
  
  /*
   * init object module in admin/savePluginConfig mode
   * @return void
   * @access private
   */
  private function init_admin_savePluginConfig() {
    global $camyks;
    
    /* check access right */
    if ($this->check_right(3) === false)
      $this->init_admin_accessDenied();
      
    /* load extension plugin list */
    $extensions = $this->get_registeredExtensions();      
    
    /* check plugin */
    if (!isset($_REQUEST['plugin']) or !isset($extensions[$_REQUEST['plugin']])) {
        $this->text = $this->get_translation('error_pluginnotfound');
    } else {
      $this->plugin = &$extensions[$_REQUEST['plugin']];
      /* save configuration */
      if ($this->plugin->save_configuration()) 
        $this->text = $this->get_translation('pluginconfiguration_saved', $this->plugin->name);
      else
        $this->text = $this->get_translation('pluginconfiguration_notsaved', $this->plugin->name);
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'Plugins')));
  }

  /* specific tool methods */
  
  /* 
   * return conf default value
   * @param string $confName
   * @param mixed $default
   * @return mixed
   * @access private
   */
  public function get_confDefaultValue($confName, $default) {
    global $camyks;

    switch ($confName) {
    case 'site_title':
      return '';
    case 'url':
      return '';
    case 'encoding':
      return 'utf8';
    case 'version':
      return '1.0';
    case 'admin_entry':
      return 'admin.php';
    case 'friendlyurls':
      return true;
    case 'site_author':
      return '';
    case 'site_company':
      return '';
    case 'workflow':
      return false;
    case 'maintenance':
      return false;
    case 'database_name':
      return '';
    case 'database_host':
      return '';
    case 'database_login':
      return '';
    case 'database_pwd':
      return '';
    case 'admin_ssl':
      return 'default';
    case 'admin_default_language':
      return 'en';
    case 'admin_languages':
      return array('en');
    case 'admin_default_theme':
      return 'IndigoFlatStyle';
    case 'site_ssl':
      return 'default';
    case 'site_default_theme':
      return '';
    case 'site_default_template':
      return '';
    case 'site_languages':
      return array('en');
    case 'site_default_language':
      return 'en';
    case 'editing_languages':
      return $camyks->get_confDefaultValue('site_languages');
    case 'page_maxmodules':
      return 8;
    case 'google_analytics':
      return '';
    case 'admin_allowblockthemechange':
      return false;
    case 'admin_itemsbypage':
      return 20;
    case 'admin_maxfilesize':
      return 128*1024;
    }
    return $default;
  }
  
  /*
   * return given ssl value description
   * @param string $value
   * @return string
   * @access public
   */
  public function get_SSLValueDescription($value='') {
    switch($value) {
      case 'auto' : return $this->get_translation('sslvalue_auto');
      case 'forced' : return $this->get_translation('sslvalue_forced');
      case 'none' : return $this->get_translation('sslvalue_none');
      case 'default' : 
    }
    return $this->get_translation('sslvalue_default');
  }
}
?>