<?php
/**
 * @brief Admin_PluginManager Module.
 * <br /> Administration module to manage plugins.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.1
 * @date Creation: Jun 2005
 * @date Modification: Nov 2020
 * @copyright 2005 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_PluginManager class.
 */
final class Admin_PluginManager extends Module {
    /**
     * var string $list
     * @brief Running mode while being executed in CaMykS admin mode.
     */
    private $mode = 'list';

    /**
     * var array $modules
     * @brief Loaded modules list.
     */
    protected $modules;

    /**
     * var array $templates
     * @brief Loaded template list.
     */
    protected $templates;

    /**
     * var array $themes
     * @brief Loaded theme list.
     */
    protected $themes;

    /**
     * var array $inputs
     * @brief Loaded input list.
     */
    protected $inputs;

    /**
     * var array $pluginsinfo
     * @brief Stores plugins status.
     */
    private $pluginsinfo;

    /**
     * var array $installedTables
     * @brief Stores installed tables in database.
     */
    protected $installedTables = null;

    /**
     * var Object $pluginItem
     * @brief Single plugin information object.
     */
    protected $pluginItem;

    /**
     * var array $unfound
     * @brief List of installed, but not found plugins.
     */
    protected $unfound;

    /**
     * var string $text
     * @brief Admin message text.
     */
    protected $text;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_PluginManager', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'System';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'configuration';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load libraries */
        $this->load_library('Admin_PluginManagerItem');

        /* Initialise library objects */
        $this->pluginItem = new Admin_PluginManagerItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module object.
     * @return boolean success
     */
    public function install() {
        return ($this->pluginItem->install() and parent::install());
    }

    /**
     * Uninstall module object.
     * @return boolean success
     */
    public function uninstall() {
        return false;
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->pluginItem->is_installed();
    }

    /**
     * Return main menus.
     * @return array
     */
    public function get_adminEngineSpecificMenus() {
        if ($this->check_right(1) === true) {
            return array(
                array(
                    'name'  => 'pluginmanager',
                    'title' => $this->get_translation('title'),
                )
            );
        }
        return array();
    }

    /**
     * Return sub menus.
     * @return array
     */
    public function get_adminEngineSpecificMenuItems() {
        if ($this->check_right(1) === true) {
            return array(
                array(
                    'name'  => 'cleandatabase',
                    'title' => $this->get_translation('cleandatabase'),
                    'icon'  => $this->get_fileURL('img/clean12.gif'),
                    'menu'  => 'pluginmanager',
                    'url'   => $this->get_adminLink(array('mode'=>'cleandb'))
                )
            );
        }
        return array();
    }

    /**
     * Initialise module object when in admin mode
     * @return void
     */
    public function init_admin() {
        /* Check read permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Load mode value */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'list';

        /* Prepare unfound module list */
        $this->unfound = array();

        /* Execute mode */
        switch ($this->mode) {
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

        /* Perform generic module admin initialisation */
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/activate mode.
     * @return void
     */
    private function init_admin_activate() {
        /* Check plugin management permission */
        if ($this->check_right(1)===false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load plugin information */
        $this->pluginItem->get_fromHeader();
        $this->pluginItem->activevalue = 1;

        /* Enable plugin */
        if ($this->pluginItem->active_plugin())
            $this->text = $this->get_translation('activationdone', $this->pluginItem->pluginvalue);
        else
            $this->text = $this->get_translation('activationfailed', $this->pluginItem->pluginvalue);

        /* Add page redirection */
        $this->set_redirect($this->get_adminLink(
            array(
                'mode'      => 'list',
                'openTab'   => ucwords($this->pluginItem->typevalue).'s',
            )
        ));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/desactivate mode
     * @return void
     */
    private function init_admin_desactivate() {
        /* Check plugin management permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load plugin information */
        $this->pluginItem->get_fromHeader();
        $this->pluginItem->activevalue = 0;

        /* Disable plugin */
        if ($this->pluginItem->save_toDatabase())
            $this->text = $this->get_translation ('desactivationdone', $this->pluginItem->pluginvalue);
        else
            $this->text = $this->get_translation ('desactivationfailed', $this->pluginItem->pluginvalue);

        /* Add page redirection */
        $this->set_redirect($this->get_adminLink(
            array(
                'mode'            => 'list',
                'openTab'     => ucwords($this->pluginItem->typevalue).'s',
            )
        ));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/setAsDefault mode
     * @return void
     */
    private function init_admin_setAsDefault() {
        /* Check plugin management permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        $cMode = isset($_REQUEST['cMode']) ? $_REQUEST['cMode'] : 'site';

        $this->pluginItem->get_fromHeader();
        if ($this->pluginItem->set_asDefault($cMode))
            $this->text = $this->get_translation('configurationupdated');
        else
            $this->text = $this->get_translation('configurationnotupdated');

        /* Add page redirection */
        $this->set_redirect($this->get_adminLink(
            array(
                'mode'      => 'list',
                'openTab'   => ucwords($this->pluginItem->typevalue).'s',
            )
        ));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/cleandb mode
     * @return void
     */
    private function init_admin_cleandb() {
        global $camyks;

        /* Check plugin management permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load plugin information */
        $camyks->get_neededPlugins();
        $this->get_modules();
        $this->get_templates();
        $this->get_themes();
        $this->get_inputs();
        $this->get_pluginsFromDatabase();

        /* Clean database */
        $this->check_pluginsinfo();
        if (count ($this->unfound) > 0) {
            foreach ($this->unfound as $p) {
                $this->pluginItem->delete_fromDatabase($p);
            }
            $this->text = $this->get_translation ('cleaningdone');
        } else {
            $this->text = $this->get_translation ('nocleaningneeded');
        }

        /* Add page redirection */
        $this->set_redirect($this->get_adminLink(array('mode'=>'list')));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object admin/list mode
     * @return void
     */
    private function init_admin_list() {
        global $camyks;

        /* Load plugin information */
        $camyks->get_neededPlugins();
        $this->get_modules();
        $this->get_templates();
        $this->get_themes();
        $this->get_inputs();
        $this->get_pluginsFromDatabase();
        $this->check_pluginsinfo();
        $this->load_installedTables();

        /* Load help */
        $this->get_help();

        /* Build tabs */
        if (!isset($camyks->inputs['TabBuilder']))
            $this->tabBuilder = input_get('TabBuilder', 'camyks');
        else
            $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Check if TabBuilder plugin is available */
        if ($this->tabBuilder === false)
            $camyks->throwFatalError(array(
                'title'         => $camyks->get_translation('error_pluginmissing_title'),
                'description'   => $camyks->get_translation('error_pluginmissing_desc', 'TabBuilder'),
            ));

        /* Adds tabs */
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
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        $this->tabBuilder->initialise(array('default'=>'Modules'));

        /* Load scripts */
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

        /* Prepare action menus */
        $this->themeActionMenu = array(
            array(
                'name'  => 'setSiteDefault',
                'title' => $this->get_translation('applyassitedefaulttheme'),
                'icon'  => $this->theme->get_pictURL('right', 12, 'std'),
                'url'   => 'javascript:pl.execute_action(\'setSiteDefaultTheme\');',
            ),
            array(
                'name'  => 'setAdminDefault',
                'title' => $this->get_translation('applyasadmindefaulttheme'),
                'icon'  => $this->theme->get_pictURL('right', 12, 'std'),
                'url'   => 'javascript:pl.execute_action(\'setAdminDefaultTheme\');',
            ),
        );
        $this->templateActionMenu = array(
            array(
                'name'    => 'setSiteDefault',
                'title' => $this->get_translation('applyassitedefaulttemplate'),
                'icon'    => $this->theme->get_pictURL('right', 12, 'std'),
                'url'     => 'javascript:pl.execute_action(\'setSiteDefaultTemplate\');',
            ),
        );
        $this->add_JSLoadScript('pl.set_param("actionURLs", "setSiteDefaultTheme", "'.$this->get_adminJSLink(array('mode'=>'setAsDefault', 'cMode'=>'site', 'type'=>'theme', 'plugin'=>'__PNAME__')).'");');
        $this->add_JSLoadScript('pl.set_param("actionURLs", "setAdminDefaultTheme", "'.$this->get_adminJSLink(array('mode'=>'setAsDefault', 'cMode'=>'admin', 'type'=>'theme', 'plugin'=>'__PNAME__')).'");');
        $this->add_JSLoadScript('pl.set_param("actionURLs", "setSiteDefaultTemplate", "'.$this->get_adminJSLink(array('mode'=>'setAsDefault', 'cMode'=>'site', 'type'=>'template', 'plugin'=>'__PNAME__')).'");');


        /* Build button list for button bars */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'    => $camyks->get_adminLink(),
            ),
        );
    }

    /* Specific tool methods */

    /**
     * Install plugin.
     * @param string $plugin
     * @param string $type
     * @param string $location
     * @param string $version
     * @return boolean success
     */
    public function install_plugin($plugin, $type, $location='camyks', $version='1.0') {
        return $this->pluginItem->active_plugin($plugin, $type, $location, $version);
    }

    /**
     * Update plugin version.
     * @param string $plugin
     * @param string $type
     * @param string $version
     * @return boolean success
     */
    public function update_pluginVersion($plugin, $type, $version) {
        return $this->pluginItem->update_pluginVersion($plugin, $type, $version);
    }

    /**
     * Load modules list.
     * @return array
     */
    private function get_modules() {
        global $camyks;
        $this->modules = array_merge(
            module_getList($camyks->camyks_plugin_path, 'camyks'),
            module_getList($camyks->site_plugin_path, 'site')
        );
    }

    /**
     * Load templates list.
     * @return array
     */
    private function get_templates() {
        global $camyks;
        $this->templates = array_merge(
            template_getList($camyks->camyks_plugin_path, 'camyks'),
            template_getList($camyks->site_plugin_path, 'site')
        );
    }

    /**
     * Load themes list.
     * @return array
     */
    private function get_themes() {
        global $camyks;
        $this->themes = array_merge(
            theme_getList($camyks->camyks_plugin_path, 'camyks'),
            theme_getList($camyks->site_plugin_path, 'site')
        );
    }

    /**
     * Load inputs list.
     * @return array
     */
    private function get_inputs() {
        global $camyks;
        $this->inputs = array_merge(
            input_getList($camyks->camyks_plugin_path, 'camyks'),
            input_getList($camyks->site_plugin_path, 'site')
        );
    }

    /**
     * Check all plugins with database value
     * @return void
     */
    private function check_pluginsinfo() {
        foreach ($this->pluginsinfo as $p) {
            /* get active value (while checking if plugin folder exists) */
            switch ($p['type']) {
                case 'module':
                    if (isset($this->modules[$p['plugin']])) {
                        $this->modules[$p['plugin']]->active = $p['active'];
                    } else {
                        $this->unfound[] = $p;
                    }
                    break;
                case 'theme':
                    if (isset($this->themes[$p['plugin']])) {
                        $this->themes[$p['plugin']]->active = $p['active'];
                    } else {
                        $this->unfound[] = $p;
                    }
                    break;
                case 'template':
                    if (isset($this->templates[$p['plugin']])) {
                        $this->templates[$p['plugin']]->active = $p['active'];
                    } else {
                        $this->unfound[] = $p;
                    }
                    break;
                case 'input':
                    if (isset($this->inputs[$p['plugin']])) {
                        $this->inputs[$p['plugin']]->active = $p['active'];
                    } else {
                        $this->unfound[] = $p;
                    }
                    break;
            }
        }
    }

    /* Specific i/o methods */

    /**
     * Return plugin list.
     * @param array $params
     * @return array
     */
    public function get_pluginList($params=array()) {
        return $this->pluginItem->get_objectList($params);
    }

    /**
     * Load plugins info from database
     * @return boolean success
     */
    private function get_pluginsFromDatabase() {
        $this->pluginsinfo = $this->pluginItem->get_objectList();
    }

    /**
     * Load installed database
     * @return boolean success
     */
    private function load_installedTables() {
        global $camyks;

        $this->installedTables = $camyks->db_conn->get_tableList();

        return true;
    }

    /**
     * Return installed table list.
     * @return array
     */
    public function get_tableList() {
        if ($this->installedTables == null)
            $this->load_installedTables();
        return $this->installedTables;
    }

    /**
     * Check if table is installed.
     * @param string $tableName
     * @return boolean result
     */
    public function check_tableExists($tableName='') {
        if ($this->installedTables === null)
            $this->load_installedTables();
        return (in_array($tableName, $this->installedTables));
    }

    /* Deprecated methods */

    /**
     * @deprecated
     * Return active plugin list.
     * @return void
     */
    function static_get_activePlugins() {
        global $camyks;

        /* Log deprecated information */
        $camyks->log_information($this, 'Use of deprecated method static_get_activePlugins.');

        /* Build sql query */
        $sql = 'select * ';
        $sql .= ' from admin_pluginmanager';
        $sql .= ' where active = 1';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Load data from database */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                switch ($data['type']) {
                case 'module':
                    $camyks->modules[$data['plugin']] = module_get($data['plugin'], $data['location']);
                    break;
                case 'theme':
                    $camyks->themes[$data['plugin']] = theme_get($data['plugin'], $data['location']);
                    break;
                case 'template':
                    $camyks->templates[$data['plugin']] = template_get($data['plugin'], $data['location']);
                    break;
                case 'template':
                    $camyks->inputs[$data['plugin']] = input_get($data['plugin'], $data['location']);
                    break;
                }
            }
        }
    }
}
?>
