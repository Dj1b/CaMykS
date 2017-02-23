<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version	: 1.01
 * Object Type          : Plugin / Module Engine
 * Create Date		: Jul 2006
 * Last Modif Date	: Oct 2008
 * History :
 * * 06-08-xx : Initial files
 * * 08-06-13 : Disable admin menu for data I/O modes
 * * 08-10-09 : Some HTML enhancements
 *
 * Content_SimpleText module
 * 
*/

class Content_SimpleText extends Module {
  /* variables */
  var $textitem;
  
  /* admin variables */
  var $mode;
  var $page_id;
  var $module_index;
  var $layouts;
  var $textid;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_SimpleText ( $path_type ) {
    parent::Module('Content_SimpleText', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.01';
    /* set plugin package */
    $this->plugin_package = 'Simple';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'Content_SimpleTextItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->textitem = new Content_SimpleTextItem(0, $this);
  }

  /* overwrite Module methods */  

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->textitem->install() ) {
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
    if ( $this->textitem->uninstall() ) {
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
    return $this->textitem->is_installed();
  }
  
  /*
   * update module
   * @return boolean success
   * @access private
   */
  function update($version, $more='') {
    global $camyks;
    
    /* check version 1.01 */
    if ( version_compare( $this->version, $version ) === 1  )
      if ( $this->textitem->update_toVersion1_01() === false )
	return false;

    /* generic update */
    return parent::update($version, $more);
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->textitem->get_nameList();
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
    $this->textid = isset($_REQUEST['id'])?$_REQUEST['id']:0;
    $this->textitem->id = $this->textid;
    
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
   * @param array $params
   * @param integer $index
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $index=null ) {
    global $camyks;

    /* initialise content list */
    if ( isset( $this->textitems ) === false ) {
      $this->textitems = array();
    }

    /* get item */
    $this->textitems[$index] = new Content_SimpleTextItem($content, $this); 
    $this->textitems[$index]->get( $camyks->current_language );
    $this->textitems[$index]->get_fromItems();
    if ( $this->textitems[$index]->vars['htmlencode'] == 1 )
      $this->textitems[$index]->vars['content'] = nl2br($this->textitems[$index]->vars['content']);
  }

  /*
   * display module object in site mode
   * @param integer $index
   * @return void
   * @access private
   */  
  function display_site ( $index=null ) {
    $this->textitem = &$this->textitems[$index];
    $this->selected_layout = 'site_'.$this->textitem->vars['layout'].'.html.inc';
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

    /* get help */
    $this->get_help();
    /* get object */
    $this->textitem->get(true);
    $this->textitem->get_fromItems();
    /* get form */
    $this->form = new HTMLForm( 'simpletext_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save')),
				'POST');
    $this->form->add_hidden ('page_id', $this->page_id );
    $this->form->add_hidden ('module_index', $this->module_index);
    $this->form->add_hidden ('id', $this->textitem->id );
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify',
								       'page_id'=> $this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    
    /* get tabs description */
    $this->tabs = array(array('name'=>'general',
			      'title'=>$this->get_translation('tabgeneral')));
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->tabs[] = array('name'=> $l,
			    'title'=>language_getIcon($l));
    }
    if ( $this->help != null ) {
      $this->tabs[] = array('name'=> 'help',
			    'title'=> $camyks->get_translation('help'));
    }
    /* get tabs javascript engine */
    $this->tabObject = 'simpletext_tabObject';
    $this->add_JSEngineFile ('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("general", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
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
    $this->textitem->get_fromHeader();
    if ( $this->textitem->save() ) {
      if ( $this->textid == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent( $this->page_id, 
							$this->module_index, 
							$this->textitem->id );
      }
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( $camyks->get_confValue('ModuleActionDelay'), $camyks->get_adminLink($this->name, 
						    array('mode'=>'modify', 
							  'id'=>$this->textitem->id, 
							  'page_id'=>$this->page_id, 
							  'module_index'=>$this->module_index ) ) );
  }  
}
?>