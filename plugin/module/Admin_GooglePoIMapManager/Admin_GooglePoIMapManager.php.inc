<?php
/*
 * CaMykS Engine
 * Developed by	    : Ideogram Design
 * Author	    : JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Jun 2010
 * Last Modif Date  : Jun 2010
 * History :
 * * 10-06-09 : Initial files
 * 
 * Admin_GooglePoIMapManager
 */

class Admin_GooglePoIMapManager extends Module {
  /* variables */
  var $pointItem;
  var $pointList;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GooglePoIMapManager ( $path_type ) {
    parent::Module('Admin_GooglePoIMapManager', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Google';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load plugin libraries */
    $this->libs[] = 'Admin_GooglePoIMapManagerPoint.php.inc';
    $this->libs[] = 'Admin_GooglePoIMapManagerCategory.php.inc';
    $this->libs[] = 'Admin_GooglePoIMapManagerIcon.php.inc';
    $this->libs[] = 'Admin_GooglePoIMapManagerConfig.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->pointItem = new Admin_GooglePoIMapManagerPoint(0, $this);
    $this->categoryItem = new Admin_GooglePoIMapManagerCategory(0, $this);
    $this->iconItem = new Admin_GooglePoIMapManagerIcon(0, $this);
    $this->config = new Admin_GooglePoIMapManagerConfig('config', $this);

    /* initialise plugin variables */
    $this->pointList = null;
    $this->catList = null;    
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->pointItem->install() and $this->categoryItem->install()
	    and $this->iconItem->install()
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
    return $this->iconItem->is_installed();
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
			     'default'=> false);
    $this->rights[1] = array('name'=>'edit_point',
			     'title'=> $camyks->get_translation('right_editpoint'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'edit_data',
			     'title'=> $this->get_translation('right_editdata'),
			     'default'=> false);
    $this->rights[3] = array('name'=>'edit_config',
			     'title'=> $this->get_translation('right_editconfig'),
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
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();

    /* check dependencies */
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    if (!isset($camyks->inputs['AdminItemListViewer']))
      return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

    /* get informations */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'main' );
    
    switch ( $this->mode ) {
    case 'edit_point':
      /* mode == edit_point */
      $this->init_admin_edit_point();
      break;
    case 'save_point':
      /* mode == save_point */
      $this->init_admin_save_point();
      break;
    case 'delete_point':
      /* mode == delete_point */
      $this->init_admin_delete_point();
      break;
    case 'edit_cat':
      /* mode == edit_cat */
      $this->init_admin_edit_category();
      break;
    case 'save_cat':
      /* mode == save_cat */
      $this->init_admin_save_category();
      break;
    case 'delete_cat':
      /* mode == delete_cat */
      $this->init_admin_delete_category();
      break;
    case 'edit_icon':
      /* mode == edit_icon */
      $this->init_admin_edit_icon();
      break;
    case 'save_icon':
      /* mode == save_icon */
      $this->init_admin_save_icon();
      break;
    case 'delete_icon':
      /* mode == delete_icon */
      $this->init_admin_delete_icon();
      break;
    case 'edit_config':
      /* mode == edit_config */
      $this->init_admin_edit_config();
      break;
    case 'save_config':
      /* mode == save_config */
      $this->init_admin_save_config();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
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

  /*
   * execute module object in request mode
   * @return void
   * @access private
   */

  /* specific admin mode methods */

  /*
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  function init_admin_main() {
    global $camyks;
    
    /* get help */
    $this->get_help();

    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();
    countries_loadLocales();

    /* build point tab data */
    $this->load_file('lib/Admin_GooglePoIMapManagerPointListParams.php.inc');
    $this->pointList = &$camyks->inputs['AdminItemListViewer'];
    $this->pointList->set_params($this->pointListParams);
    $this->pointList->initialise();
    
    /* build category tab data */
    $this->load_file('lib/Admin_GooglePoIMapManagerCategoryListParams.php.inc');
    $this->catList = new AdminItemListViewer('camyks');
    $this->catList->set_params($this->catListParams);
    $this->catList->initialise();
    
    $catIDs = array_keys($this->catList->objectList);
    $cnts = $this->pointItem->get_pointCountByCategories($catIDs);
    foreach( $this->catList->objectList as $id => $cat)
        $this->catList->objectList[$id]->vars['points'] = isset($cnts[$id])?$cnts[$id]:0;

    /* build icon tab data */
    $this->load_file('lib/Admin_GooglePoIMapManagerIconListParams.php.inc');
    $this->iconList = new AdminItemListViewer('camyks');
    $this->iconList->set_params($this->iconListParams);
    $this->iconList->initialise();
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(array('name'=>'points',
					    'title'=>$this->get_translation('tabpoints')),
				      array('name'=>'categories',
					    'title'=>$this->get_translation('tabcategories')),
				      array('name'=>'icons',
					    'title'=>$this->get_translation('tabicons'))));
    
    /* check for config tab */
    if ( $this->check_right(3) == true) {
      $this->config->get();
      $this->tabBuilder->add_tab(array('name'=>'config',
				       'title'=>$this->get_translation('tabconfig')));
    }

    /* check for help tab */
    if ( $this->help != null )
      $this->tabBuilder->add_tab(array('name'=>'help',
				       'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'points'));
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }

  /*
   * init module object in admin/edit_point mode
   * @return void
   * @access private
   */
  function init_admin_edit_point() {
    global $camyks;
    
    /* check edit point rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* load config */
    $this->config->get();

    /* get edition language list */
    $this->elg = $camyks->get_confValue('editing_languages');
    
    /* get point item */
    $point_id = isset($_REQUEST['point_id'])?$_REQUEST['point_id']:0;
    $this->pointItem->id = $point_id;
    $this->pointItem->get();
    $this->pointItem->get_fromItems();
    
    /* get form */
    $this->editform = new HTMLForm('edit_point',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_point')),
				   'POST');
    $this->editform->add_hidden('point_id', $this->pointItem->id );
    $this->editform->set_object($this->pointItem);
    
    /* add google map */
    $this->add_JSExternFile('http://maps.google.com/maps?file=api&v=2&key='.$this->config->vars['google_mapapikey'].'&sensor=false');
    $this->add_JSFile('pointeditor.js');
    $this->add_JSScript('var pe = new PointEditor("pe");');
    $this->add_JSLoadScript('pe.initialise("'.$this->editform->name.'");');
    $this->add_JSUnloadScript('GUnload();');
  
    /* add javascript params */
    $this->add_JSScript('pe.set_param("GMapDefZoom", 14);');
    
    $p = '{title:"'.addslashes($this->pointItem->vars['title']).'"';
    if ( $this->pointItem->vars['latitude'] == '' or $this->pointItem->vars['longitude'] == '' ) {
      $p .= ', address:"'.$this->pointItem->vars['address1'].' ';
      $p .= $this->pointItem->vars['address2'].' ';
      $p .= $this->pointItem->vars['address3'].'"';
    } else {
      $p .= ', lat:"'.$this->pointItem->vars['latitude'].'"';
      $p .= ', lng:"'.$this->pointItem->vars['longitude'].'"';
    }
    $p.= '}';
    $this->add_JSScript('pe.set_param("Point", '.$p.');');

    /* add javascript locales */
    $this->add_JSScript('pe.add_locale("address_undefined", "'.string_html2text($this->get_translation('js_address_undefined')).'");');
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(array('name'=>'properties',
					    'title'=>$this->get_translation('tabproperties'))));
    if (count($this->elg) > 1)  
      foreach ($this->elg as $l )
	$this->tabBuilder->add_tab(array('name'=>$l,
					 'title'=>language_getIcon($l)));
    else
      $this->tabBuilder->add_tab(array('name'=>$this->elg[0],
				       'title'=>$this->get_translation('tabcontent')));
    $this->tabBuilder->initialise();
    
    /* get editor input */
    $this->input = &$camyks->inputs['TinyMCEv3'];
    $this->input->initialise();
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->pointItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('pointnew');
    else
      $this->adminTitle .= $this->get_translation('pointid', $this->pointItem->id);
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink($this->name),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_point.html.inc';
  }
  
  /* 
   * init module object in admin/save_point mode
   * @return void
   * @access private
   */
  function init_admin_save_point() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save object */
    $this->pointItem->id = isset($_REQUEST['point_id'])?$_REQUEST['point_id']:0;
    $this->pointItem->get_fromHeader();
    if ( $this->pointItem->save() ) {
      $this->text = $this->get_translation('point_saved');
    } else {
      $this->text = $this->get_translation('point_notsaved');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name) );
  }
  
  /* 
   * init module object in admin/delete_point mode
   * @return void
   * @access private
   */
  function init_admin_delete_point() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();
      
    /* check point id */
    if (!isset($_REQUEST['point_id']))
    	return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get object */
    $this->pointItem->id = $_REQUEST['point_id'];
    /* delete object */
    if ( $this->pointItem->delete() ) {
      $this->text = $this->get_translation('point_deleted');
     } else {
      $this->text = $this->get_translation('point_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name) );
  }
  
  /*
   * init module object in admin/edit_cat mode
   * @return void
   * @access private
   */
  function init_admin_edit_category() {
    global $camyks;
    
    /* check edit category rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
        
    /* get category item */
    $this->categoryItem->id = isset($_REQUEST['cat_id'])?$_REQUEST['cat_id']:0;
    $this->categoryItem->get();
    $this->categoryItem->get_fromItems();
    
    /* get form */
    $this->editform = new HTMLForm('edit_cat',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_cat')),
				   'POST');
    $this->editform->add_hidden('cat_id', $this->categoryItem->id );
    $this->editform->set_object($this->categoryItem);
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->categoryItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('catnew');
    else
      $this->adminTitle .= $this->get_translation('catid', $this->categoryItem->id);
     
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('openTab'=>'categories')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_category.html.inc';
  }
  
  /* 
   * init module object in admin/save_cat mode
   * @return void
   * @access private
   */
  function init_admin_save_category() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save object */
    $this->categoryItem->id = isset($_REQUEST['cat_id'])?$_REQUEST['cat_id']:0;
    $this->categoryItem->get_fromHeader();
    if ( $this->categoryItem->save() ) {
       $this->text = $this->get_translation('cat_saved');
    } else {
      $this->text = $this->get_translation('cat_notsaved');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('openTab'=>'categories')));
  }
  
  /* 
   * init module object in admin/delete_cat mode
   * @return void
   * @access private
   */
  function init_admin_delete_category() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
      
    /* check cat id */
    if (!isset($_REQUEST['cat_id']))
    	return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get object */
    $this->categoryItem->id = $_REQUEST['cat_id'];
    /* delete object */
    if ( $this->categoryItem->delete() ) {
      $this->text = $this->get_translation('cat_deleted');
     } else {
      $this->text = $this->get_translation('cat_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('openTab'=>'categories')));
  }
  
  /*
   * init module object in admin/edit_icon mode
   * @return void
   * @access private
   */
  function init_admin_edit_icon() {
    global $camyks;
    
    /* check edit category rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
        
    /* get category item */
    $this->iconItem->id = isset($_REQUEST['icon_id'])?$_REQUEST['icon_id']:0;
    $this->iconItem->get();
    $this->iconItem->get_fromItems();
    
    /* get form */
    $this->editform = new HTMLForm('edit_icon',
				   $this->get_adminlink(array('mode'=>'save_icon')),
				   'POST');
    $this->editform->allow_files(true, 512*1024);
    $this->editform->add_hidden('icon_id', $this->iconItem->id );
    $this->editform->set_object($this->iconItem);
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->iconItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('iconnew');
    else
      $this->adminTitle .= $this->get_translation('iconid', $this->iconItem->id);
     
    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('openTab'=>'icons')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_icon.html.inc';
  }
  
  /* 
   * init module object in admin/save_icon mode
   * @return void
   * @access private
   */
  function init_admin_save_icon() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save object */
    $this->iconItem->id = isset($_REQUEST['icon_id'])?$_REQUEST['icon_id']:0;
    $this->iconItem->get_fromHeader();
    if ( $this->iconItem->save() ) {
       $this->text = $this->get_translation('icon_saved');
    } else {
      $this->text = $this->get_translation('icon_notsaved');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('openTab'=>'icons')));
  }
  
  /* 
   * init module object in admin/delete_icon mode
   * @return void
   * @access private
   */
  function init_admin_delete_icon() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
      
    /* check icon id */
    if (!isset($_REQUEST['icon_id']))
    	return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* get object */
    $this->iconItem->id = $_REQUEST['icon_id'];
    /* delete object */
    if ( $this->iconItem->delete() ) {
      $this->text = $this->get_translation('icon_deleted');
     } else {
      $this->text = $this->get_translation('icon_notdeleted');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('openTab'=>'icons')));
  }

  /*
   * init module object in admin/edit_config mode
   * @return void
   * @access private
   */
  function init_admin_edit_config() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed();

    /* load config */
    $this->config->get();
    
    /* get configuration form */
    $this->configform = new HTMLForm('configform',
				     $this->get_adminLink(array('mode' => 'save_config')),
				     'POST');
    $this->configform->set_object($this->config);

    /* build window title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('configuration');
         
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
  function init_admin_save_config() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* save config */
    $this->config->get_fromHeader();
    if ( $this->config->save() ) {
      $this->text = $this->get_translation('config_saved');
    } else {
      $this->text = $this->get_translation('config_notsaved');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }

  /* specific admin tool methods */

  /*
   * return point status list
   * @return array
   * @access private
   */
  function get_pointStatusList() {
    return $this->pointItem->get_statusList();
  }

  /*
   * return points status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_pointsStatusList($full=false) {
    return $this->pointItem->get_multiStatusList($full);
  }
  
  /*
   * return point country list
   * @param array $params
   * @return array
   * @access public
   */
  function get_pointCountryList($params=array()) {
    return $this->pointItem->get_countryList($params);
  }
  
  /*
   * return point list from given params
   * @param array $params
   * @return array
   * @access public
   */
  function get_pointList($params=array()) {
    return $this->pointItem->get_list($params);
  }

  /*
   * return category status list
   * @return array
   * @access private
   */
  function get_categoryStatusList() {
    return $this->categoryItem->get_statusList();
  }

  /*
   * return categories status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_categoriesStatusList($full=false) {
    return $this->categoryItem->get_multiStatusList($full);
  }
  
  /*
   * return category title list
   * @param array $params
   * @return array
   * @access public
   */
  function get_categoryTitleList($params=array()) {
    if (!isset($params['language']) or $params['language'] == '')
      $params['language'] = $this->get_adminEditionLanguage();      
    return $this->categoryItem->get_titleList($params);
  }
  
  /*
   * return icon name list
   * @param array $params
   * @return array
   * @access public
   */
  function get_iconNameList($params=array()) {
    return $this->iconItem->get_objectNameList($params);
  }

  /*
   * return icon list from given params
   * @param array $params
   * @return array
   * @access public
   */
  function get_iconList($params=array()) {
    return $this->iconItem->get_list($params);
  }
}
?>