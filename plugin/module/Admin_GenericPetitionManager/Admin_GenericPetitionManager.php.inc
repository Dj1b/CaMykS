<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.petition@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * History :
 * * 10-09-14 : Initial files
 * 
 * Admin_GenericPetitionManager
 */

class Admin_GenericPetitionManager extends Module {
  /* variables */
  var $config;
  var $petitionItem;
  var $signatureItem;
  var $petitionList;
  var $signatureList;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GenericPetitionManager ( $path_type ) {
    parent::Module('Admin_GenericPetitionManager', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* load plugin libraries */
    $this->libs[] = 'Admin_GenericPetitionManagerPetition.php.inc';
    $this->libs[] = 'Admin_GenericPetitionManagerSignature.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->petitionItem = new Admin_GenericPetitionManagerPetition(0, $this);
    $this->signatureItem = new Admin_GenericPetitionManagerSignature(0, $this);

    /* initialise plugin variables */
    $this->petitionList = null;
    $this->signatureList = null;
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ( $this->petitionItem->install() 
	     and $this->signatureItem->install() and parent::install());
  }
  
  /*
   * unintall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return parent::uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->petitionItem->is_installed();
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
    $this->rights[1] = array('name'=>'configuration',
			     'title'=> $this->get_translation('rights_configuration'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'petition',
			     'title'=> $this->get_translation('rights_petition'),
			     'default'=> false);
    $this->rights[3] = array('name'=>'signature',
			     'title'=> $this->get_translation('rights_signature'),
			     'default'=> false);
  }

  /*
   * register a menu in admin interface
   * @return array
   * @access private
   */
  function get_adminEngineSpecificMenus( ) {
    if ( $this->check_right(1)===true and $this->mode == 'list_signature') {
      return array(array('name'=>'petitionmanager',
			 'title'=>$this->get_translation('menutitle')));
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
    /* set menus */
    if ( $this->check_right(1)===true and $this->mode == 'list_signature' ) {
      return array(array('name'=>'exportXLS',
			 'title'=>$this->get_translation('xlsexport'),
			 'icon'=>$this->get_fileURL('img/xls.gif'),
			 'menu'=>'petitionmanager',
			 'url'=>'javascript:window.open(\'request.php?module='.$this->name.'&mode=exportxls&petition_id='.$this->petitionItem->id.'\');void(0);'),
		   );
    }
    return array();
  }
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();

    /* check dependencies */
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    if (!isset($camyks->inputs['AdminItemListViewer']))
      return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
    if (!isset($camyks->inputs['TinyMCEv3']))
      return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

    /* get informations */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'main' );
    
    switch ( $this->mode ) {
    case 'edit_petition':
      /* mode == edit_petition */
      $this->init_admin_edit_petition();
      break;
    case 'save_petition':
      /* mode == save_petition */
      $this->init_admin_save_petition();
      break;
    case 'delete_petition':
      /* mode == delete_petition */
      $this->init_admin_delete_petition();
      break;
    case 'list_signature':
      /* mode == list_signature */
      $this->init_admin_list_signature();
      break;
    case 'edit_signature':
      /* mode == edit_signature */
      $this->init_admin_edit_signature();
      break;
    case 'save_signature':
      /* mode == save_signature */
      $this->init_admin_save_signature();
      break;
    case 'delete_signature':
      /* mode == delete_signature */
      $this->init_admin_delete_signature();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
    }
    
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
   * execute module object in request mode
   * @return void
   * @access private
   */
  function execute_request() {
    global $camyks;
    
    /* load admin context */
    $camyks->get_adminInit();
    if ( !$camyks->check_adminUser() ) {
      /* throw fatal error */
      $error = array('title'=>$this->get_translation('fatalerror_adminonly'),
		     'description'=>$this->get_translation('fatalerror_youmustbelogged'));
      $camyks->throwFatalError( $error );
    }
    
    $camyks->current_language = 'en';
    
    /* check action value */
    if ( isset( $_REQUEST['mode'] ) ) {
      $action = $_REQUEST['mode'];
    } else {
      /* throw fatal error */
      $error = array('title'=>$this->get_translation('fatalerror_actionundefined'),
		     'description'=>$this->get_translation('fatalerror_actionmustbeset'));
      $camyks->throwFatalError( $error );
    }
    
    /* execute action */
    switch ( $action ) {
    case 'exportxls':
      return $this->execute_request_exportXLS();
    default :
      /* throw fatal error */
      $error = array('title'=>$this->get_translation('fatalerror_actionundefined'),
		     'description'=>$this->get_translation('fatalerror_actionmustbeset'));
      $camyks->throwFatalError( $error );
    }
  }
  
  /* specific admin mode methods */
  
  /*
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  function init_admin_main() {
    global $camyks;

    /* set main mode */
    $this->mode = 'main';
    
    /* get help */
    $this->get_help();
    
    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();

    /* build petition tab */
    $this->load_file('lib/Admin_GenericPetitionManagerPetitionListParams.php.inc');
    $this->petitionList = &$camyks->inputs['AdminItemListViewer'];
    $this->petitionList->set_params($this->petitionListParams);
    $this->petitionList->initialise();    

    /* get petition ids */
    $petitionIDs = array_keys($this->petitionList->objectList);
    $cnts = $this->count_signsByPetitions($petitionIDs);
    foreach( $this->petitionList->objectList as $id => &$petition)
      $petition->vars['signs'] = isset($cnts[$id])?$cnts[$id]:0;
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    /* add petitions tab */
    $this->tabBuilder->add_tab(array('name'=>'petitions',
				     'title'=>$this->get_translation('tabpetitions')));
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'petitions'));
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }
  
  /*
   * init module object in admin/edit_petition mode
   * @return void
   * @access private
   */
  function init_admin_edit_petition() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();
    $this->lgs = $camyks->get_confValue('editing_languages');
    
    /* get petition item */
    $petition_id = isset($_REQUEST['petition_id'])?$_REQUEST['petition_id']:0;
    $this->petitionItem->id = $petition_id;
    $this->petitionItem->get();
    $this->petitionItem->get_fromItems();
    
    /* get form */
    $this->editform = new HTMLForm('edit_petition',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_petition')),
				   'POST');
    $this->editform->add_hidden('petition_id', $this->petitionItem->id );
    $this->editform->set_object($this->petitionItem);
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
		/* add petitions tab */
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
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->petitionItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('petitionnew');
    else
      $this->adminTitle .= $this->get_translation('petitionid', $this->petitionItem->id);
    
    /* build button list */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_petition.html.inc';
  }
  
  /*
   * init module object in admin/save_petition mode
   * @return void
   * @access private
   */
  function init_admin_save_petition() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* check petition id */
    if ( !isset($_REQUEST['petition_id']))
      return $this->init_admin_main();
    $petition_id = $_REQUEST['petition_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save petition */
    $this->petitionItem->id = $petition_id;
    $this->petitionItem->get_fromHeader();
    if ( $this->petitionItem->save() )
      $this->text = $this->get_translation('petition_saved');
    else
      $this->text = $this->get_translation('petition_notsaved');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }
  
  /*
   * init module object in admin/delete_petition mode
   * @return void
   * @access private
   */
  function init_admin_delete_petition() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed () ;

    /* check petition id */
    if ( !isset($_REQUEST['petition_id']))
      return $this->init_admin_main();
    $petition_id = $_REQUEST['petition_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* delete petition */
    $this->petitionItem->id = $petition_id;
    if ( $this->petitionItem->delete())
      $this->text = $this->get_translation('petition_deleted');
    else
      $this->text = $this->get_translation('petition_notdeleted');
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }

  /*
   * init module object in admin/list_signature mode
   * @return void
   * @access private
   */
  function init_admin_list_signature() {
    global $camyks;

    /* check petition */
    if (!isset($_REQUEST['petition_id']))
      return $this->init_admin_main();

    /* get petition id */
    $this->petitionItem->id = $_REQUEST['petition_id'];

    /* build petition tab */
    $this->load_file('lib/Admin_GenericPetitionManagerSignatureListParams.php.inc');
    $this->signList = &$camyks->inputs['AdminItemListViewer'];
    $this->signList->set_params($this->signatureListParams);
    $this->signList->initialise();
    
    /* */
    $this->adminTitle = $this->title
      .$camyks->get_translation('formitem_separator')
      .$this->get_translation('title_listsignature');

    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));

    /* update layout */
    $this->selected_layout = 'admin_list_sign.html.inc';
  }
  
  /*
   * init module object in admin/edit_signature mode
   * @return void
   * @access private
   */
  function init_admin_edit_signature() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed () ;
    
    /* get signature item */
    $signature_id = isset($_REQUEST['signature_id'])?$_REQUEST['signature_id']:0;
    $this->signatureItem->id = $signature_id;
    $this->signatureItem->get();
    $this->signatureItem->get_fromItems();
 
    /* get form */
    $this->editform = new HTMLForm('edit_signature',
				   $this->get_adminlink(array('mode'=>'save_signature')),
				   'POST'); 
    $this->editform->set_object($this->signatureItem);
    $this->editform->add_hidden('signature_id', $this->signatureItem->id );
    $this->editform->add_hidden('petition', $this->signatureItem->vars['petition']);

    /* build button list */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('openTab'=>'categories')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));

    /* set interface title */
    $this->adminTitle = $this->title
      .$camyks->get_translation('formitem_separator')
      .$this->get_translation('signatureid', $this->signatureItem->id);

    /* update layout */
    $this->selected_layout = 'admin_edit_signature.html.inc';
  }
  
  /*
   * init module object in admin/save_signature mode
   * @return void
   * @access private
   */
  function init_admin_save_signature() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* check signature id */
    if(!isset($_REQUEST['signature_id']))
      return $this->init_admin_main();
    $signature_id = $_REQUEST['signature_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save signature */
    $this->signatureItem->id = $signature_id;
    $this->signatureItem->get_fromHeader();
    if ( $this->signatureItem->save() )
      $this->text = $this->get_translation('signature_saved');
    else
      $this->text = $this->get_translation('signature_notsaved');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('openTab'=>'categories')));
  }
  
  /*
   * init module object in admin/delete_signature mode
   * @return void
   * @access private
   */
  function init_admin_delete_signature() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* check signature id */
    if(!isset($_REQUEST['signature_id']))
      return $this->init_admin_main();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* delete signature */
    $this->signatureItem->id = $_REQUEST['signature_id'];
    $this->signatureItem->get();
    $this->signatureItem->get_fromItems();

    $p_id = $this->signatureItem->vars['petition_id'];

    if ( $this->signatureItem->delete())
      $this->text = $this->get_translation('signature_deleted');
    else
      $this->text = $this->get_translation('signature_notdeleted');
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('mode'=>'list_signature', 'petition_id'=>$p_id)));
  }

  /* specific request mode methods */

  /*
   * export results
   * @param string $where
   * @return void
   * @access private
   */
  function execute_request_exportXLS() {
    global $camyks;

    /* load petition item */
    if( !isset($_REQUEST['petition_id'])) {
      /* throw fatal error */
      $error = array('title'=>$this->get_translation('fatalerror_undefinedpetition'),
		     'description'=>$this->get_translation('fatalerror_'));
      $camyks->throwFatalError( $error );
    }
    $this->petitionItem->id = $_REQUEST['petition_id'];
    $this->petitionItem->get();
    $this->petitionItem->get_fromItems($camyks->current_language);
    
    /* load external data */
    countries_loadLocales();

    /* load excel writer library */
    require_once('Spreadsheet/Excel/Writer.php');
    
    /* prepare sql query */
    $params = array('status'=>1, 'petition'=>$this->petitionItem->id, 'order'=>'signdate', 'orderway'=>'asc');
    $where = $this->signatureItem->build_whereStatement($params);
    $sql = $this->signatureItem->get_objectList_databaseItemsSQLQuery($where, -1, -1, $params['order'], $params['orderway']);
    
    /* Creating a workbook */
    $workbook = new Spreadsheet_Excel_Writer();

    /* sending HTTP headers */
    $workbook->send($this->petitionItem->vars['title'].'-'.strftime('%Y-%m-%d').'.xls');

    /* Creating a worksheet */
    $worksheet =& $workbook->addWorksheet($this->get_translation('export_signatures'));
    
    /* creates formats */
    $header = &$workbook->addFormat();
    $header->setBold(700);
    
    $sday = 86400;
    $tdiff = $sday * 25569;
    
    $sdate = &$workbook->addFormat();
    $sdate->setNumFormat('D/M/YY');
    
    $ldate = &$workbook->addFormat();
    $ldate->setNumFormat('D/M/YY h:mm');
    
    /* add header line */
    $c = 0;
    $worksheet->write(0, $c++, '#', $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('export_signdate'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('civility'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('firstname'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('lastname'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('email'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('address'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('zipcode'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('city'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('country'))), $header);
    $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('export_birthdate'))), $header);
    
    /* add sign data */
    $cnt = 0;
    $l = 1;
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get data from database */
      while ( $data = mysql_fetch_assoc( $req )) {
	$c = 0;
	$worksheet->write($l, $c++, ++$cnt);
	$worksheet->write($l, $c++, number_format(($data['signdate'] + $tdiff) / $sday, 6,'.', ''), $ldate);
	$worksheet->write($l, $c++, $data['title']);
	$worksheet->write($l, $c++, utf8_decode($data['firstname']));
	$worksheet->write($l, $c++, utf8_decode($data['lastname']));
	$worksheet->write($l, $c++, $data['email']);
	$worksheet->write($l, $c++, utf8_decode($data['address']));
	$worksheet->write($l, $c++, ' '.$data['zipcode']);
	$worksheet->write($l, $c++, utf8_decode($data['city']));
	$worksheet->write($l, $c++, ($data['country']!=''?countries_getTranslation($data['country']):''));
	$worksheet->write($l, $c++, number_format(($data['birthdate'] + $tdiff) / $sday, 6,'.', ''), $sdate);
	$l++;
      }
    }

    /* send the file */
    $workbook->close();
  }

  /* specific admin tool methods */

  /*
   * return signature status list
   * @return array
   * @access public
   */
  function get_signatureStatusList() {
    return $this->signatureItem->get_statusList();
  }

  /*
   * return signatures status list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_signaturesStatusList($full=false) {
    return $this->signatureItem->get_multiStatusList($full);
  }

  /*
   * return signature list
   * @param array $params
   * @return array
   * @access public
   */
  function get_signatureList($params=array()) {
    return $this->signatureItem->get_list($params);
  }
  
  /*
   * return signature title list
   * @param boolean $full
   * @param array $params
   * @return array
   * @access public
   */
  function get_signatureTitleList($full=false, $params=array()) {
    if (!isset($params['language']))
      $params['language'] = $this->get_adminEditionLanguage();

    $list = $this->signatureItem->get_titleList($params);
    if ($full)
      $list = array(0=>$this->get_translation('signaturetitle_all'))+ $list;
    return $list;
  }

  /*
   * return petition status list
   * @return array
   * @access public
   */
  function get_petitionStatusList() {
    return $this->petitionItem->get_statusList();
  }
  
  /*
   * return petitions status list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_petitionsStatusList($full=false) {
    return $this->petitionItem->get_multiStatusList($full);
  }

  /*
   * return petition type list
   * @return array
   * @access public
   */
  function get_petitionTypeList() {
    return $this->petitionItem->get_typeList();
  }
  
  /*
   * return petitions type list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_petitionsTypeList($full=false) {
    return $this->petitionItem->get_multiTypeList($full);
  }

  /*
   * return petition title list
   * @param array $params
   * @return array
   * @access public
   */
  function get_petitionTitleList($params=array()) {
    return $this->petitionItem->get_titleList($params);
  }

  /*
   * return petition list
   * @param array $params
   * @return array
   * @access public
   */
  function get_petitionList($params=array()) {
    return $this->petitionItem->get_list($params);
  }

  /*
   * return petition count
   * @param array $params
   * @return array
   * @access public
   */
  function count_petitions($params=array()) {
    return $this->petitionItem->count($params);
  }

  /*
   * return signs count by given petition
   * @param array $petitions
   * @return array
   * @access public
   */
  function count_signsByPetitions($petitions) {
    return $this->signatureItem->count_byPetitions($petitions);
  }
}
?>