<?php
/**
 * @brief Tool_Installer module installation parameters library
 * @details Plugin / Module Library
 * @file plugin/module/Tool_Installer/lib/Tool_InstallerParams.php.inc
 * @author JB Lebrun <jb.lebrun@ideogram-design.fr>
 * @version 1.0.1
 * @date Creation: Oct 2017
 * @date Modification: May 2019
 * @copyright 2017 - 2019 Ideogram Design
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Tool_InstallerParams class.
 */
final class Tool_InstallerParams extends ModuleLibrary {
    /**
     * var array $themes
     * @brief Available theme list.
     */
    private $themes;

    /**
     * var array $templates
     * @brief Available template list.
     */
    private $templates;

    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* hidden items */
        $this->add_newItem('site_name', 'temp', 'text', '', '', '');
        $this->add_newItem('url', 'temp', 'text', '', '', '');
        $this->add_newItem('nextStep', 'temp', 'text', '', '', '');
        $this->add_newItem('mobileMode', 'temp', 'int', '', '', 0);

        /*    site items */
        $this->add_newItem('site_title', 'temp', 'text', '', '', '');
        $this->add_newItem('version', 'temp', 'text', '', '', '');
        $this->add_newItem('encoding', 'temp', 'text', '', '', '');
        $this->add_newItem('site_author', 'temp', 'text', '', '', '');
        $this->add_newItem('site_company', 'temp', 'text', '', '', '');

        /* admin section items */
        $this->add_newItem('admin_languages', 'temp', 'list', '', '', array());
        $this->add_newItem('admin_default_language', 'temp', 'text', '', '', '');
        $this->add_newItem('editing_languages', 'temp', 'list', '', '', array());
        $this->add_newItem('admin_default_theme', 'temp', 'text', '', '', '');
        $this->add_newItem('admin_ssl', 'temp', 'text', '', '', '');

        /* visitor section items */
        $this->add_newItem('site_languages', 'temp', 'list', '', '', array());
        $this->add_newItem('site_default_language', 'temp', 'text', '', '', '');
        $this->add_newItem('site_default_theme', 'temp', 'text', '', '', '');
        $this->add_newItem('site_default_template', 'temp', 'text', '', '', '');
        $this->add_newItem('site_ssl', 'temp', 'text', '', '', '');
        $this->add_newItem('page_maxmodules', 'temp', 'int', '', '', 8);

        /* database items */
        $this->add_newItem('database_driver', 'temp', 'text', '', '', '');
        $this->add_newItem('database_name', 'temp', 'text', '', '', '');
        $this->add_newItem('database_host', 'temp', 'text', '', '', '');
        $this->add_newItem('database_login', 'temp', 'text', '', '', '');
        $this->add_newItem('database_pwd', 'temp', 'text', '', '', '');

        /* options items */
        $this->add_newItem('google_analytics', 'temp', 'text', '', '', '');
        $this->add_newItem('google_analytics_domain', 'temp', 'text', '', '', '');
        $this->add_newItem('enable_handheldVersion', 'temp', 'text', '', '', '');
        $this->add_newItem('enable_responsiveDesign', 'temp', 'text', '', '', '');

        /* webmaster items */
        $this->add_newItem('webmaster_login', 'temp', 'text', '', '', '');
        $this->add_newItem('webmaster_password', 'temp', 'text', '', '', '');
        $this->add_newItem('webmaster_email', 'temp', 'text', '', '', '');

        $this->themes = null;
        $this->templates = null;

        /* generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Initialise object.
     * @return boolean success
     */
    public function initialise() {
        global $camyks;
        parent::initialise();

        /* load set up from config file */
        $this->get_fromArray($camyks->site_conf);

        /* specific adaptation */
        if ($this->_libItems['enable_responsiveDesign']->value == 1)
            $this->_libItems['mobileMode']->value = 1;
        elseif ($this->_libItems['enable_handheldVersion']->value == 1)
            $this->_libItems['mobileMode']->value = 2;

        /* return result */
        return true;
    }

    /**
     * Return values from items.
     * @return void
     */
    public function get_fromItems() {
        parent::get_fromItems();

        if ($this->vars['mobileMode'] == 1)
            $this->vars['enable_responsiveDesign'] = 1;
        elseif ($this->vars['mobileMode'] == 2)
            $this->vars['enable_handheldVersion'] = 1;
    }

    /* Specific items related methods */

    /**
     * Initialise hidden values.
     * @return boolean success
     */
    public function initialise_hiddenValues() {

        /* set up site name/folder value */
        if ($this->_libItems['site_name']->value == '')
            $this->_libItems['site_name']->value = basename(getcwd());

        /* set up site url value */
        if ($this->_libItems['url']->value == '') {
            $uri = explode('?', $_SERVER['REQUEST_URI'], 2);
            $this->_libItems['url']->value = (isset($_SERVER['HTTPS']) ? "https" : "http").'://'.$_SERVER['HTTP_HOST'].$uri[0];
        }
    }

    /* Specific data related methods */

    /**
     * Return admin theme list.
     * @return array
     */
    public function get_adminThemeList() {
        $this->load_availableThemes();

        $list = array();

        foreach ($this->themes as $theme)
            $list[$theme->name] = $theme->title;

        return $list;
    }

    /**
     * Return site theme list.
     * @return array
     */
    public function get_siteThemeList() {
        $this->load_availableThemes();

        $list = array();
        $list[''] = $this->get_translation('no_selected_theme');

        foreach ($this->themes as $theme)
            $list[$theme->name] = $theme->title;

        return $list;
    }

    /**
     * Return template list.
     * @return array
     */
    public function get_templateList() {
        $this->load_availableTemplates();

        $list = array();
        $list[''] = $this->get_translation('no_selected_template');

        foreach ($this->templates as $template)
            if ($template->name != 'Admin')
                $list[$template->name] = $template->title.' ('.$template->modules.')';

        return $list;
    }

    /**
     * Return SSL mode value list.
     * @return array
     */
    public function get_SSLModeList() {
        return array(
            'default'   => $this->get_translation('sslmode_default'),
            'auto'      => $this->get_translation('sslmode_auto'),
            'forced'    => $this->get_translation('sslmode_forced'),
            'none'      => $this->get_translation('sslmode_none'),
        );
    }

    /**
     * Return mobile mode value list.
     * @return array
     */
    public function get_mobileModeList() {
        return array(
            0 => $this->get_translation('mobilemode_none'),
            1 => $this->get_translation('mobilemode_responsive'),
            2 => $this->get_translation('mobilemode_dedicated'),
        );
    }

    /**
     * Return available languages (with icon).
     * @return array
     */
    public function get_availableLanguages() {
        global $camyks;

        $languages = array();
        foreach (language_getAvailableLanguages() as $l => $data) {
            $f = new FSFile($camyks->camyks_engine_path.'/data/img/flag/'.$l.LANG_ICON_EXTENSION);
            $languages[$l] = '<img src="'.$f->get_base64Data().'" alt="'.$data['title'].'" style="margin-right:4px;" />'.$data['title'];
        }
        return $languages;
    }

    /* Private methods */

    /**
     * Load available themes.
     * @return void
     */
    private function load_availableThemes() {
        global $camyks;

        /* check if themes are not already loaded */
        if ($this->themes != null)
            return;

        /* load themes */
        $this->themes = array_merge(
            theme_getList($camyks->camyks_plugin_path, 'camyks'),
            theme_getList($camyks->site_plugin_path, 'site')
        );
    }

    /**
     * Load available templates.
     * @return void
     */
    private function load_availableTemplates() {
        global $camyks;

        /* check if templates are not already loaded */
        if ($this->templates != null)
            return;

        /* load templates */
        $this->templates = array_merge(
            template_getList($camyks->camyks_plugin_path, 'camyks'),
            template_getList($camyks->site_plugin_path, 'site')
        );
    }
}
?>
