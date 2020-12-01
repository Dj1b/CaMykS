<?php
/**
 * @brief Admin_Group Module
 * <br /> Manage administration groups.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2007
 * @date Modification: Dec 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_Group class.
 */
final class Admin_Group extends Module {
    /**
     * var Object $group
     * @brief Current group object.
     */
    public $group;

    /**
     * var array $groups
     * @brief Group list.
     */
    public $groups = null;

    /**
     * CLass constructor.
     * @param $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_Group', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'System';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'users';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load library */
        $this->load_library('AdminGroup');
        $this->group = new AdminGroup('', $this);
    }

    /* Override Module methods */

    /**
     * Install module object.
     * @return boolean success
     */
    public function install() {
        return $this->group->install() and  parent::install();
    }

    /**
     * Unsinstall module object.
     * @return boolean success
     */
    public function uninstall() {
        return false;
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    function is_installed() {
        return $this->group->is_installed();
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'list';

        /* Execute action */
        switch ($this->mode) {
            case 'view':
                /* mode == view */
                $this->init_admin_view();
                break;
            case 'edit':
                /* mode == edit */
                $this->init_admin_edit();
                break;
            case 'save':
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'delete':
                /* mode == delete */
                $this->init_admin_delete();
                break;
            case 'list':
            default:
                /* mode == list */
                $this->init_admin_list();
                break;
        }

        /* Execute generic initialisation */
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/list mode
     * @return void
     */
    private function init_admin_list() {
        global $camyks;

        /* Load group list */
        $this->group_list = $this->group->static_getAdminList();

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_list.html.inc');
    }

    /**
     * Initialise module object in admin/edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;

        /* Check edit group permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check dependencies */
        $this->input = $camyks->get_input('QuickItemList');
        if ($this->input === false)
            return $this->init_admin_missingPlugin('input', 'QuickItemList');

        /* Load group to edit */
        if ($this->group->name == '' and isset ($_REQUEST['group'])) {
            $this->group->name = $_REQUEST['group'];
            $this->group->get();
        }

        /* Build edition form */
        $this->form = new HTMLForm('admin_group_form', $this->get_adminLink(array('mode'=>'save')), 'POST');
        $this->form->add_hidden('is_new', $this->group->is_new);
        $this->form->add_hidden('users', $this->group->users_);
        if ($this->group->is_new == 0) {
            $this->form->add_hidden('name', $this->group->name);
        }

        /* Load user list */
        $this->user_list = $camyks->modules['Admin_User']->user->static_getList();

        /* get list input object */
        $this->input->initialise('userchooser', $this->get_translation('allusers'), $this->user_list, $this->get_translation('selusers'), $this->group->users, $this->form->name, 'users', ':');

        /* get buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(array('mode'=>'list')),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit.html.inc');
    }

    /**
     * Initialise module object in admin/view mode.
     * @return void
     */
    private function init_admin_view() {
        global $camyks;

        /* Check group */
        if (!isset($_REQUEST['group']))
            return $this->set_redirect($this->get_adminLink());

        /* Load group */
        $this->group = new AdminGroup ($_REQUEST['group'], $this);
        if (!$this->group->get())
            return $this->set_redirect($this->get_adminLink());

        /* Load buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(array('mode'=>'list')),
            ),
        );

        if ($this->check_right(1) === true)
            $this->buttons[] = array(
                'title' => $camyks->get_translation('edit'),
                'link'  => $this->get_adminLink(array('mode'=>'edit', 'group'=>$this->group->name)),
            );

        /* update layout */
        $this->set_selectedLayout('admin_view.html.inc');
    }

    /**
     * Initialise module object in admin/delete mode.
     * @return void
     */
    private function init_admin_delete() {
        /* to do */
    }

    /**
     * Initialise module object in admin/save mode.
     * @return void
     */
    function init_admin_save() {
        global $camyks;

        /* Check edit group permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load group */
        $n = isset($_REQUEST['group']) ? $_REQUEST['group'] : '';
        $this->group = new AdminGroup ($n, $this);
        $this->group->get_fromHeader();

        /* Save group */
        if ($this->group->save()) {
            $this->set_redirect($this->get_adminLink(array('mode' => 'view',  'group' => $this->group->name)));

            /* Update layout */
            $this->text = $camyks->get_translation('savedone');
            $this->set_selectedLayout('admin_message.html.inc',  'camyks');
        } else {
            $this->init_admin_edit();
        }
    }

    /* Specific tool methods */

    /**
     * Return all groups.
     * @return array
     */
    public function get_groups() {
        if ($this->groups == null)
            $this->groups = $this->group->get_objectList();
        return $this->groups;
    }
}
?>
