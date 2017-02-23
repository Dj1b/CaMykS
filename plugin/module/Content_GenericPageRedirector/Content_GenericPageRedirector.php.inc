<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type		: Plugin / Module Engine
 * Create Date		: Sep 2009
 * Last Modif Date	: Sep 2009
 * History : 
 * * 09-09-17 : Initial files
 *
 * Content_GenericPageRedirector module
 * Redirects visitor on another page
 */

class Content_GenericPageRedirector extends Module {
  /* variables */
  var $pritem;
  
  /* admin variables */
  var $mode;
  var $page_id;
  var $module_index;
  var $layouts;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Content_GenericPageRedirector ( $path_type ) {
    parent::Module('Content_GenericPageRedirector', $path_type);
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
    $this->libs[] = 'Content_GenericPageRedirectorItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->pritem = new Content_GenericPageRedirectorItem(0, $this);
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->pritem->install() and parent::install());
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return ($this->pritem->uninstall() and parent::uninstall());
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    return $this->pritem->is_installed();
  }
  
  /*
   * get available content id/names as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->pritem->get_nameList();
  }
  
  /*
   * init module object in admin mode
   * @return void
   * access private
   */
  function init_admin () {
    global $camyks;
    
    /* pre-initialise module */
    parent::preInit_admin();
    
    /* check right for this page */
    if ( $this->check_right( $this->page_id ) === false )
      return $this->init_admin_pageAccessDenied();
    
    /* check dependencies */
    if (!isset($camyks->inputs['TinyMCEv3']))
      return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');
    if (!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    
    /* get item id */
    $this->pritem->id = $this->id;
    
    /* get action  */
    $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    
    /* get action to execute */
    switch ( $this->mode ) {
    case 'save_item':
      /* mode == save_item */
      $this->init_admin_save_item();
      break;
    case 'edit_item':
    default:
      /* mode == edit_item */
      $this->init_admin_edit_item();
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
  function init_site ( $content=1, $params=array(), $mindex=1 ) {
    global $camyks;
    
    /* load object */
    $this->pritem->id = $content;
    $this->pritem->get($camyks->current_language);
    $this->pritem->get_fromItems();
    
    if ($this->pritem->vars['url'] == '')
      return;
    if ( strpos($this->pritem->vars['url'], 'http') === 0)
      $link = $this->pritem->vars['url'];
    else
      $link = $camyks->get_siteLink($this->pritem->vars['url']);
    
    switch($this->pritem->vars['method']) {
    case 3 :
      header('Location:'.$link);
      break;
    case 1 :
      if ($this->pritem->vars['delay']==0)
	$this->add_JSLoadScript('document.location.href="'.$link.'";');
      else
	$this->add_JSLoadScript('setTimeout("document.location.href=\''.$link.'\'", '.($this->pritem->vars['delay']*1000).');'); 
      break;
    case 2 :
      $this->set_redirect($this->pritem->vars['delay'], $link);
      break;
    case 0:
      if ($this->pritem->vars['delay']==0)
	$this->add_JSLoadScript('document.location.href="'.$link.'";');
      else
	$this->add_JSLoadScript('setTimeout("document.location.href=\''.$link.'\'", '.($this->pritem->vars['delay']*1000).');'); 
      $this->set_redirect($this->pritem->vars['delay'], $link);
      break;
    }
    parent::init_site();
  }  
  
  /*
   * display module object in site mode
   * @param integer $mindex
   * @return void
   * @access private
   */  
  function display_site ($mindex=1) {
    /* update layout */
    $this->selected_layout = 'site_'.$this->pritem->vars['layout'].'.html.inc';
    parent::display_site();
  }
  
  /* specific admin mode methods */
  
  /*
   * init module object in admin/edit_item mode
   * @return void
   * @access pivate
   */
  function init_admin_edit_item() {
    global $camyks;
    
    /* get object */
    $this->pritem->get(true);
    $this->pritem->get_fromItems();
    
    /* get editor input */
    $this->editor = &$camyks->inputs['TinyMCEv3'];
    $this->editor->initialise();
    
    /* build tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array('name'=>'properties',
				     'title'=>$this->get_translation('tabproperties')));
    foreach ($camyks->_conf['editing_languages'] as $l)
      $this->tabBuilder->add_tab(array('name'=>$l,
				       'title'=>language_getIcon($l)));
    
    /* initialise tabs */
    $this->tabBuilder->initialise();
    
    /* get form */
    $this->form = new HTMLForm('edit_form',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
			       'POST');
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index);
    $this->form->add_hidden('id', $this->pritem->id );
    $this->form->set_object($this->pritem);

    /* add javascripts */
    $this->add_JSFile('pageredirector.js');
    $this->add_JSLoadScript('update_formFromMethod();');
    
    /* load page chooser input */
    if (isset($camyks->inputs['PageChooser'])) {
      $this->pc = true;
      $link = $camyks->_conf['url'].'/request.php?module=Admin_ContentPage';
      $this->add_JSScript('pc2 = new PageChooser("pagename", "update_selectedPage", "'.$link.'");');
    } else {
      $this->pc = false;
    }

    
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
    
    /* get item object */
    $this->pritem->get_fromHeader();
    if ($this->pritem->save()) {
      /* update page information with object id for new content */
      if ($this->id == 0 and $this->page_id > 0)
	    $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->pritem->id );
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('id'=>$this->pritem->id, 'mode'=>'edit_item')));
  }
  
  /* specific methods */
  
  /*
   * return redirector method list
   * @return array
   * @access private
   */
  function get_redirectorMethodList() {
    return $this->pritem->get_methodList();
  }
  
  /*
   * return layout list
   * @return array
   * @access private
   */
  function get_redirectorLayoutList() {
    return $this->pritem->get_layoutList();
  }
}
?>