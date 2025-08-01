<?php
/**
 * @brief Admin_DocumentManager module.
 * <br /> Manage documents in master website repository.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_DocumentManager class.
 */
final class Admin_DocumentManager extends Module {
    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_DocumentManager', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'Default';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override module methods */

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Buttons list */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $camyks->get_adminLink(),
        ));

        /* Load FileManager Input object */
        if (isset ($camyks->inputs['FileManager'])) {
            $this->fileManager = &$camyks->inputs['FileManager'];
            $this->fileManager->set_themeValues($this->theme);
            $this->fileManager->set_engineValues('manage', $this->get_adminLink(), array(
                'add'       => $this->check_right(1)?'1':'0',
                'remove'    => $this->check_right(2)?'1':'0',
            ));
            $this->fileManager->initialise();
        } else {
            $this->init_admin_missingPlugin('Input', 'FileManager');
        }

        /* generic init */
        parent::init_admin();
    }

    /**
     * Define permissions for this module.
     * @return void
     */
    public function get_rights() {
        global $camyks;

        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => true,
        );
        $this->rights[1] = array(
            'name'      => 'addfile',
            'title'     => $this->get_translation('addfile'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      =>'removefile',
            'title'     => $this->get_translation('removefile'),
            'default'   => false,
        );
        $this->rights[3] = array(
            'name'      =>'alterstructure',
            'title'     => $this->get_translation('alterstructure'),
            'default'   => false,
        );
    }
}
?>
