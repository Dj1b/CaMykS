<?php
/**
 * @brief Admin_MyAccount module.
 * <br /> Allows logged admin user to read or edit its own information.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3.1
 * @date Creation: Jun 2005
 * @date Modification: Jul 2025
 * @copyright 2005 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_MyAccount Module class.
 */
final class Admin_MyAccount extends Module {
    /**
     * var Object $myAccount
     * @brief Link to current admin user account object.
     */
    protected $myAccount;

    /**
     * var Object $accountManager
     * @brief Link to admin user management module.
     */
    protected $accountManager;

    /**
     * Class constructor.
     * @param string $path_type
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

    /* Mark: Override Module methods */

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

        /* Check user permissions */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Load informations */
        $this->myAccount = &$camyks->adminUser;
        $this->mode = (isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'view');

        /* Execute mode */
        switch ($this->mode) {
            case 'save':
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'modify':
            case 'edit':
                /* mode == edit */
                $this->init_admin_edit();
                break;
            case 'save_2fa':
                /* mode == save_2fa */
                $this->init_admin_save_2fa();
                break;
            case 'edit_2fa':
                /* mode == edit_2fa */
                $this->init_admin_edit_2fa();
                break;
            case 'reset_2fa':
                /* mode == reset_2fa */
                $this->init_admin_reset_2fa();
                break;
            case 'view':
            default:
                /* mode == view */
                $this->init_admin_view();
                break;
        }

        /* Perform generic init */
        parent::init_admin();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/view mode.
     * @return void
     */
    private function init_admin_view() {
        global $camyks;

        /* Load account manager */
        $this->accountManager = $camyks->get_module('Admin_User');

        /* Build button list */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $camyks->get_adminLink(),
        ));

        /* Check for edit button */
        if ($this->check_right(1)) {
            $this->buttons[] = array(
                'title' => $camyks->get_translation('edit'),
                'link'  => $this->get_adminLink(array('mode'=>'edit')),
            );
        }

        /* Check for 2FA buttons */
        if ($this->accountManager->get_configValue('authentication_2factorInput') !== '') {
            $this->buttons[] = array(
                'title' => $this->get_translation('configure_2fa'),
                'link'  => $this->get_adminLink(array('mode'=>'edit_2fa')),
            );
        }

        /* Update layout */
        $this->set_selectedLayout('admin_read.html.inc');
    }

    /**
     * Initialise module object in admin/modify mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_view();

        /* Build form */
        $this->form = new HTMLForm('myAccount', $this->get_adminLink(array('mode'=>'save')), 'POST');
        $this->form->add_hidden('myaccount_login', $this->myAccount->login);
        $this->form->add_hidden('myaccount_fullupdate', '0');

        /* Update focus */
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

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_view();

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
            $this->set_redirect($this->get_adminLink());
        } else {
            $this->init_admin_edit();
        }
    }

    /**
     * Initialise module object in admin/edit_2fa mode.
     * @return void
     */
    private function init_admin_edit_2fa() {
        global $camyks;

        /* Load 2FA plugin */
        if (!$this->load_2FAPlugin())
            return;

        /* Build HTML form */
        $this->form = new HTMLForm('Configure2FA', $this->get_adminLink(array('mode'=>'save_2fa')), 'POST');

        /* Execute 2FA plugin in for user configuration */
        $theme = $camyks->get_confValue('site_default_theme');
        $theme = &$camyks->get_theme($theme);
        $icon = $theme->get_mainIcon();
        if ($icon !== '')
            $icon = $camyks->get_rootBaseUrl('absolute').$icon;

        $this->plugin->prepare_userConfiguration(array(
            'form'          => $this->form,
            'currentValue'  => $this->myAccount->twoFactorData,
            'accountName'   => $this->myAccount->login,
            'accountIssuer' => $camyks->get_confValue('site_title'),
            'accountImage'  => $icon,
        ));

        /* Update interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('2faauthentication');

        /* Build button list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(),
            ),
            array(
                'title' => $camyks->get_translation('confirm'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Check for reset button */
        if ($this->myAccount->twoFactorData !== '') {
            $this->buttons[] = array(
                'title' => $this->get_translation('reset_2fa'),
                'link'  => $this->get_adminLink(array('mode'=>'reset_2fa')),
            );
        }

        /* Update layout */
        $this->set_selectedLayout('admin_edit2FA.html.inc');
    }

    /**
     * Initialise module object in admin/save_2fa mode.
     * @return void
     */
    private function init_admin_save_2fa() {
        global $camyks;

        /* Load 2FA plugin */
        if (!$this->load_2FAPlugin())
            return;

        /* Execute 2FA plugin in for user configuration */
        $newData = $this->plugin->confirm_userConfiguration(array(
            'currentValue' => $this->myAccount->twoFactorData,
        ));

        /* Check for confirmation */
        if ($newData == false) {
            $this->text = $this->get_translation('2faconfigurationnotconfirmed');
            if (($e = $this->plugin->get_lastError()) !== false)
                $this->text .= '<br />'.$e;
            $this->set_redirect($this->get_adminLink(array('mode'=>'edit_2fa')));
        } else {
            if ($this->myAccount->update_2FAData($newData)) {
                $this->text = $this->get_translation('2faconfigurationupdated');
                $this->set_redirect($this->get_adminLink());
            } else {
                $this->text = $this->get_translation('2faconfigurationnotupdated');
                if (($e = $this->myAccount->get_lastError()) !== false)
                    $this->text .= '<br />'.$e;
                $this->set_redirect($this->get_adminLink(array('mode'=>'edit_2fa')));
            }
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin/reset_2fa mode.
     * @return void
     */
    private function init_admin_reset_2fa() {
        global $camyks;

        /* Load 2FA plugin */
        if (!$this->load_2FAPlugin())
            return;

        /* Reset data */
        if ($this->myAccount->reset_2FAData()) {
            $this->plugin->reset_userConfigurationData();
            $this->text = $this->get_translation('2faconfigurationreset');
        } else
            $this->text = $this->get_translation('2faconfigurationnotreset');

        /* Update layout */
        $this->set_redirect($this->get_adminLink(array('mode'=>'edit_2fa')));
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /* 2FA tool methods */

    /**
     * Load 2FA plugin.
     * @return boolean success
     */
    private function load_2FAPlugin() {
        global $camyks;

         /* Load account manager */
        $this->accountManager = $camyks->get_module('Admin_User');

        /* Load plugin name to use */
        $this->plugin = $this->accountManager->get_configValue('authentication_2factorInput');

        /* Check plugin is defined */
        if ($this->plugin === '') {
            /* Define text message */
            $this->text = $this->get_translation('error_no2faplugindefined');

            /* Update layout */
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink());
            return false;
        }

        /* Load plugin object */
        $this->plugin = $camyks->get_input($this->plugin);

        /* Check plugin */
        if ($this->plugin === false) {
            /* Define text message */
            $this->text = $this->get_translation('error_2fapluginnomoreavailable');

            /* Update layout */
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink());
            return false;
        }

        /* Initialise plugin */
        $this->plugin->initialise();

        /* Return success */
        return true;
    }
}
?>
