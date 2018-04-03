<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Sep 2010
 * Last Modif Date  : Mar 2018
 * 
 * Admin_GenericGuestBookManager module
 */

final class Admin_GenericGuestBookManager extends Module {

    /*
     * internal variable
     */
    public $msgItem;
    public $msgList;
    public $config;

    /*
     * constructor
     * @param string $path_type
     * @return void
     * @access public
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericGuestBookManager', $path_type);
        
        /* set module type */
        $this->type = 'admin';
        $this->admin_type = 'content';
        
        /* set plugin version */
        $this->version = '1.0';
        
        /* set plugin package */
        $this->plugin_package = 'Generic';
        
        /* set plugin author */
        $this->author_name = 'CaMykS';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
        
        /* load plugin libaries */
        $this->load_library('Admin_GenericGuestBookManagerMessage');
        $this->load_library('Admin_GenericGuestBookManagerConfig');
        
        /* initialise plugin libraries */
        $this->msgItem = new Admin_GenericGuestBookManagerMessage(0, $this);
        $this->config = new Admin_GenericGuestBookManagerConfig('config', $this);
    
        /* register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }
    
    /* overwrite Module methods */
    
    /*
     * install module
     * @return boolean success
     * @access public
     */
    public function install() {
        return ($this->msgItem->install() and $this->config->install() and parent::install());
    }
    
    /*
     * unintall module
     * @return boolean success
     * @access public
     */
    public function uninstall() {
        return parent::uninstall();
    }
    
    /*
     * check module installation
     * @return boolean result
     * @access public
     */
    public function is_installed() {
        return $this->msgItem->is_installed();
    }
  
    /*
     * get module rights
     * @return void
     * @access public
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

    /*
     * update control panel description
     * @return void
     * @access public
     */
    public function get_adminControlPanelAction( ) {
        global $camyks;
        
        /* count messages by status */
        $n = $this->msgItem->get_objectCount('status=2');
        
        /* update module description for admin control panel */
        if ($n == 1)
            $camyks->trads['mod_admin_genericguestbookmanager_desc'] = $this->get_translation('desc1');
        elseif ($n > 1)
            $camyks->trads['mod_admin_genericguestbookmanager_desc'] = $this->get_translation('descx', $n);
    }  
    
    /*
     * return notified items for module
     * @return Array
     * @access public
     */
    public function get_adminInternalNotifications() {
        
        /* load reports count */
        $cnt = $this->msgItem->get_objectCount('status=2');
        if ($cnt == 0)
            return array();
        
        /* initialise result */
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
        
        /* send result */
        return $result;    
    }
  
    /*
     * init module object in admin mode
     * @return void
     * @access public
     */
    public function init_admin() {
        global $camyks;
        
        /* check read rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();
        
        /* check dependencies */
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        
        /* get informations */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';
        
        /* load config */
        $this->config->get();
        
        /* check action to execute */
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
    
    /* specific admin mode methods */
    
    /*
     * init module object in admin/main mode
     * @return void
     * @access private
     */
    private function init_admin_main() {
        global $camyks;
        
        /* get data */
        $this->adminTitle = $this->title;
        
        /* load list parameters*/
        $this->load_library('Admin_GenericGuestBookManagerMessageListParams');
        
        /* initialise object list input */
        $this->msgList = &$camyks->inputs['AdminItemListViewer'];
        /* add parameters */
        $this->msgList->set_params($this->msgListParams); 
        /* initialise input */
        $this->msgList->initialise();
        
        /* load tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];
        
        /* check for config panel */
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

        /* initialise tabs */        
        $this->tabBuilder->initialise(array('default'=>'Messages'));
    
        /* get buttons */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
    }

    /*
     * init module object in admin/view_msg mode
     * @return void
     * @access private
     */
    private function init_admin_viewMsg(){
        global $camyks;
        
        /* check item id */
        if (!isset($_REQUEST['msg_id']))
            return $this->init_admin_main();
        
        /* load message */
        $this->msgItem->id = (int)$_REQUEST['msg_id'];
        $this->msgItem->get();
        $this->msgItem->get_fromItems();
        
        /* load interface title */
        $this->adminTitle = $this->get_translation('title_msgid', $this->msgItem->id);
        
        /* build buttons list */
        $this->buttons = array(array(
            'link'  => $this->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
        
        /* update layout */
        $this->set_selectedLayout('admin_view_msg.html.inc');
    }
    
    /*
     * init module object in admin/edit_msg mode
     * @return void
     * @access private
     */
    private function init_admin_editMsg() {
        global $camyks;
        
        /* check rights */
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
        
        /* load interface title */
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
        
        /* update layout */
        $this->set_selectedLayout('admin_edit_msg.html.inc');
    }
    
    /*
     * init module object in admin/save_msg mode
     * @return void
     * @access private
     */
    private function init_admin_saveMsg() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();
        
        /* disable admin menu */
        $this->disable_adminEngineMenus();
        
        /* check item id */
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
        
        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /*
     * init module object in admin/delete_msg mode
     * @return void
     * @access private
     */
    private function init_admin_deleteMsg() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();
        
        /* disable admin menu */
        $this->disable_adminEngineMenus();
        
        /* check item id */
        if (!isset($_REQUEST['msg_id']))
            return $this->init_admin_main();
        
        /* try to save item */
        $this->msgItem->id = (int)$_REQUEST['msg_id'];
        if ( $this->msgItem->delete()){
            $this->text = $this->get_translation('message_deleted');
        } else {
            $this->text = $this->get_translation('message_notdeleted');
        }
        
        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }
    
    /*
     * init module object in admin/edit_config mode
     * @return void
     * @access private
     */
    private function init_admin_editConfig() {
        global $camyks;
        
        /* check user rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();
        
        /* load config */
        $this->config->get();
        
        /* load external data */
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
        
        /* update layout */
        $this->selected_layout = 'admin_edit_config.html.inc';
    }
    
    /*
     * init module object in admin/save_config mode
     * @return void
     * @access private
     */
    private function init_admin_saveConfig() {
        global $camyks;
        
        /* check user rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();
        
        /* disable admin menu */
        $this->disable_adminEngineMenus();
        
        /* save config */
        $this->config->get_fromHeader();
        if ( $this->config->save())
            $this->text = $this->get_translation('config_saved');
        else
            $this->text = $this->get_translation('config_notsaved');
        
        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect(4, $this->get_adminLink());
    }
        
    /* message related methods */
    
    /*
     * return messages status list
     * @param boolean $full
     * @return array
     * @access public
     */
    public function get_messagesStatusList($full=false) {
        return $this->msgItem->get_multiStatusList($full);
    }
    
    /*
     * return message status list
     * @return array
     * @access public
     */
    public function get_messageStatusList() {
        return $this->msgItem->get_statusList();
    }
    
    /*
     * return message status icon list
     * @return array
     * @access public
     */
    public function get_messageStatusIconList() {
        return $this->msgItem->get_statusIconList();
    }
    
    /*
     * return message list
     * @param array $params
     * @return array
     * @access public
     */
    public function get_messageList($params) {
        return $this->msgItem->get_list($params);
    }
    
    /*
     * return message count
     * @param array $param
     * @return integer
     * @access public
     */
    public function count_messages($params=array()) {
        return $this->msgItem->count($params);
    }
    
    /*
     * save message from site
     * @return boolean success
     * @access public
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
    
    /*
     * return message object
     * @return object
     * @access public
     */
    public function get_messageObject() {
        return $this->msgItem;
    }
    
    /* notification related methods */
    
    
    /*
     * send notification emails
     * @param string $vEmail
     * @return void
     * @access private
     */
    private function send_notifications() {
        global $camyks;
        
        /* check for notifications status */
        if ($this->get_configValue('notification_status') == 0)
            return true;
        
        /* load sender & recipients */
        $sender = $this->get_configValue('notification_sender');
        $recipients = $this->get_configValue('notification_recipients');

        /* check sender & recipients */
        if ($sender == '' or count($recipients) == 0)
            return true;

        /* load content */
        $subject = string_html2Text($this->get_translation('notification_emailsubject'));
    
        /* send email */
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
    
    /*
     * return admin email content
     * @return string
     * @access private
     */
    private function get_notificationContent() {
        global $camyks;
        
        /* load CSS */
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
    
    /* statistics related methods */
    
    /*
     * update statistics
     * @return boolean success
     * @access private
     */
    private function update_statistics() {
        global $camyks;
        
        /* check for statistics status */
        if ($this->get_configValue('statistic_status') == 0)
          return true;
        
        /* update statistics */
        return $camyks->update_statistic('guestbook_msg', $this->name, 'dated', '', '', '');
    }
    
    /* specific tool methods */
   
    /*
     * get config value
     * @param string $item
     * @return mixed
     * @access public
     */
    public function get_configValue($item) {
        return $this->config->get_value($item);
    }
    
    /*
     * load additional dictionnary
     * @return void
     * @access public
    */
    public function load_additionalDictionnary() {
        $this->add_translation('/data');
    }
    
    /* Admin_Site extension configuration methods */
    
    /*
     * initialise object in Admin_Site / view configuration mode
     * @return void
     * @access public
     */
    public function initialise_configDisplay() {
        $this->isConfig = true;
         
        /* load config */
        $this->config->get();
    }
  
    /*
     * display object in Admin_Site / view configuration mode
     * @return void
     * @access public
     */
    public function display_configDisplay() {
        $this->load_file('html/configuration/view.html.inc');
    }
  
    /*
     * initialise object in Admin_Site / edit configuration mode
     * @param Object $form
     * @return void
     * @access public
     */
    public function initialise_configEdition($form) {
        global $camyks;
        
        $this->isConfig = true;
         
        /* load config */
        $this->config->get();
        
        /* load external data */
        $this->userList = $camyks->modules['Admin_User']->get_activeUserList(true);
        
        /* update form */
        $this->configform = &$form;
        $this->configform->set_object($this->config);
        $this->configform->add_hidden('notification_recipients_count_', count($this->userList));
    }
    
    /*
     * display object in Admin_Site / edit configuration mode
     * @return void
     * @access public
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }
    
    /*
     * execute object in Admin_Site / save configuration mode
     * @return void
     * @access public
     */
    public function save_configuration() {
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>