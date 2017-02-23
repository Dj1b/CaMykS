<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version       : 1.01
 * Object Type          : Plugin / Module Engine
 * Create Date		: Apr 2007
 * Last Modif Date	: Jun 2008
 * History : 
 * * 07-04-xx : Initial File
 * * 07-12-19 : add a new "no box" layout
 * * 08-06-13 : Disable admin menu for data I/O modes
 * * 08-07-17 : Add attached file support
 * 
 * Content_SystemSiteReport module :
 * Display configurable site report form : reports are stored in Admin_SiteReport module
 */

class Content_SystemSiteReport extends Module {
  /* variables */
  var $titles_modes;
  var $layouts_list;
  var $rfitem;
  var $ritem;
  var $rtypelist;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_SystemSiteReport ( $path_type ) {
    parent::Module('Content_SystemSiteReport', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.01';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'SystemSiteReportForm.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->rfitem = new SystemSiteReportForm(0, $this);
    /* initialise plugin variables */
    $this->layouts_list = array('simple', 'box_normal');
    $this->title_modes = array(0=>'title_none',
			       1=>'title_text',
			       2=>'title_image',
			       3=>'title_localizedtext',
			       4=>'title_localizedimage');
  }

  /* overwrite Module methods */  

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->rfitem->install() )
      return parent::install();
    return false;
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    if ( $this->rfitem->uninstall() )
      return parent::uninstall();
    return false;
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->rfitem->is_installed();
  }

  /*
   * update module
   * @return boolean success
   * @access private
   */
  function update($version, $more='') {
    global $camyks;
    
    /* check version 1.01 */
    if ( version_compare( $this->version, $version ) === 1  )
      if ( $this->rfitem->update_toVersion1_01() === false )
	return false;

    /* generic update */
    return parent::update($version, $more);
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->rfitem->get_namelist();
  }
  
  /*
   * init objects when in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    /* page values */
    $this->page_id = isset ( $_REQUEST['page_id'] ) ? $_REQUEST['page_id'] : 0;
    $this->module_index = isset ( $_REQUEST['module_index'] ) ? $_REQUEST['module_index']: -1;
 
    /* check right for this page */
    if ( $this->check_right( $this->page_id ) === false ) {
      return $this->init_admin_pageAccessDenied();
    }
    
    /* get mode */
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'modify';

    switch ( $this->mode ) {
    case 'save' :
      /* mode == save */
      $this->init_admin_save();
      break;
    case 'modify' :
    default:
      /* mode == edit_list */
      $this->init_admin_edit();
      break;
    }
    /* generic module init */
    parent::init_admin();
  }
  
  /*
   * display object module in admin mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /*
   * init module object in site mode
   * @param integer $content
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;
    
    /* init object from content id */
    $this->rfitem->id = $content;
    /* get action to execute */
    $srfaction = isset ( $_REQUEST['srfaction'] ) ? $_REQUEST['srfaction'] : 'display';

    /* get init from action */
    switch ( $srfaction ) {
    case 'send':
      /* action == send */
      $this->init_site_send( );
      break;
    case 'display':
    default:
      /* action == display */
      $this->init_site_display( );
      break;
    }

    /* parent site init */
    parent::init_site();
  }

  /*
   * display module object in site mode
   * @return void
   * @access private
   */
  function display_site () {
    parent::display_site();
  }

  /* specific admin mode methods */

  /*
   * init object module in admin/save mode
   * @return void
   * @access private
   */
  function init_admin_save ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    $id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;

    /* save object */
    $this->rfitem->id = $id;
    $this->rfitem->get_fromHeader();
    $this->rfitem->save_toDatabase();

    /* update page information with object id for new content  */
    if ( $id == 0 and $this->page_id > 0 ) {
      ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->rfitem->id );
    }
    
    /* redirect save page */
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, array('mode'=>'modify', 
								       'id'=>$this->rfitem->id, 
								       'page_id'=>$this->page_id, 
								       'module_index'=>$this->module_index)));
    
    /* update layout */
    $this->text = $camyks->get_translation('savedone');
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * init object module in admin/edit mode
   * @return void
   * @access private
   */
  function init_admin_edit ( ) {
    global $camyks;

    if (!isset($camyks->modules['Admin_SiteReport']))
      return $this->init_adminMissingPlugin('Module', 'Admin_SiteReport');

    /* get object data  */
    $this->rfitem->id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;
    $this->rfitem->get();
    $this->rfitem->get_HTMLFiles();
    
    /* get tabs javascript engine */
    $this->openTab = isset ( $_REQUEST['openTab'] ) ? $_REQUEST['openTab'] : 'properties';
    $this->tabObject = 'sitereport_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();' );
    $this->add_JSScript($this->tabObject.'.init("properties", "'
			.$camyks->theme->parts['boxTabCSSStandart'].'","'
			.$camyks->theme->parts['boxTabCSSSelected'].'","'
			.$camyks->theme->parts['boxTabCSSRollover'].'");');
    if ( $this->openTab != 'properties' )
      $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');
    
    /* get type list */
    $this->rtypelist = $camyks->modules['Admin_SiteReport']->rtype->get_objectList();
    $this->config = &$camyks->modules['Admin_SiteReport']->config;
    $this->config->get();
    
    /* title mode selector */
    $this->add_JSEngineFile('object/cmdd.js');
    $this->add_JSScript('sitereport_modeObject = new Cmdd();');
    $this->add_JSScript('sitereport_modeObject.init("title_mode", "","","","");');
    $this->add_JSLoadScript('sitereport_modeObject.selectItem('.$this->rfitem->title_mode.');');
    
    /* get tiny_mce input */
    $this->input = $camyks->inputs['TinyMCE'];
    $this->input->set_configInfos ('file', $this->get_fileURL('js/tinymce_config.js'));
    $this->input->initialise();
    $this->input->load_themeCSSFile( $this->page_id );
    $this->input->load_pageChooser();
    
    /* get form object */
    $this->form = new HTMLForm('sitereport_form',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save')),
			       'POST');
    $this->form->allow_files ( true );
    $this->form->add_hidden('MAX_FILE_SIZE', 500000);
    $this->form->add_hidden('id', $this->rfitem->id );
    $this->form->add_hidden('type_count', count($this->rtypelist));
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );
    
    /* tab list for tabs list */
    $this->tabs = array(array('name'=>'properties',
			      'title'=>$this->get_translation('tabproperties')),
			array('name'=>'types',
			      'title'=>$this->get_translation('tabtypes')));
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->tabs[] = array('name'=>'desc'.$l,
			    'title'=>strtoupper( $l ));
    }
    if ( $this->help != null  ) {
      $this->tabs[] = array( 'name'=>'help',
			     'title'=>$camyks->get_translation('help'));
    }
    
    /* buttons list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify',
								       'page_id'=> $this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=> $this->form->get_HTMLSubmitLink())); 
  }
  
  /* specific site mode methods */

  /* 
   * init module object in site/display mode
   * @return void
   * @access private
   */
  function init_site_display (  ) {
    global $camyks;
    /* get object data */
    $this->rfitem->get();

    /* add page styles */
    $camyks->theme->get_editor_css();
    
    /* get type list */
    $t = &$camyks->modules['Admin_SiteReport']->rtype;    
    $this->rtypelist = $t->get_objectList($camyks->current_language,
					  'id in ('.implode(',', $this->rfitem->type_list).' )');
    
    /* get tiny_mce input */
    $this->input = $camyks->inputs['TinyMCE'];
    $this->input->set_configInfos ('simple');
    $this->input->initialise();
    $this->input->set_contentInfos ('text', '' );
    $this->input->set_textareaInfos ('content', '100%', '200px');
    /* get form object */
    $this->form = new HTMLForm('sitereport_form',
			       $camyks->get_siteCurrentlink( ),
			       'POST');
    $this->form->add_hidden('srfaction', 'send' );
    $this->form->add_hidden('language', $camyks->current_language);
    $this->form->add_hidden('link', isset ( $_REQUEST['srflink'] ) ? $_REQUEST['srflink'] : '' );

    /* get config */
    if ( isset($camyks->modules['Admin_SiteReport'])) {
      $this->config = &$camyks->modules['Admin_SiteReport']->config;
      $this->config->get();
      $this->file_allowed = $this->config->vars['file_allowed'];
      $this->file_maxsize = $this->config->vars['file_maxsize'].'K'.language_getFileUnit();
      $this->form->allow_files(true, $this->config->vars['file_maxsize']*1024);
    } else {
      $this->file_allowed = false;
    }

    /* anti-reload && post flood control */
    $camyks->set_sessionValue('sitereportpost',0);

    /* update layout */
    $this->selected_layout = 'site_'.$this->rfitem->layout_name.'.html.inc';
  }

  /*
   * init module object in site/send mode
   * @return void
   * @access private
   */
  function init_site_send ( ) {
    global $camyks;

    /* check anti-reload && post flood */
    if ($camyks->get_sessionValue('sitereportpost', 1)==1 )
      return $this->init_site_display();

    /* update reload action session value */
    $camyks->set_sessionValue('sitereportpost', 1);


    /* get object data */
    $this->rfitem->get();

    /* get item */
    $this->ritem = &$camyks->modules['Admin_SiteReport']->ritem;
    $this->ritem->id = 0;
    $this->ritem->get_fromheader();
    $this->ritem->save();

    /* update layout */
    $this->selected_layout = 'site_'.$this->rfitem->layout_name.'_send.html.inc';
  }
}
?>