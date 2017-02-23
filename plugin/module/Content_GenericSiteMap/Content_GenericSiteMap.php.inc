<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 * History :
 * * 08-08-24 : Initial files
 *
 * Content_GenericSiteMap module
 * 
*/

class Content_GenericSiteMap extends Module {
  /* variables */
  var $smItem;
  
  /* admin variables */
  var $mode;
  var $page_id;
  var $module_index;
  var $layouts;
  var $textid;
  
  /* site variables */
  var $sitemap;
  var $pagecount;
  var $pagelimit;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Content_GenericSiteMap ( $path_type ) {
    parent::Module('Content_GenericSiteMap', $path_type);
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
    $this->libs[] = 'Content_GenericSiteMapItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->smItem = new Content_GenericSiteMapItem(0, $this);
  }
  
  /* overwrite Module methods */  
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->smItem->install() ) {
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
    if ( $this->smItem->uninstall() ) {
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
    return $this->smItem->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->smItem->get_nameList();
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
    $this->smID = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    $this->smItem->id = $this->smID;
    
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
    
    /* get item */
    $this->smItem->id = $content;
    $this->smItem->get();
    $this->smItem->get_fromItems();
    
    /* update layout */
    $this->selected_layout = 'site_'.$this->smItem->vars['layout'].'.html.inc';
    
    /* build site map */
    $this->init_site_buildMap();
  }
  
  /*
   * display module object in site mode
   * @return void
   * @access private
   */  
  function display_site ( ) {
    parent::display_site();
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
			   'textbox2' => $this->get_translation('layout_textbox', 2));
    /* get object */
    $this->smItem->get();
    $this->smItem->get_fromItems();
    /* get form */
    $this->form = new HTMLForm('genericsitemap_form',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save')),
			       'POST');
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index);
    $this->form->add_hidden('id', $this->smItem->id );
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify',
								       'page_id'=> $this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
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
    $this->smItem->get_fromHeader();
    if ( $this->smItem->save() ) {
      if ( $this->smID == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent($this->page_id, 
						       $this->module_index, 
						       $this->smItem->id);
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
							  'id'=>$this->smItem->id, 
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }
  
  /* specific site methods */
  
  /*
   * build site map
   * @param void
   * @return void
   * @access private
   */ 
  function init_site_buildMap() {
    global $camyks;
    
    /* check admin page manager */
    if (!isset($camyks->modules['Admin_ContentPage'])) {
      $camyks->throwFatalError(array('title'=>$this->get_translation('site_fatalerror_title'),
				     'error_link'=>'http://www.camyks.net',
				     'error_title'=>'Check CaMykS website for more informations.'));
    }
    
    /* load pages */
    $this->pages = $camyks->modules['Admin_ContentPage']->get_sitePages();
    
    /* build map */
    $this->pagecount = 0;
    $this->col_width = floor(100/max(1,$this->smItem->vars['columns']));
    $this->pagelimit = ceil(count($this->pages)/(2*max(1,$this->smItem->vars['columns'])));
    
    $this->sitemap = '<div><div style="float:left;width:'.$this->col_width.'%;">';
    $this->buildPageChildrenMap($this->pages[0]->children,0);
    $this->sitemap .= '</div><div style="height:2px; font-size:1px; clear:both;">&nbsp;</div></div>';
  }
  
  /*
   * recursive page children build
   * @param array $children
   * @param integer $level
   * @return void
   * @access private
   */
  function buildPageChildrenMap($children,$level) {
    foreach( $children as $p ) {
      $page = $this->pages[$p];
      /* get page infos */
      if ( $page->active == 1 or $level > 1) {
        $title = $page->shorttitle!=''?$page->shorttitle:($page->title!=''?$page->title:$page->name);
        $url = $page->get_siteLink();
      } else if ( $page->shorttitle != '' or $page->title != '' ) {
        $title = $page->shorttitle!=''?$page->shorttitle:$page->title;
	$url = false;
      } else {
	$title = false;
      }
      /* check new column */
      if ( $this->pagecount == $this->pagelimit ) {
	$this->sitemap .= '</div><div style="float:left;width:'.$this->col_width.'%;">';
	$this->pagecount = 0;
      }
      
      /* build page map item */
      if ( $title !== false ) {
	$margin = $level>0?($level*10).'px':'0';
	$this->sitemap .= '<div class="eContent1" style="margin:1px 0 1px '.$margin.'">';
	if ( $url !== false )
	  $this->sitemap .= '<a class="eLink1" href="'.$url.'">'.$title.'</a>';
	else
	  $this->sitemap .= $title;
	$this->sitemap .= '</div>'."\n";
	$this->pagecount++;
      }
      
      /* display children */
      if ( count($page->children) > 0 )
	$this->buildPageChildrenMap($page->children,$level+1);
    }
  }
}
?>