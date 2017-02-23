<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Create Date      : Jun 2010
 * Last Modif Date  : Jun 2010
 * 
 * Content_GooglePoIMapViewer
 */

class Content_GooglePoIMapViewer extends Module {
  
  /*
   * constructor
   * @param string $path_type
   */
  function Content_GooglePoIMapViewer ( $path_type ) {
    parent::Module('Content_GooglePoIMapViewer', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Google';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';

    /* load plugin libraries */
    $this->libs[] = 'Content_GooglePoIMapViewerItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->contentItem = new Content_GooglePoIMapViewerItem(0, $this);
  }
    /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->contentItem->install() )
      return parent::install();
    return false;
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    if ( $this->contentItem->uninstall() )
      return parent::uninstall();
    return false;
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->contentItem->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->contentItem->get_nameList();
  }
  

  /*
   * init module object when in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;

    /* generic pre-initialisation */
    parent::preInit_admin();
 

    /* check dependencies */
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    if(!isset($camyks->inputs['TinyMCEv3']))
      return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');
    if(!isset($camyks->modules['Admin_GooglePoIMapManager']))
      return $this->init_admin_missingPlugin('Module', 'Admin_GooglePoIMapManager');

    /* check user rights for this page */
    if ( $this->check_right( $this->page_id ) === false )
      return $this->init_admin_pageAccessDenied();

    /* get content object id */
    $this->contentItem->id = $this->id;
    /* get mode */
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'modify';

    switch ( $this->mode ) {
    case 'save':
      /* mode == save */
      $this->init_admin_save();
      break;
    case 'modify':
    default:
      /* mode == modify */
      $this->init_admin_modify();
      break;
    }
    parent::init_admin();
  }

  /*
   * display module object when in admin part
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
  function init_site($content=1, $params=array(), $mindex=null) {
    global $camyks;
    
    /* check site manager */
    if(!isset($camyks->modules['Admin_GooglePoIMapManager'])) {
        $this->selected_layout = 'null';
        return;
    }
    
    /* load manager */
    $this->load_mapManager();
    $this->pointItem = &$this->mapManager->pointItem;

    /* load content */
    $this->contentItem->id = $content;
    $this->contentItem->get($camyks->current_language);
    $this->contentItem->get_fromItems();
    
    /* get category list */
    $cParams = array('status'=>1, '_all'=>true);
    if ($this->contentItem->vars['categories'] != '')
      $cParams['ids'] = $this->contentItem->vars['categories_'];
    $this->categoryList = $this->mapManager->get_categoryTitleList($cParams);

    /* initialise list params */
    $lp = array();
    $lp['status'] = 1;
    $lp['language'] = $camyks->current_language;

    /* check selected category */
    if (isset($params['category']) and $params['category'] > 0 
	and ( $this->contentItem->vars['categories']== '' or in_array($params['category'], $this->contentItem->vars['categories_'])))
      $lp['categories'] = $params['category'];
    else
      $lp['categories'] = array_keys($this->categoryList);
    
    /* check selected country */
    if (isset($params['country']))
      $lp['country'] = $params['country'];

    /* get point list */
    $this->pointList = $this->mapManager->get_pointList($lp);

    /* get icon list */
    $icons = array();
    foreach ($this->pointList as $p)
      if (!in_array($p->vars['icon'], $icons))
				$icons[] = $p->vars['icon'];
		if ($this->contentItem->vars['geo_status'] == 1 
			and $this->contentItem->vars['geo_icon'] > 0 
			and !in_array($this->contentItem->vars['geo_icon'], $icons))
			$icons[] = $this->contentItem->vars['geo_icon'];
    $ip = array('ids'=>$icons, '_sized'=>true);
    $this->iconList = $this->mapManager->get_iconList($ip);
            
    /* build javascript object */
    $this->add_JSEngineFile('tool/mail.js');
    $this->add_JSEngineFile('tool/html.js');
    $this->add_JSEngineFile('tool/xml.js');
    $this->add_JSExternFile('http://maps.google.com/maps?file=api&v=2&key='.$this->mapManager->config->vars['google_mapapikey'].'&sensor=false');
    $this->add_JSEngineFile('object/cajaxrequest.js');
    $this->add_JSFile('mapviewer.js');
    //$this->add_JSFile('markermanager.js');
    $this->add_JSScript('var pmv = new PoIMapViewer("pmv");');
    $this->add_JSLoadScript('pmv.initialise();');
    $this->add_JSUnloadScript('GUnload();');
  
    /* add javascript params */
    $this->add_JSScript('pmv.set_param("ajaxBaseURL", "request.php?module='.$this->name.'");');
    $this->add_JSScript('pmv.set_param("loadingImageURL", "'.$this->get_fileURL('img/loading.gif').'");');
    $this->add_JSScript('pmv.set_param("GMapDefZoom", '.$this->contentItem->vars['default_zoom'].');');
    
    /* add locale */
    $this->add_JSScript('pmv.add_locale("your_location", "'.$this->get_translation('js_your_location').'");');
    
    /* add point list */
    $cnt = 0;
    foreach($this->pointList as $id => $a) {
      $p = '{title:"'.addslashes($a->vars['title']).'"';
      $p .= ', icon:'.$a->vars['icon'];
      if ( $a->vars['latitude'] == '' or $a->vars['longitude'] == '' ) {
        unset( $this->pointList[$id] );
      } else {
        $p .= ', lat:"'.$a->vars['latitude'].'"';
        $p .= ', lng:"'.$a->vars['longitude'].'"';
      }
      $p .= '}';
      $this->add_JSScript('pmv.add_mapPoint('.$a->id.', '.$p.');');
    }
    
   if (isset($params['point']) and isset($this->pointList[$params['point']]))
     $this->add_JSLoadScript('pmv.select_point('.$params['point'].');');
   else
     foreach ($this->pointList as $id => $a ) {
       $this->add_JSLoadScript('pmv.select_point('.$id.');');
       break;
     }
   
    /* add icon list */
    $cnt = 0;
    foreach($this->iconList as $id => $a) {
      $p = '{mainImg:"'.$a->vars['mainImg'].'"';
      $p .= ', rollImg:"'.$a->vars['rollImg'].'"';
      $p .= ', slctImg:"'.$a->vars['slctImg'].'"';
      $p .= ', shdwImg:"'.$a->vars['shdwImg'].'"';
      $p .= ', mainWidth:'.$a->vars['mainWidth'].'';
      $p .= ', mainHeight:'.$a->vars['mainHeight'].'';
      $p .= ', shdwWidth:'.$a->vars['shdwWidth'].'';
      $p .= ', shdwHeight:'.$a->vars['shdwHeight'].'';
      $p .= ', anchorX:'.$a->vars['anchorLocX'].'';
      $p .= ', anchorY:'.$a->vars['anchorLocY'].'';
      $p .= '}';
      $this->add_JSScript('pmv.add_mapIcon('.$a->id.', '.$p.');');
    }

    /* check for selectors */
    if ($this->contentItem->vars['category_select'] == 1
	or $this->contentItem->vars['country_select'] == 1) {
      $this->has_selector = true;

      /* build form */
      $this->form = new HTMLForm('pointlist', null, 'post');

      /* get category values */
      if ($this->contentItem->vars['category_select'] == 1) {
	
	$this->selCategory = isset($params['category'])?(int)$params['category']:0;
	$this->add_JSScript('pmv.set_param("updateCategoryURL", "'.$this->get_pageLink(array('category'=>'_c_'), $params).'");');
      }

      /* get country values */
      if ($this->contentItem->vars['country_select'] == 1) {
	countries_loadLocales();
	$this->selCountry = isset($params['country'])?$params['country']:'';
	$this->countryList = array();
	$this->countryList[''] = $this->get_translation('countries_all');
	foreach ($this->pointList as $point) {
	  if (!isset($this->countryList[$point->vars['country']]))
	    $this->countryList[$point->vars['country']] = countries_getTranslation($point->vars['country']);
	}
	$this->add_JSScript('pmv.set_param("updateCountryURL", "'.$this->get_pageLink(array('country'=>'_c_'), $params).'");');
      }
    } else {
      $this->has_selector = false;
    }
    
    /* check mobile */
    if ($camyks->deviceMode == 'mobile') {
    	$layout = '_mobile';
    	$this->add_JSScript('pmv.set_param("hasTabs", 1);');
    } else {
    	$layout = '';
    	$this->add_JSScript('pmv.set_param("hasTabs", 0);');
    }
    
    
    $this->add_JSScript('pmv.set_param("GooglePoIMapGeoStatus", '.$this->contentItem->vars['geo_status'].');');
    if ($this->contentItem->vars['geo_status'] == 1) {
    	$this->add_JSScript('pmv.set_param("GooglePoIMapGeoIcon", '.$this->contentItem->vars['geo_icon'].');');
    	$this->add_JSScript('pmv.set_param("GooglePoIMapGeoZoom", '.$this->contentItem->vars['geo_zoom'].');');
    }
    

    /* update layout */
    $this->selected_layout = 'site_'.$this->contentItem->vars['layout'].$layout.'.html.inc';
  }
  
  /*
   * execute module object in request mode
   * @return void
   * @access private
   */
  function execute_request() {
    global $camyks;
    
    /* get action to execute */
    $action = isset($_REQUEST['action'])?$_REQUEST['action']:'';
    switch ($action) {
      case 'loadpoint':
        $this->execute_request_loadpoint();
        break;
    }
    
    /* return undefined action error */
    $result = array();
    $result['status'] = 'failed';
    $result['error'] = $this->get_translation('error_undefinedaction');
    header("Content-type: text/xml");
    die(xml_serialize2XML($result));
  }

  /* specific admin mode methods */

  /*
   * init object when in admin / modify mode
   * @return void
   * @access private
   */
  function init_admin_modify ( ) {
    global $camyks;
    
    /* load help files */
    $this->get_help();

    /* load map manager */
    $this->load_mapManager();

    /* get object values */
    $this->contentItem->get();
    $this->contentItem->get_fromItems();

    /* load data */
    $this->categoryList = $this->mapManager->get_categoryTitleList(array('status'=>1));

    /* load editor input */
    $this->editor = &$camyks->inputs['TinyMCEv3'];
    $this->editor->initialise();

    /* load editing languages */
    $this->elgs = $camyks->get_confValue('editing_languages');

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    /* add definitions tab */
    $this->tabBuilder->add_tab(array('name'=>'properties',
				     'title'=>$this->get_translation('tabproperties')));
    if (count($this->elgs) == 1)
      $this->tabBuilder->add_tab(array('name'=>$this->elgs[0],
				       'title'=>$this->get_translation('tabcontent')));
    else
      foreach($this->elgs as $l)
	$this->tabBuilder->add_tab(array('name'=>$l,
					 'title'=>language_getIcon($l)));
    
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'properties'));
    
    
    /* create html form */
    $this->form = new HTMLForm('edit_form',
			       $this->get_adminlink(array('mode'=>'save')),
			       'POST');
    $this->form->set_object($this->contentItem);
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index);
    $this->form->add_hidden('id', $this->contentItem->id );
    $this->form->add_hidden('category_cnt', count($this->categoryList));

    /* add scripts */
    $this->add_JSFile('poimapviewer_admin.js');
    $this->add_JSScript('var formName = "'.$this->form->name.'";');
    
    /* build button list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink( 'Admin_ContentPage',
								 array('mode'=>'modify',
								       'page_id'=> $this->page_id,
								       'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
  }

  /*
   * init object when in admin / save mode
   * @return void
   * @access private
   */
  function init_admin_save ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* load editing languages */
    $this->elgs = $camyks->get_confValue('editing_languages');

    /* save content */
    $this->contentItem->get_fromHeader();
    if ( $this->contentItem->save() ) {
      if ( $this->id == 0 and $this->page_id > 0 ) {
	/* update page information with object id for new content */
	ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->contentItem->id );
      }
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $this->get_adminLink(array('mode'=>'modify',
						      'id'=>$this->contentItem->id)));
  }
  
  /* specific request methods */
  
  /*
   * return loaded site in request mode
   * @return void
   * @access private
   */
  function execute_request_loadpoint() {
    global $camyks;
    
    $camyks->get_databaseConnection();
    $camyks->get_currentLanguage('site');
    
    /* initialise result */
    $result = array();
    
    /* check obj and type */
    if (!isset($_REQUEST['point'])) {
      $result['status'] = 'failed';
      $result['error'] = $this->get_translation('error_undefinedobject');
      header("Content-type: text/xml");
      die(xml_serialize2XML( $result ));
    }
    
    $result['status'] = 'success';
    $result['action'] = 'updateSelectedPoint';

    /* load params */
    $pointManager = module_get('Admin_GooglePoIMapManager', 'camyks');
    
    $pointItem = &$pointManager->pointItem;
    $pointItem->id = $_REQUEST['point'];
    $pointItem->get($camyks->current_language);
    $pointItem->get_fromItems();
    
    $result['title'] = $pointItem->vars['title'];
    $result['desc'] = $pointItem->vars['description'];
    
    /* send result as XML */
    header("Content-type: text/xml");
    die (xml_serialize2XML($result, 'request'));
  }
  
  /* specific tool methods */
           
  /*
   * load map manager
   * @return void
   * @access private
   */
  function load_mapManager() {
    global $camyks;

    /* check map manager module */
    if(isset($camyks->modules['Admin_GooglePoIMapManager'])) {
      $this->mapManager = &$camyks->modules['Admin_GooglePoIMapManager'];
      $this->mapManager->config->get();
    } else
      $this->mapManager = false;
  }


  /*
   * return layout list
   * @return array
   * @access public
   */
  function get_layoutList() {
    return array('nobox'=>$this->get_translation('layout_nobox'),
		 'largebox'=>$this->get_translation('layout_largebox'));
    
  }
  
  /*
   * return geolocalisation status list
   * @return array
   * @acces public
   */
  function get_geoStatusList() {
  	return array(0=>$this->get_translation('geostatus_disabled'),
  							1=>$this->get_translation('geostatus_enabled'));
  }
  
  /*
   * return icon title list
   * @return array
   * @access public
   */
  function get_iconTitleList() {
  	return $this->mapManager->get_iconNameList();
  }
  

  /*
   * return page link
   * @param array $newParams
   * @param array $oldParmas
   * @return string
   * @access private
   */
  function get_pageLink($newParams=array(), $oldParams=array()) {
    global $camyks;
    $params = array();

    if (isset($oldParams['point']))
      $params['point'] = $oldParams['point'];
    if (isset($oldParams['country']))
      $params['country'] = $oldParams['country'];
    if (isset($oldParams['category']))
      $params['category'] = $oldParams['category'];
    
    if (count($camyks->get_confValue('site_languages')) > 1 )
      $lg = $camyks->current_language;
    else
      $lg = null;
    
    $params = array_merge($params, $newParams);
    return $camyks->get_siteLink($camyks->contentPage->id,'',
				 $lg,
				 $params);
  }
}
?>