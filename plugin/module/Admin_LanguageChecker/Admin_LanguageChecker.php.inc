<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Nov 2006
 * Last Modif Date	: Sep 2007
 *
 * Admin_LanguageChecker Module
 * Help developers to compare dictionnary files from plugins
 */

class Admin_LanguageChecker extends Module {
  /* variables */
  var $action;
  var $locales;
  var $langs;
  var $list;
  var $items;
  var $prefix;
  var $defaultTab;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_LanguageChecker ($path_type) {
    parent::Module('Admin_LanguageChecker', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'devel';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Development';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* module values */
    $this->libs[] = 'Admin_LanguageCheckerEngine.php.inc';

    /* init */
    $this->get_PHPLibs();
  }
  
  /* overwrite Module methods */
  
  /*
   * set module rights
   * @return void
   * @access private
   */
  function get_rights () {
    global $camyks;
    $this->rights[0] = array('name'=>'read',
			     'title'=>$camyks->get_translation('read'),
			     'default'=>false);
  }
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    /* check access right */
    if ($this->check_right(0) === false) {
      return $this->init_admin_accessDenied();
    }

    /* check action to execute */
    $this->action = (isset($_REQUEST['action'])?$_REQUEST['action']:'list');
    switch ($this->action) {
    case 'checker' : 
      $this->init_admin_checker();
      break;
    case 'list' : 
    default : 
      $this->init_admin_list();
      break;
    }
    parent::init_admin();
  }

  /* specific mode methods */

  /*
   * init module object in admin/checker mode
   * @return void
   * @access private
   */
  function init_admin_checker () {
    global $camyks;
    $this->locales = array();
    $view = $_REQUEST['view'];
    $type = $_REQUEST['type'];
    $this->items = array();
    
    /* load folder */
    if ($type == 'engine' and $view == 'camyks') {
        $folder = $camyks->camyks_engine_path.'/locale';
    } else if ($type == 'engine') {
        $folder = $camyks->camyks_engine_path.'/locale/'.$view;
    } else if ($type == 'module') {
        $folder = $camyks->modules[$view]->plugin_path.'/locale';
    } else if ($type == 'input') {
        $folder = $camyks->inputs[$view]->plugin_path.'/locale';
    }
    
    /* load available languages for folder */
    $languages = array_merge($camyks->get_confValue('editing_languages'), language_getDictionnaryList($folder));
        
    foreach ($languages as $language) {
      $this->locales[$language] = new Admin_LanguageCheckerEngine ($folder, $language);
      
      /* get all items */
      foreach ($this->locales[$language]->trads as $item => $value) {
	    if (!in_array($item, $this->items)) {
	        $this->items[] = $item;
	    }
      }
    }
    
    /* sort items */
    sort($this->items);
    
    /* get prefix */
    foreach ($this->items as $i) {
      $this->prefix = $i;
      break;
    }
    foreach ($this->items as $i) {
      $this->prefix = string_getSimilarBeginning($i, $this->prefix);
    }
    
    /* get default tab */
    $this->defaultTab = '';
    foreach ($this->locales as $l=>$v) {
      $this->defaultTab = 'lang'.$l;
      break;
    }
    
    /* load tab engine */
    $this->tabObject = 'admin_languagechecker_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("'.$this->defaultTab.'", "'
			.$camyks->theme->parts['boxTabCSSStandart'].'", "'
			.$camyks->theme->parts['boxTabCSSSelected'].'", "'
			.$camyks->theme->parts['boxTabCSSRollover'].'");');
    
    /* get tabs */
    $this->tabs = array();
    foreach ($this->locales as $l => $v) {
      $this->tabs[] = array ('name' => 'lang'.$l,
			     'title' => language_getIcon($l));
    }

    /* get buttons */
    $this->buttons =  array(array('title'=>$camyks->get_translation('back'),
				  'link'=>$this->get_adminLink()));

    /* update layout */
    $this->selected_layout = 'checker.html.inc';
  }
  
  /*
   * init module object in admin/list mode
   * @return void
   * @access private
   */
  function init_admin_list () {
    global $camyks;
    $this->list = array();
    
    /* add camyks global locales */
    $this->list['camyks'] = array('type'=>'engine', 'title' => 'CaMykS');
    
    /* add camyks dedicated locales */
    $folders = folder_listFolders($camyks->camyks_engine_path.'/locale');
    foreach ($folders as $folder)
      $this->list[$folder] = array('type'=>'engine', 'title' => ' / '.$folder);

    /* add modules */
    foreach ($camyks->modules as $m) {
      $this->list[$m->name] = array('type'=>'module', 'title' => $m->title);
    }

    /* add inputs */
    foreach ($camyks->inputs as $m) {
      $this->list[$m->name] = array('type'=>'input', 'title' => $m->name);
    }

    /* get buttons */
    $this->buttons =  array(array('title'=>$camyks->get_translation('back'),
				  'link'=>$camyks->get_adminLink()));

    /* update layout */
    $this->selected_layout = 'list.html.inc';
  }  
}
?>