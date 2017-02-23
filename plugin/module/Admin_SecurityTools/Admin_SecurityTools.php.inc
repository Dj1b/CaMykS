<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Create Date		: Oct 2007
 * Last Modif Date	: May 2008
 * History :
 * * 07-10-27 : Initial files, IP Filter tool
 * * 07-11-05 : Add backup tool
 * * 08-05-21 : Minor online help html improvements (french)
 * * 08-05-28 : Disable admin menu for data I/O modes
 *
 * Some security tools :
 * - IP Filter : Done
 * - BackUp : Done ( based on register_shutdown_function method )
 * - Flood (POST) Control : ?
 *
 * To Do :
 * - remove cdata & cplugin folders sym links from "complete" backup
 * - fully display the page before starting a new "automatic" backup
 * - allow to cp, ftp, scp, ... automatic backups
 * - add script timeout extension as parameter into the backup config file
*/

class Admin_SecurityTools extends Module {
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_SecurityTools ( $path_type ) {
    parent::Module('Admin_SecurityTools', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'configuration';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';

    /* get module libs */
    $this->libs[] = 'Admin_SecurityToolsConfig.php.inc';
    $this->libs[] = 'Admin_SecurityIPFilterRule.php.inc';
    $this->libs[] = 'Admin_SecurityBackUpFile.php.inc';
    $this->get_PHPLibs();

    /* get lib objects */
    $this->config = new Admin_SecurityToolsConfig('config', $this );
    $this->ipfilterrule = new Admin_SecurityIPFilterRule(0, $this );
    $this->backupfile = new Admin_SecurityBackUpFile(0, $this );

    /* load config */
    $this->config->get();

    /* check security */
    $this->check_security();

    /* list tools */
    $this->tools = array('ipfilter', 'backup');
  }
  
  /* overwrite Module Methods */

  /*
   * install module object
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->ipfilterrule->install() and $this->backupfile->install() ) {
      return parent::install();
    }
    return false;
  }
  
  /*
   * uninstall module object
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return ($this->ipfilterrule->uninstall() 
	    and $this->backupfile->uninstall()
	    and parent::uninstall());
  }

  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed( ) {
    return $this->backupfile->is_installed();
  }

  /* 
   * get rights
   * @return void
   * @access private
   */
  function get_rights ( ) {
    global $camyks;
    $this->rights[0] = array('name'=>'read',
			     'title'=> $camyks->get_translation('read'),
			     'default'=> false);
    $this->rights[1] = array('name'=>'config',
			     'title'=> $this->get_translation('right_config'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'ipfilter',
			     'title'=> $this->get_translation('right_ipfilter'),
			     'default'=> false);
    $this->rights[3] = array('name'=>'backup',
			     'title'=> $this->get_translation('right_backup'),
			     'default'=> false);
  }

  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check read rights */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied () ;
    }

    /* get mode */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'main' );

    /* execute mode */
    switch ( $this->mode ) {
    case 'update_config':
      /* mode == update_config */
      $this->init_admin_updateConfig();
      break;
    case 'edit_ipfilter':
      /* mode == edit_ipfilter */
      $this->init_admin_editIPFilter();
      break;
    case 'save_ipfilter':
      /* mode == save_ipfilter */
      $this->init_admin_saveIPFilter();
      break;
    case 'delete_ipfilter':
      /* mode == delete_ipfilter */
      $this->init_admin_deleteIPFilter();
      break;
    case 'edit_backupconfig':
      /* mode == edit_backupconfig */
      $this->init_admin_editBackUpConfig();
      break;
    case 'save_backupconfig':
      /* mode == save_backupconfig */
      $this->init_admin_saveBackUpConfig();
      break;
    case 'delete_backupfile':
      /* mode == delete_backupfile */
      $this->init_admin_deleteBackUpFile();
      break;
    case 'edit_newbackupfile':
      /* mode == edit_newbackupfile */
      $this->init_admin_editNewBackUpFile();
      break;
    case 'save_newbackupfile':
      /* mode == save_newbackupfile */
      $this->init_admin_saveNewBackUpFile();
    case 'main':
      /* mode == main */
      $this->init_admin_main();
      break;
    }
    /* generic initialisation */
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

    /* add needed JS */
    $this->add_JSFile('admin_securitytools.js');

    /* get tabs */
    $this->tabObject = 'securitytools_tabObject';
    $this->openTab = isset( $_REQUEST['openTab'] ) ? $_REQUEST['openTab'] : '';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("main", "'
      .$this->theme->parts['boxTabCSSStandart'].'","'
      .$this->theme->parts['boxTabCSSSelected'].'","'
      .$this->theme->parts['boxTabCSSRollover'].'");');
    if ( $this->openTab != '' ) {
      $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');
    }

    $this->tabs = array(array('name'=>'main',
			      'title'=>$this->get_translation('tabmain')));
    /* check for available tools */
    if ( $this->config->vars['ipfilter'] ) {
      $this->tabs[] = array('name'=>'ipfilter',
			    'title'=>$this->get_translation('tool_ipfilter'));
      /* add needed JS for ipfilter tool */
      $this->add_JSScript('deletefiprmessage="'.$camyks->encode_value(html_entity_decode($this->get_translation('deletefilteriprule'))).'";');
      $this->add_JSScript('deletefiprurl="'.$camyks->get_adminJSLink($this->name,
								     array('mode'=>'delete_ipfilter',
									   'ruleid'=>'')).'";');
      /* get filter ip rules */
      $this->get_IPFilterRules();
    }

    if ( $this->config->vars['backup'] and $this->check_right(3) ) {
      $this->tabs[] = array('name'=>'backup',
			    'title'=>$this->get_translation('tool_backup'));
      /* add needed JS for ipfilter tool */
      $this->add_JSScript('deletebackupmessage="'.$camyks->encode_value(html_entity_decode($this->get_translation('backup_deletebackup'))).'";');
      $this->add_JSScript('deletebackupurl="'.$camyks->get_adminJSLink($this->name,
									array('mode'=>'delete_backupfile',
									      'backup_id'=>'')).'";');
      /* get backup files */
      $this->get_backUpFiles();
    }

    /* get plugin help */
    $this->get_help();
    if ( $this->help ) {
      $this->tabs[] = array('name'=>'help',
			    'title'=>$camyks->get_translation('help'));
    }

    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }

  /*
   * init module object in admin/edit_ipfilter mode
   * @return void
   * @access private
   */
  function init_admin_editIPFilter() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(2) === false ) {
      return $this->init_admin_actionNotAllowed();
    }
    /* get object */
    $ruleid = isset($_REQUEST['ruleid']) ? $_REQUEST['ruleid'] : 0;
    $this->ipfilterrule->id = $ruleid;
    $this->ipfilterrule->get();
    $this->ipfilterrule->get_fromItems();
    /* get form */
    $this->init_admin_editIPFilterForm();
  }

  /*
   * complete module object init in admin/edit_ipfilter
   * @return void
   * @access private
   */
  function init_admin_editIPFilterForm() {
    global $camyks;
    /* get form */
    $this->form = new HTMLForm('edit_ipfilter',
			       $camyks->get_adminLink($this->name,
						      array('mode'=>'save_ipfilter')),
			       'POST');
    $this->form->add_hidden('ruleid', $this->ipfilterrule->id );

    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink($this->name, array('openTab'=>'ipfilter')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->form->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));

    $this->selected_layout = 'admin_editipfilter.html.inc';
 
  }

  /*
   * init module object in admin/save_ipfilter mode
   * @return void
   * @access private
   */
  function init_admin_saveIPFilter() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(2) === false ) {
      return $this->init_admin_actionNotAllowed();
    }
    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* save rule */
    $ruleid = isset($_REQUEST['ruleid']) ? $_REQUEST['ruleid'] : 0;
    $this->ipfilterrule->id = $ruleid;
    $this->ipfilterrule->get_fromHeader();
    if ( $this->ipfilterrule->save() ) {
      $this->text = $this->get_translation('rule_saved');
      $this->selected_layout = 'admin_message.html.inc';
      $this->selected_layout_location = 'camyks';
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'ipfilter')));
    } else {
      $this->ipfilterrule->get_fromItems();
      $this->init_admin_editIPFilterForm();
    }
  }

  /*
   * init module object in admin/delete_ipfilter mode
   * @return void
   * @access private
   */
  function init_admin_deleteIPFilter() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(2) === false ) {
      $this->init_admin_actionNotAllowed();
      return;
    }
    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* delete rule */
    $ruleid = isset($_REQUEST['ruleid']) ? $_REQUEST['ruleid'] : 0;
    $this->ipfilterrule->id = $ruleid;
    if ( $this->ipfilterrule->delete()) {
      $this->text = $this->get_translation('rule_deleted');
    } else {
      $this->text = $this->get_translation('rule_notdeleted');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'ipfilter')));
  }

  /*
   * init module object in admin/update_config mode
   * @return void
   * @access private
   */
  function init_admin_updateConfig() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(1) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* get update values */
    if ( isset($_REQUEST['action']) and in_array($_REQUEST['action'], array('enable', 'disable'))
	 and isset($_REQUEST['item']) and isset($this->config->vars[$_REQUEST['item']])) {
      $this->config->vars[$_REQUEST['item']] = ( $_REQUEST['action'] == 'enable' );
      if ($this->config->save() ) {
	$this->text = $this->get_translation('config_saved');
      } else {
	$this->text = $this->get_translation('config_notsaved');
      }
    } else {
      $this->text = $this->get_translation('config_notsaved');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }

  /*
   * init module object in admin/edit_backupconfig mode
   * @return void
   * @access private
   */
  function init_admin_editBackUpConfig() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(3) === false ) {
      return $this->init_admin_actionNotAllowed();
    }
    
    /* get values lists for backup tool */
    $this->get_backUpValues();
    
    /* get form */
    $this->form = new HTMLForm('edit_backupconfig',
			       $camyks->get_adminLink($this->name,
						      array('mode'=>'save_backupconfig')),
			       'POST');
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink($this->name, array('openTab'=>'backup')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->form->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    /* update layout */
    $this->selected_layout='admin_editbackupconfig.html.inc';
  }
  
  /*
   * init module object in admin/save_backupconfig mode
   * @return void
   * @access private
   */
  function init_admin_saveBackUpConfig() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(3) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get values lists for backup tool */
    $this->get_backUpValues();
    
    /* get method value */
    $this->config->vars['backup_method'] = (isset($_REQUEST['backup_method']) and isset($this->backup_methods[$_REQUEST['backup_method']])) ? $_REQUEST['backup_method']:'manual';
    
    /* get compression value */
    $this->config->vars['backup_compression'] = (isset($_REQUEST['backup_compression']) and isset($this->backup_compressions[$_REQUEST['backup_compression']])) ? $_REQUEST['backup_compression']:'tar';
    
    /* get type value */
    $this->config->vars['backup_type'] = (isset($_REQUEST['backup_type']) and isset($this->backup_types[$_REQUEST['backup_type']]))? $_REQUEST['backup_type']:'complete';
    
    /* get temp folder value */
    $this->config->vars['backup_temp'] = (isset($_REQUEST['backup_temp']) ? $_REQUEST['backup_temp'] : '' );

    /* get nextdate value */
    switch ( $this->config->vars['backup_method'] ) {
    case 'daily':
      $this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m'), date('d')+1, date('Y'));
      break; 
    case 'weekly':
      if ( date('w') == 0 ) {
	    $d = 6;
      } else {
	    $d = date('w')-1;
      }
      $this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m'), date('d')-$d+7, date('Y'));
      break;
    case 'monthly':
      $this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m')+1, 1, date('Y'));
      break;
    default:
      $this->config->vars['backup_nextdate'] = 0;
      break;
    }
   
    /* save config file */
    if ($this->config->save() ) {
      $this->text = $this->get_translation('config_saved');
    } else {
      $this->text = $this->get_translation('config_notsaved');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'backup')));
  }

  /*
   * init module object in admin/save_backupconfig mode
   * @return void
   * @access private
   */
  function init_admin_deleteBackUpFile() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(3) === false ) {
      return $this->init_admin_actionNotAllowed();
    }
    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* get backup */
    $bid = isset($_REQUEST['backup_id'])?$_REQUEST['backup_id']:0;
    $this->backupfile->id = $bid;
    if ( $bid > 0 and $this->backupfile->get() ) {
      $this->backupfile->get_fromItems();
      
      /* try to delete file */
      if ( file_exists($this->plugin_var_path.'/'.$this->backupfile->backupdir.'/'.$this->backupfile->vars['name']))
        unlink( $this->plugin_var_path.'/'.$this->backupfile->backupdir.'/'.$this->backupfile->vars['name'] );
        
      /* delete database informations */
      $this->backupfile->delete();
      $this->text = $this->get_translation('backup_deleted');
    } else {
      $this->text = $this->get_translation('backup_notdeleted');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'backup')));
  }

  /*
   * init module object in admin/edit_newbackupfile mode
   * @return void
   * @access private
   */
  function init_admin_editNewBackUpFile() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(3) === false ) {
      return $this->init_admin_actionNotAllowed();
    }
    
    /* get values lists for backup tool */
    $this->get_backUpValues();
    
    /* get form */
    $this->form = new HTMLForm('edit_newbackupfile',
			       $camyks->get_adminLink($this->name,
						      array('mode'=>'save_newbackupfile')),
			       'POST');
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink($this->name, array('openTab'=>'backup')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->form->get_HTMLSubmitLink(),
				 'title'=>$this->get_translation('backup_createbackup')));
    /* update layout */
    $this->selected_layout='admin_editnewbackupfile.html.inc';
  }

  /*
   * init module object in admin/save_newbackupfile mode
   * @return void
   * @access private
   */
  function init_admin_saveNewBackUpFile() {
    global $camyks;
    /* check rights */
    if ( $this->check_right(3) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    $compression = isset($_REQUEST['backup_compression'])?$_REQUEST['backup_compression']:null;
    $type = isset($_REQUEST['backup_type'])?$_REQUEST['backup_type']:null;

    if ( $this->backupfile->backup('manual', $type, $compression ) ) {
      $this->text = $this->get_translation('backup_saved');
    } else {
      $this->text = $this->get_translation('backup_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'backup')));
  }

  /* specific tool methods */

  /*
   * check all security tools
   * @return void
   * @access private
   */
  function check_security () {
    global $camyks;

    /* IP Filter */
    if ( $this->config->vars['ipfilter'] ) {
      $this->ipfilterrule->check_security();
    }

    /* BackUp */
    if ( $this->config->vars['backup'] ) {
      if ( $camyks->mode == CAMYKS_MODE_ADMIN
	   and $this->config->vars['backup_method'] != 'manual'
	   and mktime() > $this->config->vars['backup_nextdate'] ) {
	    /* call backup method at the end of the whole script */
	    register_shutdown_function('_Admin_Securitytools_execute_backup');
      }
    }
  }

  /*
   * load IP Filter rules
   * @return void
   * @access private
   */
  function get_IPFilterRules() {
    $this->ipfilterrules = $this->ipfilterrule->get_objectList();
  }

  /*
   * load back up files
   * @return void
   * @access private
   */
  function get_backUpFiles() {
    $this->backupfiles = $this->backupfile->get_objectList();
  }

  /*
   * get all needed backup values
   * @return void
   * @access private
   */
  function get_backUpValues() {
    $this->backup_methods = $this->get_backupMethodsList();
    $this->backup_compressions = $this->get_backupCompressionsList();
    $this->backup_types = $this->get_backupTypesList();
  }

  /*
   * return backup methods list
   * @return array
   * @access private
   */
  function get_backupMethodsList() {
    $list = array();
    $list['manual'] = $this->get_translation('backup_method_manual');
    $list['daily'] = $this->get_translation('backup_method_daily');
    $list['weekly'] = $this->get_translation('backup_method_weekly');
    $list['monthly'] = $this->get_translation('backup_method_monthly');
    return $list;
  }

  /*
   * return backup compressions list
   * @return array
   * @access private
   */
  function get_backupCompressionsList() {
    $list = array();
    $list['tar'] = $this->get_translation('backup_compression_tar');
    $list['tgz'] = $this->get_translation('backup_compression_tgz');
    $list['tbz'] = $this->get_translation('backup_compression_tbz');
    $list['zip'] = $this->get_translation('backup_compression_zip');
    return $list;
  }

  /*
   * return backup types list
   * @return array
   * @access private
   */
  function get_backupTypesList() {
    $list = array();
    $list['complete'] = $this->get_translation('backup_type_complete');
    $list['data'] = $this->get_translation('backup_type_data');
    $list['file'] = $this->get_translation('backup_type_file');
    return $list;
  }
}

/* static methods */

/*
 * Execute backup
 * @return void
 * @access private
 */
function _Admin_Securitytools_execute_backup() {
  global $camyks;
  
  /* get Admin_SecurityTool module */
  $_this = $camyks->modules['Admin_SecurityTools'];
  
  /* update next backup date */
  switch ( $_this->config->vars['backup_method'] ) {
  case 'daily':
    $_this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m'), date('d')+1, date('Y'));
    break; 
  case 'weekly':
    if ( date('w') == 0 ) {
      $d = 6;
    } else {
      $d = date('w')-1;
    }
    $_this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m'), date('d')-$d+7, date('Y'));
    break;
  case 'monthly':
    $_this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m')+1, 1, date('Y'));
    break;
  default:
    $_this->config->vars['backup_nextdate'] = 0;
    break;
  }
  $_this->config->save();
  
  /* backup */
  $_this->backupfile->backup( );
}
?>