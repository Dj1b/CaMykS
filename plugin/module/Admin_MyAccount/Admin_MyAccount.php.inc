<?php
/**
 * @brief Admin_MyAccount Module.
 * <br /> Allows logged admin user to read or edit its own information.
 * @details Plugin / Module Engine
 * @file plugin/module/Admin_MyAccount/Admin_MyAccount.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Jan 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_MyAccount Module class.
 */
final class Admin_MyAccount extends Module {
    /**
     * var Object $myAccount
     * @brief Configuration object.
     */
    protected $myAccount;

    /**
     * Class constructor.
     * @param boolean $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_MyAccount', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'personal';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Override Module methods */

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
        $this->rights[1] = array(
            'name'      => 'write',
            'title'     => $camyks->get_translation('write'),
            'default'   => true,
        );
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* get informations */
        $this->myAccount = &$camyks->adminUser;
        $this->mode = (isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : '');

        /* if user has no rights for this module, make redirection to home */
        if ($this->check_right(0) === false) {
            return $this->init_admin_accessDenied() ;
        } else if ($this->check_right(1) === false) {
            $this->init_admin_view();
        } else {
            switch ($this->mode) {
                case 'save':
                    /* mode == save */
                    $this->init_admin_save();
                    break;
                case 'modify':
                default:
                    /* mode == modify */
                    $this->init_admin_modify();
                    break;
            }
        }
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/view mode.
     * @return void
     */
    private function init_admin_view() {
        global $camyks;

        /* Build button list */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $camyks->get_adminLink(),
        ));

        /* Update layout */
        $this->set_selectedLayout('admin_read.html.inc');
    }

    /**
     * Initialise module object in admin/modify mode.
     * @return void
     */
    private function init_admin_modify() {
        global $camyks;

        /* Build form */
        $this->form = new HTMLForm('myAccount', $this->get_adminLink(array('mode'=>'save')), 'POST');
        $this->form->add_hidden('myaccount_login', $this->myAccount->login);
        $this->form->add_hidden('myaccount_fullupdate', '0');

        /* update focus */
        $this->add_JSLoadScript('document.'.$this->form->name.'.myaccount_lastname.focus();');

        /* Set password layout javascript */
        $this->add_JSEngineFile ('object/cmdd.js');
        $this->add_JSScript('myaccount_pwdObject = new Cmdd();');
        $this->add_JSScript('myaccount_pwdObject.init("changepwd", "","","","");');
        $this->add_JSLoadScript('myaccount_pwdObject.selectItem(0);');

        /* Build button list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            )
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit.html.inc');
    }

    /**
     * Initialise module object in admin/save mode.
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Load account data */
        $this->myAccount->get_fromHeader('myaccount_');
        $this->myAccount->is_new = false;

        /* Save account */
        if ($this->myAccount->save()) {
            /* Disable admin menus */
            $this->disable_adminEngineMenus();

            /* Create text message */
            $this->text = $this->get_translation('savedone');

            /* Update layout */
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink(array('mode'=> 'modify')));
        } else {
            $this->init_admin_modify();
        }
    }
}
?>
