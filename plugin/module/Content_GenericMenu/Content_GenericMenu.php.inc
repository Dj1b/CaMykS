<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Jul 2007
 * Last Modif Date	: Jun 2008
 * History : 
 * * 07-07-xx : Initial file
 * * 07-12-15 : update for full multi content support
 * * 07-12-18 : add a new layer
 * * 08-06-13 : Disable admin menu for data I/O modes
 *
 * Content_GenericMenu module
*/

class Content_GenericMenu extends Module {
  /* variables */
  var $menuitem;
  
  /* admin variables */
  var $mode;
  var $page_id;
  var $module_index;
  var $layouts;
  var $imageid;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_GenericMenu ( $path_type ) {
    parent::Module('Content_GenericMenu', $path_type);
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
    $this->libs[] = 'Content_GenericMenuItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->menuitem = new Content_GenericMenuItem(0, $this);

    /* initialise plugin variables */
    $this->layouts = array();
    $layouts = array('horizontal_bottomlayers', 
		     'vertical_rightlayers',
		     'vertical_leftlayers',
		     'vertical_inline', 
		     'custom');
    foreach ( $layouts as $l ) {
      $this->layouts[ $l ] = $this->get_translation('layout_'.$l);
    }
  }

  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->menuitem->install() ) {
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
    if ( $this->menuitem->uninstall() ) {
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
    return $this->menuitem->is_installed();
  }
  
  /*
   * get available content ids as list
   * @return array
   * @access private
   */
  function get_contentList ( ) {
    return $this->menuitem->get_nameList();
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
    $this->menuid = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    $this->menuitem->id = $this->menuid;

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

    if ( !isset($this->contents) ) {
      /* get site pages */
      $this->pages = $camyks->modules['Admin_ContentPage']->get_sitePages();
      /* update styles */
      $this->add_styleFile('genericmenu.css');
      /* get contents list */
      $this->contents = array();
    }
    
    /* get item */    
    $this->contents[$mindex] = new Content_GenericMenuItem( $content, $this );
    $this->contents[$mindex]->get();
    $this->contents[$mindex]->get_fromItems();
    
    /* check if "root" page exits */    
    if ( isset ( $this->pages[ $this->contents[$mindex]->vars['root'] ] ) ) {
      /* get root page */
      $this->contents[$mindex]->vars['rootpage'] = &$this->pages[ $this->contents[$mindex]->vars['root'] ];
      
      /* specific layout initialisation */
      switch ( $this->contents[$mindex]->vars['layout'] ) {
      case 'horizontal_bottomlayers':
	$this->contents[$mindex]->vars['layeredMenu'] = $this->init_site_buildlayers( $mindex, 'bottom' );
	break;
      case 'vertical_rightlayers':
	$this->contents[$mindex]->vars['layeredMenu'] = $this->init_site_buildlayers( $mindex, 'right' );
	break;
      case 'vertical_leftlayers':
	$this->contents[$mindex]->vars['layeredMenu'] = $this->init_site_buildlayers( $mindex, 'left' );
	break;
      case 'vertical_inline':
      case 'custom':
      default:
	
      }
    }
    parent::init_site();
  }  
  
  /*
   * display module object in site mode
   * @param integer $mindex
   * @return void
   * @access private
   */  
  function display_site ( $mindex=null ) {
    $this->mindex = $mindex;
    $this->layeredMenu = &$this->contents[$mindex]->vars['layeredMenu'];
    $this->root = &$this->contents[$mindex]->vars['rootpage'];
    /* update layout */
    $this->selected_layout = 'site_'.$this->contents[$mindex]->vars['layout'].'.html.inc';
    parent::display_site();
  }
  
  /* specific admin mode methods */

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
    $this->menuitem->get(true);
    $this->menuitem->get_fromItems();
    
    /* get tabs description */
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('tabgeneral')));			    
    
    if ( $this->help != null ) {
      $this->tabs[] = array('name'=> 'help',
			    'title'=> $camyks->get_translation('help'));
    }
    /* get tabs javascript engine */
    $this->tabObject = 'menu_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
    
    /* get form */
    $this->form = new HTMLForm( 'genericmenu_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
				'POST');
    $this->form->add_hidden ('page_id', $this->page_id );
    $this->form->add_hidden ('module_index', $this->module_index);
    $this->form->add_hidden ('id', $this->menuitem->id );
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

    /* save menu */
    $this->menuitem->get_fromHeader();
    if ( $this->menuitem->save() ) {
      if ( $this->menuid == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent( $this->page_id, 
							$this->module_index, 
							$this->menuitem->id );
      }
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    $this->menuitem->get_fromItems();
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify_item', 
							  'id'=>$this->menuitem->id,
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }
  
  /* specific site tool methods */

  /*
   * init module object in site mode 
   * @param integer $mindex
   * @param string $location
   * @return void
   * @access private
   */
  function init_site_buildlayers( $mindex, $location ) {
    /* add layered engine */
    $this->add_JSEngineFile('tool/htmlelement.js');
    $this->add_JSEngineFile('tool/clientenv.js');
    $this->add_JSEngineFile('object/cmenu.js');
    $this->add_JSLoadScript('globalCMenu.init();');
    
    $layeredMenu = array();
    
    /* build menu */
    if ( $this->contents[$mindex]->vars['levels'] > 1 ) {
      foreach ( $this->contents[$mindex]->vars['rootpage']->children as $p ) {
	$page = $this->pages[$p];
	if ( count($page->children) > 0 ) {
	  $this->add_JSScript('var cgm'.$mindex.'_'.$page->name.'Menu = new CMenu("cgm'.$mindex.'_'.$page->name.'Menu", null, "cgm'.$mindex.'_'.$page->name.'Button", "'.$location.'");');
	  $this->add_JSScript('globalCMenu.registerMenu( cgm'.$mindex.'_'.$page->name.'Menu );');
	  $m = array();
	  foreach ( $page->children as $_p ) {
	    $_page = $this->pages[$_p];
	    if ( (!isset( $_page->metas['menu']) or $_page->metas['menu']['content'] != 'hidden') and $_page->active==1 ) 
	      $m[] = array('menu' => 'cgm_'.$_page->name.'Menu',
			   'name' => $_page->name,
			   'title' => $_page->shorttitle!=''?$_page->shorttitle:($_page->title!=''?$_page->title:$_page->name),
			   'icon' => '',
			   'url' => $_page->get_siteLink(),
			   'children' => array());
	  }
	  $layeredMenu['cgm'.$mindex.'_'.$page->name.'Menu']= $m;
	}
      }
    }
    return $layeredMenu;
  }
}
?>