<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Apr 2007
 * Last Modif Date	: May 2008
 * History :
 * * 07-04-xx : Initial files
 * * 08-05-28 : Disable admin menu for data I/O modes
 *
 * Admin_MessagePanel module
 * Display admin users messages
 */

class Admin_MessagePanel extends Module {
  /* variables */
  var $message;
  var $messages;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_MessagePanel ( $path_type ) {
    parent::Module('Admin_MessagePanel', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'helpers';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load libs */
    $this->libs[] = 'Admin_MessagePanelItem.php.inc';
    $this->get_PHPLibs();
    $this->message = new Admin_MessagePanelItem( 0, $this );
  }

  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->message->install( ) ) {
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
    return $this->message->uninstall();
  }

  /*
   * check if module installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    return $this->message->is_installed();
  }

  /*
   * set module object rights
   * @return void
   * @access private
   */
  function get_rights ( ) {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> true);
    $this->rights[1] = array( 'name'=>'write',
			      'title'=> $camyks->get_translation('write'),
			      'default'=> true);
  }

  /*
   * update description in Control Panel Module
   * @return void
   * @access private
   */
  function get_adminControlPanelAction( ) {
    global $camyks;
    $date = $this->message->get_lastObjectDate();
    if ( date_isSameDay ( $date ) ) {
      $camyks->trads['mod_admin_messagepanel_desc'] = 
	vsprintf($camyks->trads['mod_admin_messagepanel_desc_hour'], strftime('%H:%M', $date));
    } else {
      $camyks->trads['mod_admin_messagepanel_desc'] = 
	vsprintf($camyks->trads['mod_admin_messagepanel_desc_date'], date_displayQuickDate($date));
    }
  }
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check access right */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied();
    }
    
    /* get module mode */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'view' );
    
    /* get action to execute case of mode */
    switch ( $this->mode ) {
    case 'save':
      /* mode == save */
      $this->init_admin_save();
      break;
    case 'view':
    default:
      /* mode == view */
      $this->init_admin_view();
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
  function init_admin_view ( ) {
    global $camyks;
    /* message list */
    $this->messages = $this->message->get_objectlist(false,
						     '',
						     0,
						     20,
						     'creation_date',
						     'desc');
    /* message to edit */
    $this->message->id = isset( $_REQUEST['messageid'] ) ? $_REQUEST['messageid'] : 0 ;
    $this->message->get();
    $this->message->get_fromItems();

    /* get form */
    $this->form = new HTMLForm( 'admin_messagepanel_form',
				$camyks->get_adminLink( $this->name, array('mode'=>'save')),
				'POST');
    $this->form->add_hidden('messageid', $this->message->id);
    if ( $this->message->id > 0 ) {
      $this->form->add_hidden('creation_date', $this->message->vars['creation_date'] );
      $this->form->add_hidden('user', $this->message->vars['user'] );
    } else {
      $this->form->add_hidden('user', $camyks->adminUser->login );
    }

    /* get tabs engine */
    $this->openTab = isset($_REQUEST['openTab']) ? $_REQUEST['openTab'] : 'list';
    $this->tabObject = 'admin_messagepanel_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("list", "'
			.$camyks->theme->parts['boxTabCSSStandart'].'","'
			.$camyks->theme->parts['boxTabCSSSelected'].'","'
			.$camyks->theme->parts['boxTabCSSRollover'].'");');
    if ( $this->openTab != 'list' )
      $this->add_JSLoadScript($this->tabObject.'.mouseclick("'.$this->openTab.'");');

    /* get tabs */
    $this->tabs = array(array('name'=>'list',
			      'title'=>$this->get_translation('tablist')));
    if ( $this->check_right(1)===true ) {
      $this->tabs[] = array('name'=>'form',
			    'title'=>$this->get_translation('tab'.($this->message->id==0?'new':'edit')));
    }    

    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link' =>$camyks->get_adminLink()));
  }

  /*
   * init module object in admin/save mode
   * @return void
   * @access private
   */
  function init_admin_save ( ) {
    global $camyks;
    /* check edit items rights */
    if ( $this->check_right(1) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menus */
    $this->disable_adminEngineMenus();
    
    /* get item data */
    $this->message->id = isset ( $_REQUEST['messageid'] ) ? $_REQUEST['messageid'] : 0;
    $this->message->get_fromHeader();
    if ( $this->message->save() ) {
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name, array('mode'=>'list')));
  }
}
?>