<?php
/**
 * @brief Admin_SystemUniqueIDManager module.
 * <br /> Provides unique ids on requests.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Jan 2015
 * @date Modification: Jul 2025
 * @copyright 2015 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemUniqueIDManager class.
 */
final class Admin_SystemUniqueIDManager extends Module {
    /**
     * var Object $keyItem
     * @brief Unique id object.
     */
    public $keyItem;

    /**
     * var array $uniqueIDList
     * @brief Unique id list.
     */
    public $keyList = null;

    /**
     * var Object $config
     * @brief Plugin configuration.
     */
    protected $config;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_SystemUniqueIDManager', $path_type);

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

        /* Load plugin libraries */
        $this->load_library('Admin_SystemUniqueIDManagerKey');
        $this->load_library('Admin_SystemUniqueIDManagerConfig');

        /* Initialise plugin libraries */
        $this->keyItem = new Admin_SystemUniqueIDManagerKey(0, $this);
        $this->config = new Admin_SystemUniqueIDManagerConfig('config', $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->keyItem->install() and parent::install());
    }

    /**
     * Unintall module.
     * @return boolean success
     */
    public function uninstall() {
        return parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->keyItem->is_installed();
    }

    /**
     * Define module permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;

        $this->rights[0] = array(
            'name'      =>'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
           );

        $this->rights[1] = array(
            'name'      =>'write',
            'title'     => $camyks->get_translation('write'),
            'default'   => false,
           );
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

        /* Load configuration */
        $this->config->get();

        /* Load action to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        switch ($this->mode) {
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_edit_config();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_save_config();
                break;
            case 'create_key':
                /* mode == create_key */
                $this->init_admin_create_key();
                break;
            case 'delete_key':
                /* mode == delete_key */
                $this->init_admin_delete_key();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* Perform generic initialisation */
        parent::init_admin();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/main mode
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* Build uniqueID tab */
        $this->load_library('Admin_SystemUniqueIDManagerKeyListParams');
        $this->keyList = &$camyks->inputs['AdminItemListViewer'];
        $this->keyList->set_params($this->keyListParams);
        $this->keyList->initialise();

        /* Load data */
        $this->generatingMethodList = $this->get_keyGeneratingMethodList();
        $this->totalGeneratedKeys = $this->count_keys();
        $this->freeGeneratedKeys = $this->count_keys(array('status'=>0));

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Summary',
                'title' => $this->get_translation('formtitle_summary'),
            ),
            array(
                'name'  => 'Keys',
                'title' => $this->get_translation('keys'),
            ),
        ));

        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Keys'));

        /* Load buttons */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
    }

    /**
     * Initialise module object in admin/edit_config mode
     * @return void
     */
    private function init_admin_edit_config() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Build tabs */
        $this->tabBuilder = &$camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'Configuration',
            'title' => $this->get_translation('formtitle_configuration'))
           );

        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));
        $this->tabBuilder->initialise(array('default'=>'Configuration'));

         /* Load data */
        $this->generatingMethodList = $this->get_keyGeneratingMethodList();

        /* Build form */
        $this->editform = new HTMLForm('edit_config', $this->get_adminlink(array('mode'=>'save_config')), 'POST');
        $this->editform->set_object($this->config);

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
               ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
               ),
           );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_config.html.inc');
    }

    /**
     * Initialise module object in admin/save_config mode.
     * @return void
     */
    private function init_admin_save_config() {
        global $camyks;

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save config object */
        $this->config->get_fromHeader();
        if ($this->config->save()) {
            $this->text = $this->get_translation('config_saved');
        } else {
            $this->text = $this->get_translation('config_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/create_key mode.
     * @return void
     */
    private function init_admin_create_key() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Create object */
        $this->keyItem->initialise();
        if ($this->keyItem->save())
            $this->text = $this->get_translation('key_created');
        else
            $this->text = $this->get_translation('key_notcreated');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'uniqueIDs')));
    }

    /**
     * Initialise module object in admin/delete_key mode.
     * @return void
     */
    private function init_admin_delete_key() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Delete object */
        $this->keyItem->id = isset($_REQUEST['key_id']) ? (int)$_REQUEST['key_id'] : 0;
        $this->keyItem->get();
        $this->keyItem->get_fromItems();
        if ($this->keyItem->is_deletable() and $this->keyItem->delete())
            $this->text = $this->get_translation('key_deleted');
        else
            $this->text = $this->get_translation('key_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'uniqueIDs')));
    }

    /* Mark: Attribes data values methods */

    /**
     * Return single key status list.
     * @return array
     */
    protected function get_keyStatusList() {
        return $this->keyItem->get_statusList();
    }

    /**
     * Return keys status list.
     * @param boolean $more
     */
    protected function get_keysStatusList($more=false) {
        return $this->keyItem->get_multiStatusList($more);
    }

    /**
     * Return keys generating method list.
     * @return array
     */
    protected function get_keyGeneratingMethodList() {
        return $this->keyItem->get_generatingMethodList();
    }

    /**
     * Return keys count.
     * @param array $params
     * @return integer
     */
    public function count_keys($params=array()) {
        return $this->keyItem->count($params);
    }

    /**
     * Return key list.
     * @param array $params
     * @return array
     */
    public function get_keyList($params=array()) {
        return $this->keyItem->get_list($params);
    }

    /* Mark: External request methods */

    /**
     * Return new unique ID.
     * @param string $plugin
     * @param string $object
     * @return mixed // unique ID on success, false on failure
     */
    public function get_newUniqueID($plugin, $object) {
        if (!$this->keyItem->load_freeItem())
            $this->keyItem->initialise();
        $this->keyItem->_libItems['plugin']->value = $plugin;
        $this->keyItem->_libItems['object']->value = $object;
        if ($this->keyItem->save()) {
            $this->keyItem->get_fromItems();
            return $this->keyItem->vars['uniqueID'];
        }
        return false;
    }

    /**
     * Return given config item value.
     * @param string $item
     * @return mixed
     */
    public function get_configValue($item) {
        if (!isset($this->config->vars))
            $this->config->get();
        if (isset($this->config->vars[$item]))
            return $this->config->vars[$item];
        return false;
    }
}
?>
