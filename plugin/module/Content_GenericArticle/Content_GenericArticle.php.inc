<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Sep 2007
 * Last Modif Date	: Oct 2008
 * History :
 * * 07-09-xx : Initial files
 * * 08-06-13 : Disable admin menu for data I/O modes
 * * 08-06-13 : Some minor adjustments to support english locales
 * * 08-07-31 : Add TinyMCEv3 support
 * * 08-10-09 : Some HTML enhancements
 *
 * Content_GenericArticle module
 */

class Content_GenericArticle extends Module {
  /* variables */
  var $articleitem;
  
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
  function Content_GenericArticle ( $path_type ) {
    parent::Module('Content_GenericArticle', $path_type);
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
    $this->libs[] = 'Content_GenericArticleItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->articleitem = new Content_GenericArticleItem(0, $this);    
    /* initialise plugin variables */
    $this->layouts = array();
    $layouts = array('classic', 'classicbox', 'notebox', 'contentbox', 'custom');
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
    global $camyks;
    if ( $this->articleitem->install() ) {
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
    if ( $this->articleitem->uninstall() ) {
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
    return $this->articleitem->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->articleitem->get_nameList();
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
    $this->articleid = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    $this->articleitem->id = $this->articleid;

    /* get action  */
    $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    
    /* get action to execute */
    switch ( $this->mode ) {
    case 'save_item':
      $this->init_admin_save_item();
      break;
    case 'modify_item':
    default:
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
   * @param int $content
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;

    /* add mail encoding javascript */
    $this->add_JSEngineFile('tool/mail.js');

    /* get item */
    $this->articleitem->id = $content; 
    $this->articleitem->get( $camyks->current_language );
    $this->articleitem->get_fromItems();

    /* get author */
    $this->articleAuthor = $camyks->modules['Admin_User']->get_userNameAndEmail( $this->articleitem->vars['author']);
    
    if ( $this->articleAuthor['firstname'] == '' and $this->articleAuthor['lastname'] == '' ) {
      $this->articleAuthor['display'] = $this->articleAuthor['login'];
    } else if ( $this->articleAuthor['firstname'] == '' ) {
      $this->articleAuthor['display'] = $this->articleAuthor['lastname'];
    } else if ( $this->articleAuthor['lastname'] == '' ) {
      $this->articleAuthor['display'] = $this->articleAuthor['firstname'];
    } else {
      $this->articleAuthor['display'] = $this->articleAuthor['firstname'].' '
	.$this->articleAuthor['lastname'];
    }

    if ( $this->articleAuthor['email'] != '' ) {
      $name = $this->articleAuthor['display'];
      $this->articleAuthor['display'] = '<a class="title3" href="'.mail_encode($this->articleAuthor['email']).'">'.$name.'</a>';
    }
    
    /* update layout */
    $this->selected_layout = 'site_'.$this->articleitem->vars['layout'].'.html.inc';

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
   * init module object in admin/modify_item mode
   * @return void
   * @access private
   */
  function init_admin_modify_item() {
    global $camyks;

    /* check editor availability */
    if (!isset($camyks->inputs['TinyMCEv3']) and !isset($camyks->inputs['TinyMCE']))
      return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

    /* get help */
    $this->get_help();

    /* get object */
    $this->articleitem->get(true);
    $this->articleitem->get_fromItems();
    
    /* get tabs description */
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('tabgeneral')));			    
    
    /* add all available language for edition tabs */
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->tabs[] = array('name'=> $l,
			    'title'=> language_getIcon($l));
    }
    
    /* add help if needed */
    if ( $this->help != null ) {
      $this->tabs[] = array('name'=> 'help',
			    'title'=> $camyks->get_translation('help'));
    }
    /* get tabs javascript engine */
    $this->tabObject = 'article_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
    
    /* get form */
    $this->form = new HTMLForm('genericarticle_form',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
			       'POST');
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index);
    $this->form->add_hidden('id', $this->articleitem->id );
    
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify', 
								       'page_id'=>$this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=> $this->form->get_HTMLSubmitLink()));
    
    /* get user list */
    $this->adminList = $camyks->modules['Admin_User']->get_activeUserList();
    
    /* get tiny_mce input */
    if (isset($camyks->inputs['TinyMCEv3'])) {
      $this->input = &$camyks->inputs['TinyMCEv3'];
    } elseif (isset($camyks->inputs['TinyMCE'])) {
      $this->input = &$camyks->inputs['TinyMCE'];
      $this->input->set_configInfos ('default');
    }

    /* initialise input */
    $this->input->initialise();
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

    /* save article */
    $this->articleitem->get_fromHeader();
    if ( $this->articleitem->save() ) {
      if ( $this->articleid == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent( $this->page_id, 
							$this->module_index, 
							$this->articleitem->id );
      }
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    $this->articleitem->get_fromItems();
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify_item', 
							  'id'=>$this->articleitem->id,
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }
}
?>