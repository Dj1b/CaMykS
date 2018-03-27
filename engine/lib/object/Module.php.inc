<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Engine / Object Library
 * Creation Date    : Jun 2005
 * Last Modif Date  : Mar 2018
 *
 * CaMykS engine Module object
 *
 * TO DO :
 * - error management
 */

class Module extends Plugin {
  /* variables */

  /* module type */
  var $type;
  /* php libs needed for current module */
  var $libs;
  /* check if init is done */
  var $init_done;
  /* style files used by module */
  var $style_files;
  /* style scripts used by module */
  var $style_scripts;
  /* style included files used by module */
  var $style_included_files;
  /* javascript module files to import */
  var $js_files;
  /* javascript engine files to import */
  var $js_extfiles;
  /* javascripts codes to write before file importation */
  var $js_pre_scripts;
  /* javascripts codes to write after file importation */
  var $js_scripts;
  /* javascripts codes to write in body "onload" value */
  var $js_load_scripts;
  /* selected layout */
  var $selected_layout;
  var $selected_layout_location;
  /* used theme */
  var $theme;
  /* available languages */
  var $languages;
  /* rights */
  var $rights;
  /* content */
  var $content;
  /* content id list */
  var $contentList;
  /* help */
  var $help;
  /* libdesc */
  var $libdesc;
  /* has editable content */
  var $is_editable;

  /*
   * constructor
   * @param string $name the module name
   * @param string $path_type the module path ( camyks or site )
   * @access public
   */
  function Module ( $name, $path_type ) {
    global $camyks;
    parent::Plugin( $name, 'module', $path_type );
    $this->libs = array();
    $this->init_done = false;
    /* styles */
    $this->style_files = array();
    $this->style_scripts = array();
    $this->style_included_files = array();
    /* javascripts */
    $this->js_externfiles = array(); /* extern script files */
    $this->js_enginefiles = array(); /* engine script files */
    $this->js_files = array(); /* module script files */
    $this->js_pre_scripts = array();
    $this->js_scripts = array();
    $this->js_load_scripts = array();

    /* available rights for the module */
    $this->rights = array();

    /* load language : needed to have title & description */
    $this->add_translation ();

    /* get localized title from translation file */
    $this->title = $this->get_translation('title');

    /* set help value by default */
    $this->help = null;

    /* set libdesc value by default */
    $this->libdesc = 'Module:'.$this->name;

    /* has editable content value */
    $this->is_editable = true;

    /* set layout to null */
    $this->selected_layout = '';
    $this->selected_layout_location = 'module';
  }

  /* methods */

  /*
   * initialise object
   * @return void
   * @access public
   */
  function init () {
    if ( $this->init_done ) {
      return;
    }
    $this->init_done = true;
  }

  /***************** TESTS ******************/
  /*
   * return if module is active
   * @return boolean
   * @access public
   */
  function is_active ( ) {
    return $this->active;
  }

  /*
   * return if module is correctly installed
   * @return boolean
   * @access public
   */
  function is_installed ( ) {
    return null;
  }

  /***************** INFO REQUEST ***********/

  /*
   * return version value
   * @return string
   * @access public
   */
  function get_version ( ) {
    return $version;
  }

  /***************** MODULE SUB ENGINE *********/

  /*
   * load PHP libraries
   * @return void
   * @access public
   */
  function get_PHPLibs ( ) {
    foreach ( $this->libs as $lib ) {
      $file = $this->plugin_path .'/lib/' . $lib;
      if ( file_exists ( $file ) ) {
	require_once( $file );
      } else {
	/* TO DO */
	/* send an error to a global object : file not found */
      }
    }
  }

  /*
   * return availables languages for the module
   * @return void
   * @access public
   */
  function get_languages ( ) {
    global $camyks;
    $path = $this->plugin_path.'/locale';
    $this->languages = array();
    $locales_files = folder_listFiles ( $path );
    foreach ( $locales_files as $f ) {
      if ( substr ( $f, 0, 12 ) == 'translation_'
	   and substr ( $f , strlen ( $f ) - strlen ( $camyks->file_extension ), strlen ( $camyks->file_extension ) ) == $camyks->file_extension ) {
	$this->languages[] = substr ( $f, 12, strlen ( $f ) - 12 - strlen ( $camyks->file_extension ) );
      }
    }
  }

  /***************** HELP **********************/
  /*
   * get help files
   * @return void
   * @access public
   */
  function get_help ( ) {
    global $camyks;
    /* check if help files exists */
    $hfile = 'help/'.$camyks->current_language.'/help.php.inc';
    $this->load_file( $hfile );
    if ( isset( $this->help ) ) {
      /* update help with default main page */
      array_unshift( $this->help, array('title'=>$camyks->get_translation('module_generic_help'),
					'html'=>'help_module_generic.html.inc',
					'location'=>'camyks'));
      /* add javascripts for help engine */
      $this->add_JSEngineFile ( 'object/cmdd.js');
      $this->add_JSScript( strtolower($this->name).'_helpObject = new Cmdd();' );
      $this->add_JSScript( strtolower($this->name).'_helpObject.init("'.$this->name.
	'", "","'.$camyks->theme->parts['boxTabCSSStandart'].
	'","'.$camyks->theme->parts['boxTabCSSSelected'].
	'","'.$camyks->theme->parts['boxTabCSSRollover'].'");');

      /* open first element */
      foreach ( $this->help as $i => $v ) {
	$this->add_JSLoadScript( strtolower($this->name).'_helpObject.mouseclick(\''.$i.'\');');
	break;
      }
    }
  }

  /*
   * display help files
   * @return void
   * @access public
   */
  function display_help ( ) {
    global $camyks;
    $this->load_engineFile('data/html/help.html.inc');
  }

  /***************** ADD INFOS TO MAIN PAGE *******************/

  /*
   * set module applied theme
   * @param string $theme the theme name
   * @return void
   * @access public
   */
  function set_theme ( $theme ) {
    global $camyks;
    if ( isset ( $camyks->themes[$theme] ) ) {
      $this->theme = &$camyks->themes[$theme];
    } else {
      $this->theme = &$camyks->themes[$camyks->_conf['site_default_theme']];
    }
    $this->theme->get_parts( );
  }

  /***************** LANGUAGE & LOCALES METHODS ****************/

  /*
   * load language dictionnary file
   * @param string $more
   * @param strinh $lg
   * @return void
   * @access public
   */
  function add_translation($more='', $lg=null) {
    global $camyks;
    $camyks->add_translation($this->plugin_path.'/locale'.$more, $lg);
  }

  /*
   * get locale value
   * @param string $value the locale value to return
   * @param mxed $data the optional inserted data
   * @return string
   * @access public
   */
  function get_translation ( $value, $data=null ) {
    global $camyks;
    return $camyks->get_translation('mod_'.strtolower($this->name).'_'.$value, $data);
  }

  /*
   * return language to use for admin content edition
   * @return string
   * @access private
   */
  function get_adminEditionLanguage() {
    global $camyks;

    if ( ($l =  $camyks->get_confValue('editing_default_language')) != false )
      return $l;
    $elgs =  $camyks->get_confValue('editing_languages');
    if ( in_array($camyks->current_language, $elgs) )
      return $camyks->current_language;
    else
      return $elgs[0];
  }

  /***************** CONTENT METHODS *************************/

  /*
   * if module has editable content, return content list as structured array $id=>$name/title
   * if module has no editable content, return -1
   * @return mixed
   * @acess public
   */
  function get_contentList ( ) {
    return -1;
  }

  /***************** ADMIN METHODS **************************/

  /*
   * pre-init module object in admin mode
   * @return void
   * @access public
   */
  function preInit_admin() {
    if ($this->type == 'content') {
      /* page values */
      $this->id = isset($_REQUEST['id']) ? $_REQUEST['id'] : 0;
      $this->page_id = isset ( $_REQUEST['page_id'] ) ? $_REQUEST['page_id'] : 0;
      $this->module_index = isset ( $_REQUEST['module_index'] ) ? $_REQUEST['module_index']: -1;
    } elseif ($this->type == 'admin' ) {

    }
  }


  /*
   * init module object in admin mode
   * @return void
   * @access public
   */
  function init_admin () {
    /* generic init */
    $this->init_generic();
    /* set admin layout by default */
    if ( $this->selected_layout == '' ) {
      $this->selected_layout = 'admin.html.inc';
    }
  }

  /*
   * display module object in admin mode
   */
  function display_admin () {
    $this->get_adminLayout();
  }

  /* init parent only */
  function init_parent_admin ( ) {
    Module::init_admin();
  }

  /*
   * init module object in admin/access denied mode
   * @return void
   * @access public
   */
  function init_admin_accessDenied ( ) {
    global $camyks;
    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* redirect to home */
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink());
    $this->text = $camyks->get_translation ('module_access_denied');
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * init module object in admin/page access denied mode
   * @return void
   * @access public
   */
  function init_admin_pageAccessDenied ( ) {
    global $camyks;
    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* redirect to page tree ( or to home ) */
    if ( isset($camyks->modules['Admin_ContentPage']))
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink('Admin_ContentPage'));
    else
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink());
    $this->text = $camyks->get_translation ('module_page_access_denied');
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * init module object in admin/action not allowed mode
   * @return void
   * @access public
   */
  function init_admin_actionNotAllowed ( ) {
    global $camyks;
    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* redirect to module home or admin home */
    if ( $this->check_right(0) )
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
    else
      $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink( ));
    $this->text = $camyks->get_translation ('module_action_not_allowed');
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * init module object in admin/missing plugin mode
   * @return void
   * @access public
   */
  function init_admin_missingPlugin ( $type, $name ) {
    global $camyks;

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* redirect to admin home */
    $type = $camyks->get_translation ( $type );
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink( ));
    $this->text = $camyks->get_translation('module_plugin_missing', array($type, $name) );
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * return admin link
   * @param array $params
   * @param string $module
   * @return string
   * @access private
   */
  function get_adminLink($params=array(), $module=null) {
    global $camyks;

    /* check module value */
    if (isset($module)) {

    } elseif (isset($params['module'])) {
      $module = $params['module'];
      unset($params['module']);
    } else {
      $module = $this->name;
    }

    /* check module */
    if (!isset($camyks->modules[$module]))
      return '';
    else
      $type = $camyks->modules[$module]->type;

    /* add content module params */
    if ($type == 'content') {
      $tparams = array('id'=>$this->id,
		       'page_id'=>$this->page_id,
		       'module_index'=>$this->module_index);
      $params = array_merge($tparams, $params);
    }
    return $camyks->get_adminLink($module, $params);
  }

  /*
   * return admin js link
   * @param array $params
   * @param string $module
   * @return string
   * @access private
   */
  function get_adminJSLink($params=array(), $module=null) {
    global $camyks;

    /* check module value */
    if(isset($module)) {

    } elseif (isset($params['module'])) {
      $module = $params['module'];
      unset($params['module']);
    } else {
      $module = $this->name;
    }

    /* check module */
    if (!isset($camyks->modules[$module]))
      return '';
    else
      $type = $camyks->modules[$module]->type;

    /* add content module params */
    if ($type == 'content') {
      $tparams = array('id'=>$this->id,
		       'page_id'=>$this->page_id,
		       'module_index'=>$this->module_index);
      $params = array_merge($tparams, $params);
    }
    return $camyks->get_adminJSLink($module, $params);
  }

  /***************** SITE METHODS ************************/

  /*
   * init module object in site mode
   * @return void
   * @access public
   */
  function init_site ( $content=1, $params=array(), $index=null ) {
    /* generic init */
    $this->init_generic();
    /* set site layout by default */
    if ( $this->selected_layout == '' ) {
      $this->selected_layout = 'site.html.inc';
    }
  }

  /*
   * display module in site mode
   * @return void
   * @access public
   */
  function display_site () {
    $this->get_siteLayout();
  }

  /***************** REQUEST METHODS ************************/

  /*
   * execute module in request mode
   * @return void
   * @access public
   */
  function execute_request () {
    echo 'This plugin doesn\'t support requests.';
  }

  /***************** GENERIC METHODS *********************/

  /*
   * generic module initialisation
   * @return boolean
   * @access public
   */
  function init_generic() {
    return true;
  }

  /***************** LAYOUT MANAGEMENT **************/

  /*
   * update selected layout
   * @param string $layout
   * @param string $location
   * @access public
   */
  public function set_selectedLayout($layout='', $location='') {
    $this->selected_layout = $layout;
    if ($location != '')
      $this->selected_layout_location = $location;
  }

  /*
   * load selected admin layout
   * @param string $layout the selected layout
   * @return void
   * @access public
   */
  function get_adminLayout ($layout='') {
    if ($layout != '') {
      $this->load_file('html/'.$layout);
    } else if ($this->selected_layout != '') {
      if ($this->selected_layout_location == 'camyks')
		$this->load_engineFile('data/html/'.$this->selected_layout);
      else
		$this->load_file('html/'.$this->selected_layout);
    } else {
      $this->load_file('html/admin.html.inc');
    }
  }

  /*
   * load selected site layout
   * @return void
   * @access public
   */
  function get_siteLayout ( ) {
    if ( $this->selected_layout != '' ) {
      if ( $this->selected_layout_location == 'camyks' )
	    $this->load_engineFile( 'data/html/'.$this->selected_layout );
      else
	    $this->load_file( 'html/'.$this->selected_layout );
    } else {
      $this->load_file( 'html/site.html.inc' );
    }
  }

  /**************** ADMIN ENGINE MANAGEMENT *********/
  /*
   * return admin menus to register : always display
   * @return array
   * @access private
   */
  function get_adminEngineGenericMenus ( ) {
    return array();
  }

  /* return admin menu items to register : always display
   * @return array
   * @access private
   */
  function get_adminEngineGenericMenuItems ( ) {
    return array();
  }

  /*
   * return admin menus to register : display only when module is selected
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenus ( ) {
    return array();
  }

  /*
   * return admin menu items to register : display only when module is selected
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenuItems ( ) {
    return array();
  }

  /*
   * allow module to add specific data to admin page
   * @return boolean
   * @access private
   */
  function get_adminEngineGenericInit() {
    return true;
  }

  /*
   * allow module to add specific content to admin page
   * @return string
   * @access private
   */
  function get_adminEngineGenericDisplay() {
    return '';
  }

  /*
   * return notified items for module
   * @return Array
   * @access public
   */
  function get_adminInternalNotifications() {
    return array();
  }

  /**************** MODULE SPECIFIC METHODS ***********/

  /*
   * tell admin Tool_InfoBar to disable menus
   * @return void
   * @access public
   */
  function disable_adminEngineMenus() {
    global $camyks;
    if (isset($camyks->modules['Tool_InfoBar']))
      $camyks->modules['Tool_InfoBar']->disable_adminMenus();
  }


  /**************** MODULE SPECIFIC CALLBACKS ***********/

  /*
   * get action to execute in control panel
   * @return boolean
   * @access public
   */
  function get_adminControlPanelAction ( ) {
    return true;
  }

  /*
   * get object titles in statistics engine
   * @param array $list the id list to get
   * @param string $object the object
   * @return array
   * @access public
   */
  function get_adminStatisticsValueTitles ( $list, $object=null ) {
    return $list;
  }

  /*
   * get object specific options in statistics engine
   * @param string $object
   * @return string
   * @access public
   */
  function get_adminStatisticsSpecificOptions($object=null) {
    return '';
  }

  /***************** RIGHTS METHODS ***************/

  /*
   * modify right list
   * @return void
   * @access public
   */
  function get_rights( ) {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> false);
    $this->rights[1] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('write'),
			      'default'=> false);
  }

  /*
   * return right value for this module/mode
   * @return boolean
   * @access public
   */
  function check_right ( $info ) {
    global $camyks;
    switch ( $this->type ) {
    case 'admin':
      /* check admin user rights for this admin module */
      if ($camyks->adminUser!==false)
        return $camyks->adminUser->get_right($this->name, $info);
      return false;
    case 'content':
      /* check admin user right for the current page */
      if (isset($camyks->modules['Admin_ContentPage']) and $camyks->modules['Admin_ContentPage']->check_right(2)){
	$page = $camyks->modules['Admin_ContentPage']->page;
	$page->id = $info;
	$page->get();
	return $page->check_rights();
      }
      return false;
    case 'tool':
    default:
      return true;
    }
  }

  /***************** UTIL METHODS ******************/

  /*
   * return default buttons definition for html form file input
   * @param array $buttons
   * @param boolean $delete add view button to buttons list
   * @return array
   * @access public
   */
  function get_fileInputButtons( $buttons=array(), $delete=true) {
    global $camyks;

    if (is_array($buttons))
      $buttons = array_merge(array('view'=>true, 'listen'=>true, 'delete'=>true), $buttons);
    else
      $buttons = array('view'=>$buttons, 'delete'=>$delete, 'listen'=>$buttons);

    $list = array();
    if ( $buttons['view']===true )
      $list['view']=array('std'=>$this->theme->get_pictURL('view', 12, 'std'),
			  'ovr'=>$this->theme->get_pictURL('view', 12, 'ovr'),
			  'title'=>$camyks->get_translation('display'));
	if ( $buttons['listen']===true )
      $list['listen']=array('std'=>$this->theme->get_pictURL('right', 12, 'std'),
			    'ovr'=>$this->theme->get_pictURL('right', 12, 'ovr'),
			    'title'=>$camyks->get_translation('listen'));
    if ( $buttons['delete']===true )
      $list['delete']=array('std'=>$this->theme->get_pictURL('cross', 12, 'std'),
			    'ovr'=>$this->theme->get_pictURL('cross', 12, 'ovr'),
			    'title'=>$camyks->get_translation('delete'));
    return $list;
  }

  /*
   * return default buttons definition for html from date input
   * @param boolean $update add update button to button list
   * @param boolean $reset add reset button to button list
   * @return array
   * @access public
   */
  function get_dateInputButtons( $update=true, $reset=true ) {
    global $camyks;

    $list = array();
    if ( $update===true )
      $list['update']=array('std'=>$this->theme->get_pictURL('target', 12, 'std'),
			    'ovr'=>$this->theme->get_pictURL('target', 12, 'ovr'),
			    'title'=>$camyks->get_translation('update'));
    if( $reset===true )
      $list['reset']=array('std'=>$this->theme->get_pictURL('cross', 12, 'std'),
			   'ovr'=>$this->theme->get_pictURL('cross', 12, 'ovr'),
			   'title'=>$camyks->get_translation('reset'));
    return $list;
  }

  /*************** PAGE MANAGER RELATED METHODS *****/


  /*
   * set module object, with current settings in given page slot
   * @param integer $pageId
   * @param integer $moduleIndex
   * @param integer $contentId
   * @return boolean result
   * @access private
   */
  function add_moduleContentToPage( $pageId, $moduleIndex, $contentId) {
    global $camyks;

    /* check module type */
    if ( $this->type != 'content')
      return false;

    /* check page manager module */
    if (!isset($camyks->modules['Admin_ContentPage']))
      return false;

    /* update page information with object id for new content */
	return $camyks->modules['Admin_ContentPage']->page->static_update_singleModuleContent( $pageId, $moduleIndex, $contentId );
  }
}
?>
