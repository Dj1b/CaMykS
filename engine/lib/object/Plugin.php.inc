<?php
/**
 * @brief Plugin object
 * <br />Parent object for Module, Input, Template, Theme
 * @details Engine / Object Library
 * @file engine/lib/object/Plugin.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Jun 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Plugin class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
abstract class Plugin {
    /**
     * @var string $name
     * @brief Plugin name.
     */
    public $name;

    /**
     * @var string $version
     * @brief Plugin version.
     */
    public $version;

    /**
     * @var boolean $active
     * @brief Plugin installation status.
     */
    public $active = false;

    /**
     * @var string $plugin_package
     * @brief Plugin package.
     */
    public $plugin_package = '';

    /**
     * @var string $plugin_type
     * @brief Plugin type.
     */
    public $plugin_type;

    /**
     * @var string $object_type
     * @brief Plugin type.
     */
    public $object_type;

    /**
     * @var string $plugin_path
     * @brief Plugin path.
     */
    public $plugin_path;

    /**
     * @var string $plugin_site_path
     * @brief Plugin site path (for element overwriting).
     */
    public $plugin_site_path;

    /**
     * @var string $plugin_var_path
     * @brief Plugin var path.
     */
    public $plugin_var_path;

    /**
     * @var string $plugin_url
     * @brief Plugin URL.
     */
    public $plugin_url;

    /**
     * @var string $plugin_site_url
     * @brief Plugin site URL (for element overwriting).
     */
    public $plugin_site_url;

    /**
     * @var string $plugin_var_url
     * @brief Plugin var URL.
     */
    public $plugin_var_url;

    /**
     * @var string $path_type
     * @brief Plugin path type.
     */
    public $path_type;

    /**
     * @var string $author_name
     * @brief Plugin author name.
     */
    public $author_name;

    /**
     * @var string $author_mail
     * @brief Plugin author email.
     */
    public $author_mail;

    /**
     * @var string $author_group
     * @brief Plugin author group.
     */
    public $author_group;

    /**
     * @var string $plugin_dependencies
     * @brief Plugin dependencies.
     */
    public $plugin_dependencies = array();

    /**
     * Class constructor.
     * @param string $name
     * @param string $plugin_type
     * @param string $path_type
     * @return void
     */
    public function __construct($name, $plugin_type, $path_type) {
        global $camyks;
        /* set title value */
        $this->name = $name;
        /* set default version value */
        $this->version = '1.0';
        /* set type value */
        $this->plugin_type = $plugin_type;
        $this->object_type = $plugin_type;
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
    }

    /**
     * Return version value.
     * @return string
     */
    public function get_version() {
        return $this->version;
    }

    /**
     * Load library file.
     * @param string $library
     * @return boolean success
     */
    public function load_library($library='') {
        global $camyks;

        /* build file path */
        $filePath = $this->plugin_path.'/lib/'.$library.$camyks->file_extension;

        /* load file if exists */
        if (file_exists($filePath))
            return ((require_once($filePath)) == true);
        return false;
    }

    /**
     * Load a file from plugin folder.
     * @param string $file
     * @return boolean success
     */
    public function load_file($file='') {
        if (file_exists($this->plugin_site_path.'/'.$file)) {
            require($this->plugin_site_path.'/'.$file);
            return true;
        } else if (file_exists ($this->plugin_path.'/'.$file)) {
            require($this->plugin_path.'/'.$file);
            return true;
        }
        return false;
    }

    /**
     * Load a file from var plugin folder.
     * @param string $file
     * @return boolean success
     */
    public function load_varFile($file='') {
        $loadfile = $this->plugin_var_path.'/'.$file ;
        if (file_exists ($loadfile) and is_file ($loadfile)) {
            require($loadfile);
        }
    }

    /**
     * Load a file from engine data folder.
     * @param string $file
     * @return void
     */
    public function load_engineFile($file='') {
        global $camyks;
        if (file_exists($camyks->site_engine_url.'/'.$file)) {
            require ($camyks->site_engine_url.'/'.$file);
        } elseif (file_exists($camyks->camyks_engine_path.'/'.$file)) {
            require ($camyks->camyks_engine_path.'/'.$file);
        }
    }

    /**
     * Return a file URL from engine data folder.
     * @param string $file
     * @param integer $path
     * @parblock - Available values for path are <br />
     * \e 0 Default <br />
     * \e 1 Absolute <br />
     * \e 2 Relative <br />
     * @endparblock
     * @return void
     */
    public function get_engineFileURL($file='', $path=false) {
        global $camyks;

        switch ($path) {
            case 2: $baseURL = ''; break;
            case true: case 1: $baseURL = $camyks->get_rootBaseURL('absolute');  break;
            case 0: default : $baseURL = $camyks->get_rootBaseURL($path); break;
        }

        if (file_exists($camyks->site_engine_url.'/'.$file)) {
            return $baseURL.$camyks->site_engine_url.'/'.$file;
        } elseif (file_exists($camyks->camyks_engine_path.'/'.$file)) {
            return $baseURL.$camyks->camyks_engine_path.'/'.$file;
        }
        return '';
    }

    /**
     * Return plugin file URL.
     * @param string $file
     * @param integer $path
     * @parblock - Available values for path are <br />
     * \e 0 Default <br />
     * \e 1 Absolute <br />
     * \e 2 Relative <br />
     * @endparblock
     * @param string $default
     * @return string
     */
    public function get_fileURL ($file='', $path=null, $default='') {
        global $camyks;

        switch ($path) {
            case 2: $baseURL = ''; break;
            case true: case 1: $baseURL = $camyks->get_rootBaseURL('absolute');  break;
            case 0: default : $baseURL = $camyks->get_rootBaseURL($path); break;
        }

        /* get file url in site plugin folder */
        if (file_exists ($this->plugin_site_path.'/'.$file))
            return $baseURL.$this->plugin_site_url.'/'.$file;
        /* get file url in plugin folder */
        if (file_exists ($this->plugin_path.'/'.$file))
            return $baseURL.$this->plugin_url.'/'.$file;
        /* get default file url */
        return $default;
    }

    /**
     * Return plugin var file URL.
     * @param string $file
     * @param boolean $path
     * @param string $default
     * @return string
     */
    public function get_varFileURL ($file='', $path=false, $default='') {
        global $camyks;

        switch ($path) {
            case 2: $baseURL = ''; break;
            case true: case 1: $baseURL = $camyks->get_rootBaseURL('absolute');  break;
            case 0: default : $baseURL = $camyks->get_rootBaseURL($path); break;
        }

        /* get file url in plugin folder */
        if (file_exists ($this->plugin_var_path.'/'.$file))
            return $baseURL.$this->plugin_var_url.'/'.$file;
        return $default;
    }

    /**
     * Return file path.
     * @param string $file
     * @return string
     */
    public function get_filePath($file='') {
        if (file_exists($this->plugin_site_path.'/'.$file)) {
            return $this->plugin_site_path.'/'.$file ;
        } else if (file_exists ($this->plugin_path.'/'.$file)) {
            return $this->plugin_path.'/'.$file ;
        }
        return '';
    }

    /**
     * Return file from var plugin folder.
     * @param string $file
     * @return string
     */
    public function get_varFilePath($file='') {
        if (file_exists ($this->plugin_var_path.'/'.$file)) {
            return $this->plugin_var_path.'/'.$file ;
        } else {
            return $this->plugin_var_path.'/';
        }
    }

    /***************** HTML PAGE HEADER METHODS ***********************/

    /**
     * Add a redirection to given page URL.
     * @param integer $time the timeout in second
     * @param string $url the url to target
     * @return void
     */
    protected function set_redirect($time, $url = '') {
        global $camyks;
        if (is_string($time)) {
            $url = $time;
            $time = $camyks->get_confValue('ModuleActionDelay');
        }
        $camyks->HTMLPage->set_redirect($time, $url);
    }

    /**
     * Add a meta tag to the page.
     * @param string $name
     * @param string $content
     * @param string $method
     * @return void
     */
    protected function add_meta($name, $content, $method='name') {
        global $camyks;
         $camyks->HTMLPage->add_meta ($name, $content, $method);
    }

    /***************** JS & CSS METHODS ******************/

    /**
     * Add a plugin Javascript file to the page.
     * @param string $file
     * @return void
     */
    public function add_JSFile($file) {
        global $camyks;
        if ($this->path_type == 'camyks')
            $camyks->HTMLPage->add_JSFile($camyks->camyks_plugin_url.'/'.$this->plugin_type.'/'.$this->name.'/js/'.$file);
        else
            $camyks->HTMLPage->add_JSFile('plugin/'.$this->plugin_type.'/'.$this->name.'/js/'.$file);
    }

    /**
     * Add an engine Javascript file to the page.
     * @param string $file
     * @return void
     */
    public function add_JSEngineFile($file) {
        global $camyks;
        $camyks->HTMLPage->add_JSFile($camyks->get_dataFilePath('js/'.$file));
    }

    /**
     * Add an external javascript file to the page.
     * @param string $file
     * @return void
     */
    public function add_JSExternFile($file) {
        global $camyks;
        $camyks->HTMLPage->add_JSFile($file);
    }

    /**
     * Add a Javascript script to the page.
     * @param string $script
     * @param boolean $unique
     * @return void
     */
    public function add_JSScript($script, $unique=false) {
        global $camyks;
        $camyks->HTMLPage->add_JSScript($script, $unique);
    }

    /**
     * Add a Javascript pre script to the page.
     * @param string $script
     * @param boolean $unique
     * @return void
     */
    public function add_JSPreScript($script, $unique=false) {
        global $camyks;
        $camyks->HTMLPage->add_JSPreScript($script, $unique);
    }

    /**
     * Add a Javascript script to the page events.
     * @param string $event
     * @param string $script
     * @param boolean $unique
     * @return void
     */
    public function add_JSWindowEventScript($event, $script, $unique=false) {
        global $camyks;
        $camyks->HTMLPage->add_JSWindowEventScript($event, $script, $unique);
    }

    /**
     * Add a Javascript script to the page load event.
     * @param string $script
     * @param boolean $unique
     * @return void
     */
    public function add_JSLoadScript($script, $unique=false) {
        $this->add_JSWindowEventScript('load', $script, $unique);
    }

    /**
     * Add a Javascript script to the page unload event.
     * @param string $script
     * @param boolean $unique
     * @return void
     */
    public function add_JSUnloadScript($script, $unique=false) {
        $this->add_JSWindowEventScript('unload', $script, $unique);
    }

    /**
     * Add a CSS style file to the page.
     * @param string $file
     * @param string $media
     * @param string $condition
     * @return void
     */
    public function add_styleFile($file, $media='', $condition='') {
        global $camyks;

        if ($this->get_filePath('css/'.$file, false) != false)
            $camyks->HTMLPage->add_styleFile($this->get_fileURL('css/'.$file, 2), $media, $condition);
        elseif ($this->get_filePath($file, false) != false)
            $camyks->HTMLPage->add_styleFile($this->get_fileURL($file, 2), $media, $condition);
    }

    /**
     * Add a CSS style script to the page.
     * @param string $css
     * @return void
     */
    public function add_styleScript($css) {
        global $camyks;
        $camyks->HTMLPage->add_styleScript($css);
    }

    /**
     * Add a CSS style file to be included in the page.
     * @param string $file
     * @return void
     */
    public function add_styleIncludedFile($file) {
        global $camyks;
        $camyks->HTMLPage->add_styleIncludedFile($file);
    }

    /**
     * Add an external javascript file to the page.
     * @param string $file
     * @param string $media
     * @param string $condition
     * @return void
     */
    public function add_StyleExternFile($file, $media='', $condition='') {
        global $camyks;
        $camyks->HTMLPage->add_styleFile($file, $media, $condition);
    }

    /**
     * Add RSS Feed link.
     * @param string $title
     * @param string $url
     * @return void
     */
    public function set_RSSFeed($title, $url) {
        global $camyks;
        $camyks->HTMLPage->add_RSSFeed($title, $url);
    }

    /**
     * Add extra texts to page header
     * @param string $content
     * @return void
     */
    public function add_headerExtra($content='') {
        global $camyks;
        $camyks->HTMLPage->add_headerExtra($content);
    }

    /***************** INSTALL/UNINSTALL METHODS ****************/

    /**
     * Install plugin.
     * @return boolean
     */
    public function install() {
        global $camyks;
        $camyks->log_information($this, 'Installation Successfull', '');
        return true;
    }

    /**
     * Uninstall plugin.
     * @return boolean
     */
    public function uninstall() {
        $camyks->log_information($this, 'Uninstall Successfull', '');
        return true;
    }

    /**
     * Update plugin.
     * @return boolean
     */
    public function update($version, $more='') {
        global $camyks;
        if (isset($camyks->modules['Admin_PluginManager']) and $camyks->modules['Admin_PluginManager']->update_pluginVersion($this->name, $this->plugin_type, $this->version)) {
            $camyks->log_information($this, 'Update from '.$version.' to version '.$this->version.' successful', $more);
            return true;
        }
        return false;
    }

    /* locales related methods */

    /**
     * Load language dictionnary file.
     * @param string $more
     * @param string $lg
     * @return void
     */
    public function add_translation($more='', $lg=null) {
        global $camyks;
        $camyks->add_translation($this->plugin_path.'/locale'.$more, $lg);
    }

    /**
     * Return locale value.
     * @param string $value
     * @param mixed $data
     * @return string
     */
    public function get_translation($value, $data=null) {
        global $camyks;
        return $camyks->get_translation(strtolower($this->name).'_'.$value, $data);
    }
    
    /**
     * Load available language files for the plugin
     * @return void
     */
    public function get_languages() {
        $this->languages = language_getDictionnaryList($this->plugin_path.'/locale');
    }

    /* dependencies management methods */

    /**
     * Add a dependency.
     * @param string $plugin
     * @param string $type
     * @param string $version
     * @param boolean $mandatory
     * @return void
     */
    protected function add_dependency($plugin, $type, $version='1.0', $mandatory=false) {
        $this->plugin_dependency[] = array(
            'plugin'    => $plugin,
            'type'      => $type,
            'version'   => $version,
            'mandatory' => $mandatory,
        );
    }

    /**
     * Build dependencies list
     * @return boolean success
     */
    protected function set_dependencies() {
        return true;
    }

    /* shared object management */

    /**
     * Register this plugin to be accessed by any other.
     * @param string $name
     * @return boolean success
     */
    protected function register_asSharedObject($name) {
        global $camyks;
        return $camyks->register_sharedObject($name, $this);
    }

    /**
     * Return requested shared object.
     * @param string $name
     * @return Object
     */
    protected function &get_sharedObject($name) {
        return $camyks->get_sharedObject($name);
    }

    /* extensions management methods */

    /**
     * Register plugin as extension to another.
     * @param string $plugin
     * @return void
     */
    protected function register_asExtension($plugin) {
        global $camyks;
        $camyks->register_asExtension($plugin, $this->name, $this->plugin_type);
    }

    /**
     * Return registered extensions.
     * @return array
     */
    protected function get_registeredExtensions() {
        global $camyks;
        return $camyks->get_registeredExtensions($this->name);
    }

    /* CaMykS event handler management methods */

    /**
     * Register plugin as handler for CaMykS event.
     * @param string $event
     */
    protected function register_asCaMykSEventHandler($event) {
        global $camyks;
        $camyks->register_eventHandler($event, $this);
    }

    /**
     * Execute handler on CaMykS initialisation.
     * @return void
     */
    public function execute_onCaMykSInitialise() {}

    /**
     * Execute handler on CaMykS page load.
     * @return void
     */
    public function execute_onCaMykSPageLoad() {}

    /**
     * Execute handler on body opening.
     * @return string
     */
    public function execute_onCaMykSBodyOpen() {return '';}

    /**
     * Execute handler on body closing.
     * @return string
     */
    public function execute_onCaMykSBodyClose() {return '';}

    /**
     * Execute handler on camyks terminate.
     * @return void
     */
    public function execute_onCaMykSTerminate() {}
    
    /* Request mode methods */
    
    /**
     * Return HTML request mode link.
     * @param array $params
     * @return string
     */
    public function get_requestLink($params=array()) {
        global $camyks;

        $params = array_merge(array($this->plugin_type=>$this->name), $params);
        return $camyks->get_requestLink($params);
    }
    
    /**
     * Return JavaScript request mode link.
     * @param array $params
     * @return string
     */
    public function get_requestJSLink($params=array()) {
        global $camyks;

        $params = array_merge(array($this->plugin_type=>$this->name), $params);
        return $camyks->get_requestJSLink($params);
    }

    /**
     * Execute module in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* throw a fatal error, if not overwritten */
        $camyks->add_generic_translation();
        $camyks->throwFatalError(array(
            'title'         => $camyks->get_translation('error_fatalerror'),
            'description'   => $camyks->get_translation('error_plugin_doesnt_support_requests_desc'),
            'content1'      => $camyks->get_translation('error_plugin_doesnt_support_requests_content'),
            'back_title'    => $camyks->get_translation('error_plugin_doesnt_support_requests_back_title'),
            'back_link'     => $camyks->get_confValue('url'),
        ));
    }

    /* Deprecated methods */

    /**
     * Alias to get_varFilePath method.
     * @see get_varFilePath()
     * @param string $file
     * @return void
     * @deprecated Use get_varFilePath instead.
     */
    public function get_varFile($file) {$this->get_varFilePath($file);}
}
?>
