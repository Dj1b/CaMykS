<?php
/**
 * @brief Module plugin object
 * @details Engine / Object Library
 * @file engine/lib/object/Module.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ModuleLibraryItem class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
class Module extends Plugin {
    /**
     * @var string $type
     * @brief Module type, can be \b admin or \b content.
     */
    public $type;
    
    /**
     * @var string $title
     * @brief Module title.
     */
    public $title;
    
    /**
     * @var string $libdesc
     * @brief Module library description.
     */
    public $libdesc;
    
    /**
     * @var array $libs
     * @brief Module libraries to load.
     */
    protected $libs = array();
    
    /**
     * @var Theme $theme
     * @brief Theme applied to the Module.
     */
    public $theme;
    
    /**
     * @var array $languages
     * @brief Module available locale files.
     */
    public $languages;
    
    /**
     * @var array $rights
     * @brief Module permissions.
     */
    public $rights = array();
    
    /**
     * @var string $selected_layout
     * @brief Module layout to use.
     */
    public $selected_layout = '';
    
    /**
     * @var string $selected_layout_location
     * @brief Module layout location, can be \b module or \b camyks.
     */
    public $selected_layout_location = 'module';
    
    /**
     * @var array $help
     * @brief Module help files.
     */
    public $help = null;
    
    /**
     * @var boolean $is_editable
     * @brief Module has editable content.
     */
    public $is_editable = true;
    
    /**
     * @var string $text
     * @brief Module admin message.
     */
    protected $text = '';

    /**
     * Class constructor
     * @param string $name the module name
     * @param string $path_type the module path (camyks or site)
     */
    public function __construct($name, $path_type) {
        $this->Module($name, $path_type);
    }
  
    /**
     * Old style constructor.
     * @param string $name the module name
     * @param string $path_type the module path (camyks or site)
     */
    public function Module($name, $path_type) {
        parent::__construct($name, 'module', $path_type);

        /* load language : needed to have title & description */
        $this->add_translation();

        /* get localized title from translation file */
        $this->title = $this->get_translation('title');

        /* set libdesc value by default */
        $this->libdesc = 'Module:'.$this->name;
    }

    /**
     * Check if module is installed.
     * @return boolean
     */
    public function is_installed() {
        return null;
    }

    /**
     * Load available language files for the module
     * @return void
     */
    public function get_languages () {
        global $camyks;
        $path = $this->plugin_path.'/locale';
        $this->languages = array();
        $locales_files = folder_listFiles ($path);
        foreach ($locales_files as $f) {
            if (substr ($f, 0, 12) == 'translation_' and substr ($f , strlen ($f) - strlen ($camyks->file_extension), strlen ($camyks->file_extension)) == $camyks->file_extension) {
                $this->languages[] = substr ($f, 12, strlen ($f) - 12 - strlen ($camyks->file_extension));
            }
        }
    }

    /***************** HELP **********************/
  
    /**
     * Load help files.
     * @return void
     */
    public function get_help() {
        global $camyks;
        /* check if help files exists */
        $hfile = 'help/'.$camyks->current_language.'/help.php.inc';
        $this->load_file($hfile);
        if (isset($this->help)) {
            /* update help with default main page */
            array_unshift($this->help, array(
                'title'=>$camyks->get_translation('module_generic_help'),
                'html'=>'help_module_generic.html.inc',
                'location'=>'camyks'
            ));
            /* add javascripts for help engine */
            $this->add_JSEngineFile ('object/cmdd.js');
            $this->add_JSScript(strtolower($this->name).'_helpObject = new Cmdd();');
            $this->add_JSScript(strtolower($this->name).'_helpObject.init("'.$this->name.
                '", "","'.$camyks->theme->parts['boxTabCSSStandart'].
                '","'.$camyks->theme->parts['boxTabCSSSelected'].
                '","'.$camyks->theme->parts['boxTabCSSRollover'].'");');

            /* open first element */
            foreach ($this->help as $i => $v) {
                $this->add_JSLoadScript(strtolower($this->name).'_helpObject.mouseclick(\''.$i.'\');');
                break;
            }
        }
    }

    /**
     * Display help files.
     * @return void
     */
    public function display_help() {
        global $camyks;
        $this->load_engineFile('data/html/help.html.inc');
    }

    /***************** ADD INFOS TO MAIN PAGE *******************/

    /**
     * Set module applied theme.
     * @param string $theme the theme name
     * @return void
     */
    public function set_theme($theme) {
        global $camyks;
        if (isset ($camyks->themes[$theme])) {
            $this->theme = &$camyks->themes[$theme];
        } else {
            $this->theme = &$camyks->themes[$camyks->_conf['site_default_theme']];
        }
        $this->theme->get_parts();
    }

    /***************** LANGUAGE & LOCALES METHODS ****************/

    /**
     * Return locale value.
     * @param string $value the locale value to return
     * @param mxed $data the optional inserted data
     * @return string
     */
    public function get_translation($value, $data=null) {
        global $camyks;
        return $camyks->get_translation('mod_'.strtolower($this->name).'_'.$value, $data);
    }

    /**
     * Return language to use for admin content edition.
     * @return string
     */
    public function get_adminEditionLanguage() {
        global $camyks;

        if (($l =  $camyks->get_confValue('editing_default_language')) != false)
            return $l;
        $elgs =  $camyks->get_confValue('editing_languages');
        if (in_array($camyks->current_language, $elgs))
            return $camyks->current_language;
        else
        return $elgs[0];
    }

    /***************** CONTENT METHODS *************************/

    /**
     * Return existing content list.
     * <br /> If the module is not editable return -1
     * @return mixed
     */
    public function get_contentList() {
        return -1;
    }

    /***************** ADMIN METHODS **************************/

    /**
     * Pre-initialise module object in admin mode
     * @return void
     */
    public function preInit_admin() {
        if ($this->type == 'content') {
            /* page values */
            $this->id = isset($_REQUEST['id']) ? $_REQUEST['id'] : 0;
            $this->page_id = isset ($_REQUEST['page_id']) ? $_REQUEST['page_id'] : 0;
            $this->module_index = isset ($_REQUEST['module_index']) ? $_REQUEST['module_index']: -1;
        } elseif ($this->type == 'admin') {

        }
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        /* set admin layout by default */
        if ($this->selected_layout == '') {
            $this->set_selectedLayout('admin.html.inc');
        }
    }

    /**
     * Display module object in admin mode.
     * @return void
     */
    public function display_admin() {
        $this->get_adminLayout();
    }

    /*
     * Initialise parent only.
     * @return void
     */
    public function init_parent_admin() {
        Module::init_admin();
    }

    /**
     * init module object in admin/access denied mode
     * @return void
     */
    protected function init_admin_accessDenied() {
        global $camyks;
        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* redirect to home */
        $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink());
        $this->text = $camyks->get_translation ('module_access_denied');
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/page access denied mode
     * @return void
     */
    protected function init_admin_pageAccessDenied() {
        global $camyks;
        
        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* redirect to page tree (or to home) */
        if (isset($camyks->modules['Admin_ContentPage']))
            $this->set_redirect($camyks->get_adminLink('Admin_ContentPage'));
        else
            $this->set_redirect($camyks->get_adminLink());
        $this->text = $camyks->get_translation ('module_page_access_denied');
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/action not allowed mode
     * @return void
     */
    protected function init_admin_actionNotAllowed () {
        global $camyks;
        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* redirect to admin home */
        $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink());
        $this->text = $camyks->get_translation ('module_action_not_allowed');
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/missing plugin mode
     * @return void
     */
    protected function init_admin_missingPlugin($type, $name) {
        global $camyks;

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* redirect to admin home */
        $type = $camyks->get_translation ($type);
        $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink());
        $this->text = $camyks->get_translation('module_plugin_missing', array($type, $name));
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Return admin link.
     * @param array $params
     * @param string $module
     * @return string
    */
    public function get_adminLink($params=array(), $module=null) {
        global $camyks;

        /* check module value */
        if (isset($module)) {

        } elseif (isset($params['module'])) {
            $module = $params['module'];
            unset($params['module']);
        } else {
            $module = $this->name;
        }

        /* check module */
        if (!isset($camyks->modules[$module]))
            return '';
        else
            $type = $camyks->modules[$module]->type;

        /* add content module params */
        if ($type == 'content') {
            $tparams = array(
                'id'=>$this->id,
                'page_id'=>$this->page_id,
                'module_index'=>$this->module_index
            );
            $params = array_merge($tparams, $params);
        }
        return $camyks->get_adminLink($module, $params);
    }

    /**
     * Return admin Javascript link.
     * @param array $params
     * @param string $module
     * @return string
     */
    public function get_adminJSLink($params=array(), $module=null) {
        global $camyks;

        /* check module value */
        if (isset($module)) {

        } elseif (isset($params['module'])) {
            $module = $params['module'];
            unset($params['module']);
        } else {
            $module = $this->name;
        }

        /* check module */
        if (!isset($camyks->modules[$module]))
            return '';
        else
            $type = $camyks->modules[$module]->type;

        /* add content module params */
        if ($type == 'content') {
            $tparams = array(
                'id'=>$this->id,
                'page_id'=>$this->page_id,
                'module_index'=>$this->module_index
            );
            $params = array_merge($tparams, $params);
        }
        return $camyks->get_adminJSLink($module, $params);
    }

    /***************** SITE METHODS ************************/

    /**
     * Initialise module object in site mode.
     * @param integer $content
     * @param array $params
     * @param integer $index
     * @return void
     */
    public function init_site($content=1, $params=array(), $index=null) {
        /* set site layout by default */
        if ($this->selected_layout == '') {
            $this->set_selectedLayout('site.html.inc');
        }
    }

    /**
     * Display module in site mode.
     * @return void
     */
    public function display_site() {
        $this->get_siteLayout();
    }

    /***************** REQUEST METHODS ************************/

    /**
     * Execute module in request mode.
     * @return void
     */
    public function execute_request() {
        echo 'This plugin doesn\'t support requests.';
    }

    /***************** LAYOUT MANAGEMENT **************/

    /**
     * Update selected layout.
     * @param string $layout
     * @param string $location
     * @return void
     */
    public function set_selectedLayout($layout='', $location='') {
        $this->selected_layout = $layout;
        $this->selected_layout_location = $location;
    }

    /**
     * Load selected admin layout.
     * @param string $layout the selected layout
     * @return void
     */
    public function get_adminLayout($layout='') {
        if ($layout != '') {
            $this->load_file('html/'.$layout);
        } else if ($this->selected_layout != '') {
            if ($this->selected_layout_location == 'camyks')
                $this->load_engineFile('data/html/'.$this->selected_layout);
            else
                $this->load_file('html/'.$this->selected_layout);
        } else {
            $this->load_file('html/admin.html.inc');
        }
    }

    /**
     * Load selected site layout
     * @return void
     */
    public function get_siteLayout() {
        if ($this->selected_layout != '') {
            if ($this->selected_layout_location == 'camyks')
                $this->load_engineFile('data/html/'.$this->selected_layout);
            else
                $this->load_file('html/'.$this->selected_layout);
        } else {
            $this->load_file('html/site.html.inc');
        }
    }

    /**************** ADMIN ENGINE MANAGEMENT *********/
  
    /**
     * Return admin menus to register : always displayed.
     * @return array
     */
    public function get_adminEngineGenericMenus() {
        return array();
    }

    /**
     * Return admin menu items to register : always displayed.
     * @return array
     */
    public function get_adminEngineGenericMenuItems() {
        return array();
    }

    /**
     * Return admin menus to register : display only when module is selected.
     * @return array
     */
    public function get_adminEngineSpecificMenus() {
        return array();
    }

    /**
     * Return admin menu items to register : display only when module is selected.
     * @return array
     */
    public function get_adminEngineSpecificMenuItems() {
        return array();
    }

    /**
     * Allow module to add specific data to admin page
     * @return boolean
     */
    public function get_adminEngineGenericInit() {
        return true;
    }

    /**
     * Display module specific content to admin page
     * @return string
     */
    public function get_adminEngineGenericDisplay() {
        return '';
    }

    /**
     * Return notified items for module
     * @return array
     */
    public function get_adminInternalNotifications() {
        return array();
    }

    /**************** MODULE SPECIFIC METHODS ***********/

    /**
     * Tell admin Tool_InfoBar to disable menus
     * @return void
     */
    protected function disable_adminEngineMenus() {
        global $camyks;
        if (isset($camyks->modules['Tool_InfoBar']))
            $camyks->modules['Tool_InfoBar']->disable_adminMenus();
    }

    /**************** MODULE SPECIFIC CALLBACKS ***********/

    /**
     * Return action to execute in control panel
     * @return boolean
     */
    public function get_adminControlPanelAction() {
        return true;
    }

    /**
     * Return object titles in statistics engine
     * @param array $list the id list to get
     * @param string $object the object
     * @return array
     */
    public function get_adminStatisticsValueTitles($list, $object=null) {
        return $list;
    }

    /**
     * Return object specific options in statistics engine
     * @param string $object
     * @return string
     */
    public function get_adminStatisticsSpecificOptions($object=null) {
        return '';
    }

    /***************** RIGHTS METHODS ***************/

    /**
     * Load right list.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'=>'read',
            'title'=> $camyks->get_translation('read'),
            'default'=> false
        );
        $this->rights[1] = array(
            'name'=>'read',
            'title'=> $camyks->get_translation('write'),
            'default'=> false
        );
    }

    /**
     * Return right value for this module/mode.
     * @param $info
     * @return boolean
     */
    public function check_right($info) {
        global $camyks;
        switch ($this->type) {
            case 'admin':
                /* check admin user rights for this admin module */
                if ($camyks->adminUser!==false)
                    return $camyks->adminUser->get_right($this->name, $info);
                return false;
            case 'content':
                /* check admin user right for the current page */
                if (isset($camyks->modules['Admin_ContentPage']) and $camyks->modules['Admin_ContentPage']->check_right(2)) {
                    $page = $camyks->modules['Admin_ContentPage']->page;
                    $page->id = $info;
                    $page->get();
                    return $page->check_rights();
                }
                return false;
            case 'tool':
            default:
                return true;
        }
    }

    /***************** UTIL METHODS ******************/

    /**
     * Return default buttons definition for html form file input.
     * @param array $buttons
     * @param boolean $delete add view button to buttons list
     * @return array
     */
    public function get_fileInputButtons($buttons=array(), $delete=true) {
        global $camyks;

        if (is_array($buttons))
            $buttons = array_merge(array('view' => true, 'listen' => true, 'delete' => true), $buttons);
        else
            $buttons = array('view' => $buttons, 'delete' => $delete, 'listen' => $buttons);

        $list = array();
        if ($buttons['view'] === true)
            $list['view'] = array(
                'std'   => $this->theme->get_pictURL('view', 12, 'std'),
                'ovr'   => $this->theme->get_pictURL('view', 12, 'ovr'),
                'title' => $camyks->get_translation('display')
            );
        if ($buttons['listen'] === true)
            $list['listen'] = array(
                'std'   => $this->theme->get_pictURL('right', 12, 'std'),
                'ovr'   => $this->theme->get_pictURL('right', 12, 'ovr'),
                'title' => $camyks->get_translation('listen')
            );
        if ($buttons['delete'] === true)
            $list['delete'] = array(
                'std'   => $this->theme->get_pictURL('cross', 12, 'std'),
                'ovr'   => $this->theme->get_pictURL('cross', 12, 'ovr'),
                'title' => $camyks->get_translation('delete')
            );
        return $list;
    }

    /**
     * Return default buttons definition for html from date input.
     * @param boolean $update add update button to button list
     * @param boolean $reset add reset button to button list
     * @return array
     */
    public function get_dateInputButtons($update=true, $reset=true) {
        global $camyks;

        $list = array();
        if ($update === true)
            $list['update'] = array(
                'std'   => $this->theme->get_pictURL('target', 12, 'std'),
                'ovr'   => $this->theme->get_pictURL('target', 12, 'ovr'),
                'title' => $camyks->get_translation('update')
            );
        if ($reset === true)
            $list['reset'] = array(
                'std'   => $this->theme->get_pictURL('cross', 12, 'std'),
                'ovr'   => $this->theme->get_pictURL('cross', 12, 'ovr'),
                'title' => $camyks->get_translation('reset')
            );
        return $list;
    }

    /*************** PAGE MANAGER RELATED METHODS *****/

    /**
     * Apply module object, with current settings, in given page module location
     * @param integer $pageId
     * @param integer $moduleIndex
     * @param integer $contentId
     * @return boolean result
     */
    protected function add_moduleContentToPage($pageId, $moduleIndex, $contentId) {
        global $camyks;

        /* check module type */
        if ($this->type != 'content')
            return false;

        /* check page manager module */
        if (!isset($camyks->modules['Admin_ContentPage']))
            return false;

        /* update page information with object id for new content */
        return $camyks->modules['Admin_ContentPage']->page->static_update_singleModuleContent($pageId, $moduleIndex, $contentId);
    }
  
    /* deprecated methods */
  
    /**
     * Load PHP libraries.
     * @return void
     * @deprecated Use Plugin::load_library instead.
     */
    protected function get_PHPLibs () {
        foreach ($this->libs as $lib) {
            $file = $this->plugin_path .'/lib/' . $lib;
            if (file_exists ($file)) {
                require_once($file);
            }
        }
    }
    
    /**
     * Generic module initialisation.
     * @return boolean
     * @deprecated Never been used.
     */
    public function init_generic() {
        return true;
    }
}
?>
