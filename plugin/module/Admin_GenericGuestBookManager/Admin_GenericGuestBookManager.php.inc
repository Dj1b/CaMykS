<?php
/**
 * @brief Admin_GenericGuestBookManager module
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Sep 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericGuestBookManager class.
 */
final class Admin_GenericGuestBookManager extends Module {
    /**
     * @var Object $msgItem
     * @brief Message object.
     */
    public $msgItem;
    
    /**
     * @var array $msgList
     * @brief Message list.
     */
    public $msgList;
    
    /**
     * var Object $config
     * @brief Plugin configuration.
     */
    protected $config;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericGuestBookManager', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libaries */
        $this->load_library('Admin_GenericGuestBookManagerMessage');
        $this->load_library('Admin_GenericGuestBookManagerConfig');

        /* Initialise plugin libraries */
        $this->msgItem = new Admin_GenericGuestBookManagerMessage(0, $this);
        $this->config = new Admin_GenericGuestBookManagerConfig('config', $this);

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
        $this->register_asExtension('Content_GenericLegalMentions');
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->msgItem->install() and $this->config->install() and parent::install());
    }

    /**
     * Uninstall module.
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
        return $this->msgItem->is_installed();
    }

    /**
     * Define module permission.
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
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      =>'edit_config',
            'title'     => $this->get_translation('rights_editconfig'),
            'default'   => false,
        );
    }

    /**
     * Update control panel description.
     * @return void
     */
    public function get_adminControlPanelAction( ) {
        global $camyks;

        /* Count messages by status */
        $n = $this->msgItem->get_objectCount('status=2');

        /* Update module description for admin control panel */
        if ($n == 1)
            $camyks->trads['mod_admin_genericguestbookmanager_desc'] = $this->get_translation('desc1');
        elseif ($n > 1)
            $camyks->trads['mod_admin_genericguestbookmanager_desc'] = $this->get_translation('descx', $n);
    }

    /**
     * Return notified items for module.
     * @return Array
     */
    public function get_adminInternalNotifications() {

        /* Load reports count */
        $cnt = $this->msgItem->get_objectCount('status=2');
        if ($cnt == 0)
            return array();

        /* Initialise result */
        $result = array($this->name => array(
            'title' => $this->title,
            'items' => array(
                array(
                    'title'     => $this->get_translation('messagestatus_pending'),
                    'cnt'       => $cnt,
                    'priority'  => 1,
                )
            )
        ));

        /* Send result */
        return $result;
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');

        /* Load configuration */
        $this->config->get();

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        /* Execute action */
        switch ($this->mode) {
            case 'view_msg':
                /* mode == view_msg */
                $this->init_admin_viewMsg();
                break;
            case 'edit_msg':
                /* mode == edit_msg */
                $this->init_admin_editMsg();
                break;
            case 'save_msg':
                /* mode == save_msg */
                $this->init_admin_saveMsg();
                break;
            case 'delete_msg':
                /* mode == delete_msg */
                $this->init_admin_deleteMsg();
                break;
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_editConfig();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_saveConfig();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* generic Module init */
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/main mode
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* get data */
        $this->adminTitle = $this->title;

        /* Load list parameters*/
        $this->load_library('Admin_GenericGuestBookManagerMessageListParams');

        /* Initialise object list input */
        $this->msgList = &$camyks->inputs['AdminItemListViewer'];
        /* add parameters */
        $this->msgList->set_params($this->msgListParams);
        /* Initialise input */
        $this->msgList->initialise();

        /* Load tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* Check for config panel */
        if ($this->check_right(2) !== false) {
            $this->tabBuilder->add_tab(array(
                'name'  => 'Config',
                'title' => $this->get_translation('tabconfig'),
            ));
        }

        /* add message list tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'Messages',
            'title' => $this->get_translation('messages'),
        ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Messages'));

        /* get buttons */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
    }

    /**
     * Initialise module object in admin/view_msg mode
     * @return void
     */
    private function init_admin_viewMsg(){
        global $camyks;

        /* Check item id */
        if (!isset($_REQUEST['msg_id']))
            return $this->init_admin_main();

        /* Load message */
        $this->msgItem->id = (int)$_REQUEST['msg_id'];
        $this->msgItem->get();
        $this->msgItem->get_fromItems();

        /* Load interface title */
        $this->adminTitle = $this->get_translation('title_msgid', $this->msgItem->id);

        /* build buttons list */
        $this->buttons = array(array(
            'link'  => $this->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));

        /* Update layout */
        $this->set_selectedLayout('admin_view_msg.html.inc');
    }

    /**
     * Initialise module object in admin/edit_msg mode
     * @return void
     */
    private function init_admin_editMsg() {
        global $camyks;

        /* Check rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* get item */
        $this->msgItem->id = isset($_REQUEST['msg_id'])?(int)$_REQUEST['msg_id']:0;
        $this->msgItem->get();
        $this->msgItem->get_fromItems();

        /* build edition form */
        $this->editform = new HTMLForm(
            'editform',
            $this->get_adminLink(array('mode'=>'save_msg')),
            'POST'
        );
        $this->editform->set_object($this->msgItem);
        $this->editform->add_hidden('msg_id', $this->msgItem->id);

        /* Load interface title */
        if ($this->msgItem->id == 0 )
            $this->adminTitle = $this->get_translation('title_newmsg');
        else
            $this->adminTitle = $this->get_translation('title_msgid', $this->msgItem->id);

        /* build buttons list */
        $this->buttons = array(
            array(
                'link'=>$this->get_adminLink(),
                'title'=>$camyks->get_translation('back'),
            ),
            array(
                'link'=>$this->editform->get_HTMLSubmitLink(),
                'title'=>$camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_msg.html.inc');
    }

    /**
     * Initialise module object in admin/save_msg mode
     * @return void
     */
    private function init_admin_saveMsg() {
        global $camyks;

        /* Check rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* Check item id */
        if (!isset($_REQUEST['msg_id']))
            return $this->init_admin_main();

        /* try to save item */
        $this->msgItem->id = (int)$_REQUEST['msg_id'];
        $this->msgItem->get_fromHeader();
        if ($this->msgItem->save()) {
            $this->text = $this->get_translation('message_saved');
        } else {
            $this->text = $this->get_translation('message_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/delete_msg mode
     * @return void
     */
    private function init_admin_deleteMsg() {
        global $camyks;

        /* Check rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* Check item id */
        if (!isset($_REQUEST['msg_id']))
            return $this->init_admin_main();

        /* try to save item */
        $this->msgItem->id = (int)$_REQUEST['msg_id'];
        if ( $this->msgItem->delete()){
            $this->text = $this->get_translation('message_deleted');
        } else {
            $this->text = $this->get_translation('message_notdeleted');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/edit_config mode
     * @return void
     */
    private function init_admin_editConfig() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load config */
        $this->config->get();

        /* Load external data */
        $this->userList = $camyks->modules['Admin_User']->get_activeUserList(true);

        /* get configuration form */
        $this->configform = new HTMLForm(
            'configform',
            $this->get_adminLink(array('mode' => 'save_config')),
            'POST'
        );
        $this->configform->set_object($this->config);
        $this->configform->add_hidden('notification_recipients_count_', count($this->userList));

        /* build window title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('title_config');

        /* build button list */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->configform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
        );

        /* Update layout */
        $this->selected_layout = 'admin_edit_config.html.inc';
    }

    /**
     * Initialise module object in admin/save_config mode
     * @return void
     */
    private function init_admin_saveConfig() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save config */
        $this->config->get_fromHeader();
        if ( $this->config->save())
            $this->text = $this->get_translation('config_saved');
        else
            $this->text = $this->get_translation('config_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect(4, $this->get_adminLink());
    }

    /* message related methods */

    /**
     * Return messages status list
     * @param boolean $full
     * @return array
     */
    public function get_messagesStatusList($full=false) {
        return $this->msgItem->get_multiStatusList($full);
    }

    /**
     * Return message status list
     * @return array
     */
    public function get_messageStatusList() {
        return $this->msgItem->get_statusList();
    }

    /**
     * Return message status icon list
     * @return array
     */
    public function get_messageStatusIconList() {
        return $this->msgItem->get_statusIconList();
    }

    /**
     * Return message list
     * @param array $params
     * @return array
     */
    public function get_messageList($params) {
        return $this->msgItem->get_list($params);
    }

    /**
     * Return message count
     * @param array $params
     * @return integer
     */
    public function count_messages($params=array()) {
        return $this->msgItem->count($params);
    }

    /**
     * save message from site
     * @return boolean success
     */
    public function save_siteMessage() {
        $this->msgItem->id = 0;
        $this->msgItem->get_fromHeader();
        $this->msgItem->_libItems['status']->value = $this->get_configValue('message_validation') == 0 ? 1 : 2;
        if ($this->msgItem->save()) {
            $this->send_notifications();
            $this->update_statistics();
            return true;
        }
        $this->msgItem->get_fromItems();
        return false;
    }

    /**
     * Return message object
     * @return object
     */
    public function get_messageObject() {
        return $this->msgItem;
    }

    /* notification related methods */

    /**
     * Send notification emails
     * @param string $vEmail
     * @return void
     */
    private function send_notifications() {
        global $camyks;

        /* Check for notifications status */
        if ($this->get_configValue('notification_status') == 0)
            return true;

        /* Load sender & recipients */
        $sender = $this->get_configValue('notification_sender');
        $recipients = $this->get_configValue('notification_recipients');

        /* Check sender & recipients */
        if ($sender == '' or count($recipients) == 0)
            return true;

        /* Load content */
        $subject = string_html2Text($this->get_translation('notification_emailsubject'), 'ISO-8859-1');

        /* Send email */
        foreach ($recipients as $rec) {
            $this->admin = new AdminUser($rec);
            $this->admin->get();
            $content = $this->get_notificationContent();
            mail_sendHTMLMail(array(
                'to'        =>$this->admin->email,
                'from'      =>$sender,
                'subject'   =>$subject,
                'content'   =>$content
            ));
        }
    }

    /**
     * Return admin email content
     * @return string
     */
    private function get_notificationContent() {
        global $camyks;

        /* Load CSS */
        $css = $camyks->themes[$camyks->get_confValue('site_default_theme')]->get_filePath('email.css');

        /* build html page */
        ob_start();
        $page = new HTMLPage();
        $page->add_styleIncludedFile($css);
        $page->add_HTMLHeader();
        $this->load_file('html/email_notification.html.inc');
        $page->add_HTMLFooter();

        $c = ob_get_contents();
        ob_end_clean();
        return $c;
    }

    /* Statistics related methods */

    /**
     * Update statistics
     * @return boolean success
     */
    private function update_statistics() {
        global $camyks;

        /* Check for statistics status */
        if ($this->get_configValue('statistic_status') == 0)
          return true;

        /* Update statistics */
        return $camyks->update_statistic('guestbook_msg', $this->name, 'dated', '', '', '');
    }

    /* Specific tool methods */

    /**
     * Return config value.
     * @param string $item
     * @return mixed
     */
    public function get_configValue($item) {
        return $this->config->get_value($item);
    }

    /**
     * Load additional dictionnary.
     * @return void
    */
    public function load_additionalDictionnary() {
        $this->add_translation('/data');
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode
     * @return void
     */
    public function initialise_configDisplay() {
        $this->isConfig = true;

        /* Load config */
        $this->config->get();
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

        /* Load config */
        $this->config->get();

        /* Load external data */
        $this->userList = $camyks->modules['Admin_User']->get_activeUserList(true);

        /* Update form */
        $this->configform = &$form;
        $this->configform->set_object($this->config);
        $this->configform->add_hidden('notification_recipients_count_', count($this->userList));
    }

    /**
     * Display object in Admin_Site / edit configuration mode
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }

    /**
     * Execute object in Admin_Site / save configuration mode
     * @return void
     */
    public function save_configuration() {
        $this->config->get_fromHeader();
        return $this->config->save();
    }

    /* Content_GenericLegalMentions extension methods */

    /**
     * Return legal mentions data.
     * @return array
     */
    public function get_legalMentionsData() {
        /* Load dictionnary */
        $this->load_additionalDictionnary();

        /* Return values */
        return array(
            $this->name => array(
                array(
                    'title'         => $this->get_translation('legalmentions_data_title'),
                    'description'   => $this->get_translation('legalmentions_data_description'),
                    'duration'      => $this->get_translation('legalmentions_data_duration'),
                    'data'          => $this->get_translation('legalmentions_data_items'),
                ),
            ),
        );
    }
}
?>
