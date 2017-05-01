<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * Object Version	: 1.0
 * Object Type      : Engine / Main Object
 * Creation Date    : Jun 2005
 * Last Modif Date  : Feb 2017
 *
 * CaMykS engine object
 */

/* constants */
define ('CAMYKS_MODE_SITE',		    0 );
define ('CAMYKS_MODE_ADMIN',		1 );
define ('CAMYKS_MODE_REQUEST',		2 );
define ('CAMYKS_MODE_MANAGER',		3 );
define ('CAMYKS_MODE_INSTALL',		4 );
define ('CAMYKS_NAME', 			    'CaMykS');

class Camyks {
  /* name */
  var $name;	
  /* camyks current version */
  var $version;
  /* camyks last modification date */
  var $last_modification_date;
 
  /* Camyks objects */
  /* site */
  var $site;
  var $site_name;
  /* mode ( admin / site / manager / install ) */
  var $mode;
  
  /* all "in file" translation for site */
  var $trads;
  /* all "from db" translation for site */
  var $dbtrads;

  /* camyks path */
  var $camyks_path;
  /* plugin path in camyks folder */
  var $camyks_plugin_path;
  /* module url in camyks folder */
  var $camyks_plugin_url;
  /* engine path in camyks folder */
  var $camyks_engine_path;
  
  /* site site path */
  var $site_path;
  /* plugin path in site folder */
  var $site_plugin_path;
  /* plugin url in site folder */
  var $site_plugin_url;
  /* var folder path in site folder */
  var $site_var_path;
  /* var folder url in site folder */
  var $site_var_url;
  /* cache path in site folder */
  var $site_cache_path;
  /* cache url in site folder */
  var $site_data_url;
  
  /* site base url */
  var $site_base_url;

  /* database vars */
  var $db_table_prefix;
  var $db_conn;
  
  /* file extension */
  var $file_extension;
  
  /* CMS plugins */
  var $modules;
  var $templates;
  var $inputs;
  var $themes;

  /* selected theme */
  var $theme;
  
  /* languages */
  var $current_language;
  
  /* cache */
  var $cache;
  
  /* session */
  var $session_vars;	

  /* shared data */
  var $shared_data;
  
  var $plugin_extensions;

  /* page */
  var $HTMLPage;
  var $contentPage;

  /* running modes */
  var $previewMode;
  var $deviceMode;

  /*
   * CaMykS Constructor
   * @param array $site_conf
   * @param integer $mode
   */
  function Camyks ( $site_conf, $mode=CAMYKS_MODE_SITE ) {
    /* init vars */
    $this->name = CAMYKS_NAME;
    $this->object_type = CAMYKS_NAME;
    $this->site_conf = $site_conf;
    $this->site_name = $site_conf['site_name'];

    $this->camyks_path = realpath($site_conf['engine_path']);
    if ( isset($this->site_conf['installed'])
	 and $this->site_conf['installed']==1 ) {
      $this->mode = $mode;
    } else {
      $this->mode = CAMYKS_MODE_INSTALL;
    }
    $this->trads = array();
    $this->dbtrads = array();
    $this->cache = array();
    $this->session_vars = array();
    $this->shared_data = array();
    $this->plugin_extensions = array();
    $this->adminUser = false;
  }
  
  /* methods */
  
  /* CaMykS main method */
  function execute ( ) {
    /* init camyks object */
    $this->initialise();
    /* build content with CaMykS engine object */
    $this->get_pageContent();
    /* kill CaMykS engine object */
    $this->init_kill();
  }
  
  /******************** INIT **************************/
  /* global init for object */
  function initialise () {
    /* get generic initialisation */
    $this->get_genericInit();
    
    /* get specific initialisation */
    switch ( $this->mode ) {
    case CAMYKS_MODE_SITE:
      $this->get_siteInit();
      break;
    case CAMYKS_MODE_ADMIN:
      $this->get_adminInit();
      break;
    case CAMYKS_MODE_REQUEST:
      $this->get_requestInit();
      break;
    case CAMYKS_MODE_MANAGER:
      $this->get_managerInit();
      break;
    case CAMYKS_MODE_INSTALL:
      $this->get_installInit();
      break;
    }
  }
  
  /* generic camyks initialization */
  function get_genericInit() {
    /* get camyks configuration file */
    $this->get_confFiles();

    /* get camyks needed pathes */
    $this->get_camyksPathes();

    /* get camyks needed lib files */
    $this->get_libs();

    /* get site site needed pathes */
    $this->get_sitePathes();

    /* update included pathes */
    set_include_path(get_include_path().PATH_SEPARATOR
		     .$this->camyks_engine_path.'/lib/object/'.PATH_SEPARATOR
		     .$this->camyks_engine_path.'/lib/tool/'.PATH_SEPARATOR
		     .$this->camyks_engine_path.'/lib/external/'.PATH_SEPARATOR
		     .$this->camyks_engine_path.'/lib/external/PEAR/');
		     
    /* check bench to start */
    $this->benchMode = isset($_REQUEST['_cBench']);
    if ($this->benchMode) {
      $this->benchMode = new CBench(array('output'=>$_REQUEST['_cBench']));
      $this->benchMode->start('CaMykS mode initialisation');
    }    
  }
  
  /* init camyks in site mode */
  function get_siteInit() {
    /* check security */
    $this->check_security('site');
    
    /* get database connection */
    $this->get_databaseConnection();

    /* language */
    $this->get_currentLanguage('site');

    /* get global language */
    $this->add_generic_translation();

    /* get plugin lists */
    $this->get_plugins();

    /* check admin user */
    $this->get_adminUser();

    /* get generic & site conf */
    $this->check_siteConf( );

    /* check plugins version */
    $this->check_plugins( );
  }
  
  /* init camyks in admin mode */
  function get_adminInit() {
    /* check security */
    $this->check_security('admin');
  
    /* get database connection */
    $this->get_databaseConnection();

    /* language */
    $this->get_currentLanguage('admin');

    /* get plugin lists */
    $this->get_plugins();

    /* get generic & admin conf */
    $this->check_adminConf();

    /* get global language */
    $this->add_generic_translation();

    /* check plugins version */
    $this->check_plugins( );

    /* check admin user */
    $this->get_adminUser();
  }

  /* init camyks in request mode */
  function get_requestInit() {

  }

  /* init camyks in install mode */
  function get_installInit() {
    
    /* language */
    $this->get_currentLanguage('admin');

    /* get plugin lists */
    $this->get_plugins();

    /* get generic & admin conf */
    $this->check_adminConf();

    /* get global language */
    $this->add_generic_translation();

    /* initialise installer module */
    if ( isset( $this->modules['Tool_Installer'] ) )
      $this->modules['Tool_Installer']->init_admin();
    else {
      /* throw fatal error */
      $error = array('title'=>'Installer Module not found',
		     'description'=>'Installer Module not found',
		     'error_link'=>'http://www.camyks.net',
		     'error_title'=>'Check CaMykS website for more informations.');
      $this->throwFatalError( $error );
    }
  }
  
  /*
   * initialise CaMykS in manager mode
   * @return void
   * @access private
   */
  function get_managerInit() {
    /* get manager libs */
    require_once ('./fx/engine/include.php.inc');
  }
  
  /******************** CONFIGURATION *****************/
  
  /*
   * get camyks conf files
   * @return void
   * @access private
   */
  function get_confFiles ( ) {
    /* load global config */
    require_once ($this->camyks_path.'/engine/etc/dynamic.php.inc');
    
    /* apply time zone */
    date_default_timezone_set($this->get_confValue('TimeZone', 'Europe/Paris'));
    
    /* load static config */
    require_once ($this->camyks_path.'/engine/etc/static.php.inc');
    
    /* merge engine and site configs */
    $this->_conf = array_merge($this->_conf, $this->site_conf);
  }

  /*
   * initialise required CaMykS pathes
   * @return void
   * @access private
   */
  function get_camyksPathes ( ) {
    /* check camyks installation mode */
    if ( preg_match('/^camyks/', $this->_conf['engine_path']))
      $this->_installationMode = 'dedicated';
    else
      $this->_installationMode = 'shared';

    /* set camyks plugin full path */
    $this->camyks_plugin_path = $this->camyks_path.'/'.$this->plugin_folder;
    /* set camyks plugin full url */
    if ( $this->_installationMode=='shared')
      $this->camyks_plugin_url = 'c'.$this->plugin_folder;
    else
      $this->camyks_plugin_url = 'camyks/'.$this->plugin_folder;
    /* set camyks lib full path */
    $this->camyks_engine_path = $this->camyks_path.'/'.$this->engine_folder;
  }

  /*
   * load all internal libs files
   * @return void
   * @access private
   */
  function get_libs () {
  
    /* start capture extra codes */
    ob_start();
  
    /* load all object library */
    require_once( $this->camyks_engine_path.'/lib/object/CBench.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/CDBConnection.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/CImage.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/CMail.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/CRequestAnswer.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/Database_connection.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/HTMLForm.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/HTMLPage.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/Plugin.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/Input.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/Module.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/Template.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/Theme.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/ModuleConfig.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/ModuleConfigItem.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/ModuleLibrary.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/ModuleLibraryItem.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/ModuleLibraryJoin.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/MLDatabaseItem.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/MLDatabaseLocalizedItem.php.inc');
    require_once( $this->camyks_engine_path.'/lib/object/MLTextItem.php.inc');    
    require_once( $this->camyks_engine_path.'/lib/object/MLTextLocalizedItem.php.inc');    
    require_once( $this->camyks_engine_path.'/lib/object/MLFileItem.php.inc');    
    require_once( $this->camyks_engine_path.'/lib/object/MLFileLocalizedItem.php.inc');    
    require_once( $this->camyks_engine_path.'/lib/object/MLTemporaryItem.php.inc');    
    require_once( $this->camyks_engine_path.'/lib/object/FSFile.php.inc');    

    /* load all tool library */
    require_once( $this->camyks_engine_path.'/lib/tool/array.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/client.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/cookie.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/countries.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/data.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/date.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/file.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/folder.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/html.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/input.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/language.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/mail.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/module.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/password.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/plugin.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/shell.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/statics.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/string.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/string2.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/template.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/theme.php.inc');
    require_once( $this->camyks_engine_path.'/lib/tool/xml.php.inc');
    
    /* load site libraries */
    if (file_exists($this->site_path.'./assets/lib')) {
      foreach (glob ($this->site_path.'./assets/lib/*.php.inc') as $filename) {
        require_once($filename);
      }
    }
    
    /* clear extra codes */
    ob_end_clean();
  }

  /*
   * initialise needed site pathes
   * @return void
   * @access private
   */
  function get_sitePathes (  ) {
    /* set site full path */
    $this->site_path = '.';
    /* set site plugin full path */
    $this->site_plugin_path = $this->site_path.'/'.$this->plugin_folder;
    /* set site plugin full url */
    $this->site_plugin_url = $this->plugin_folder;
    /* set site var folder full path */
    $this->site_var_path = './'.$this->var_folder;
    /* set site var folder full url */
    $this->site_var_url = $this->var_folder;
    /* set site cache full path */
    $this->site_cache_path = $this->site_path.'/'.$this->cache_folder;
    /* set available engine data full url */
    if ( $this->_installationMode == 'shared' )
      $this->site_data_url = 'cdata';
    else
      $this->site_data_url = 'camyks/engine/data';
    /* set site engine path */
    $this->site_engine_url = 'assets';
      
    /* set site base url */
    $this->site_base_url = $this->get_defaultBaseURL();
  }
  
  /*
   * check security 
   * @return void
   * @access private
   */
  function check_security($mode) {
    if ( !in_array($mode, array('site', 'admin')))
      die();
    
    /* load ssl value to apply */
    $value = $this->get_confValue($mode.'_ssl', 'default');
    
    /* load current status */
    $isSSL = client_isHTTPS();
    
    /* define SSL URL */
    if (preg_match('/http:\/\//', $this->get_confValue('url')))
      $sslURL = preg_replace('/http:\/\//', 'https://', $this->get_confValue('url'));
    else
      $sslURL = $this->get_confValue('url');
        
    /* be sure that conf URL is properly set */
    if ($isSSL and preg_match('/http:\/\//', $this->get_confValue('url')))
      $this->set_confValue('url', preg_replace('/http:\/\//', 'https://', $this->get_confValue('url')));
    
    /* execute relevent action */
    switch ($value) {
      case 'forced':
        if ($isSSL) return;
        header('Location:'.$sslURL.$_SERVER['REQUEST_URI']);
        break;
      case 'none':
        if (!$isSSL) return;
        header('Location:http://'.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI']);
        break;
      case 'auto':
        if ($isSSL) return;
        $test = get_headers('https://'.$_SERVER['HTTP_HOST']);
        if (preg_match('/200/', $test[0])) {          
          header('Location:'.$sslURL.$_SERVER['REQUEST_URI']);
        }
        break;
      case 'default': default:
        return;
    }
  }

  /*
   * check site configuration
   * @return void
   * @access private
   */
  function check_siteConf ( ) {
    /* get site theme from configuration */
    $theme = isset($this->_conf['site_default_theme'])?$this->_conf['site_default_theme']:'GreyStyle';

    /* check theme */
    if ( isset ( $this->themes[$theme] ) ) {
      $this->theme = &$this->themes[$theme];
    } else {
      /* error */
      $error = array('title'=>'Configuration file error',
		     'description'=>'Configuration file error',
		     'content1'=>'Check your site configuration file for the "site_default_theme" value.',
		     'content2'=>'This value must be set to the name of an activated theme.',
		     'content3'=>'The default theme value is "GreyStyle". ',
		     'error_link'=>'http://www.camyks.net',
		     'error_title'=>'Check CaMykS website for more informations.');
      $this->throwFatalError( $error );
    }
    
    /* check preview mode value */
    $this->previewMode = (isset($_REQUEST['preview']) and $_REQUEST['preview']=='forced' and $this->check_adminUser());

    /* check device mode value */
    $this->check_deviceMode();
  }

  /*
   * check admin configuration
   * @return void
   * @access private
   */
  function check_adminConf ( ) {

    /* get admin theme from configuration */
    $theme = isset($this->_conf['admin_default_theme'])?$this->_conf['admin_default_theme']:'GreyStyle';

    /* check theme */
    if ( isset ($this->themes[$theme]) ) {
      $this->theme = &$this->themes[$theme];
    } else {
      /* throw error */
      $error = array('title'=>'Configuration file error',
		     'description'=>'Configuration file error',
		     'content1'=>'Check your site configuration file for the "admin_default_theme" value.',
		     'content2'=>'This value must be set to the name of an activated theme.',
		     'content3'=>'The default theme value is "GreyStyle". ',
		     'error_link'=>'http://www.camyks.net',
		     'error_title'=>'Check CaMykS website for more informations.');
      $this->throwFatalError( $error );
    }
  }
  
  /*
   * define/update configuration value
   * @param string $confName
   * @param mixed $value
   * @return void
   * @access public
   */
  function set_confValue($confName, $value='') {
    $this->_conf[$confName] = $value;
  }

  /*
   * return configuration value
   * @param string $confName
   * @param mixed $default
   * @return mixed
   * @access public
   */
  function get_confValue($confName, $default='') {
    if (isset($this->_conf[$confName]))
      return $this->_conf[$confName];
    if (isset($this->modules['Admin_Site']))
      return $this->modules['Admin_Site']->get_confDefaultValue($confName, $default);
    return $default;
  }

  
  /******************** LOCALISATION ******************/

  /*
   * load dictionnary from its path
   * @param string $path
   * @param string $lang
   * @return void
   * @access public 
   */
  function add_translation ( $path, $lang=null ) {
    
    /* check language */
    if ( $lang == null )
      $lang = $this->current_language;
        
    /* build full path */
    $file = $path . '/translation_'.$lang.$this->file_extension;
   
    if (file_exists ($file)){
      /* load file for given language */
      require ( $file );
    } else {
      /* build full path for default language */
      $file = $path . '/translation_'.$this->default_language.$this->file_extension;
      if ( file_exists ( $file ) ) {
	/* load file for default language */
	require_once ( $file );
      } else {
	/* TO DO */
	/* send an error to a global object : current language & default language file not found */
      }
    }
  }
  
  /*
   * load an internal dictionnary
   * @param string $more
   * @param string $language
   * @return void
   * @access public
   */
  function add_generic_translation ( $more='', $language=null ) {
    $this->add_translation ( $this->camyks_engine_path.'/locale/'.$more, $language );
  }
  
  /*
   * return localisation values
   * @param string $string
   * @param mixed $data
   * @return string
   * @access public
   */
  function get_translation ( $string, $data=array() ) {
    $string = strtolower ($string);
    if (isset($this->trads[$string]))
      return vsprintf($this->trads[$string], $data );
    return $string;
  }

  /* 
   * manage the language to use
   * @param string $type
   * @return void
   * @access private
   */
  function get_currentLanguage ( $type ) {
    /* get available language list */
    if ( isset ( $this->_conf[$type.'_languages'] ) and is_array( $this->_conf[$type.'_languages']) ) {
      $list = $this->_conf[$type.'_languages'];
    } else {
      $list = array();
    }

    if ( $type == 'admin' ) {
      $newlg = (isset( $_REQUEST['_clg_'] ) ? $_REQUEST['_clg_'] : '' );
    } else {
      $newlg = (isset( $_REQUEST['_clg_'] ) ? substr($_REQUEST['_clg_'], 1, 3) : '' );
    }

    if ( count( $list ) == 0 or $newlg=='' or !in_array ( $newlg, $list ) ) {
      if ( $this->get_sessionValue($type.'language') != null ) {
	    $l = $this->get_sessionValue( $type.'language');
      } else if ($type == 'admin' and ($lc = cookie_get('adminlanguage'))!=null) {
	    $l = $lc;
	  } else if ( isset($_SERVER['HTTP_ACCEPT_LANGUAGE']) and in_array ( ($lc = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2)), $list)) {
	    $l = $lc;
      } else if ( isset ( $this->_conf[$type.'_default_language']) ) {
	    $l = $this->_conf[$type.'_default_language'];
      } else {
	    $l = 'en';
      }
    } else {
      $l = $newlg;
    }
    
    /* set the language to use */
    if ( $type == 'admin' )
      cookie_save('adminlanguage', $l, 90);
    $this->set_sessionValue($type.'language', $l);
    $this->current_language = $l;
    $loc = setlocale ( LC_ALL, language_getLocale( $l, $this->_conf['encoding'] ) );
  }

  /*
   * deprecated
   * @return array
   * @access public
   */
  function get_availableLanguages ( ) {
    return language_getAvailableLanguages();
  }

  /******************** ENCODING **********************/


  function decode_value ( $v ) {
    switch ( $this->_conf['encoding'] ) {
    case 'utf8':
      return utf8_decode(stripslashes( $v ));
      break;
    default:
      return stripslashes( $v );
    }
  }

  function encode_value ( $v ) {
    switch ( $this->_conf['encoding'] ) {
    case 'utf8':
      return addslashes(utf8_encode( $v ));
      break;
    default:
      return addslashes( $v );
    }
  }
  
  function get_htmlencodingvalue( ) {
    switch ( $this->_conf['encoding'] ) {
    case 'utf8':
      return 'UTF-8';
      break;
    default:
      return 'UTF-8';
    }
  }
  
  function get_mysqlencodingvalue( ) {
    switch ( $this->_conf['encoding'] ) {
    case 'utf8':
      return 'utf8';
      break;
    default:
      return 'utf8';
    }
  }

  /******************** PLUGINS ***********************/
  /* get all available and active plugins */
  function get_plugins ( ) {
    ob_start();
    $this->modules = array();
    $this->themes = array();
    $this->templates = array();
    $this->inputs = array();
    /* check if pluginmanager table exists */
    /* build sql query */
    $sql = "show tables like 'admin_pluginmanager'";
    
    /* execute sql query */
    if ( isset($this->db_conn) and $this->db_conn->execute_query($sql) and $this->db_conn->get_queryDataLine()) {
      /* get active plugins from database */
      /* build sql query */
      $sql = 'select * ';
      $sql .= ' from admin_pluginmanager';
      $sql .= ' where active = 1';
      $sql .= ' order by plugin';
            
      /* execute sql query */
      $this->db_conn->execute_query($sql) or $this->throwFatalError(array('title'=>'Fatal Error',
							       'description'=>'Connection to plugin database failed',
							       'content1'=>'CaMykS is not able to get plugins from your website.',
							       'error_link'=>'http://www.camyks.net',
							       'error_title'=>'Check CaMykS website for more informations.'));
      
      $plugins = array();
      
      /* get data from database */
      while ($data = $this->db_conn->get_queryDataLine()) {
        $plugins[] = $data;
     }
             
      /* load plugins */
      foreach ($plugins as $data) {
	    switch ( $data['type'] ) {
	      case 'module':
	        $m = module_get( $data['plugin'], $data['location'] );
	        if ( $m !== false ) {
	          $m->_installedVersion = $data['version'];
	         $this->modules[$data['plugin']] = $m;
	        }
	        break;
	      case 'theme':
	        $t = theme_get ( $data['plugin'], $data['location'] );
	        if ( $t !== false ) {
	          $t->_installedVersion = $data['version'];
	          $this->themes[$data['plugin']] = $t;
	        }
	        break;
	      case 'template':
	        $t = template_get ( $data['plugin'], $data['location']);
	        if ( $t !== false ) {
	          $t->_installedVersion = $data['version'];
	          $this->templates[$data['plugin']] = $t;
	        }
	        break;
	      case 'input':
	        $i = input_get( $data['plugin'], $data['location'] );
	        if ( $i !== false ) {
	          $i->_installedVersion = $data['version'];
	          $this->inputs[$data['plugin']] = $i;
	        }
	        break;
	    }
      }
      
      unset($plugins);
      
      /* check for plugin updates */
      plugin_checkUpdates();
    } else {
      /* get all plugins */
      $this->get_modules( );
      $this->get_templates( );
      $this->get_inputs( );
      $this->get_themes( );
    }
    ob_clean();
  }
  
  /* compare active plugins and requiered plugins */
  function check_plugins() {
    $this->get_neededPlugins();
    /* check modules */
    foreach ( $this->neededModules as $p ) {
      if ( !isset($this->modules[$p['name']]))
	die ( 'Plugin '.$p['name'].' is missing.' );
      else if ( $this->modules[$p['name']]->version < $p['version'] )
	die ( 'CaMykS need version '.$p['version'] . ' of plugin '.$p['name'].', current is '.$this->modules[$p['name']]->version.'.');
    }

    /* check inputs */
    foreach ( $this->neededInputs as $p ) {
      if ( !isset($this->inputs[$p['name']]))
	die ( 'Plugin '.$p['name'].' is missing.' );
      else if ( $this->modules[$p['name']]->version < $p['version'] )
	die ( 'CaMykS need version '.$p['version'] . ' of plugin '.$p['name'].', current is '.$this->inputs[$p['name']]->version.'.');
    }

    /* check themes */
    foreach ( $this->neededThemes as $p ) {
      if ( !isset($this->themes[$p['name']]))
	die ( 'Plugin '.$p['name'].' is missing.' );
      else if ( $this->themes[$p['name']]->version < $p['version'] )
	die ( 'CaMykS need version '.$p['version'] . ' of plugin '.$p['name'].', current is '.$this->inputs[$p['name']]->version.'.');
    }

    /* check templates */
    foreach ( $this->neededTemplates as $p ) {
      if ( !isset($this->templates[$p['name']]))
	die ( 'Plugin '.$p['name'].' is missing.' );
      else if ( $this->templates[$p['name']]->version < $p['version'] )
	die ( 'CaMykS need version '.$p['version'] . ' of plugin '.$p['name'].', current is '.$this->templates[$p['name']]->version.'.');
    }
  }
  
  /* get modules list in CaMykS object */
  function get_modules ( ) {
    $this->modules = array_merge(module_getList($this->camyks_plugin_path, 'camyks'), 
				 module_getList($this->site_plugin_path, 'site'));
  }
  
  /* get templates list in CaMykS object */
  function get_templates ( ) {
    $this->templates = array_merge(template_getList($this->camyks_plugin_path, 'camyks'),
				   template_getList($this->site_plugin_path, 'site'));
  }
  
  /* get inputs list in CaMykS object */
  function get_inputs ( ) {
    $this->inputs = array_merge(input_getList($this->camyks_plugin_path, 'camyks'),
				input_getList($this->site_plugin_path, 'site'));
  }
  
  /* get themes list in CaMykS object */
  function get_themes ( ) {
    $this->themes = array_merge(theme_getList($this->camyks_plugin_path, 'camyks'),
				theme_getList($this->site_plugin_path, 'site'));
  }
  
  
  /* get needed plug-ins list */
  function get_neededPlugins () {
    $file = $this->camyks_engine_path.'/'.$this->conf_folder.'/neededPlugins'.$this->file_extension;
    if ( file_exists( $file ) ) {
      require_once ( $file );
    } else {
      $this->neededModules = array();
      $this->neededInputs = array();
      $this->neededTemplates = array();
      $this->neededThemes = array();
    }
  }

  /* return plugin path */
  function get_pluginPath ( $path_type ) {
    switch ( $path_type ) {
    case 'camyks' : return $this->camyks_plugin_path;
    case 'site' : return $this->site_plugin_path;
    }
  }

  /* return plugin url */
  function get_pluginURL ( $path_type ) {
    switch ( $path_type ) {
    case 'camyks' : return $this->camyks_plugin_url;
    case 'site' : return $this->site_plugin_url;
    }
  }

  /****************** ADMIN USER *********************/
  /*
   * load admin user
   * @return void
   * @access private
   */
  function get_adminUser() {
    /* load current adminUser */
    if (isset($this->modules['Admin_User'])) {
      $this->adminUser = new AdminUser($this->get_sessionValue('admin_user'));
      $this->adminUser->get_fromDatabase();
    }
  }

  /*
   * check if user is connected
   * @return boolean result
   * @access public
   */
  function check_adminUser() {
    return ( $this->adminUser != false and $this->adminUser->login != '' );
  }

  /******************** CACHES ***********************/
  
  /*
   * return cache file
   * @param string $title
   * @return mixed
   * @access public
   */
  function get_cache ( $title ) {
    // if cache is already loaded, get cached cache value
    if ( isset ( $this->cache[$title] ) ) {
      return $this->cache[$title];
    }
    
    // check if cache file exists
    $file = $this->site_cache_path."/".$title.$this->file_extension;
    if ( file_exists ( $file ) ) {
      require_once( $file );
      // check if cache var is correctly set
      if ( isset ( $cache_value ) ) {
	$this->cache[ $title ] = file_getUnserializedVar ( $cache_value );
	return $this->cache[ $title ];
      } else {
	/* TO DO */
	/* no cache value founded */
      }
    } else {
      /* TO DO */
      /* no cache file found */
    }
    return null;
  }
  
	// set cache file	
  function set_cache ( $title, $content, $desc = "" ) {
    $file_path = $this->site_cache_path."/".$title.$this->file_extension;
    // try to open file & write inside
    if ( $file = fopen($file_path, "w")) {
			// update content
      $file_content = file_getPHPFileHeader( $desc );
      $file_content .= file_getSerializedVar ( $title, $content );
      $file_content .= file_getPHPFileEnder();
      
      // write content to file
      fputs( $file, $file_content);
      fclose( $file);
    } else {
      /* TO DO */
      /* cannot save cache file */
    }
  }
  
  /******************** DEVICE *************************/
  
  /*
   * check selected device mode value
   * @param string $device
   * @return void
   * @access public
   */
  function check_deviceMode ($device='') {
    /* load device value */
    if ($device != '') {
      $deviceStatus = 'forced';
    } elseif (isset($_REQUEST['_cDevice'])) {
      $device = $_REQUEST['_cDevice'];
      $deviceStatus = 'forced';
    } elseif ($this->get_sessionValue('deviceMode', '') != '') {
      $this->deviceMode = $this->get_sessionValue('deviceMode');
      return;
    } else {
      $ua = client_getUAInfos();
      
      /* check for hacks or fakes */
      if (in_array($ua['platform_type'], array('hack', 'fake'))) {
        header('HTTP/1.1 403 Forbidden');
        die();
      }
      
      /* define define/format */
      $device = $ua['platform_format'];
      $deviceStatus = 'auto';
    }
        
    /* check device value */
    if ($device == 'mobile')
      $device = 'handheld';
    elseif (!in_array($device, array('desktop', 'tablet', 'handheld'))) {
      $device = 'desktop';
      $deviceStatus = 'auto';
    }
        
    /* set device value */
    $this->deviceMode = $device;
    $this->set_sessionValue('deviceMode', $device);
    $this->set_sessionValue('deviceStatus', $deviceStatus);
  }

  /******************** ERRORS *************************/

  function throwFatalError( $error ) {
    /* complete error values */
    $error['site_title'] = isset($this->_conf['site_title'])?$this->_conf['site_title']:'';
    /* display error */
    $splashError = $this->camyks_engine_path.'/data/html/splash_error.html.inc';
    if ( file_exists( $splashError ) ) {
      require_once( $splashError );
    } else {
      /* to do */
    }
    $this->init_kill();
    die();
  }

  /******************** LOGS ***************************/
  function log_event( $type, &$object, $desc1='', $desc2='', $file='', $line=0 ) {
    if ( is_string( $object ) ) {
      /* old system create a report */

    } else {
    
      /* add log report */
      if ( isset ( $this->modules['Admin_SystemReport'] ) 
	   and $this->modules['Admin_SystemReport']->is_installed() ) {
	   
	    $this->modules['Admin_SystemReport']->add_newReport($type,
							    $object,
							    $desc1,
							    $desc2,
							    $file,
							    $line );
      }
    }
    /* always return false */
    return false;
  }
  
  /* log_event shortcut for sql error */
  function log_sqlerror ( &$object, $sqlquery='', $file='', $line=0 ) {
    return $this->log_event('SQL Error',
			    $object,
			    $sqlquery,
			    $this->db_conn->get_queryError(),
			    $file,
			    $line);
  }

  /* log_event shortcut for internal error */
  function log_internalerror ( &$object, $desc1='', $desc2='', $file='', $line=0 ) {
    return  $this->log_event('Internal Error',
			     $object,
			     $desc1,
			     $desc2,
			     $file,
			     $line);
  }

  /* log_event shortcut for information */
  function log_information ( &$object, $info1='', $info2='' ) {
    return $this->log_event('Information',
			    $object,
			    $info1,
			    $info2);
  }

  /* log_event shortcut for execution error */
  function log_executionerror( &$object, $desc1='', $desc2='') {
    return $this->log_event('Execution Error',
			    $object,
			    $desc1,
			    $desc2);
  }

  /******************** STATS **************************/
  /*
   * try to write statistic
   * @param string $name
   * @param string $module
   * @param string $type
   * @param string $main
   * @param string $data1
   * @param strint $data2
   * @param array $params
   * @return void
   * @access public
   */
  function update_statistic ( $name='', $module='', $type='', $main='', $data1='', $data2='', $params=array() ) {
    if (isset($this->modules['Admin_Statistics'])) {
      $this->modules['Admin_Statistics']->update_statistic($name, $module, $type, $main, $data1, $data2, $params);
    }
  }

  /*
   * update site statistics
   * @return void
   * @access private
   */
  function update_siteStatistics ( ) {
    /* update global statistics in site mode only */
    if ( $this->mode != CAMYKS_MODE_SITE )
      return;
    /* update global statistics for visitors only */
    if ( $this->check_adminUser()===true )
      return;
    /* update global statistics only if statistic engine is available */
    if (isset($this->modules['Admin_Statistics']))
      $this->modules['Admin_Statistics']->update_siteStatistics();
  }
  
  /******************** DATABASE ***********************/
  
  /* 
   * create connection to the database
   * @return boolean success
   * @access public
   */
  function get_databaseConnection () {
    if ( $this->_conf['database_name'] != "" ) {
      $this->db_conn = new Database_connection($this->get_confValue('database_host'),
					       $this->get_confValue('database_login'), 
					       $this->get_confValue('database_pwd'),
					       $this->get_confValue('database_driver', '')
					);
      if ($this->db_conn->is_active()) {
	    if ($this->db_conn->select($this->_conf['database_name'])) {
	      return true;
	    } else {
	      /* error : database not found on database server */
	      $error = array('title'=>'Database connection failed',
			 'description'=>'Database connection failed',
			 'content1'=>'CaMykS was able to connect to MySQL server, but database doesn\'t exist.',
			 'error_link'=>'http://www.camyks.net',
			 'error_title'=>'Check CaMykS website for more informations.');
	      }
      } else {
	    /* error : database connection failed */
	    $error = array('title'=>'Database connection failed',
		       'description'=>'Database connection failed',
		       'content1'=>'CaMykS was not able to connect to MySQL server.',
		       'content2'=>'- MySQL server may be down.',
		       'content3'=>'- Configuration file databases values may be wrong.',
		       'error_link'=>'http://www.camyks.net',
		       'error_title'=>'Check CaMykS website for more informations.');
      }
    } else {
      /* error : no database name defined */
      $error = array('title'=>'Configuration file error',
		     'description'=>'Configuration file error',
		     'content1'=>'Check your site configuration file for the "database_name" value.',
		     'error_link'=>'http://www.camyks.net',
		     'error_title'=>'Check CaMykS website for more informations.');
    }
    $this->throwFatalError( $error );
  }
  
  /*
   * return database connection
   * @return Object 
   * @access public
   */
  function &get_dbConnection() {
    return $this->db_conn;
  }
  
  /******************** SESSION  *************************/
  
  /*
   * save var to session
   * @param string $name
   * @param mixed $value
   * @return void
   * @access public
   */
  function set_sessionValue ( $name, $value='' ) {
    $_SESSION[$this->site_name.'_'.$name] = $value;
  }
  
  /*
   * get var from session
   * @param string $name
   * @param mixed $value
   * @return void
   * @access public
   */
  function get_sessionValue( $name, $value = null ) {
    if ( isset($_SESSION[$this->site_name.'_'.$name ]) )
      return $_SESSION[$this->site_name.'_'.$name];
    return $value;
  }
  
  /*
   * trash session
   * @return void
   * @access public
   */
  function kill_session ( ) {
    foreach ( $_SESSION as $name => $value ) {
      if ( strpos($name, $this->site_name.'_')==0 ) {
	    unset($_SESSION[$name]);
      }
    }
  }

  /******************** SHARED DATA ********************/

  function set_sharedData ( $name, $data=null, $sub=null ) {
  	if ( $sub == null)
  		$this->shared_data[$name] = $data;
  	else {
  		if (!isset($this->shared_data[$name]))
  			$this->shared_data[$name] = array();
  		if ($data == null)
				$this->shared_data[$name][] = $sub;
			else
				$this->shared_data[$name][$data] = $sub;
  	}
  }

  function get_sharedData ( $name, $value=null ) {
  	if ($value != null and isset($this->shared_data[$name][$value]))
  		return $this->shared_data[$name][$value];
  
    if ( isset ( $this->shared_data[$name] ) )
      return $this->shared_data[$name];
    return $value;
  }

  function check_sharedData ( $name ) {
    return isset($this->shared_data[$name]);
  }
  
  /******************** PLUGIN EXTENSIONS **************/
  
  /*
   * register a plugin as an extension to another
   * @param string $plugin
   * @param string $ext_name
   * @param string $ext_type
   * @return void
   * @access public
   */
  function register_asExtension($plugin, $ext_name, $ext_type) {
  	if (!isset($this->plugin_extensions[$plugin]))
  		$this->plugin_extensions[$plugin] = array();
  	$this->plugin_extensions[$plugin][] = array('name'=>$ext_name, 'type'=>$ext_type);
  }
  
  /*
   * get registered extensions
   * @param string $plugin
   * @return array
   * @access public
   */
  function get_registeredExtensions($plugin) {
  	if (!isset($this->plugin_extensions[$plugin]))
  		return array();
	$list = array();
	foreach ($this->plugin_extensions[$plugin] as $p) {
	  switch ($p['type']) {
		case 'module':
	      if (isset($this->modules[$p['name']]))
			$list[$p['name']] = $this->modules[$p['name']];
		  break;
		case 'input':
		  if (isset($this->inputs[$p['name']]))
			$list[$p['name']] = $this->inputs[$p['name']];
		  break;
		case 'theme':
		  if (isset($this->themes[$p['name']]))
			$list[$p['name']] = $this->themes[$p['name']];
		  break;
		case 'template':
		  if (isset($this->templates[$p['name']]))
			$list[$p['name']] = $this->templates[$p['name']];
		  break;
		default:
			break;
		}
	}
	return $list;
  }
  
  /******************** PATHES & URLS ******************/
  
  /*
   * return root base url
   * @param string $mode
   * @return string
   * @access public
   */
  function get_rootBaseURL($mode = null) {
  	if ($mode == null)
  		return $this->site_base_url;
  	return $this->get_defaultBaseURL($mode);
  }
  
  /*
   * return default base url
   * @param mixed $mode
   * @return $string
   * @access private
   */
  function get_defaultBaseURL($mode=null) {
  	/* check for default mode */
  	if ($mode == null)
  		$mode = $this->get_confValue('file_path');
  		
  	/* check for boolean mode value */
  	if ($mode === false)
  	  $mode = 'relative';
  	elseif ($mode === true)
  	  $mode ='absolute';
  
  	/* return base url from mode */
  	switch ($mode) {
  		case 'absolute':
  		case 'absolute_long':
  			return $this->get_confValue('url').'/';
  		case 'absolute_short':
  			return '/';
  		case 'relative':
  		default:
  			return '';
  	}
  	return '';
  }
  
  /*
   * return file url
   * @param string $filePath
   * @param string $mode
   * @return $string
   * @access private
   */
  function get_fileURL($file='', $mode=null) {
    if (substr($file, 0, 2) == './')
      $file = substr($file, 2);
    return $this->get_rootBaseURL($mode).$file;
  }
  
  
  /******************** DATA FILES *********************/

  /*
   * return data file URL
   * @param string $file
   * @param boolean $full
   * @param string $default
   * @return string
   * access public
   */
  function get_dataFileURL($file, $full=null, $default='') {
	
	$baseURL = $this->get_rootBaseURL($full);
    
    /* get file url from site data folder */
    if (file_exists ($this->site_engine_url.'/'.$file))
      return $baseURL.$this->site_engine_url.'/'.$file;
      
    /* get file url from camyks data folder */
    if (file_exists ($this->site_data_url.'/'.$file))
      return $baseURL.$this->site_data_url.'/'.$file;
      
    /* get default file url */
    return $default;
  }
	
  /*
   * return data file path
   * @param string $file
   * @return string
   * @access public
   */
  function get_dataFilePath ( $file ) {
  	/* get file from site data folder */
    if (file_exists ($this->site_engine_url.'/'.$file))
      return $this->site_engine_url.'/'.$file;
      
    /* get file from camyks data folder */
    if (file_exists($this->camyks_path.'/engine/data/'.$file))
      return $this->site_data_url.'/'.$file ;
    
    /* TO DO */
    /* File not found */
    return '';
  }
  
  /******************** ENDING *************************/

  /* init kill camyks object */
  function init_kill() {
    if ($this->benchMode !== false) $this->benchMode->export();
    register_shutdown_function('camyks_kill');
    die();
  }

  /* kill camyks object */
  function kill () {
    /* close database */
    if ( isset($this->db_conn) ) {
      $this->db_conn->kill();
    }
  }
  
  /******************* LINKS ***************************/

  function get_adminLink ( $module='', $params=array() ) {
    $link = $this->_conf['admin_entry'];
    if ( $module != '' ) {
      $link .= '?module='.$module;
    }
    foreach ( $params as $key => $value ) {
      if ( $key != '' ) {
	$link .= '&amp;'.$key .'='.$value;
      }
    }
   return $link;
  }

  function get_adminJSLink ($module='', $params=array()) {
    $link = $this->_conf['admin_entry'];
    if ( $module != '' ) {
      $link .= '?module='.$module;
    }
    foreach ( $params as $key => $value ) {
      if ( $key != '' ) {
	$link .= '&'.$key .'='.$value;
      }
    }
    return $link;
  }
  
  function get_requestLink ($params=array()) {
    $link = 'request.php?';

    $items = array();
    foreach ( $params as $key => $value ) {
      if ( $key != '' ) {
	    $items[] = $key .'='.$value;
      }
    }
    $link .= implode('&amp;', $items);
    return $link;
  }

  function get_requestJSLink ($params=array()) {
    $link = 'request.php?';

    $items = array();
    foreach ( $params as $key => $value ) {
      if ( $key != '' ) {
	    $items[] = $key .'='.$value;
      }
    }
    $link .= implode('&', $items);
    return $link;
  }

  function get_siteLink ($page, $name='', $lg='', $params=array()) {
    return $this->modules['Admin_ContentPage']->get_sitePageLink($page, $lg, $params);
  }

  function get_siteHomepageLink () {
    return $this->modules['Admin_ContentPage']->get_siteHomePageLink();
  }

  function get_siteCurrentLink ($lg='', $params=null) {
    return $this->get_siteLink ( $this->contentPage->id,
				 $this->contentPage->name,
				 $lg,
				 $params!=null?$params:$this->contentPage->params);
  }

  function get_siteLinkByName ($name, $lg='', $params=array()) {
    $page = ContentPage::static_get_pageBasicInfoByName( $name );
    return $this->get_rootBaseURL().$this->get_siteLink ( $page->id,
				 $page->name,
				 $lg,
				 $params);
  }

  function get_siteLinkEncodeParams($params) {
    if ( count( $params ) == 0 ) 
      return '';
    $p = array();
    foreach ( $params as $n => $v ) {
      $p[] = ''.$n;
      $p[] = ''.$v;
    }
    $p = implode('_', $p );
    return $p;
  }

  function get_siteLinkDecodeParams($params) {
    $p = array();
    $params = explode ('_', $params);
    for ( $i=1; $i<count( $params); $i+=2 ) {
      $p[$params[$i-1]] = $params[$i];
    }
    return $p;
  }

  /******************* CONTENT *************************/
  /* build content */
  function get_pageContent() {
    if ($this->benchMode!==false) $this->benchMode->start('CaMykS page loading');
  
    switch ( $this->mode ) {
    case CAMYKS_MODE_SITE:
      $this->get_sitePageContent();
      break;
    case CAMYKS_MODE_ADMIN:
      $this->get_adminPageContent();
      break;
    case CAMYKS_MODE_REQUEST:
      $this->get_requestPageContent();
      break;
    case CAMYKS_MODE_MANAGER:
      $this->get_managerPageContent();
      break;
    case CAMYKS_MODE_INSTALL:
      $this->get_installPageContent();
      break;
    }

  }
  
  /* build content for visite site */
  function get_sitePageContent() {
    /* create page */
    $this->HTMLPage = new HTMLPage();
    $this->HTMLPage->set_charset($this->get_htmlencodingvalue());

    /* update HTML page metas with site informations */
    $this->HTMLPage->set_siteInformations( $this->get_confValue('site_title'), 
					   $this->get_confValue('site_company'));

    /* create page content */
    $page = isset ( $_REQUEST['page'] ) ? $_REQUEST['page'] : '';
    $params = isset ( $_REQUEST['params'] ) ? $_REQUEST['params'] : '';
    $this->contentPage = new ContentPage ($this->mode, 0, $params );
        
    /* get init from content */
    $this->contentPage->load_asFrontPage($page);
          
    /* get internal locales */
    $this->HTMLPage->set_pageInformations ( $this->contentPage->title,
					    $this->contentPage->description,
					    $this->contentPage->keywords, 
					    $this->current_language);
    $this->HTMLPage->set_robotInformations();

    /* set mobile configuration values */
    if ($this->deviceMode == 'handheld')
      $this->HTMLPage->set_mobileMeta(true, $this->get_confValue('mobileConfig'));

    /* set google analytics informations */
    $this->HTMLPage->set_googleInformations($this->get_confValue('google_analytics', ''), $this->get_confValue('google_analytics_domain', ''));

    /* add favicon */
    if ( ($f = $this->get_confValue('favicon', false)) !== false ) {
      $this->HTMLPage->set_favicon($f);
    } else {
      $this->HTMLPage->set_favicon();
    }
        
    $this->contentPage->init_site();

    /* update statistics */
    $this->update_siteStatistics();

    /* display html header */
    $this->HTMLPage->add_HTMLHeader();
    /* display html content */
    $this->contentPage->display();
    /* display html footer */
    $this->HTMLPage->add_HTMLFooter();
  }
  
  /* build content for admin */
  function get_adminPageContent() {
    /* init admin module to display */
    if ( $this->check_adminUser() === false ) {
      /* check for over written admin login module */
      if ( isset( $this->_conf['adminLoginModule'] ) and isset( $this->modules[$this->_conf['adminLoginModule']]))
	    $module = $this->_conf['adminLoginModule'];
      else
	    $module = 'Tool_Login';
    } else if ( isset ( $_REQUEST['module'] ) ) {
      $module = $_REQUEST['module'];
    } else {
      /* check for over written admin home  module */
      if ( isset( $this->_conf['adminHomeModule'] ) and isset( $this->modules[$this->_conf['adminHomeModule']]))
	    $module = $this->_conf['adminHomeModule'];
      else
	    $module = 'Tool_ControlPanel';
    }
    
    /* set up HTML Page config  */
    $this->set_confValue('html_version', 5);

    /* create page */
    $this->HTMLPage = new HTMLPage();
    $this->HTMLPage->set_charset( $this->get_htmlencodingvalue());
    $this->HTMLPage->add_JSFile($this->get_dataFilePath('js/tool/adminengine.js'));
    
    /* create admin special page content */
    $this->contentPage = $this->modules['Admin_ContentPage']->get_newPage();
    $this->contentPage->set_adminData ( $module );
    
    /* get init from content */
    $this->theme->initialise();
    $this->contentPage->init_admin();

    /* update header vars */
    $this->HTMLPage->set_siteInformations ($this->_conf['site_title'],
					    'CaMykS Team',
					    '');
    $this->HTMLPage->set_pageInformations ($this->get_translation('administration').' - ' .$this->contentPage->modules[0]->title,
					    null,
					    null,
					    $this->current_language);
    $this->HTMLPage->set_robotInformations (false, false);
    if ( isset($this->_conf['favicon']) ) {
      $this->HTMLPage->set_favicon( $this->_conf['favicon'] );
    } else {
      $this->HTMLPage->set_favicon( );
    }

    /* display html header */
    $this->HTMLPage->add_HTMLHeader();
    /* display html main content */
    $this->contentPage->display();
    /* display html footer */
    $this->HTMLPage->add_HTMLFooter();
  }

  /* build content in request mode */
  function get_requestPageContent() {
    $plugin = false;
    
    /* get plugin */
    if (isset($_GET['module'])) {
      if (($plugin = module_get ( $_GET['module'], 'site' )) === false)
	    $plugin = module_get ( $_GET['module'], 'camyks' );
    } elseif (isset($_GET['input'])) {
      if (($plugin = input_get ( $_GET['input'], 'site' )) === false) 
	    $plugin = input_get ( $_GET['input'], 'camyks' );
    }
    /* get plugin init & display */
    if ( $plugin !== false ) {
      $plugin->execute_request();
    }
    
    /* check for CaMykS Asset request */
    if (isset($_GET['CaMykSAsset'])) {
      $asset = $_GET['CaMykSAsset'];      
      if (preg_match('/\.\./', $asset))
        die();
        
      $file = new FSFile($this->camyks_path.'/engine/data/'.$asset);
      if ($file->exists) $file->send();
    }
    
    /* check for CaMykS Asset request */
    if (isset($_GET['PluginAsset'])) {
      $asset = $_GET['PluginAsset'];      
      if (preg_match('/\.\./', $asset))
        die();
      
      $file = new FSFile($this->camyks_path.'/plugin/'.$asset);
      if ($file->exists) $file->send();
    }
  }
  
  /* build content in manager mode */
  function get_managerPageContent() {
    /* open manager */
    manager_main();
  }

  /* build content in install mode */
  function get_installPageContent() {
    
    $this->get_currentLanguage('admin');
    /* create page */
    $this->HTMLPage = new HTMLPage();
    $this->HTMLPage->set_charset ( $this->get_htmlencodingvalue());
    $this->theme->get_included_main_css();
    $this->theme->get_included_parts();

    /* start to build the page with header */
    $this->HTMLPage->set_siteInformations ( $this->_conf['site_title'],
					    'CaMykS Team',
					    '');
    $this->HTMLPage->set_pageInformations ( $this->modules['Tool_Installer']->title,
					    null,
					    null,
					    $this->current_language);
    $this->HTMLPage->set_robotInformations ( false, false );

    $this->HTMLPage->add_HTMLHeader();

    $this->modules['Tool_Installer']->display_admin();

    /* html ender */
    $this->HTMLPage->add_HTMLFooter();
  }
}
?>