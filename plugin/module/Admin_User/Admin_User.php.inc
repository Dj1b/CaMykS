<?php
/**
 * @brief Admin_User Module
 * <br /> Manage administration users.
 * @details Plugin, Module Engine
 * @file plugin/module/Admin_User/Admin_User.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1
 * @date Creation: Jun 2005
 * @date Modification: Mar 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_User class.
 */
final class Admin_User extends Module {
    /**
     * var Object $user
     * @brief Current user object.
     */
    public $user;

    /**
     * var array $user_list
     * @brief User list.
     */
    public $user_list;

    /**
     * var integer $layout_itemsByLine
     * @brief Define layout items by line.
     */
    public $layout_itemsByLine = 3;

    /**
     * var integer $layout_cellwidth
     * @brief Define layout cell width.
     */
    public $layout_cellwidth = '180px';

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_User', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'System';
        $this->version = '1.1';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'users';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libray */
        $this->load_library('AdminUser');

        /* Initialise plugin libraries */
        $this->user = new AdminUser('');
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->user->install() and parent::install());
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->user->is_installed();
    }

    /**
     * Update plugin.
     * @return boolean
     */
    public function update($version, $more='') {
        global $camyks;

        if (version_compare($version, '1.1', '<'))
            if (!$this->update_toVersion1_1()) return false;

        parent::update($version, $more);
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

        /* Load module mode */
        $this->mode = (isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'list');

        /* Execute action*/
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
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/list mode
     * @return void
     */
    private function init_admin_list() {
        global $camyks;

        /* Load params */
        $this->load_library('Admin_UserListParams');
        $this->params = new Admin_UserListParams(0, $this);
        $this->params->initialise();
        $this->params->get_fromHeader();
        $this->params->get_fromItems();

        /* Build list params form */
        $this->listForm = new HTMLForm('listForm', $this->get_adminLink(), 'POST');
        $this->listForm->set_object($this->params);

        /* Load data */
        $this->usersStatusList = $this->user->get_usersStatusList(array('addAll'=>true));

        /* Get user list */
        $this->user_list = $this->user->get_userList($this->params->build_whereStatement());

        /* Button list for buttons bar */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $camyks->get_adminLink(),
        ));

        /* Update layout */
        $this->set_selectedLayout('admin_list.html.inc');
    }

    /**
     * Initialise module object in admin/edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;

        /* Check write permission */
        if ($this->check_right(1)===false)
            return $this->init_admin_actionNotAllowed();

        /* Load user profile to modify */
        if ($this->user->login == '') {
            $this->user->login = isset ($_REQUEST['user']) ? $_REQUEST['user'] : '';
            $this->user->get();
        } else {
            $this->user->initialise();
        }

        /* Build form */
        $this->form = new HTMLForm('adminuser', $this->get_adminLink(), 'POST');
        $this->form->add_hidden('mode', 'save');
        $this->form->add_hidden('adminuser_full_update', 1);
        $this->form->add_hidden('adminuser_webmaster', $this->user->webmaster);
        $this->form->add_hidden('adminuser_is_new', $this->user->is_new);

        /* Check if a user is modifying a webmaster */
        if ($camyks->adminUser->webmaster == 0 and $this->user->webmaster == 1) {
            $this->text = $this->get_translation('usermodificationnotallowed');
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink(array('mode'=>'list')));
            return;
        }

        /* Load help */
        $this->get_help();

        /* Build tabs */
        if (!isset($camyks->inputs['TabBuilder']))
            $this->tabBuilder = input_get('TabBuilder', 'camyks');
        else
            $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* Check if TabBuilder plugin is available */
        if ($this->tabBuilder === false)
            $camyks->throwFatalError(array(
                'title'         => $this->get_translation('error_pluginmissing_title'),
                'description'   => $this->get_translation('error_pluginmissing_desc', 'TabBuilder'),
           ));

        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Properties',
                'title' => $this->get_translation('personalinfos'),
           ),
            array(
                'name'  => 'Rights',
                'title' => $this->get_translation('rights'),
            ),
        ));

        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* Build buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'    => $this->get_adminLink(),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'    => $this->form->get_HTMLSubmitLink(),
            )
        );

        /* Adds javascript for new passord entries */
        if ($this->user->is_new == 0) {
            $this->add_JSEngineFile('object/cmdd.js');
            $this->add_JSScript('adminuser_pwdObject = new Cmdd();');
            $this->add_JSScript('adminuser_pwdObject.init("changepwd", "","","","");');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_edit.html.inc');
    }

    /**
     * Initialise module object in admin/view mode.
     * @return void
     */
    private function init_admin_view() {
        global $camyks;

        /* get user profile to view */
        $this->user = new AdminUser ((isset ($_REQUEST['user']) ? $_REQUEST['user'] : ''));
        $this->user->get();

        /* get help */
        $this->get_help();

        /* build tabs */
        if (!isset($camyks->inputs['TabBuilder']))
            $this->tabBuilder = input_get('TabBuilder', 'camyks');
        else
            $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* check if TabBuilder plugin is available */
        if ($this->tabBuilder === false)
            $camyks->throwFatalError(array(
                'title'         => $camyks->get_translation('error_pluginmissing_title'),
                'description'   => $camyks->get_translation('error_pluginmissing_desc', 'TabBuilder'),
           ));

        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Properties',
                'title' => $this->get_translation('personalinfos'),
           ),
            array(
                'name'  => 'Rights',
                'title' => $this->get_translation('rights'),
            ),
        ));

        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* Build buttons */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $this->get_adminLink(array('mode'=>'list')),
        ));
        if ($this->check_right(1)===true)
            $this->buttons[] = array(
                'title' => $camyks->get_translation('edit'),
                'link'  => $this->get_adminLink(array('mode'=>'edit', 'user'=>$this->user->login)),
           );

        /* Update layout */
        $this->set_selectedLayout('admin_view.html.inc');
    }

    /**
     * Initialise module object in admin/delete mode
     * @return void
     */
    private function init_admin_delete() {
        /* to do */
    }

    /**
     * Initialise module object in admin/save mode
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Check edit permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load user */
        $this->user = new AdminUser();
        $this->user->get_fromHeader('adminuser_');

        /* Save user */
        if ($this->user->save()) {
            $this->text = $camyks->get_translation('savedone');
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink(array('mode'=>'view', 'user'=> $this->user->login)));
        } else {
            $this->init_admin_edit();
        }
    }

    /* Specific tool methods */

    /**
     * Return structured array with name and email.
     * @param string $login
     * @return array
     */
    public function get_userNameAndEmail($login) {
        $user = new AdminUser($login);
        $user->get_fromDatabase();
        return array(
            'login'     => $user->login,
            'firstname' => $user->firstname,
            'lastname'  => $user->lastname,
            'email'     => $user->email,
        );
    }

    /**
     * Return structured array of all active users.
     * @param integer $objMode
     * @return array
     */
    public function get_activeUserList($objMode=false) {
        return $this->user->get_activeUserList($objMode);
    }

    /**
     * Return all users list.
     * @param string $where
     * @param integer $objMode
     * @return array
     */
    public function get_userList($where='', $objMode=false) {
        return $this->user->get_userList($where, $objMode);
    }

    /**
     * Return status values.
     * @return array
     */
    public function get_userStatusList() {
        global $camyks;
        $list = array();
        $list[0] = $camyks->get_translation('inactive');
        $list[1] = $camyks->get_translation('active');
        return $list;
    }

    /* Update methods */

    /**
     * Apply version 1.1 update.
     * @return boolean success
     */
    private function update_toVersion1_1() {
        return ($this->user->update_toVersion1_1());
    }
}
?>
