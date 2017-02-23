<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Creation Date	: Jun 2005
 * Last Modif Date      : Mar 2007
 * History :
 * * 05-06-xx : Initial files
 *
 * Site configuration engine
 *
 * TO DO :
 * - complete config settings
 * - save config mode
 *
*/

class Admin_Site extends Module {
  /* variables */
  var $conf;
  var $mode;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_Site ($path_type) {
    parent::Module('Admin_Site', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'configuration';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* conf array from camyks object */
    $this->conf = array();
    $this->conf_elements=array('cms', /* CaMykS */
			       'cms_version', /* CaMykS version */
			       'engine_path', /* CaMykS path */
			       'site_name', /* site name ( folder name ) */
			       'site_title', /* site title */
			       'url', /* site url */
			       'encoding', /* data encoding */
			       'version', /* site version */
			       'admin_entry', /* admin entry point : admin.php */
			       'friendlyurls', /* is friendlyurls actived */
			       'site_author', /* site author */
			       'site_company', /* site company */
			       'workflow', /* workflow active */
			       'maintenance', /* is maintenant actived */
			       'database_name', /* database name */
			       'database_host', /* database host */
			       'database_login', /* database login */
			       'database_pwd', /* database pwd */
			       'admin_ssl', /* ssl handling in admin mode */
			       'admin_default_language', /* default language in admin mode */
			       'admin_languages', /* availables languages in admin mode */
			       'admin_default_theme', /* default theme in admin mode */
			       'site_ssl', /* ssl handling in site mode */
			       'site_default_theme', /* default theme in site mode */
			       'site_default_template', /* default template in site mode */
			       'site_languages', /* availables languages in site mode */
			       'site_default_language', /* default language in site mode */
			       'editing_languages', /* available languages in edition mode */
			       'page_maxmodules', /* max modules in a page */
			       'google_analytics', /* google analytics code */
			       'admin_allowblockthemechange', /* allow block theme change in page editor */
			       'admin_itemsbypage', /* items displayed in generic admin lists */
			       'admin_maxfilesize', /* max file size in admin forms */
			       
			       );
  }
  
  /* overwrite Module methods */
  
  /*
   * get module rights
   * @return void
   * @access private
   */
  function get_rights() {
    global $camyks;
    $this->rights[0] = array('name'=>'read',
			     'title'=> $camyks->get_translation('read'),
			     'default'=> false);
    /* $this->rights[1] = array('name'=>'edit',
			     'title'=> $camyks->get_translation('write'),
			     'default'=> false);*/
  }

  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    if ( $this->check_right(0) === false ) {
      $this->init_admin_accessDenied();
    } else if ( $this->check_right(1) === false ) {
      $this->init_admin_read();
    } else {
      $this->mode = ( isset( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'modify' );      
      switch ( $this->mode ) {
      case 'save':
	$this->init_admin_save();
	break;
      case 'modify':
      default:
	/* 
	 * TO DO 
	 * execute init_admin_modify method
	 */
	$this->init_admin_read();
	break;
      }
    }
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
   * init object module in admin/save mode
   * @return void
   * @access private
   */
  function init_admin_save () {
    global $camyks;
    $c = array();
    /* get all values */
    $c['cms'] = $_POST['cms'];
    $c['cms_version'] = $_POST['cms_version'];
    $c['engine_path'] = $_POST['engine_path'];
    $c['short_name'] = $_POST['short_name'];
    $c['real_name'] = $_POST['real_name'];
    $c['url'] = $_POST['url'];
    $c['version'] = $_POST['version'];
    $c['maintenance'] = $_POST['maintenance'];
    $c['site_author'] = $_POST['site_author'];
    $c['site_company'] = $_POST['site_compagny'];
    $c['database_name'] = $camyks->site_conf['database_name'];
    $c['database_host'] = $camyks->site_conf['database_host'];
    $c['database_login'] = $camyks->site_conf['database_login'];
    $c['database_pwd'] = $camyks->site_conf['database_pwd'];
    $c['admin_entry'] = $_POST['admin_entry'];
    $c['admin_default_theme'] = $_POST['admin_default_theme'];
    $c['admin_default_language'] = $_POST['admin_default_language'];
    $c['admin_languages'] = array();
    $c['site_default_theme'] = $_POST['admin_default_theme'];
    $c['site_default_template'] = $_POST['admin_default_template'];
    $c['site_default_language'] = $_POST['admin_default_language'];
    $c['site_languages'] = array();
  }

  /*
   * init object module in admin/modify mode
   * @return void
   * @access private
   */
  function init_admin_modify() {
    global $camyks;
    /* get conf */
    $this->conf = &$camyks->_conf;
    /* get javascript tab object */
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript('admin_site_tabObject = new CTab();');
    $this->add_JSScript('admin_site_tabObject.init("general", "'
			.$camyks->theme->parts['boxTabCSSStandart'].'", "'
			.$camyks->theme->parts['boxTabCSSSelected'].'", "'
			.$camyks->theme->parts['boxTabCSSRollover'].'");');
    /* get form object */
    $this->form = new HTMLForm ( 'siteConf',
				 $camyks->get_adminLink($this->name),
				 'POST');
    $this->form->add_hidden ('action', 'save' );
    $this->form->add_hidden ('name', $this->conf['site_name']);
    $this->form->add_hidden ('database_host', $this->conf['database_host']);
    $this->form->add_hidden ('database_name', $this->conf['database_name']);
    $this->form->add_hidden ('database_login', $this->conf['database_login']);
    $this->form->add_hidden ('database_pwd', $this->conf['database_pwd']);
    /* update layout */
    $this->selected_layout = 'admin_rw.html.inc';
  }

  /*
   * init object module in admin/read only mode
   * @return void
   * @access private
   */
  function init_admin_read ( ) {
    global $camyks;
    /* get conf */
    $this->conf = &$camyks->_conf;
    /* get javascript tab object */
    $this->tabObject = 'admin_site_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'", "'
			.$this->theme->parts['boxTabCSSSelected'].'", "'
			.$this->theme->parts['boxTabCSSRollover'].'");');
    
    /* tab list for tabs bar */
    $this->tabs = array(array('name' => 'general',
			      'title' => $this->get_translation('general')),
			array('name' => 'db',
			      'title' => $this->get_translation('database')),
			array('name' => 'viewpart',
			      'title' => $this->get_translation('viewpart')),
			array('name' => 'adminpart',
			      'title' => $this->get_translation('adminpart')));
    
    /* button list for buttons bar */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink()));

    /* get database size */
    $this->dbsize = $camyks->db_conn->database_getSize();
    $this->dbsize = file_getFileSize($this->dbsize);
    
    /* update layout */
    $this->selected_layout = 'admin_r.html.inc';   
  }

  /* specific tool methods */
  
  /* 
   * return conf default value
   * @param string $confName
   * @param mixed $default
   * @return mixed
   * @access private
   */
  function get_confDefaultValue($confName, $default) {
    global $camyks;

    switch ($confName) {
    case 'site_title':
      return '';
    case 'url':
      return '';
    case 'encoding':
      return 'utf8';
    case 'version':
      return '1.0';
    case 'admin_entry':
      return 'admin.php';
    case 'friendlyurls':
      return true;
    case 'site_author':
      return '';
    case 'site_company':
      return '';
    case 'workflow':
      return false;
    case 'maintenance':
      return false;
    case 'database_name':
      return '';
    case 'database_host':
      return '';
    case 'database_login':
      return '';
    case 'database_pwd':
      return '';
    case 'admin_ssl':
      return 'default';
    case 'admin_default_language':
      return 'en';
    case 'admin_languages':
      return array('en');
    case 'admin_default_theme':
      return 'GreyStyle';
    case 'site_ssl':
      return 'default';
    case 'site_default_theme':
      return 'GreyStyle';
    case 'site_default_template':
      return 'DefaultPage';
    case 'site_languages':
      return array('en');
    case 'site_default_language':
      return 'en';
    case 'editing_languages':
      return $camyks->get_confDefaultValue('site_languages');
    case 'page_maxmodules':
      return 8;
    case 'google_analytics':
      return '';
    case 'admin_allowblockthemechange':
      return false;
    case 'admin_itemsbypage':
      return 20;
    case 'admin_maxfilesize':
      return 128*1024;
    }
    return $default;
  }
}
?>