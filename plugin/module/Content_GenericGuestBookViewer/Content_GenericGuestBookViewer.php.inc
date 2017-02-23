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
 * * 10-09-23 : Initial file 
 *
 * Content_GenericGuestBookViewer module :
 * Display Admin_GenericGuestBookManager contents
 */

class Content_GenericGuestBookViewer extends Module {
  /*
   * Constructor
   * @param string $path_type
   */
  function Content_GenericGuestBookViewer ( $path_type ) {
    parent::Module('Content_GenericGuestBookViewer', $path_type);
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
    $this->libs[] = 'Content_GenericGuestBookViewerItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->configItem = new Content_GenericGuestBookViewerItem( 0, $this );
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

    /* check dependencies */
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    if (!isset($camyks->inputs['TinyMCEv3']))
      return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');
    
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
    /* add email management javascripts */
    $this->add_JSEngineFile('tool/mail.js');
 
    /* load manager */
    $this->load_guestBookManager();
    $this->msgItem = $this->manager->get_messageObject();
    $this->mdgItem->isLoaded = false;

    /* load config */
    $this->configItem->id = $content;
    $this->configItem->get();
    $this->configItem->get_fromItems();    

    /* check action to execute */
    $mode = isset($params['msg'])?$params['msg']:'list';

    /* execute action */
    switch ($mode) {
    case 'save':
      $this->init_site_save_message();
      break;
    case 'add':
      $this->init_site_add_message();
      break;
    case 'list':
    default:
      $this->init_site_list_message($params);
      break;
    }
  }

  /*
   * init module object in site / save message mode
   * @return void
   * @access private
   */
  function init_site_save_message() {
    /* attempt to save message */
    if ($this->manager->save_siteMessage()) {
      /* update layout*/
      $this->selected_layout = 'site_message_'.$this->configItem->vars['layout'].'.html.inc';

      return true;
    }
    /* load message fo re-edition */
    $this->msgItem->get_fromItems();
    $this->msgItem->isLoaded = true;
    return $this->init_site_add_message();

  }

  /*
   * init module object in site / add message mode
   * @return void
   * @access private
   */
  function init_site_add_message() {
    global $camyks;

    /* load message data */
    if ($this->msgitem->isLoaded == false)
      $this->msgItem->initialise();
    
    /* check for form display */
    if ($this->configItem->vars['formlayout']==1)
      return $this->init_site_list_message();

    /* load message edition form */
    $this->get_messageForm();
    
    /* update layout */
    $this->selected_layout = 'site_form_'.$this->configItem->vars['layout'].'.html.inc';
  }

  /* 
   * init module object in site / list message mode
   * @params array $params
   * @return void
   * @access private
   */
  function init_site_list_message($params) {
    global $camyks;

    /* check for popup usage */
    if ($this->configItem->vars['formlayout']==1){
      /* load popup engine */
      $this->add_JSEngineFile('tool/popup.js');

      /* load message edition form */
      $this->get_messageForm();
      
      /* check for automatic popup opening */
      if ($this->msgItem->isLoaded == true)
	$this->add_JSLoadScript('popup_openModal("msgpopup");');
    }

    /* count message total */
    $this->msgCount = $this->manager->count_messages(array('status'=>1));
    
    /* build params list */
    $p = array();
    $p['pageCurrent'] = isset($params['page'])?$params['page']:0;
    $p['pageCount'] = ceil($this->msgCount/(int)$this->configItem->vars['msgcount']);
    
    /* check current page */
    if ($p['pageCurrent'] >= $p['pageCount'])
      $p['pageCurrent'] = 0;

    /* add page controller params */
    if(isset($camyks->inputs['GenericPageController'])) {
      
      /* load message list page controller */
      $p['pageParams'] = array($camyks->contentPage->id, $camyks->current_language, array());
      $p['pageParam'] = 'page';
      $p['hideEmpty'] = 1;
      if($this->configItem->vars['gpcstyle'] == 0) {
	$p['buttonSource'] = 'theme';
	$p['styleSource'] = 'theme';
      } else {
	$p['buttonSource'] = 'plugin';
	$p['styleSource'] = 'plugin';
      }
            
      /* load page controller */
      $this->pageController = &$camyks->inputs['GenericPageController'];
      $this->pageController->initialise($p);
    } else {
      $this->pageController = false;
    }

    /* load sign list */
    $sParams = array('status'=>1, 
		     'order'=>'edate',
		     'orderway'=>'desc',
		     'limit' => $p['pageCurrent']*$this->configItem->vars['msgcount'],
		     'count' => $this->configItem->vars['msgcount']);

    $this->msgList = $this->manager->get_messageList($sParams);    
    
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
    $this->configItem->get(true);
    $this->configItem->get_fromItems();

    /* load manager */
    $this->load_guestBookManager();

    /* get edition languages */
    $this->lgs = $camyks->get_confValue('editing_languages');
        
    /* get form object */
    $this->form = new HTMLForm('editform',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save')),
			       'POST');
    $this->form->set_object($this->configItem);
    $this->form->add_hidden('id', $this->configItem->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    /* add properties tab */
    $this->tabBuilder->add_tab(array('name'=>'properties',
				     'title'=>$this->get_translation('tabproperties')));
    if ( count( $this->lgs ) == 1)
      $this->tabBuilder->add_tab(array('name'=>$this->lgs[0],
				       'title'=>$this->get_translation('tabcontent')));
    else
      foreach ( $this->lgs as $l )
	$this->tabBuilder->add_tab(array('name'=>$l,
					 'title'=>language_getIcon($l)));
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder->add_tab(array('name'=>'help',
				       'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'properties'));
    
    /* load editor */
    $this->editor = &$camyks->inputs['TinyMCEv3'];
    $this->editor->initialise();
    
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
							  'module_index'=>$this->module_index ) ) );
    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * return config layout list
   * @return array
   * @access public
   */
  function get_configLayoutList() {
    return $this->configItem->get_layoutList();
  }

  /*
   * return config form layout list
   * @return array
   * @access public
   */
  function get_configFormLayoutList() {
    return $this->configItem->get_formLayoutList();
  }

  /*
   * return config GPC style list
   * @return array5A
   * @access private
   */
  function get_configGPCStyleList() {
    return $this->configItem->get_gpcStyleList();
  }

  /* specific tool methods in site mode */

  /*
   * load blog manager module
   * @return void
   * @access private
   */
  function load_guestBookManager() {
    global $camyks; 
    /* load blog manager */
    if ( !isset($camyks->modules['Admin_GenericGuestBookManager'] ) )
      /* to do */
      die();
    $this->manager = $camyks->modules['Admin_GenericGuestBookManager'];
  }

  /*
   * return add message link
   * @return string
   * @access private
   */
  function get_newMessageLink() {
    global $camyks;
    if ($this->configItem->vars['formlayout'] == 1)
      return 'javascript:popup_openModal(\'msgpopup\');';
    return $camyks->get_siteLink($camyks->contentPage->id, '', '', array('msg'=>'add'));
  }

  /*
   * return message list link
   * @return string
   * @access private
   */
  function get_messageListLink() {
    global $camyks;
    return $camyks->get_siteLink($camyks->contentPage->id);
  }

  /*
   * load message edition form
   * @return void
   * @access private
   */
  function get_messageForm() {
    global $camyks;
    /* load sign form */
    $this->msgform = new HTMLForm('msgform',
				  'javascript:void(0);',
				  'POST');
    $this->msgform->set_parent($this);
    $this->msgform->set_object($this->msgItem);
    $this->add_JSLoadScript('document.msgform.action="'.$camyks->get_siteLink($camyks->contentPage->id, '', null, array('msg'=>'save')).'?preview=forced";');
  }
}
?>