<?php
/**
 * @brief Tool_Installer module.
 * <br /> System module used to install a website.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 2.0.3.1
 * @date Creation: Aug 2007
 * @date Modification: Jul 2025
 * @copyright 2005 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Tool_Installer class.
 */
final class Tool_Installer extends Module {

    /**
     * var array $summary
     * @brief Summary data.
     */
    protected $summary;

    /**
     * var boolean $allowInstall
     * @brief Is installation allowed.
     */
    private $allowInstall;

    /**
     * var array $allowInstall
     * @brief List of symbolic links.
     */
    private $symLinks = array('plugin'=>'cplugin', 'engine/data'=>'cdata');

    /**
     * var array $textColors
     * @brief List of colors.
     */
    private $textColors = array('yes' => 'green', 'no' => '#CC3333');

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Tool_Installer', $path_type);

        /* Override Plugin variables */
        $this->version = '2.0';
        $this->plugin_package = 'System';

        /* Override Module variables */
        $this->type = 'tool';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load library */
        $this->load_library('Tool_InstallerParams');
        $this->params = new Tool_InstallerParams(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Load mode to execute */
        $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'welcome';

        /* Load params */
        $this->params->initialise();
        $this->params->load_fromSession('InstallerConfig', true);
        $this->params->initialise_hiddenValues();
        $this->params->get_fromItems();

        /* Add specific styles */
        $bkgdPicture = new FSFile($this->get_filePath('img/bkgd.png'));
        $this->add_styleScript("\n".'body{ background-repeat:no-repeat; background-position:50% 0; background-image:url("'.$bkgdPicture->get_base64Data().'");}');

        /* Installer execution */
        switch ($mode) {
            case 'install':
                /* Mode == install */
                $this->init_admin_install();
                break;
            case 'summary':
                /* Mode == summary */
                $this->init_admin_summary();
                break;
            case 'save_configuration':
                /* Mode == save_configuration */
                $this->init_admin_save_configuration();
                break;
            case 'configuration':
                /* Mode == configuration */
                $this->init_admin_configuration();
                break;
            case 'welcome':
                /* Mode == welcome */
                $this->init_admin_welcome();
                break;
        }
    }

    /* Mark: Admin mode initialise sub methods */

    /**
     * Initialise module object in admin/welcome mode.
     * @return void
     */
    private function init_admin_welcome() {
        global $camyks;

        /* Load camyks logo */
        $this->welcomePicture = new FSFile($camyks->camyks_engine_path.'/data/img/logo/logo500.png');

        /* Update selected layout */
        $this->set_selectedLayout('admin_welcome.html.inc');
    }

    /**
     * Initialise module object in admin/configuration mode.
     * @return void
     */
    private function init_admin_configuration() {
        global $camyks;

        /* Build configuration form */
        $this->configForm = new HTMLForm('configForm', '?mode=save_configuration', 'POST');
        $this->configForm->set_object($this->params);

        /* Load script */
        $this->add_JSScript(file_get_contents($camyks->camyks_engine_path.'/data/js/object/ctab.js'));
        $this->add_JSScript('var cTabs = new CTab();');
        $this->add_JSLoadScript('cTabs.init("", "eTableSubHeader", "eTableSubHeader", "eTableSubHeader");');
        $this->add_JSLoadScript('cTabs.mouseclick("Website");');
        $this->add_JSScript('document.addEventListener("keydown", function (e) {    onTabPressed(e); }, false);');
        $this->add_JSScript('function onTabPressed(e) {');
        $this->add_JSScript('if (e.keyCode != 9) return;');
        $this->add_JSScript('elmnt = document.activeElement.name;');
        $this->add_JSScript('switch (elmnt) {');
        $this->add_JSScript('case "site_company": e.preventDefault(); cTabs.mouseclick("Admin"); document.getElementById("configForm")["_admin_languages_en"].focus(); return;');
        $this->add_JSScript('case "admin_ssl": e.preventDefault(); cTabs.mouseclick("Site"); document.getElementById("configForm")["_site_languages_en"].focus(); return;');
        $this->add_JSScript('case "site_ssl": e.preventDefault(); cTabs.mouseclick("Database"); document.getElementById("configForm")["database_driver"].focus(); return;');
        $this->add_JSScript('case "database_pwd": e.preventDefault(); cTabs.mouseclick("Webmaster"); document.getElementById("configForm")["webmaster_login"].focus(); return;');
        $this->add_JSScript('case "webmaster_email": e.preventDefault(); cTabs.mouseclick("Options"); document.getElementById("configForm")["google_analytics"].focus(); return;');
        $this->add_JSScript('case "mobileMode": e.preventDefault(); cTabs.mouseclick("Website"); document.getElementById("configForm")["site_title"].focus(); return;');
        $this->add_JSScript('}');

        $this->add_JSScript('}');

        /* Load data */
        $this->driverList = Database_connection::get_availableDriverList();
        $this->encodingList = array('utf8'=>'UTF8');
        $this->SSLModeList = $this->params->get_SSLModeList();
        $this->adminThemeList = $this->params->get_adminThemeList();
        $this->siteThemeList = $this->params->get_siteThemeList();
        $this->templateList = $this->params->get_templateList();
        $this->mobileModeList = $this->params->get_mobileModeList();
        $this->languages = $this->params->get_availableLanguages();

        /* Build button list */
        $this->buttons = array(array(
            'title' => $this->get_translation('continue'),
            'link'  => $this->configForm->get_HTMLSubmitLink(),
        ));

        /* Update selected layout */
        $this->set_selectedLayout('admin_configuration.html.inc');
    }

    /**
     * Initialise module object in admin/save_configuration mode.
     * @return void
     */
    private function init_admin_save_configuration() {

        /* Check from header data */
        if (!isset($_REQUEST['site_title'])) {
            header('Location:?mode=configuration');
            die();
        }

        /* Load config from header */
        $this->params->get_fromHeader();
        $this->params->get_fromItems();

        /* Save config */
        $this->params->save_toSession('InstallerConfig');

        /* Go to summary display */
        header('Location:?mode=summary');
    }

    /**
     * Initialise module object in admin/main mode
     * @return void
     */
    private function init_admin_summary() {
        global $camyks;

        /* Define some running vars */
        $this->allowInstall = true;
        $this->summary = array();

        /* Merge personnalised config */
        foreach ($camyks->site_conf as $name => $value) {
            if (isset($this->params->vars[$name])) $camyks->site_conf[$name] = $this->params->vars[$name];
        }

        /* Execute all checks */
        $this->checkCaMykSConfig();
        $this->checkSiteConfig();
        $this->checkPlugins();
        $this->checkDatabase();
        $this->checkSymLinks();
        $this->checkAdminUser();

        /* Build button list */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => '?mode=configuration',
        ));

        if ($this->allowInstall) {
            $this->buttons[] = array(
                'title' => $this->get_translation('install'),
                'link'  => '?mode=install',
           );
        } else {
            $this->buttons[] = array(
                'title' => $this->get_translation('install'),
                'link'  => '',
           );
        }

        /* Update selected layout */
        $this->set_selectedLayout('admin_summary.html.inc');
    }

    /**
     * Initialise module object in admin/install mode.
     * @return void
     */
    private function init_admin_install() {
        global $camyks;

        /* Define some running vars */
        $this->allowInstall = true;
        $this->isInstalled = true;
        $this->buttons = array();
        $this->summary = array();

        /* Merge personnalised config */
        foreach ($camyks->site_conf as $name => $value) {
            if (isset($this->params->vars[$name])) $camyks->site_conf[$name] = $this->params->vars[$name];
        }

        /* Check optional config items */
        if (isset($camyks->site_conf['database_host']) and trim($camyks->site_conf['database_host']) == '') unset($camyks->site_conf['database_host']);
        if (isset($camyks->site_conf['database_login']) and trim($camyks->site_conf['database_login']) == '') unset($camyks->site_conf['database_login']);
        if (isset($camyks->site_conf['database_pwd']) and trim($camyks->site_conf['database_pwd']) == '') unset($camyks->site_conf['database_pwd']);

        /* Build button list */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => '?mode=configuration',
        ));

        /* Basic checks */
        $this->checkSiteConfig();
        $this->checkPlugins();

        /* Install all part if installation is allowed */
        if ($this->allowInstall) {
            /* Erase check message */
            $this->summary = array();

            $this->installDatabase();

            if ($this->isInstalled)
                $this->installPlugins();

            if ($this->isInstalled)
                $this->installsymLinks();

            if ($this->isInstalled) {
                /* finalise installation */
                $this->installDone();
            } else {

            }
        }

        /* Update selected layout */
        $this->set_selectedLayout('admin_summary.html.inc');
    }

    /* Mar: Specific tool methods */

    /**
     * Check CaMykS engine config.
     * @return void
     */
    private function checkCaMykSConfig() {
        global $camyks;

        /* Add CaMykS config title */
        $this->summary[] = array(
            'type'  => 'title',
            'name'  => $this->get_translation('camyksconfigcheck'),
            'value' => '',
        );

        /* Display engine availability */
        $this->summary[] = array(
            'type'  => 'message',
            'name'  => $this->get_translation('availability'),
            'value' => $this->get_translation('ok'),
            'color' => $this->textColors['yes'],
        );

        /* Display engine installation mode */
        $this->summary[] = array(
            'type'  => 'message',
            'name'  => $this->get_translation('installationmode'),
            'value' => $camyks->get_translation($camyks->_installationMode),
        );
    }

    /**
     * Check site configuration file.
     * @return void
     */
    private function checkSiteConfig() {
        global $camyks;

        /* Add configuration file title */
        $this->summary[] = array(
            'type'  => 'title',
            'name'  => $this->get_translation('siteconfigcheck'),
            'value' => '',
        );

        /* Check site/folder name */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('configvalue', 'site_name'),
            'value' => '',
        );

        $folderName = explode('/', realpath('.'));
        $folderName = $folderName[count($folderName)-1];
        if ($folderName == $camyks->site_conf['site_name']){
            $message['value'] = $this->get_translation('ok');
            $message['color'] = $this->textColors['yes'];
        } else {
            $message['value'] = $this->get_translation('sitename_error');
            $message['color'] = $this->textColors['no'];
            $this->allowInstall = false;
        }
        $this->summary[] = $message;

        /* Check site url */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('configvalue', 'url'),
            'value' => '',
        );

        if (isset($camyks->site_conf['url']) and $camyks->site_conf['url'] != '') {
            $message['value'] = $this->get_translation('ok');
            $message['color'] = $this->textColors['yes'];
        } else {
            $message['value'] = $this->get_translation('url_error');
            $message['color'] = $this->textColors['no'];
            $this->allowInstall = false;
        }
        $this->summary[] = $message;

        /* Check admininstation entry file */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('configvalue', 'admin_entry'),
            'value' => '',
        );

        if (isset($camyks->site_conf['admin_entry']) and file_exists(realpath('./'.$camyks->site_conf['admin_entry']))) {
            $message['value'] = $this->get_translation('ok');
            $message['color'] = $this->textColors['yes'];
        } else {
            $message['value'] = $this->get_translation('adminentry_error');
            $message['color'] = $this->textColors['no'];
            $this->allowInstall = false;
        }
        $this->summary[] = $message;

        /* Check database name */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('configvalue', 'database_name'),
            'value' => '',
        );

        if (isset($camyks->site_conf['database_name']) and $camyks->site_conf['database_name'] != '') {
            $message['value'] = $this->get_translation('ok');
            $message['color'] = $this->textColors['yes'];
        } else {
            $message['value'] = $this->get_translation('database_name_error');
            $message['color'] = $this->textColors['no'];
            $this->allowInstall = false;
        }
        $this->summary[] = $message;

        /* Check page_maxmodules (default value is 8) */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('configvalue', 'page_maxmodules'),
            'value' => '',
        );

        if (isset($camyks->site_conf['page_maxmodules']) and $camyks->site_conf['page_maxmodules'] > 0) {
            $message['value'] = $this->get_translation('ok');
            $message['color'] = $this->textColors['yes'];
        } else {
            $message['value'] = $this->get_translation('page_maxmodules_error');
            $this->allowInstall = false;
            $message['color'] = $this->textColors['no'];
        }
        $this->summary[] = $message;
    }

    /**
     * Check database connection.
     * @return void
     */
    private function checkDatabase() {
        global $camyks;

        /* Add database tests title */
        $this->summary[] = array(
            'type'  => 'title',
            'name'  => $this->get_translation('databasecheck'),
            'value' => '',
       );

        /* Create connection */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('database_connection'),
            'value' => '',
        );
        $camyks->db_conn = new Database_connection (
            isset($camyks->site_conf['database_host']) ? $camyks->site_conf['database_host'] : $camyks->_conf['database_host'],
            isset($camyks->site_conf['database_login']) ? $camyks->site_conf['database_login'] : $camyks->_conf['database_login'],
            isset($camyks->site_conf['database_pwd']) ? $camyks->site_conf['database_pwd'] : $camyks->_conf['database_pwd'],
            isset($camyks->site_conf['database_driver']) ? $camyks->site_conf['database_driver'] : $camyks->_conf['database_driver']
        );

        /* Check status */
        $status = $camyks->db_conn->check_status($camyks->site_conf['database_name']);

        if ($status['ServerConnected']) {
            $message['value'] = $this->get_translation('ok');
            $message['color'] = $this->textColors['yes'];
        } else {
            $message['value'] = $this->get_translation('database_connection_failed');
            $message['color'] = $this->textColors['no'];
            $this->allowInstall = false;
        }
        $this->summary[] = $message;

        /* Check if database exists */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('database_db'),
            'value' => ''
        );

        if ($status['DatabaseExists'])
            $message['value'] = $this->get_translation('ok');
        else
            $message['value'] = $this->get_translation('database_dbdoesntexist');

        $this->summary[] = $message;

        /* Close the database */
        $camyks->db_conn->close();
    }

    /**
     * Check symbolic links existance.
     * @return void
     */
    private function checkSymLinks() {
        global $camyks;

        /* Do not install sym links in "dedicated" installation mode */
        if ($camyks->_installationMode == 'dedicated')
            return;

        /* Add symLinks check title */
        $this->summary[] = array(
            'type'  => 'title',
            'name'  => $this->get_translation('symLinkscheck'),
            'value' => '',
        );

        /* Check write right */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('write_rights'),
            'value' => '',
        );
        $myfile = realpath('.');

        if (is_writable($myfile)) {
            $message['value'] = $camyks->get_translation('yes');
            $message['color'] = $this->textColors['yes'];
        } else {
            $message['value'] = $camyks->get_translation('no');
            $message['color'] = $this->textColors['no'];
            $this->allowInstall = false;
        }
        $this->summary[] = $message;

        /* Check symlink exists */
        foreach ($this->symLinks as $l) {
            $message = array(
                'type'  => 'message',
                'name'  => $this->get_translation('symlinkfound', $l),
                'value' => '',
            );

            if (file_exists(realpath('./'.$l))) {
                $message['value'] = $camyks->get_translation('yes');
            } else {
                $message['value'] = $camyks->get_translation('no');
            }
            $this->summary[] = $message;
        }
    }

    /**
     * Check mandatory plugins.
     * @return void
     */
    private function checkPlugins() {
        global $camyks;

        $this->summary[] = array(
            'type'  => 'title',
            'name'  => $this->get_translation('pluginscheck'),
            'value' => ''
        );

        /* Check modules */
        foreach ($camyks->neededModules as $p) {
            $message = array(
                'type'  => 'message',
                'name'  => $camyks->get_translation('modulex', $p['name']),
            );
            if (!isset($camyks->modules[$p['name']])) {
                $message['value'] = $this->get_translation('notfound');
                $message['color'] = $this->textColors['no'];
                $this->allowInstall = false;
            } elseif ($camyks->modules[$p['name']]->version < $p['version']) {
                $message['value'] = $this->get_translation('oldversion');
                $message['color'] = $this->textColors['no'];
                $this->allowInstall = false;
            } else {
                $message['value'] = $camyks->get_translation('yes');
                $message['color'] = $this->textColors['yes'];
            }
            $this->summary[] = $message;
        }

        /* Check inputs */
        foreach ($camyks->neededInputs as $p) {
            $message = array(
                'type'  => 'message',
                'name'  => $camyks->get_translation('inputx', $p['name']),
           );

            if (!isset($camyks->inputs[$p['name']])) {
                $message['value'] = $this->get_translation('notfound');
                $message['color'] = $this->textColors['no'];
                $this->allowInstall = false;
            } elseif ($camyks->inputs[$p['name']]->version < $p['version']) {
                $message['value'] = $this->get_translation('oldversion');
                $message['color'] = $this->textColors['no'];
                $this->allowInstall = false;
            } else {
                $message['value'] = $camyks->get_translation('yes');
                $message['color'] = $this->textColors['yes'];
            }
            $this->summary[] = $message;
        }

        /* Check themes */
        foreach ($camyks->neededThemes as $p) {
            $message = array(
                'type'  => 'message',
                'name'  => $camyks->get_translation('themex', $p['name']),
           );

            if (!isset($camyks->themes[$p['name']])) {
                $message['value'] = $this->get_translation('notfound');
                $message['color'] = $this->textColors['no'];
                $this->allowInstall = false;
            } elseif ($camyks->themes[$p['name']]->version < $p['version']) {
                $message['value'] = $this->get_translation('oldversion');
                $message['color'] = $this->textColors['no'];
                $this->allowInstall = false;
            } else {
                $message['value'] = $camyks->get_translation('yes');
                $message['color'] = $this->textColors['yes'];
            }
            $this->summary[] = $message;
        }

        /* Check templates */
        foreach ($camyks->neededTemplates as $p) {
            $message = array(
                'type'  => 'message',
                'name'  => $camyks->get_translation('templatex', $p['name']),
            );

            if (!isset($camyks->templates[$p['name']])) {
                $message['value'] = $this->get_translation('notfound');
                $message['color'] = $this->textColors['no'];
                $this->allowInstall = false;
            } elseif ($camyks->templates[$p['name']]->version < $p['version']) {
                $message['value'] = $this->get_translation('oldversion');
                $message['color'] = $this->textColors['no'];
                $this->allowInstall = false;
            } else {
                $message['value'] = $camyks->get_translation('yes');
                $message['color'] = $this->textColors['yes'];
            }
            $this->summary[] = $message;
        }
    }

    /**
     * Check admin user.
     * @return void
     */
    private function checkAdminUser() {
        global $camyks;

        if (!$camyks->modules['Admin_User'])
            return;

        /* Add title */
        $this->summary[] = array(
            'type'  => 'title',
            'name'  => $this->get_translation('adminscheck'),
            'value' => ''
        );

        /* Prepare message */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('masteraccount'),
        );

        /* Prepare admin user */
        $user = $camyks->modules['Admin_User']->user;
        $user->login = $this->params->vars['webmaster_login'];
        $user->change_pwd = 1;
        $user->pwd = $this->params->vars['webmaster_password'];
        $user->pwd_conf = $this->params->vars['webmaster_password'];
        $user->email = $this->params->vars['webmaster_email'];

        /* Check admin user */
        if ($user->check_data()) {
            $message['value'] = $camyks->get_translation('yes');
            $message['color'] = $this->textColors['yes'];
        } else {
            $message['value'] = $user->_libError;
            $message['color'] = $this->textColors['no'];
            $this->allowInstall = false;
        }
        $this->summary[] = $message;
    }

    /**
     * Install database.
     * @return void
     */
    private function installDatabase() {
        global $camyks;

        /* Get database connection */
        $camyks->db_conn = new Database_connection(
            isset($camyks->site_conf['database_host']) ? $camyks->site_conf['database_host']:$camyks->_conf['database_host'],
            isset($camyks->site_conf['database_login']) ? $camyks->site_conf['database_login']:$camyks->_conf['database_login'],
            isset($camyks->site_conf['database_pwd']) ? $camyks->site_conf['database_pwd']:$camyks->_conf['database_pwd'],
            isset($camyks->site_conf['database_driver']) ? $camyks->site_conf['database_driver']:$camyks->_conf['database_driver']
        );

        /* Check if connection is active */
        if ($camyks->db_conn->is_active()) {
            if (!$camyks->db_conn->database_exists($camyks->site_conf['database_name'])) {
                $message = array(
                    'type'  => 'message',
                    'name'  => $this->get_translation('database_created'),
                );

                /* Try to create database */
                if (!$camyks->db_conn->database_create($camyks->site_conf['database_name'], $camyks->get_mysqlencodingvalue())) {
                    $message['value'] = $camyks->get_translation('no');
                    $message['color'] = $this->textColors['no'];
                    $this->isInstalled = false;
                    $this->summary[] = $message;
                    return;
                }
                $message['value'] = $camyks->get_translation('yes');
                $message['color'] = $this->textColors['yes'];

                $this->summary[] = $message;
            }

            /* Open database */
            $camyks->db_conn->select($camyks->site_conf['database_name']);
        } else {
            /* Database connection failed */
            $this->summary[] = array(
                'type'  => 'message',
                'name'  => $this->get_translation('database_connection'),
                'value' => $this->get_translation('database_connection_failed'),
                'color' => $this->textColors['no'],
            );
            $this->isInstalled = false;
        }
    }

    /**
     * Install symbolic links.
     * @return void
     */
    private function installsymLinks() {
        global $camyks;

        /* Do not install sym links in "dedicated" installation mode */
        if ($camyks->_installationMode == 'dedicated')
            return;

        /* Build symLinks */
        foreach ($this->symLinks as $f => $l) {
            $message = array(
                'type'  => 'message',
                'name'  => $this->get_translation('symlink_x_created', $l),
            );

            /* Check if link already exists */
            if (file_exists(realpath('./'.$l)))
                continue;

            /* Create link */
            shell_ln($camyks->site_conf['engine_path'].'/'.$f, realpath('.').'/'.$l);

            /* Check it has correctly be created */
            if (file_exists(realpath('./'.$l))) {
                $message['value'] = $camyks->get_translation('yes');
                $message['color'] = $this->textColors['yes'];
                $this->summary[] = $message;
            } else {
                $message['value'] = $camyks->get_translation('no');
                $message['color'] = $this->textColors['no'];
                $this->summary[] = $message;
                $this->isInstalled = false;
                return;
            }
        }
    }

    /**
     * Install plugins.
     * @return void
     */
    private function installPlugins() {
        global $camyks;

        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('module_x_installed', 'Admin_PluginManager'),
        );

        /* First, try to install plugin manager plugin */
        if ($camyks->modules['Admin_PluginManager']->install()) {
            $message['value'] = $camyks->get_translation('yes');
            $message['color'] = $this->textColors['yes'];
            $this->summary[] = $message;

            /* Remove plugin manager from needed modules list */
            unset($camyks->neededModules['Admin_PluginManager']);

            /* Install needed modules */
            foreach ($camyks->neededModules as $p) {
                $message = array(
                    'type'  => 'message',
                    'name'  => $this->get_translation('module_x_installed', $p['name']),
                );
                if ($camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'module', false, 1)) {
                    $message['value'] = $camyks->get_translation('yes');
                    $message['color'] = $this->textColors['yes'];
                    $this->summary[] = $message;
                } else {
                    $message['value'] = $camyks->get_translation('no');
                    $message['color'] = $this->textColors['no'];
                    $this->summary[] = $message;
                    $this->isInstalled = false;
                    return;
                }
            }

            /* Install needed inputs */
            foreach ($camyks->neededInputs as $p) {
                $message = array(
                    'type'  => 'message',
                    'name'  => $this->get_translation('input_x_installed', $p['name']),
                );

                if ($camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'input', false, 1)) {
                    $message['value'] = $camyks->get_translation('yes');
                    $message['color'] = $this->textColors['yes'];
                    $this->summary[] = $message;
                } else {
                    $message['value'] = $camyks->get_translation('no');
                    $message['color'] = $this->textColors['no'];
                    $this->summary[] = $message;
                    $this->isInstalled = false;
                    return;
                }
            }

            /* Install needed themes */
            foreach ($camyks->neededThemes as $p) {
                $message = array(
                    'type'  => 'message',
                    'name'  => $this->get_translation('theme_x_installed', $p['name']),
                );

                if ($camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'theme', false, 1)) {
                    $message['value'] = $camyks->get_translation('yes');
                    $message['color'] = $this->textColors['yes'];
                    $this->summary[] = $message;
                } else {
                    $message['value'] = $camyks->get_translation('no');
                    $message['color'] = $this->textColors['no'];
                    $this->summary[] = $message;
                    $this->isInstalled = false;
                    return;
                }
            }

            /* Install needed templates */
            foreach ($camyks->neededTemplates as $p) {
                $message = array(
                    'type'  => 'message',
                    'name'  => $this->get_translation('template_x_installed', $p['name']),
                );

                if ($camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'template', false, 1)) {
                    $message['value'] = $camyks->get_translation('yes');
                    $message['color'] = $this->textColors['yes'];
                    $this->summary[] = $message;
                } else {
                    $message['value'] = $camyks->get_translation('no');
                    $message['color'] = $this->textColors['no'];
                    $this->summary[] = $message;
                    $this->isInstalled = false;
                    return;
                }
            }
        } else {
            $message['value'] = $camyks->get_translation('no');
            $message['color'] = $this->textColors['no'];
            $this->summary[] = $message;
            $this->isInstalled = false;
        }
    }

    /**
     * Finalise installation.
     * @return boolean success
     */
    private function installDone() {
        global $camyks;

        /* Update camyks version in conf file */
        $camyks->site_conf['cms_version'] = $camyks->version;

        /* Add 'installed' value to the conf file */
        $camyks->site_conf['installed'] = 1;

        $content = file_getPHPFileHeader('site configuration file', '1.0');
        $content .= '$conf = ' . var_export($camyks->site_conf, true) . ';';
        $content .= file_getPHPFileFooter();

        /* Write configuration file */
        if (!file_write(realpath('./etc/site.php.inc'), $content)) {
            $message = array(
                'type'  => 'message',
                'name'  => $this->get_translation('installation_done'),
                'value' => $camyks->get_translation('no'),
                'color' => $this->textColors['no'],
            );
            $this->summary[] = $message;
            $message = array(
                'type'  => 'detail',
                'name'  => $this->get_translation('installation_error_cantwriteconfigfile'),
                'value' => '',
                'color' => $this->textColors['no'],
            );
            $this->summary[] = $message;
            return false;
        }

        /* Add installation successfull message line */
        $message = array(
            'type'  => 'message',
            'name'  => $this->get_translation('installation_done'),
            'value' => $camyks->get_translation('yes'),
            'color' => $this->textColors['yes'],
        );
        $this->summary[] = $message;

        /* Remove config from session */
        $this->params->delete_fromSession('InstallerConfig');

        /* Add site admin link button */
        $this->buttons = array(array(
            'title' => $this->get_translation('open_admin'),
            'link'  => $camyks->get_adminLink(),
        ));

        /* Return success */
        return true;
    }
}
?>
