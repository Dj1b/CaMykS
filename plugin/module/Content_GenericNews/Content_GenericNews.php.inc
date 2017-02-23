<?php
/*
 * CaMyks Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Mar 2007
 * Last Modif Date	: Jun 2008
 * History :
 * * 07-03-xx : Initial files
 * * 08-05-20 : Update admin list layout
 * * 08-06-13 : Disable admin menu for data I/O modes
 * 
 * Content_GenericNews module :
 * Display news
 */

class Content_GenericNews extends Module {
  /* variables */
  var $layouts_list;
  var $layouts_item;
  var $titles_modes;
  var $newspage;
  var $newsbypage;
  var $status;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_GenericNews ( $path_type ) {
    parent::Module('Content_GenericNews', $path_type);
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
    $this->libs[] = 'Content_GenericNewsList.php.inc';
    $this->libs[] = 'Content_GenericNewsItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin variables */
    $this->layouts_list = array('box_list_titleonly',
				'box_list_complete',
				'box_list_completebyday',
				'box_list_completebymonth',
				'box_list_completebyyear',
				'custom');
    
    $this->layouts_item = array('box_item_complete');
    $this->newsbypage = 16;
    $this->status = array( 0 => 'inedition',
			   1 => 'inline' );
    /* initialise plugin libaries */
    $this->newslist = new Content_GenericNewsList( 0, $this );
    $this->newsitem = new Content_GenericNewsItem( 0, $this );
  }

  /* overwrite Module methods */
 
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->newslist->install() and $this->newsitem->install() )
      return parent::install();
    return false;
  }

  /*
   * uninstall module
   * @return boolean success
   * @access private
   */  
  function uninstall ( ) {
    return $this->newsitem->uninstall() and $this->newslist->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->newsitem->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->newslist->get_namelist();
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
    
    /* initialise module with mode */
    switch ( $this->mode ) {
    case 'save_list' :
      /* mode == save_list */
      $this->init_admin_save_list();
      break;
    case 'save_item' :
      /* mode == save_item */
      $this->init_admin_save_item();
      break;
    case 'edit_item' :
      /* mode == edit_item */
      $this->init_admin_edit_item();
      break;
    case 'edit_list':
    case 'modify' :
    default:
      /* mode == edit_list */
      $this->init_admin_edit_list();
      break;
    }
    /* generic module init */
    parent::init_admin();
  }
  
  /*
   * display module in admin mode
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
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;

    /* add module css styles */
    $this->add_styleFile('genericnews.css');

    /* add email management javascripts */
    $this->add_JSEngineFile('tool/mail.js');
    
    /* get news list to display */
    $this->newslist->id = $content;
    $this->newslist->get();
    $this->newslist->get_fromItems();

    if ( isset ( $params['newsitem'] ) and $params['newsitem'] >= 0 ) {
      /* get single item initialisation */
      $this->init_site_item ( $params );
    } else {
      /* get news list initialisation */
      $this->init_site_list( $params );
    }
    /* parent site init */
    parent::init_site();
  }

  /*
   * display module in site mode
   * @return void
   * @access private
   */
  function display_site () {
    parent::display_site();
  }
  
  /* specific admin mode methods */

  /*
   * init admin page when mode is save_list
   * @return void
   * @access private
   */
  function init_admin_save_list ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    $id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;

    /* save object */
    $this->newslist->id = $id;
    $this->newslist->get_fromHeader();
    if ( $this->newslist->save() ) {
      /* update page information with object id for new content */
      if ( $id == 0 and $this->page_id > 0 ) {
	ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->newslist->id );
      }
      $this->text = $this->get_translation('newslistsaved');
    } else {
      $this->text = $this->get_translation('newslistnotsaved');
    }
    /* redirect save page */
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name,
						    array('mode'=>'modify',
							  'id'=>$this->newslist->id,
							  'page_id'=>$this->page_id,
							  'module_index'=>$this->module_index ) ) );
    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * init admin page when mode is save_item
   * @return void
   * @access private
   */
  function init_admin_save_item ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    $id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;

    /* save object */
    $this->newsitem->id = $id;
    $this->newsitem->get_fromHeader();
    if ( $this->newsitem->save() ) {
      $this->newsitem->get_fromItems();
      /* redirect save page */
      $this->text = $this->get_translation('newsitemsaved');
    } else {
      $this->text = $this->get_translation('newsitemsaved');
    }      
    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify',
							  'id'=>$this->newsitem->vars['listid'],
							  'page_id'=>$this->page_id,
							  'module_index'=>$this->module_index ) ) );
  }

  /*
   * init admin page when mode is edit_item
   * @return void
   * @access private
   */
  function init_admin_edit_item ( ) {
    global $camyks;

    /* get object id */
    $id = isset ( $_REQUEST['newsitemid'] ) ? $_REQUEST['newsitemid'] : 0;

    /* get object data */
    $this->newsitem->id = $id;
    $this->newsitem->get();
    $this->newsitem->get_fromItems();

    if ( $this->newsitem->id == 0 ) {
      $this->newsitem->vars['listid'] = isset($_REQUEST['listid'] )?$_REQUEST['listid']:0;
    }

    /* get form object */
    $this->form = new HTMLForm ( 'newsitem_form',
				 $camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
				 'POST');
    $this->form->add_hidden('id', $this->newsitem->id );
    $this->form->add_hidden('listid', $this->newsitem->vars['listid'] );
    $this->form->add_hidden('author', $this->newsitem->vars['author'] );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );


    /* buttons list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink($this->name,
								array('mode' => 'edit_list', 
								      'page_id' => $this->page_id,
								      'id' => $this->newsitem->vars['listid']))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    /* layout */
    $this->selected_layout = 'admin_edit_item.html.inc';
  }
  
  /*
   * init admin page when mode is edit_list
   * @return void
   * @access private
   */
  function init_admin_edit_list ( ) {
    global $camyks;
    
    /* get object id */
    $id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;
    
    /* get object data */
    $this->newslist->id = $id;
    $this->newslist->get();
    $this->newslist->get_fromItems();
    if ( $id > 0 ) {
      /* get tabs javascript engine */
      $this->openTab = isset ( $_REQUEST['openTab'] ) ? $_REQUEST['openTab'] : 'newsitems';
      $this->tabObject = 'newslist_tabObject';
      $this->add_JSEngineFile ('object/ctab.js');
      $this->add_JSScript($this->tabObject.' = new CTab();');
      $this->add_JSScript($this->tabObject.'.init("properties", "'
			  .$camyks->theme->parts['boxTabCSSStandart'].'","'
			  .$camyks->theme->parts['boxTabCSSSelected'].'","'
			  .$camyks->theme->parts['boxTabCSSRollover'].'");');
      $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');
      /* get news list */
      $this->newspage = isset ( $_REQUEST['newspage']) ? $_REQUEST['newspage'] : 0;
      if ( ! ( $this->newspage >= 0 ) ) {
	$this->newspage = 0;
      }
      $this->newsitems = $this->newsitem->get_adminlist( $this->newslist->id, $this->newspage, $this->newsbypage );
      $this->newscount = $this->newsitem->get_listcount ( $this->newslist->id );
      /* get news list link */
      $this->linknext = $camyks->get_adminLink($this->name,
					       array('mode'=>$this->mode,
						     'id'=>$this->newslist->id,
						     'page_id'=>$this->page_id,
						     'module_index'=>$this->module_index,
						     'openTab'=>'newsitems',
						     'newspage'=>($this->newspage+1)));
      $this->linkprevious = $camyks->get_adminLink($this->name,
						   array('mode'=>$this->mode,
							 'id'=>$this->newslist->id,
							 'page_id'=>$this->page_id,
							 'module_index'=>$this->module_index,
							 'openTab'=>'newsitems',
							 'newspage'=>($this->newspage-1)));
      $this->linkedit = $camyks->get_adminLink($this->name,
					       array('mode'=>'edit_item',
						     'listid'=>$this->newslist->id,
						     'page_id'=>$this->page_id,
						     'module_index'=>$this->module_index,
						     'newsitemid'=>''));
      $this->linknew = $camyks->get_adminLink($this->name,
					      array('mode'=>'edit_item',
						    'listid'=>$this->newslist->id,
						    'page_id'=>$this->page_id,
						    'module_index'=>$this->module_index,
						    'newsitemid'=>0));
    }
    /* get form object */
    $this->form = new HTMLForm ( 'newslist_form',
				 $camyks->get_adminlink( $this->name, array('mode'=>'save_list')),
				 'POST');
    $this->form->add_hidden('id', $this->newslist->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );    
    

    if ( $this->newslist->id > 0 ) {
      /* tab list for tabs list */
      $this->tabs = array(array('name'=>'properties',
				'title'=>$this->get_translation('tabproperties')),
			  array('name'=>'newsitems',
				'title'=>$this->get_translation('tabnewsitems')));
  
    }
    /* buttons list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink('Admin_ContentPage',
								array('mode'=>'modify',
								      'page_id'=> $this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    
    /* layout */
    $this->selected_layout = 'admin_edit_list.html.inc';
  }
  
  /* specific site mode methods */

  /*
   * init module object in site/list mode
   * @param array $params
   * @return void
   * @access private
   */
  function init_site_list ( $params ) {
    global $camyks;
    
    /* get news page to display */
    if ( isset ( $params['newspage'] ) and $params['newspage'] >= 0 ) {
      $this->newspage = $params['newspage'];
    } else {
      $this->newspage = 0;
    }
    
    /* get news items to display from news list */
    $this->newsitems = $this->newsitem->get_siteList( $this->newslist->id,
						      $this->newspage,
						      $this->newslist->vars['count_list']);
    
    $this->newscount = $this->newsitem->get_listcount( $this->newslist->id,
						       1,
						       $camyks->current_language,
						       true);
    
    /* set link */
    if ( ($this->newspage+1)*$this->newslist->vars['count_list'] < $this->newscount)
      $this->nextnews = $camyks->get_siteLink( $camyks->contentPage->id,
					       $camyks->contentPage->name,
					       '',
					       array('newspage'=> $this->newspage+1));
    else 
      $this->nextnews = '';

    if ( $this->newspage > 0 )
      $this->prevnews = $camyks->get_siteLink( $camyks->contentPage->id,
					       $camyks->contentPage->name,
					       '',
					       array('newspage'=> $this->newspage-1));
    else
      $this->prevnews = '';
    

    /* buttons list */
    $this->buttons = array(array('title' => $this->get_translation('previousnews'),
				 'link' => $this->prevnews ),
			   array('title' => $this->get_translation('page', array( $this->newspage+1 )),
				 'link' => '' ),
			   array('title' => $this->get_translation('nextnews'),
				 'link' => $this->nextnews ));
    
    /* set layout to display */
    $this->selected_layout = 'site_'.$this->newslist->vars['layout_list'].'.html.inc';
  }
  
  /*
   * init module object in site/item mode
   * @param array $params
   * @return void
   * @access private
   */
  function init_site_item ( $params ) {
    global $camyks;
    /* get news item object */
    $this->newsitem->id = $params['newsitem'];
    if ( $this->newsitem->get() === false ) {
      $this->init_site_list();
    }
    $this->newsitem->get_fromItems();
    /* check if object is valid */
    if ( ($this->newsitem->vars['language'] != $camyks->current_language )
	 or ( $this->newsitem->vars['status'] == 0 )
	 or ( $this->newsitem->vars['listid'] != $this->newslist->id ) )
      return $this->init_site_list();
    
    /* buttons list */
    $this->buttons = array(array('title' => $this->get_translation('back'),
				 'link' => $camyks->get_siteLink( $camyks->contentPage->id,
								  $camyks->contentPage->name)));
    
    /* set layout to display */
    $this->selected_layout = 'site_'.$this->newslist->vars['layout_item'].'.html.inc';
    return true;
  }

  /* specific site tool methods */

  /*
   * return current page site link for given news item
   * @param integer $id
   * @return string
   * @access private
   */
  function get_singlenewslink ( $id ) {
    global $camyks;
    return $camyks->get_siteLink ( $camyks->contentPage->id,
				   $camyks->contentPage->name,
				   '',
				   array('newsitem'=>$id));
  }
}
?>