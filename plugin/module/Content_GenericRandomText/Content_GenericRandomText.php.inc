<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Mar 2007
 * Last Modif Date	: Oct 2008
 * History :
 * * 07-03-xx : Initial files
 * * 08-06-13 : Disable admin menu for data I/O modes
 * * 08-10-20 : Add english localisation | bug corrections
 * 
 * Content_GenericRandomText module
*/

class Content_GenericRandomText extends Module {
  /* variables */
  var $glist;
  var $gitem;
  var $layouts;

  /* 
   * constructor
   * @param string $path_type
   */
  function Content_GenericRandomText ( $path_type ) {
    parent::Module('Content_GenericRandomText', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'skymac.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'GenericRandomTextItem.php.inc';
    $this->libs[] = 'GenericRandomTextList.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->gitem = new GenericRandomTextItem( 0, $this );
    $this->glist = new GenericRandomTextList( 0, $this );
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->glist->install()
	 and $this->gitem->install() )
      return parent::install();
    return false;
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return $this->glist->uninstall() and $this->gitem->uninstall() ;
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->gitem->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access private
   */
  function get_contentList ( ) {
    return $this->glist->get_namelist();
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
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'edit_list';

    switch ( $this->mode ) {
    case 'save_item':
      /* mode == save_item */
      $this->init_admin_save_item();
      break;
    case 'edit_item':
      /* mode == edit_item */
      $this->init_admin_edit_item();
      break;
    case 'delete_item':
      /* mode == delete_item */
      $this->init_admin_delete_item();
      break;
    case 'save_list' :
      /* mode == save_list */
      $this->init_admin_save_list();
    break;
    case 'edit_list' :
    default:
      /* mode == edit_list */
      $this->init_admin_edit_list();
      break;
    }
    /* generic module init */
    parent::init_admin();
  }
  
  /*
   * display object when in admin part
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
    /* get layout list */
    $this->get_layoutlist();
   
    /* check for session values */
    if ( $camyks->get_sessionValue('grt'.$content.'_layout') != null ) {
      $this->selected_layout = 'site_'.$camyks->get_sessionValue('grt'.$content.'_layout').'html.inc';
      $this->text = $camyks->get_sessionValue('grt'.$content.'_content');
    } else {
      /* get object */
      $this->glist->id = $content;
      $this->glist->get();
      $this->glist->get_fromItems();
      $this->glist->get_itemList();

      /* update layout */
      $this->selected_layout = 'site_'.$this->glist->vars['layout'].'.html.inc';
      
      /* get text to display */
      $randoms = array();
      foreach ($this->glist->vars['items'] as $items ) {
	for($i=0; $i< $items->vars['weight']; $i++ ) {
	  $randoms[] = $items->id;
	}
      }
  
      /* execute random check */
      $selected = $randoms[rand(0, count($randoms)-1)];

      /* get text to display */
      $this->text = $this->glist->vars['items'][$selected]->vars['content'];

      if ( $this->glist->vars['sessionkeep'] == 1 ) {
	$camyks->set_sessionValue('grt'.$content.'_layout', $this->glist->vars['layout']);
	$camyks->set_sessionValue('grt'.$content.'_content', $this->text);
      }
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
   * init module object in admin/save_list mode
   * @return void
   * @access private
   */
  function init_admin_save_list ( ) {
    global $camyks;
    
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get list id */
    $id = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    /* save list */
    $this->glist->id = $id;
    $this->glist->get_fromHeader();
    if ( $this->glist->save() ) {
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    /* update page information with object id for new content */
    if ( $id == 0 and $this->page_id > 0 ) {
      ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->glist->id );
    }
    /* update layout */
    $this->selected_layout='admin_message.html.inc';
    $this->selected_layout_location='camyks';   
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('id' => $this->glist->id,
						      'page_id'=>$this->page_id,
						      'module_index'=>$this->module_index)));
  }

  /*
   * init module object in admin/edit_list mode
   * @return void
   * @access private
   */
  function init_admin_edit_list ( ) {
    global $camyks;
    
    $this->get_layoutlist();

    $this->glist->id = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    $this->glist->get();
    $this->glist->get_fromItems();
    $this->glist->get_itemList();

    /* form */
    $this->form = new HTMLForm('genericrandomtextlist',
			       $camyks->get_adminLink($this->name),
			       'POST');
    $this->form->add_hidden('mode', 'save_list');
    $this->form->add_hidden('id', $this->glist->id);
    $this->form->add_hidden('module_index', $this->module_index);
    $this->form->add_hidden('page_id', $this->page_id);

    /* get tabs */
    if ( $this->glist->id > 0 ) {
      $this->tabs = array(array('name'=>'properties',
				'title'=>$this->get_translation('tabproperties')),
			  array('name'=>'items',
				'title'=>$this->get_translation('tabitems'))); 
      /* add javascript files and scripts */
      $this->add_JSEngineFile('object/ctab.js');
      $this->tabObject = 'randomText_tabObject';
      $this->add_JSScript($this->tabObject.' = new CTab();');
      $this->add_JSScript($this->tabObject.'.init("properties", "'
			  .$this->theme->parts['boxTabCSSStandart'].'","'
			  .$this->theme->parts['boxTabCSSSelected'].'","'
			  .$this->theme->parts['boxTabCSSRollover'].'");');
    }

    /* interface button */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify',
								       'page_id'=> $this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=> $this->form->get_HTMLSubmitLink()));
    
    /* links */
    $this->edittextlink = $camyks->get_adminLink($this->name,
						 array('mode'=>'edit_item',
						      'listid'=>$this->glist->id,
						       'page_id'=>$this->page_id,
						       'module_index'=>$this->module_index,
						       'textid'=>''));
    $this->add_JSScript('var deleteTextLink="'.$camyks->get_adminJSLink($this->name,
									array('mode'=>'delete_item',
									      'listid'=>$this->glist->id,
									      'page_id'=>$this->page_id,
									      'module_index'=>$this->module_index,
									      'textid'=>'')).'";');
    $this->add_JSScript('var deleteTextMessage="'.string_html2Text($this->get_translation('deletemessage')).'";');
    $this->deleteTextLink = 'javascript:adminengine_confirmRedirect(deleteTextLink+%s, deleteTextMessage);';
  }
  
  /*
   * init module object in admin/save_item mode
   * @return void
   * @access private
   */
  function init_admin_save_item ( ) {
    global $camyks;
    
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save list */
    $this->gitem->id = isset($_REQUEST['textid'])?$_REQUEST['textid']:0;
    $this->gitem->get_fromHeader();
    $this->gitem->get_fromItems();
    if ( $this->gitem->save() ) {
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    /* update layout */
    $this->selected_layout='admin_message.html.inc';
    $this->selected_layout_location='camyks';   
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						array('id' => $this->gitem->vars['listid'],
						      'page_id'=>$this->page_id,
						      'module_index'=>$this->module_index)));
  }
    
  /*
   * init module object in admin/edit_item mode
   * @return void
   * @access private
   */
  function init_admin_edit_item ( ) {
    global $camyks;
    
    /* get item object */
    $this->gitem->id = isset($_REQUEST['textid'])?$_REQUEST['textid']:0;
    $this->gitem->get();
    $this->gitem->get_fromItems();
    $this->gitem->vars['listid'] = isset($_REQUEST['listid'])?$_REQUEST['listid']:0;
    
    /* get form */
    $this->form = new HTMLForm('genericrandomtextlist',
			       $camyks->get_adminLink($this->name),
			       'POST');
    $this->form->add_hidden('mode', 'save_item');
    $this->form->add_hidden('textid', $this->gitem->id);
    $this->form->add_hidden('module_index', $this->module_index);
    $this->form->add_hidden('page_id', $this->page_id);
    $this->form->add_hidden('listid', $this->gitem->vars['listid']);
    
    /* interface button */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink($this->name,
								array('mode'=>'edit_list',
								      'id'=>$this->gitem->vars['listid'],
								      'page_id'=> $this->page_id,
								      'module_index'=>$this->module_index))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=> $this->form->get_HTMLSubmitLink()));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_item.html.inc';
  }  

  /*
   * init module object in admin/delete_item mode
   * @return void
   * @access private
   */
  function init_admin_delete_item ( ) {
    global $camyks;
    
    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get item object */
    $this->gitem->id = isset($_REQUEST['textid'])?$_REQUEST['textid']:0;
    $this->gitem->get();
    $listid = $this->gitem->_libItems['listid']->value;

    /* delete object */
    if ( $this->gitem->delete() >= 1 ) {
      $this->text = $camyks->get_translation('deletedone');
    } else {
      $this->text = $camyks->get_translation('deletefailed');
    }
    /* update layout */
    $this->selected_layout='admin_message.html.inc';
    $this->selected_layout_location='camyks';   
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('id' =>$listid,
							'page_id'=>$this->page_id,
							'module_index'=>$this->module_index)));
  }  
  
  /* specific tool methods */

  /*
   * return layout list
   * @return void
   * @access private
   */
  function get_layoutList() {
    $this->layoutlist =  array('classic'=>$this->get_translation('layout_classic'),
			       'boxed'=>$this->get_translation('layout_boxed'));
  }
}
?>