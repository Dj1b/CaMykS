<?php
/**
 * @brief Admin_MyShortcuts Module.
 * <br /> Allows logged admin user to manage its admin shortcuts.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: May 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_MyShortcuts Module class.
 */
final class Admin_MyShortcuts extends Module {
    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_MyShortcuts', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'personal';

        /* Deine plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_UserShortcut');

        /* Initialise plugin libraries */
        $this->shortcutItem = new Admin_UserShortcut(0, $this);

        /* Initialise plugin variables */
        $this->shortcutList = null;
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->shortcutItem->install() and parent::install());
    }

    /**
     * Check installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->shortcutItem->is_installed();
    }

    /**
     * Build module permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;

        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => true,
        );
    }

    /**
     * Register a menu in admin interface.
     * @return array
     */
    public function get_adminEngineGenericMenus() {
        if ($this->check_right(0)) {
            return array(array(
                'name'  => 'myshortcuts',
                'title' => $this->get_translation('menutitle'),
            ));
        }
        return array();
    }

    /**
     * Register menu items in admin interface.
     * @return array
     */
    public function get_adminEngineGenericMenuItems() {
        global $camyks;

        /* Check admin user permission */
        if ($this->check_right(0) === false)
            return array();

        /* Build menu items */
        $menu = array(
            array(
                'name'  => 'add_newshortcut',
                'title' => $this->get_translation('add_newshortcut'),
                'icon'  => $this->get_fileURL('img/add12.gif'),
                'menu'  => 'myshortcuts',
                'url'   => 'javascript:adminengine_modalPopupOpen(\'admin_myshortcuts_addpopup\');globalCMenu.unselect(\'myshortcutsMenu\')',
            ),
            array(
                'name'  => 'edit_shortcuts',
                'title' => $this->get_translation('edit_shortcuts'),
                'icon'  => $this->get_fileURL('img/edit12.gif'),
                'menu'  => 'myshortcuts',
                'url'   => $this->get_adminLink(),
            ),
        );

        /* Load user shortcuts list */
        $this->get_userShortcuts();

        if (count($this->shortcutList) > 0) {
            /* Inserts separator in menu */
            $menu[] = array(
                'name'  => 'separator',
                'title' => '----',
                'menu'  => 'myshortcuts',
            );

            /* Inserts shortcuts */
            foreach ($this->shortcutList as $item) {
                $menu[] = array(
                    'name'  => 'shortcut'.$item->id,
                    'title' => $item->vars['name'],
                    'icon'  => $this->get_fileURL('img/favorite12.gif'),
                    'menu'  => 'myshortcuts',
                    'url'   => $camyks->get_confValue('admin_entry').'?'.htmlentities($item->vars['url']),
                );
            }
        }
        return $menu;
    }

    /**
     * Initialise module object adminengine mode.
     * @return void
     */
    public function get_adminEngineGenericInit() {
        global $camyks;

        /* Build form */
        $this->addform = new HTMLForm('admin_myshortcut_addform', $this->get_adminLink(), 'POST');
        $this->addform->add_hidden('mode', 'add_new');
        $this->addform->add_hidden('user', $camyks->adminUser->login);
        $this->addform->add_hidden('url', $_SERVER['QUERY_STRING']);

        /* Build popup buttons */
        $this->popupbuttons = array(
            array(
                'title' => $camyks->get_translation('close'),
                'link'  => 'javascript:adminengine_modalPopupClose(\'admin_myshortcuts_addpopup\');',
            ),
            array(
                'title' => $camyks->get_translation('add'),
                'link'  => $this->addform->get_HTMLSubmitLink(),
            ),
        );
        return;
    }

    /**
     * Display module object in adminengine mode.
     * @return void
     */
    public function get_adminEngineGenericDisplay() {
        $this->load_file('html/adminengine.html.inc');
    }

    /**
     * Initialise object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check admin user permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Load mode */
        $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'main';

        /* Execute action case of mode */
        switch ($this->mode) {
            case 'delete_shortcut':
                $this->init_admin_delete();
                break;
            case 'add_new':
                $this->init_admin_add_new();
                break;
            case 'edit_shortcut':
                $this->init_admin_edit();
                break;
            case 'save_shortcut':
                $this->init_admin_save();
                break;
            case 'open_shortcut':
                $this->init_admin_open();
                break;
            case 'main':
            default:
                $this->init_admin_main();
                break;
        }

        /* Generic module admin initialisation */
        parent::init_admin();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
    public function init_admin_main() {
        global $camyks;

        /* Build shortcut list */
        $this->load_library('Admin_UserShortcutListParams');
        $this->shortcutObjectList = new AdminItemListViewer('camyks');
        $this->shortcutObjectList->set_params($this->shortcutListParams);
        $this->shortcutObjectList->initialise();

        /* Build buttons */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $camyks->get_adminLink(),
        ));
    }

    /**
     * Initialise module object in admin/delete mode.
     * @return void
      */
    private function init_admin_delete() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object id */
        $this->shortcutItem->id = isset($_REQUEST['shortcut_id']) ? (int)$_REQUEST['shortcut_id'] : 0;

        /* Delete object */
        if ($this->shortcutItem->delete()) {
            $this->text = $camyks->get_translation('deletedone');
        } else {
            $this->text = $camyks->get_translation('deletefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/add_new mode.
     * @return void
      */
    private function init_admin_add_new() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->shortcutItem->get_fromHeader();
        if ($this->shortcutItem->save()) {
            $this->text = $camyks->get_translation('savedone');
            $this->set_redirect($camyks->get_confValue('admin_entry').'?'.$this->shortcutItem->_libItems['url']->value);
        } else {
            $this->text = $camyks->get_translation('savefailed');
            $this->set_redirect($camyks->get_adminLink());
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/edit mode.
     * @return void
      */
    private function init_admin_edit() {
        global $camyks;

        /* Load object id */
        $this->shortcutItem->id = isset($_REQUEST['shortcut_id']) ? (int)$_REQUEST['shortcut_id'] : 0;
        $this->shortcutItem->get();
        $this->shortcutItem->get_fromItems();

        /* Check shortcut */
        if ($this->shortcutItem->vars['user'] != $camyks->adminUser->login) {
            $this->text = $this->get_translation('accessdenied');
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink());
            return;
        }

        /* add form object */
        $this->form = new HTMLForm('admin_myshortcuts', $this->get_adminLink(array('mode'=>'save_shortcut')), 'POST');
        $this->form->set_object($this->shortcutItem);
        $this->form->add_hidden('shortcut_id', $this->shortcutItem->id);

        /* Build buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(),
            ),
            array(
                'link'  => $this->form->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit.html.inc');
    }

    /**
     * Initialise module object in admin/edit mode.
     * @return void
      */
    private function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object id */
        $this->shortcutItem->id = isset($_REQUEST['shortcut_id']) ? (int)$_REQUEST['shortcut_id'] : 0;

        /* Load object data */
        $this->shortcutItem->get_fromHeader();

        /* Save object */
        if ($this->shortcutItem->save()) {
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_redirect($this->get_adminLink());
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/open mode.
     * @return void
      */
    private function init_admin_open() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object id */
        $this->shortcutItem->id = isset($_REQUEST['shortcut_id']) ? (int)$_REQUEST['shortcut_id'] : 0;

        /* Load object data */
        $this->shortcutItem->get();
        $this->shortcutItem->get_fromItems();

        /* Update layout */
        $this->set_selectedLayout('null.html.inc');
        $this->set_redirect(0, $camyks->get_confValue('admin_entry').'?'.$this->shortcutItem->vars['url']);
    }

    /* Mark: Specific tool methods */

    /**
     * Build current admin user shortcut list.
     * @return void
     */
    private function get_userShortcuts() {
        global $camyks;

        /* Check if list already exists */
        if ($this->shortcutList !== null)
            return;

        /* Load list */
        $this->shortcutList = $this->shortcutItem->get_objectList(false, 'user="'.$camyks->adminUser->login.'"');
    }
}
?>
