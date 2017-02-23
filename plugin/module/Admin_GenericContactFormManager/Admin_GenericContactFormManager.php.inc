<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Nov 2010
 * Last Modif Date  : Nov 2010
 * History :
 * * 10-11-02 : Initial files
 * 
 * Admin_GenericContactFormManager module
 */

class Admin_GenericContactFormManager extends Module {
  /*
   * internal variable
   */
  var $formItem;
  var $formList;
  var $subjectItem;
  var $subjectList;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GenericContactFormManager ( $path_type ) {
    parent::Module('Admin_GenericContactFormManager', $path_type);
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
    $this->libs[] = 'Admin_GenericContactFormManagerForm.php.inc';
    $this->libs[] = 'Admin_GenericContactFormManagerSubject.php.inc';
    $this->libs[] = 'Admin_GenericContactFormManagerConfig.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->formItem = new Admin_GenericContactFormManagerForm(0, $this);
    $this->subjectItem = new Admin_GenericContactFormManagerSubject(0, $this);
    $this->config = new Admin_GenericContactFormManagerConfig('config', $this);
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->formItem->install() and $this->subjectItem->install()
	    and $this->config->install() and parent::install());
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
    return $this->formItem->is_installed();
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
			     'default'=>true);
    $this->rights[1] = array('name'=>'edit_forms',
			     'title'=> $this->get_translation('rights_editforms'),
			     'default'=>false);
    $this->rights[2] = array('name'=>'edit_subject',
			     'title'=>$this->get_translation('rights_editsubjects'),
			     'default'=>false);
    $this->rights[3] = array('name'=>'edit_config',
			     'title'=>$this->get_translation('rights_editconfig'),
			     'default'=>false);
  }

  /*
   * update control panel description
   * @return void
   * @access private
   */
  function get_adminControlPanelAction( ) {
    global $camyks;
    $n = $this->formItem->get_objectCount('status=0');
    if ( $n == 1 )
      $camyks->trads['mod_admin_genericcontactformmanager_desc'] = $camyks->trads['mod_admin_genericcontactformmanager_desc1'];
    elseif ($n > 1)
      $camyks->trads['mod_admin_genericcontactformmanager_desc'] = vsprintf($camyks->trads['mod_admin_genericcontactformmanager_descx'], $n);
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
    case 'view_form':
      /* mode == view_form */
      $this->init_admin_viewForm();
      break;
    case 'edit_form':
      /* mode == edit_form */
      $this->init_admin_editForm();
      break;
    case 'save_form':
      /* mode == save_form */
      $this->init_admin_saveForm();
      break;
    case 'delete_form':
      /* mode == delete_form */
      $this->init_admin_deleteForm();
      break;
    case 'view_subject':
      /* mode == view_subject */
      $this->init_admin_viewSubject();
      break;
    case 'edit_subject':
      /* mode == edit_subject */
      $this->init_admin_editSubject();
      break;
    case 'save_subject':
      /* mode == save_subject */
      $this->init_admin_saveSubject();
      break;
    case 'delete_subject':
      /* mode == delete_subject */
      $this->init_admin_deleteSubject();
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
    $this->load_file('lib/Admin_GenericContactFormManagerFormListParams.php.inc');

    /* initialise object list input */
    $this->formList = &$camyks->inputs['AdminItemListViewer'];
    /* add parameters */
    $this->formList->set_params($this->formListParams); 
    /* initialise input */
    $this->formList->initialise();

    /* check for config panel */
    if ($this->check_right(2) !== false) {
      /* get tabs */
      $this->tabBuilder = &$camyks->inputs['TabBuilder'];
      $this->tabBuilder->add_tabs(array(array('name'=>'config',
					      'title'=>$this->get_translation('tabconfig')),
					array('name'=>'forms',
					      'title'=>$this->get_translation('tabforms'))));
      $this->tabBuilder->initialise(array('default'=>'forms'));
    }
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }

  /*
   * init module object in admin/view_form mode
   * @return void
   * @access private
   */
  function init_admin_viewForm(){
    global $camyks;

    /* check item id */
    if (!isset($_REQUEST['form_id']))
      return $this->init_admin_main();

    /* load form */
    $this->formItem->id = $_REQUEST['form_id'];
    $this->formItem->get();
    $this->formItem->get_fromItems();
    
    /* load interface title */
    $this->adminTitle = $this->get_translation('title_formid', $this->formItem->id);
    
    /* build buttons list */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
    
    /* update layout */
    $this->selected_layout = 'admin_view_form.html.inc';
  }

  /*
   * init module object in admin/edit_form mode
   * @return void
   * @access private
   */
  function init_admin_editForm(){
    global $camyks;
    
    /* check rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* get item */
    $this->formItem->id = isset($_REQUEST['form_id'])?$_REQUEST['form_id']:0;
    $this->formItem->get();
    $this->formItem->get_fromItems();

    /* build edition form */
    $this->editform = new HTMLForm('editform',
				   $this->get_adminLink(array('mode'=>'save_form')),
				   'POST');
    $this->editform->set_object($this->formItem);
    $this->editform->add_hidden('form_id', $this->formItem->id);
    $this->editform->add_hidden('locale', $this->formItem->vars['locale']);
    $this->editform->add_hidden('ipaddress', $this->formItem->vars['ipaddress']);

    /* load interface title */
    if ($this->formItem->id == 0 )
      $this->adminTitle = $this->get_translation('title_newform');
    else
      $this->adminTitle = $this->get_translation('title_formid', $this->formItem->id);


    /* build buttons list */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));

    /* update layout */
    $this->selected_layout = 'admin_edit_form.html.inc';
  }

  /*
   * init module object in admin/save_form mode
   * @return void
   * @access private
   */
  function init_admin_saveForm(){
    global $camyks;
    
    /* check rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* check item id */
    if (!isset($_REQUEST['form_id']))
      return $this->init_admin_main();

    /* try to save item */
    $this->formItem->id = $_REQUEST['form_id'];
    $this->formItem->get_fromHeader();
    if ( $this->formItem->save() ) {
      $this->text = $this->get_translation('form_saved');
    } else {
      $this->text = $this->get_translation('form_notsaved');
    }
    /* update layout */
    $this->selected_layout = 'admin_form.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }

  /*
   * init module object in admin/delete_form mode
   * @return void
   * @access private
   */
  function init_admin_deleteForm(){
    global $camyks;
    
    /* check rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* check item id */
    if (!isset($_REQUEST['form_id']))
      return $this->init_admin_main();

    /* try to save item */
    $this->formItem->id = $_REQUEST['form_id'];
    if ( $this->formItem->delete()){
      $this->text = $this->get_translation('form_deleted');
    } else {
      $this->text = $this->get_translation('form_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_form.html.inc';
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
    $this->selected_layout = 'admin_form.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }
  
  /* specific tool methods */

  /*
   * return forms status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_formsStatusList($full=false) {
    return $this->formItem->get_multiStatusList($full);
  }

  /*
   * return form status list
   * @return array
   * @access private
   */
  function get_formStatusList() {
    return $this->formItem->get_statusList();
  }

  /*
   * return form status icon list
   * @return array
   * @access private
   */
  function get_formStatusIconList() {
    return $this->formItem->get_statusIconList();
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
    return $camyks->update_statistic('contact_form', $this->name, 'dated', '', '', '');
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
   * return form list
   * @param array $params
   * @return array
   * @access public
   */
  function get_formList($params) {
    return $this->formItem->get_list($params);
  }

  /*
   * save form from site
   * @return boolean success
   * @access public
   */
  function save_siteForm() {
    $this->formItem->id = 0;
    $this->formItem->get_fromHeader();
    if($this->formItem->save()) {
      $this->send_notifications();
      $this->update_statistics();
      return true;
    }
    $this->formItem->get_fromItems();
    return false;
  }

  /*
   * return form object
   * @return object
   * @access public
   */
  function get_formObject() {
    return $this->formItem;
  }

  /*
   * return form count
   * @param array $param
   * @return integer
   * @access public
   */
  function count_forms($params=array()) {
    return $this->formItem->count($params);
  }
  
}
?>