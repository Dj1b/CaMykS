<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Apr 2007
 * Last Modif Date	: Jun 2008
 * History
 * * 07-04-xx : Initial files 
 * * 08-06-13 : Disable admin menu for data I/O modes
 * 
 * Content_GenericFaq module
 */

class Content_GenericFaq extends Module {
  /* variables */
  var $layouts_list;
  var $titles_modes;
  var $faqpage;
  var $faqsbypage;
  var $status;

  var $faqlist;
  var $faqitem;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_GenericFaq ( $path_type ) {
    parent::Module('Content_GenericFaq', $path_type);
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
    $this->libs[] = 'Content_GenericFaqList.php.inc';
    $this->libs[] = 'Content_GenericFaqItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin variables */
    $this->layouts_list = array('box_list',
				'box_listindex',
				'box_listprefix');
    
    $this->faqsbypage = 20;
    
    $this->status = array( 0 => 'inedition',
			   1 => 'inline' );
    /* initialise plugin libraries */
    $this->faqlist = new Content_GenericFaqList(0, $this );
    $this->faqitem = new Content_GenericFaqItem(0, $this );
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->faqlist->install() and $this->faqitem->install() )
      return parent::install();
    return false;
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return $this->faqitem->uninstall() and $this->faqlist->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->faqitem->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->faqlist->get_namelist();
  }
  
  /*
   * init module object in admin mode
   * @return array
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

    /* init faq list object */
    $id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;
    /* get object data */
    $this->faqlist->id = $id;


    /* get mode */
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'modify';
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
    case 'move_item_up' :
      /* mode == move_item_up */
      $this->init_admin_move_item_up();
      $this->init_admin_edit_list();
      break;
    case 'move_item_down':
      /* mode == move_item_down */
      $this->init_admin_move_item_down();
      $this->init_admin_edit_list();
      break;
    case 'delete_item':
      /* mode == delete_item */
      $this->init_admin_delete_item();
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
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;
    
    /* get news list to display */
    $this->faqlist->id = $content;
    $this->faqlist->get();
    $this->faqlist->get_fromItems();

    /* get news list initialisation */
    $this->init_site_list( $params );

    /* parent site initialisation */
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
   * init module object in admin / save_list mode
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
    $this->faqlist->id = $id;
    $this->faqlist->get_fromHeader();
    if ( $this->faqlist->save() ) {
      /* update page information with object id for new content */
      if ( $id == 0 and $this->page_id > 0 ) {
	ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->faqlist->id );
      }
      $this->text = $this->get_translation('listsaved');
    } else {
      $this->text = $this->get_translation('listnotsaved');
    }
    /* redirect save page */
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify', 
							  'id'=>$this->faqlist->id, 
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }
  
  /*
   * init module object in admin / save_item mode
   * @return void
   * @access private
   */
  function init_admin_save_item ( ) {
    global $camyks;
    
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    $id = isset ( $_REQUEST['itemid'] ) ? $_REQUEST['itemid'] : 0;
    
    /* save object */
    $this->faqitem->id = $id;
    $this->faqitem->get_fromHeader();
    if ( $this->faqitem->save() ) {
      $this->faqitem->get_fromItems();      
      $this->text = $this->get_translation('itemsaved');
    } else {
      $this->text = $this->get_translation('itemnotsaved');      
    }
    /* layout */
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify', 
							  'id'=>$this->faqlist->id,
							  'page_id'=>$this->page_id,
							  'module_index'=>$this->module_index ) ) );
    
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }
  
  /*
   * init module object in admin / edit_item mode
   * @return void
   * @access private
   */
  function init_admin_edit_item ( ) {
    global $camyks;
    
    /* get object id */
    $id = isset ( $_REQUEST['itemid'] ) ? $_REQUEST['itemid'] : 0;
    
    /* get object data */
    $this->faqitem->id = $id;
    $this->faqitem->get();
    $this->faqitem->get_fromItems();
    
    /* set list id */
    if ( $this->faqitem->id == 0 ) {
      $this->faqitem->vars['listid'] = $this->faqlist->id;
    }
    
    /* get form object */
    $this->form = new HTMLForm('faqitem_form',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
			       'POST');
    $this->form->add_hidden('id', $this->faqitem->vars['listid'] );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );
    $this->form->add_hidden('itemid', $this->faqitem->id );
    $this->form->add_hidden('listid', $this->faqitem->vars['listid'] );


    /* buttons list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( $this->name,
								 array( 'mode' => 'edit_list', 
									'page_id' => $this->page_id,
									'id' => $this->faqitem->vars['listid']))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>'javascript:document.faqitem_form.submit();'));
    
    /* layout */
    $this->selected_layout = 'admin_edit_item.html.inc';
  }
  
  /*
   * init module object in admin / edit_list mode
   * @return void
   * @access private
   */
  function init_admin_edit_list ( ) {
    global $camyks;
    
    $this->faqlist->get();
    $this->faqlist->get_fromItems();
    
    if ( $this->faqlist->id != 0 ) {
      
      /* get tabs javascript engine */
      $this->openTab = isset ( $_REQUEST['openTab'] ) ? $_REQUEST['openTab'] : 'items';
      $this->tabObject = 'faqlist_tabObject';
      $this->add_JSEngineFile('object/ctab.js');
      $this->add_JSScript($this->tabObject.'= new CTab();');
      $this->add_JSScript($this->tabObject.'.init("properties", "'
			  .$camyks->theme->parts['boxTabCSSStandart'].'","'
			  .$camyks->theme->parts['boxTabCSSSelected'].'","'
			  .$camyks->theme->parts['boxTabCSSRollover'].'");');
      $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');
      
      $this->faqitems = $this->faqitem->get_adminlist( $this->faqlist->id );
      $this->faqcount = $this->faqitem->get_listcount ( $this->faqlist->id );
      /* get faq list link */
      $this->linkedit = $camyks->get_adminLink($this->name,
					       array('mode'=>'edit_item',
						     'id'=>$this->faqlist->id,
						     'page_id'=>$this->page_id,
						     'module_index'=>$this->module_index,
						     'itemid'=>''));
      $this->linknew = $camyks->get_adminLink($this->name,
					      array('mode'=>'edit_item',
						    'id'=>$this->faqlist->id,
						    'page_id'=>$this->page_id,
						    'module_index'=>$this->module_index,
						    'itemid'=>0));
      $this->linkup = $camyks->get_adminLink($this->name,
					     array('mode'=>'move_item_up',
						   'id'=>$this->faqlist->id,
						   'page_id'=>$this->page_id,
						   'module_index'=>$this->module_index,
						   'itemid'=>''));
      $this->linkdown = $camyks->get_adminLink($this->name,
					       array('mode'=>'move_item_down',
						     'id'=>$this->faqlist->id,
						     'page_id'=>$this->page_id,
						     'module_index'=>$this->module_index,
						     'itemid'=>''));
      $this->linkdelete = $camyks->get_adminLink($this->name,
						 array('mode'=>'delete_item',
						       'id'=>$this->faqlist->id,
						       'page_id'=>$this->page_id,
						       'module_index'=>$this->module_index,
						       'itemid'=>''));   
    }
    /* get form object */
    $this->form = new HTMLForm ( 'faqlist_form',
				 $camyks->get_adminlink( $this->name, array('mode'=>'save_list')),
				 'POST');
    $this->form->add_hidden('id', $this->faqlist->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );
    

    if ( $this->faqlist->id > 0 ) {
      /* tab list for tabs list */
      $this->tabs = array(array('name'=>'properties',
				'title'=>$this->get_translation('tabproperties')),
			  array('name'=>'items',
				'title'=>$this->get_translation('tabitems')));
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
  
  /*
   * init module object in admin / move_item_up mode
   * @return void
   * @access private
   */
  function init_admin_move_item_up () {
    if ( isset ( $_REQUEST['itemid'] ) ) {
      $this->faqitem->id = $_REQUEST['itemid'];
      $this->faqitem->get();
      $this->faqitem->move_up();
    }
  }
  
  /*
   * init module object in admin / move_item_down mode
   * @return void
   * @access private
   */
  function init_admin_move_item_down() {
    if ( isset ( $_REQUEST['itemid'] ) ) {
      $this->faqitem->id = $_REQUEST['itemid'];
      $this->faqitem->get();
      $this->faqitem->move_down();
    }
  }

  /*
   * init module object in admin / delete_item mode
   * @return void
   * @access private
   */
  function init_admin_delete_item ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* delete object */
    $this->faqitem->id = isset ( $_REQUEST['itemid'] ) ? $_REQUEST['itemid'] : 0;
    if ( $this->faqitem->delete() ) {
      $this->text = $camyks->get_translation('deletedone');
    } else {
      $this->text = $camyks->get_translation('deletefailed');
    }

    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';

    /* redirect save page */
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify', 
							  'id'=>$this->faqlist->id, 
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }

  /* specific site mode methods */

  /*
   * init module object in site / list mode
   * @param array $params
   * @return void
   * @access private
   */
  function init_site_list ( $params ) {
    global $camyks;
    /* get news page to display */
    if ( isset ( $params['faqpage'] ) and $params['faqpage'] >= 0 ) {
      $this->faqpage = $params['faqpage'];
    } else {
      $this->faqpage = 0;
    }
    /* get news items to display from news list */
    $this->faqitems = $this->faqitem->get_siteList( $this->faqlist->id,
						    $this->faqpage,
						    $this->faqlist->vars['count_list']);
    
    $this->faqcount = $this->faqitem->get_listcount( $this->faqlist->id,
						     1,
						     $camyks->current_language);
    
    /* set link */
    if ( ($this->faqpage+1)*$this->faqlist->vars['count_list'] < $this->faqcount)
      $this->nextfaqs = $camyks->get_siteLink( $camyks->contentPage->id,
					       $camyks->contentPage->name,
					       '',
					       array('faqpage'=> $this->faqpage+1));
    else 
      $this->nextfaqs = '';
    
    if ( $this->faqpage > 0 )
      $this->prevfaqs = $camyks->get_siteLink( $camyks->contentPage->id,
					       $camyks->contentPage->name,
					       '',
					       array('faqpage'=> $this->faqpage-1));
    else 
      $this->prevfaqs = '';
    
    /* get buttons */
    $this->buttons = array(array('title' => $this->get_translation('previousfaqs'),
				 'link' => $this->prevfaqs ),
			   array('title' => $this->get_translation('page', array( $this->faqpage+1 )),
				 'link' => '' ),
			   array('title' => $this->get_translation('nextfaqs'),
				 'link' => $this->nextfaqs ));
    
    /* set layout to display */
    $this->selected_layout = 'site_'.$this->faqlist->vars['layout_list'].'.html.inc';
  }
}
?>