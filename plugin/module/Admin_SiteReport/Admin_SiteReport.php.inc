<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Apr 2007
 * Last Modif Date	: Jul 2008
 * History :
 * * 07-04-xx : Initial files
 * * 08-05-28 : Disable admin menu for data I/O modes
 * * 08-07-17 : Add configuration library | Add attached file to report | Add delete type mode
 *
 * Admin_SiteReport Module
 */

class Admin_SiteReport extends Module {
  /* vars : data */
  var $ritem;
  var $rtype;
  var $itemlist;
  var $typelist;
  var $config;

  /* vars : list */
  var $itemsbypage;
  var $listpage;
  var $listtype;
  var $listviewed;

  /* vars : view item */
  var $answermode;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_SiteReport ( $path_type ) {
    parent::Module('Admin_SiteReport', $path_type);
    /* set module mode */
    $this->type = 'admin';
    $this->admin_type = 'monitoring';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load libs */
    $this->libs[] = 'Admin_SiteReportItem.php.inc';
    $this->libs[] = 'Admin_SiteReportType.php.inc';
    $this->libs[] = 'Admin_SiteReportConfig.php.inc';
    $this->get_PHPLibs();
    /* module values */
    $this->ritem = new Admin_SiteReportItem( -1, $this );
    $this->rtype = new Admin_SiteReportType( -1, $this );
    $this->config = new Admin_SiteReportConfig('config', $this);
    $this->itemsbypage = 20;
  }

  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->ritem->install( ) and $this->rtype->install( ) and $this->config->install() ) {
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
    /* TO DO */
  }

  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    return $this->rtype->is_installed();
  }
 
  /*
   * set module rights
   * @return void
   * @access private
   */
  function get_rights ( ) {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> true);
    $this->rights[1] = array( 'name'=>'answer',
			      'title'=> $this->get_translation('answer'),
			      'default'=> false);
    $this->rights[2] = array( 'name'=>'configure',
			      'title'=> $this->get_translation('configure'),
			      'default'=> false);
  }

  /*
   * update control panel description
   * @return void
   * @access private
   */
  function get_adminControlPanelAction( ) {
    global $camyks;
    $condition = 'answer_date=0';
    $n = $this->ritem->get_objectcount( $condition );
    $camyks->trads['mod_admin_sitereport_desc'] = vsprintf($camyks->trads['mod_admin_sitereport_desc_'], $n );
  }
 
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check read rights */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied();
    }

    /* get module mode */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'list' );

    /* get action to execute case of mode */
    switch ( $this->mode ) {
    case 'edittype':
      /* mode == edittype */
      $this->init_admin_edittype();
      break;
    case 'savetype':
      /* mode == savetype */
      $this->init_admin_savetype();
      break;
    case 'viewtype':
      /* mode == viewtype */
      $this->init_admin_viewtype();
      break;
    case 'deletetype':
      /* mode == deletetype */
      $this->init_admin_deletetype();
      break;
    case 'viewitem':
      /* mode == viewitem */
      $this->init_admin_viewitem();
      break;
    case 'saveitem':
      /* mode == saveitem */ 
      $this->init_admin_saveitem();
      break;
    case 'deleteitem':
      /* mode == deleteitem */
      $this->init_admin_deleteitem();
      break;
    case 'saveconfig':
      /* mode == saveconfig */ 
      $this->init_admin_saveconfig();
      break;
    case 'downloadfile':
      /* mode == downloadfile */
      $this->init_admin_downloadfile();
      break;
    case 'deletefile':
      /* mode == deletefile */
      $this->init_admin_deletefile();
      break;
    case 'list':
    default:
      /* mode == list */
      $this->init_admin_list();
      break;
    }
    parent::init_admin();
  }

  /*
   * init module object in display mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /* specific admin mode methods */

  /*
   * init module object in admin/list mode
   * @return void
   * @access private
   */
  function init_admin_list ( ) {
    global $camyks;

    /* load config */
    $this->config->get();

    /* get header values */
    $this->listpage = isset ( $_REQUEST['listpage'] ) ? $_REQUEST['listpage'] : 0;
    $this->listtype = isset ( $_REQUEST['listtype'] ) ? $_REQUEST['listtype'] : '';
    $this->listviewed = isset ( $_REQUEST['listviewed']) ? $_REQUEST['listviewed'] : 0;

    if ( $this->listviewed == 1 ) {
      $listtests = 'answer_date>0';
    } else if ( $this->listviewed == 2 ) {
      $listtests = 'answer_date=0';
    } else {
      $listtests = '';
    }
    /* get object list */
    $this->itemlist = $this->ritem->get_objectList( false, $listtests, $this->listpage, $this->itemsbypage, 'creation_date', 'desc' );
    $this->pages = ceil($this->ritem->get_objectCount($listtests) / $this->itemsbypage);
    /* get form */
    $this->form = new HTMLForm('admin_sitereport_form',
			       $camyks->get_adminLink( $this->name, array('mode'=>'list')),
			       'POST');
    /* get tabs engine */
    $this->get_admin_tabs ('list');

    /* build some links */
    $this->add_JSScript('var deletereportlink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deleteitem',
											     'ritem'=>'')).'";');
    $this->add_JSScript('var deletereportmessage="'.string_html2Text($this->get_translation('message_js_deletereport')).'";');
    $this->add_JSScript('var deletetypelink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deletetype',
											   'rtype'=>'')).'";');
    $this->add_JSScript('var deletetypemessage="'.string_html2Text($this->get_translation('message_js_deletetype')).'";');
    $this->viewReportLink = $camyks->get_adminLink($this->name, array('mode'=>'viewitem', 'ritem'=>''));
    $this->viewTypeLink = $camyks->get_adminLink($this->name, array('mode'=>'viewtype', 'rtype'=>''));
    $this->editTypeLink = $camyks->get_adminLink($this->name, array('mode'=>'edittype', 'rtype'=>''));

    /* button list for buttons bar */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
			   'link' =>$camyks->get_adminLink()));
    
    /* tab list for tabs bar */
    $this->tabs = array(array('name'=>'list',
			'title'=>$this->get_translation('tablist')));
    if ( $this->check_right(2)===true ) {
      $this->tabs[] = array('name'=>'configure',
		      'title'=>$this->get_translation('tabconfigure'));
      $this->tabs[] = array('name'=>'types',
		      'title'=>$this->get_translation('tabtypes'));
      
      /* get type list */
      $this->typelist = $this->rtype->get_objectlist( );
    
      /* get config form */
      $this->configform = new HTMLForm('admin_sitereport_configform',
				       $camyks->get_adminLink($this->name, array('mode'=>'saveconfig')),
				       'POST');
      $this->add_JSScript('admin_sitereport_configFormName="'.$this->configform->name.'";');
      $this->add_JSFile('admin_sitereport.js'); 

      /* load config */
      $this->config->get();
    }
  }

  /*
   * init module object in admin/edittype mode
   * @return void
   * @acces private
   */
  function init_admin_edittype ( ) {
    global $camyks;
    /* check configure rights */
    if ( $this->check_right(2) === false ) {
      return $this->init_admin_actionNotAllowed();
    }
    /* get object */
    $this->rtype->id = isset ( $_REQUEST['rtype'] ) ? $_REQUEST['rtype'] : 0;
    $this->rtype->get( true );

    $this->rtype->get_fromItems();
    $this->form = new HTMLForm('admin_sitereport_form',
			       $camyks->get_adminLink( $this->name, array('mode'=>'savetype')),
			       'POST');
    $this->form->add_hidden('rtype', $this->rtype->id );

    /* button list for buttons bar */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link' =>$camyks->get_adminLink( $this->name )),
			   array('title'=>$this->get_translation('validtype'),
				 'link' =>$this->form->get_HTMLSubmitLink()));

    /* update layout */
    $this->selected_layout = 'admin_edittype.html.inc';
  }

  /*
   * init module object in admin/savetype mode
   * @return void
   * @access private
   */
  function init_admin_savetype ( ) {
    global $camyks;
    /* check configure rights */
    if ( $this->check_right(2) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save object */
    $this->rtype->id = isset ( $_REQUEST['rtype'] ) ? $_REQUEST['rtype'] : 0;
    $this->rtype->get_fromHeader();
    if ($this->rtype->save())
      $this->text = $this->get_translation('message_typesaved');
    else
      $this->text = $this->get_translation('message_typenotsaved');
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, array('mode'=>'list')));
  }

  /*
   * init module object in admin/viewtype mode
   * @return void
   * @access private
   */
  function init_admin_viewtype ( ) {
    global $camyks;
    /* check configure rights */
    if ( $this->check_right(2) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* get object */
    $this->rtype->id = isset ( $_REQUEST['rtype'] ) ? $_REQUEST['rtype'] : 0;
    $this->rtype->get( true );
    $this->rtype->get_fromItems();

    /* button list for buttons bar */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link' =>$camyks->get_adminLink( $this->name )));

    /* update layout */
    $this->selected_layout = 'admin_viewtype.html.inc';
  }

  /*
   * init module object in admin/deletetype mode
   * @return void
   * @access private
   */
  function init_admin_deletetype ( ) {
    global $camyks;
    /* check configure rights */
    if ( $this->check_right(2) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save object */
    $this->rtype->id = isset ( $_REQUEST['rtype'] ) ? $_REQUEST['rtype'] : 0;
    $this->rtype->get();
    if ( $this->rtype->delete() )
      $this->text = $this->get_translation('message_typedeleted');
    else
      $this->text = $this->get_translation('message_typenotdeleted');
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, array('mode'=>'list')));
  }

  /*
   * init module object in admin/viewitem mode
   * @return void
   * @access private
   */
  function init_admin_viewitem ( ) {
    global $camyks;
    /* get item data */
    $this->ritem->id = isset ( $_REQUEST['ritem'] ) ? $_REQUEST['ritem'] : 0;
    $this->ritem->get();
    $this->ritem->get_fromItems();
    $this->ritem->load_attachedFile();

    /* get item type title */
    $this->rtype->id = $this->ritem->vars['type'];
    if ( in_array( $camyks->current_language, $camyks->site_conf['editing_languages']) ) {
      $this->rtype->get( $camyks->current_language );
    } else {
      $this->rtype->get( );
    }
    $this->rtype->get_fromItems();

    /* set answer mode */
    if ( $this->ritem->vars['answer_date'] > 0 ) {
      $this->answermode = 'answered';
    } else if ( $this->check_right(1)===true ) {
      $this->answermode = 'form';
      /* add form */
      $this->form = new HTMLForm('admin_sitereport_form',
				 $camyks->get_adminLink( $this->name, array('mode'=>'saveitem')),
				 'POST');
      $this->form->add_hidden('ritem', $this->ritem->id );
      $this->form->add_hidden('answer_admin', $camyks->adminUser->login );
      /* add javascript */
      $this->add_JSScript('admin_sitereport_formName="'.$this->form->name.'";');
      $this->add_JSFile('admin_sitereport.js'); 
    } else {
      $this->answermode = 'none';
    }

    $this->downloadFileLink = $camyks->get_adminLink($this->name, array('mode'=>'downloadfile',
									'ritem'=>$this->ritem->id));
    $this->add_JSScript('var deletefilelink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deletefile',
											   'ritem'=>$this->ritem->id)).'";');
    $this->add_JSScript('var deletefilemessage="'.string_html2Text($this->get_translation('message_js_deletefile')).'";');
			
    /* button list for buttons bar */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link' =>$camyks->get_adminLink($this->name)));
    
    if ( $this->answermode == 'form' ) {
      $this->buttons[] = array('title'=>$camyks->get_translation('valid'),
			       'link'=>$this->form->get_HTMLSubmitLink());
    }
    
    
    /* tab list for tabs bar */
    $this->tabs = array(array('name'=>'request',
			      'title'=>$this->get_translation('tabrequest')),
			array('name'=>'answer',
			      'title'=>$this->get_translation('tabanswer')));
    
    /* get tabs */
    $this->get_admin_tabs('request');

    /* update layout */
    $this->selected_layout = 'admin_viewitem.html.inc';
  }

  /*
   * init module object in admin/saveitem mode
   * @return void
   * @access private
   */
  function init_admin_saveitem ( ) {
    global $camyks;
    /* check edit items rights */
    if ( $this->check_right(1) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get item data */
    $this->ritem->id = isset ( $_REQUEST['ritem'] ) ? $_REQUEST['ritem'] : 0;
    /* check if item is not already answered */ 
    $this->ritem->get();
    $this->ritem->get_fromItems();
    if  ( $this->ritem->vars['answer_date'] > 0 ) {
      $this->text = $this->get_translation('allreadyanswered');
    } else {
      $this->ritem->get_fromHeader();
      if ( $this->ritem->save() ) {
	$this->text = $camyks->get_translation('savedone');
      } else {
	$this->text = $camyks->get_translation('savefailed');
      }
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, array('mode'=>'list')));
  }
  
  /*
   * init module object in admin/deleteitem mode
   * @return void
   * @access private
   */
  function init_admin_deleteitem ( ) {
    global $camyks;
    /* check edit items rights */
    if ( $this->check_right(1) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get item data */
    $this->ritem->id = isset ( $_REQUEST['ritem'] ) ? $_REQUEST['ritem'] : 0;
    if ( $this->ritem->delete() ) {
      $this->text = $camyks->get_translation('deletedone');
    } else {
      $this->text = $camyks->get_translation('deletefailed');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, array('mode'=>'list')));
  }


  /*
   * init module object in admin/saveconfig mode
   * @return void
   * @access private
   */
  function init_admin_saveconfig ( ) {
    global $camyks;
    /* check configure rights */
    if ( $this->check_right(2) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save object */
    $this->config->get_fromHeader();
    if ( $this->config->save() )
      $this->text = $this->get_translation('message_configsaved');
    else
      $this->text = $this->get_translation('message_confignotsaved');

    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, array('mode'=>'list')));
  }


  /*
   * init module object in admin/downloadfile mode
   * @return void
   * @access private
   */
  function init_admin_downloadfile ( ) {
    global $camyks;
    if (!isset($_REQUEST['ritem']))
      return $this->init_admin_list();

    /* get item data */
    $this->ritem->id = $_REQUEST['ritem'];
    $this->ritem->get();
    $this->ritem->get_fromItems();
    $this->ritem->load_attachedFile();
    if ( $this->ritem->attachedFile == false )
      return $this->init_admin_viewitem();

    $this->ritem->attachedFile->download();
    die();
  }

  /*
   * init module object in admin/deletefile mode
   * @return void
   * @access private
   */
  function init_admin_deletefile ( ) {
    global $camyks;
    if (!isset($_REQUEST['ritem']))
      return $this->init_admin_list();

    /* get item data */
    $this->ritem->id = $_REQUEST['ritem'];
    $this->ritem->get();
    if ( $this->ritem->delete_attachedFile() )
      $this->text = $this->get_translation('message_attachedfiledeleted');
    else
      $this->text = $this->get_translation('message_attachedfilenotdeleted');

    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, array('mode'=>'viewitem', 'ritem'=>$this->ritem->id)));
  }



  /* specific tool methods */

  /*
   * get javascript for tabs
   * @return void
   * @access private
   */
  function get_admin_tabs ( $default='' ) {
    $this->tabObject = 'admin_sitereport_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("'.$default.'", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
  }
}
?>