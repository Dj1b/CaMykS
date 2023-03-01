<?php
/**
 * @brief Tool_Login Module.
 * <br /> System module to log in/out admin section.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.2
 * @date Creation: Jun 2005
 * @date Modification: Feb 2022
 * @copyright 2005 - 2022 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Tool_Login class.
 */
final class Tool_Login extends Module {
    /**
     * var string $login
     * @brief Input login value.
     */
    protected $login;

    /**
     * var string $pwd
     * @brief Input password value.
     */
    protected $pwd;

    /**
     * var array $languages
     * @brief Available languages for admin section.
     */
    protected $adminLanguages;

    /**
     * var object $form
     * @brief Used form to log in.
     */
    protected $form;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        /* get Module generic init */
        parent::__construct('Tool_Login', $path_type);

        /* Override Plugin variables */
        $this->version = '1.1';
        $this->plugin_package = 'System';

        /* Override Module variables */
        $this->type = 'tool';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Override Module methods */

    /**
     * Return menu item to be registered.
     * @return array
     */
    public function get_adminEngineGenericMenuItems() {
        return array(array(
            'menu'  => 'admin',
            'name'  => 'logout',
            'title' => $this->get_translation('logout'),
            'url'   => $this->get_adminLink(array('mode'=>'logout')),
            'icon'  => $this->get_fileURL('img/icon12.gif'),
        ));
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Load mode */
        $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'login';

        /* Execute initialisation following mode */
        switch($mode) {
            case 'logout': return $this->init_admin_logout();
            case 'confirm2FA': return $this->init_admin_confirm2FA();
            case 'login': default:
                if (!is_null($camyks->get_sessionValue('require2FA', null)))
                    return $this->init_admin_display2FA();
                return $this->init_admin_login();
        }
    }

    /* admin mode methods */

    /**
     * Initialise module object in admin / login mode.
     * @return void
     */
    private function init_admin_login() {
        global $camyks;

        /* Initialise values */
        $this->text = '';

        /* Check if a user is loging in */
        if (isset($_REQUEST['login'])) {
            $this->login = isset($_REQUEST['login']) ? $_REQUEST['login'] : '';
            $this->pwd = isset($_REQUEST['pwd']) ? $_REQUEST['pwd'] : '';

            $this->user = new AdminUser($this->login);

            /* Check password */
            if ($this->user->can_login($this->pwd)) {

                /* Check for 2FA authentication */
                if (($plugin = $camyks->modules['Admin_User']->get_configValue('authentication_2factorInput')) !== '') {
                    if ($camyks->get_input($plugin) !== false and $this->user->get() and $this->user->twoFactorData !== '') {
                        $camyks->set_sessionValue('require2FA', $this->user->login);
                        header('Location:'.$camyks->get_adminLink());
                        die();
                    }
                }

                /* Log user in */
                $this->log_userIn();

            } else {
                /* Add stat */
                if (!$camyks->log('AdminLogin', 'Login', 'Failure ('.$this->login.')'))
                    $camyks->update_statistic('adminloginfailed', $this->name, 'single', $this->login, client_getIp(), '', array('checkIPFilter'=>0));
                /* Add message */
                $this->text = $this->get_translation('loginfailed');
            }
        }

        /* Load languages */
        $this->adminLanguages = array();
        foreach ($camyks->get_confValue('admin_languages') as $l)
            $this->adminLanguages[$l] = language_getTitle($l);

        /* Build form */
        $this->form = new HTMLForm('login', $camyks->get_adminLink(), 'POST');

        /* Build button list */
        $this->buttons = array(
            array(
                'title' => $this->get_translation('access'),
                'url'   => $this->form->get_HTMLSubmitLink(),
            )
        );
    }

    /**
     * Initialise module object in admin / display2FA mode.
     * @return void
     */
    private function init_admin_display2FA() {
        global $camyks;

        /* Load 2FA plugin */
        if (!$this->load_2FAPlugin()) {
            header('Location:'.$camyks->get_adminLink());
            die();
        }

        /* Load user for 2FA authentication */
        if (!$this->load_userFor2FAAuthentication()) {
            header('Location:'.$camyks->get_adminLink());
            die();
        }

        /* Build HTML form */
        $this->form = new HTMLForm('Confirm2FA', $this->get_adminLink(array('mode'=>'confirm2FA')), 'POST');

        /* Execute 2FA plugin in for user login confirmation */
        $this->plugin->prepare_userLogin(array(
            'form'  => $this->form,
        ));

        /* Build button list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('valid'),
                'url'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_2FA.html.inc');
    }

    /**
     * Initialise module object in admin / confirm2FA mode.
     * @return void
     */
    private function init_admin_confirm2FA() {
        global $camyks;

        /* Load 2FA plugin */
        if (!$this->load_2FAPlugin()) {
            header('Location:'.$camyks->get_adminLink());
            die();
        }

        /* Load user for 2FA authentication */
        if (!$this->load_userFor2FAAuthentication()) {
            header('Location:'.$camyks->get_adminLink());
            die();
        }

        /* Perform 2FA check */
        if ($this->plugin->confirm_userLogin(array('secret'=>$this->user->twoFactorData))) {
            $this->log_userIn();
            return;
        }
        $camyks->set_sessionValue('require2FAMessage', $this->plugin->get_lastError());

        /* 2FA check failed */
        header('Location:'.$camyks->get_adminLink());
        die();
    }

    /**
     * Initialise module object in admin / logout mode.
     * @return void
     */
    private function init_admin_logout() {
        global $camyks;

        /* disable admin menus */
        $this->disable_adminEngineMenus();

        /* kill admin user session */
        if ($camyks->check_adminUser()) {
            $camyks->kill_session();
            $camyks->log('AdminLogin', 'Logout', 'Success');
        }

        /* redirect user to login panel */
        $this->set_redirect($camyks->get_adminLink());

        /* build message panel */
        $this->text = $this->get_translation('logout_message');
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /* Specific tool methods */

    /**
     * Log user in .
     * @return void
     */
    private function log_userIn() {
        global $camyks;

        /* Add user to session */
        $camyks->set_sessionValue('admin_user', $this->user->login);
        $camyks->set_sessionValue('admin_time', time());

        /* Add stat */
        if (!$camyks->log('AdminLogin', 'Login', 'Success ('.$this->user->login.')'))
            $camyks->update_statistic('adminlogin', $this->name, 'single', $this->user->login, client_getIp(), '', array('checkIPFilter'=>0, 'checkAdmin'=>0));
        header('Location:'.$camyks->get_adminLink());
        die();
    }

    /**
     * Load pending user for 2FA authentication.
     * @return boolean success
     */
    private function load_userFor2FAAuthentication() {
        global $camyks;

        /* Check pending account */
        if (($login = $camyks->get_sessionValue('require2FA', '')) === '')
            return false;

        /* Load user */
        $this->user = new AdminUser($login);
        if (!$this->user->get())
            return false;

        /* Check user two factor data */
        if ($this->user->twoFactorData === '')
            return false;

        /* Return success */
        return true;
    }

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
        if ($this->plugin === '')
            return false;

        /* Load plugin object */
        $this->plugin = $camyks->get_input($this->plugin);

        /* Check plugin */
        if ($this->plugin === false)
            return false;

        /* Initialise plugin */
        $this->plugin->initialise();

        /* Return success */
        return true;
    }
}
?>
