<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Sep 2008
 * Last Modif Date	: Sep 2008
 * History
 * * 08-09-25 : Initial files
 *
 * Content_GoogleSearchResultsViewer module :
 * Display Google Search Results
 */

class Content_GoogleSearchResultsViewer extends Module {
  /* variables */
  var $gsrItem;
  var $gsrList;
  
  /*
   * Constructor.
   * @param string $path_type
   */
  function Content_GoogleSearchResultsViewer ( $path_type ) {
    parent::Module('Content_GoogleSearchResultsViewer', $path_type);
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
    $this->libs[] = 'Content_GoogleSearchResultsViewerItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->gsrItem = new Content_GoogleSearchResultsViewerItem(0, $this);
    /* initialise plugin variables */
    $this->gsrList = array();
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->gsrItem->install() )
      return parent::install();
    return false;
  }

  /*
   * uninstall module
   * @return boolean success
   * @access private
   */  
  function uninstall ( ) {
    return $this->gsrItem->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->gsrItem->is_installed();
  }
  
  /*
   * get available content ids as list
   * @return array
   * @access private
   */
  function get_contentList ( ) {
    return $this->gsrItem->get_namelist();
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

    $this->gsrItem->id = $content;
    $this->gsrItem->get();
    $this->gsrItem->get_fromItems();
        
    /* parent site init */
    parent::init_site();
  }
  
  /*
   * display module object in site mode
   * @return void
   * @access private
   */
  function display_site ($mindex=null) {
    /* update layout */
    $this->selected_layout = 'site_'.$this->gsrItem->vars['layout'].'.html.inc';
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
    $this->gsrItem->id = $id;
    $this->gsrItem->get();
    $this->gsrItem->get_fromItems();
    
    /* get form object */
    $this->form = new HTMLForm('gsr_form',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save')),
			       'POST');
    $this->form->add_hidden('id', $this->gsrItem->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );
    
    /* add form relative scripts */
    $this->add_JSScript('var googlesearchresultsviewer_form = null;');
    $this->add_JSLoadScript('googlesearchresultsviewer_form=document.'.$this->form->name.';');
    $this->add_JSLoadScript('googlesearchresultsviewer_initialise();');
    $this->add_JSFile('googlesearchresultsviewer.js');
    $this->add_JSScript('var locales={};');
    $this->add_JSScript('locales["googlesearchresultsviewer_invalidcode"]="'.string_html2text($this->get_translation('js_invalidcode')).'";', true);
    $this->add_JSScript('locales["googlesearchresultsviewer_resetgsr"]="'.string_html2text($this->get_translation('js_resetgsr')).'";', true);
    
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
    $this->gsrItem->id = $id;
    $this->gsrItem->get_fromHeader();
    if ( $this->gsrItem->save() ) {
      /* update page information with object id for new content */
      if ( $id == 0 and $this->page_id > 0 ) {
	ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->gsrItem->id );
      }
      $this->text = $this->get_translation('savedone');
    } else {
      $this->text = $this->get_translation('savefailed');
    }
    /* redirect save page */
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name,
						    array('mode'=>'edit',
							  'id'=>$this->gsrItem->id,
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