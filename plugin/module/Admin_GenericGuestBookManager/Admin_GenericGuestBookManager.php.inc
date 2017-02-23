<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * History :
 * * 10-09-22 : Initial files
 * 
 * Admin_GenericGuestBookManager module
 */

class Admin_GenericGuestBookManager extends Module {
  /*
   * internal variable
   */
  var $msgItem;
  var $msgList;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GenericGuestBookManager ( $path_type ) {
    parent::Module('Admin_GenericGuestBookManager', $path_type);
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
    $this->libs[] = 'Admin_GenericGuestBookManagerMessage.php.inc';
    $this->libs[] = 'Admin_GenericGuestBookManagerConfig.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->msgItem = new Admin_GenericGuestBookManagerMessage(0, $this);
    $this->config = new Admin_GenericGuestBookManagerConfig('config', $this);
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->msgItem->install() and $this->config->install()
	    and parent::install());
  }
  
  /*
   * unintall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return parent::uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->msgItem->is_installed();
  }
  
  /*
   * get module rights
   * @return void
   * @access private
   */
  function get_rights() {
    global $camyks;
    $this->rights[0] = array('name'=>'read',
			     'title'=> $camyks->get_translation('read'),
			     'default'=> true);
    $this->rights[1] = array('name'=>'write',
			     'title'=> $camyks->get_translation('write'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'edit_config',
			     'title'=> $this->get_translation('rights_editconfig'),
			     'default'=> false);
  }

  /*
   * update control panel description
   * @return void
   * @access private
   */
  function get_adminControlPanelAction( ) {
    global $camyks;
    $n = $this->msgItem->get_objectCount('status=2');
    if ( $n == 1 )
      $camyks->trads['mod_admin_genericguestbookmanager_desc'] = $camyks->trads['mod_admin_genericguestbookmanager_desc1'];
    elseif ($n > 1)
      $camyks->trads['mod_admin_genericguestbookmanager_desc'] = vsprintf($camyks->trads['mod_admin_genericguestbookmanager_descx'], $n);
  }
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check read rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();

    /* check dependencies */
    if (!isset($camyks->inputs['AdminItemListViewer']))
      return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    
    /* get informations */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'main' );

    /* load config */
    $this->config->get();

    /* check action to execute */
    switch ( $this->mode ) {
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
 
  /*
   * display module object in admin mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }
  
  /* specific admin mode methods */

  /*
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  function init_admin_main() {
    global $camyks;

    /* get data */
    $this->adminTitle = $this->title;
  
    /* load list parameters*/
    $this->load_file('lib/Admin_GenericGuestBookManagerMessageListParams.php.inc');

    /* initialise object list input */
    $this->msgList = &$camyks->inputs['AdminItemListViewer'];
    /* add parameters */
    $this->msgList->set_params($this->msgListParams); 
    /* initialise input */
    $this->msgList->initialise();

    /* check for config panel */
    if ($this->check_right(2) !== false) {
      /* get tabs */
      $this->tabBuilder = &$camyks->inputs['TabBuilder'];
      $this->tabBuilder->add_tabs(array(array('name'=>'config',
					      'title'=>$this->get_translation('tabconfig')),
					array('name'=>'messages',
					      'title'=>$this->get_translation('tabmessages'))));
      $this->tabBuilder->initialise(array('default'=>'messages'));
    }
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }

  /*
   * init module object in admin/view_msg mode
   * @return void
   * @access private
   */
  function init_admin_viewMsg(){
    global $camyks;

    /* check item id */
    if (!isset($_REQUEST['msg_id']))
      return $this->init_admin_main();

    /* load message */
    $this->msgItem->id = $_REQUEST['msg_id'];
    $this->msgItem->get();
    $this->msgItem->get_fromItems();
    
    /* load interface title */
    $this->adminTitle = $this->get_translation('title_msgid', $this->msgItem->id);
    
    /* build buttons list */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
    
    /* update layout */
    $this->selected_layout = 'admin_view_msg.html.inc';
  }

  /*
   * init module object in admin/edit_msg mode
   * @return void
   * @access private
   */
  function init_admin_editMsg(){
    global $camyks;
    
    /* check rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* get item */
    $this->msgItem->id = isset($_REQUEST['msg_id'])?$_REQUEST['msg_id']:0;
    $this->msgItem->get();
    $this->msgItem->get_fromItems();

    /* build edition form */
    $this->editform = new HTMLForm('editform',
				   $this->get_adminLink(array('mode'=>'save_msg')),
				   'POST');
    $this->editform->set_object($this->msgItem);
    $this->editform->add_hidden('msg_id', $this->msgItem->id);
    $this->editform->add_hidden('locale', $this->msgItem->vars['locale']);
    $this->editform->add_hidden('ipaddress', $this->msgItem->vars['ipaddress']);

    /* load interface title */
    if ($this->msgItem->id == 0 )
      $this->adminTitle = $this->get_translation('title_newmsg');
    else
      $this->adminTitle = $this->get_translation('title_msgid', $this->msgItem->id);


    /* build buttons list */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));

    /* update layout */
    $this->selected_layout = 'admin_edit_msg.html.inc';
  }

  /*
   * init module object in admin/save_msg mode
   * @return void
   * @access private
   */
  function init_admin_saveMsg(){
    global $camyks;
    
    /* check rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* check item id */
    if (!isset($_REQUEST['msg_id']))
      return $this->init_admin_main();

    /* try to save item */
    $this->msgItem->id = $_REQUEST['msg_id'];
    $this->msgItem->get_fromHeader();
    if ( $this->msgItem->save() ) {
      $this->text = $this->get_translation('message_saved');
    } else {
      $this->text = $this->get_translation('message_notsaved');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }

  /*
   * init module object in admin/delete_msg mode
   * @return void
   * @access private
   */
  function init_admin_deleteMsg(){
    global $camyks;
    
    /* check rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* check item id */
    if (!isset($_REQUEST['msg_id']))
      return $this->init_admin_main();

    /* try to save item */
    $this->msgItem->id = $_REQUEST['msg_id'];
    if ( $this->msgItem->delete()){
      $this->text = $this->get_translation('message_deleted');
    } else {
      $this->text = $this->get_translation('message_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }

  /*
   * init module object in admin/edit_config mode
   * @return void
   * @access private
   */
  function init_admin_editConfig() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* load config */
    $this->config->get();

    /* load external data */
    $this->userList = $camyks->modules['Admin_User']->get_activeUserList(true);
    
    /* get configuration form */
    $this->configform = new HTMLForm('configform',
				     $this->get_adminLink(array('mode' => 'save_config')),
				     'POST');
    $this->configform->set_object($this->config);
    $this->configform->add_hidden('notification_recipients_count_', count($this->userList));

    /* build window title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('title_config');
    
    /* build button list */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->configform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_config.html.inc';
  }
  
  /*
   * init module object in admin/save_config mode
   * @return void
   * @access private
   */
  function init_admin_saveConfig() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(2) === false )
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
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }
  
  /* specific tool methods */

  /*
   * return messages status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_messagesStatusList($full=false) {
    return $this->msgItem->get_multiStatusList($full);
  }

  /*
   * return message status list
   * @return array
   * @access private
   */
  function get_messageStatusList() {
    return $this->msgItem->get_statusList();
  }

  /*
   * return message status icon list
   * @return array
   * @access private
   */
  function get_messageStatusIconList() {
    return $this->msgItem->get_statusIconList();
  }

  /*
   * send notification emails
   * @param string $vEmail
   * @return void
   * @access private
   */
  function send_notifications() {
    global $camyks;

    /* check for notifications status */
    if($this->get_configValue('notification_status') == 0)
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
      mail_sendHTMLMail(array('to'=>$this->admin->email,
			      'from'=>$sender,
			      'subject'=>$subject,
			      'content'=>$content));
    }
  }  
  
  /*
   * return admin email content
   * @return string
   * @access private
   */
  function get_notificationContent() {
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

  /*
   * update statistics
   * @return boolean success
   * @access private
   */
  function update_statistics() {
    global $camyks;

    /* check for statistics status */
    if($this->get_configValue('statistic_status') == 0)
      return true;
    
    /* update statistics */
    return $camyks->update_statistic('guestbook_msg', $this->name, 'dated', '', '', '');
  }

  /*
   * get config value
   * @param string $item
   * @return mixed
   * @access private
   */
  function get_configValue($item) {
    if (!isset($this->config->vars))
      $this->config->get();
    return $this->config->vars[$item];
  }

  /* specific public methods */
  
  /*
   * return message list
   * @param array $params
   * @return array
   * @access public
   */
  function get_messageList($params) {
    return $this->msgItem->get_list($params);
  }

  /*
   * save message from site
   * @return boolean success
   * @access public
   */
  function save_siteMessage() {
    $this->msgItem->id = 0;
    $this->msgItem->get_fromHeader();
    $this->msgItem->_libItems['status']->value = $this->get_configValue('message_validation') == 0 ? 1 : 2;
    if($this->msgItem->save()) {
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
  function get_messageObject() {
    return $this->msgItem;
  }

  /*
   * return message count
   * @param array $param
   * @return integer
   * @access public
   */
  function count_messages($params=array()) {
    return $this->msgItem->count($params);
  }
  
}
?>