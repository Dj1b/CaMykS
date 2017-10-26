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
    $this->rights[0] = array('name'=>'read',
			     'title'=> $camyks->get_translation('read'),
			     'default'=> false);
    /* $this->rights[1] = array('name'=>'edit',
			     'title'=> $camyks->get_translation('write'),
			     'default'=> false);*/
  }

  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  public function init_admin () {
    global $camyks;
    if ( $this->check_right(0) === false ) {
      $this->init_admin_accessDenied();
    } else if ( $this->check_right(1) === false ) {
      $this->init_admin_read();
    } else {
      $this->mode = ( isset( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'modify');      
      switch ( $this->mode ) {
      case 'save':
	    $this->init_admin_save();
	    break;
      case 'modify':
      default:
	    /* 
	     * TO DO 
	     * execute init_admin_modify method
	     */
	    $this->init_admin_read();
	    break;
      }
    }
    parent::init_admin();
  }
  
  /* specific admin mode methods */ 


  /*
   * init object module in admin/read mode
   * @return void
   * @access private
   */
  private function init_admin_read() {
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
	
	if ( $this->help != null )
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
    $this->selected_layout = 'admin_read_config.html.inc';   
  }
  
  /*
   * init object module in admin/modify mode
   * @return void
   * @access private
   */
  private function init_admin_modify() {
    global $camyks;
    
    return true;    
  }
  
  /*
   * init object module in admin/save mode
   * @return void
   * @access private
   */
  private function init_admin_save () {
    global $camyks;
    
    return true;
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
      return 'GreyStyle';
    case 'site_ssl':
      return 'default';
    case 'site_default_theme':
      return 'GreyStyle';
    case 'site_default_template':
      return 'DefaultPage';
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