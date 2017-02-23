<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Nov 2007
 * Last Modif Date	: Jun 2008
 * History : 
 * * 07-11-21 : Initial files
 * * 08-06-13 : Disable admin menu for data I/O modes
 * * 08-10-20 : Add english localisation
 *
 * Content_GenericPageList module
 * Display page list with full page names
 */

class Content_GenericPageList extends Module {
  /* variables */
  var $plitem;
  
  /* admin variables */
  var $mode;
  var $page_id;
  var $module_index;
  var $layouts;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_GenericPageList ( $path_type ) {
    parent::Module('Content_GenericPageList', $path_type);
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
    $this->libs[] = 'Content_GenericPageListItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->plitem = new Content_GenericPageListItem(0, $this);
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->plitem->install() ) {
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
    if ( $this->plitem->uninstall() ) {
      return parent::uninstall();
    }
    return false;
  }

  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    return $this->plitem->is_installed();
  }
  
  /*
   * get available content id/names as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->plitem->get_nameList();
  }

  /*
   * init module object in admin mode
   * @return void
   * access private
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
    $this->plid = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    $this->plitem->id = $this->plid;

    /* get action  */
    $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    
    /* get action to execute */
    switch ( $this->mode ) {
    case 'save_item':
      /* mode == save_item */
      $this->init_admin_save_item();
      break;
    case 'modify_item':
    default:
      /* mode == modify_item */
      $this->init_admin_modify_item();
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
   * @param array $params
   * @param integer $mindex
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;

    if ( !isset( $this->contents ) ) {
      /* get pages */
      $this->pages = $camyks->modules['Admin_ContentPage']->get_sitePages(null, 'active=1');
      /* create contents list */
      $this->contents = array();
    }

    $this->contents[$mindex] = new Content_GenericPageListItem( $content, $this );
    $this->contents[$mindex]->get( $camyks->current_language );
    $this->contents[$mindex]->get_fromItems();

    /* check if "root" page exits */    
    if ( isset ( $this->pages[ $this->contents[$mindex]->vars['root']])) {
      /* get root page */
      $this->contents[$mindex]->vars['pages'] = $this->pages[$this->contents[$mindex]->vars['root']]->children;
    } else {
      foreach ( $this->pages as $p ) {
	$this->contents[$mindex]->vars['pages'] = $this->pages[$p->id]->children;
	break;
      }
    }

    /* check for reverse display */
    if ( $this->contents[$mindex]->vars['listorder'] == 'reverse' ) {
      $this->contents[$mindex]->vars['pages'] = array_reverse( $this->contents[$mindex]->vars['pages'] );
    }

    parent::init_site();
  }  

  /*
   * display module object in site mode
   * @param integer $mindex
   * @return void
   * @access private
   */  
  function display_site ($mindex=null) {
    /* get selected content */
    $this->plitem = $this->contents[$mindex];
    /* update layout */
    $this->selected_layout = 'site_'.$this->plitem->vars['layout'].'.html.inc';
    parent::display_site();
  }

  /* specific admin mode methods */

  /*
   * init module object in admin/modify_item mode
   * @return void
   * @access pivate
   */
  function init_admin_modify_item() {
    global $camyks;
    /* get help */
    $this->get_help();

    /* get object */
    $this->plitem->get(true);
    $this->plitem->get_fromItems();
    
    /* get tabs description */
    $this->tabs = array(array('name'=>'properties',
			      'title'=>$this->get_translation('tabproperties')));
  
    if ( $this->help != null ) {
      $this->tabs[] = array('name'=> 'help',
			    'title'=> $camyks->get_translation('help'));
    }
    /* get tabs javascript engine */
    $this->tabObject = 'pagelist_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
    
    /* get form */
    $this->form = new HTMLForm( 'genericpl_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
				'POST');
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index);
    $this->form->add_hidden('id', $this->plitem->id );
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify', 
								       'page_id'=>$this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=> $this->form->get_HTMLSubmitLink()));
    
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

    /* get item object */
    $this->plitem->get_fromHeader();
    if ( $this->plitem->save() ) {
      if ( $this->plid == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent( $this->page_id, 
							$this->module_index, 
							$this->plitem->id );
      }
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify_item', 
							  'id'=>$this->plitem->id,
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }  
}
?>