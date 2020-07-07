<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version	: 1.0.1
 * Object Type          : Plugin / Module Engine
 * Create Date		: May 2008
 * Last Modif Date	: Jul 2020
 * History :
 * * 08-05-05 : Initial files
 * * 08-05-28 : Disable admin menu for data I/O modes
 *
 * Admin_GenericDownloadManager
 */

class Admin_GenericDownloadManager extends Module {
  /* variables */
  var $config;
  var $documentItem;
  var $categoryItem;
  var $documentList;
  var $categoryList;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GenericDownloadManager ( $path_type ) {
  	global $camyks;
    parent::Module('Admin_GenericDownloadManager', $path_type);
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
    $this->libs[] = 'Admin_GenericDownloadManagerConfig.php.inc';
    $this->libs[] = 'Admin_GenericDownloadManagerDocument.php.inc';
    $this->libs[] = 'Admin_GenericDownloadManagerCategory.php.inc';
    $this->get_PHPLibs();

    /* initialise plugin libraries */
    $this->config = new Admin_GenericDownloadManagerConfig('config', $this);
    $this->documentItem = new Admin_GenericDownloadManagerDocument(0, $this);
    $this->categoryItem = new Admin_GenericDownloadManagerCategory(0, $this);

    /* initialise plugin variables */
    $this->documentList = null;
    $this->categoryList = null;

    /* TinyMCE Extension */
    if ($camyks->mode == CAMYKS_MODE_ADMIN)
    	$this->register_asExtension('TinyMCEv3');
  }

  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->config->install() and $this->documentItem->install()
	    and $this->categoryItem->install() and parent::install());
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
    return $this->documentItem->is_installed();
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
    $this->rights[1] = array('name'=>'config',
			     'title'=> $this->get_translation('rights_config'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'category',
			     'title'=> $this->get_translation('rights_category'),
			     'default'=> false);
    $this->rights[3] = array('name'=>'document',
			     'title'=> $this->get_translation('rights_document'),
			     'default'=> false);
  }

  /*
   * return file names for statistics tools
   * @param array $items
   * @param string $type
   * @return array
   * @access private
   */
  function get_adminStatisticsValueTitles ( $items, $type=null ) {
    /* check given items */
    if ( count($items) == 0 )
      return array();

    /* get files names */
    switch ( $type ) {
    case 'genericdownload':
      $doc_objects = $this->documentItem->get_titlesList('objectid in ('.implode(',', $items).')');
      foreach ( $items as $item ) {
	if ( isset ( $doc_objects[$item] ) ) {
	  $items[$item] = $doc_objects[$item];
	}
      }
      return $items;
      break;
    default:
      return $items;
    }
  }

  /*
   * return TinyMCE plugin params
   * @return array
   * @access public
   */
  function get_tinyMCEPluginParams() {
  	global $camyks;
  	$this->add_JSFile('tinymce_plugin/editor_plugin.js');
  	$this->add_JSFile('tinymce_plugin/langs/'.$camyks->current_language.'.js');
  	return array(
    		'name'=>'genericdownloadmanager',
    		'buttons'=>array('insertDownloadLink'));
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

    /* load config */
    $this->config->get();

    /* get informations */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'main' );

    switch ( $this->mode ) {
    case 'edit_config':
      /* mode == edit_config */
      $this->init_admin_edit_config();
      break;
    case 'save_config':
      /* mode == save_config */
      $this->init_admin_save_config();
      break;
    case 'edit_category':
      /* mode == edit_category */
      $this->init_admin_edit_category();
      break;
    case 'save_category':
      /* mode == save_category */
      $this->init_admin_save_category();
      break;
    case 'delete_category':
      /* mode == delete_category */
      $this->init_admin_delete_category();
      break;
    case 'edit_document':
      /* mode == edit_document */
      $this->init_admin_edit_document();
      break;
    case 'save_document':
      /* mode == save_document */
      $this->init_admin_save_document();
      break;
    case 'delete_document':
      /* mode == delete_document */
      $this->init_admin_delete_document();
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

    /* build error */
    $this->error = array('title'=>$this->get_translation('downloaderrortitle'),
		   'description'=>$this->get_translation('downloaderrordesc'),
		   'content1'=>$this->get_translation('downloaderrorcnt1'));

    /* Load config */
    $this->config->get();

    /* check file to download */
    if (isset($_REQUEST['did']))
    	return $this->execute_request_downloadFile();

    /* check action to execute */
    if( isset($_REQUEST['action'])) {
    	switch($_REQUEST['action']) {
    		case 'loadData':
    			return $this->execute_request_loadData();
    	}
		}

    /* throw fatal error */
    $camyks->throwFatalError( $this->error );
  }


  /* specific admin mode methods */

  /*
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  function init_admin_main() {
    global $camyks;

    /* get help */
    $this->get_help();

    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();

    /* build document tab */
    $this->load_file('lib/Admin_GenericDownloadManagerDocumentListParams.php.inc');
    $this->listDocument = new AdminItemListViewer('camyks');
    $this->listDocument->set_params($this->documentListParams);
    $this->listDocument->initialise();

    /* build category tab */
    if ( $this->check_right(2) === true ) {
      $this->load_file('lib/Admin_GenericDownloadManagerCategoryListParams.php.inc');
      $this->listCategory = new AdminItemListViewer('camyks');
      $this->listCategory->set_params($this->categoryListParams);
      $this->listCategory->initialise();

      /* get categories id */
      $categoryIDs = array_keys($this->listCategory->objectList);
      $cnts = $this->documentItem->get_documentCountByCategories($categoryIDs);
      foreach( $this->listCategory->objectList as $id => $category)
	    $this->listCategory->objectList[$id]->vars['docs'] = isset($cnts[$id])?$cnts[$id]:0;
    }

    /* build config tab */
    if ( $this->check_right(3) === true ) {
      $this->configLinkModeList = $this->get_configLinkModeList();
    }

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    /* add configuration tab */
    if ( $this->check_right(1) === true )
      $this->tabBuilder->add_tab(array('name'=>'configuration',
				       'title'=>$this->get_translation('tabconfiguration')));
    /* add categories tab */
    if ( $this->check_right(2) === true )
      $this->tabBuilder->add_tab(array('name'=>'categories',
				       'title'=>$this->get_translation('tabcategories')));
    /* add documents tab */
    $this->tabBuilder->add_tab(array('name'=>'documents',
				     'title'=>$this->get_translation('tabdocuments')));
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'documents'));

    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }

  /*
   * init module object in admin/edit_config mode
   * @return void
   * @access private
   */
  function init_admin_edit_config() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* build config form */
    $this->configform = new HTMLForm('configform',
				     $camyks->get_adminLink($this->name, array('mode' => 'save_config')),
				     'POST');
    $this->configform->set_object($this->config);

    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->configform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    /* set interface title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('editconfig_title');

    /* update layout */
    $this->selected_layout = 'admin_edit_config.html.inc';
  }

  /*
   * init module object in admin/save_config mode
   * @return void
   * @access private
   */
  function init_admin_save_config() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(1) === false )
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* save config */
    $this->config->get_fromHeader();
    if ( $this->config->save() ) {
      $this->text = $this->get_translation('config_saved');
    } else {
      $this->text = $this->get_translation('config_not_saved');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }

  /*
   * init module object in admin/edit_document mode
   * @return void
   * @access private
   */
  function init_admin_edit_document() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed();

    /* get language to use with content */
    $lg = $this->get_adminEditionLanguage();

    /* get document item */
    $document_id = isset($_REQUEST['document_id'])?$_REQUEST['document_id']:0;
    $this->documentItem->id = $document_id;
    $this->documentItem->get();
    $this->documentItem->get_fromItems();

    /* get data */
    $this->categoryList = $this->get_categoryTitleList();

    /* get form */
    $this->editform = new HTMLForm('edit_document',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_document')),
				   'POST');
    $this->editform->allow_files(true, $this->config->vars['file_size']*1024*1024 );
    $this->editform->add_hidden('document_id', $this->documentItem->id );
    if ($this->documentItem->id == 0
	or $this->documentItem->vars['security'] == '')
      $this->editform->add_hidden('update_security', 1);
    $this->editform->set_object($this->documentItem);

    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->documentItem->id == 0 )
      $this->adminTitle .= $this->get_translation('documentnew');
    else
      $this->adminTitle .= $this->get_translation('documentid', $this->documentItem->id);

    /* build button list */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));

    /* update layout */
    $this->selected_layout = 'admin_edit_document.html.inc';
  }

  /*
   * init module object in admin/save_document mode
   * @return void
   * @access private
   */
  function init_admin_save_document() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed();

    /* check document id */
    if ( !isset($_REQUEST['document_id']))
      return $this->init_admin_main();
    $document_id = (int)$_REQUEST['document_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* save document */
    $this->documentItem->id = $document_id;
    $this->documentItem->get_fromHeader();
    if ( $this->documentItem->save() )
      $this->text = $this->get_translation('document_saved');
    else
      $this->text = $this->get_translation('document_not_saved');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }

  /*
   * init module object in admin/delete_document mode
   * @return void
   * @access private
   */
  function init_admin_delete_document() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(3) === false )
      return $this->init_admin_actionNotAllowed () ;

    /* check document id */
    if ( !isset($_REQUEST['document_id']))
      return $this->init_admin_main();
    $document_id = (int)$_REQUEST['document_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* delete document */
    $this->documentItem->id = $document_id;
    if ( $this->documentItem->delete())
      $this->text = $this->get_translation('document_deleted');
    else
      $this->text = $this->get_translation('document_not_deleted');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }

  /*
   * init module object in admin/edit_category mode
   * @return void
   * @access private
   */
  function init_admin_edit_category() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed () ;

    /* get category item */
    $category_id = isset($_REQUEST['category_id'])?$_REQUEST['category_id']:0;
    $this->categoryItem->id = $category_id;
    $this->categoryItem->get();
    $this->categoryItem->get_fromItems();

    /* get form */
    $this->editform = new HTMLForm('edit_category',
				   $this->get_adminlink(array('mode'=>'save_category')),
				   'POST');
    $this->editform->set_object($this->categoryItem);
    $this->editform->add_hidden('category_id', $this->categoryItem->id );

    /* build button list */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('openTab'=>'categories')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));

    /* set interface title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->categoryItem->id == 0 )
      $this->adminTitle .= $this->get_translation('newcategory');
    else
      $this->adminTitle .= $this->get_translation('categoryid', $this->categoryItem->id);

    /* update layout */
    $this->selected_layout = 'admin_edit_category.html.inc';
  }

  /*
   * init module object in admin/save_category mode
   * @return void
   * @access private
   */
  function init_admin_save_category() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* check category id */
    if(!isset($_REQUEST['category_id']))
      return $this->init_admin_main();
    $category_id = $_REQUEST['category_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* save category */
    $this->categoryItem->id = $category_id;
    $this->categoryItem->get_fromHeader();
    if ( $this->categoryItem->save() )
      $this->text = $this->get_translation('category_saved');
    else
      $this->text = $this->get_translation('category_not_saved');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'categories')));
  }

  /*
   * init module object in admin/delete_category mode
   * @return void
   * @access private
   */
  function init_admin_delete_category() {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* check category id */
    if(!isset($_REQUEST['category_id']))
      return $this->init_admin_main();
    $category_id = $_REQUEST['category_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* delete category */
    $this->categoryItem->id = $category_id;
    if ( $this->categoryItem->delete())
      $this->text = $this->get_translation('category_deleted');
    else
      $this->text = $this->get_translation('category_not_deleted');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'categories')));
  }

  /* request mode methods */

  /*
   * return selected file as download
   * @return void
   * @access private
   */
  function execute_request_downloadFile() {
  	global $camyks;

  	/* load parameters */
    $fid = (int)$_REQUEST['did'];
    $sid = isset($_REQUEST['sid'])?addslashes($_REQUEST['sid']):'';

    /* load CaMykS */
    $camyks->get_siteInit();

    /* check if module is installed */
    if (!$this->is_installed())
      $camyks->throwFatalError($this->error);

    /* get document object */
    $this->documentItem->id = $fid;
    $this->documentItem->get(true);
    $this->documentItem->get_fromItems();

    /* check security code */
    if ($this->config->vars['link_mode'] == 1
	 and $this->documentItem->vars['security'] != $sid)
      $camyks->throwFatalError($this->error);

    /* check document object */
    if ($this->documentItem->vars['active'] == 0)
      $camyks->throwFatalError($this->error);

    /* check document file */
    $file = new FSFile( $this->documentItem->vars['file'] );
    if ($file->exists === false)
      $camyks->throwFatalError($this->error);

    /* update statistics */
    $camyks->update_statistic('genericdownload', $this->name, 'mixed', $this->documentItem->id, '', '' );

    /* download file */
    if ($this->documentItem->vars['filetitle'] != '')
      $file->download($this->documentItem->vars['filetitle']);
    else
      $file->download();
  }

  /*
   * return selected file as download
   * @return void
   * @access private
   */
  function execute_request_loadData() {
  	global $camyks;

    /* get database connection */
    $camyks->get_databaseConnection();
    $camyks->add_generic_translation();

    /* get default language */
    $lg = $this->get_adminEditionLanguage();

		/* init result */
		$result = array('result'=>'success',
										'categories'=>array(),
										'documents'=>array());

		/* get category list */
		$list = $this->categoryItem->get_nameList('title', 'active=1', $lg);
		foreach ($list as $id=>$item)
			$result['categories'][] = array('id'=>$id, 'title'=>$item);

    /* get document list */
    $list = $this->documentItem->get_objectList($lg, 'active=1');
    foreach ($list as $id=>$item)
    	$result['documents'][] = array('id'=>$id,
    		'title'=> string_html2text($item->vars['title'].' ('.$item->get_fileInfos().')'),
    		'category'=> $item->vars['category'],
    		'link'=> $item->get_link());

     /* send XML */
    header("Content-type: text/xml");
    echo xml_serialize2XML( $result );
	}

  /* specific admin tool methods */

  /*
   * return category status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_categoryStatusList($full=false) {
    $list = array();
    if ($full)
      $list['-1'] = $this->get_translation('categorystatus_all');
    $list['0'] = $this->get_translation('categorystatus_inactive');
    $list['1'] = $this->get_translation('categorystatus_active');
    return $list;
  }

  /*
   * return status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_categoryTitleList($full=false) {
    $list = $this->categoryItem->get_nameList('title', '', $this->get_adminEditionLanguage());
    if ($full)
      $list = array('-1'=>$this->get_translation('categorystatus_all'))+ $list;
    return $list;
  }

  /*
   * return document status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_documentStatusList($full=false) {
    $list = array();
    if ($full)
      $list['-1'] = $this->get_translation('documentstatus_all');
    $list['0'] = $this->get_translation('documentstatus_inactive');
    $list['1'] = $this->get_translation('documentstatus_active');
    return $list;
  }

  /*
   * return language list
   * @return array
   * @access private
   */
  function get_languageList() {
    global $camyks;
    $list = array();
    $list[''] = $this->get_translation('document_language_all');
    foreach($camyks->_conf['editing_languages'] as $l)
      $list[$l] = $camyks->get_translation('lang_'.$l);
    return $list;
  }

  /*
   * return configuration link mode list
   * @return array
   * @access private
   */
  function get_configLinkModeList() {
    $list = array();
    $list[0] = $this->get_translation('configlinkmode_simple');
    $list[1] = $this->get_translation('configlinkmode_secure');
    return $list;
  }
}
?>
