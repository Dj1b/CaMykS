<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Jun 2015
 * Last Modif Date	: Nov 2017
 * History :
 * * 15-06-24 : Initial files
 * 
 * Admin_GenericMediaLibraryManager
 */

class Admin_GenericMediaLibraryManager extends Module {
  /* variables */
  var $config;
  var $documentItem;
  var $pictureGalleryItem;
  var $documentList;
  var $categoryList;
  
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GenericMediaLibraryManager ( $path_type ) {
  	global $camyks;
    parent::Module('Admin_GenericMediaLibraryManager', $path_type);
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
    $this->libs[] = 'Admin_GenericMediaLibraryManagerConfig.php.inc';
    $this->libs[] = 'Admin_GenericMediaLibraryManagerPictureGallery.php.inc';
    $this->libs[] = 'Admin_GenericMediaLibraryManagerPicture.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->config = new Admin_GenericMediaLibraryManagerConfig('config', $this);
    $this->pictureGalleryItem = new Admin_GenericMediaLibraryManagerPictureGallery(0, $this);
    $this->pictureItem = new Admin_GenericMediaLibraryManagerPicture(0, $this);

    /* initialise plugin variables */
    $this->pictureGalleryList = null;
    $this->pictureList = null;

  }
  
  /* overwrite Module methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->config->install() and $this->pictureItem->install() 
	    and $this->pictureGalleryItem->install() and parent::install());
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
    return $this->pictureItem->is_installed();
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
			     'title'=> $this->get_translation('rights_picturegalleries'),
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
    case 'view_pictureGallery':
      /* mode == view_pictureGallery */
      $this->init_admin_view_pictureGallery();
      break;
    case 'edit_pictureGallery':
      /* mode == edit_pictureGallery */
      $this->init_admin_edit_pictureGallery();
      break;
    case 'save_pictureGallery':
      /* mode == save_pictureGallery */
      $this->init_admin_save_pictureGallery();
      break;
    case 'delete_pictureGallery':
      /* mode == delete_pictureGallery */
      $this->init_admin_delete_pictureGallery();
      break;
    case 'edit_picture':
      /* mode == edit_picture */
      $this->init_admin_edit_picture();
      break;
    case 'save_picture':
      /* mode == save_picture */
      $this->init_admin_save_picture();
      break;
    case 'delete_picture':
      /* mode == delete_picture */
      $this->init_admin_delete_picture();
      break;
    case 'moveUp_picture':
      /* mode == moveUp_picture */
      $this->init_admin_moveUp_picture();
      break;
    case 'moveDown_picture':
      /* mode == moveDown_picture */
      $this->init_admin_moveDown_picture();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
    }
    
    parent::init_admin();
  }
  
  /*
   * execute module object in request mode
   * @return void
   * @access private
   */
  function execute_request() {
    global $camyks;
    
    /* build error message */
    $error = array('title'=>$this->get_translation('downloadfailed'),
		     'description'=>$this->get_translation('downloaderror'),
		     'content1'=>$this->get_translation('downloaderror2'));
    
    /* load mode to execute */
    $mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    
    /* execute mode */
    switch ($mode) {
      case 'optimisePictureImage':
        $this->execute_request_optimisePictureImage(); break;
      case 'optimisePictureThumb':
        $this->execute_request_optimisePictureThumb(); break;
      default :
	    /* throw fatal error */
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
    
    /* get help */
    $this->get_help();
    
    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();
    
    /* build picture galleries tab */
    $this->load_file('lib/Admin_GenericMediaLibraryManagerPictureGalleryListParams.php.inc');
    $this->pictureGalleryList = new AdminItemListViewer('camyks');
    $this->pictureGalleryList->set_params($this->pictureGalleryListParams);
    $this->pictureGalleryList->initialise();
    
    /* update picture count in galleries */
    $galleryIds = array_keys($this->pictureGalleryList->objectList);
    $cnts = $this->pictureItem->get_pictureCountByGalleries($galleryIds);
    foreach( $this->pictureGalleryList->objectList as $id => $gallery)
	  $this->pictureGalleryList->objectList[$id]->vars['pictures'] = isset($cnts[$id])?$cnts[$id]:0;
    
    /* build configuration tab */
    $this->configResizeModeList = $this->get_configResizeModeList();
    $this->configFileTypeList = $this->get_configFileTypeList();
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    
    /* add picture galleries tab */
    $this->tabBuilder->add_tab(array('name'=>'PictureGalleries',
				     'title'=>$this->get_translation('tabpicturegalleries')));
	
	/* add configuration tab */
    if ( $this->check_right(1) === true )
      $this->tabBuilder->add_tab(array('name'=>'Configuration',
				       'title'=>$this->get_translation('tabconfiguration')));
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'PictureGalleries'));
    
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
   
    /* load data */
    $this->configResizeModeList = $this->get_configResizeModeList();
    $this->configFileTypeList = $this->get_configFileTypeList();

    /* get buttons */
    $this->buttons = array(array('link'=>$this->get_adminLink(),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->configform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    /* set interface title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('edit_config');
    
    /* update layout */
    $this->selected_layout = 'configuration/admin_edit.html.inc';
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
      $this->text = $this->get_translation('config_notsaved');
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink(array('openTab'=>'Configuration')));
  }
  
  /*
   * init module object in admin/view_pictureGallery mode
   * @return void
   * @access private
   */
  function init_admin_view_pictureGallery() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();
    
    /* get pictureGallery item */
    $this->pictureGalleryItem->id = isset($_REQUEST['pictureGallery_id'])?(int)$_REQUEST['pictureGallery_id']:0;
    $this->pictureGalleryItem->get();
    $this->pictureGalleryItem->get_fromItems();
    
    /* no selected gallery, try to create new one */
    if ( $this->pictureGalleryItem->id == 0) 
      $this->init_admin_edit_pictureGallery();
    
    /* load pictures list */
    $this->load_file('lib/Admin_GenericMediaLibraryManagerPictureListParams.php.inc');
    $this->pictureList = new AdminItemListViewer('camyks');
    $this->pictureList->set_params($this->pictureListParams);
    $this->pictureList->initialise();
    
    /* load data */
    $this->pictureGalleryStatusList = $this->get_pictureGalleryStatusList();
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    
    /* add picture galleries tab */
    $this->tabBuilder->add_tabs(array(
        array('name'=>'Properties',
		      'title'=>$this->get_translation('tabproperties')),
        array('name'=>'Pictures',
		      'title'=>$this->get_translation('pictures')),
    ));
	
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'Properties'));
    
    /* check preview max width */
    $this->previewWidth = min(250, $this->get_configValue('picture_thumbWidth'));
    
    /* add scripts */
	$this->add_JSFile('PictureList.js');
    $this->add_JSScript('var pl = new PictureList("pl");');
    $this->add_JSScript('pl.set_param("previewMaxWidth", '.$this->previewWidth.');');
    $this->add_JSScript('pl.set_param("picturesURL", new Array());');
    if (count($this->pictureList->objectList) > 0) {
      foreach ($this->pictureList->objectList as $img) {
        $this->add_JSScript('pl.set_param("picturesURL", '.$img->id.', "'.$img->vars['thumb'].'");');
      }
    }
    $this->add_JSLoadScript('pl.initialise();');
    
    /* build button list */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('openTab'=>'PictureGalleries')),
				                 'title'=>$camyks->get_translation('back')));

    /* set interface title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('pictureGalleryid', $this->pictureGalleryItem->id);

    /* update layout */
    $this->selected_layout = 'admin_view_pictureGallery.html.inc';
  }
  
  
  /*
   * init module object in admin/edit_pictureGallery mode
   * @return void
   * @access private
   */
  function init_admin_edit_pictureGallery() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* get language to use with content */
    $this->language = $this->get_adminEditionLanguage();
    
    /* get pictureGallery item */
    $pictureGallery_id = isset($_REQUEST['pictureGallery_id'])?(int)$_REQUEST['pictureGallery_id']:0;
    $this->pictureGalleryItem->id = $pictureGallery_id;
    $this->pictureGalleryItem->get();
    $this->pictureGalleryItem->get_fromItems();
 
    /* get form */
    $this->editform = new HTMLForm('edit_pictureGallery',
				   $this->get_adminlink(array('mode'=>'save_pictureGallery')),
				   'POST'); 
    $this->editform->set_object($this->pictureGalleryItem);
    $this->editform->add_hidden('pictureGallery_id', $this->pictureGalleryItem->id );
    
    /* load pictures list */
    $this->load_file('lib/Admin_GenericMediaLibraryManagerPictureSelectionListParams.php.inc');
    $this->pictureList = new AdminItemListViewer('camyks');
    $this->pictureList->set_params($this->pictureListParams);
    $this->pictureList->initialise();
    
    /* load data */
    $this->pictureGalleryStatusList = $this->get_pictureGalleryStatusList();
    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    
    /* add picture galleries tab */
    $this->tabBuilder->add_tabs(array(
        array('name'=>'Properties',
		      'title'=>$this->get_translation('tabproperties')),
        array('name'=>'Pictures',
		      'title'=>$this->get_translation('defaultpicture')),
    ));
    foreach ($camyks->_conf['editing_languages'] as $l ) {
    	$this->tabBuilder->add_tab(array('name'=>$l,
				       'title'=>language_getIcon($l)));
	}
	
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'Properties'));
    
    /* get editor input */
    $this->input = &$camyks->inputs['TinyMCEv3'];
    $this->input->initialise();
    
    /* check preview max width */
    $this->previewWidth = min(250, $this->get_configValue('picture_thumbWidth'));
    
    /* add scripts */
	$this->add_JSFile('PictureList.js');
    $this->add_JSScript('var pl = new PictureList("pl");');
    $this->add_JSScript('pl.set_param("previewMaxWidth", '.$this->previewWidth.');');
    $this->add_JSScript('pl.set_param("picturesURL", new Array());');
    if (count($this->pictureList->objectList) > 0) {
      foreach ($this->pictureList->objectList as $img) {
        $this->add_JSScript('pl.set_param("picturesURL", '.$img->id.', "'.$img->vars['thumb'].'");');
      }
    }
    $this->add_JSLoadScript('pl.initialise();');

    /* set interface title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->pictureGalleryItem->id == 0 ) {
      $this->adminTitle .= $this->get_translation('newpictureGallery');
      $this->buttons = array(array('link'=>$this->get_adminLink(array('openTab'=>'PictureGalleries')),
				 'title'=>$camyks->get_translation('back')));
    } else {
      $this->adminTitle .= $this->get_translation('pictureGalleryid', $this->pictureGalleryItem->id);
      $this->buttons = array(array('link'=>$this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureGalleryItem->id)),
				 'title'=>$camyks->get_translation('back')));
    }
    
    /* add valid button */
    $this->buttons[] = array('link'=>$this->editform->get_HTMLSubmitLink(), 'title'=>$camyks->get_translation('valid'));

    /* update layout */
    $this->selected_layout = 'admin_edit_pictureGallery.html.inc';
  }
  
  /*
   * init module object in admin/save_pictureGallery mode
   * @return void
   * @access private
   */
  function init_admin_save_pictureGallery() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* check pictureGallery id */
    if(!isset($_REQUEST['pictureGallery_id']))
      return $this->init_admin_main();
    $pictureGallery_id = (int)$_REQUEST['pictureGallery_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save pictureGallery */
    $this->pictureGalleryItem->id = $pictureGallery_id;
    $this->pictureGalleryItem->get_fromHeader();
    if ( $this->pictureGalleryItem->save() )
      $this->text = $this->get_translation('pictureGallery_saved');
    else
      $this->text = $this->get_translation('pictureGallery_notsaved');

    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureGalleryItem->id)));
  }
  
  /*
   * init module object in admin/delete_pictureGallery mode
   * @return void
   * @access private
   */
  function init_admin_delete_pictureGallery() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* check pictureGallery id */
    if(!isset($_REQUEST['pictureGallery_id']))
      return $this->init_admin_main();
    $pictureGallery_id = $_REQUEST['pictureGallery_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* delete pictureGallery */
    $this->pictureGalleryItem->id = $pictureGallery_id;
    if ( $this->pictureGalleryItem->delete())
      $this->text = $this->get_translation('pictureGallery_deleted');
    else
      $this->text = $this->get_translation('pictureGallery_notdeleted');
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'PictureGalleries')));
  }

  /*
   * init module object in admin/edit_picture mode
   * @return void
   * @access private
   */
  function init_admin_edit_picture() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    /* get language to use with content */
    $lg = $this->get_adminEditionLanguage();
    
    /* get picture item */
    $this->pictureItem->id = isset($_REQUEST['picture_id'])?(int)$_REQUEST['picture_id']:0;
    $this->pictureItem->get();
    $this->pictureItem->get_fromItems();
    
    if ($this->pictureItem->id == 0 and !isset($_REQUEST['gallery'])) {
      /* no gallery defined for new picture */
      
    } elseif ($this->pictureItem->id == 0) {
      /* set gallery value */
      $this->pictureItem->vars['gallery'] = (int)$_REQUEST['gallery'];
    }
           
    /* create form */
    $this->editform = new HTMLForm('edit_picture',
				                   $this->get_adminlink(array('mode'=>'save_picture')),
				                   'POST');
    $this->editform->allow_files(true, $this->config->vars['picture_maxFileSize']*1024*1024 );
    $this->editform->set_object($this->pictureItem);
    $this->editform->add_hidden('picture_id', $this->pictureItem->id );
    $this->editform->add_hidden('gallery', $this->pictureItem->vars['gallery']);
    $this->editform->add_hidden('sortPosition', $this->pictureItem->vars['sortPosition']);
    
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    if ($this->pictureItem->id == 0 ) 
      $this->adminTitle .= $this->get_translation('newpicture');
    else
      $this->adminTitle .= $this->get_translation('pictureid', $this->pictureItem->id);
    
    /* build button list */
    $this->buttons = array(array('link'=>$this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->editform->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    
    /* update layout */
    $this->selected_layout = 'admin_edit_picture.html.inc';
  }
  
  /*
   * init module object in admin/save_picture mode
   * @return void
   * @access private
   */
  function init_admin_save_picture() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();

    /* check picture id */
    if ( !isset($_REQUEST['picture_id']))
      return $this->init_admin_main();
    $picture_id = $_REQUEST['picture_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save picture */
    $this->pictureItem->id = $picture_id;
    $this->pictureItem->get_fromHeader();
    if ($c = $this->pictureItem->save() )
      if ($this->pictureItem->autoDisabled == 1)
        $this->text = $this->get_translation('picture_autodisabled');
      else
        $this->text = $this->get_translation('picture_saved');
    else
      $this->text = $this->get_translation('picture_notsaved');
    $this->pictureItem->get_fromItems();
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    
    /* check for picture optimisations */
    if ($c and $this->pictureItem->has_newPicture())  {
        /* load scripts */
        $this->add_JSEngineFile('tool/xml.js');
        $this->add_JSEngineFIle('object/cajaxrequest.js');
        $this->add_JSFile('PictureSaving.js');
        $this->add_JSScript('var ps = new PictureSaving("ps");');
        $this->add_JSScript('ps.set_param("pictureId", '.$this->pictureItem->id.');');
        $this->add_JSScript('ps.set_param("requestBaseURL", "request.php?module='.$this->name.'");');
        $this->add_JSScript('ps.set_param("backURL", "'.$this->get_adminJSLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')).'");');
        $this->add_JSScript('ps.set_param("quitDelay", '.$camyks->get_confValue('ModuleActionDelay').');');
        $this->add_JSScript('ps.set_locale("picture_saved", "'.$this->get_translation('pictureimage_saved').'");');
        $this->add_JSScript('ps.set_locale("thumb_saved", "'.$this->get_translation('picturethumb_saved').'");');
        $this->add_JSLoadScript('ps.initialise();');
    } else
      $this->set_redirect($this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')));
  }
  
  /*
   * init module object in admin/delete_picture mode
   * @return void
   * @access private
   */
  function init_admin_delete_picture() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed () ;

    /* check picture id */
    if ( !isset($_REQUEST['picture_id']))
      return $this->init_admin_main();
    $picture_id = $_REQUEST['picture_id'];

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* delete picture */
    $this->pictureItem->id = $picture_id;
    $this->pictureItem->get();
    $this->pictureItem->get_fromItems();
    if ( $this->pictureItem->delete())
      $this->text = $this->get_translation('picture_deleted');
    else
      $this->text = $this->get_translation('picture_notdeleted');
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')));
  }
  
  /* 
   * init module object in admin/moveUp_picture mode
   * @return void
   * @access private
   */
  function init_admin_moveUp_picture() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
      
    if (!isset($_REQUEST['picture_id']))
      return $this->init_admin_main();
    
    /* try to moveup item */
    $this->pictureItem->id = (int)$_REQUEST['picture_id'];
    $this->pictureItem->get();
    $this->pictureItem->get_fromItems();
    $this->pictureItem->update_moveUp();
    
    /* update layout */
    $this->selected_layout = '__';
    $this->set_redirect(0, $this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')));
  }
  
  /* 
   * init module object in admin/moveDown_picture mode
   * @return void
   * @access private
   */
  function init_admin_moveDown_picture() {
    global $camyks;
    
    /* check user rights */
    if ( $this->check_right(2) === false )
      return $this->init_admin_actionNotAllowed();
    
    if (!isset($_REQUEST['picture_id']))
      return $this->init_admin_main();
    
    /* try to moveup item */
    $this->pictureItem->id = (int)$_REQUEST['picture_id'];
    $this->pictureItem->get();
    $this->pictureItem->get_fromItems();
    $this->pictureItem->update_moveDown();
    
    /* update layout */
    $this->selected_layout = '__';
    $this->set_redirect(0, $this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')));
  }
  
  /* specific request mode methods */
  
  /*
   * execute module object in picture picture optimisation mode
   * @return void
   * @access private
   */
  function execute_request_optimisePictureImage() {
  	global $camyks;
  	
  	/* load camyks engine */
  	$camyks->get_siteInit();
  	
  	/* load parameters and picture object */
    if (!isset($_REQUEST['picture_id']))
        return;
    $this->pictureItem->id = (int)$_REQUEST['picture_id'];
    if ($this->pictureItem->id == 0 or !$this->pictureItem->get($camyks->current_language))
        return;
    $this->pictureItem->get_fromItems();
    $result = new CRequestAnswer(array('status'=>'failure'));
    if ($this->pictureItem->optimise_picture())
        $result->update_params(array('status'=>'success'));
    $result->send_asXML(array('action'=>'optimisePictureImage'));
  }
  
  /*
   * execute module object in picture thumb optimisation mode
   * @return void
   * @access private
   */
  function execute_request_optimisePictureThumb() {
  	global $camyks;
  	
  	/* load camyks engine */
  	$camyks->get_siteInit();
  	
  	/* load parameters and picture object */
    if (!isset($_REQUEST['picture_id']))
        return;
    $this->pictureItem->id = (int)$_REQUEST['picture_id'];
    if ($this->pictureItem->id == 0 or !$this->pictureItem->get($camyks->current_language))
        return;
    $this->pictureItem->get_fromItems();
    $result = new CRequestAnswer(array('status'=>'failure'));
    if ($this->pictureItem->optimise_thumb())
        $result->update_params(array('status'=>'success'));
    $result->send_asXML(array('action'=>'optimisePictureThumb'));
  }

  /* specific admin tool methods */
  
  /*
   * return given config item value
   * @param string $item
   * @return mixed
   * @access private
   */
  function get_configValue($item) {
    if (!isset($this->config->vars))
      $this->config->get();
    if (isset($this->config->vars[$item]))
      return $this->config->vars[$item];
    return false;
  }

  /*
   * return config resize mode list
   * @return array
   * @access private
   */
  function get_configResizeModeList() {
    return $this->config->get_resizeModeList();
  }
  
  /*
   * return config resize mode list
   * @return array
   * @access private
   */
  function get_configFileTypeList() {
    return $this->config->get_fileTypeList();
  }

  /*
   * return picture gallery status list
   * @return array
   * @access private
   */
  function get_pictureGalleryStatusList() {
    return $this->pictureGalleryItem->get_statusList();
  }

  /*
   * return picture galleries status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_pictureGalleriesStatusList($full=false) {
    return $this->pictureGalleryItem->get_multiStatusList($full);
  }
  
  /*
   * return picture galleries title list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_pictureGalleriesTitleList($params=array()) {
    return $this->pictureGalleryItem->get_titleList($params);
  }
  
  /*
   * return picture gallery status icon list
   * @return array
   * @access private
   */
  function get_pictureGalleryStatusIconList() {
    return $this->pictureGalleryItem->get_statusIconList();
  }
  
  /*
   * return picture gallery list
   * @param array $params
   * @return array
   * @access private
   */
  function get_pictureGalleryList($params=array()) {
    return $this->pictureGalleryItem->get_list($params);
  }
  
  /*
   * return picture gallery count
   * @param array $params
   * @return array
   * @access private
   */
  function count_pictureGalleries($params=array()) {
    return $this->pictureGalleryItem->count($params);
  }
  
  /*
   * return picture  status list
   * @return array
   * @access private
   */
  function get_pictureStatusList() {
    return $this->pictureItem->get_statusList();
  }

  /*
   * return pictures status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_picturesStatusList($full=false) {
    return $this->pictureItem->get_multiStatusList($full);
  }
  
  /*
   * return picture list
   * @param array $params
   * @return array
   * @access private
   */
  function get_pictureList($params=array()) {
    return $this->pictureItem->get_list($params);
  }
  
  /*
   * return picture count
   * @param array $params
   * @return array
   * @access private
   */
  function count_pictures($params=array()) {
    return $this->pictureItem->count($params);
  }
  
  /*
   * return first picture list
   * @param array $params
   * @return array
   * @access private
   */
  function get_firstPicturesList($params=array()) {
    return $this->pictureItem->get_firstList($params);
  }
}
?>