<?php
/**
 * @brief Admin_GenericEmailingManager Module
 * <br /> Manage contact lists, and send emailings.
 * @details Plugin, Module Engine
 * @file plugin/module/Admin_GenericEmailingManager/Admin_GenericEmailingManager.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericEmailingManager class.
 */
final class Admin_GenericEmailingManager extends Module {
    /**
     * var Object $contactItem
     * @brief Contact object.
     */
    protected $contactItem;

    /**
     * var array $contactList
     * @brief Contact list.
     */
    protected $contactList = null;

    /**
     * var Object $emailingItem
     * @brief Emailing object.
     */
    public $emailingItem;

    /**
     * var array $emailingList
     * @brief Emailing list.
     */
    protected $emailingList = null;

    /**
     * var Object $emailItem
     * @brief Email object.
     */
    protected $emailItem;

    /**
     * var array $emailList
     * @brief Email list.
     */
    protected $emailList = null;

    /**
     * var Object $config
     * @brief Configuration object.
     */
    protected $config;

    /**
     * var integer $maxFileSize
     * @brief Maximum upload file size in Mb/Mo.
     */
    protected $maxFileSize = 8;

    /**
     * var array $extensions
     * @brief List of plugin extensions.
     */
    protected $extensions = null;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericEmailingManager', $path_type);

        /* Overrides Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Overrides Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_GenericEmailingManagerConfig');
        $this->load_library('Admin_GenericEmailingManagerContact');
        $this->load_library('Admin_GenericEmailingManagerContactsImportConfig');
        $this->load_library('Admin_GenericEmailingManagerEmailing');
        $this->load_library('Admin_GenericEmailingManagerEmailingConfig');
        $this->load_library('Admin_GenericEmailingManagerEmail');

        /* initialise plugin libraries */
        $this->config = new Admin_GenericEmailingManagerConfig('config', $this);
        $this->contactItem = new Admin_GenericEmailingManagerContact(0, $this);
        $this->emailingItem = new Admin_GenericEmailingManagerEmailing(0, $this);
        $this->emailItem = new Admin_GenericEmailingManagerEmail(0, $this);
    }

    /* Overrides Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->contactItem->install() and $this->emailingItem->install()
            and $this->emailItem->install() and parent::install());
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
        return $this->emailingItem->is_installed();
    }

    /**
     * Register a menu in admin interface.
     * @return array
     */
    public function get_adminEngineSpecificMenus() {
        /* Check menus to be displayed */
        if (!($this->mode == 'main' and $this->check_right(1))
                and !($this->mode == 'view_emailing' and $this->check_right(2)
                and $this->emailingItem->id > 0 and $this->emailingItem->vars['status'] == 2))
            return array();

        /* Initialise menu list */
        $menus = array(array(
            'name'  => 'emailingmanager',
            'title' => $this->get_translation('menutitle'),
        ));

        /* Load extensions */
        $this->load_registeredExtensions();

        /* Load extensions menus */
        foreach ($this->extensions as &$plugin) {
             $ms = $plugin->load_managerMenu();
             foreach ($ms as $m)
                 if (!isset($menus[$m]))
                     $menus[] = array('name'=>$m, 'title'=>$this->get_translation('ext_'.$m));
        }

        /* Return built menus */
        return $menus;
    }

    /**
     * Register menu items in admin interface.
     * @return array
     */
    public function get_adminEngineSpecificMenuItems() {
        global $camyks;

        /* Initialise menus items list */
        $items = array();

        /* Build menus */
        if ($this->mode == 'view_emailing' and $this->check_right(2) and $this->emailingItem->id > 0 and $this->emailingItem->vars['status'] == 2) {
            $items[] = array(
                'name'  => 'resultsexport',
                'title' => $this->get_translation('resultsexport'),
                'icon'  => $this->get_fileURL('img/xls.gif'),
                'menu'  => 'emailingmanager',
                'url'   => 'javascript:window.open(\'request.php?module='.$this->name.'&mode=export_emailingResults&emailing='.$_REQUEST['emailing_id'].'\');void(0);'
            );
        } elseif ($this->mode == 'main' and $this->check_right(1)) {
            $items[] = array(
                'name'  => 'contactsimport',
                'title' => $this->get_translation('contactsimport'),
                'icon'  => $this->get_fileURL('img/xls.gif'),
                'menu'  => 'emailingmanager',
                'url'   => $this->get_adminLink(array('mode'=>'import_contactsPrepare'))
            );
            $items[] = array(
                'name'  => 'contactsexport',
                'title' => $this->get_translation('contactsexport'),
                'icon'  => $this->get_fileURL('img/xls.gif'),
                'menu'  => 'emailingmanager',
                'url'   => 'javascript:window.open(\'request.php?module='.$this->name.'&mode=export_contactList\');void(0);'
            );
        }

        /* Load extensions */
        $this->load_registeredExtensions();

        /* Adds extensions menus */
        foreach ($this->extensions as &$plugin)
             $items = array_merge($items, $plugin->load_managerMenuItems());

        /* Return built menus item list */
        return $items;
    }

    /**
     * Return module rights.
     * @return void
     */
    public function get_rights() {
        $this->rights[0] = array(
            'name'      => 'read_data',
            'title'     => $this->get_translation('read_data'),
            'default'   => false,
        );
        $this->rights[1] = array(
            'name'      => 'edit_data',
            'title'     => $this->get_translation('edit_data'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      => 'read_emailings',
            'title'     => $this->get_translation('read_emailings'),
            'default'   => false,
        );
        $this->rights[3] = array(
            'name'      => 'edit_emailings',
            'title'     => $this->get_translation('edit_emailings'),
            'default'   => false,
        );
        $this->rights[4] = array(
            'name'      => 'send_emailings',
            'title'     => $this->get_translation('send_emailings'),
            'default'   => false,
        );
        $this->rights[5] = array(
            'name'      => 'config',
            'title'     => $this->get_translation('config'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

        /* Load configuration */
        $this->config->get();

        /* Load mode to execute */
        $this->mode = (isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main');

        switch ($this->mode) {
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_edit_config();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_save_config();
                break;
            case 'view_emailing':
                /* mode == view_emailing */
                $this->init_admin_view_emailing();
                break;
            case 'edit_emailing':
                /* mode == edit_emailing */
                $this->init_admin_edit_emailing();
                break;
            case 'save_emailing':
                /* mode == save_emailing */
                $this->init_admin_save_emailing();
                break;
            case 'delete_emailing':
                /* mode == delete_emailing */
                $this->init_admin_delete_emailing();
                break;
            case 'send_emailing':
                /* mode == send_emailing */
                $this->init_admin_send_emailing();
                break;
            case 'reset_emailing':
                /* mode == reset_emailing */
                $this->init_admin_reset_emailing();
                break;
            case 'edit_contact':
                /* mode == edit_contact */
                $this->init_admin_edit_contact();
                break;
            case 'save_contact':
                /* mode == save_contact */
                $this->init_admin_save_contact();
                break;
            case 'delete_contact':
                /* mode == delete_contact */
                $this->init_admin_delete_contact();
                break;
            case 'delete_email':
                /* mode == delete_email */
                $this->init_admin_delete_email();
                break;
            case 'mark_email':
                /* mode == mark_email */
                $this->init_admin_mark_email();
                break;
            case 'import_contactsPrepare':
                /* mode == import_contactsPrepare */
                $this->init_admin_import_contactsPrepare();
                break;
            case 'import_contactsCheckAndConfigure':
                /* mode == import_contactsCheckAndConfigure */
                $this->init_admin_import_contactsCheckAndConfigure();
                break;
            case 'import_contactsExecute':
                /* mode = import_contactsExecute */
                $this->init_admin_import_contactsExecute();
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

        /* Define error */
        $error = array(
            'title'         => $this->get_translation('fatalerror_actionundefined'),
            'description'   => $this->get_translation('fatalerror_actionmustbeset1'),
            'content1'      => $this->get_translation('fatalerror_actionmustbeset2'),
        );

        /* Check action value */
        if (isset($_REQUEST['mode'])) {
            $action = $_REQUEST['mode'];
        } else {
            /* Throw fatal error */
            $camyks->throwFatalError($error);
        }

        /* Execute action */
        switch ($action) {
            case 'preview_emailing':
                /* mode == preview emailing */
                $this->execute_request_previewEmailing();
                break;
            case 'withdraw_contact':
                /* mode == withdraw_contact */
                $this->execute_request_withdrawContact();
                break;
            case 'export_emailingResults':
                /* mode == export_emailingResults */
                $this->execute_request_exportEmailingResults();
                break;
            case 'export_contactList':
                /* mode == export_contactList */
                $this->execute_request_exportContactList();
                break;
            case 'send_emailingInitialise':
                /* mode == send_emailingInitialise */
                $this->execute_request_sendEmailingInitialise();
                break;
            case 'send_emailingExecute':
                /* mode == send_emailingExecute */
                $this->execute_request_sendEmailingExecute();
                break;
            case 'send_emailingFinalise':
                /* mode == send_emailingFinalise */
                $this->execute_request_sendEmailingFinalise();
                break;
            case 'import_contactInitialise':
                /* mode == import_contactInitialise */
                $this->execute_request_importContactInitialise();
                break;
            case 'import_contactExecute':
                /* mode == import_contactExecute */
                $this->execute_request_importContactExecute();
                break;
            case 'import_contactFinalise':
                /* mode == import_contactFinalise */
                $this->execute_request_importContactFinalise();
                break;
            case 'email_action':
                /* mode == email_action */
                $params = explode('-', isset($_REQUEST['params'])?$_REQUEST['params']:'');
                $action = array_shift($params);
                switch ($action) {
                    case 'check':
                        $this->execute_request_setEmailAsOpened($params);
                        break;
                    case 'link':
                        $this->execute_request_openEmailLink($params);
                        break;
                    case 'display':
                        $this->execute_request_previewEmailing($params);
                        break;
                    case 'unsubscribe':
                        $this->execute_request_unsubscribeContact($params);
                        break;
                }
                break;
            default :
                /* Throw fatal error */
                $camyks->throwFatalError($error);
        }
    }

    /* specific admin mode methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Load tabs */
        $this->tabBuilder = &$camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'contacts',
            'title' => $this->get_translation('contacts'),
        ));
        if ($this->check_right(2)) {
            $this->tabBuilder->add_tab(array(
                'name'  => 'emailings',
                'title' => $this->get_translation('emailings'),
            ));
        }
        if ($this->check_right(5)) {
            $this->tabBuilder->add_tab(array(
                'name'  => 'config',
                'title' => $this->get_translation('configuration'),
            ));
        }
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'=>'help',
                'title'=>$camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'fact'));

        /* Build contact tab */
        $this->load_library('Admin_GenericEmailingManagerContactListParams');
        $this->contactList = new AdminItemListViewer('camyks');
        $this->contactList->set_params($this->contactListParams);
        $this->contactList->initialise();

        /* Build emailing tabs */
        if ($this->check_right(2)) {
                $this->load_library('Admin_GenericEmailingManagerEmailingListParams');
                $this->emailingList = new AdminItemListViewer('camyks');
                $this->emailingList->set_params($this->emailingListParams);
                $this->emailingList->initialise();
        }

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            )
        );
    }

    /**
     * Initialise module object in admin/edit_config mode.
     * @return void
     */
    private function init_admin_edit_config() {
        global $camyks;

        /* Check edit product rights */
        if ($this->check_right(5) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load tabs */
        $this->tabBuilder = &$camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'manager',
            'title' => $this->get_translation('properties'),
        ));
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'manager'));

        /* Load configuration form */
        $this->editform = new HTMLForm('edit_config', $this->get_adminlink(array('mode'=>'save_config')), 'POST');
        $this->editform->set_object($this->config);

        /* Load page chooser input */
        $this->add_JSFile('configuration.js');
        if (isset($camyks->inputs['PageChooser'])) {
            $this->pc = true;
            $camyks->inputs['PageChooser']->initialise("pagename", null, "update_selectedPage");
        } else {
            $this->pc = false;
        }

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('configuration');

        /* Build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back')
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_config.html.inc');
    }

    /**
     * Initialise module object in admin/save_config mode.
     * @return void
     */
    private function init_admin_save_config() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(5) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save object */
        $this->config->get_fromHeader();
        if ($this->config->save()) {
            $this->text = $this->get_translation('config_saved');
        } else {
            $this->text = $this->get_translation('config_notsaved');
        }

        /* Update layout and redirect user */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'config')));
    }

    /**
     * Initialise module object in admin/view_emailing mode.
     * @return void
     */
    private function init_admin_view_emailing() {
        global $camyks;

        /* Check edit emailing rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load help */
        $this->get_help();

        /* Load tabs */
        $this->tabBuilder = &$camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'properties',
                'title' => $this->get_translation('tabproperties'),
            ),
            array(
                'name'  => 'sending',
                'title' => $this->get_translation('tabsending'),
            ),
        ));
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Load emailing item */
        $this->emailingItem->id = isset($_REQUEST['emailing_id']) ? (int)$_REQUEST['emailing_id'] : 0;
        $this->emailingItem->get();
        $this->emailingItem->get_fromItems();

        /* Load data */
        $this->emailingStatusList = $this->get_emailingStatusList();
        $this->contactSourceList = $this->get_contactSourceList();

        if ($this->emailingItem->vars['status'] < 2) {
            $source = explode(':', $this->emailingItem->vars['contact_source']);
            if ($source[0] == 'internal') {
                $this->contactCount = $this->count_contacts(array(
                    'status'=>$source[1],
                    'group'=>$this->emailingItem->vars['contact_group'],
                ));
            } elseif (isset($camyks->modules[$source[0]])) {
                $this->contactCount = $camyks->modules[$source[0]]->count_emailingManagerContacts($source[1]);
            } else {
                $this->contactCount = 0;                }
        } elseif ($this->emailingItem->vars['status'] == 2) {
            $this->contactNameList = array();
            $this->emailingStatisticsSummary = $this->get_emailingStatisticsSummary($this->emailingItem->id);

            /* Build email tab */
            $this->load_library('Admin_GenericEmailingManagerEmailListParams');
            $this->emailList = &$camyks->inputs['AdminItemListViewer'];
            $this->emailList->set_params($this->emailListParams);
            $this->emailList->initialise();
            $this->tabBuilder->add_tab(array(
                'name'  => 'emails',
                'title' => $this->get_translation('tabdetails'),
            ));

            /* get contact list */
            $sources = array();
            foreach ($this->emailList->objectList as $email) {
                if (!isset($sources[$email->vars['source']]))
                    $sources[$email->vars['source']] = array();
                $sources[$email->vars['source']][$email->vars['contact']] = '';
            }

            foreach ($sources as $source => $contacts) {
                $src = explode(':', $source);
                if ($src[0] == 'internal') {
                    $l = $this->contactItem->get_fullNameList(array('ids'=>array_keys($contacts)));
                } elseif (isset($camyks->modules[$src[0]])) {
                    $l = $camyks->modules[$src[0]]->get_emailingManagerContactTitleFromIds(array_keys($contacts));
                } else {
                    $l = array();
                }
                foreach ($contacts as $id => $title) {
                    if (isset($l[$id]))
                        $sources[$source][$id] = $l[$id];
                }
            }

            foreach ($this->emailList->objectList as &$email) {
                if (isset($sources[$email->vars['source']][$email->vars['contact']]))
                    $email->vars['title'] = $sources[$email->vars['source']][$email->vars['contact']];
            }
        }

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'properties'));

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->emailingItem->id == 0)
            $this->adminTitle .= $this->get_translation('emailingnew');
        else
            $this->adminTitle .= $this->get_translation('emailingid', $this->emailingItem->id);

        /* Build buttons */
        $this->buttons = array(array(
            'link'  => $this->get_adminLink(array('openTab'=>'emailings')),
            'title' => $camyks->get_translation('back'),
        ));
        if ($this->check_right(3) !== false and $this->emailingItem->vars['status'] == 0) {
            $this->buttons[] = array(
                'link'  => $this->get_adminLink(array('mode' => 'edit_emailing', 'emailing_id' => $this->emailingItem->id)),
                'title' => $camyks->get_translation('edit'),
            );
        }

        /* Update layout */
        $this->set_selectedLayout('admin_view_emailing.html.inc');
    }

    /**
     * Initialise module object in admin/edit_emailing mode.
     * @return void
     */
    private function init_admin_edit_emailing() {
        global $camyks;

        /* Check edit emailing rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load help */
        $this->get_help();

        /* Load tabs */
        $this->tabBuilder = &$camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'properties',
                'title' => $this->get_translation('tabproperties'),
            ),
            array(
                'name'  => 'advanced',
                'title' => $this->get_translation('tabadvanced'),
            ),
        ));

        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'properties'));

        /* Load emailing item */
        $this->emailingItem->id = isset($_REQUEST['emailing_id']) ? (int)$_REQUEST['emailing_id'] : 0;
        $this->emailingItem->get();
        $this->emailingItem->get_fromItems();

        /* Load data */
        $this->emailingStatusList = $this->get_emailingStatusList();
        $this->contactSourceList = $this->get_contactSourceList();
        $this->contactGroupList = $this->get_contactGroupList(true);

        /* Build emailing edition form */
        $this->editform = new HTMLForm('edit_emailing', $this->get_adminlink(array('mode'=>'save_emailing')), 'POST');
        $this->editform->allow_files(true, 1024*1204);
        $this->editform->set_object($this->emailingItem);
        $this->editform->add_hidden('emailing_id', $this->emailingItem->id);
        $this->editform->add_hidden('status', $this->emailingItem->vars['status']);

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->emailingItem->id == 0)
            $this->adminTitle .= $this->get_translation('emailingnew');
        else
            $this->adminTitle .= $this->get_translation('emailingid', $this->emailingItem->id);

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'emailings')),
                'title' => $camyks->get_translation('back')
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_emailing.html.inc');
    }

    /**
     * Initialise module object in admin/save_emailing mode.
     * @return void
     */
    private function init_admin_save_emailing() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load emailing object */
        $this->emailingItem->id = isset($_REQUEST['emailing_id']) ? (int)$_REQUEST['emailing_id'] : 0;
        $this->emailingItem->get_fromHeader();

        /* Save emailing object */
        if ($this->emailingItem->save()) {
            $this->text = $this->get_translation('emailing_saved');
        } else {
            $this->text = $this->get_translation('emailing_notsaved');
        }

        /* Update layout and make redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'emailings')));
    }

    /**
     * Initialise module object in admin/delete_emailing mode.
     * @return void
     */
    private function init_admin_delete_emailing() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Check emailing id */
        if (!isset($_REQUEST['emailing_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object id */
        $this->emailingItem->id = (int)$_REQUEST['emailing_id'];

        /* Delete object */
        if ($this->emailingItem->delete()) {
            $this->text = $this->get_translation('emailing_deleted');
        } else {
            $this->text = $this->get_translation('emailing_notdeleted');
        }

        /* Update layout and make redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'emailings')));
    }

    /**
     * Initialise module object in admin/reset_emailing mode.
     * @return void
     */
    private function init_admin_reset_emailing() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(4) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Check emailing id */
        if (!isset($_REQUEST['emailing_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->emailingItem->id = (int)$_REQUEST['emailing_id'];
        $this->emailingItem->get();
        $this->emailingItem->_libItems['status']->value = 0;
        $this->emailingItem->get_fromItems();

        /* Update config object */
        $this->emailingItem->config->vars['emailing_current'] = 0;
        $this->emailingItem->config->vars['emailing_list'] = array();

        /* Update object */
        if ($this->emailingItem->save() and $this->emailingItem->config->save()) {
            $this->text = $this->get_translation('emailing_reseted');
        } else {
            $this->text = $this->get_translation('emailing_notreseted');
        }

        /* Update layout and make redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>$this->emailingItem->id)));
    }

    /**
     * Initialise module object in admin/send_emailing mode.
     * @return void
     */
    private function init_admin_send_emailing() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(4) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Check emailing id */
        if (!isset($_REQUEST['emailing_id']))
            return $this->init_admin_main();

        /* Load object */
        $this->emailingItem->id = (int)$_REQUEST['emailing_id'];
        $this->emailingItem->get();
        $this->emailingItem->get_fromItems();

        /* Add javascripts */
        $this->add_JSEngineFile('tool/xml.js');
        $this->add_JSEngineFile('object/cajaxrequest.js');
        $this->add_JSFile('emailingengine.js');
        $this->add_JSScript('var ee = new EmailingEngine("ee");');
        $this->add_JSScript('ee.set_param("requestBaseURL", "'.$camyks->get_confValue('url').'/request.php?module='.$this->name.'&emailing_id='.$this->emailingItem->id.'");');
        $this->add_JSLoadScript('ee.initialise();');

        if ($this->emailingItem->vars['status'] == 0) {
            $this->add_JSScript('ee.set_param("startAt", -1);');
            $this->add_JSScript('ee.set_param("emailCount", -1);');
        } else {
            $this->add_JSScript('ee.set_param("startAt", '.$this->emailingItem->config->vars['emailing_current'].');');
            $this->add_JSScript('ee.set_param("emailCount", '.count($this->emailingItem->config->vars['emailing_list']).');');
        }
        $this->add_JSScript('ee.set_param("sendingInterval", '.($this->emailingItem->vars['advanced_sending_interval']*1000).');');

        /* Add locales */
        $this->add_JSScript('ee.set_locale("continue_sending", "'.string_html2text($this->get_translation('continue_sending')).'");');
        $this->add_JSScript('ee.set_locale("initialise_emailing", "'.string_html2text($this->get_translation('initialise_emailing')).'");');
        $this->add_JSScript('ee.set_locale("send_email", "'.string_html2text($this->get_translation('send_email')).'");');
        $this->add_JSScript('ee.set_locale("finalise_emailing", "'.string_html2text($this->get_translation('finalise_emailing')).'");');

        /* Update layout title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('emailsending');

        /* Build buttons */
        $this->buttons = array(array(
            'link'  => $this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>$this->emailingItem->id)),
            'title' => $camyks->get_translation('back')
        ));

        /* Update layout */
        $this->set_selectedLayout('admin_send_emailing.html.inc');
    }

    /**
     * Initialise module object in admin/edit_contact mode
     * @return void
     */
    private function init_admin_edit_contact() {
        global $camyks;

        /* Check edit contact rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load help */
        $this->get_help();

        /* Load tabs */
        $this->tabBuilder = &$camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'properties',
            'title' => $this->get_translation('tabproperties'),
        ));

        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'properties'));

        /* Load contact item */
        $this->contactItem->id = isset($_REQUEST['contact_id']) ? (int)$_REQUEST['contact_id'] : 0;
        $this->contactItem->get();
        $this->contactItem->get_fromItems();

        /* Load data */
        $this->statusList = $this->get_contactStatusList();
        $this->contactGroupList = $this->get_contactGroupList(false, true);

        /* Build contact edition form */
        $this->editform = new HTMLForm('edit_contact', $this->get_adminlink(array('mode'=>'save_contact')), 'POST');
        $this->editform->set_object($this->contactItem);
        $this->editform->add_hidden('contact_id', $this->contactItem->id);
        $this->editform->add_hidden('old_email', $this->contactItem->vars['email']);

        /* Add javascript */
        $this->add_JSFile('contacteditor.js');
        $this->add_JSScript('var ce = new ContactEditor("ce");');
        $this->add_JSLoadScript('ce.initialise();');

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->contactItem->id == 0)
            $this->adminTitle .= $this->get_translation('contactnew');
        else
            $this->adminTitle .= $this->get_translation('contactid', $this->contactItem->id);

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_contact.html.inc');
    }

    /**
     * Initialise module object in admin/save_contact mode.
     * @return void
     */
    private function init_admin_save_contact() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->contactItem->id = isset($_REQUEST['contact_id']) ? (int)$_REQUEST['contact_id'] : 0;
        $this->contactItem->get_fromHeader();

        /* Save object */
        if ($this->contactItem->save()) {
            $this->text = $this->get_translation('contact_saved');
        } else {
            if (isset($this->contactItem->_libError))
                $this->text = $this->contactItem->_libError;
            else
                $this->text = $this->get_translation('contact_notsaved');
        }

        /* Update layout and make redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'contacts')));
    }

    /**
     * Initialise module object in admin/delete_contact mode.
     * @return void
     */
    private function init_admin_delete_contact() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Check contact id */
        if (!isset($_REQUEST['contact_id']))
                return $this->init_admin_main();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object id */
        $this->contactItem->id = (int)$_REQUEST['contact_id'];

        /* Delete object */
        if ($this->contactItem->delete()) {
            $this->text = $this->get_translation('contact_deleted');
        } else {
            $this->text = $this->get_translation('contact_notdeleted');
        }

        /* Update layout and make redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'contacts')));
    }

    /**
     * Initialise module object in admin/delete_email mode.
     * @return void
     */
    private function init_admin_delete_email() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Check emailing id */
        if (!isset($_REQUEST['email_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->emailItem->id = (int)$_REQUEST['email_id'];
        $this->emailItem->get();
        $this->emailItem->get_fromItems();
        $emailing = $this->emailItem->vars['emailing'];

        /* Delete object */
        if ($this->emailItem->delete()) {
            $this->text = $this->get_translation('email_deleted');
        } else {
            $this->text = $this->get_translation('email_notdeleted');
        }

        /* Update layout and make redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>$emailing, 'openTab'=>'emails')));
    }

    /**
     * Initialise module object in admin/mark_email mode.
     * @return void
     */
    private function init_admin_mark_email() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Check emailing id */
        if (!isset($_REQUEST['email_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->emailItem->id = (int)$_REQUEST['email_id'];
        $this->emailItem->get();
        $this->emailItem->get_fromItems();
        $emailing = $this->emailItem->vars['emailing'];

        /* Mark object as invalid */
        if ($this->emailItem->mark_asInvalid()) {
            /* update contact status */
            $this->mark_contactAsInvalid($this->emailItem->vars['contact'], $this->emailItem->vars['source']);

            $this->text = $this->get_translation('email_markedasinvalid');
        } else {
            $this->text = $this->get_translation('email_notmarkedasinvalid');
        }

        /* Update layout and make redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>$emailing, 'openTab'=>'emails')));
    }

    /**
     * Initialise module object in admin/import_contactsPrepare mode.
     * @return void
     */
    private function init_admin_import_contactsPrepare() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Build importation form */
        $this->importform = new HTMLForm('import_contact', $this->get_adminlink(array('mode'=>'import_contactsCheckAndConfigure')), 'POST');
        $this->importform->allow_files($this->maxFileSize * 1024 *1024);

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('contacstimport');

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->importform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('continue'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_import_contactsPrepare.html.inc');
    }

    /**
     * Initialise module object in admin/import_contactsCheckAndConfigure mode.
     * @return void
     */
    private function init_admin_import_contactsCheckAndConfigure() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        $this->uploadResult = false;

        /* Load file */
        if (isset($_FILES['file']) and $_FILES['file']['name'] != '') {
            folder_completePath($this->get_varFilePath().'Importations');

            /* get file extension */
            if (preg_match('/.*\.([^\.]*)/', $_FILES['file']['name'], $ext))
                $ext = '.'.$ext[1];
            else
                $ext = '';

            $file = strftime('%F-%H-%M-%S'.$ext);
            $path = $this->get_varFilePath().'Importations/'.$file;
            if (move_uploaded_file($_FILES['file']['tmp_name'], $path)) {
                /* Load library */
                require_once 'Spreadsheet/Excel/Reader.php';

                /* Load file */
                $this->xlsFile = new Spreadsheet_Excel_Reader($path);
            }
        }

        $this->importContactFieldList = array(
            'none'          => $this->get_translation('none'),
            'status'        => $this->get_translation('status'),
            'lastname'      => $camyks->get_translation('lastname'),
            'firstname'     => $camyks->get_translation('firstname'),
            'email'         => $camyks->get_translation('email'),
            'group'         => $this->get_translation('group'),
            'denomination'  => $this->get_translation('denomination'),
        );

        /* Build import contact form */
        $this->importform = new HTMLForm('import_contact', $this->get_adminlink(array('mode'=>'import_contactsExecute')), 'POST');
        $this->importform->add_hidden('import_file', $file);
        $this->importform->add_hidden('colcount', $this->xlsFile->colcount());
        $this->importform->add_hidden('rowcount', $this->xlsFile->rowcount());

        /* Build scripts */
        $this->add_JSFile('importcontactconfigure.js');
        $this->add_JSScript('var icc = new ImportContactConfiguration("icc");');
        $this->add_JSScript('icc.set_param("form", "'.$this->importform->name.'");');
        $this->add_JSLoadScript('icc.initialise();');

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('contacstimport');

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('mode'=>'import_contactsPrepare')),
                'title' => $camyks->get_translation('back')),
            array(
                'link'  => $this->importform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('continue'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_import_contactsCheckAndConfigure.html.inc');
    }

    /**
     * Initialise module object in admin/import_contactsExecute mode.
     * @return void
     */
    private function init_admin_import_contactsExecute() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load data from headers */
        $data = $_REQUEST;

        /* Build default values */
        $this->config = new Admin_GenericEmailingManagerContactsImportConfig('contactsImport', $this);
        $this->config->initialise();
        $this->config->vars['import_file'] = $data['import_file'];
        $this->config->vars['first_line'] = $data['loadfromline'];
        $this->config->vars['import_current'] = 0;
        $this->config->vars['row_count'] = $data['rowcount'];
        $this->config->vars['col_count'] = $data['colcount'];
        $this->config->vars['cols_params'] = array();
        for($i=1; $i<$data['colcount']+1; $i++) {
            $this->config->vars['cols_params']['col'.$i.'_field'] = $data['col'.$i.'_field'];
            if ($data['col'.$i.'_field'] == 'status') {
                $this->config->vars['cols_params']['col'.$i.'_status'] = array();
                foreach ($this->contactItem->get_statusList() as $id => $name)
                    if ($data['col'.$i.'_status'.$id] != '')
                        $this->config->vars['cols_params']['col'.$i.'_status'][$data['col'.$i.'_status'.$id]] = $id;
            }
        }
        $this->config->save();

        /* Add javascripts */
        $this->add_JSEngineFile('tool/xml.js');
        $this->add_JSEngineFile('object/cajaxrequest.js');
        $this->add_JSFile('importcontactengine.js');
        $this->add_JSScript('var ice = new ImportContactEngine("ice");');
        $this->add_JSScript('ice.set_param("requestBaseURL", "'.$camyks->get_confValue('url').'/request.php?module='.$this->name.'");');
        $this->add_JSLoadScript('ice.initialise();');

        $this->add_JSScript('ice.set_param("startAt", -1);');
        $this->add_JSScript('ice.set_param("contactCount", '.($data['rowcount']-$data['loadfromline']+1).');');

        /* Add locales */
        //$this->add_JSScript('ice.set_locale("continue_sending", "'.string_html2text($this->get_translation('continue_sending')).'");');
        $this->add_JSScript('ice.set_locale("initialise_importation", "'.string_html2text($this->get_translation('initialise_importation')).'");');
        $this->add_JSScript('ice.set_locale("import_contact", "'.string_html2text($this->get_translation('import_contact')).'");');
        $this->add_JSScript('ice.set_locale("finalise_importation", "'.string_html2text($this->get_translation('finalise_importation')).'");');

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('contacstimport');

        /* Build buttons */
        $this->buttons = array(array(
            'link'  => $this->get_adminLink(array('mode'=>'import_contactsPrepare')),
            'title' => $camyks->get_translation('back'))
        );

        /* Update layout */
        $this->set_selectedLayout('admin_import_contactsExecute.html.inc');
    }

    /* Specific request mode methods */

    /**
     * Execute module object in request / preview mode.
     * @param array $params
     * @return void
     */
    private function execute_request_previewEmailing($params=null) {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_adminInit();

        if ($params !== null)
            $eId = $params[0];
        elseif (isset($_REQUEST['emailing_id']))
            $eId = (int)$_REQUEST['emailing_id'];
        else
            return false;

        if ($params !== null and $params[1] == 'direct')
            $linkMode = 'direct';
        elseif (isset($_REQUEST['link_mode']))
            $linkMode = $_REQUEST['link_mode'];
        else
            $linkMode = 'redirect';

        /* Load emailing */
        $this->emailingItem->id = $eId;
        $this->emailingItem->get();
        $this->emailingItem->get_fromItems();

        /* Load random contact */
        $this->contactItem->id = 1;
        $this->contactItem->get();
        $this->contactItem->get_fromItems();

        /* Build email params */
        if ($params !== null)
            $params = array_merge($params, $this->contactItem->get_itemsAsMailParams());
        else
            $params = $this->contactItem->get_itemsAsMailParams();
        $params['image_path'] = $this->emailingItem->get_imageFolderURL().'/';

        if ($linkMode == 'redirect')
            $params['link_([0-9]*)'] = $camyks->get_confValue('url').'/emailing-link-'.$this->emailingItem->id.'-test-$1.gnl';
        else {
            $this->emailingItem->load_config();
            foreach ($this->emailingItem->config->vars['content_links'] as $id => $link)
                $params['link_'.$id] = $link;
        }

        $params['opened_img'] = $this->get_fileURL('img/blank.gif', true);

        /* Write emailing file */
        die($this->emailingItem->get_emailContent($params));
    }

    /**
     * Execute module object in request / unsubscribe mode.
     * @return void
     */
    private function execute_request_unsubscribeContact($params) {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_siteInit();

        /* Check email value */
        if (!isset($_REQUEST['email']))
            die('Error : no email given');

        /* Check contact id value */
        if (count($params) < 2)
            die('Error : no contact id given');

        /* Load email id */
        $this->emailItem->id = $params[1];

        /* Update email */
        if (!$this->emailItem->update_asUnsubscribed($params[0]))
            die('Error');

        /* Load contact id */
        $this->contactItem->id = $this->emailItem->vars['contact'];

        $this->config->get();

        /* update contact */
        if ($this->contactItem->update_asUnsubscribed($_REQUEST['email'])) {
            header('Location:'.$camyks->get_siteLink($this->config->vars['unsubscribe_backpage']));
        } else {
            die('Error');
        }
    }

    /**
     * Execute module object in request / export emailing results mode.
     * @return void
     */
    private function execute_request_exportEmailingResults() {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_adminInit();

        /* Check email value */
        if (!isset($_REQUEST['emailing']))
                die('Error : no emailing given');

        /* Load excel writer library */
        require_once('Spreadsheet/Excel/Writer.php');

        /* Load emailing */
        $this->emailingItem->id = (int)$_REQUEST['emailing'];
        $this->emailingItem->get();
        $this->emailingItem->get_fromItems();

        /* Load emailing emails */
        $emails = $this->emailItem->get_objectList(false, 'emailing='.$_REQUEST['emailing'], -1, -1, 'send_date', 'asc');

        /* Load contact list */
        $sources = array();
        foreach ($emails as $email) {
            if (!isset($sources[$email->vars['source']]))
                $sources[$email->vars['source']] = array();
            $sources[$email->vars['source']][$email->vars['contact']] = '';
        }

        foreach ($sources as $source => &$contacts) {
            $src = explode(':', $source);
            if ($src[0] == 'internal') {
                $l = $this->contactItem->get_fullNameList(array('ids'=>array_keys($contacts)));
            } elseif (isset($camyks->modules[$src[0]])) {
                $l = $camyks->modules[$src[0]]->get_emailingManagerContactTitleFromIds(array_keys($contacts), $src[1]);
            } else {
                $l = array();
            }
            foreach ($contacts as $id => &$title) {
                if (isset($l[$id]))
                    $sources[$source][$id] = $l[$id];
            }
        }

        foreach ($emails as $id => $email) {
            if (isset($sources[$email->vars['source']][$email->vars['contact']]))
                $emails[$id]->vars['title'] = $sources[$email->vars['source']][$email->vars['contact']];
        }


        /* Creating a workbook */
        $workbook = new Spreadsheet_Excel_Writer();

        /* Sending HTTP headers */
        $workbook->send('Export_'.strftime('%Y-%m-%d').'.xls');

        /* Creating a worksheet */
        $worksheet =& $workbook->addWorksheet('E-Mailing');

        /* Creates formats */
        $workbook->setCustomColor(16, 26, 97, 169);
        $header = &$workbook->addFormat();
        $header->setBold(700);
        $header->setColor(16);

        /* Add title line */
        $c = 0;
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('contact'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('sending'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('opening'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('firstclick'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('clicks'))), $header);

        $l = 1;
        foreach ($emails as $email) {
            $c = 0;
            /* Add details in cells */
            $worksheet->write($l, $c++, utf8_decode($email->vars['title']));
            $worksheet->write($l, $c++, $email->get_sentDateValue());
            $worksheet->write($l, $c++, $email->get_openedDateValue());
            $worksheet->write($l, $c++, $email->get_firstClickDateValue());
            $worksheet->write($l, $c++, $email->vars['click_count']);
            $l++;
        }

        /* Close and send XLS file */
        $workbook->close();
    }

    /**
     * Execute module object in request / export contact list mode.
     * @return void
     */
    private function execute_request_exportContactList() {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_adminInit();

        /* Check admin user */
        if ($camyks->check_adminUser() == false)
            return $camyks->init_kill();

        /* Load excel writer library */
        require_once('Spreadsheet/Excel/Writer.php');

        /* Load data */
        $contactCount = $this->contactItem->count();
        $status = $this->contactItem->get_statusList();
        $groups = $this->get_contactGroupList();

        /* Creating a workbook */
        $workbook = new Spreadsheet_Excel_Writer();

        /* Sending HTTP headers */
        $workbook->send('Export-'.strftime('%Y-%m-%d').'.xls');

        /* Creating a worksheet */
        $worksheet =& $workbook->addWorksheet('Contacts');

        /* Creates formats */
        $workbook->setCustomColor(16, 26, 97, 169);
        $header = &$workbook->addFormat();
        $header->setBold(700);
        $header->setColor(16);

        /* Add title line */
        $c = 0;
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('status'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('lastname'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('firstname'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('email'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('group'))), $header);

        /* Load insert data block by block */
        $l = 1; // file line
        $blockLength = 1000; // contacts block length to optimise memory usage
        $blockCurrent = 0; // current block to run, to be updated in loop

        while ($blockCurrent*$blockLength < $contactCount) {
            $contacts = $this->contactItem->get_objectList(false, '' , $blockCurrent*$blockLength, $blockLength, 'lastname', 'asc');

            foreach ($contacts as $id => $contact) {
                $c = 0;
                /* add details cells */
                $worksheet->write($l, $c++, utf8_decode(string_html2text($status[$contact->vars['status']])));
                $worksheet->write($l, $c++, utf8_decode($contact->vars['lastname']));
                $worksheet->write($l, $c++, utf8_decode($contact->vars['firstname']));
                $worksheet->write($l, $c++, $contact->vars['email']);
                $worksheet->write($l, $c++, isset($groups[$contact->vars['group']]) ? utf8_decode($groups[$contact->vars['group']]) : '');
                $l++;
            }
            $blockCurrent++;
        }

        /* Send workbook */
        $workbook->close();
    }

    /**
     * Execute module object in request / send_emailingInitialise mode.
     * @return void
     */
    private function execute_request_sendEmailingInitialise() {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_adminInit();

        /* Initialise result */
        $result = array('result'=>'failure', 'step'=>1);

        /* Check emailing id */
        if (!isset($_REQUEST['emailing_id']))
            return $result;

        /* Load emailing */
        $this->emailingItem->id = (int)$_REQUEST['emailing_id'];
        $this->emailingItem->get();
        $this->emailingItem->get_fromItems();

        $source = explode(':', $this->emailingItem->vars['contact_source']);
        if ($source[0] == 'internal') {
            /* Load contact list */
            $contactList = $this->get_contactIdList(array(
                'status'    => $source[1],
                'group'     => $this->emailingItem->vars['contact_group'],
           ));
        } elseif (isset($camyks->modules[$source[0]])) {
            $contactList = $camyks->modules[$source[0]]->get_emailingManagerContactList($source[1]);
        } else {
            $contactList = array();
        }

        /* Add list to */
        $this->emailingItem->config->vars['emailing_list'] = array();
        foreach ($contactList as $c)
            $this->emailingItem->config->vars['emailing_list'][] = array('contactid'=>$c, 'status'=>0);

        if ($this->emailingItem->config->save()) {
            /* Update emailing status */
            $this->emailingItem->_libItems['status']->value = 1;
            $this->emailingItem->_libItems['sdate']->value = time();
            $this->emailingItem->update_databaseSpecificItems(array('status', 'sdate'));

            $result['result'] = 'success';
            $result['count'] = count($contactList);
            $result['message'] = $this->get_translation('initialise_emailing_done');
            $result['message2'] = $this->get_translation('emailstobesent', count($contactList));
        } else {
            $result['result'] = 'failure';
            $result['message'] = $this->get_translation('initialise_emailing_failure');
        }

        /* Send XML */
        header("Content-type: text/xml");
        echo xml_serialize2XML($result);
        die();
    }

    /**
     * Execute module object in request / send_emailingExecute mode.
     * @return void
     */
    private function execute_request_sendEmailingExecute() {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_adminInit();

        /* Initialise result */
        $result = array('result'=>'failure', 'step'=>2);

        /* Check emailing id */
        if (!isset($_REQUEST['emailing_id']))
            return $result;

        /* Check object to execute */
        if (!isset($_REQUEST['obj']))
            return $result;

        $current = (int)$_REQUEST['obj'];

        /* Load emailing */
        $this->emailingItem->id = (int)$_REQUEST['emailing_id'];
        $this->emailingItem->get();
        $this->emailingItem->get_fromItems();

        /* Load contact */
        $source = explode(':', $this->emailingItem->vars['contact_source']);
        if ($source[0] == 'internal') {
            $this->contactItem->id = $this->emailingItem->config->vars['emailing_list'][$current]['contactid'];
            $this->contactItem->get();
            $this->contactItem->get_fromItems();
        } elseif (isset($camyks->modules[$source[0]])) {
            $this->contactItem->id = $this->emailingItem->config->vars['emailing_list'][$current]['contactid'];
            $this->contactItem->get_fromArray($camyks->modules[$source[0]]->get_emailingManagerContactInfo($this->contactItem->id, $source[1]));
            $this->contactItem->get_fromItems();
        } else {
            /* what to do ? */
        }

        /* Create new email */
        $this->emailItem->initialise();
        $this->emailItem->_libItems['emailing']->value = $this->emailingItem->id;
        $this->emailItem->_libItems['source']->value = $this->emailingItem->vars['contact_source'];
        $this->emailItem->_libItems['contact']->value = $this->contactItem->id;
        $this->emailItem->save();

        /* Initialise e-mail object */
        $mail = new CMail();

        /* Check and set return path */
        if ($this->emailingItem->vars['advanced_envelope_email'] != '')
            $mail->set_returnPath($this->emailingItem->vars['advanced_envelope_email']);

        /* Set mail sender */
        $mail->set_sender($this->emailingItem->vars['sender_email'], $this->emailingItem->vars['sender_name']);

        /* Set mail reply to */
        $mail->add_replyTo($this->emailingItem->vars['replyto_email'], $this->emailingItem->vars['replyto_name']);

        /* Set mail recipient */
        $mail->add_recipient($this->contactItem->vars['email'], $this->contactItem->get_fullName());

        /* Set mail content */
        $mail->set_subject(utf8_decode($this->emailingItem->vars['email_title']));
        $mail->set_textBody('');

        $params = $this->contactItem->get_itemsAsMailParams();
        $params['image_path'] = $this->emailingItem->get_imageFolderPath().'/';
        $params['unsubscribe_link'] = $camyks->get_confValue('url').'/emailing-unsubscribe-'.$this->emailingItem->id.'-'.$this->emailItem->id.'.gnl?email='.$this->contactItem->vars['email'];
        $params['link_([0-9]*)'] = $camyks->get_confValue('url').'/emailing-link-'.$this->emailingItem->id.'-'.$this->emailItem->id.'-$1.gnl';
        $params['opened_img'] = $camyks->get_confValue('url').'/emailing-check-'.$this->emailingItem->id.'-'.$this->emailItem->id.'.gnl';

        /* Check and set List-Unsubscribe link */
        if ($this->emailingItem->vars['advanced_include_listunsub'] == 1) {
            if ($this->emailingItem->vars['advanced_envelope_email'] != '')
                $e = $this->emailingItem->vars['advanced_envelope_email'];
            elseif ($this->emailingItem->vars['replyto_email'] != '')
                $e = $this->emailingItem->vars['replyto_email'];
            elseif ($this->emailingItem->vars['sender_email'] != '')
                $e = $this->emailingItem->vars['sender_email'];
            $mail->add_header('List-Unsubscribe', '<mailto:'.$e.'>, <'.$params['unsubscribe_link'].'>');
        }

        $mail->set_HTMLBody($this->emailingItem->get_emailContent($params));

        /* Attach embed images */
        $i=0;
        while (isset($this->emailingItem->vars['email_contentimage'.$i])) {
            $mail->add_embeddedImage($this->emailingItem->vars['email_contentimage'.$i]);
            $i++;
        }

        $name = $this->contactItem->get_fullName();
        if ($name == '')
            $name = $this->contactItem->vars['email'];
        else
            $name .= '('.$this->contactItem->vars['email'].')';

        /* Send email */
        if ($mail->send()) {
            $result['result'] = 'success';
            $result['message'] = $this->get_translation('send_email_done', htmlentities($name));

            /* Update email */
            $this->emailItem->_libItems['sent_status']->value = 1;
            $this->emailItem->_libItems['sent_date']->value = time();
            $this->emailItem->save();
        } else {
            $result['message'] = $this->get_translation('send_email_failure', htmlentities($name));
            $result['error'] = isset($mail->error)?$mail->error:'Undefined';
        }

        /* Update config */
        $this->emailingItem->config->vars['emailing_current'] = $current;
        $this->emailingItem->config->vars['emailing_list'][$current]['status'] = 1;
        $this->emailingItem->config->save();

        /* Send XML */
        header("Content-type: text/xml");
        echo xml_serialize2XML($result);
        die();
    }

    /**
     * Execute module object in request / send_emailingFinalise mode.
     * @return void
     */
    private function execute_request_sendEmailingFinalise() {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_adminInit();

        /* init result */
        $result = array('result'=>'failure', 'step'=>3);

        /* Check emailing id */
        if (!isset($_REQUEST['emailing_id']))
            return $result;

        /* Load emailing */
        $this->emailingItem->id = (int)$_REQUEST['emailing_id'];
        $this->emailingItem->get();
        $this->emailingItem->get_fromItems();

        /* Update emailing status */
        $this->emailingItem->_libItems['status']->value = 2;
        $this->emailingItem->_libItems['edate']->value = time();
        $this->emailingItem->update_databaseSpecificItems(array('status', 'edate'));

        $result['result'] = 'success';
        $result['message'] = $this->get_translation('finalise_emailing_done');

        /* Send XML */
        header("Content-type: text/xml");
        echo xml_serialize2XML($result);
        die();
    }

    /**
     * Execute module object in request / setEmailAsOpened mode.
     * @param array $params
     * @return void
     */
    private function execute_request_setEmailAsOpened($params) {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_siteInit();

        /* Load blank img */
        $f = new FSFile($this->get_filePath('img/blank.gif'));

        /* Check params number */
        if (count($params) != 2)
            $f->send();
        $emailing = $params[0];
        $email = $params[1];

        /* Check for test values */
        if ($email == 'test')
            $f->send();

        $this->emailItem->id = (int)$email;
        $this->emailItem->get();
        $this->emailItem->get_fromItems();

        /* Check emailing value */
        if ((int)$emailing == $this->emailItem->vars['emailing'] and $this->emailItem->vars['opened_status'] == 0) {
            $this->emailItem->_libItems['opened_status']->value = 1;
            $this->emailItem->_libItems['opened_date']->value = time();
            $this->emailItem->save();
        }

        /* Send image */
        $f->send();
    }

    /**
     * Execute module object in request / openEmailLink mode.
     * @param array $params
     * @return void
     */
    private function execute_request_openEmailLink($params) {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_siteInit();

        /* Load blank img */
        $f = new FSFile($this->get_filePath('img/blank.gif'));

        /* Check params number */
        if (count($params) != 3)
            header('Location: '.$camyks->get_confValue('url').'/');
        $emailing = $params[0];
        $email = $params[1];
        $link = $params[2];

        /* Check for test values */
        if ($email != 'test') {
            /* Load email */
            $this->emailItem->id = (int)$email;
            if ($this->emailItem->get()) {
                $this->emailItem->get_fromItems();
                if ((int)$emailing == $this->emailItem->vars['emailing']) {
                    if ($this->emailItem->vars['opened_status'] == 0) {
                        $this->emailItem->_libItems['opened_status']->value = 1;
                        $this->emailItem->_libItems['opened_date']->value = time();
                    }
                    if ($this->emailItem->vars['firstclick_date'] == 0)
                        $this->emailItem->_libItems['firstclick_date']->value = time();
                    $this->emailItem->_libItems['click_count']->value++;
                    $this->emailItem->save();
                }
            }
        }

        /* Load emailing */
        $this->emailingItem->id = (int)$emailing;
        if (!$this->emailingItem->get())
            header('Location: '.$camyks->get_confValue('url').'');
        $this->emailingItem->load_config();

        /* Redirect visitor to the good page */
        if (isset($this->emailingItem->config->vars['content_links'][$link])) {
            header('Location: '.$this->emailingItem->config->vars['content_links'][$link]);
        } else {
            /* send default link */
            header('Location: '.$camyks->get_confValue('url').'');
        }
    }

    /**
     * Execute module object in request / import_contactInitialise mode.
     * @return void
     */
    private function execute_request_importContactInitialise() {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_adminInit();

        /* Initialise result */
        $result = array('result'=>'failure', 'step'=>1);

        $this->config = new Admin_GenericEmailingManagerContactsImportConfig('contactsImport', $this);
        $this->config->get();

        /* Build result */
        $result['result'] = 'success';
        $result['count'] = $this->config->vars['row_count'];
        $result['message'] = $this->get_translation('initialise_importation_done');
        $result['message2'] = $this->get_translation('contactstobeimported', $this->config->vars['row_count']+1-$this->config->vars['first_line']);

        /* Send XML */
        header("Content-type: text/xml");
        echo xml_serialize2XML($result);
        die();
    }

    /**
     * Execute module object in request / import_contactExecute mode.
     * @return void
     */
    private function execute_request_importContactExecute() {
        global $camyks;

        /* Load site context */
        $camyks->get_adminInit();

        /* init result */
        $result = array('result'=>'failure', 'step'=>2);

        /* Check object to execute */
        if (!isset($_REQUEST['obj']))
            return $result;

        $current = (int)$_REQUEST['obj'];

        /* Load configuration */
        $this->config = new Admin_GenericEmailingManagerContactsImportConfig('contactsImport', $this);
        $this->config->get();

        /* Load XLS file */
        $path = $this->get_varFilePath().'Importations/'.$this->config->vars['import_file'];
        require_once 'Spreadsheet/Excel/Reader.php';
        $this->xlsFile = new Spreadsheet_Excel_Reader($path);

        /* Build line to read */
        $line = $this->config->vars['first_line'] + $current;

        /* Build contact to save */
        $this->contactItem->id = 0;
        $this->contactItem->initialise();
        $this->contactItem->_libItems['status']->value = 1;

        for ($i=1; $i<$this->config->vars['col_count']+1; $i++) {
            if ($this->config->vars['cols_params']['col'.$i.'_field'] === 'none')
                continue;
            if ($this->config->vars['cols_params']['col'.$i.'_field'] == 'status') {
                 if (isset($this->config->vars['cols_params']['col'.$i.'_status']) and $this->config->vars['cols_params']['col'.$i.'_status'][$this->xlsFile->value($line, $i)] >= 0)
                    $this->contactItem->_libItems['status']->value = $this->config->vars['cols_params']['col'.$i.'_status'][$this->xlsFile->value($line, $i)];
            } else {
                 $this->contactItem->_libItems[$this->config->vars['cols_params']['col'.$i.'_field']]->value = $this->xlsFile->value($line, $i);
            }
        }
        $this->contactItem->get_fromItems();
        $name = $this->contactItem->get_fullName();
        if ($name == '')
            $name = $this->contactItem->vars['email'];
        else
            $name .= '('.$this->contactItem->vars['email'].')';
        $name = string_text2html($name);
        if ($this->contactItem->save()) {
            $result['result'] = 'success';
            $result['message'] = $this->get_translation('import_contact_done', $name);
        } else {
            $result['message'] = $this->get_translation('import_contact_failure', $name);
            $result['error'] = $this->contactItem->_libError;
        }

        /* Update config */
        $this->config->vars['import_current'] = $current+1;
        $this->config->save();

        /* Send XML */
        header("Content-type: text/xml");
        echo xml_serialize2XML($result);
        die();
    }

    /**
     * Execute module object in request / import_contactFinalise mode.
     * @return void
     */
    private function execute_request_importContactFinalise() {
        global $camyks;

        /* Load CaMykS context */
        $camyks->get_adminInit();

        /* Initialise result */
        $result = array('result'=>'failure', 'step'=>3);

        /* Load configuration */
        $this->config = new Admin_GenericEmailingManagerContactsImportConfig('contactsImport', $this);
        $this->config->get();

        /* Trash all old files */
        folder_delete($this->get_varFilePath().'Importations');

        /* Update result */
        $result['result'] = 'success';
        $result['message'] = $this->get_translation('finalise_importation_done');

        /* Send XML */
        header("Content-type: text/xml");
        echo xml_serialize2XML($result);
        die();
    }

    /* Data management & manipulation methods */

    /**
     * Return emailing status list.
     * @return array
     */
    public function get_emailingStatusList() {
        return $this->emailingItem->get_statusList();
    }

    /**
     * Return emailings status list.
     * @param boolean $more
     * @return array
     */
    public function get_emailingsStatusList($more=false) {
        return $this->emailingItem->get_multiStatusList($more);
    }

    /**
     * Return emailing status icon list.
     * @param boolean $more
     * @return array
     */
    public function get_emailingStatusIconList($more=false) {
        if (!isset($this->emailingStatusIconList))
            $this->emailingStatusIconList = $this->emailingItem->get_statusIconList();
        return $this->emailingStatusIconList;
    }

    /**
     * Return emailing statistics summary.
     * @param integer $emailing
     * @return array
     */
    private function get_emailingStatisticsSummary($emailing) {
        return $this->emailItem->get_statisticsSummary($emailing);
    }

    /**
     * Return contact status list.
     * @return array
     */
    public function get_contactStatusList() {
        return $this->contactItem->get_statusList();
    }

    /**
     * Return contacts status list.
     * @param boolean $more
     * @return array
     */
    public function get_contactsStatusList($more=false) {
        return $this->contactItem->get_multiStatusList($more);
    }

    /**
     * Return contact status icon list.
     * @param boolean $more
     * @return array
     */
    public function get_contactStatusIconList($more=false) {
        if (!isset($this->contactStatusIconList))
            $this->contactStatusIconList = $this->contactItem->get_statusIconList();
        return $this->contactStatusIconList;
    }

    /**
     * Return contact list.
     * @param array $params
     * @return array
     */
    private function get_contactList($params=array()) {
        return $this->contactItem->get_list($params);
    }

    /**
     * Return contact group list.
     * @param boolean $all
     * @param boolean $other
     * @return array
     */
    protected function get_contactGroupList($all=false, $other=false) {
        return $this->contactItem->get_groupList($all, $other);
    }

    /**
     * Return contact source list.
     * @return array $params
     */
    private function get_contactSourceList() {
        $this->load_registeredExtensions();
        $list = array(
            'internal:1' => $this->get_translation('contactsource_internal'),
            'internal:99' => $this->get_translation('contactsource_internaltest'),
        );
        foreach ($this->extensions as $module) {
            $list = array_merge($list, $module->get_emailingManagerContactSourceList());
        }
        return $list;
    }

    /**
     * Return contact count
     * @param array $params
     * @return array
     */
    private function count_contacts($params=array()) {
        return $this->contactItem->count($params);
    }

    /**
     * Return contact id list.
     * @param array $params
     * @return array
     */
    private function get_contactIdList($params=array()) {
        return $this->contactItem->get_idList($params);
    }

    /**
     * Return contact email list.
     * @param array $params
     * @return array
     */
    private function get_contactEmailList($params=array()) {
        return $this->contactItem->get_emailList($params);
    }

    /**
     * Mark contact as invalid
     * @param integer $contactId
     * @param string $source
     * @return boolean success
     */
    private function mark_contactAsInvalid($contactId, $source) {
        $source = explode(':', $source);
        if ($source[0] == 'internal') {
            $this->contactItem->id = $contactId;
            return $this->contactItem->mark_asInvalid();
        }
    }

    /**
     * Load extensions list.
     * @return void
     */
    private function load_registeredExtensions() {
        if (is_array($this->extensions))
            return;
        $this->extensions = $this->get_registeredExtensions();
    }

    /**
     * Add contact information.
     * @param array $params
     * @return boolean success
     */
    public function add_contact($params=array()) {
        return $this->contactItem->add_object($params);
    }
}
?>
