<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Jul 2006
 * Last Modif Date	: Jun 2008
 * History :
 * * 06-07-xx : Initial files
 * * 08-06-13 : Disable admin menu for data I/O modes
 *
 * Content_SimpleImage module
*/
 
class Content_SimpleImage extends Module {
  /* variables */
  var $imageitem;
  
  /* admin variables */
  var $mode;
  var $page_id;
  var $module_index;
  var $layouts;
  var $imageid;
  var $maxfilesize;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_SimpleImage ( $path_type ) {
    parent::Module('Content_SimpleImage', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Simple';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'Content_SimpleImageItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->imageitem = new Content_SimpleImageItem(0, $this);
    /* initialise plugin variables */
    $this->maxfilesize = 1024*1024; /* 1 Mo */
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->imageitem->install() ) {
      return parent::install();
    }
    return false;
  }

  /*
   * unistall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    if ( $this->imageitem->uninstall() ) {
      return parent::uninstall();
    }
    return false;
  }
  
  /*
   * check module isntallation
   * @return boolean result
   * @access private
   */ 
  function is_installed ( ) {
    return $this->imageitem->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access private
   */
  function get_contentList ( ) {
    return $this->imageitem->get_nameList();
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
    $this->imageitem->id = $this->imageid;

    /* get action  */
    $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    
    /* get action to execute */
    switch ( $this->mode ) {
    case 'save' :
      /* mode == save */
      $this->init_admin_save();
      break;
    case 'modify':
    default:
      /* mode == modify */
      $this->init_admin_modify();
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
   * @param integer $content
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;
    /* get item */
    $this->imageitem->id = $content; 
    $this->imageitem->get( $camyks->current_language );
    $this->imageitem->get_fromItems();
    $this->selected_layout = 'site_'.$this->imageitem->vars['layout'].'.html.inc';
  }
  
  /* specific admin mode methods */

  /*
   * init module object in admin/modify mode
   * @return void
   * @access private
   */
  function init_admin_modify() {
    global $camyks;
    /* get layout list */
    $this->layouts = array('text' => $this->get_translation('layout_text'),
			   'textbox1' => $this->get_translation('layout_textbox', 1),
			   'textbox2' => $this->get_translation('layout_textbox', 2),
			   'textmixtbox' => $this->get_translation('layout_textmixtbox'));
    
    /* get help */
    $this->get_help();
    /* get object */
    $this->imageitem->get(true);
    $this->imageitem->get_fromItems();
    /* get form */
    $this->form = new HTMLForm( 'simpleimage_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save')),
				'POST');
    $this->form->allow_files(true, $this->maxfilesize);
    $this->form->add_hidden ('page_id', $this->page_id );
    $this->form->add_hidden ('module_index', $this->module_index);
    $this->form->add_hidden ('id', $this->imageitem->id );
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify',
								       'page_id'=> $this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    
    /* get tabs description */
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('tabgeneral')));
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->tabs[] = array('name'=> $l,
			    'title'=> strtoupper( $l ));
    }
    if ( $this->help != null ) {
      $this->tabs[] = array('name'=> 'help',
			    'title'=> $camyks->get_translation('help'));
    }
    /* get tabs javascript engine */
    $this->tabObject = 'simpletext_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
  }
  
  /*
   * init module object in admin/modify mode
   * @return void
   * @access private
   */
  function init_admin_save() {
    global $camyks;
 
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save item */
    $this->imageitem->get_fromHeader();
    if ( $this->imageitem->save() ) {
      if ( $this->imageid == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent( $this->page_id, 
							$this->module_index, 
							$this->imageitem->id );
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
							  'id'=>$this->imageitem->id, 
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }  
}
?>