<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CamykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Jun 2007
 * Last Modif Date	: May 2008
 * History :
 * * 07-06-xx : Initial files
 * * 08-05-28 : Disable admin menu for data I/O mode
 *
 * Admin_MyMessages module
 * Internal Message System Module
 */

class Admin_MyMessages extends Module {
  /* variables */
  var $maxmessages;
  var $message;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_MyMessages ( $path_type ) {
    parent::Module('Admin_MyMessages', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'personal';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';

    /* load plugin libraries */
    $this->libs[] = 'Admin_InternalMessage.php.inc';
    $this->get_PHPLibs();
  
    /* get plugin libraries */
    $this->message = new Admin_InternalMessage(0, $this);

    /* initialise some variables */
    $this->maxmessages = 20;
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->message->install() )
      Return parent::install();
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
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->message->is_installed();
  }
  
  /*
   * get module rights
   * @return void
   * @access private
   */
  function get_rights() {
    global $camyks;
    $this->rights[0] = array('name'=>'read',
			     'title'=> $camyks->get_translation('read'),
			     'default'=> true);
    $this->rights[1] = array('name'=>'write',
			     'title'=> $camyks->get_translation('write'),
			     'default'=> true);
  }

  /*
   * update description in control panel
   * @return void
   * @access private
   */
  function get_adminControlPanelAction ( ) {
    global $camyks;
    $n = $this->message->get_objectCount('touser="'.$camyks->adminUser->login.'" and tostatus=2');
    $camyks->trads['mod_admin_mymessages_desc'] = vsprintf($camyks->trads['mod_admin_mymessages_desc_'], $n );
  }
  
  /*
   * init module object when in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    /* check read rights */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied();
    }
    
    /* get mode */
    $mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'list';
    
    /* execute mode */
    switch ( $mode ) {
    case 'update' :
      /* mode == update */
      $this->init_admin_update();
      break;
    case 'send' :
      /* mode == send */
      $this->init_admin_send ();
      break;
    case 'read':
      /* mode == read */
      $this->init_admin_read();
      break;
    case 'list':
    default:
      /* mode == list */
      $this->init_admin_list();
      break;
    }
    
    /* generic initialisation */
    parent::init_admin();
  }
  
  /* specific admin mode methods */

  /*
   * init module object in admin/update mode
   * @return void
   * @access private
   */
  function init_admin_update () {
    global $camyks;
    
    /* get pm ids */
    $pmslist = isset ( $_REQUEST['pms'] ) ? explode(',', $_REQUEST['pms']) : array();
    $pms = array();
    foreach ( $pmslist as $p ) {
      if ( isset ( $_REQUEST['pm_'.$p] ) and $_REQUEST['pm_'.$p] == 1 ) {
	$pms[] = $p;
      }
    }
    
    /* get other data */
    $action = isset($_REQUEST['action']) ? $_REQUEST['action'] : '';
    $view = isset($_REQUEST['view']) ? $_REQUEST['view'] : '';
    
    if ( $action == 0 ) {
      $this->message->delete_messages ( $pms, $view );
    } else if ( $action > 0 ) {
      $this->message->update_messagesStatus ( $pms, $view, $action );
    }
    
    /* set message display */
    $this->text = $this->get_translation( $view.'box_messages_updated' );
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect (4, $camyks->get_adminLink($this->name) );  
  }  

  /*
   * init module object in admin/send mode
   * @return void
   * @access private
   */
  function init_admin_send () {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get message data */
    $this->message->get_fromHeader();

    /* save message */
    if ( $this->message->save() ) {
      $this->text = $this->get_translation('pmsent');
    } else {
      $this->text = $this->get_translation( $this->message->_libError );
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect (4, $camyks->get_adminLink($this->name) );
  }
  
  /* 
   * init module object in admin/read mode
   * @return void
   * @access private
   */
  function init_admin_read ( ) {
    global $camyks;
    
    /* check private message */
    if ( !isset ( $_REQUEST['pm_id'] ) ) {
      return $this->init_admin_list();
    }
    
    /* get message */
    $this->message->id = $_REQUEST['pm_id'];
    if ( $this->message->get() === false )
      return $this->init_admin_list();
    $this->message->get_fromItems();
    
    /* get buttons */
    $this->buttons=array(array('title'=>$camyks->get_translation('back'), 
			       'link'=>$camyks->get_adminLink($this->name)));
    
    /* update message status and set view value */
    if ( $camyks->adminUser->login == $this->message->vars['fromuser'] ) {
      $this->message->update_messagesStatus( array( $this->message->id ), 'from' );
      $this->ouser = $this->message->vars['touser'];
      $this->view = 'to';
    } else if ( $camyks->adminUser->login == $this->message->vars['touser'] ) {
      $this->message->update_messagesStatus( array( $this->message->id ), 'to' );
      $this->ouser = $this->message->vars['fromuser'];
      $this->view = 'from';
     
      /* update button with "answer" one */
      $this->buttons[]=array('title'=>$this->get_translation('answer'), 
			     'link'=>$camyks->get_adminLink($this->name,
							    array('openTab'=>'write',
								  'touser'=>$this->ouser,
								  'title'=>'RE : '.$this->message->vars['title'])));
    }
    /* udpate layout */
    $this->selected_layout = 'admin_read.html.inc';
  }


  /*
   * initialise pm lists display action
   * @return void
   * @access private
   */
  function init_admin_list ( ) {
    global $camyks;

    /* get received pms */
    $this->receivedbox = $this->message->get_reveivedBoxMessageList();
    
    /* get sent pms */ 
    $this->sentbox = $this->message->get_sentBoxMessageList();    
    
    /* add tabs  */
    $this->openTab = isset ( $_REQUEST['openTab'] ) ? $_REQUEST['openTab'] : 'receivedbox';
    $this->tabObject = 'privatemessage_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("receivedbox", "'
			.$this->theme->parts['boxTabCSSStandart'].'","'
			.$this->theme->parts['boxTabCSSSelected'].'","'
			.$this->theme->parts['boxTabCSSRollover'].'");');
    if ( $this->openTab != 'receivedbox' )
      $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');
    
    $this->tabs = array(array('name'=>'receivedbox',
			      'title'=>$this->get_translation('tabreceivedbox')),
			array('name'=>'sentbox',
			      'title'=>$this->get_translation('tabsentbox')),
			array('name'=>'write',
			      'title'=>$this->get_translation('tabwritemessage')));
    
    
    /* add form for pm writing */
    $this->writeform = new HTMLForm('privatemessage_form',
				    $camyks->get_adminLink($this->name),
				    'POST');
    $this->writeform->add_hidden('mode', 'send');
    
    /* add form for received pm management */
    $this->rboxform = new HTMLForm('privatemessage_rboxform',
				   $camyks->get_adminLink($this->name),
				   'POST');
    $this->rboxform->add_hidden('mode', 'update');
    $this->rboxform->add_hidden('view', 'to');
    $pms = array();
    foreach ( $this->receivedbox as $pm ) {
      $pms[] = $pm->id;
    }
    $this->rboxform->add_hidden('pms', implode(',', $pms ));
    
    /* add form for received pm management */
    $this->sboxform = new HTMLForm('privatemessage_sboxform',
				   $camyks->get_adminLink($this->name),
				   'POST');
    $this->sboxform->add_hidden('mode', 'update');
    $this->sboxform->add_hidden('view', 'from');
    $pms = array();
    foreach ( $this->sentbox as $pm ) {
      $pms[] = $pm->id;
    }
    $this->sboxform->add_hidden('pms', implode(',', $pms ));
    
    /* get some values */
    $this->message->get();
    $this->message->get_fromHeader();
    $this->message->get_fromitems();
    
    /* get buttons */
    $this->buttons=array(array('title'=>$camyks->get_translation('back'), 
			       'link'=>$camyks->get_adminLink()));
  }
}
?>