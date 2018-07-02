<?php
/*
 * CaMykS Engine
 * Developed by        : camyks.net
 * Author        : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version    : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date        : Oct 2005
 * Last Modif Date    : Jun 2008
 * History : 
 * * 05-10-xx : Initial files
 * * 08-06-17 : Update menu management
 *
 * Tool_InfoBar object
 */

class Tool_InfoBar extends Module {
  /* variables */
  var $barMenu;
  var $menuDisabled;
  
  /* 
   * constructor
   * @param string $path_type
   */
  function Tool_InfoBar ($path_type) {
    parent::Module('Tool_InfoBar', $path_type);
    /* set module type */
    $this->type = 'tool';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->authors_name = 'CaMykS Team';
    $this->authors_mail = 'camyks.contact@gmail.com';
    $this->authors_group = 'camyks.net';
    /* initialise plugin variables */
    $this->menuDisabled = false;
  }
  
  /* overwrite Module methods */

  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;

    if ($camyks->adminUser->login == '' or $this->menuDisabled == true) {
      $this->init_admin_nobodylogged ();
    } else {
      $this->init_admin_userlogged();
    }
    /* generic admin init */
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

  /*
   * execute module request
   * @return void
   * @access private
   */
  function execute_request() {
    global $camyks;

    /* get action to execute */
    $action = $_REQUEST['action'];
    switch($action) {
    case 'refreshAdminSession':
      
      /* load admin engine */
      $camyks->get_adminInit();
      
      /* send XML header */
      header("Content-type: text/xml");
      
      /* check login */
      if ($camyks->check_adminUser()) {
    echo '<result>success</result>';
      } else {
    echo '<result>failed</result>';
      }
      break;
    }
  }

  /* specific admin mode methods */
  
  /*
   * admin init when an admin user is logged
   * @return void
   * @access private
   */
  function init_admin_userlogged () {
    global $camyks;
    /* get admin login or name */
    if ($camyks->adminUser->firstname == '' and $camyks->adminUser->lastname == '') {
      $login = $camyks->adminUser->login;
    } else {
      $login = $camyks->adminUser->firstname . ' ' . $camyks->adminUser->lastname;
    }
    /* init bar menu */
    $this->barMenu = array();
    
    /* set main menus */
    $this->register_barMenu('admin', $this->get_translation('admin'));
    
    /* set menu items */
    $this->register_barMenuItem(array(
        'menu' => 'admin', 
        'name' => 'login', 
        'title' => $login,
        'icon' => $this->get_fileURL('img/user12.gif'),
    ));
    
    /* update menu bar with all tool & admin module entries */
    foreach ($camyks->modules as $name => $m) {
      /* get menus */
      $menus = $m->get_adminEngineGenericMenus();
      foreach ($menus as $menu) {
        $this->register_barMenu($menu['name'], $menu['title']);
      }
      /* get menu items */
      $items = $m->get_adminEngineGenericMenuItems();
      foreach ($items as $item) {
        $this->register_barMenuItem($item);
      }

      /* get generic admin menu init */
      $camyks->modules[$name]->get_adminEngineGenericInit();
    }

    /* update menu bar with specefic selected module */
    foreach ($camyks->contentPage->modules as $m) {
      /* get menus */
      $menus = $m->get_adminEngineSpecificMenus();
      foreach ($menus as $menu) {
    $this->register_barMenu ($menu['name'], $menu['title']);
      }
      /* get menu items */
      $items = $m->get_adminEngineSpecificMenuItems();
      foreach ($items as $item) {
    $this->register_barMenuItem ($item);
      }
    }

    /* specific javascript */
    $this->add_JSFile('admin_infobar.js');
    $this->add_JSScript('infobar_basedate="'.date_displayQuickDate(TODAY, $camyks->current_language).' ";');

    /* keep alive javascript */
    if ($camyks->get_confValue('admin_keep_alive') !== false and $camyks->get_confValue('admin_keep_alive') > 0){
      $this->add_JSEngineFile('object/cajaxrequest.js');

      $ka_duration = $camyks->get_confValue('admin_keep_alive')*60*1000;
      $ka_refresh = ($camyks->get_confValue('admin_keep_alive_refresh') !== false ? (int)$camyks->get_confValue('admin_keep_alive_refresh'):5)*60*1000;
      $ka_url = 'request.php?module='.$this->name.'&action=refreshAdminSession';
      $this->add_JSScript('infobar_refreshImage = "'.$this->get_fileURL('img/refresh.gif').'";');
      $this->add_JSLoadScript('admin_infobarengine_start('.$ka_duration.','.$ka_refresh.', "'.$ka_url.'");');
    } else {
      $this->add_JSLoadScript('admin_infobarengine_start(0, 0);');
    }

    /* menu javascript */
    $this->add_JSEngineFile('tool/htmlelement.js');
    $this->add_JSEngineFile('tool/clientenv.js');
    $this->add_JSEngineFile('object/cmenu.js');
    foreach ($this->barMenu as $name => $menu) {
      if (count($menu['content']) > 0) {
    /* register menu */
    $this->add_JSScript('var '.$name.'Menu = new CMenu("'.$name.'Menu", null, "'.$name.'Button", "bottom");');
    $this->add_JSScript('globalCMenu.registerMenu('.$name.'Menu);');
    /* update menu onmouseover script */
    $this->add_JSLoadScript('document.getElementById("_'.$name.'_").setAttribute("onmouseout", document.getElementById("_'.$name.'_").getAttribute("onmouseout")+";globalCMenu.unselect(\''.$name.'Menu\')");');
      }
    }

    /* add language menu */
    if (count($camyks->site_conf['admin_languages']) > 1) {
      $this->languageMenu = array('name' => 'languageMenu',
                  'title' => language_getIcon($camyks->current_language, true),
                  'content'=>array());
      foreach ($camyks->site_conf['admin_languages'] as $lg) {
    $this->languageMenu['content'][] = array('menu' => 'language', 
                         'name' => $lg, 
                         'title' => language_getTitle($lg),
                         'url' => $camyks->get_adminLink().'?_clg_='.$lg,
                         'icon'=>language_getIcon($lg, false));
      }
      /* register menu */
      $this->add_JSScript('var languageMenu = new CMenu("languageMenu", null, "languageButton", "bottom");');
      $this->add_JSScript('globalCMenu.registerMenu(languageMenu);');
      /* update menu onmouseover script */
      $this->add_JSLoadScript('document.getElementById("_language_").setAttribute("onmouseout", document.getElementById("_language_").getAttribute("onmouseout")+";globalCMenu.unselect(\'languageMenu\')");');
    }
    
    /* start javascript menu engine */
    $this->add_JSLoadScript('globalCMenu.init();', true);
    /* layout to display */
    $this->selected_layout = 'admin.html.inc';
  }

  /*
   * admin init when nobody is logged
   * @return void
   * @access private
   */
  function init_admin_nobodylogged () {
    $this->selected_layout = 'adminnobody.html.inc';
  }

  /*
   * register a menu
   * @param string $name
   * @param string $title
   * @return boolean success
   * @access private
   */
  function register_barMenu ($name, $title) {
    /* check values */
    if ($name == '' or $title == '' or isset($this->barMenu[$name]))
      return false;
    /* update menu */
    $this->barMenu[$name] = array('title'=>$title,
                  'content'=>array());
    return true;
  }

  /*
   * register an item into a menu
   * @param array $item
   * @return boolan success
   * @access private
   */
  function register_barMenuItem ($item) {
    /* check values */
    if ($item['menu'] == '' or $item['name'] == '' or $item['title'] == '' or (!isset ($this->barMenu[$item['menu']])))
      return false;

    /* item default values */
    if (!isset ($item['url']))
      $item['url'] = '';

    if (!isset($item['children']) or is_array($item['children']) === false) {
      $item['children'] = array();
    }

    /* update menu */
    $this->barMenu[$item['menu']]['content'][] = $item;
        
    return true;
  }

  /*
   * disable menu
   * @return void
   * @access public
   */
  function disable_adminMenus() {
    $this->menuDisabled = true;
  }
}
?>