<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 * History
 * * 08-07-08 : Initial files
 * * 08-07-22 : Add support of TinyMCE version 3
 *
 * Content_GoogleMapsViewer module :
 * Display Google Maps item
 */

class Content_GoogleMapsViewer extends Module {
  /* variables */
  var $mapItem;
  var $mapList;
  
  /*
   * Constructor.
   * @param string $path_type
   */
  function Content_GoogleMapsViewer ( $path_type ) {
    parent::Module('Content_GoogleMapsViewer', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Google';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'Content_GoogleMapsViewerItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->mapItem = new Content_GoogleMapsViewerItem(0, $this);
    /* initialise plugin variabbles */
    $this->mapList = array();
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->mapItem->install() )
      return parent::install();
    return false;
  }

  /*
   * uninstall module
   * @return boolean success
   * @access private
   */  
  function uninstall ( ) {
    return $this->mapItem->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->mapItem->is_installed();
  }
  
  /*
   * get available content ids as list
   * @return array
   * @access private
   */
  function get_contentList ( ) {
    return $this->mapItem->get_namelist();
  }
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    /* get page values */
    $this->page_id = isset ( $_REQUEST['page_id'] ) ? $_REQUEST['page_id'] : 0;
    $this->module_index = isset ( $_REQUEST['module_index'] ) ? $_REQUEST['module_index']: -1;
    
    /* check right for this page */
    if ( $this->check_right( $this->page_id ) === false ) {
      return $this->init_admin_pageAccessDenied();
    }

    /* get mode */
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'edit';
    
    /* initialise module with mode */
    switch ( $this->mode ) {
    case 'save' :
      /* mode == save */
      $this->init_admin_save();
      break;
    case 'edit' :
    default:
      /* mode == edit */
      $this->init_admin_edit();
      break;
    }
    /* generic module init */
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
   * init module object in site mode
   * @return void
   * @access private
   */
  function init_site ($content=1, $params=array(), $mindex=null) {
    global $camyks;
    
    if ( count($this->mapList) == 0 ) {
      /* add theme editor styles */
      $camyks->theme->get_editor_css();
      /* add email management javascripts */
      $this->add_JSEngineFile('tool/mail.js');
    }
    
    $mapItem = new Content_GoogleMapsViewerItem( $content, $this );
    $mapItem->get($camyks->current_language);
    $mapItem->get_fromItems();
    
    $this->mapList[$mindex] = $mapItem;
    
    /* parent site init */
    parent::init_site();
  }
  
  /*
   * display module object in site mode
   * @return void
   * @access private
   */
  function display_site ($mindex=null) {
    /* get content */
    $this->mapItem = &$this->mapList[$mindex];
    /* get layout */
    $this->selected_layout = 'site_'.($this->check_layout($this->mapItem->vars['layout'])?$this->mapItem->vars['layout']:'classic').'.html.inc';
    /* generic display engine */
    parent::display_site();
  }
  
  /* specific mode methods */
  
  /*
   * init module in admin / edit mode
   * @return void
   * @access private
   */
  function init_admin_edit ( ) {
    global $camyks;
    /* get object id */
    $id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;
    
    /* get object data */
    $this->mapItem->id = $id;
    $this->mapItem->get();
    $this->mapItem->get_fromItems();
    
    /* get form object */
    $this->form = new HTMLForm ('maps_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save')),
				'POST');
    $this->form->add_hidden('id', $this->mapItem->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );
    
    /* get tabs object */
    $this->tabObject = 'maps_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();' );
    $this->add_JSScript($this->tabObject.'.init("properties", "'
			.$camyks->theme->parts['boxTabCSSStandart'].'","'
			.$camyks->theme->parts['boxTabCSSSelected'].'","'
			.$camyks->theme->parts['boxTabCSSRollover'].'");');
    $this->tabs = array(array('name'=>'properties',
			      'title'=>$this->get_translation('tab_properties')));
    foreach( $camyks->_conf['editing_languages'] as $l ) {
      $this->tabs[] = array('name'=>'desc_'.$l,
			    'title'=>'<img src="'.language_getIcon($l, false).'" border="0" alt="'.$l.'" style="" />');
    }
    
    /* get web editor */
    if ( isset($camyks->inputs['TinyMCEv3'])) {
      $this->webEditor = &$camyks->inputs['TinyMCEv3'];
    } elseif ( isset($camyks->inputs['TinyMCE'])) {
      $this->webEditor = &$camyks->inputs['TinyMCE'];
    } else {
      $this->webEditor = false;
    }
    
    /* initialise web editor */
    if ( $this->webEditor !== false ){
      $this->webEditor->set_textareaInfos('content', '100%', '400px');
      $this->webEditor->initialise();
    }

    /* get color picker */
    if ( isset($camyks->inputs['ColorPicker'] ) ) {
      $this->colorPicker = &$camyks->inputs['ColorPicker'];
      $this->colorPicker->initialise('link_color', 'default', 'modal');
    } else {
      $this->colorPicker = false;
    }
    
    /* add form relative scripts */
    $this->add_JSScript('var googlemapsviewer_form = null;');
    $this->add_JSLoadScript('googlemapsviewer_form=document.'.$this->form->name.';');
    $this->add_JSLoadScript('googlemapsviewer_initialise();');
    $this->add_JSFile('googlemapsviewer.js');
    $this->add_JSScript('var locales = {};', true);
    $this->add_JSScript('locales["googlemapsviewer_invalidcode"]="'.string_html2text($this->get_translation('js_invalidcode')).'";', true);
    $this->add_JSScript('locales["googlemapsviewer_resetmap"]="'.string_html2text($this->get_translation('js_resetmap')).'";', true);
    
    $this->add_JSEngineFile('object/ctransition.js');
    
    /* button interface */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink('Admin_ContentPage',
								array('mode'=>'modify',
								      'page_id'=> $this->page_id,
								      'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
  }

  /*
   * init module in admin / save mode
   * @return void
   * @access private
   */
  function init_admin_save ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    if ( !(isset($_REQUEST['id'] )))
      $this->init_admin_edit();
    $id = $_REQUEST['id'];

    /* save object */
    $this->mapItem->id = $id;
    $this->mapItem->get_fromHeader();
    if ( $this->mapItem->save() ) {
      /* update page information with object id for new content */
      if ( $id == 0 and $this->page_id > 0 ) {
	ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->mapItem->id );
      }
      $this->text = $this->get_translation('savedone');
    } else {
      $this->text = $this->get_translation('savefailed');
    }
    /* redirect save page */
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name,
						    array('mode'=>'edit',
							  'id'=>$this->mapItem->id,
							  'page_id'=>$this->page_id,
							  'module_index'=>$this->module_index ) ) );
    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }
  
  /* specific methods */
  
  /*
   * return layouts list
   * @return array
   * @access public
   */
  function get_layouts() {
    return array('classic'=>$this->get_translation('layout_classic'),
      'boxed'=>$this->get_translation('layout_boxed'));
  }
  
  /*
   * check given layout
   * @param string $layout
   * @return boolean result
   * @access public
   */
  function check_layout($layout='') {
    $l = $this->get_layouts();
    return isset($l[$layout]);
  }
}
?>