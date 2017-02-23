<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0b
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Jul 2007
 * Last Modif Date	: Mar 2010
 * History :
 * * 07-07-xx : Initial files
 * * 08-06-13 : Disable admin menu for data I/O modes
 * * 08-10-10 : HTML Enhancements, add english localisation, add dependency list
 * * 10-03-01 : Admin interface enhancements 
 *
 * Content_GenericGallery module
 */

class Content_GenericGallery extends Module {
  /* variables */
  var $imagelist;
  var $imageitem;
  
  /* admin vars */
  var $mode;
  var $page_id;
  var $module_index;
  var $layouts;
  var $imageid;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_GenericGallery ( $path_type ) {
    parent::Module('Content_GenericGallery', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'Content_GenericGalleryItem.php.inc';
    $this->libs[] = 'Content_GenericGalleryList.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->imageitem = new Content_GenericGalleryItem(0, $this);
    $this->imagelist = new Content_GenericGalleryList(0, $this);
    /* initialise plugin variables */
    $this->maxfilesize = 512*1024; /* 512 Ko */
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    global $camyks;
    if ( $this->imageitem->install() and $this->imagelist->install() ) {
      return parent::install();
    }
    return false;
  }

  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    if ( $this->imageitem->uninstall() and $this->imagelist->uninstall() ) {
      return parent::uninstall();
    }
    return false;
  }

  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed() {
    return $this->imagelist->is_installed();
  }

  /*
   * build dependencies list
   * @return boolean
   * @access private
   */
  function set_dependencies() {
    $this->add_dependency('SmartGallery', 'Input', '1.0', true);
    return true;
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->imagelist->get_nameList();
  }

  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
 
    /* page values */
    $this->page_id = isset ( $_REQUEST['page_id'] ) ? $_REQUEST['page_id'] : 0;
    $this->module_index = isset ( $_REQUEST['module_index'] ) ? $_REQUEST['module_index']: -1;
 
    /* check right for this page */
    if ( $this->check_right( $this->page_id ) === false ) {
      return $this->init_admin_pageAccessDenied();
    }
   
    /* get item id */
    $this->imageid = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    $this->imagelist->id = $this->imageid;

    /* get action  */
    $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    
    /* get action to execute */
    switch ( $this->mode ) {
    case 'save_item':
      $this->init_admin_save_item();
      break;
    case 'modify_item':
      $this->init_admin_modify_item();
      break;
    case 'delete_item':
      $this->init_admin_delete_item();
      break;
    case 'save_list' :
      $this->init_admin_save_list();
      break;
    case 'modify_list':
    default:
      $this->init_admin_modify_list();
      break;
    }
    
    /* generic admin initialisation */
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
   * @param int $content
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;

    /* check if input is available */
    if ( !isset( $camyks->inputs['SmartGallery'] ) ) {
      return;
    }

    /* get item */
    $this->imagelist->id = $content; 
    $this->imagelist->get( $camyks->current_language );
    $this->imagelist->get_fromItems();
    $this->imagelist->get_itemList( $camyks->current_language );

    /* get input */
    $this->gallery = $camyks->inputs['SmartGallery'];
    $this->gallery->set_URLsValues( $this->plugin_var_url.'/'.$this->imageitem->_libItems['image']->folder,
				    $this->plugin_var_url.'/'.$this->imageitem->_libItems['thumb']->folder);

    $this->gallery->set_themeValues( $this->imagelist->vars['theme'] );
    
    $this->gallery->set_thumbValues( $this->imagelist->vars['thumbWidth'],
				     $this->imagelist->vars['thumbHeight'],
				     $this->imagelist->vars['thumbCount']);

    $this->gallery->set_imageValues( $this->imagelist->vars['imageWidth'],
				     $this->imagelist->vars['imageHeight'],
				     $this->imagelist->vars['imageTitle'],
				     $this->imagelist->vars['imageDesc']);

    $this->gallery->set_slidingValues($this->imagelist->vars['slidingMethod'],
				       $this->imagelist->vars['slidingAccel'],
				       $this->imagelist->vars['slidingSpeed'],
				       $this->imagelist->vars['slidingInterval']);

    foreach ( $this->imagelist->items as $item ) {
      if ( $item->vars['image'] != '' and $item->vars['thumb'] != '' ) {
	$image = explode('/', $item->vars['image']);
	$image = $image[count($image)-1];
	$thumb = explode('/', $item->vars['thumb']);
	$thumb = $thumb[count($thumb)-1];
	
	$this->gallery->add_item( $item->id,
				  'image',
				  $thumb,
				  $image,
				  $item->vars['title'],
				  $item->vars['description']);
      }
    }
    
    $this->gallery->initialise($this->imagelist->vars['name']);

    /* update layout */
    $this->selected_layout = 'site_'.$this->imagelist->vars['layout'].'.html.inc';

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
   * init module object in admin/modify_list mode
   * @return void
   * @access private
   */
  function init_admin_modify_list() {
    global $camyks;
    /* set layout list */
    $this->layouts = array('nobox' => $this->get_translation('layout_nobox'),
			   'box1' => $this->get_translation('layout_box', 1),
			   'box2' => $this->get_translation('layout_box', 2));

    if (!isset( $camyks->inputs['SmartGallery'])){
      return $this->init_admin_missingPlugin('Input', 'SmartGallery');
    }
    
    /* set theme list */
    $this->themes = $camyks->inputs['SmartGallery']->themes;
    /* set sliding method list */
    $this->slidingMethods = $camyks->inputs['SmartGallery']->slidingMethods;
	
    /* get help */
    $this->get_help();

    /* get object */
    $this->imagelist->get(true);
    $this->imagelist->get_fromItems();
    $this->imagelist->get_itemList();
    /* get form */
    $this->form = new HTMLForm( 'genericgallery_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save_list')),
				'POST');
    $this->form->add_hidden ('page_id', $this->page_id );
    $this->form->add_hidden ('module_index', $this->module_index);
    $this->form->add_hidden ('id', $this->imagelist->id );
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify',
								       'page_id'=> $this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    
    /* edit image link */
    $this->editlink = $camyks->get_adminLink( $this->name,
					      array('id'=>$this->imagelist->id,
						    'page_id'=> $this->page_id,
						    'module_index'=> $this->module_index,
						    'mode'=>'modify_item',
						    'itemid'=>''));
    /* delete image link */
    $this->add_JSScript('var deleteImageMessage="'.string_text2HTML($this->get_translation('deleteitemconfirm')).'";');
    $this->add_JSScript('var deleteImageLink="'.$camyks->get_adminLink( $this->name,
									array('id'=>$this->imagelist->id,
									      'page_id'=> $this->page_id,
									      'module_index'=> $this->module_index,
									      'mode'=>'delete_item',
									      'itemid'=>'')).'";');
    $this->dellink = 'javascript:adminengine_confirmRedirect(deleteImageLink+%s,deleteImageMessage);';
    
    /* get tabs description */
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('tabgeneral')));
    if ( $this->imagelist->id > 0 ) {
      $this->tabs[] = array('name'=>'images',
			    'title'=>$this->get_translation('tabimages'));
      
    }
    
    /* add help tab */
    if ( $this->help != null ) {
      $this->tabs[] = array('name'=> 'help',
			    'title'=> $camyks->get_translation('help'));
    }
    /* get tabs javascript engine */
    $this->tabObject = 'gallery_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
  }

  /*
   * init module object in admin/save_list mode
   * @return void
   * @access private
   */
  function init_admin_save_list() {
    global $camyks;
    
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save list */
    $this->imagelist->get_fromHeader();
    if ( $this->imagelist->save() ) {
      if ( $this->imageid == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent( $this->page_id, 
							$this->module_index, 
							$this->imagelist->id );
      }
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify', 
							  'id'=>$this->imagelist->id, 
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }
  
  /*
   * init module object in admin/modify_item mode
   * @return void
   * @access private
   */
  function init_admin_modify_item() {
    global $camyks;
    
    /* get help */
    $this->get_help();
    
    /* get object */
    $itemid = isset($_REQUEST['itemid'])?$_REQUEST['itemid']:0;
    $this->imageitem->id = $itemid;
    $this->imageitem->get(true);

    if ( $itemid == 0 ) {
      $this->imageitem->_libItems['listid']->value = $_REQUEST['id'];
    }

    $this->imageitem->get_fromItems();
    
    /* get tabs description */
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('tabgeneral')));			    
    
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->tabs[] = array('name'=> $l,
			    'title'=>language_getIcon($l));
    }
    
    if ( $this->help != null ) {
      $this->tabs[] = array('name'=> 'help',
			    'title'=> $camyks->get_translation('help'));
    }
    /* get tabs javascript engine */
    $this->tabObject = 'gallery_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');

    /* get form */
    $this->form = new HTMLForm( 'genericgallery_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
				'POST');
    $this->form->allow_files(true, $this->maxfilesize);
    $this->form->add_hidden ('page_id', $this->page_id );
    $this->form->add_hidden ('module_index', $this->module_index);
    $this->form->add_hidden ('id', $this->imageitem->vars['listid'] );
    $this->form->add_hidden ('listid', $this->imageitem->vars['listid'] );
    $this->form->add_hidden ('itemid', $this->imageitem->id );
    $this->form->add_hidden ('position', $this->imageitem->vars['position'] );
    /* get buttons (on valid, show main tab to be sure that image are sent )*/
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( $this->name,
								 array('mode'=>'modify', 
								       'id'=>$this->imageitem->vars['listid'], 
								       'page_id'=>$this->page_id, 
								       'module_index'=>$this->module_index ))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>'javascript:'.$this->tabObject.'.mouseclick(\'general\');'
				 .'setTimeout(\''.$this->form->get_JSSubmitLink().'\',100);void(0);'));
    
    
    /* update layout */
    $this->selected_layout = 'admin_item.html.inc';
  }
  
  /*
   * init module object in admin/save_item mode
   * @return void
   * @access private
   */
  function init_admin_save_item() {
    global $camyks;
    
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save item */
    $itemid = isset($_REQUEST['itemid'])?$_REQUEST['itemid']:0;
    $this->imageitem->id = $itemid;
    $this->imageitem->get_fromHeader();
    if ( $this->imageitem->save() ) {
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    $this->imageitem->get_fromItems();
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect (4, $camyks->get_adminLink($this->name, 
						   array('mode'=>'modify_item', 
							 'id'=>$this->imageitem->vars['listid'],
							 'itemid'=>$itemid,
							 'page_id'=>$this->page_id, 
							 'module_index'=>$this->module_index)));
  }

  /*
   * init module object in admin/save_delete mode
   * @return void
   * @access private
   */
  function init_admin_delete_item() {
    global $camyks;
        
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* delete item */
    $itemid = isset($_REQUEST['itemid'])?$_REQUEST['itemid']:'';
    $this->imageitem->id = $itemid;
    if ( $this->imageitem->delete() ) {
      $this->text = $camyks->get_translation('deletedone');
    } else {
      $this->text = $camyks->get_translation('deletefailed');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify_list', 
							  'id'=>$this->imagelist->id,
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }
}
?>