<?php
/**
 * @brief Admin_SystemNotifications Module
 * <br /> Gather and display notifications from websites you manage.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Jun 2018
 * @date Modification: Jan 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemNotifications Module class.
 */
final class Admin_SystemNotifications extends Module {
    /**
     * var object $websiteItem
     * @brief Website object.
     */
    protected $websiteItem;

    /**
     * var array $websiteList
     * @brief Website list.
     */
    protected $websiteList = null;

    /**
     * var boolean $isConfig
     * @brief Is module is configuration mode.
     */
    protected $isConfig = false;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_SystemNotifications', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'System';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'monitoring';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_SystemNotificationsWebsite');
        $this->load_library('Admin_SystemNotificationsConfig');

        /* Initialise plugin libraries */
        $this->websiteItem = new Admin_SystemNotificationsWebsite(0, $this);
        $this->config = new Admin_SystemNotificationsConfig('config', $this);

        /* register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->websiteItem->install() and parent::install());
    }

    /**
     * Unintall module.
     * @return boolean success
     */
    public function uninstall() {
        return parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->websiteItem->is_installed();
    }

    /**
     * Build module rights.
     * @return void
     */
    public function get_rights() {
        global $camyks;

        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
        );
        $this->rights[1] = array(
            'name'      => 'write',
            'title'     => $camyks->get_translation('write'),
            'default'   => false,
        );
    }

    /**
     * Update description in control panel
     * @return void
     */
    public function get_adminControlPanelAction() {
        global $camyks;

        /* Load configuration */
        $this->config->get();

        /* Update control panel status */
        if (date_isToday($this->config->vars['running_lastCheck']))
            $camyks->trads['mod_admin_systemnotifications_desc'] = $this->get_translation('descdate', strtolower($camyks->get_translation('today')));
        elseif (date_isYesterday($this->config->vars['running_lastCheck']))
            $camyks->trads['mod_admin_systemnotifications_desc'] = $this->get_translation('descdate', strtolower($camyks->get_translation('yesterday')));
        elseif ($this->config->vars['running_lastCheck'] > 0)
            $camyks->trads['mod_admin_systemnotifications_desc'] = $this->get_translation('descdatethe', date_displayLongDate($this->config->vars['running_lastCheck']));
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* check read permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

        /* load config */
        $this->config->get();

        /* load mode */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        switch ($this->mode) {
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_edit_config();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_save_config();
                break;
            case 'edit_website':
                /* mode == edit_website */
                $this->init_admin_edit_website();
                break;
            case 'save_website':
                /* mode == save_website */
                $this->init_admin_save_website();
                break;
            case 'delete_website':
                /* mode == delete_website */
                $this->init_admin_delete_website();
                break;
            case 'check_website':
                /* mode == check_website */
                $this->init_admin_check_website();
                break;
            case 'check_websites':
                /* mode == check_websites */
                $this->init_admin_check_websites();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        parent::init_admin();
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* build error message */
        $error = array(
            'title'         => $this->get_translation('requesterror_requestfailed'),
            'description'   => $this->get_translation('requesterror_undefinedaction'),
        );

        /* load mode to execute */
        $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

        /* execute mode */
        switch ($mode) {
            case 'loadNotifications':
                return $this->execute_request_loadNotifications();
            default :
                /* throw fatal error */
                $camyks->throwFatalError($error);
        }
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* get help */
        $this->get_help();

        /* get language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* load current website modules data */
        $modules = array();
        foreach ($camyks->modules as $module)
            $modules = array_merge($modules, $module->get_adminInternalNotifications());

        /* get tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];
        $this->tabBuilder->add_tab(array(
            'name'  => 'FollowUp',
            'title' => $this->get_translation('tabfollowup'),
        ));

        /* check for write rights */
        if ($this->check_right(1) == true) {

            /* check for master mode */
            if ($this->config->vars['module_mode'] == 1) {

                /* add website tab */
                $this->tabBuilder->add_tab(array(
                    'name'  => 'Websites',
                    'title' => $this->get_translation('websites'),
                ));

                /* build websites tab */
                $this->load_file('lib/Admin_SystemNotificationsWebsiteListParams.php.inc');
                $this->websiteList = &$camyks->inputs['AdminItemListViewer'];
                $this->websiteList->set_params($this->websiteListParams);
                $this->websiteList->initialise();
            }

            /* add configuration tab */
            $this->tabBuilder->add_tab(array(
                'name'  => 'Configuration',
                'title' => $this->get_translation('tabconfiguration'),
            ));

            /* add configuration data */
            $this->moduleModeList = $this->get_configurationModuleModeList();
            $this->accessStatusList = $this->get_configurationAccessStatusList();
            $this->accessAuthenticationList = $this->get_configurationAccessAuthenticationList();
            $this->adminList = $this->get_adminUserList(array('addAll'=>true));
        }

        /* load all sites data if master mode */
        if ($this->config->vars['module_mode'] == 1) {

            if ($this->config->vars['running_lastCheck'] + $this->config->vars['module_checkDelay']*60 < time()) {

                /* initialise follow up list with current website */
                $this->followUpList = array(
                    array(
                        'name'      => $camyks->get_confValue('site_title'),
                        'title'     => $camyks->get_confValue('site_title'),
                        'url'       => $camyks->get_confValue('url'),
                        'modules'   => $modules,
                        'error'     => '',
                        'self'      => true,
                    ),
                );

                /* load full website list */
                $wsList = $this->get_websiteList(array('status'=>1));

                foreach ($wsList as $website) {

                    /* execute check */
                    $result = $website->check_notifications();

                    /* check request result */
                    if ($result === false) {
                        $this->followUpList[$website->id] = array('name' => $website->vars['name'], 'error' => $this->get_translation('requesterror_connectionfailed'));
                    } else {
                        $result = json_decode($result, true);
                        if (isset($result['data']))
                            $this->followUpList[$website->id] = array_merge(array('name' => $website->vars['name']), $result['data']);
                        else
                            $this->followUpList[$website->id] = array('name' => $website->vars['name'], 'error' => $this->get_translation('requesterror_nodatasent'));
                    }

                    /* update last check value */
                    $this->config->vars['running_lastCheck'] = time();
                    $this->config->vars['running_cache'] = $this->followUpList;
                    $this->config->save();
                }
            } else {
                /* load from cache */
                $this->followUpList = $this->config->vars['running_cache'];
            }
        }

        /* finalise tabs */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));
        /* initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'FollowUp'));

        /* get buttons */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
    }

    /**
     * Initialise module object in admin/edit_config mode.
     * @return void
     */
    private function init_admin_edit_config() {
        global $camyks;

        /* check admin write rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* get help */
        $this->get_help();

        /* load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'Configuration',
            'title' => $this->get_translation('tabconfiguration'))
        );

        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));
        $this->tabBuilder->initialise(array('default'=>'Configuration'));

        /* load data */
        $this->moduleModeList = $this->get_configurationModuleModeList();
        $this->accessStatusList = $this->get_configurationAccessStatusList();
        $this->accessAuthenticationList = $this->get_configurationAccessAuthenticationList();
        $this->adminList = $this->get_adminUserList(array('addAll'=>true));

        /* build form */
        $this->editForm = new HTMLForm('edit_config', $this->get_adminlink(array('mode'=>'save_config')), 'POST');
        $this->editForm->set_object($this->config);
        $this->editForm->add_hidden('running_lastCheck', $this->config->vars['running_lastCheck']);

        /* add scripts */
        $this->add_JSFile('ConfigEditor.js');
        $this->add_JSScript('var ce = new ConfigEditor("ce");');
        $this->add_JSScript('ce.set_param("form", "'.$this->editForm->name.'");');
        $this->add_JSLoadScript('ce.initialise();');

        /* build buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'Configuration')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editForm->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
       );

        /* update layout */
        $this->set_selectedLayout('admin_edit_config.html.inc');
    }

    /**
     * Initialise module object in admin/save_config mode.
     * @return void
     */
    private function init_admin_save_config() {
        global $camyks;

        /* check admin write permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* save config object */
        $this->config->get_fromHeader();
        if ($this->config->save()) {
            $this->text = $this->get_translation('config_saved');
        } else {
            $this->text = $this->get_translation('config_notsaved');
        }

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Configuration')));
    }

    /**
     * Initialise module object in admin/edit_website mode.
     * @return void
     */
    private function init_admin_edit_website() {
        global $camyks;

        /* check admin write permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* get help */
        $this->get_help();

        /* load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'Properties',
            'title' => $this->get_translation('tabproperties'),
        ));

        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* load website object */
        $this->websiteItem->id = isset($_REQUEST['website_id']) ? (int)$_REQUEST['website_id'] : 0;
        $this->websiteItem->get();
        $this->websiteItem->get_fromItems();

        /* build form */
        $this->editForm = new HTMLForm('edit_website', $this->get_adminlink(array('mode'=>'save_website')), 'POST');
        $this->editForm->set_object($this->websiteItem);
        $this->editForm->add_hidden('website_id', $this->websiteItem->id);

        /* get buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'Websites')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editForm->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* update layout */
        $this->set_selectedLayout('admin_edit_website.html.inc');
    }

    /**
     * Initialise module object in admin/save_website mode.
     * @return void
     */
    private function init_admin_save_website() {
        global $camyks;

        /* check admin write permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* save object */
        $this->websiteItem->id = isset($_REQUEST['website_id']) ? (int)$_REQUEST['website_id'] : 0;
        $this->websiteItem->get_fromHeader();
        if ($this->websiteItem->save())
            $this->text = $this->get_translation('website_saved');
        else
            $this->text = $this->get_translation('website_notsaved');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Websites')));
    }

    /**
     * Initialise module object in admin/delete_website mode.
     * @return void
     */
    private function init_admin_delete_website() {
        global $camyks;

        /* check admin write permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* delete object */
        $this->websiteItem->id = isset($_REQUEST['website_id']) ? (int)$_REQUEST['website_id'] : 0;
        $this->websiteItem->get();
        $this->websiteItem->get_fromItems();
        if ($this->websiteItem->delete())
            $this->text = $this->get_translation('website_deleted');
        else
            $this->text = $this->get_translation('website_notdeleted');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Websites')));
    }

    /**
     * Initialise module object in admin/check_website mode.
     * @return void
     */
    private function init_admin_check_website() {
        global $camyks;

        /* check object */
        $this->websiteItem->id = isset($_REQUEST['website_id']) ? (int)$_REQUEST['website_id'] : 0;
        $this->websiteItem->get();
        $this->websiteItem->get_fromItems();

        $result = $this->websiteItem->check_notifications();

        /* check request result */
        if ($result === false) {
            $this->config->vars['running_cache'][$this->websiteItem->id] = array('name' => $this->websiteItem->vars['name'], 'error' => $this->get_translation('requesterror_connectionfailed'));
        } else {
            $result = json_decode($result, true);
            if (isset($result['data']))
                $this->config->vars['running_cache'][$this->websiteItem->id] = array_merge(array('name' => $this->websiteItem->vars['name']), $result['data']);
            else
                $this->config->vars['running_cache'][$this->websiteItem->id] = array('name' => $this->websiteItem->vars['name'], 'error' => $this->get_translation('requesterror_nodatasent'));
        }

        /* update configuration */
        $this->config->save();

        /* Define layout text */
        $this->text = $this->get_translation('website_checked');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/check_websites mode.
     * @return void
     */
    private function init_admin_check_websites() {
        global $camyks;

        /* load all sites data if master mode */
        if ($this->config->vars['module_mode'] == 1) {

            /* load current website modules data */
            $modules = array();
            foreach ($camyks->modules as $module)
                $modules = array_merge($modules, $module->get_adminInternalNotifications());

            /* initialise follow up list with current website */
            $this->followUpList = array(
                array(
                    'name'      => $camyks->get_confValue('site_title'),
                    'title'     => $camyks->get_confValue('site_title'),
                    'url'       => $camyks->get_confValue('url'),
                    'modules'   => $modules,
                    'error'     => '',
                    'self'      => true,
                ),
            );

            /* load full website list */
            $wsList = $this->get_websiteList(array('status'=>1));

            foreach ($wsList as $website) {

                /* execute check */
                $result = $website->check_notifications();

                /* check request result */
                if ($result === false) {
                    $this->followUpList[$website->id] = array('name' => $website->vars['name'], 'error' => $this->get_translation('requesterror_connectionfailed'));
                } else {
                    $result = json_decode($result, true);
                    if (isset($result['data']))
                        $this->followUpList[$website->id] = array_merge(array('name' => $website->vars['name']), $result['data']);
                    else
                        $this->followUpList[$website->id] = array('name' => $website->vars['name'], 'error' => $this->get_translation('requesterror_nodatasent'));
                }

                /* update last check value */
                $this->config->vars['running_lastCheck'] = time();
                $this->config->vars['running_cache'] = $this->followUpList;
                $this->config->save();
            }
        }

        /* Define layout text */
        $this->text = $this->get_translation('websites_checked');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /* Request mode methods */

    /**
     * Execute module object in request/load notifications mode
     * @return void
     */
    private function execute_request_loadNotifications() {
        global $camyks;

        /* initialise CaMykS in site mode */
        $camyks->get_siteInit();

        /* load configuration */
        $this->config->get();

        /* initialise answer */
        $answer = new CRequestAnswer();

        /* initialise follow up list with current website */
        $data = array(
            'title'     => $camyks->get_confValue('site_title'),
            'url'       => $camyks->get_confValue('url'),
            'modules'   => array(),
            'error'     => '',
            'self'      => false,
        );

        /* check service is enabled */
        if ($this->config->vars['access_status'] == 0) {
            $answer->set_asFailure();
            $data['error'] = $this->get_translation('requesterror_accessdisabled');
            $answer->update_param('data', $data);
            return $answer->send_asJSON();
        }

        /* check authentication with credentials */
        if ($this->config->vars['access_authentication'] == 1) {
            $login = isset($_REQUEST['login'])?$_REQUEST['login']:'';
            $password = isset($_REQUEST['password'])?$_REQUEST['password']:'';

            if ($this->config->vars['access_authLogin'] != '' and $login != $this->config->vars['access_authLogin']) {
                $answer->set_asFailure();
                $data['error'] = $this->get_translation('requesterror_authenticationfailed');
                $answer->update_param('data', $data);
                return $answer->send_asJSON();
            }

            $user = new AdminUser($login);
            if (!$user->can_login($password)) {
                $answer->set_asFailure();
                $data['error'] = $this->get_translation('requesterror_authenticationfailed');
                $answer->update_param('data', $data);
                return $answer->send_asJSON();
            }
        }

        /* check authentication with IP address */
        if ($this->config->vars['access_authentication'] == 2) {
            if ($this->config->vars['access_authIP'] == '' and !client_isServerClient()) {
                $answer->set_asFailure();
                $data['error'] = $this->get_translation('requesterror_authenticationfailed');
                $answer->update_param('data', $data);
                return $answer->send_asJSON();
            }

            if ($this->config->vars['access_authIP'] != '' and $this->config->vars['access_authIP'] != client_getIP()) {
                $answer->set_asFailure();
                $data['error'] = $this->get_translation('requesterror_authenticationfailed');
                $answer->update_param('data', $data);
                return $answer->send_asJSON();
            }
        }

        /* load current website modules data */
        $modules = array();
        foreach ($camyks->modules as $module)
            $modules = array_merge($modules, $module->get_adminInternalNotifications());
        $data['modules'] = $modules;

        /* send request result as success */
        $answer->set_asSuccess();
        $answer->update_param('data', $data);
        return $answer->send_asJSON();
    }

    /* Configuration related methods */

    /**
     * Return configuration module mode list
     * @return array
     */
    private function get_configurationModuleModeList() {
        return $this->config->get_moduleModeList();
    }

    /**
     * Return configuration access status list.
     * @return array
     */
    private function get_configurationAccessStatusList() {
        return $this->config->get_accessStatusList();
    }

    /**
     * Return configuration access authentication list.
     * @return array
     */
    private function get_configurationAccessAuthenticationList() {
        return $this->config->get_accessAuthenticationList();
    }

    /* Website related methods */

    /**
     * Return single website list.
     * @return array
     */
    public function get_websiteStatusList() {
        return $this->websiteItem->get_statusList();
    }

    /**
     * Return websites status list.
     * @param boolean $more
     * @return array
     */
    public function get_websitesStatusList($more=false) {
        return $this->websiteItem->get_multiStatusList($more);
    }

    /**
     * Return website count.
     * @param array $params
     * @return integer
     */
    public function count_websites($params=array()) {
        return $this->websiteItem->count($params);
    }

    /**
     * Return website list.
     * @param array $params
     * @return array
     */
    public function get_websiteList($params=array()) {
        return $this->websiteItem->get_list($params);
    }

    /* Specific tool methods */

    /**
     * Return given config item value.
     * @param string $item
     * @return mixed
     */
    public function get_configValue($item) {
        if (!isset($this->config->vars))
            $this->config->get();
        if (isset($this->config->vars[$item]))
            return $this->config->vars[$item];
        return false;
    }

    /**
     * Return admin user list.
     * @param params $params
     * @return array
     */
    private function get_adminUserList($params=array()) {
        global $camyks;

        $defaultParams = array('addAll'=>false);
        $params = array_merge($defaultParams, $params);

        $admins = $camyks->modules['Admin_User']->get_activeUserList(true);
        $menu = array();
        if ($params['addAll'])
            $menu[''] = $this->get_translation('credentials_all');
        foreach($admins as $admin)
            $menu[$admin->login] = $admin->get_nameDisplay();
        return $menu;
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode
     * @return void
     */
    public function initialise_configDisplay() {
        $this->isConfig = true;

        /* load configuration */
        $this->config->get();

        /* load data */
        $this->moduleModeList = $this->get_configurationModuleModeList();
        $this->accessStatusList = $this->get_configurationAccessStatusList();
        $this->accessAuthenticationList = $this->get_configurationAccessAuthenticationList();
        $this->adminList = $this->get_adminUserList(array('addAll'=>true));
    }

    /**
     * Display object in Admin_Site / view configuration mode
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/configuration/view.html.inc');
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        global $camyks;

        $this->isConfig = true;

        /* load configuration */
        $this->config->get();

        /* load data */
        $this->moduleModeList = $this->get_configurationModuleModeList();
        $this->accessStatusList = $this->get_configurationAccessStatusList();
        $this->accessAuthenticationList = $this->get_configurationAccessAuthenticationList();
        $this->adminList = $this->get_adminUserList(array('addAll'=>true));

        /* update form */
        $this->editForm = &$form;
        $this->editForm->set_object($this->config);
        $this->editForm->add_hidden('running_lastCheck', $this->config->vars['running_lastCheck']);

        /* add scripts */
        $this->add_JSFile('ConfigEditor.js');
        $this->add_JSScript('var ce = new ConfigEditor("ce");');
        $this->add_JSScript('ce.set_param("form", "'.$this->editForm->name.'");');
        $this->add_JSLoadScript('ce.initialise();');
    }

    /**
     * Display object in Admin_Site / edit configuration mode
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }

    /*
     * Execute object in Admin_Site / save configuration mode
     * @return void
     */
    public function save_configuration() {
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
