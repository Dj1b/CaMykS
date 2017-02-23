<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Jul 2010
 * Last Modif Date  : Jul 2010
 * History :
 * * 10-07-13 : Initial files
 * 
 * Admin_GenericDirectoryManager
 */

class Admin_GenericDirectoryManager extends Module {
  /* variables */
  var $config;
  var $contactItem;
  var $categoryItem;
  var $contactList;
  var $categoryList;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GenericDirectoryManager ( $path_type ) {
    parent::Module('Admin_GenericDirectoryManager', $path_type);
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
    $this->libs[] = 'Admin_GenericDirectoryManagerContact.php.inc';
    $this->libs[] = 'Admin_GenericDirectoryManagerCategory.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->contactItem = new Admin_GenericDirectoryManagerContact(0, $this);
    $this->categoryItem = new Admin_GenericDirectoryManagerCategory(0, $this);

    /* initialise plugin variables */
    $this->contactList = null;
    $this->categoryList = null;
  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ( $this->contactItem->install() 
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
    return $this->contactItem->is_installed();
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
    $this->rights[1] = array('name'=>'category',
			     'title'=> $this->get_translation('rights_category'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'contact',
			     'title'=> $this->get_translation('rights_contact'),
			     'default'=> false);
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
    case 'edit_contact':
      /* mode == edit_contact */
      $this->init_admin_edit_contact();
      break;
    case 'save_contact':
      /* mode == save_contact */
      $this->init_admin_save_contact();
      break;
    case 'delete_contact':
      /* mode == delete_contact */
      $this->init_admin_delete_contact();
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
    
    /* build contact tab */
    $this->load_file('lib/Admin_GenericDirectoryManagerContactListParams.php.inc');
    $this->listContact = new AdminItemListViewer('camyks');
    $this->listContact->set_params($this->contactListParams);
    $this->listContact->initialise();
    
    /* build category tab */
    if ( $this->check_right(1) === true ) {
      $this->load_file('lib/Admin_GenericDirectoryManagerCategoryListParams.php.inc');
      $this->listCategory = new AdminItemListViewer('camyks');
      $this->listCategory->set_params($this->categoryListParams);
      $this->listCategory->initialise();
      
      /* get categories id */
      $categoryIDs = array_keys($this->listCategory->objectList);
      $cnts = $this->contactItem->count_byCategories($categoryIDs);
      foreach( $this->listCategory->objectList as $id => $category)
	$this->listCategory->objectList[$id]->vars['contacts'] = isset($cnts[$id])?$cnts[$id]:0;
    }
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    /* add contacts tab */
    $this->tabBuilder->add_tab(array('name'=>'contacts',
				     'title'=>$this->get_translation('tabcontacts')));
    /* add categories tab */
    if ( $this->check_right(1) === true )
      $this->tabBuilder->add_tab(array('name'=>'categories',
				       'title'=>$this->get_translation('tabcategories')));
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'contacts'));
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
  }
  
  /*
   * init module object in admin/edit_contact mode
   * @return void
   * @access private
   */
  function init_admin_edit_contact() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();
    $this->lgs = $camyks->get_confValue('editing_languages');
    
    /* get contact item */
    $contact_id = isset($_REQUEST['contact_id'])?$_REQUEST['contact_id']:0;
    $this->contactItem->id = $contact_id;
    $this->contactItem->get();
    $this->contactItem->get_fromItems();
    
    /* get data */
    $this->categoryList = $this->get_categoryTitleList();
    
    /* get form */
    $this->editform = new HTMLForm('edit_contact',
				   $camyks->get_adminlink( $this->name, array('mode'=>'save_contact')),
				   'POST');
    $this->editform->add_hidden('contact_id', $this->contactItem->id );
    $this->editform->set_object($this->contactItem);
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
		/* add contacts tab */
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
    $this->tabBuilder->initialise(array('default'=>'contacts'));
    
    /* load editor */
    $this->editor = &$camyks->inputs['TinyMCEv3'];
    $this->editor->initialise();
    
    /* initialise page chooser */
    $this->add_JSFile('glossarymanager.js');
    $link = $camyks->get_confValue('url').'/request.php?module=Admin_ContentPage';
    $this->add_JSScript('pc2 = new PageChooser("pagename", "glossarymanager_updateButtonLink", "'.$link.'");');
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->contactItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('contactnew');
    else
      $this->adminTitle .= $this->get_translation('contactid', $this->contactItem->id);
    
    /* build button list */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_contact.html.inc';
  }
  
  /*
   * init module object in admin/save_contact mode
   * @return void
   * @access private
   */
  function init_admin_save_contact() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* check contact id */
    if ( !isset($_REQUEST['contact_id']))
      return $this->init_admin_main();
    $contact_id = $_REQUEST['contact_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save contact */
    $this->contactItem->id = $contact_id;
    $this->contactItem->get_fromHeader();
    if ( $this->contactItem->save() )
      $this->text = $this->get_translation('contact_saved');
    else
      $this->text = $this->get_translation('contact_notsaved');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }
  
  /*
   * init module object in admin/delete_contact mode
   * @return void
   * @access private
   */
  function init_admin_delete_contact() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed () ;

    /* check contact id */
    if ( !isset($_REQUEST['contact_id']))
      return $this->init_admin_main();
    $contact_id = $_REQUEST['contact_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* delete contact */
    $this->contactItem->id = $contact_id;
    if ( $this->contactItem->delete())
      $this->text = $this->get_translation('contact_deleted');
    else
      $this->text = $this->get_translation('contact_notdeleted');
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink());
  }
  
  /*
   * init module object in admin/edit_category mode
   * @return void
   * @access private
   */
  function init_admin_edit_category() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
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
    if ( $this->check_right(1) === false )
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
      $this->text = $this->get_translation('category_notsaved');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('openTab'=>'categories')));
  }
  
  /*
   * init module object in admin/delete_category mode
   * @return void
   * @access private
   */
  function init_admin_delete_category() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(1) === false )
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
      $this->text = $this->get_translation('category_notdeleted');
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('openTab'=>'categories')));
  }

  /* specific admin tool methods */

  /*
   * return category status list
   * @return array
   * @access public
   */
  function get_categoryStatusList() {
    return $this->categoryItem->get_statusList();
  }

  /*
   * return categories status list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_categoriesStatusList($full=false) {
    return $this->categoryItem->get_multiStatusList($full);
  }
  
  /*
   * return category title list
   * @param boolean $full
   * @param array $params
   * @return array
   * @access public
   */
  function get_categoryTitleList($full=false, $params=array()) {
    if (!isset($params['language']))
      $params['language'] = $this->get_adminEditionLanguage();

    $list = $this->categoryItem->get_titleList($params);
    if ($full)
      $list = array(0=>$this->get_translation('categorytitle_all'))+ $list;
    return $list;
  }

  /*
   * return contact status list
   * @return array
   * @access public
   */
  function get_contactStatusList() {
    return $this->contactItem->get_statusList();
  }
  
  /*
   * return contacts status list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_contactsStatusList($full=false) {
    return $this->contactItem->get_multiStatusList($full);
  }

  /*
   * return contact list
   * @param array $params
   * @return array
   * @access public
   */
  function get_contactList($params=array()) {
    return $this->contactItem->get_list($params);
  }

  /*
   * return contact count
   * @param array $params
   * @return array
   * @access public
   */
  function count_contacts($params=array()) {
    return $this->contactItem->count($params);
  }
}
?>