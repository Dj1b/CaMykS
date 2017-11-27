<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Creation Date    : Jun 2005
 * Last Modif Date  : Feb 2007
 * History :
 * * 05-06-xx : Initial file
 *
 * Plugin engine object
 * Parent object for Module, Input, Template, Theme objects
 */
class Plugin {
  /* variables */
  /* name used for PHP : must be unique */
  var $name;
  /* plugin type */
  var $plugin_type;
  /* plugin paths */
  var $plugin_path;
  var $plugin_site_path;
  var $plugin_var_path;
  /* plugin urls */
  var $plugin_url;
  var $plugin_site_url;
  var $plugin_var_url;
  /* plugin current version */
  var $version;
  /* is plugin active */
  var $active;
  /* path type ( value can be 'camyks' or 'site' ) */
  var $path_type;
  /* author infos */
  var $author_name;
  var $author_mail;
  var $author_group;
  /* plugin dependencies */
  var $plugin_dependencies;
  /* plugin package */
  var $plugin_package;

  /*
   * constructor
   * @param string $name
   * @param string $plugin_type
   * @param string $path_type
   */
  function Plugin ( $name, $plugin_type, $path_type  ) {
    global $camyks;
    /* set title value */
    $this->name = $name;
    /* set default version value */
    $this->version = '1.0';
    /* set type value */
    $this->plugin_type = $plugin_type;
    $this->object_type = $plugin_type;
    /* inactive plugin */
    $this->active = false;
    /* set plugin path type */
    $this->path_type = $path_type;
    /* set path values */
    $this->plugin_path = $camyks->get_pluginPath($path_type).'/'.$plugin_type.'/'.$this->name;
    $this->plugin_site_path = $camyks->get_pluginPath('site').'/'.$plugin_type.'/'.$this->name;
    $this->plugin_var_path = $camyks->site_var_path.'/'.$plugin_type.'/'.$this->name;
    /* set url values */ 
    $this->plugin_url = $camyks->get_pluginURL($path_type).'/'.$plugin_type.'/'.$this->name;
    $this->plugin_site_url = $camyks->get_pluginURL('site').'/'.$plugin_type.'/'.$this->name;
    $this->plugin_var_url = $camyks->site_var_url.'/'.$plugin_type.'/'.$this->name;
    /* set dependencies */
    $this->plugin_dependencies = array();
    $this->plugin_package = '';
  }
  
  /* plugin methods */

  /*
   * load a file from plugin folder
   * @param string $file
   * @return boolean success
   * @access public
   */
  function load_file ( $file ) {
    if ( file_exists( $this->plugin_site_path.'/'.$file ) ) {
      require( $this->plugin_site_path.'/'.$file );
      return true;
    } else if ( file_exists ($this->plugin_path.'/'.$file ) ) {
      require( $this->plugin_path.'/'.$file );
      return true;
    } else {
      /* TO DO */
      /* File not found */
    } 
    return false;
  }

  /*
   * load a file from var plugin folder
   * @param string $file
   * @return void
   * @access public
   */
  function load_varFile ( $file ) {
    $loadfile = $this->plugin_var_path.'/'.$file ;
    if ( file_exists ( $loadfile ) and is_file ($loadfile) ){
      require( $loadfile );
    } else {
      /* TO DO */
      /* File not found */
    }
  }

  /*
   * load a file from engine data folder
   * @param string $file
   * @return void
   * @access public
   */
  function load_engineFile ( $file ) {
    global $camyks;
    if (file_exists($camyks->site_engine_url.'/'.$file)) {
      require ($camyks->site_engine_url.'/'.$file);
    } elseif (file_exists($camyks->camyks_engine_path.'/'.$file)){
      require ($camyks->camyks_engine_path.'/'.$file);
    } else {
      /* TO DO */
      /* File not found */
    }
  }
  
  /*
   * get a file URL from engine data folder
   * @param string $file
   * @param integer $path
   * @return void
   * @access public
   */
  function get_engineFileURL ( $file, $path=false ) {
    global $camyks;
    
    switch ($path) {
      case 2: $baseURL = ''; break;
      case true: case 1: $baseURL = $camyks->get_rootBaseURL('absolute');  break;
      case 0: default : $baseURL = $camyks->get_rootBaseURL($path); break;
    }
        
    if (file_exists($camyks->site_engine_url.'/'.$file)) {
      return $baseURL.$camyks->site_engine_url.'/'.$file;
    } elseif (file_exists($camyks->camyks_engine_path.'/'.$file)){
      return $baseURL.$camyks->camyks_engine_path.'/'.$file;
    } else {
      /* TO DO */
      /* File not found */
      return '';
    }
  }

  /*
   * return plugin file url
   * @param string $file
   * @param integer $path
   *    0 : intermediate
   *    1 : full
   *    2 : strict
   * @param string $default
   * @return string
   * @access public
   */
  function get_fileURL ( $file, $path=null, $default='' ) {
    global $camyks;
    
    switch ($path) {
      case 2: $baseURL = ''; break;
      case true: case 1: $baseURL = $camyks->get_rootBaseURL('absolute');  break;
      case 0: default : $baseURL = $camyks->get_rootBaseURL($path); break;
    }
    
    /* get file url in site plugin folder */
    if ( file_exists ( $this->plugin_site_path.'/'.$file ) )
      return $baseURL.$this->plugin_site_url.'/'.$file;
    /* get file url in plugin folder */
    if ( file_exists ( $this->plugin_path.'/'.$file ) )
      return $baseURL.$this->plugin_url.'/'.$file;
    /* get default file url */
    return $default;
  }

  /*
   * return plugin var file
   * @param string $file
   * @param boolean $full
   * @param string $default
   * @return string
   * @access public
   */
  function get_varFileURL ( $file, $full=false, $default='' ) {
    global $camyks;
    
    $baseURL = $camyks->get_rootBaseURL($full);

    /* get file url in plugin folder */
    if ( file_exists ( $this->plugin_var_path.'/'.$file ) )
      return $baseURL.$this->plugin_var_url.'/'.$file;
    return $default;
  }

  /*
   * return file path
   * @param string $file
   * @return string
   * @access public
   */
  function get_filePath ( $file ) {
    if ( file_exists( $this->plugin_site_path.'/'.$file ) ) {
      return $this->plugin_site_path.'/'.$file ;
    } else if ( file_exists ($this->plugin_path.'/'.$file ) ) {
      return $this->plugin_path.'/'.$file ;
    } else {
      /* TO DO */
      /* File not found */
    } 
  }
  
  /*
   * return file from var plugin folder
   * @param string $file
   * @return string
   * @access public
   */
  function get_varFilePath ($file='') {
    if ( file_exists ( $this->plugin_var_path.'/'.$file ) ){
      return $this->plugin_var_path.'/'.$file ;
    } else {
    	return $this->plugin_var_path;
      /* TO DO */
      /* File not found */
    }
  }


  /*
   * DEPRECATED : alias to previous method
   */
  function get_varFile($file){$this->get_varFilePath($file);}
  
  /***************** HTML PAGE HEADER METHODS ***********************/

  /*
   * set a redirect to the current page
   * @param integer $time the timeout in second
   * @param string $url the url to target
   * @return void
   * @access private
   */
  function set_redirect ( $time, $url = '' ) {
    global $camyks;
    if (is_string($time)) {
      $url = $time;
      $time = $camyks->get_confValue('ModuleActionDelay');
    }
    
    $camyks->HTMLPage->set_redirect( $time, $url );
  }

  /*
   * add a meta tag to the page
   * @param string $name
   * @param string $content
   * @param string $method
   * @return void
   * @acces private
   */
  function add_meta ($name, $content, $method='name') {
    global $camyks;
    $camyks->HTMLPage->add_meta ($name, $content, $method);
  }

  /***************** JS & CSS METHODS ******************/

  /*
   * update javascript file list
   * @param string $file
   * @return void
   * @access public
   */
  function add_JSFile ( $file ) {
    global $camyks;
    if ($this->path_type == 'camyks')
      $camyks->HTMLPage->add_JSFile($camyks->camyks_plugin_url.'/'.$this->plugin_type.'/'.$this->name.'/js/'.$file);
    else
      $camyks->HTMLPage->add_JSFile('plugin/'.$this->plugin_type.'/'.$this->name.'/js/'.$file);
  }

  /*
   * update javascript file list
   * @param string $file
   * @return void
   * @access public
   */
  function add_JSEngineFile ( $file ) {
    global $camyks;
    $camyks->HTMLPage->add_JSFile($camyks->get_dataFilePath('js/'.$file));
  }

  /*
   * update javascript file list
   * @param string $file
   * @return void
   * @access public
   */
  function add_JSExternFile ( $file  ) {
    global $camyks;
    $camyks->HTMLPage->add_JSFile ( $file );
  }

  /*
   * update javascript script list
   * @param string $script
   * @param boolean $unique
   * @return void
   * @access public
   */
  function add_JSScript ( $script, $unique=false ) {
    global $camyks;
    $camyks->HTMLPage->add_JSScript( $script, $unique );
  }

  /*
   * update javascript post script list
   * @param string $script
   * @param boolean $unique
   * @return void
   * @access public
   */
  function add_JSPreScript ( $script, $unique=false ) {
    global $camyks;
    $camyks->HTMLPage->add_JSPreScript ( $script, $unique );
  }

  /*
   * update javascript window event
   * @param string $event
   * @param string $script
   * @param boolean $unique
   * @return void
   * @access public
   */
  function add_JSWindowEventScript($event, $script, $unique=false) {
    global $camyks;
    $camyks->HTMLPage->add_JSWindowEventScript($event, $script, $unique);
  }

  /*
   * update javascript onload script list
   * @param string $script
   * @param boolean $unique
   * @return void
   * @access public
   */
  function add_JSLoadScript ( $script, $unique=false ) {
    $this->add_JSWindowEventScript('load', $script, $unique);
  }

  /*
   * update javascript onunload script list
   * @param string $script
   * @param boolean $unique
   * @return void
   * @access public
   */
  function add_JSUnloadScript ( $script, $unique=false ) {
    $this->add_JSWindowEventScript('unload', $script, $unique);
  }

  /*
   * update style file list
   * @param string $file
   * @param string $media
   * @return void
   * @access public
   */
  function add_styleFile ( $file, $media='', $condition='' ) {
    global $camyks;
        
    if ($this->get_filePath('css/'.$file, false) != false)
      $camyks->HTMLPage->add_styleFile($this->get_fileURL('css/'.$file, 2), $media, $condition);
    elseif ($this->get_filePath($file, false) != false)
      $camyks->HTMLPage->add_styleFile($this->get_fileURL($file, 2), $media, $condition);
  }

  /*
   * update style scripts
   * @param string $css
   * @return void
   * @access public
   */
  function add_styleScript ( $css ) {
    global $camyks;
    $camyks->HTMLPage->add_styleScript( $css );
  }

  /*
   * update style included files
   * @param string $script
   * @return void
   * @access public
   */
  function add_styleIncludedFile ( $file ) {
    global $camyks;
    $camyks->HTMLPage->add_styleIncludedFile ( $file );
  }
  
  /*
   * update style file list
   * @param string $file
   * @return void
   * @access public
   */
  function add_StyleExternFile($file, $media='', $condition='') {
    global $camyks;
    $camyks->HTMLPage->add_styleFile($file, $media, $condition);
  }

  /* 
   * update RSS Feed link
   * @param string $title
   * @param string $url
   * @return void
   * @access public
   */
  function set_RSSFeed( $title, $url ) {
    global $camyks;
    $camyks->HTMLPage->set_RSSFeed( $title, $url );
  }
  
  /*
   * add extra texts to page header
   * @param string $content
   * @return void
   * @access public
   */
  function add_headerExtra($content='') {
    global $camyks;
    $camyks->HTMLPage->add_headerExtra($content);
  }

  /***************** INSTALL/UNINSTALL METHODS ****************/

  /*
   * install plugin
   * @param string $more
   * @return boolean
   * @access public
   */
  function install () {
    global $camyks;
    $camyks->log_information($this, 'Installation Successfull', ''); 
    return true;
  }
  
  /*
   * uninstall plugin
   * @return boolean
   * @access public
   */
  function uninstall(){
    $camyks->log_information($this, 'Uninstall Successfull', ''); 
    return true;
  }

  /*
   * update plugin
   * @return boolean
   * @access private
   */
  function update( $version, $more='' ) {
    global $camyks;
    if ( isset($camyks->modules['Admin_PluginManager']) and 
	 $camyks->modules['Admin_PluginManager']->update_pluginVersion($this->name, $this->plugin_type, $this->version)){
      $camyks->log_information($this, 'Update from '.$version.' to version '.$this->version.' successful', $more); 
      return true;
    }
    return false;
  }

  /* dependencies management methods */

  /*
   * add a dependency
   * @param string $plugin
   * @param string $type
   * @param string $version
   * @param boolean $mandatory
   */
  function add_dependency($plugin, $type, $version='1.0', $mandatory=false) {
    $this->plugin_dependency[] = array('plugin'=>$plugin,
				       'type'=>$type,
				       'version'=>$version,
				       'mandatory'=>$mandatory);
  }
  
  /*
   * build dependencies list
   * @return boolean success
   * @access private
   */
  function set_dependencies() {
    return true;
  }
  
  /* extensions management methods */
  
  /*
   * register plugin as extension to another
   * @param string $plugin
   * @return void
   * @access public
   */
  function register_asExtension($plugin) {
  	global $camyks;
  	$camyks->register_asExtension($plugin, $this->name, $this->plugin_type);
  }
  
  /*
   * get registered extensions
   * @return array
   * @access public
   */
  function get_registeredExtensions() {
  	global $camyks;
  	return $camyks->get_registeredExtensions($this->name);
  }
  
  /* CaMykS event handler management methods */
  
  /*
   * register plugin as handler for CaMykS event
   * @param string $event
   * @access protected
   */
  protected function register_asCaMykSEventHandler($event) {
    global $camyks;
    $camyks->register_eventHandler($event, $this);
  }
  
  /*
   * execute handler on CaMykS initialisation
   * @return void
   * @access public
   */
  public function execute_onCaMykSInitialise() {}
  
  /*
   * execute handler on CaMykS page load
   * @return void
   * @access public
   */
  public function execute_onCaMykSPageLoad() {}
  
  /*
   * execute handler on body opening
   * @return string
   * @access public
   */
  public function execute_onCaMykSBodyOpen() {return '';}
  
  /*
   * execute handler on body closing
   * @return string
   * @access public
   */
  public function execute_onCaMykSBodyClose() {return '';}
  
  /*
   * execute handler on camyks terminate
   * @return void
   * @access public
   */
  public function execute_onCaMykSTerminate() {}
  
}
?>