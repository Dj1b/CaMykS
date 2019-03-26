<?php
/**
 * @brief CaMykS CMS master class.
 * @details Engine / Main Object
 * @file Camyks.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.12
 * @date Creation: Jun 2005
 * @date Modification: Mar 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * @def CAMYKS_MODE_SITE
 */
define('CAMYKS_MODE_SITE',      0);

/**
 * @def CAMYKS_MODE_ADMIN
 */
define('CAMYKS_MODE_ADMIN',     1);

/**
 * @def CAMYKS_MODE_REQUEST
 */
define('CAMYKS_MODE_REQUEST',   2);

/**
 * @def CAMYKS_MODE_MANAGER
 */
define('CAMYKS_MODE_MANAGER',   3);

/**
 * @def CAMYKS_MODE_INSTALL
 */
define('CAMYKS_MODE_INSTALL',   4);

/**
 * @def CAMYKS_NAME
 */
define('CAMYKS_NAME',           'CaMykS');

/**
 * CaMykS master class.
 */
final class Camyks {

    /**
     * @var string $name
     * @brief CaMykS object name.
     */
    public $name = CAMYKS_NAME;

    /**
     * @var string $title
     * @brief CaMykS object title.
     */
    public $title = CAMYKS_NAME;

    /**
     * @var string $object_type
     * @brief CaMykS object type.
     */
    public $object_type = CAMYKS_NAME;

    /**
     * @var string $version
     * @brief CaMykS current version.
     */
    public $version;

    /**
     * @var integer $last_modification_date
     * @brief CaMykS last modification date.
     */
    public $last_modification_date;

    /**
     * @var string $site_name
     * @brief CaMykS current site name.
     */
    public $site_name;

    /**
     * @var string $mode
     * @brief CaMykS running mode (admin / site / manager / install).
     */
    public $mode;

    /**
     * @var array $trads
     * @brief CaMykS merged locales.
     */
    public $trads = array();

    /**
     * @var string $camyks_path
     * @brief CaMykS path.
     */
    public $camyks_path;

    /**
     * @var string $camyks_plugin_path
     * @brief CaMykS plugins path.
     */
    public $camyks_plugin_path;

    /**
     * @var string $camyks_plugin_url
     * @brief CaMykS plugins base url.
     */
    public $camyks_plugin_url;

    /**
     * @var string $camyks_engine_path
     * @brief CaMykS libraries path.
     */
    public $camyks_engine_path;

    /**
     * @var string $site_path
     * @brief Current site path.
     */
    public $site_path;

    /**
     * @var string $site_plugin_path
     * @brief Current site plugins path.
     */
    public $site_plugin_path;

    /**
     * @var string $site_plugin_url
     * @brief Current site plugins base url.
     */
    public $site_plugin_url;

    /**
     * @var string $site_cache_path
     * @brief Current site cache path.
     */
    public $site_cache_path;

    /**
     * @var string $site_data_url
     * @brief Current site data folder base url.
     */
    public $site_data_url;

    /**
     * @var string $site_base_url
     * @brief Current site base url.
     */
    public $site_base_url;

    /**
     * @var string $db_table_prefix
     * @brief Database tables prefix.
     */
    public $db_table_prefix;

    /**
     * @var Database_connection $db_conn
     * @brief Main database connection
     */
    public $db_conn;

    /**
     * @var string $file_extension
     * @brief Files extension.
     */
    public $file_extension;

    /**
     * @var array $modules
     * @brief CaMykS modules.
     */
    public $modules;

    /**
     * @var array $templates
     * @brief CaMykS templates.
     */
    public $templates;

    /**
     * @var array $themes
     * @brief CaMykS themes.
     */
    public $themes;

    /**
     * @var array $inputs
     * @brief CaMykS inputs.
     */
    public $inputs;

    /**
     * @var Theme $theme
     * @brief CaMykS current theme.
     */
    public $theme;

    /**
     * @var string $current_language
     * @brief CaMykS current language.
     */
    public $current_language;

    /**
     * @var array $cache
     * @brief CaMykS cache
     */
    public $cache = array();

    /**
     * @var array $shared_data
     * @brief CaMykS shared data.
     */
    public $shared_data = array();

    /**
     * @var array $sharedObjects
     * @brief CaMykS shared objects.
     */
    public $sharedObjects = array();

    /**
     * @var array $plugin_extensions
     * @brief CaMykS plugins extensions.
     */
    public $plugin_extensions = array();

    /**
     * @var HTMLPage $HTMLPage
     * @brief CaMykS HTML page
     */
    public $HTMLPage;

    /**
     * @var ContentPage $contentPage
     * @brief CaMykS content page.
     */
    public $contentPage;

    /**
     * @var string $previewMode
     * @brief CaMykS current preview mode.
     */
    public $previewMode;

    /**
     * @var string $deviceMode
     * @brief CaMykS current device mode.
     */
    public $deviceMode;

    /**
     * @var array $openedDBonnections
     * @brief CaMykS opened database connections.
     */
    private $openedDBonnections = array();

    /**
     * @var array $eventsHandlers
     * @brief CaMykS event handlers.
     */
    private $eventsHandlers;

    /**
     * @var boolean $falseRef
     * @brief CaMykS false value as reference
     */
     private $falseRef = false;

     /**
      * @var mixed $adminUser
      * @brief Current logged admin user
      */
     public $adminUser = false;

    /**
     * CaMykS Constructor.
     * @param array $site_conf
     * @param integer $mode
     */
    public function __construct($site_conf, $mode=CAMYKS_MODE_SITE) {

        /* initialise some variables */
        $this->site_conf = $site_conf;
        $this->site_name = $site_conf['site_name'];
        $this->camyks_path = realpath($site_conf['engine_path']);
        if (isset($this->site_conf['installed']) and $this->site_conf['installed']==1) {
            $this->mode = $mode;
        } else {
            $this->mode = CAMYKS_MODE_INSTALL;
        }
        $this->eventsHandlers = array('onInitialise'=>array(), 'onPageLoad'=>array(), 'onBodyOpen'=>array(), 'onBodyClose'=>array(), 'onTerminate'=>array());

        /* load request vars */
        $this->benchMode = $this->get_executionVariable('_cBench');

        /* register shutdown function    */
        register_shutdown_function(array($this, 'terminate'));
    }

    /* methods */

    /**
     * Execute CaMykS.
     * @return void
     */
    public function execute() {
        /* init camyks object */
        $this->initialise();
        /* build content with CaMykS engine object */
        $this->get_pageContent();
    }

    /******************** INIT **************************/

    /**
     * CaMykS global initialisation.
     * @return void
     */
    public function initialise() {
        /* get generic initialisation */
        $this->get_genericInit();

        /* get specific initialisation */
        switch ($this->mode) {
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

        /* run onInitialise event handlers */
        $this->run_eventHandlers('onInitialise');
    }

    /**
     * CaMykS generic initialisation.
     * @return void
     */
    private function get_genericInit() {
        /* get camyks configuration file */
        $this->get_confFiles();

        /* get camyks needed pathes */
        $this->get_camyksPathes();

        /* get camyks needed lib files */
        $this->get_libs();

        /* get site site needed pathes */
        $this->get_sitePathes();

        /* check bench to start */
        if ($this->benchMode) {
            $this->benchMode = new CBench(array('output'=>$this->benchMode));
            $this->benchMode->start('CaMykS mode initialisation');
        }
    }

    /**
     * Initialise CaMykS in site mode.
     * @return void
     */
    public function get_siteInit() {
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
        $this->check_siteConf();

        /* check plugins version */
        $this->check_plugins();
    }

    /**
     * Initialise CaMykS in admin mode.
     * @return void
     */
    public function get_adminInit() {
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
        $this->check_plugins();

        /* check admin user */
        $this->get_adminUser();
    }

    /**
     * Initialise CaMykS in request mode.
     * @return void
     */
    private function get_requestInit() {
        /* do nothing, to be set in plugin execution */
    }

    /**
     * Initialise CaMykS in install mode.
     * @return void
     */
    private function get_installInit() {
        /* language */
        $this->get_currentLanguage('admin');

        /* get minimal plugin lists */
        $this->load_neededPlugins();

        /* load installer plugin */
        $this->modules['Tool_Installer'] = module_get('Tool_Installer');

        /* get generic & admin conf */
        $this->check_adminConf();

        /* get global language */
        $this->add_generic_translation();

        /* prepare page */
        $this->HTMLPage = new HTMLPage();

        /* initialise installer module */
        if (isset($this->modules['Tool_Installer']))
            $this->modules['Tool_Installer']->init_admin();
        else {
            /* throw fatal error */
            $this->throwFatalError(array(
                'title'         => 'Installer Module not found',
                'description'   => 'Installer Module not found',
                'error_link'    => 'http://www.camyks.net',
                'error_title'   => 'Check CaMykS website for more informations.',
           ));
        }
    }

    /**
     * Initialise CaMykS in manager mode.
     * @return void
     */
    private function get_managerInit() {
        /* to do */
    }

    /******************** CONFIGURATION *****************/

    /**
     * get CaMykS conf files
     * @return void
     */
    private function get_confFiles() {
        /* load global config */
        require_once ($this->camyks_path.'/engine/etc/dynamic.php.inc');

        /* apply time zone */
        date_default_timezone_set($this->get_confValue('TimeZone', 'Europe/Paris'));

        /* load static config */
        require_once ($this->camyks_path.'/engine/etc/static.php.inc');

        /* merge engine and site configs */
        foreach ($this->site_conf as $name => $value)
            if (!isset($this->_conf[$name]) or trim($value) != '')
                $this->_conf[$name] = $value;
    }

    /**
     * Initialise required CaMykS pathes.
     * @return void
     */
    private function get_camyksPathes() {
        /* check camyks installation mode */
        if (preg_match('/^camyks/', $this->get_confValue('engine_path')))
            $this->_installationMode = 'dedicated';
        else
            $this->_installationMode = 'shared';

        /* set camyks plugin full path */
        $this->camyks_plugin_path = $this->camyks_path.'/'.$this->plugin_folder;

        /* set camyks plugin full url */
        if ($this->_installationMode=='shared')
            $this->camyks_plugin_url = 'c'.$this->plugin_folder;
        else
            $this->camyks_plugin_url = 'camyks/'.$this->plugin_folder;

        /* set camyks lib full path */
        $this->camyks_engine_path = $this->camyks_path.'/'.$this->engine_folder;
    }

    /**
     * Load all internal libs files.
     * @return void
     */
    private function get_libs() {
        /* start capture extra codes */
        ob_start();

        /* load all object library */
        require_once($this->camyks_engine_path.'/lib/object/CBench.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/CDBConnection.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/CImage.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/CMail.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/CRequestAnswer.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/Database_connection.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/HTMLForm.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/HTMLPage.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/Plugin.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/Input.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/Module.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/Template.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/Theme.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/PluginConfig.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/ModuleConfig.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/PluginConfigItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/ModuleLibrary.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/ModuleLibraryItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/ModuleLibraryJoin.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/MLDatabaseItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/MLDatabaseLocalizedItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/MLTextItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/MLTextLocalizedItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/MLFileItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/MLFileLocalizedItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/MLTemporaryItem.php.inc');
        require_once($this->camyks_engine_path.'/lib/object/FSFile.php.inc');

        /* load all tool library */
        require_once($this->camyks_engine_path.'/lib/tool/array.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/client.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/cookie.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/countries.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/data.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/date.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/file.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/folder.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/html.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/http.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/input.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/language.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/mail.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/module.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/password.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/plugin.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/shell.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/statics.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/string.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/template.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/theme.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/url.php.inc');
        require_once($this->camyks_engine_path.'/lib/tool/xml.php.inc');

        /* load site libraries */
        if (file_exists($this->site_path.'./assets/lib')) {
            foreach (glob ($this->site_path.'./assets/lib/*.php.inc') as $filename) {
                require_once($filename);
            }
        }

        /* clear extra codes */
        ob_end_clean();
    }

    /**
     * Initialise needed site pathes.
     * @return void
     */
    private function get_sitePathes() {
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
        if ($this->_installationMode == 'shared')
            $this->site_data_url = 'cdata';
        else
            $this->site_data_url = 'camyks/engine/data';
        /* set site engine path */
        $this->site_engine_url = 'assets';

        /* set site base url */
        $this->site_base_url = $this->get_defaultBaseURL();

        /* update included pathes */
        set_include_path(get_include_path().PATH_SEPARATOR
                 .$this->camyks_engine_path.'/lib/object/'.PATH_SEPARATOR
                 .$this->camyks_engine_path.'/lib/tool/'.PATH_SEPARATOR
                 .$this->camyks_engine_path.'/lib/external/'.PATH_SEPARATOR
                 .$this->camyks_engine_path.'/lib/external/PEAR/');
    }

    /**
     * Check security.
     * @param string $mode
     * @return void
     */
    private function check_security($mode) {
        if (!in_array($mode, array('site', 'admin')))
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

    /**
     * Check site configuration.
     * @return void
     */
    private function check_siteConf() {
        /* get site theme from configuration */
        $theme = $this->get_confValue('site_default_theme', 'GreyStyle');

        /* check theme */
        if (isset($this->themes[$theme])) {
            $this->theme = &$this->themes[$theme];
        } else {
            /* error */
            $this->throwFatalError(array(
                'title'         => 'Configuration file error',
                'description'   => 'Configuration file error',
                'content1'      => 'Check your site configuration file for the "site_default_theme" value.',
                'content2'      => 'This value must be set to the name of an activated theme.',
                'error_link'    => 'http://www.camyks.net',
                'error_title'   => 'Check CaMykS website for more informations.',
            ));
        }

        /* check preview mode value */
        $this->previewMode = (isset($_REQUEST['preview']) and $_REQUEST['preview']=='forced' and $this->check_adminUser());

        /* check device mode value */
        $this->check_deviceMode();
    }

    /**
     * Check admin configuration.
     * @return void
     */
    private function check_adminConf() {
        /* get admin theme from configuration */
        $theme = $this->get_confValue('admin_default_theme', 'IndigoFlatStyle');

        /* check theme */
        if (isset($this->themes[$theme])) {
            $this->theme = &$this->themes[$theme];
        } else {
            /* throw error */
            $this->throwFatalError(array(
                'title'=>'Configuration file error',
                'description'=>'Configuration file error',
                'content1'=>'Check your site configuration file for the "admin_default_theme" value.',
                'content2'=>'This value must be set to the name of an activated theme.',
                'content3'=>'The default theme value is "IndigoFlatStyle". ',
                'error_link'=>'http://www.camyks.net',
                'error_title'=>'Check CaMykS website for more informations.',
            ));
        }
    }

    /**
     * Define/update configuration value.
     * @param string $confName
     * @param mixed $value
     * @return void
     */
    public function set_confValue($confName, $value='') {
        $this->_conf[$confName] = $value;
    }

    /**
     * Return a configuration value.
     * @param string $confName
     * @param mixed $default
     * @return mixed
     */
    public function get_confValue($confName, $default='') {
        if (isset($this->_conf[$confName]))
            return $this->_conf[$confName];
        if (isset($this->modules['Admin_Site']))
            return $this->modules['Admin_Site']->get_confDefaultValue($confName, $default);
        return $default;
    }

    /**
     * Update configuration file.
     * @param array $params
     * @return boolean result
     */
    public function update_siteConfFile($params=array()) {

        /* check admin mode and admin user connected */
        if ($this->mode !== CAMYKS_MODE_ADMIN or !$this->check_adminUser())
            return false;

        /* update camyks site configuration */
        $this->site_conf = array_merge($this->site_conf, $params);

        /* build configuration file content */
        $content = file_getPHPFileHeader('site configuration file', '1.0');
        $content .= '$conf = ' . var_export($this->site_conf, true) . ';';
        $content .= file_getPHPFileFooter();

        /* write file */
        file_write(realpath('./etc/site.php.inc'), $content);
        return true;
    }

    /******************** LOCALISATION ******************/

    /**
     * Load dictionnary from its path.
     * @param string $path
     * @param string $lang
     * @return void
     */
    public function add_translation($path, $lang=null) {
        /* check language */
        if ($lang == null)
            $lang = $this->current_language;

        /* build full path */
        $file = $path . '/translation_'.$lang.$this->file_extension;

        if (file_exists($file)){
            /* load file for given language */
            require ($file);
        } else {
            /* build full path for default language */
            $file = $path . '/translation_'.$this->default_language.$this->file_extension;
            if (file_exists ($file)) {
                /* load file for default language */
                require_once ($file);
            } else {
                /* TO DO */
                /* send an error to a global object : current language & default language file not found */
            }
        }
    }

    /**
     * Load an internal dictionnary.
     * @param string $more
     * @param string $language
     * @return void
     */
    public function add_generic_translation($more='', $language=null) {
        $this->add_translation($this->camyks_engine_path.'/locale/'.$more, $language);
    }

    /**
     * Return localisation values.
     * @param string $string
     * @param mixed $data
     * @return string
     */
    public function get_translation($string, $data=array()) {
        $string = strtolower ($string);
        if (isset($this->trads[$string]))
            return vsprintf($this->trads[$string], $data);
        return $string;
    }

    /**
     * Manage the language to use.
     * @param string $type
     * @return void
     */
    public function get_currentLanguage($type) {
        /* get available language list */
        $list = $this->get_confValue($type.'_languages');
        if (!is_array($list))
          $list = array();

        /* load language from header */
        $newlg = '';
        if (isset($_REQUEST['_clg_'])) {
            if ($type == 'admin')
                $newlg =  $_REQUEST['_clg_'];
            elseif (strlen($_REQUEST['_clg_']) == 3)
                $newlg = substr($_REQUEST['_clg_'], 1, 3);
            else
                $newlg = $_REQUEST['_clg_'];
        }

        if (count($list) == 0 or $newlg == '' or !in_array($newlg, $list)) {
            if ($this->get_sessionValue($type.'language') != null) {
                $l = $this->get_sessionValue($type.'language');
            } else if ($type == 'admin' and ($lc = cookie_get('adminlanguage')) != null) {
                $l = $lc;
            } else if (isset($_SERVER['HTTP_ACCEPT_LANGUAGE']) and in_array (($lc = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2)), $list)) {
                $l = $lc;
            } else {
                $l = $this->get_confValue($type.'_default_language', 'en');
            }
        } else {
            $l = $newlg;
        }

        /* set the language to use */
        if ($type == 'admin')
            cookie_save('adminlanguage', $l, 90);
        $this->set_sessionValue($type.'language', $l);
        $this->current_language = $l;
        $loc = setlocale(LC_ALL, language_getLocale($l, $this->get_confValue('encoding')));
    }

    /******************** ENCODING **********************/

    /**
     * Return decoded value.
     * @param mixed $v
     * @return mixed
     */
    public function decode_value($v) {
        switch ($this->get_confValue('encoding')) {
            case 'utf8':
                return utf8_decode(stripslashes($v));
                break;
            default:
                return stripslashes($v);
        }
    }

    /**
     * Return encoded value.
     * @param mixed $v
     * @return mixed
     */
    public function encode_value($v) {
        switch ($this->get_confValue('encoding')) {
            case 'utf8':
                return addslashes(utf8_encode($v));
                break;
            default:
                return addslashes($v);
        }
    }

    /**
     * Return HTML value for encoding.
     * @return string
     */
    public function get_htmlEncodingValue() {
        switch ($this->get_confValue('encoding')) {
            case 'utf8':
                return 'UTF-8';
                break;
            default:
                return 'UTF-8';
        }
    }

    /**
     * Return SQL value for encoding.
     * @return string
     */
    public function get_mysqlEncodingValue() {
        switch ($this->get_confValue('encoding')) {
            case 'utf8':
                return 'utf8';
                break;
            default:
                return 'utf8';
        }
    }

    /******************** PLUGINS ***********************/

    /**
     * Get all available and active plugins.
     * @return void
     */
    private function get_plugins() {

        /* load plugin manager */
        $pluginManager = module_get('Admin_PluginManager', 'camyks');
        if ($pluginManager != false) {
            /* load active plugin list from plugin manager */
            $plugins = $pluginManager->get_pluginList(array('status'=>1));

            /* prepare lists */
            $this->modules = array();
            $this->themes = array();
            $this->templates = array();
            $this->inputs = array();

            /* prevent errors display in plugins */
            ob_start();

            /* load plugin objects */
            foreach ($plugins as $data) {
                switch ($data['type']) {
                    /* load module */
                    case 'module':
                        $m = module_get($data['plugin'], $data['location']);
                        if ($m !== false) {
                            $m->_installedVersion = $data['version'];
                            $this->modules[$data['plugin']] = $m;
                        }
                        break;
                    /* load theme */
                    case 'theme':
                        $t = theme_get($data['plugin'], $data['location']);
                        if ($t !== false) {
                            $t->_installedVersion = $data['version'];
                            $this->themes[$data['plugin']] = $t;
                        }
                        break;
                    /* load template */
                    case 'template':
                        $t = template_get($data['plugin'], $data['location']);
                        if ($t !== false) {
                            $t->_installedVersion = $data['version'];
                           $this->templates[$data['plugin']] = $t;
                        }
                        break;
                    /* load input */
                    case 'input':
                        $i = input_get($data['plugin'], $data['location']);
                        if ($i !== false) {
                            $i->_installedVersion = $data['version'];
                            $this->inputs[$data['plugin']] = $i;
                        }
                        break;
                }
            }

            /* stop catching errors */
            ob_clean();

            /* check for plugin updates */
            plugin_checkUpdates();
        } else {
            /* connection failed, throw fatal error */
            $this->throwFatalError(array(
                'title'         => 'Fatal Error',
                'description'   => 'Connection to plugin database failed',
                'content1'      => 'CaMykS is not able to get plugins from your website.',
                'error_link'    => 'http://www.camyks.net',
                'error_title'   => 'Check CaMykS website for more informations.'
            ));
        }
    }

    /**
     * Compare active plugins and required plugins.
     * @return void
     */
    private function check_plugins() {
        /* load needed plugins */
        $this->get_neededPlugins();

        /* check modules */
        foreach ($this->neededModules as $p) {
            if (!isset($this->modules[$p['name']]))
                die ('Plugin '.$p['name'].' is missing.');
            else if ($this->modules[$p['name']]->version < $p['version'])
                die ('CaMykS need version '.$p['version'] . ' of plugin '.$p['name'].', current is '.$this->modules[$p['name']]->version.'.');
        }

        /* check inputs */
        foreach ($this->neededInputs as $p) {
            if (!isset($this->inputs[$p['name']]))
                die ('Plugin '.$p['name'].' is missing.');
            else if ($this->modules[$p['name']]->version < $p['version'])
                die ('CaMykS need version '.$p['version'] . ' of plugin '.$p['name'].', current is '.$this->inputs[$p['name']]->version.'.');
        }

        /* check themes */
        foreach ($this->neededThemes as $p) {
            if (!isset($this->themes[$p['name']]))
                die ('Plugin '.$p['name'].' is missing.');
            else if ($this->themes[$p['name']]->version < $p['version'])
                die ('CaMykS need version '.$p['version'] . ' of plugin '.$p['name'].', current is '.$this->inputs[$p['name']]->version.'.');
        }

        /* check templates */
        foreach ($this->neededTemplates as $p) {
            if (!isset($this->templates[$p['name']]))
                die ('Plugin '.$p['name'].' is missing.');
            else if ($this->templates[$p['name']]->version < $p['version'])
                die ('CaMykS need version '.$p['version'] . ' of plugin '.$p['name'].', current is '.$this->templates[$p['name']]->version.'.');
        }
    }

    /**
     * Load modules list in CaMykS object.
     * @return void
     */
    public function get_modules() {
        $this->modules = array_merge(
            module_getList($this->camyks_plugin_path, 'camyks'),
            module_getList($this->site_plugin_path, 'site')
        );
    }

    /**
     * Load themes list in CaMykS object.
     * @return void
     */
    public function get_themes() {
        $this->themes = array_merge(
            theme_getList($this->camyks_plugin_path, 'camyks'),
            theme_getList($this->site_plugin_path, 'site')
        );
    }

    /**
     * Load templates list in CaMykS object.
     * @return void
     */
    public function get_templates() {
        $this->templates = array_merge(
            template_getList($this->camyks_plugin_path, 'camyks'),
            template_getList($this->site_plugin_path, 'site')
        );
    }

    /**
     * Load inputs list in CaMykS object.
     * @return void
     */
    public function get_inputs() {
        $this->inputs = array_merge(
            input_getList($this->camyks_plugin_path, 'camyks'),
            input_getList($this->site_plugin_path, 'site')
        );
    }

    /**
     * Return module object.
     * @param string $moduleName
     * @return Module
     */
    public function &get_module($moduleName) {
        if (isset($this->modules[$moduleName]))
            return $this->modules[$moduleName];
        return $this->falseRef;
    }

    /**
     * Return theme object.
     * @param string $themeName
     * @return Theme
     */
    public function &get_theme($themeName) {
        if (isset($this->themes[$themeName]))
            return $this->themes[$themeName];
        return $this->falseRef;
    }

    /**
     * return template object.
     * @param string $templateName
     * @return Template
     */
    public function &get_template($templateName) {
        if (isset($this->templates[$templateName]))
            return $this->templates[$templateName];
        return $this->falseRef;
    }

    /**
     * return input object.
     * @param string $inputName
     * @return Input
     */
    public function &get_input($inputName) {
        if (isset($this->inputs[$inputName]))
            return $this->inputs[$inputName];
        return $this->falseRef;
    }

    /**
     * Load needed plugins list from CaMykS configuration.
     * @return void
     */
    public function get_neededPlugins() {
        $file = $this->camyks_engine_path.'/'.$this->conf_folder.'/neededPlugins'.$this->file_extension;
        if (file_exists($file)) {
            require_once ($file);
        } else {
            $this->neededModules = array();
            $this->neededInputs = array();
            $this->neededTemplates = array();
            $this->neededThemes = array();
        }
    }

    /**
     * Load needed plugins.
     * @return void
     */
    private function load_neededPlugins() {
        $this->get_neededPlugins();

        /* load modules */
        foreach ($this->neededModules as $module)
            if (($p = module_get($module['name'])) !== false) $this->modules[$module['name']] = $p;

        /* load themes */
        foreach ($this->neededThemes as $theme)
            if (($p = theme_get($theme['name'])) !== false) $this->themes[$theme['name']] = $p;

        /* load templates */
        foreach ($this->neededTemplates as $template)
            if (($p = template_get($template['name'])) !== false) $this->templates[$template['name']] = $p;

        /* load inputs */
        foreach ($this->neededInputs as $input)
            if (($p = input_get($input['name'])) !== false) $this->inputs[$input['name']] = $p;
    }

    /**
     * Return plugin path case of plugin path type.
     * @param string $path_type
     * @return string
     */
    public function get_pluginPath($path_type) {
        switch ($path_type) {
            case 'camyks' : return $this->camyks_plugin_path;
            case 'site' : return $this->site_plugin_path;
        }
        return '';
    }

    /**
     * Return plugin url case of plugin path type.
     * @param string $path_type
     * @return string
     */
    public function get_pluginURL($path_type) {
        switch ($path_type) {
            case 'camyks' : return $this->camyks_plugin_url;
            case 'site' : return $this->site_plugin_url;
        }
        return '';
    }

    /****************** ADMIN USER *********************/

    /**
     * Load admin user from session.
     * @return void
     */
    public function get_adminUser() {
        /* load current adminUser */
        if (isset($this->modules['Admin_User'])) {
            $this->adminUser = new AdminUser($this->get_sessionValue('admin_user'));
            $this->adminUser->get();
        }
    }

    /**
     * Check if admin user is connected.
     * @return boolean result
     */
    public function check_adminUser() {
        return ($this->adminUser != false and $this->adminUser->login != '');
    }

    /******************** CACHES ***********************/

    /**
     * Return cache file.
     * @param string $title
     * @return mixed
     */
    public function get_cache($title) {
        /* if cache is already loaded, get cached cache value */
        if (isset($this->cache[$title])) {
            return $this->cache[$title];
        }

        /* check if cache file exists */
        $file = $this->site_cache_path.'/'.$title.$this->file_extension;
        if (file_exists ($file)) {
            require_once($file);
            /* check if cache var is correctly set */
            if (isset($cache_value)) {
                $this->cache[ $title ] = file_getUnserializedVar($cache_value);
                return $this->cache[$title];
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

    /**
     * Set cache file.
     * @param string $title
     * @param mixed $content
     * @param string $desc
     * @return void
     */
    public function set_cache($title, $content, $desc = '') {
        $file_path = $this->site_cache_path.'/'.$title.$this->file_extension;

        /* try to open file & write inside */
        if ($file = fopen($file_path, "w")) {
            /* update content */
            $file_content = file_getPHPFileHeader($desc);
            $file_content .= file_getSerializedVar($title, $content);
            $file_content .= file_getPHPFileEnder();

            /* write content to file */
            fputs($file, $file_content);
            fclose($file);
        } else {
            /* TO DO */
            /* cannot save cache file */
        }
    }

    /******************** DEVICE *************************/

    /**
     * Check selected device mode value.
     * @param string $device
     * @return void
     */
    public function check_deviceMode($device='') {
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
            /* define define/format */
            $device = isset($ua['platform_format'])?$ua['platform_format']:'desktop';
            $deviceStatus = 'auto';
        }

        /* check device value */
        if ($device == 'mobile')
            $device = 'handheld';
        elseif (!in_array($device, array('desktop', 'tablet', 'handheld', 'tvset'))) {
            $device = 'desktop';
            $deviceStatus = 'auto';
        }

        /* set device value */
        $this->deviceMode = $device;
        $this->set_sessionValue('deviceMode', $device);
        $this->set_sessionValue('deviceStatus', $deviceStatus);
    }

    /******************** ERRORS *************************/

    /**
     * Stop CaMykS, with an error.
     * @param array $error
     */
    public function throwFatalError($error) {
        /* complete error values */
        $error['site_title'] = $this->get_confValue('site_title', '');

        /* display error */
        $splashError = $this->camyks_engine_path.'/data/html/splash_error.html.inc';
        if (file_exists($splashError)) {
            require_once($splashError);
        } else {
            /* to do */
        }

        /* start closing CaMykS */
        die();
    }

    /******************** LOGS ***************************/

    /**
     * Check is log manager module is available
     * @return boolean result.
     */
    public function are_logsAvailable() {
        return (isset($this->modules['Admin_SystemLogManager']));
    }

    /**
     * Log message in log manager module.
     * @param string $object
     * @param string $action
     * @param string $message
     */
    public function log($object, $action, $message='') {
        if (isset($this->modules['Admin_SystemLogManager']))
            return $this->modules['Admin_SystemLogManager']->write_log($object, $action, $message);
        return false;
    }

    /**
     * Log event in system report module.
     * @param string $type
     * @param Object $object
     * @param string $desc1
     * @param string $desc2
     * @param string $file
     * @param integer $line
     * @return boolean success
     */
    public function log_event($type, &$object, $desc1='', $desc2='', $file='', $line=0) {
        /* add log report */
        if (isset($this->modules['Admin_SystemReport']) and $this->modules['Admin_SystemReport']->is_installed()) {
            $this->modules['Admin_SystemReport']->add_newReport($type, $object, $desc1, $desc2, $file, $line);
        }
        /* always return false */
        return false;
    }

    /**
     * Log sql error in system report module.
     * @param Object $object
     * @param string $sqlquery
     * @param string $file
     * @param integer $line
     * @return boolean success
     */
    public function log_sqlerror(&$object, $sqlquery='', $file='', $line=0) {
        return $this->log_event('SQL Error', $object, $sqlquery, $this->db_conn->get_queryError(), $file, $line);
    }

    /**
     * Log internal error in system report module.
     * @param object $object
     * @param string $desc1
     * @param string $desc2
     * @param string $file
     * @param integer $line
     * @return boolean success
     */
    public function log_internalerror(&$object, $desc1='', $desc2='', $file='', $line=0) {
        return $this->log_event('Internal Error', $object, $desc1, $desc2, $file, $line);
    }

    /**
     * Log information in system report module.
     * @param object $object
     * @param string $desc1
     * @param string $desc2
     * @return boolean success
     */
    public function log_information(&$object, $desc1='', $desc2='') {
        return $this->log_event('Information', $object, $desc1, $desc2);
    }

    /**
     * Log execution error in system report module.
     * @param object $object
     * @param string $desc1
     * @param string $desc2
     * @return boolean success
     */
    public function log_executionerror(&$object, $desc1='', $desc2='') {
        return $this->log_event('Execution Error', $object, $desc1, $desc2);
    }

    /******************** STATS **************************/

    /**
     * Try to update statistic.
     * @param string $name
     * @param string $module
     * @param string $type
     * @param string $main
     * @param string $data1
     * @param strint $data2
     * @param array $params
     * @return void
     */
    public function update_statistic($name='', $module='', $type='', $main='', $data1='', $data2='', $params=array()) {
        if (isset($this->modules['Admin_Statistics'])) {
            $this->modules['Admin_Statistics']->update_statistic($name, $module, $type, $main, $data1, $data2, $params);
        }
    }

    /**
     * Update site statistics.
     * @return void
     */
    public function update_siteStatistics() {
        /* update global statistics in site mode only */
        if ($this->mode != CAMYKS_MODE_SITE)
            return;

        /* update global statistics for visitors only */
        if ($this->check_adminUser()===true)
            return;

        /* update global statistics only if statistic engine is available */
        if (isset($this->modules['Admin_Statistics']))
            $this->modules['Admin_Statistics']->update_siteStatistics();
    }

    /******************** DATABASE ***********************/

    /**
     * Create connection to the database.
     * @return boolean success
     */
    public function get_databaseConnection() {
        if ($this->get_confValue('database_name') != '') {
            $this->db_conn = new Database_connection(
                $this->get_confValue('database_host'),
                $this->get_confValue('database_login'),
                $this->get_confValue('database_pwd'),
                $this->get_confValue('database_driver', '')
            );
            if ($this->db_conn->is_active()) {
                if ($this->db_conn->select($this->get_confValue('database_name'))) {
                    return true;
                } else {
                    /* error : database not found on database server */
                    $error = array(
                        'title'         => 'Database connection failed',
                        'description'   => 'Database connection failed',
                        'content1'      => 'CaMykS was able to connect to database server, but database doesn\'t exist.',
                        'error_link'    => 'http://www.camyks.net',
                        'error_title'   => 'Check CaMykS website for more informations.'
                    );
                }
            } else {
                /* error : database connection failed */
                $error = array(
                    'title'         => 'Database connection failed',
                    'description'   => 'Database connection failed',
                    'content1'      => 'CaMykS was not able to connect to database server.',
                    'content2'      => '- SQL server may be down.',
                    'content3'      => '- Configuration file databases values may be wrong.',
                    'error_link'    => 'http://www.camyks.net',
                    'error_title'   => 'Check CaMykS website for more informations.',
                );
            }
        } else {
            /* error : no database name defined */
            $error = array(
                'title'         => 'Configuration file error',
                'description'   => 'Configuration file error',
                'content1'      => 'Check your site configuration file for the "database_name" value.',
                'error_link'    => 'http://www.camyks.net',
                'error_title'   => 'Check CaMykS website for more informations.'
            );
        }
        $this->throwFatalError($error);
    }

    /**
     * Return database connection.
     * @return Object
     */
    public function &get_dbConnection() {
        return $this->db_conn;
    }

    /**
     * Register an opened connection.
     * @param Object $connection
     * @return void
     */
    public function register_dbConnection(&$connection) {
        $this->openedDBonnections[] = $connection;
    }

    /******************** SESSION    *************************/

    /**
     * Save var to session.
     * @param string $name
     * @param mixed $value
     * @return void
     */
    public function set_sessionValue($name, $value='') {
        $_SESSION[$this->site_name.'_'.$name] = $value;
    }

    /**
     * Get var from session.
     * @param string $name
     * @param mixed $value
     * @return void
     */
    public function get_sessionValue($name, $value = null) {
        if (isset($_SESSION[$this->site_name.'_'.$name]))
            return $_SESSION[$this->site_name.'_'.$name];
        return $value;
    }

    /**
     * close session.
     * @return void
     */
    public function kill_session() {
        foreach ($_SESSION as $name => $value) {
            if (strpos($name, $this->site_name.'_') == 0) {
                unset($_SESSION[$name]);
            }
        }
    }

    /******************** EXECUTION VARS *****************/

    /**
     * Get variable from session or header
     * @param string $name
     * @return mixed
     */
    public function get_executionVariable($name) {
        if (isset($_REQUEST[$name])) {
            if (($value = $_REQUEST[$name]) == 'false')
                $value = false;
            $this->set_sessionValue($name, $value);
            return $value;
        }
        return $this->get_sessionValue($name, false);
    }

    /**
     * Set variable to session
     * @param string $name
     * @param mixed $value
     * @return void
     */
    public function set_executionVariable($name, $value) {
        $this->set_sessionValue($name, $value);
    }

    /******************** SHARED DATA ********************/

    /**
     * Set a shared data.
     * @param string $name
     * @param mixed $data
     * @param string $sub
     * @return void
     */
    public function set_sharedData($name, $data=null, $sub=null) {
        if ($sub === null) {
            $this->shared_data[$name] = $data;
        } else {
         if (!isset($this->shared_data[$name]))
                $this->shared_data[$name] = array();
            if ($data === null)
                $this->shared_data[$name][] = $sub;
            else
                $this->shared_data[$name][$data] = $sub;
        }
    }

    /**
     * Get a shared data.
     * @param string $name
     * @param mixed $value
     * @return mixed
     */
    public function get_sharedData($name=null, $value=null) {
        if ($name == null)
            return $this->shared_data;

        if ($value != null and isset($this->shared_data[$name][$value]))
            return $this->shared_data[$name][$value];

        if (isset($this->shared_data[$name]))
            return $this->shared_data[$name];

        return $value;
    }


    /**
     * Check some shared data.
     * @param string $name
     * @return boolean result
     */
    public function check_sharedData($name) {
        return isset($this->shared_data[$name]);
    }

    /******************** SHARED OBJECTS ********************/

    /**
     * Register a plugin to be accessed by any other.
     * @param string $name
     * @param Plugin $object
     * @return boolean success
     */
    public function register_sharedObject($name, &$object) {
        if (isset($this->sharedObjects[$name]))
            return false;
        $this->sharedObjects[$name] = $object;
        return true;
    }

    /**
     * Return requested shared object.
     * @param string $name
     * @return Object
     */
    public function &get_sharedObject($name) {
        if (!isset($this->sharedObjects[$name]))
            return $this->falseRef;
        return $this->sharedObjects[$name];
    }

    /**
     * Return shared object name list.
     * @return array
     */
    public function get_sharedObjectList() {
        $list = array();
        foreach ($this->sharedObjects as $name => $object)
            $list[$name] = get_class($object);
        return $list;
    }

    /******************** PLUGIN EXTENSIONS **************/

    /**
     * Register a plugin as an extension to another.
     * @param string $plugin
     * @param string $ext_name
     * @param string $ext_type
     * @return void
     */
    public function Register_asExtension($plugin, $ext_name, $ext_type) {
        if (!isset($this->plugin_extensions[$plugin]))
            $this->plugin_extensions[$plugin] = array();
        $this->plugin_extensions[$plugin][] = array('name'=>$ext_name, 'type'=>$ext_type);
    }

    /**
     * Get registered extensions.
     * @param string $plugin
     * @return array
     */
    public function get_registeredExtensions($plugin) {
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

    /******************** EVENT HANDLERS *****************/

    /**
     * Register an event handler.
     * @param string $event
     * @param Object $plugin
     * @return void
     */
    public function register_eventHandler($event, &$plugin) {
        $this->eventsHandlers[$event][] = $plugin;
    }


    /**
     * Run event handlers.
     * @param string $event
     * @return void
     */
    private function run_eventHandlers($event) {
        foreach ($this->eventsHandlers[$event] as $plugin) {
            switch ($event) {
                case 'onInitialise' :       $plugin->execute_onCaMykSInitialise(); break;
                case 'onPageLoad' :         $plugin->execute_onCaMykSPageLoad(); break;
                case 'onBodyOpen' :         $this->HTMLPage->write_HTMLContent($plugin->execute_onCaMykSBodyOpen()); break;
                case 'onBodyClose' :        $this->HTMLPage->write_HTMLContent($plugin->execute_onCaMykSBodyClose()); break;
                case 'onTerminate' :        $plugin->execute_onCaMykSTerminate(); break;
            }
        }
    }

    /******************** PATHES & URLS ******************/

    /**
     * Return root base url.
     * @param string $mode
     * @return string
     */
    public function get_rootBaseURL($mode = null) {
        if ($mode == null)
            return $this->site_base_url;
        return $this->get_defaultBaseURL($mode);
    }

    /**
     * Return default base url.
     * @param mixed $mode
     * @return $string
     */
    public function get_defaultBaseURL($mode=null) {
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
                return $this->get_confValue('url').(substr($this->get_confValue('url'), -1) == '/' ? '' : '/');
            case 'absolute_short':
                return '/';
            case 'relative':
            default:
                return '';
        }
        return '';
    }

    /**
     * Return file url.
     * @param string $file
     * @param string $mode
     * @return $string
     */
    public function get_fileURL($file='', $mode=null) {
        if (substr($file, 0, 2) == './')
            $file = substr($file, 2);
        return $this->get_rootBaseURL($mode).$file;
    }


    /******************** DATA FILES *********************/

    /**
     * Return data file URL.
     * @param string $file
     * @param boolean $full
     * @param string $default
     * @return string
     * access public
     */
    public function get_dataFileURL($file, $full=null, $default='') {

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

    /**
     * Return data file path.
     * @param string $file
     * @return string
     */
    public function get_dataFilePath ($file) {
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

    /**
     * Finish closing CaMykS object.
     * @return void
     */
    public function terminate() {
        /* export bench before closing */
        if ($this->benchMode !== false) $this->benchMode->export();

        /* close databases */
        foreach ($this->openedDBonnections as $connection)
            $connection->close();

        /* run onTerminate event handlers */
        $this->run_eventHandlers('onTerminate');
    }

    /******************* LINKS ***************************/

    /**
     * Return HTML admin mode link.
     * @param string $module
     * @param array $params
     * @return string
     */
    public function get_adminLink($module='', $params=array()) {
        $link = $this->get_confValue('admin_entry', 'admin.php');
        if ($module != '') {
            $link .= '?module='.$module;
        }
        foreach ($params as $key => $value) {
            if ($key != '') {
                $link .= '&amp;'.$key .'='.$value;
            }
        }
        return $link;
    }

    /**
     * Return JavaScript admin mode link.
     * @param string $module
     * @param array $params
     * @return string
     */
    public function get_adminJSLink($module='', $params=array()) {
        $link = $this->get_confValue('admin_entry', 'admin.php');
        if ($module != '') {
            $link .= '?module='.$module;
        }
        foreach ($params as $key => $value) {
            if ($key != '') {
                $link .= '&'.$key .'='.$value;
            }
        }
        return $link;
    }

    /**
     * Return HTML request mode link.
     * @param array $params
     * @return string
     */
    public function get_requestLink($params=array()) {
        $link = $this->get_confValue('request_entry', 'request.php').'?';

        $items = array();
        foreach ($params as $key => $value) {
            if ($key != '') {
                $items[] = $key .'='.$value;
            }
        }
        $link .= implode('&amp;', $items);
        return $link;
    }

    /**
     * Return JavaScript request mode link.
     * @param array $params
     * @return string
     */
    public function get_requestJSLink($params=array()) {
        $link = $this->get_confValue('request_entry', 'request.php').'?';

        $items = array();
        foreach ($params as $key => $value) {
            if ($key != '') {
                $items[] = $key .'='.$value;
            }
        }
        $link .= implode('&', $items);
        return $link;
    }

    /**
     * Return site mode link.
     * @param mixed $page
     * @param string $name
     * @param string $lg
     * @param array $params
     * @return string
     */
    public function get_siteLink($page, $name='', $lg='', $params=array()) {
        return $this->modules['Admin_ContentPage']->get_sitePageLink($page, $lg, $params);
    }

    /**
     * Return home page link in site mode.
     * @return string
     */
    public function get_siteHomepageLink() {
        return $this->modules['Admin_ContentPage']->get_siteHomePageLink();
    }

    /**
     * Return site mode link based on current one.
     * @param string $lg
     * @param array $params
     * @return string
     */
    public function get_siteCurrentLink($lg='', $params=null) {
        return $this->get_siteLink($this->contentPage->id, $this->contentPage->name, $lg, $params!=null?$params:$this->contentPage->params);
    }

    /**
     * Return site mode link to key page.
     * @param string $key
     * @param string $lg
     * @param array $params
     * @return string
     */
    public function get_siteKeypageLink($key='', $lg='', $params=null) {
        return $this->modules['Admin_ContentPage']->get_siteKeyPageLink($key, $lg, $params);
    }

    /**
     * Return encoded params for link.
     * @param array $params
     * @return string
     */
    public function get_siteLinkEncodeParams($params) {
        if (count($params) == 0)
            return '';
        $p = array();
        foreach ($params as $n => $v) {
            $p[] = ''.$n;
            $p[] = ''.$v;
        }
        $p = implode('_', $p);
        return $p;
    }

    /**
     * Return decoded params for link.
     * @param string $params
     * @return array
     */
    function get_siteLinkDecodeParams($params) {
        $p = array();
        $params = explode('_', $params);
        for ($i=1; $i<count($params); $i+=2) {
            $p[$params[$i-1]] = $params[$i];
        }
        return $p;
    }

    /******************* CONTENT *************************/

    /**
     * Build page content.
     * @return void
     */
    private function get_pageContent() {
        if ($this->benchMode!==false) $this->benchMode->start('CaMykS page loading');

        switch ($this->mode) {
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

    /**
     * Build page content in site mode.
     * @return void
     */
    private function get_sitePageContent() {
        /* create page */
        $this->HTMLPage = new HTMLPage();
        $this->HTMLPage->set_charset($this->get_htmlencodingvalue());

        /* update HTML page metas with site informations */
        $this->HTMLPage->set_siteInformations($this->get_confValue('site_title'), $this->get_confValue('site_company'));

        /* create page content */
        $page = isset ($_REQUEST['page']) ? $_REQUEST['page'] : '';
        $params = isset ($_REQUEST['params']) ? $_REQUEST['params'] : '';
        $this->contentPage = new ContentPage($this->mode, 0, $params);

        /* get init from content */
        $this->contentPage->load_asFrontPage($page);

        /* run onInitialise event handlers */
        $this->run_eventHandlers('onPageLoad');

        /* get internal locales */
        $this->HTMLPage->set_pageInformations($this->contentPage->title, $this->contentPage->description, $this->contentPage->keywords, $this->current_language);

        /* set mobile configuration values */
        if ($this->deviceMode == 'handheld')
            $this->HTMLPage->set_mobileMeta(true, $this->get_confValue('mobileConfig'));

        /* set google analytics informations */
        $this->HTMLPage->set_googleInformations($this->get_confValue('google_analytics', ''), $this->get_confValue('google_analytics_domain', ''));

        /* initialise page */
        $this->contentPage->init_site();

        /* add favicon */
        $this->HTMLPage->set_favicon();

        /* display html header */
        $this->HTMLPage->add_HTMLHeader();

        /* run onBodyOpen event handlers */
        $this->run_eventHandlers('onBodyOpen');

        /* display html content */
        $this->contentPage->display();

        /* run onBodyClose event handlers */
        $this->run_eventHandlers('onBodyClose');

        /* display html footer */
        $this->HTMLPage->add_HTMLFooter();
    }

    /**
     * Build page content in admin mode.
     * @return void
     */
    private function get_adminPageContent() {
        /* init admin module to display */
        if ($this->check_adminUser() === false) {
            /* check for over written admin login module */
            if ($this->get_confValue('adminLoginModule') !== false and isset($this->modules[$this->get_confValue('adminLoginModule')]))
                $module = $this->get_confValue('adminLoginModule');
            else
                $module = 'Tool_Login';
        } else if (isset($_REQUEST['module'])) {
            $module = $_REQUEST['module'];
        } else {
            /* check for over written admin home module */
            if ($this->get_confValue('adminHomeModule') !== false and isset($this->modules[$this->get_confValue('adminHomeModule')]))
                $module = $this->get_confValue('adminHomeModule');
            else
                $module = 'Tool_ControlPanel';
        }

        /* set up HTML Page config */
        $this->set_confValue('html_version', 5);

        /* create page */
        $this->HTMLPage = new HTMLPage();
        $this->HTMLPage->set_charset($this->get_htmlencodingvalue());
        $this->HTMLPage->add_JSFile($this->get_dataFilePath('js/tool/adminengine.js'));

        /* create admin special page content */
        $this->contentPage = $this->modules['Admin_ContentPage']->get_newPage();
        $this->contentPage->set_adminData($module);

        /* get init from content */
        $this->theme->initialise();
        $this->contentPage->init_admin();

        /* update header vars */
        $this->HTMLPage->set_siteInformations($this->get_confValue('site_title'), 'CaMykS Team', '');
        $this->HTMLPage->set_pageInformations(
            $this->get_translation('administration').' - ' .$this->contentPage->modules[0]->title,
            null,
            null,
            $this->current_language
        );
        $this->HTMLPage->set_robotInformations(false, false);

        /* add favicon */
        $this->HTMLPage->set_favicon();

        /* display html header */
        $this->HTMLPage->add_HTMLHeader();
        /* display html main content */
        $this->contentPage->display();
        /* display html footer */
        $this->HTMLPage->add_HTMLFooter();
    }

    /**
     * Build page content in request mode.
     * @return void
     */
    function get_requestPageContent() {
        $plugin = false;

        /* Load plugin. */
        if (isset($_GET['module'])) {
            if (($plugin = module_get($_GET['module'], 'site')) === false)
                $plugin = module_get($_GET['module'], 'camyks');
        } elseif (isset($_GET['input'])) {
            if (($plugin = input_get($_GET['input'], 'site')) === false)
                $plugin = input_get($_GET['input'], 'camyks');
        } elseif (isset($_GET['theme'])) {
            if (($plugin = theme_get($_GET['theme'], 'site')) === false)
                $plugin = theme_get($_GET['theme'], 'camyks');
        } elseif (isset($_GET['template'])) {
            if (($plugin = template_get($_GET['template'], 'site')) === false)
                $plugin = template_get($_GET['template'], 'camyks');
        }
        /* get plugin init & display */
        if ($plugin !== false) {
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

    /**
     * Build page content in manager mode.
     * @return void
     */
    private function get_managerPageContent() {
        /* open manager *
        manager_main();
        */
    }

    /**
     * Build content in install mode.
     * @return void
     */
    private function get_installPageContent() {

        $this->get_currentLanguage('admin');

        /* create page */
        $this->HTMLPage->set_charset($this->get_htmlencodingvalue());
        $this->theme->get_included_main_css();
        $this->theme->get_included_parts();

        /* start to build the page with headers */
        $this->HTMLPage->set_siteInformations(
            $this->get_confValue('site_title'),
            'CaMykS Team',
            ''
        );
        $this->HTMLPage->set_pageInformations(
            $this->modules['Tool_Installer']->title,
            null,
            null,
            $this->current_language
        );
        $this->HTMLPage->set_robotInformations(false, false);
        $this->HTMLPage->add_HTMLHeader();

        /* add installer display */
        $this->modules['Tool_Installer']->display_admin();

        /* add html footer */
        $this->HTMLPage->add_HTMLFooter();
    }

    /* Deprecated methods */

    /**
     * Return available languages
     * @deprecated
     * @return array
     */
    public function get_availableLanguages() {
        return language_getAvailableLanguages();
    }

    /**
     * Start closing CaMykS object.
     * @deprecated
     * @return void
     * @see terminate()
     */
    public function init_kill() {
        die();
    }

    /**
     * Return site mode link based name.
     * @deprecated
     * @see get_siteLink()
     * @param string $name
     * @param string $lg
     * @param array $params
     * @return string
     */
    public function get_siteLinkByName ($name, $lg='', $params=array()) {
        $page = ContentPage::static_get_pageBasicInfoByName($name);
        return $this->get_rootBaseURL().$this->get_siteLink($page->id, $page->name, $lg, $params);
    }
}
?>
