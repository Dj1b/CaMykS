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
 * * 07-11-06 : Initial files
 * * 08-06-13 : Disable admin menu for data I/O modes
 *
 * Content_GenericQuickMessage module
 */

class Content_GenericQuickMessage extends Module {
  /* variables */
  var $qmitem;
  var $qmlist;
  
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
  function Content_GenericQuickMessage ( $path_type ) {
    parent::Module('Content_GenericQuickMessage', $path_type);
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
    $this->libs[] = 'Content_GenericQuickMessageList.php.inc';
    $this->libs[] = 'Content_GenericQuickMessageItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->qmlist = new Content_GenericQuickMessageList(0, $this);
    $this->qmitem = new Content_GenericQuickMessageItem(0, $this);
    /* initialise plugin variables */
    $this->itemsbypage = 20;
  }

  /* overwrite Module methods */   
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->qmitem->install() and $this->qmlist->install() ) {
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
    if ( $this->qmlist->uninstall() and $this->qmitem->uninstall() ) {
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
    return $this->qmlist->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access private
   */
  function get_contentList ( ) {
    return $this->qmlist->get_nameList();
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
    $this->listid = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    $this->qmlist->id = $this->listid;

    /* get action  */
    $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    
    /* get action to execute */
    switch ( $this->mode ) {
    case 'save_item':
      /* mode == save_item */
      $this->init_admin_save_item();
      break;
    case 'edit_item':
      /* mode == edit_item */
      $this->init_admin_edit_item();
      break;
    case 'save_list':
      /* mode == save_list */
      $this->init_admin_save_list();
      break;
    case 'edit_list':
    default:
      /* mode == edit_list */
      $this->init_admin_edit_list();
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
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;

    if ( !isset( $this->content ) ) {
      /* add js to the page */
      $this->add_JSEngineFile('tool/mail.js');
      $this->add_JSFile('content_genericquickmessage.js');
      /* create content list */
      $this->contents = array();
      $this->forms = array();
    }

    /* add contents to list */
    $this->contents[ $mindex ] = new Content_GenericQuickMessageList( $content, $this );
    $this->contents[ $mindex ]->get();
    $this->contents[ $mindex ]->get_fromItems();


    $this->forms[ $mindex ] = '';

    $this->contents[ $mindex ]->vars['panel'] = 'Messages'.$mindex;
    $this->add_JSScript('cgqm_panels["'.$mindex.'"] = "Messages'.$mindex.'";');

    if ( $this->contents[ $mindex ]->vars['status'] == 0  ) {
      /* deny new message */
      $this->contents[ $mindex ]->vars['save_message'] = $this->get_translation('message_closed');

    } else if ( $this->contents[ $mindex ]->vars['status'] == 1
		and ( !isset( $camyks->modules['Admin_GUAEManager'] )
		      or (( $this->account = $camyks->modules['Admin_GUAEManager']->get_currentUser()) !== false
			  and $this->account->id == 0 )))  {
      /* must be connected and registered to post message */
      $this->contents[ $mindex ]->vars['save_message'] = $this->get_translation('message_registered');
    } else if ( isset( $_REQUEST['qmsave'] )
		and isset( $_REQUEST['listid'] )
		and $_REQUEST['listid'] == $content ) {
      /* save message */
      $this->qmitem->get_fromHeader();
      if ( $this->qmitem->save() ) {
	if ( $this->contents[ $mindex ]->vars['validation'] == 0 )
	  $this->contents[ $mindex ]->vars['save_message'] = $this->get_translation('message_saved');
	else
	  $this->contents[ $mindex ]->vars['save_message'] = $this->get_translation('message_savedadmin');
      } else {
	$this->contents[ $mindex ]->vars['save_message'] = $this->get_translation('message_notsaved');
      }
      $this->contents[ $mindex ]->vars['panel'] = 'Form'.$mindex;
      $this->add_JSScript('cgqm_panels["'.$mindex.'"] = "Form'.$mindex.'";');
      $this->add_JSLoadScript('setTimeout("content_genericquickmessage_swapPanels(\'Messages\', '.$mindex.');", 6000);');
    } else {
      /* add form */
      $this->forms[ $mindex ] = new HTMLForm('qmf'.$this->contents[$mindex]->id,
					     $camyks->get_siteCurrentLink(),
					     'POST');
      $this->forms[ $mindex ]->add_hidden('listid', $this->contents[$mindex]->id);
      $this->forms[ $mindex ]->add_hidden('qmsave', 1);
    }
    
    /* get messages list */
    $this->contents[ $mindex ]->get_validatedMessages();
    
    /* generic init */
    parent::init_site();
  }

  /*
   * display module object in site mode
   * @param integer $mindex
   * @return void
   * @access private
   */  
  function display_site ( $mindex=null ) {
    /* get module content */
    $this->content = $this->contents[ $mindex ];
    $this->form = $this->forms[ $mindex ];
    $this->mindex = $mindex;
    parent::display_site();
  }
 
  /* specific admin mode methods */

  /*
   * init module object in admin/edit_list mode
   * @return void
   * @access private
   */
  function init_admin_edit_list() {
    global $camyks;
    /* get help */
    $this->get_help();

    /* get object */
    $this->qmlist->get();
    $this->qmlist->get_fromItems();
    
    /* get tabs description */
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('tabgeneral')));			    
  

    if ( $this->qmlist->id > 0 ) {
      $this->tabs[] = array('name'=> 'messages',
			    'title'=> $this->get_translation('tabmessages'));
    }

    if ( $this->help != null ) {
      $this->tabs[] = array('name'=> 'help',
			    'title'=> $camyks->get_translation('help'));
    }
    /* get tabs javascript engine */
    $this->tabObject = 'qml_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
    $this->openTab = isset($_REQUEST['openTab'])?$_REQUEST['openTab']:'';
    if ( $this->openTab != '' ) {
      $this->add_JSLoadScript($this->tabObject.'.mouseclick("'.$this->openTab.'");');
    }


    /* get form */
    $this->form = new HTMLForm( 'qml_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save_list')),
				'POST');
    $this->form->add_hidden ('page_id', $this->page_id );
    $this->form->add_hidden ('module_index', $this->module_index);
    $this->form->add_hidden ('id', $this->qmlist->id );
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify', 
								       'page_id'=>$this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=> $this->form->get_HTMLSubmitLink()));
    /* build message list */
    if ( $this->qmlist->id > 0 ) {
      /* build list form */
      $this->listform = new HTMLForm('qml_listform',
				     $camyks->get_adminLink($this->name),
				     'POST');
      $this->listform->add_hidden ('page_id', $this->page_id );
      $this->listform->add_hidden ('module_index', $this->module_index);
      $this->listform->add_hidden ('id', $this->qmlist->id );
      $this->listform->add_hidden ('openTab', 'messages' );
      
      /* get header values */
      $this->listpage = isset ( $_REQUEST['listpage'] ) ? $_REQUEST['listpage'] : 0;
      $this->liststatus = isset ( $_REQUEST['liststatus']) ? $_REQUEST['liststatus'] : -1;
      /* build query */
      $query = 'listid='.$this->qmlist->id;
      if ( $this->liststatus >= 0 ) {
	$query .= ' and status='.$this->liststatus;
      }
    
      /* get report list */
      $this->qmcount = $this->qmitem->get_objectCount( $query );
      $this->pages = ceil($this->qmcount / $this->itemsbypage );
      $this->listpage = min( $this->listpage, $this->pages );
      $this->qmitems = $this->qmitem->get_objectList(false, 
						     $query, 
						     $this->listpage*$this->itemsbypage,
						     $this->itemsbypage,
						     'ndate',
						     'desc');
      /* build edit item link */
      $this->editItemLink = $camyks->get_adminLink($this->name,
						   array('id'=>$this->qmlist->id,
							 'page_id'=>$this->page_id,
							 'module_index'=>$this->module_index,
							 'mode'=>'edit_item',
							 'messageid'=>''));
    }
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
    $this->qmlist->get_fromHeader();
    if ( $this->qmlist->save() ) {
      if ( $this->listid == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent( $this->page_id, 
							$this->module_index, 
							$this->qmlist->id );
      }
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    $this->qmlist->get_fromItems();
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'edit_list', 
							  'id'=>$this->qmlist->id,
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }
  
  /*
   * init module object in admin/edit_item mode
   * @return void
   * @access private
   */
  function init_admin_edit_item() {
    global $camyks;
    
    /* get list linfos */
    $this->qmlist->get();
    $this->qmlist->get_fromItems();
    
    /* get item */
    $this->qmitem->id = isset($_REQUEST['messageid'])?$_REQUEST['messageid']:0;
    $this->qmitem->get();
    $this->qmitem->get_fromItems();
    
    /* get form */
    $this->form = new HTMLForm( 'qmi_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
				'POST');
    $this->form->add_hidden ('page_id', $this->page_id );
    $this->form->add_hidden ('module_index', $this->module_index);
    $this->form->add_hidden ('id', $this->qmlist->id );
    $this->form->add_hidden ('listid', $this->qmlist->id );
    $this->form->add_hidden ('messageid', $this->qmitem->id );
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink($this->name, 
								array('mode'=>'edit_list', 
								      'id'=>$this->qmlist->id,
								      'page_id'=>$this->page_id, 
								      'module_index'=>$this->module_index,
								      'openTab'=>'messages'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=> $this->form->get_HTMLSubmitLink()));
    
    
    /* update layout */
    $this->selected_layout = 'admin_edit_item.html.inc';
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
    $this->qmitem->id = isset($_REQUEST['messageid'])?$_REQUEST['messageid']:0;
    $this->qmitem->get_fromHeader();
    if ( $this->qmitem->save() ) {
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    $this->qmitem->get_fromItems();
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'edit_list', 
							  'id'=>$this->qmlist->id,
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index,
							  'openTab'=>'messages') ) );
  }

  /* specific site tool methods */

  /*
   * return list object validation value
   * @param int $listid
   * @return int
   * @access public
   */
  function get_listObject ( $listid ) {
    if ( $this->qmlist->id != $listid and $this->qmlist->id != 0) {
      $qml = new Content_GenericQuickMessageList( $listid, $this );
      $qml->get();
      $qml->get_fromItems();
      return $qml;
    } else {
      if ( $this->qmlist->id == 0 ) {
	$this->qmlist->id = $listid;
      }
      if ( !isset( $this->qmlist->vars['validation'] ) ) {
	$this->qmlist->get();
	$this->qmlist->get_fromItems();
      }
      return $this->qmlist;
    }
  }
}
?>