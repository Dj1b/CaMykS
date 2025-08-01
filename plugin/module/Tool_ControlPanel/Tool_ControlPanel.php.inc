<?php
/**
 * @brief Tool_ControlPanel module.
 * <br /> Default admin module, hub to website edition.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2005
 * @date Modification: Jul 2025
 * @copyright 2005 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Tool_ControlPanel class.
 */
final class Tool_ControlPanel extends Module {

    /**
     * var int $cols
     * @brief Displayed columns of modules in main layout.
     */
    protected $cols = 2;

    /**
     * var array $admin_modules
     * @brief List of available admin modules by groups.
     */
    protected $admin_modules = array(
        'personal'      => array(),
        'content'       => array(),
        'users'         => array(),
        'configuration' => array(),
        'monitoring'    => array(),
        'helpers'       => array(),
        'devel'         => array(),
        'specific'      => array(),
    );

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Tool_ControlPanel', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'System';

        /* Override Module variables */
        $this->type = 'tool';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override Module methods */

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* List all modules to display */
        foreach ($camyks->modules as $mod_name => $mod) {
            /* Keep only admin type module */
            if ($mod->type == 'admin') {
                /* Check if module is installed */
                if ($mod->is_installed()!== false) {
                    /* Check if user is able to view this module */
                    if ($mod->check_right(0)) {
                        /* Check if an admin type is defined */
                        if (!isset($mod->admin_type)) {
                            $mod->admin_type = 'other';
                        }

                        /* Check if group already exists */
                        if (!isset ($this->admin_modules[$mod->admin_type])) {
                            $this->admin_modules[$mod->admin_type] = array();
                        }

                        /* Add module name in list */
                        $this->admin_modules[$mod->admin_type][] = $mod_name;

                        /* Load specific init */
                        $camyks->modules[$mod_name]->get_adminControlPanelAction();
                    }
                }
            }
        }
    }

    /**
     * Return menu items to be registered.
     * @return array
     */
    public function get_adminEngineGenericMenuItems() {
        return array(
            array(
                'menu'  => 'admin',
                'name'  => 'homepanel',
                'title' => $this->get_translation('adminhome'),
                'url'   => $this->get_adminLink(),
                'icon'  => $this->get_fileURL('img/icon12.gif'),
            ),
        );
    }
}
?>
