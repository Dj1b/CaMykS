<?php
/**
 * @brief Admin_ToDoList module.
 * <br /> Manages shared to do list for admin users.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_ToDoList class.
 */
final class Admin_ToDoList extends Module {
    /**
     * var Object $item
     * @brief Task object.
     */
    public $item;

    /**
     * var Object $comment
     * @brief Comment object.
     */
    public $comment;

    /**
     * var array $todolist
     * @brief Task list.
     */
    public $todolist = null;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_ToDoList', $path_type);

        /* Override Plugins variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'helpers';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_ToDoItem');
        $this->load_library('Admin_ToDoComment');

        /* initialise plugin libraries */
        $this->item = new Admin_ToDoItem(0, $this);
        $this->comment = new Admin_ToDoComment(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->item->install() and $this->comment->install()
            and parent::install();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->comment->is_installed();
    }

    /**
     * Define module permissions.
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
            'name'      => 'write',
            'title'     => $camyks->get_translation('write'),
            'default'   => true,
        );
    }

    /**
     * Update description in control panel.
     * @return void
     */
    public function get_adminControlPanelAction() {
        global $camyks;
        $n = $this->item->get_objectCount('to_user="" or to_user="'.$camyks->adminUser->login.'" or from_user="'.$camyks->adminUser->login.'"');
        $camyks->trads['mod_admin_todolist_desc'] = $this->get_translation('desc_', $n);
    }


    /**
     * Initialise module object in admin mode.
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
            case 'savecomment':
                /* mode == savecomment */
                $this->init_admin_savecomment();
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
        parent::init_admin();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/list mode.
     * @return void
     */
    public function init_admin_list() {
        global $camyks;
        /* get to-do-items list */
        $this->todolist = $this->item->get_objectList(false, 'to_user="" or to_user="'.$camyks->adminUser->login.'" or from_user="'.$camyks->adminUser->login.'"');
        /* get tabs engine */
        $this->get_admin_tabs();
    }

    /**
     * Initialise module object in admin/edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;

        if ($this->check_right(1)===false) {
            return $this->init_admin_actionNotAllowed();
        }

        /* get user profile to modify */
        if ($this->item->id == -1) {
            $this->item->id = isset($_REQUEST['todo']) ? $_REQUEST['todo'] : 0;
            $this->item->get();
        }

        /* get form */
        $this->form = new HTMLForm('admintodolist', $this->get_adminLink(), 'POST');
        $this->form->add_hidden('mode', 'save');
        $this->form->add_hidden('todo', $this->item->id);
        $this->form->add_hidden('from_user', $this->item->vars['from_user']);
        $this->form->add_hidden('creation_date', $this->item->vars['creation_date']);

        /* get list(and tabs engine) */
        $this->init_admin_list();

        /* select tabs */
        $this->add_JSLoadScript('admin_todolist_tabObject.mouseclick("edit");');
    }

    /**
     * Initialise module object in admin/view mode.
     * @return void
     */
    private function init_admin_view() {
        global $camyks;
        /* get user profile to view */
        $this->item->id = isset($_REQUEST['todo']) ? $_REQUEST['todo'] : 0;
        $this->item->get();

        /* get comment form */
        $this->form = new HTMLForm('admintodolist', $this->get_adminLink(), 'POST');
        $this->form->add_hidden('mode', 'savecomment');
        $this->form->add_hidden('todo', $this->item->id);
        $this->form->add_hidden('from_user', $camyks->adminUser->login);
        $this->form->add_hidden('creation_date', -1);

        /* select tabs */
        $this->add_JSLoadScript('admin_todolist_tabObject.mouseclick("view");');

        /* get list(and tabs engine) */
        $this->init_admin_list();
    }

    /**
     * Initialise module object in admin/delete mode.
     * @return void
     */
    private function init_admin_delete() {
        global $camyks;

        /* Check rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menus */
        $this->disable_adminEngineMenus();

        /* get item */
        $this->item->id = isset($_REQUEST['todo']) ? (int)$_REQUEST['todo'] : 0;
        if ($this->item->delete_fromDatabase()) {
            $this->text = $camyks->get_translation('deletedone');
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink(array('mode'=>'list')));
        } else {
            $this->init_admin_edit();
        }
    }

    /**
     * Initialise module object in admin/save mode.
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Check rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menus */
        $this->disable_adminEngineMenus();

        /* get item */
        $this->item->id = isset($_REQUEST['todo']) ? (int)$_REQUEST['todo'] : 0;
        $this->item->get_fromHeader();
        if ($this->item->save()) {
            $this->text = $camyks->get_translation('savedone');
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink(array('mode'=>'view', 'todo'=> $this->item->id)));
        } else {
            $this->init_admin_edit();
        }
    }

    /**
     * Initialise module object in admin/savecomment mode.
     * @return void
     */
    private function init_admin_savecomment() {
        global $camyks;

        /* disable admin menus */
        $this->disable_adminEngineMenus();

        /* get comment item */
        $this->comment->id = 0;
        $this->comment->get_fromHeader();
        if ($this->comment->save()) {
            $this->text = $this->get_translation('commentsaved');
        } else {
            $this->text = $this->get_translation('commentnotsaved');
        }
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view', 'todo'=> $this->comment->_libItems['todo']->value)));
    }

    /* Mark: Specific tool methods */

    /**
     * Inserts javascript for tabs.
     * @return void
     */
    private function get_admin_tabs() {
        global $camyks;
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript('admin_todolist_tabObject = new CTab();');
        $this->add_JSScript('admin_todolist_tabObject.init("general", "'.$camyks->theme->parts['boxTabCSSStandart'].'","'.$camyks->theme->parts['boxTabCSSSelected'].'","'.$camyks->theme->parts['boxTabCSSRollover'].'");');
    }
}
?>
