<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Engine
 * Create Date		: May 2007
 * Last Modif Date	: May 2008
 * History :
 * * 07-05-xx : Initial files
 * * 08-05-20 : Rebuild admin layouts
 * * 08-05-28 : Check right on I/O modes
 * *            Disable admin menu for data I/O modes
 *
 * Admin_SystemReport Module
 */

class Admin_SystemReport extends Module {
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_SystemReport ( $path_type ) {
    parent::Module('Admin_SystemReport', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'monitoring';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'skymac.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load plugin libraries */
    $this->libs[] = 'Admin_SystemReportItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */ 
    $this->reportItem = new Admin_SystemReportItem( 0, $this );
    /* initialise plugin variables */
    $this->reportList = array();
    $this->reportsByPage = 20;
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install() {
    if ( $this->reportItem->install() )
      return parent::install();
    return false;
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall() {
    return $this->reportItem->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed() {
    return $this->reportItem->is_installed();
  }

  /*
   * register a menu in admin interface
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenus( ) {
    if ( $this->check_right(1)===true ) {
      return array(array('name'=>'systemreport',
			 'title'=>$this->get_translation('title')));
    }
    return array();
  }

  /*
   * register menu items in admin interface
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenuItems( ) {
    global $camyks;
    /* get mode */
    $mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'display';
    /* set menus */
    if ( $this->check_right(1)===true and $mode == 'display') {
      return array(array('name'=>'markselected',
			 'title'=>$this->get_translation('markitemsasread'),
			 'icon'=>$this->get_fileURL('img/valid12.gif'),
			 'menu'=>'systemreport',
			 'url'=>'javascript:admin_systemreport_marklogsasread();'),
		   array('name'=>'deleteselected',
			 'title'=>$this->get_translation('deleteitems'),
			 'icon'=>$this->get_fileURL('img/clean12.gif'),
			 'menu'=>'systemreport',
			 'url'=>'javascript:admin_systemreport_deletelogs();'));
    }
    return array();
  }
  
  
  /*
   * set module rights
   * @return void
   * @access private
   */
  function get_rights() {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> false);
    $this->rights[1] = array( 'name'=>'write',
			      'title'=> $camyks->get_translation('write'),
			      'default'=> false);
  }
  
  /*
   * update description in control panel
   * @return void
   * @access private
   */
  function get_adminControlPanelAction ( ) {
    global $camyks;
    $n = $this->reportItem->get_objectCount('status=0');
    $camyks->trads['mod_admin_systemreport_desc'] = vsprintf($camyks->trads['mod_admin_systemreport_desc_'], $n );
  }
  
  /*
   * return notified items for module
   * @return Array
   * @access public
   */
  function get_adminInternalNotifications() {
  
  	/* load reports count by type */
	$cnts = $this->reportItem->count_reportsByType(array('status'=>0));
	if (count($cnts) == 0)
	  return array();
	
	/* initialise result */
	$result = array($this->name => array(
		'title'	=> $this->title,
		'items'	=> array()));
	
	/* add types to results */
	foreach ($cnts as $type => $cnt) {
		$result[$this->name]['items'][] = array(
			'title'	=> $type,
			'cnt'	=> $cnt,
			'priority'	=> $type == 'Information' ? 0 : 2,
		);
	}
	
	/* send result */
	return $result;	
  }

  /*
   * init object when in admin mode 
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    
    /* check read rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();
    
    /* check dependencies */
    if (!isset($camyks->inputs['AdminItemListViewer']))
      return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

    /* get mode */
    $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'display';

    /* execute mode */
    switch ( $this->mode ) {
    case 'deletesingle':
      $this->init_admin_deletesingle();
      break;
    case 'markasreadsingle':
      $this->init_admin_markasreadsingle();
      break;
    case 'deletemulti':
      $this->init_admin_deletemulti();
      break;
    case 'markasreadmulti':
      $this->init_admin_markasreadmulti();
      break;
    case 'readreport':
      $this->init_admin_readReport();
      break;
    case 'display':
    default:
      $this->init_admin_main();
      break;
    }

    /* generic initialisation */
    parent::init_admin();
  }


  /* specific admin mode methods */

  /*
   * init module object in admin/display mode
   * @return void
   * @access private
   */
  function init_admin_main( ) {
    global $camyks;
    
    /* build testimonial tab */
    $this->load_file('lib/Admin_SystemReportItemListParams.php.inc');
    $this->reportList = &$camyks->inputs['AdminItemListViewer'];
    $this->reportList->set_params($this->reportListParams);
    $this->reportList->initialise();
    
    /* build multi selection form */
    $this->itemform = new HTMLForm('admin_systemreport_selection',
				        $this->get_adminLink(array()),
				        'POST');
    $this->itemform->add_hidden('mode', 'display');
    $this->itemform->add_hidden('ids', '');
    
    /* add delete log javascripts */
    $this->add_JSFile('admin_systemreport.js');
    $this->add_JSScript('admin_systemreport_selectionform="'.$this->itemform->name.'";');
    $this->add_JSScript('admin_systemreport_deletelogsmessage="'.string_html2Text($this->get_translation('deletelogsmessage')).'";');
    $this->add_JSScript('admin_systemreport_marklogsmessage="'.string_html2Text($this->get_translation('marklogsmessage')).'";');
    
    /* set interface buttons */
    $this->buttons = array(array(
        'title' => $camyks->get_translation('back'),
		'link'  => $camyks->get_adminLink(),
	));
    
    return;
  }

  /*
   * init module object in admin/readreport mode
   * @return void
   * @access private
   */
  function init_admin_readReport() {
    global $camyks;
    
    /* load report */
    $this->reportItem->id = isset($_REQUEST['report_id'])?(int)$_REQUEST['report_id']:-1;
    if ( $this->reportItem->get() === false )
      return $this->init_admin_display();
    $this->reportItem->get_fromItems();

    $this->adminTitle = $this->title.$camyks->get_translation('formitem_separator').$this->get_translation('reportid', $this->reportItem->id);

    /* set interface buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink($this->name)));
    
    /* set actions available when admin user has rights */
    if ( $this->check_right(1)=== true ) {
      if ( $this->reportItem->vars['status'] == 0 ) {
	/* build list form */
	$this->markform = new HTMLForm('admin_systemreport_markform',
				       $camyks->get_adminLink( $this->name, 
							       array('mode'=>'markasreadsingle')),
				       'POST');
	$this->markform->add_hidden('report', $this->reportItem->id );
	$this->buttons[] = array('title'=>$this->get_translation('markasread'),
				 'link'=>$this->markform->get_HTMLSubmitLink());
      }
    }

    /* update layout */
    $this->selected_layout = 'admin_readreport.html.inc';
  }
  
  /*
   * init module object in admin/deletesingle mode
   * @return void
   * @access private
   */
  function init_admin_deleteSingle() {
    global $camyks;

    /* check rights */
    if ( $this->check_right(1)===false)
      return $this->init_admin_accessDenied();

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get item */
    $this->reportItem->id = isset( $_REQUEST['report'])? (int)$_REQUEST['report'] : 0;
    if ( $this->reportItem->id > 0 ) {
      $this->reportItem->delete();
      $this->text = $camyks->get_translation('deletedone');
    } else {
      $this->text = $this->get_translation('reportdoesntexist');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }
  
  /*
   * init module object in admin/markasreadsingle mode
   * @return void
   * @access private
   */
  function init_admin_markasreadsingle() {
    global $camyks;

    /* check rights */
    if ( $this->check_right(1)===false)
      return $this->init_admin_accessDenied();

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get item */
    $this->reportItem->id = isset( $_REQUEST['report'])? (int)$_REQUEST['report'] : 0;
    if ( $this->reportItem->id > 0 and $this->reportItem->update_withAnswer() ) {
      $this->text = $this->get_translation('markeddone');
    } else {
      $this->text = $this->get_translation('reportdoesntexist');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());  
  }
  
  
  /*
   * init module object in admin/markasreadmulti mode
   * @return void
   * @access private
   */
  function init_admin_markasreadmulti() {
    global $camyks;

    /* check rights */
    if ( $this->check_right(1)===false)
      return $this->init_admin_accessDenied();

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get generic item selection */
    $list = $this->get_selectedItems();
    if ( $this->reportItem->update_reports( $list ) ) {
      $this->text = $this->get_translation('multimarkeddone');
    } else {
      $this->text = $this->get_translation('erroroccured');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }  
  
  /*
   * init module object in admin/deletemulti mode
   * @return void
   * @access private
   */
  function init_admin_deletemulti() {
    global $camyks;

    /* check rights */
    if ( $this->check_right(1)===false)
      return $this->init_admin_accessDenied();

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get generic item selection */
    $list = $this->get_selecteditems();
    if ( $this->reportItem->delete_reports( $list ) ) {
      $this->text = $this->get_translation('multideletedone');
    } else {
      $this->text = $this->get_translation('erroroccured');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());  
  }  
  
  /* specific tool methods */

  /*
   * create and save a new report
   * @param string $type
   * @param object $object
   * @param string $errordesc1
   * @param string $errordesc2
   * @param string $errorfile
   * @param string $errorline
   * @return boolean success
   * @access public
   */
  function add_newReport ( $type, &$object, $desc1='', $desc2='',  $file='', $line='' ) {

    /* check if object is not this module to kill loop script */
    if ( strtolower(get_class($object)) == strtolower(get_class($this->reportItem) ) ) {
      /* TO DO */
      return false;
    }
    $this->reportItem->update_values( $type, $object, $desc1, $desc2, $file, $line );
    return $this->reportItem->save();
  }

  /*
   * return selected item list
   * @return array
   * @access private
   */
  function get_selecteditems ( ) {
    $list = array();
    
    $ids = isset($_REQUEST['ids'])?$_REQUEST['ids']:'';
    
    if ($ids == '')
      return $list;    
    
    $list = explode(',', $ids);
    foreach ($list as $id)
      $id = (int)$id;
    
    return $list;
  }
  
  /* specific content management methods */

  /*
   * return single report status list
   * @return array
   * @access public
   */
  function get_reportStatusList() {
	return $this->reportItem->get_statusList();
  }

  /*
   * return report status list
   * @param boolean $more
   * @return array
   * @access private
   */
  function get_reportsStatusList($more=false) {
   	return $this->reportItem->get_multiStatusList($more);
  }
  
  /*
   * return report type list
   * @param boolean $more
   * @return array
   * @access private
   */
  function get_reportTypeList($more=false) {
    return $this->reportItem->get_typelist($more);
  }
}
?>