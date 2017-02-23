<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * History
 * * 10-09-20 : Initial file 
 *
 * Content_GenericPetitionViewer module :
 * Display Admin_GenericPetitionManager contents
 */

class Content_GenericPetitionViewer extends Module {
  /*
   * Constructor
   * @param string $path_type
   */
  function Content_GenericPetitionViewer ( $path_type ) {
    parent::Module('Content_GenericPetitionViewer', $path_type);
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
    $this->libs[] = 'Content_GenericPetitionViewerItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->configItem = new Content_GenericPetitionViewerItem( 0, $this );
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->configItem->install() )
      return parent::install();
    return false;
  }

  /*
   * uninstall module
   * @return boolean success
   * @access private
   */  
  function uninstall ( ) {
    return $this->configItem->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->configItem->is_installed();
  }
  
  /*
   * get available content ids as list
   * @return array
   * @access private
   */
  function get_contentList ( ) {
    return $this->configItem->get_namelist();
  }
 
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;

    /* generic pre-initialisation */
    parent::preInit_admin();
 
    /* check right for this page */
    if ( $this->check_right( $this->page_id ) === false )
      return $this->init_admin_pageAccessDenied();

    /* get mode */
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'edit';

    /* initialise module with mode */
    switch ( $this->mode ) {
    case 'save' :
      /* mode == save */
      $this->init_admin_save();
    break;
    case 'edit' :
    default:
      /* mode == edit */
      $this->init_admin_edit();
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
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;

    /* add email management javascripts */
    $this->add_JSEngineFile('tool/mail.js');

    /* save params */
    $this->params = $params;
 
    /* load manager */
    $this->load_petitionManager();
   
    /* load sign object */
    $this->signItem = &$this->manager->signatureItem;

    /* check for signature saving */
    if (isset($params['save']) and $params['save'] == 'sign') {
      if ($this->signItem->save_fromSite()) {
	$this->saveMode = 'success';
	$this->signItem->id = 0;
	$this->signItem->get();
      } else {
	$this->saveMode = 'failure';
	$this->saveError = $this->signItem->_libError;
	$this->add_JSLoadScript('popup_openModal("signpopup");');
      }
    } else {
      $this->saveMode = 'null';
      $this->signItem->id = 0;
      $this->signItem->get();
    }
    $this->signItem->get_fromItems();
    
    /* get news list to display */
    $this->configItem->id = $content;
    $this->configItem->get();
    $this->configItem->get_fromItems();    
    
    /* load petition data */
    $this->petitionItem = &$this->manager->petitionItem;
    $this->petitionItem->id = $this->configItem->vars['petition'];
    $this->petitionItem->get($camyks->current_language);
    $this->petitionItem->get_fromItems();
    $this->petitionItem->get_signCount();

    /* load sign page controller */
    $p = array();
    $p['pageCurrent'] = isset($params['page'])?$params['page']:0;
    $p['pageCount'] = ceil($this->petitionItem->vars['signs'] / (int)$this->configItem->vars['signcount']);
    $p['pageParams'] = array($camyks->contentPage->id, $camyks->current_language, array());
    $p['pageParam'] = 'page';
    $p['hideEmpty'] = 1;
    $p['buttonSource'] = 'theme';
    $p['styleSource'] = 'theme';

    /* check current page */
    if ($p['pageCurrent'] >= $p['pageCount'])
      $p['pageCurrent'] = 0;
    
    /* load sia page controller */
    $this->pageController = &$camyks->inputs['GenericPageController'];
    $this->pageController->initialise($p);
   
    /* load sign list */
    $sParams = array('status'=>1, 
		     'petition'=>$this->petitionItem->id, 
		     'order'=>'signdate', 
		     'orderway'=>'desc',
		     'limit' => $p['pageCurrent']*$this->configItem->vars['signcount'],
		     'count' => $this->configItem->vars['signcount']);
    $this->signList = $this->manager->get_signatureList($sParams);
    
    /* load sign form */
    $this->signform = new HTMLForm('signform',
				   'javascript:void(0);',
				   'POST');
    $this->signform->set_parent($this);
    $this->signform->set_object($this->signItem);
    $this->signform->add_hidden('petition', $this->petitionItem->id);
    $this->add_JSLoadScript('document.signform.action="'.$camyks->get_siteLink($camyks->contentPage->id, '', null, array('save'=>'sign')).'"');
    
    $this->add_JSEngineFile('tool/popup.js');
    
    /* update layout */
    $this->selected_layout = 'site_'.$this->configItem->vars['layout'].'.html.inc';
    
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
  /* specific mode methods */

  /*
   * init module in admin / edit mode
   * @return void
   * @access private
   */
  function init_admin_edit ( ) {
    global $camyks;
    /* get object id */
    $id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;

    /* get object data */
    $this->configItem->id = $id;
    $this->configItem->get();
    $this->configItem->get_fromItems();

    /* load manager */
    $this->load_petitionManager();

    /* get edition languages */
    $this->elgs = $camyks->get_confValue('editing_languages');

    /* load data */
    $this->petitionList = $this->manager->get_petitionTitleList(array('status'=>'>0'));
        
    /* get form object */
    $this->form = new HTMLForm('editform',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save')),
				'POST');
    $this->form->set_object($this->configItem);
    $this->form->add_hidden('id', $this->configItem->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );
    
    /* button interface */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink('Admin_ContentPage',
								array('mode'=>'modify',
								      'page_id'=> $this->page_id,
								      'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
  }
  
  /*
   * init module in admin / save mode
   * @return void
   * @access private
   */
  function init_admin_save ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    if ( !(isset($_REQUEST['id'] )))
      $this->init_admin_edit();
    $id = $_REQUEST['id'];

    /* save object */
    $this->configItem->id = $id;
    $this->configItem->get_fromHeader();
    if ( $this->configItem->save() ) {
      /* update page information with object id for new content */
      if ( $id == 0 and $this->page_id > 0 ) {
	ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->configItem->id );
      }
      $this->text = $this->get_translation('savedone');
    } else {
      $this->text = $this->get_translation('savefailed');
    }
    /* redirect save page */
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(
						    array('mode'=>'edit',
							  'id'=>$this->configItem->id,
							  'page_id'=>$this->page_id,
							  'module_index'=>$this->module_index)));
    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * return layout list
   * @return array
   * @access public
   */
  function get_layoutList() {
    return array('nobox'=>$this->get_translation('layout_nobox'));
  }

  /* specific tool methods in site mode */

  /*
   * load blog manager module
   * @return void
   * @access private
   */
  function load_petitionManager() {
    global $camyks; 
    /* load blog manager */
    if ( !isset($camyks->modules['Admin_GenericPetitionManager'] ) )
      /* to do */
      die();
    $this->manager = $camyks->modules['Admin_GenericPetitionManager'];
  }
}
?>