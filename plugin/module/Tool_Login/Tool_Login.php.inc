<?php
/**
 * @brief Tool_Login Module
 * <br /> System module to log in/out admin section.
 * @details Plugin / Module Engine
 * @file plugin/module/Tool_Login/Tool_Login.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1
 * @date Creation: Jun 2005
 * @date Modification: Jun 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Tool_Login Module class.
 * @author CaMykS Team <camyks.contact@gmail.com>
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

        /* set module type */
        $this->type = 'tool';

        /* set plugin version */
        $this->version = '1.1';

        /* set plugin package */
        $this->plugin_package = 'System';

        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite Module methods */
    
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
    public function init_admin () {
        $mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'login';
        switch($mode) {
            case 'logout': return $this->init_admin_logout();
            case 'login': default: return $this->init_admin_login();
        }
    }
    
    /* admin mode methods */
    
    /**
     * Initialise module object in admin / login mode.
     * @return void
     */
    private function init_admin_login() {
        global $camyks;

        /* init values */
        $this->text = '';

        /* check if a user is loging */
        if (isset($_REQUEST['login'])) {
            $this->login = (isset($_REQUEST['login']) ? $_REQUEST['login'] : '');
            $this->pwd = (isset($_REQUEST['pwd']) ? $_REQUEST['pwd'] : '');

            $user = new AdminUser($this->login);
            if ($user->can_login($this->pwd)) {
                $camyks->set_sessionValue('admin_user', $this->login);
                $camyks->set_sessionValue('admin_time', time());
                                
                 /* add stat */
                 if (!$camyks->log('AdminLogin', 'Login', 'Success ('.$this->login.')'))
                    $camyks->update_statistic('adminlogin', $this->name, 'single', $this->login, client_getIp(), '', array('checkIPFilter'=>0, 'checkAdmin'=>0));
                $this->selected_layout = 'null';
                header('Location:'.$camyks->get_adminLink());
                die();
            } else {
                /* add stat */
                if (!$camyks->log('AdminLogin', 'Login', 'Failure ('.$this->login.')'))
                    $camyks->update_statistic('adminloginfailed', $this->name, 'single', $this->login, client_getIp(), '', array('checkIPFilter'=>0));
                /* */
                $this->text = $this->get_translation('loginfailed');
            }
        }

        /* get languages */
        $this->adminLanguages = array();
        foreach ($camyks->get_confValue('admin_languages') as $l)
            $this->adminLanguages[$l] = language_getTitle($l);

        /* build form */
        $this->form = new HTMLForm('login', $camyks->get_adminLink(), 'POST');

        /* build button list */
        $this->buttons = array(
            array(
                'title' => $this->get_translation('access'),
                'url'   => $this->form->get_HTMLSubmitLink(),
            )
        );

        /* load extension plugins */
        $this->load_extensions();
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
    
    /* specific tool methods */

    /**
     * Load registered extension plugins.
     * @return void
     */
    private function load_extensions() {
        $this->extensions = $this->get_registeredExtensions();
    }
}
?>
