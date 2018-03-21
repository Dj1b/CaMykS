<?php
/* 
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Jun 2005
 * Last Modif Date  : Mar 2018
 * History :
 * * 05-06-xx : Initial files
 * * 08-02-19 : Add model support
 * * 08-05-02 : Rewrite page index management
 * * 08-05-12 : Some minor optimisation about popup messages
 * * 08-05-18 : Rewrite online help (french)
 * * 08-06-17 : Update HTML layouts, add id to finder menu items
 * * 09-08-31 : Sort module lists in content tab
 * * 14-12-05 : Add configuration panel
 * * 17-02-28 : Support for "modern" URLs
 * 
 * Admin_ContentPage Module object ( Mandatory module )
 * Manage site pages
 * 
 * TO DO :
 * - other page type ( folder, ... )
 * - cut/paste action
 * - rights propagation
 */

final class Admin_ContentPage extends Module {
  /* variables */

  /* page object */
  public $page;

  /* mode : finder / modify / save / delete / moveup / movedown */
  public $mode;
  public $available_modes;

  /* modify / save vars */
  public $page_id;
  /* finder vars */
  public $htmlcols;
  public $opened;
  
  /* configuration */
  public $config;
   
  /*
   * constructor
   * @param string $path_type
   * @return void
   * @access public
   */
  public function __construct($path_type) {
    global $camyks;
    /* get Module generic init */
    parent::Module('Admin_ContentPage', $path_type);
    /* set module type values  */
    $this->type = 'admin';
    $this->admin_type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set author description */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';

    /* module values */
    $this->titles = array();
    $this->libs[] = 'ContentPage.php.inc';
    $this->libs[] = 'Admin_ContentPageConfig.php.inc';
    $this->get_PHPLibs();
    $this->page = new ContentPage($camyks->mode, 0);
    $this->pages = null;
    $this->siteHomePage = null;
    
    /* load config */
    $this->config = new Admin_ContentPageConfig('config', $this);
    $this->config->get();
    
    /* register plugin as Admin_Site extension */
    $this->register_asExtension('Admin_Site');
  }
  
  /* overwrite module methods */

  /*
   * install module
   * @return boolean success
   * @access public
   */
  public function install() {
    return ($this->page->install() and $this->config->install() and parent::install());
  }

  /*
   * uninstall module
   * @return boolean success
   * @access public
   */
  public function uninstall() {
    return false;
  }

  /*
   * check module installation
   * @return boolean result
   * @access public
   */
  public function is_installed( ) {
    return $this->page->is_installed();
  }
  
  /*
   * return statistic titles
   * @param array $pages
   * @param string $type
   * @return array
   * @access public
   */
  public function get_adminStatisticsValueTitles($pages, $type=null) {
    switch ($type) {
      case 'sitepage':
      case 'firstpage':
        $lg = $this->get_adminEditionLanguage();
        $page_objects = $this->page->static_get_listedPages(implode(',', $pages), $lg);
        foreach ($pages as $page) {
	      if (isset ( $page_objects[$page])) {
	        $pages[$page] = $page_objects[$page]->title;
	      }
        }
        return $pages;
        break;
      default:
        return $pages;
    }
  }
  
  /* 
   * set module rights 
   * @return void
   * @access public
   */
  public function get_rights() {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> true);
    $this->rights[1] = array( 'name'=>'write',
			      'title'=> $camyks->get_translation('write'),
			      'default'=> true);
    $this->rights[2] = array( 'name'=>'root',
			      'title'=> $this->get_translation('rights_modify_root'),
			      'default'=> false);
    $this->rights[3] = array( 'name'=>'rights',
			      'title'=> $this->get_translation('rights_modify_rights'),
			      'default'=> false);
    $this->rights[4] = array( 'name'=>'structure',
			      'title'=> $this->get_translation('rights_modify_structure'),
			      'default'=> false);
    $this->rights[5] = array( 'name'=>'editmodels',
			      'title'=> $this->get_translation('rights_modify_models'),
			      'default'=> false);
    $this->rights[6] = array( 'name'=>'overwritemodels',
			      'title'=> $this->get_translation('rights_overwrite_models'),
			      'default'=> false);
    /* workflow values */
    if ( $camyks->site_conf['workflow'] == 1 ) {
      $this->rights[7] = array( 'name'=>'putinline',
				'title'=> $this->get_translation('rights_putinline'),
				'default'=> false);
    }
    $this->rights[8] = array('name'=>'configuration',
        'title'=>$this->get_translation('rights_configuration'),
        'default'=>false);
  }

  /*
   * build admin menu object
   * @return array
   * @access public
   */
  public function get_adminEngineSpecificMenus() {
    /* return menu in finder mode and when admin is allowed */
    if ($this->mode == 'finder' and $this->check_right(5)===true) {
      return array(array(
        'name'  => 'pagesmanager',
		'title' => $this->get_translation('title'),
	  ));
    }
    /* return empty menu in other modes */
    return array();
  }
  
  /*
   * build admin menu items
   * @return array
   * @access public
   */
  public function get_adminEngineSpecificMenuItems() {
    global $camyks;
    /* return menu items in finder mode and when admin is allowed */
    if ($this->mode == 'finder' and $this->check_right(5)===true) {
      $items = array();
      $items[] = array(
        'name'  => 'newmodel',
		'title' => $this->get_translation('newmodel'),
		'icon'  => $this->theme->get_pictURL('plus', 12, 'std'),
		'menu'  => 'pagesmanager',
		'url'   => $camyks->get_adminLink(
		    $this->name,
			array(
			    'mode'=>'modify',
			    'type'=>'model',
				'page_id'=>0
			)
		)
	  );
      /* load models */
      $models = $this->page->get_modelsList();
      if (count($models) > 0) {
	    $items[] = array(
	        'name'  => 'separator',
			'title' => '----',
			'menu'  => 'pagesmanager');
	    foreach ($models as $model) {
	        $items[] = array(
	            'name'  => 'model'.$model->id,
			    'title' => $this->get_translation('modelobject', $model->name),
			    'icon'  => $this->theme->get_pictURL('file', 12, 'std'),
			    'menu'  => 'pagesmanager',
			    'url'   => 'javascript:contentPage_openModelActions('.$model->id.');'
			);
	    }
      }
      return $items;
    }
    /* return empty menu in other modes */
    return array();
  }
  
  /*
   * initialise module object in admin mode
   * @return void
   * @access public
   */
  public function init_admin() {
    global $camyks;

    /* check read right */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();
      
    /* check dependencies */
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    
    $this->available_modes = array('finder','modify', 'save', 'delete', 'moveup', 'movedown', 'move', 'edit_config', 'save_config');
    $this->add_styleFile('contentpage.css');
    /* get mode to display from header params */
    if ( isset($_REQUEST['mode'] ) ) {
      $this->mode = ( in_array($_REQUEST['mode'], $this->available_modes ) ? $_REQUEST['mode'] : 'finder');
    } else {
      $this->mode = 'finder';
    }
    
    /* mode == modif or mod == save */
    if ( !in_array($this->mode, array('finder', 'edit_config', 'save_config'))) {
      $this->page_id = ( isset ( $_REQUEST['page_id'] ) ? $_REQUEST['page_id'] : -1 );
      if ( ! ($this->page_id >= 0) ) {
	    /* no page id given, switch to finder mode */
	    $this->mode = 'finder';
      }
    }
    
    switch($this->mode) {
      case 'finder':
        /* mode == finder */
        /* get default opened pages */
        $this->opened = isset ( $_REQUEST['opened'] ) ? $_REQUEST['opened'] : '';
        $this->allowedition = $this->check_right(1);
        $this->language = $camyks->current_language;
        $this->init_admin_finder();
        break;
      case 'modify':
        /* mode  == modify */
        $this->init_admin_modify();
        break;
      case 'save':
        /* mode == save */
        $this->init_admin_save();
        break;
      case 'delete':
        /* mode == delete */
        $this->init_admin_delete();
        break;
      case 'moveup':
        /* mode == moveup */
        $this->init_admin_moveup();
        break;
      case 'movedown':
        /* mode == movedown */
        $this->init_admin_movedown();
        break;
      case 'move':
        /* mode == move */
        $this->init_admin_move();
        break;
      case 'edit_config':
         /* mode == edit_config */
         $this->init_admin_edit_config();
        break;
      case 'save_config':
        /* mode == save_config */
        $this->init_admin_save_config();
        break;
    }
    parent::init_admin();
  }

  /*
   * execute module object as a request 
   * @return void
   * @access public
   */
  public function execute_request() {
    global $camyks;

    /* initialise camyks */
    $camyks->get_adminInit();
    
    /* check admin session value  */
    if ($camyks->get_sessionValue('admin_user') == null) {
      die();
    }
    $camyks->adminUser = new AdminUser($camyks->get_sessionValue('admin_user'));
    if (!$camyks->adminUser->get_fromDatabase()) {
      die();
    }

    /* get values from header */
    $this->execute_request_get_headerValues();

    /* add generic translation for file description */
    $camyks->add_generic_translation();

    /* build html page */
    $camyks->HTMLPage = new HTMLPage();
    $camyks->HTMLPage->set_charset ( $camyks->get_htmlencodingvalue());
    $camyks->HTMLPage->add_styleFile ( $camyks->site_data_url.'/css/generic.css' );
    $camyks->HTMLPage->set_siteInformations ( $camyks->site_conf['site_title'],
					      $camyks->site_conf['site_author'],
					      $camyks->site_conf['site_company']);
    $camyks->HTMLPage->set_robotInformations ( false, false );

    /* initialise plugin */
    $this->initialise_finderMode();    

    /* overwrite button list for buttons bar */
    $this->buttons = array(array('title'=>$camyks->get_translation('cancel'),
				 'link'=>'javascript:window.close();'),
			   array('title'=>$camyks->get_translation('select'),
				 'link'=>'javascript:contentPage_requestSelectPage();'));
    
    $this->add_styleFile('contentpage.css');
    
    /* complete javascript */
    $this->add_JSScript('var pc_mode="'.$this->request_mode.'";');
    $this->add_JSScript('var pc_callback="'.$this->request_callback.'";');

    /* load theme */
    $this->theme->initialise_adminMode();

    $this->selected_layout = 'request.html.inc';
    
    /* display html page */
    $camyks->HTMLPage->add_HTMLHeader();
    $camyks->HTMLPage->write_HTMLContent();
    $this->display_admin();
    $camyks->HTMLPage->add_HTMLFooter();
    $camyks->HTMLPage->write_HTMLContent();
  }

  /* specific mode methods */

  /*
   * initialise module object in admin/finder mode
   * @return void
   * @access private
   */
  private function init_admin_finder() {
    global $camyks;
    
    $this->initialise_finderMode();

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array(
        'name'  => 'finder',
		'title' => $this->get_translation('pages'),
    ));
    
    /* load configuration data */
    if ($this->check_right(8)) {
      $this->W3CValidatorStatus = $this->config->get_w3cValidatorList();
      $this->OGMetaStatus = $this->config->get_ogMetaStatusList();
      $this->Error404FallBacks = $this->config->get_404FallbackList();
      $this->tabBuilder->add_tab(array(
        'name'=>'Configuration',
		'title'=>$this->get_translation('configuration'),
      ));
    }
    
    /* get help pages */
    $this->get_help();
    if ( $this->help != null )
	 	 $this->tabBuilder->add_tab(array(
	 	    'name'  => 'help',
			'title' => $camyks->get_translation('help')
		));
    $this->tabBuilder->initialise(array('default'=>'finder'));
  

    /* button list for buttons bar */
    $this->buttons = array(array(
        'title' => $camyks->get_translation('back'),
		'link'  => $camyks->get_adminLink()
	));

    /* update layout */
    $this->selected_layout = 'finder.html.inc';
  }
  
  /*
   * initialise module object in admin/modify mode
   * @return void
   * @access private
   */
  private function init_admin_modify() {
    global $camyks;

    /* get help pages */
    $this->get_help();

    /* get all admin group */
    $this->admin_groups = $camyks->modules['Admin_Group']->get_groups();
    
    $this->wfEditor = array();
    foreach ( $this->admin_groups as $g ) {
      $this->wfEditors[$g->name] = $g->title;
    }
    
    /* build meta methods & language lists */
    $this->meta_methods = array('hidden' => $this->get_translation('metamethod_hidden'),
    			                'name' => $this->get_translation('metamethod_name'),
			                    'http-equiv' => $this->get_translation('metamethod_http'),
			                    'link:rel' => $this->get_translation('metamethod_linkrel'));
    $this->meta_languages = array();
    $this->meta_languages[''] = $this->get_translation('metalanguage_all');
    foreach( $camyks->get_confValue('editing_languages') as $l) {
       $this->meta_languages[$l] = $camyks->get_translation('lang_'.$l);
    }
    
    /* get page content */
    $this->page->id = $this->page_id;
    $this->page->get();
    
    /* get all available content for each */
    $this->modules = array();
    $this->contents = array();
    foreach ( $camyks->modules as $mod ) {
      if ( isset($mod->type) and $mod->type == 'content' ) {
	$this->modules[$mod->name] = $mod->title;
	$this->contents[ $mod->name ] = $mod->get_contentList();
      }
    }
    asort($this->modules);

    /* set form object */
    $this->form = new HTMLForm ('admin_contentpage_form',
				$camyks->get_adminLink($this->name, array('mode'=>'save')),
				'POST');
    $this->form->add_hidden('next', '');
    $this->form->add_hidden('page_id', $this->page->id );
    $this->form->add_hidden('parent_id', $this->page->parent_id );
    $this->form->add_hidden('type', $this->page->type);
        
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];

    /* check for theme change on module */
    $this->allow_theme_change = $camyks->get_confValue('admin_allowblockthemechange');
    
    switch( $this->page->type ) {
    case 'model':
      /* get rights */
      if ( $this->check_right(5)===true ) {
	    $this->allow_content_edition = true;
	    $this->allow_rights_edition = true;
      } else {
	    return $this->init_admin_actionNotAllowed();
      }
      
      /* get models list : empty */
      $this->models = array();
      
      /* tab list for tabs list */
      $this->tabBuilder->add_tabs(array(array('name'=>'general',
				'title'=>$this->get_translation('tabgeneral')),
			  array('name'=>'content',
				'title'=>$this->get_translation('tabcontent'))));
      break;
    case 'page':
    default:
      /* get rights */
      $this->allow_content_edition = ($this->check_right(1) and $this->page->check_rights());
      $this->allow_rights_edition = $this->check_right(3);
      
      /* get models list */
      $this->models = $this->page->get_modelsList('active=1');
      
      /* tab list for tabs list */
      $this->tabBuilder->add_tabs(array(array('name'=>'general',
				'title'=>$this->get_translation('tabgeneral')),
			  array('name'=>'metas',
				'title'=>$this->get_translation('tabmetas')),
			  array('name'=>'content',
				'title'=>$this->get_translation('tabcontent'))));
      foreach ( $camyks->site_conf['editing_languages'] as $l ) {
	    $this->tabBuilder->add_tab(array('name'=> $l,
			      'title'=> language_getIcon($l)));
      }
      if ( $this->help != null ) {
	    $this->tabBuilder->add_tab(array('name'=> 'help',
			      'title'=> $camyks->get_translation('help')));
      }
    }
    /* intialise tabs */
    $this->tabBuilder->initialise(array('default'=>'general'));
    
    /* add edition Javascripts */
    if ( $this->allow_content_edition ) {
      /* build model title list */
      $this->modelTitleList = array();
      if ( $this->check_right(6)) {
        $this->modelTitleList[''] = array('value'=>$this->get_translation('none'));
        $this->modelTitleList['-'] = array('value'=>'', 'class'=>'separator', 'disabled'=>'disabled');
      }
      foreach ($this->models as $m)
        $this->modelTitleList[$m->id] = $m->name;
      
      /* build theme title list */
      $this->themeTitleList = array();
      $this->themeTitleList[''] = array('value'=>$this->get_translation('defaultfromsite'));
      $this->themeTitleList['-'] = array('value'=>'', 'class'=>'separator', 'disabled'=>'disabled');
      foreach ($camyks->themes as $theme)
        $this->themeTitleList[$theme->name] = $theme->title;
      $this->mthemeTitleList = $this->themeTitleList;
      $this->mthemeTitleList[''] = array('value'=>$this->get_translation('defaultfrompage'));
      
      /* build template title list */
      $this->templateTitleList = array();
      $this->templateTitleList[''] = array('value'=>$this->get_translation('defaultfromsite'));
      $this->templateTitleList['-'] = array('value'=>'', 'class'=>'separator', 'disabled'=>'disabled');
      foreach ($camyks->templates as $template)
        $this->templateTitleList[$template->name] = $template->title;
      
      /* build module title list */
      $this->moduleTitleList = array();
      $this->moduleTitleList[''] = $this->get_translation('none');
      foreach ( $this->modules as $name => $title )
         $this->moduleTitleList[$name] = $title;
    
      $this->add_JSFile('contentpage_editor.js');
      $this->add_JSScript('var acpe = new AdminContentPageEditor("acpe");');
      $this->add_JSLoadScript('acpe.initialise();');

      /* add page id value */
      $this->add_JSScript('acpe.add_param("pageID", '.$this->page->id.');');

      /* add form name value */
      $this->add_JSScript('acpe.add_param("form", "'.$this->form->name.'");');
      
      /* add module values */
      $this->add_JSScript('acpe.add_param("maxModules", '.$this->page->maxmodules.');');

      /* add template blocks values */
      $this->add_JSScript('acpe.add_param("templateBlocks", {})');
      foreach( $camyks->templates as $t )
	$this->add_JSScript('acpe.add_arrayParam("templateBlocks", "'.$t->name.'", '.$t->modules.');');
      $this->add_JSScript('acpe.add_arrayParam("templateBlocks", "__null__", 1);');

      /* add default template value */
      $this->add_JSScript('acpe.add_param("defaultTemplate", "'.$camyks->site_conf['site_default_template'].'");');

      /* add mode mode value */
      if ( $this->check_right(6) ) {
	    $this->add_JSScript('acpe.add_param("modelMode", "admin");');
      } else {	
	    $this->add_JSScript('acpe.add_param("modelMode", "user");');
      }
      
      /* add block theme change value */
      $this->add_JSScript('acpe.add_param("allowThemeChange",'.($this->allow_theme_change?'true':'false').');');

      /* add module content values */
      $this->add_JSScript('acpe.add_param("moduleContents", {});');
      $this->add_JSScript('acpe.add_param("moduleEditable", {});');
      foreach ( $this->contents as $c => $v ) {
	    if ( $v == -1 ) {
	        $this->add_JSScript('acpe.add_arrayParam("moduleContents", "'.$c.'", -1);');
	        $this->add_JSScript('acpe.add_arrayParam("moduleEditable", "'.$c.'", 0);');
	    } else {
	        $s = 'acpe.add_arrayParam("moduleContents", "'.$c.'", {';
	        if (count($v) > 0) {
	            foreach ( $v as $id => $name ) {
	                $s .= ''. $id .':"'.$name.'",';
	            }
	            $s = substr ( $s, 0, strlen($s)-1);
	        }
	        $s .= '});';
	        $this->add_JSScript($s);
	        $this->add_JSScript('acpe.add_arrayParam("moduleEditable", "'.$c.'", '.($camyks->modules[$c]->is_editable === false?0 : $camyks->modules[$c]->is_editable).');'); 
	    }
      }
      
      /* add selected content values */
      $this->add_JSScript('acpe.add_param("selectedContents", new Array());');
      for( $i=0; $i< $this->page->maxmodules; $i++ ) {
	    $c = isset($this->page->modules[$i]['content'])?$this->page->modules[$i]['content']:'';
	    $this->add_JSScript('acpe.add_arrayParam("selectedContents", '.$i.', "'.$c.'");');
      }

      /* add model values */
      $this->add_JSScript('acpe.add_param("models", new Array());');
      foreach($this->models as $model) {
	    $s = 'acpe.add_arrayParam("models", '.$model->id.', {';
	    $s .= '"id":'.$model->id.', "name":"'.$model->name.'",';
	    $s .= '"template":"'.$model->template.'", ';
	    $s .= '"theme":"'.$model->theme.'", ';

      if ( $model->template == '' ) {
	    $model->template = $camyks->get_confValue('site_default_template');
	  }
	  for ($i = 0; $i< $camyks->templates[$model->template]->modules; $i++) {
	    $s .= '"m'.$i.'_name":"'.$model->modules[$i]['name'].'",';
	    $s .= '"m'.$i.'_content":"'.$model->modules[$i]['content'].'",';
	    $s .= '"m'.$i.'_theme":"'.$model->modules[$i]['theme'].'",';
	  }
	  $s .= '});';
	  $this->add_JSScript($s);
      }
      
      /* add locales */
      $this->add_JSScript('acpe.add_locale("no_content","'.string_html2Text($this->get_translation('no_content')).'");');
      $this->add_JSScript('acpe.add_locale("new_content", "'.string_html2Text($this->get_translation('new_content')).'");');
    }
    
    /* button list for buttons bars */
    $this->buttons = array(array(
        'title' => $camyks->get_translation('back'),
		'link'  => $camyks->get_adminLink( $this->name, array('opened'=> $this->page->id))
	));
    if ( $this->allow_content_edition or $this->allow_rights_edition ) {
      $this->buttons[] = array(
        'title' => $camyks->get_translation('valid'),
		'link'  => 'javascript:acpe.valid_page();'
	  );
    }
    
    /* update layout */
    $this->selected_layout = 'modify.html.inc';
  }
  
  /*
   * initialise module object in admin/save mode
   * @return void
   * @access private
   */
  private function init_admin_save() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get page id */
    $this->page->id = isset($_REQUEST['page_id'])?$_REQUEST['page_id']:0;
    $this->page->get();

    /* get rights */
    $this->allow_content_edition = $this->check_right(1); 
    $this->allow_rights_edition = $this->check_right(3);

    $this->page->allow_content_edition = $this->allow_content_edition;
    $this->page->allow_rights_edition = $this->allow_rights_edition;

    /* get page content */
    $this->page->get_fromHeader();

    /* save page */
    if ($this->page->save()) {
      $this->text = $this->get_translation('save', array( "'".$this->page->name."'") );
      if ( $_REQUEST['next'] == '' ) {
	    $this->set_redirect ($this->get_adminLink(array('mode'=>'modify', 'page_id'=> $this->page->id )));
      } else {
	    $n = $_REQUEST['next'];
	    $m = $this->page->modules[$n]['name'];
	    $id = $this->page->modules[$n]['content'];
	    $this->set_redirect ($camyks->get_adminLink($m, array('id'=>$id, 'page_id'=> $this->page->id, 'module_index' => $n )));
      }
    } else {
      $this->text = $this->get_translation('savefailed', array( "'".$this->page->name."'"));
      if ($this->page->id == 0) {
	    $this->set_redirect($camyks->get_adminLink($m));
      } else {
	    $this->set_redirect($this->get_adminLink(array('mode'=>'modify', 'page_id'=> $this->page->id)));
      }
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }
  
  /*
   * initialise module object in admin/delete mode
   * @return void
   * @access private
   */
  private function init_admin_delete() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();
    
    /* get page */
    $this->page->id = $this->page_id;
    $this->page->get();
    if ($this->page->has_children()) {
      $this->text = $this->get_translation('deletepagefailed_haschildren', array("'".$this->page->name."'"));
      $this->set_redirect($this->get_adminLink(array('opened'=>$this->page->parent_id)));
    } else {
      $this->page->delete_fromDatabase();
      $this->text = $this->get_translation('deletepage', array( "'".$this->page->name."'"));
      $this->set_redirect($this->get_adminLink(array('opened'=>$this->page->parent_id)));
    }
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * initialise module object in admin/move mode
   * @return void
   * @access private
   */
  private function init_admin_move() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();
    
    /* get page */
    if (isset($_REQUEST['parent_id'])) {
      $newParentId = (int)$_REQUEST['parent_id'];
      $this->page->id = $this->page_id;
      $this->page->get();
      if ($this->page->update_move($newParentId)) {
	    $this->text = $this->get_translation('pagemoved', array( "'".$this->page->name."'"));
	    $this->set_redirect($this->get_adminLink(array('opened'=>$this->page->id)));
	    return;
      }
    }
    $this->set_redirect($this->get_adminLink(array('opened'=>$this->page->parent_id)));
    $this->text = $this->get_translation('modifypageerror', array( "'".$this->page->name."'"));
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }
  
  /*
   * initialise module object in admin/move up mode
   * @return void
   * @access private
   */
  private function init_admin_moveup() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();
    
    /* get page */
    $this->page->id = $this->page_id;
    $this->page->get();
    if ($this->page->update_moveUp()) {
      $this->set_redirect (0, $this->get_adminLink(array('opened'=>$this->page->parent_id)));
      $this->selected_layout = 'admin_empty.html.inc';
      $this->selected_layout_location = 'camyks';
    } else {
      $this->set_redirect ($this->get_adminLink(array('opened'=>$this->page->parent_id)));
      $this->text = $this->get_translation('modifypageerror', array("'".$this->page->name."'"));
      /* update layout */
      $this->selected_layout = 'admin_message.html.inc';
      $this->selected_layout_location = 'camyks';
    }
  }

  /*
   * initialise module object in admin/move up mode
   * @return void
   * @access private
   */
  private function init_admin_movedown() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();
    
    /* get page */
    $this->page->id = $this->page_id;
    $this->page->get();
    if ($this->page->update_moveDown()) {
      $this->set_redirect(0, $this->get_adminLink(array('opened'=>$this->page->parent_id)));
      $this->selected_layout = 'admin_empty.html.inc';
      $this->selected_layout_location = 'camyks';
    } else {
      $this->text = $this->get_translation('modifypageerror', array("'".$this->page->name."'"));
      $this->set_redirect ($this->get_adminLink(array('opened'=>$this->page->parent_id)));
      /* update layout */
      $this->selected_layout = 'admin_message.html.inc';
      $this->selected_layout_location = 'camyks';
    }
  }
  
   /*
   * init module object in admin/edit_config mode
   * @return void
   * @access private
   */
  private function init_admin_edit_config() {
    global $camyks;
    
    /* check edit product rights */
    if ($this->check_right(8) === false)
      return $this->init_admin_actionNotAllowed();
    
    $this->get_help();
                      
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array(
        'name'  => 'Configuration',
		'title' => $this->get_translation('configuration'),
    ));
	if ( $this->help != null )
	 	$this->tabBuilder->add_tab(array(
	 	    'name'=>'help',
			'title'=>$camyks->get_translation('help'),
	    ));

    $this->tabBuilder->initialise(array('default'=>'Configuration'));
    
    /* load config form */
    $this->editform = new HTMLForm(
        'edit_config',
		$this->get_adminlink(array('mode'=>'save_config')),
		'POST'
	);
	
	$this->initialise_configEdition($this->editform);
	$this->isConfig = false;
				   
    /* build title */
    $this->adminTitle = $this->title;
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('configuration');
    
    /* build button list */
    $this->buttons = array(
        array(
            'link'  => $this->get_adminLink(array('openTab'=>'Configuration')),
	        'title' => $camyks->get_translation('back'),
	    ),
		array(
		    'link'  => $this->editform->get_HTMLSubmitLink(),
			'title' => $camyks->get_translation('valid'),
		),
	);
    
    /* update layout */
    $this->selected_layout = 'admin_edit_config.html.inc';
  }
  
  /* 
   * init module object in admin/save_config mode
   * @return void
   * @access private
   */
  private function init_admin_save_config() {
    global $camyks;
    
    /* check user rights */
    if ($this->check_right(8) === false)
      return $this->init_admin_actionNotAllowed();

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    /* save object */
    $this->config->get_fromHeader();
    if ($this->config->save()) {
      $this->text = $this->get_translation('config_saved');
    } else {
      $this->text = $this->get_translation('config_notsaved');
    }
    
    /* update layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array('openTab'=>'Configuration')));
  }

  /*
   * get all pages in admin mode
   * @return void
   * @access private
   */
  private function get_adminPages() {
    $this->pages = $this->page->get_adminPagesTree();
  }

  /*
   * get all pages in visit mode
   * @param string $lg
   * @param string $where
   * @return array
   * @access public
   */
  public function get_sitePages($lg=null, $where='') {
    if ($this->pages == null)
      $this->pages = $this->page->get_pagesList($lg, $where);
    return $this->pages;
  }

  /*
   * return page link
   * @param mixed $page
   * @param string $lg
   * @param array $param
   * @return string
   * @access public
   */
  public function get_sitePageLink($page='', $lg='', $params=array()) {
  
    /* no page, no link */
    if ( $page == '' )
      return '';
            
    /* check with loaded pages */
    if (isset($this->pages[$page]))
      return $this->pages[$page]->get_siteLink($params, $lg);
          
    /* load page as single one */
    $p = new ContentPage( CAMYKS_MODE_SITE, 0);
    if ($p->get($page))
	  return $p->get_siteLink($params, $lg);

    /* page found */
	return '';
  }

  /*
   * return key page link
   * @param string $key
   * @param string $lg
   * @param array $param
   * @return string
   * @access public
   */
  public function get_siteKeyPageLink($key='', $lg='', $params=array()) {
  
    /* no page, no link */
    if ($key == '')
      return '';
    
    /* load page from key */
    $page = $this->get_keyPage($key);
    if ($page == false)
      return '';
    
    /* return site page link */
    return $this->get_sitePageLink($page, $lg, $params);
  }

  /*
   * return homepage link
   * @return string
   * @access public
   */
  public function get_siteHomePageLink() {
    
    /* check if home page is defined */
    if ($this->siteHomePage > 0)
      return $this->pages[$this->siteHomePage]->get_siteLink();
  
    /* load home page from db */
    $p = new ContentPage(CAMYKS_MODE_SITE, 0);
    if ($p->get_homeFromDatabase()) {
      return $p->get_siteLink();
    }
    return '';
  }
  
  /*
   * store homepage
   * @return string
   * @access public
   */
  public function set_siteHomePage($pId) {
    if ($this->siteHomePage > 0)
      return;
    $this->siteHomePage = $pId;
  }

  /*
   * return a new ContentPage object
   * @return ContentPage Object
   * @access public
   */
  public function get_newPage() {
    global $camyks;
    return new ContentPage($camyks->mode, 0);
  }

  /*
   * check current admin user right on given page
   * @param mixed $page
   * @return boolean result
   * @access private
   */
  private function check_pageRights($page) {
    if ($page == 0) {
      return $this->check_right(2);
    } else {
      return $this->pages[$page]->check_rights();
    }
  }
  
  /*
   * build HTML admin page tree
   * @return string
   * @access private
   */
  private function get_sitePagesHtmlCols() {
    $this->htmlcols = array();
    $this->pages[0]->_level = 0;
    $this->pages[0]->_path = 'r';
    $this->build_sitePagesHtmlCols ($this->pages[0]->children, 0, 'r', true, 0);
  }

  /*
   * build HTML admin page tree columns
   * @param array $children
   * @param int $level
   * @param string $root
   * @param boolean $visible
   * @param int $parent_id
   * @return string
   * @access private
   */
  private function build_sitePagesHtmlCols ($children, $level, $root, $visible, $parent_id) {
    global $camyks;

    /* build html */
    $h = '<div style="display:'.($visible?'block':'none').';"';
    $h .= ' id="'.$root.'"';
    $h .= ' class="contentpagemain">';
    $h .= html_getTableHeader(0, 0, 'width:100%;');
    foreach ($children as $child) {
      /* child item shortcut */
      $item = &$this->pages[$child];
      $item->_level = $level+1;
      $item->_path = $root.'-'.$item->id;

      /* check if this item is selected one */
      if ( $this->opened == $item->id or $this->opened == $item->name)
				$this->opened = $root.'-'.$item->id;

      /* build item html div */
      $h .= '<tr>';      
      $h .= '<td class="contentpageitem"';
      $h .= ' id="td_'.$root.'-'.$item->id.'"';
      $h .= ' onmouseover="cpt.rolloveritem('.($level+1).',\''.$root.'-'.$item->id.'\');"';
      $h .= ' onmouseout="cpt.rolloutitem('.($level+1).',\''.$root.'-'.$item->id.'\');"';
      $h .= ' onclick="cpt.openitem('.($level+1).',\''.$root.'-'.$item->id.'\')">';
      $h .= html_getTableHeader( 0, 0, 'width:100%;');
      $h .= '<tr>';
      /* display homepage pict */
      $h .= '<td class="contentpagecolhp" align="center">';
      if ($item->homepage == 1) {
	    $h .= '<img src="'.$this->get_fileURL('img/home.gif').'"';
	    $h .= ' width="12" height="12" border="0" alt="';
	    $h .= $this->get_translation('is_homepage');
	    $h .= '" />';
      } else {
	    $h .= '<img src="'.$this->get_fileURL('img/page.gif').'"';
	    $h .= ' width="9" height="12" border="0" alt="';
	    $h .= $this->get_translation('is_page');
	    $h .= '" />';
      }
      $h .= '</td>';
      /* display page title */
      $h .= '<td class="contentpagecoltxt'.($item->active==0?'dis':'').'" title="'.$item->name.'">';
      $h .= substr($item->name, 0, 18);
      $h .= '</td>';
      if ($this->allowedition) {
	    /* display menu button */
	    $h .= '<td class="contentpagecolimg" align="center">';
	    $h .= '<img id="pageActionsButton'.$item->id.'" src="'.$this->get_fileURL('img/menu_off.gif').'"';
	    $h .= ' width="10" height="10" alt="" border="0" style="cursor:pointer;"';
	    $h .= ' onmouseover="this.src=\''.$this->get_fileURL('img/menu_on.gif').'\';"';
	    $h .= ' onmouseout="this.src=\''.$this->get_fileURL('img/menu_off.gif').'\';';
	    $h .= ' contentPage_closePageActions();"';
	    $h .= ' onclick="contentPage_openPageActions('.$item->id.')" />';
	    $h .= '</td>';
      }
      $h .= '</tr>';
      $h .= html_getTableFooter();
      $h .= '</td>';
      $h .= '</tr>';
    }
    if ($this->allowedition and $this->check_pageRights($parent_id)) {
      /* "add new page" box */
      $h .= '<tr>';
      $h .= '<td class="contentpageadd"';
      $h .= ' onmouseover="this.className=\'contentpageaddroll\';"';
      $h .= ' onmouseout="this.className=\'contentpageadd\';">';
      $h .= html_getTableHeader( 0, 0, 'width:100%;');
      $h .= '<tr>';
      /* display homepage pict */
      $h .= '<td class="contentpagecolhp" align="center">';
      $h .= '<img src="'.$this->get_fileURL('img/add.gif').'" width="10" height="10" alt="" border="0" />';
      $h .= '</td>';
      /* display page title */
      $h .= '<td class="contentpagecoltxt">';
      $h .= $this->get_translation('altercolumn');
      $h .= '</td>';
      $h .= '<td class="contentpagecolimg" align="center">';
      $h .= '<img id="columnActionsButton'.$parent_id.'" src="'.$this->get_fileURL('img/menu_off.gif').'"';
      $h .= ' width="10" height="10" alt="" border="0" style="cursor:pointer;"';
      $h .= ' onmouseover="this.src=\''.$this->get_fileURL('img/menu_on.gif').'\';"';
      $h .= ' onmouseout="this.src=\''.$this->get_fileURL('img/menu_off.gif').'\';';
      $h .= ' contentPage_closeColumnActions();"';
      $h .= ' onclick="contentPage_openColumnActions('.$parent_id.')" />';
      $h .= '</td>';
      $h .= '</tr>';
      $h .= html_getTableFooter();
      $h .= '</td>';
      $h .= '</tr>';
    }
    $h .= html_getTableFooter();
    $h .= '</div>';
    if (!isset($this->htmlcols[$level])) 
      $this->htmlcols[$level] = ''; 
    $this->htmlcols[$level] .= $h;
    $h = '';
    
    /* start building children  */
    foreach ($children as $child) {
      $item = &$this->pages[$child];
	$this->build_sitePagesHtmlCols($item->children, $level+1, $root.'-'.$item->id, false, $item->id);
    }
  }

  /*
   * extract open pages from header opened value
   * @return void
   * @access private
   */
  private function get_openedPages() {
    $t = explode('-', $this->opened);
    $this->opened = array();
    if ( count($t) == 0 )
      return;
    $r = $t[0];
    for ($i=1; $i<count($t); $i++) {
      $r .= '-'.$t[$i];
      $this->opened[] = array('level'=> $i, 'item'=>$r);
    }
  }

  /*
   * get header values in execute request mode
   * @return void
   * @access private
   */
  private function execute_request_get_headerValues() {
    global $camyks;
    $this->request_mode = isset($_REQUEST['pc_mode'])?$_REQUEST['pc_mode']:'page_id';
    $this->opened = isset($_REQUEST['pc_page'])?$_REQUEST['pc_page']:'';
    $this->request_callback = isset($_REQUEST['pc_callback'])?$_REQUEST['pc_callback']:'page_updatevalue';
    $this->theme = $camyks->themes[$camyks->site_conf['admin_default_theme']];
    $this->allowedition = false;
    $this->language = isset($_REQUEST['pc_lg'])?$_REQUEST['pc_lg']:'';
  }

  /* search engine methods */
  
  /*
   * get search results data
   * @param array $lib
   * @param array $ids
   * @return array
   * @access public
   */
  public function get_adminSearchEngineResultsInfos($lib='', $ids=array()) {
    global $camyks;

    switch ($lib) {
    case 'ContentPage':
      if (count($ids) > 1)
	    $w = 'admin_contentpage.id IN('.implode(',', array_keys($ids)).')';
      else
	    $w = 'admin_contentpage.id='.implode(',', array_keys($ids));
      $objs = $this->get_sitePages(null, $w);
      $type = $this->get_translation('pagetitle');
      $results = array();
      foreach ($objs as $pid => $obj) {
	    if ($pid > 0)
	      $results[$pid] = array('title'=>$obj->title, 'type'=>$type, 'link'=>$obj->get_siteLink());
      }
      return $results;
      break;
    }
    return array();
  }

  /*
   * return config value
   * @param string $param
   * @param mixed $default
   * @return mixed
   * @access public
   */
  public function get_configValue($param, $default=false) {
    return $this->config->get_value($param, $default);
  }

  /*
   * return key page from config
   * @param string $key
   * @return mixed
   * @access public
   */
  public function get_keyPage($key) {
    return $this->config->get_keyPage($key);
  }
  
  /*
   * update key page in config
   * @param string $key
   * @param mixed $value
   * @return void
   * @access public
   */
  public function set_keyPage($key, $value=null) {
    return $this->config->set_keyPage($key, $value);
  }

  /*
   * return navigation root from config
   * @param string $key
   * @return mixed
   * @access public
   */
  public function get_navigationRoot($key) {
    return $this->config->get_navigationRoot($key);
  }

  /*
   * initialise finder mode
   * @return void
   * @access private
   */
  private function initialise_finderMode() {
    global $camyks;
    
    /* add javascript for "finder" mode */
    $this->add_JSFile('contentpage_finder.js' );
    $this->add_JSScript('var action_base_url="'.$this->get_adminLink().'";');
    $this->add_JSScript('var site_base_url="'.$camyks->get_confValue('url').'";');
    $this->add_JSScript('var w3c_base_url="http://validator.w3.org/check?uri=";');

    /* add javascript for layered menu */
    $this->add_JSEngineFile('tool/htmlelement.js');
    $this->add_JSEngineFile('tool/clientenv.js');
    $this->add_JSEngineFile('object/cmenu.js');
    $this->add_JSScript('var pageActionsMenu = new CMenu("pageActionsMenu", null, null, "right");');
    $this->add_JSScript('globalCMenu.registerMenu( pageActionsMenu );');
    $this->add_JSScript('var columnActionsMenu = new CMenu("columnActionsMenu", null, null, "right");');
    $this->add_JSScript('globalCMenu.registerMenu( columnActionsMenu );');
    $this->add_JSScript('var modelActionsMenu = new CMenu("modelActionsMenu", "pagesmanagerMenu", null, "right");');
    $this->add_JSScript('globalCMenu.registerMenu( modelActionsMenu );');
    $this->add_JSLoadScript('globalCMenu.init();', true);
    
    /* build layered menu */
    $this->pageActionsMenu = array(/* modify page */
				   array('name' => 'action_modify',
					 'title' => $camyks->get_translation('modify'),
					 'url' => 'javascript:contentPage_pageActionModify()',
					 'icon'=> $this->theme->get_pictURL('edit', 12, 'std')),
				   /* duplicate page 
				  array('name'=>'action_duplicate',
					'title' => $camyks->get_translation('duplicate'),
					'url' => 'javascript:alert()',
					'icon'=> ''),
				  /* delete page */
				   array('name'=>'action_delete',
					 'title' => $camyks->get_translation('delete'),
					 'url' => 'javascript:contentPage_pageActionDelete()',
					 'icon'=> $this->theme->get_pictURL('cross', 12, 'std')),
				   /* preview page */
				   array('name'=>'action_preview',
					 'title' => $camyks->get_translation('preview'),
					 'url' => 'javascript:contentPage_pageActionPreview()',
					 'icon'=> $this->theme->get_pictURL('view', 12, 'std'))
	);
	
	/* W3C validation */
	if ($this->config->vars['action_w3cValidator'] == 1)
	  $this->pageActionsMenu[] = array('name' => 'w3c', 
					 'title' => $this->get_translation('w3c_validation'),
					 'url' => 'javascript:contentPage_pageActionW3CValidation()',
					 'icon'=> $this->theme->get_pictURL('valid', 12, 'std'));
    
    /* add structure modification */   
    if ($this->check_right(4)) {
      /* separator */
      $this->pageActionsMenu[] = array('title'=>'----',
				       'url'=>'');
      /* move */
      $this->pageActionsMenu[] = array('name' => 'action_move',
				       'title' => $this->get_translation('move'),
				       'url' => 'javascript:contentPage_pageActionMove()',
				       'icon'=> $this->theme->get_pictURL('file', 12, 'std'));
      /* move up */
      $this->pageActionsMenu[] = array('name' => 'action_move_up',
				       'title' => $this->get_translation('move_up'),
				       'url' => 'javascript:contentPage_pageActionMoveUp()',
				       'icon'=> $this->theme->get_pictURL('up', 12, 'std'));
      /* move down */
      $this->pageActionsMenu[] = array('name' => 'action_move_down',
				       'title' => $this->get_translation('move_down'),
				       'url' => 'javascript:contentPage_pageActionMoveDown()',
				       'icon'=> $this->theme->get_pictURL('down', 12, 'std'));
    }
    
    /* paste currently moved page */
    $this->columnActionsMenu = array(array('name' => 'action_paste_moved',
					   'title' => $this->get_translation('paste_moved_page'),
					   'url' => 'javascript:contentPage_columnActionPasteMoved()',
					   'icon'=> $this->theme->get_pictURL('file', 12, 'std')),
				     /* new page */
				     array('name' => 'action_new_page',
					   'title' => $this->get_translation('newpage'),
					   'url' => 'javascript:contentPage_columnActionNewPage()',
					   'icon'=> $this->theme->get_pictURL('plus', 12, 'std')));
    
    
    if ($this->check_right(5)) {
      $this->modelActionsMenu=array(/* edit model */
				    array('title'=>$this->get_translation('editmodel'),
					  'url'=>'javascript:contentPage_modelActionEdit()',
					  'icon'=>$this->theme->get_pictURL('edit', 12, 'std')),
				    array('title'=>$this->get_translation('deletemodel'),
					  'url'=>'javascript:contentPage_modelActionDelete()',
					  'icon'=>$this->theme->get_pictURL('cross', 12, 'std')));
    } else {
      $this->modelActionsMenu=array();
    }
    
    /* disable paste moved page button */
    $this->add_JSScript('var movedpage = 0;');
    $this->add_JSLoadScript('document.getElementById("action_paste_moved").style.display="none";');
				 
	/* check opened value */
	$this->opened = explode('.', $this->opened);
	$this->opened = $this->opened[0];
    
    /* get site pages and children */
    $this->get_adminPages();
    /* build html cols with pages */
    $this->get_sitePagesHtmlCols();
        
    /* set opened pages as array */
    $this->get_openedPages();
    
    /* add javascript for exploring page tree */
    $this->add_JSFile ('contentpagetree.js');
    $this->add_JSScript('cpt = new ContentPageTree('.count($this->htmlcols).');');
    $this->add_JSScript('cpt.initialise("r", "contentpageitemroll", "contentpageitem", "contentpageitemsel");');
    foreach ( $this->pages as $page ) {
      if ( isset($page->id ) ) {
					$this->add_JSScript( 'cpt.buildline('.$page->_level
			     .','.$page->id
			     .', "'.$page->_path
			     .'", "'.$page->name
			     .'", "'.$page->get_sitelink(null, $this->language).'");' );
      }
    }
    
    /* add javascript onLoad script to automaticaly open item at startup */
    foreach ($this->opened as $o) {
      $this->add_JSLoadScript( 'cpt.openitem('.$o['level'].', \''.$o['item'].'\');' );
    }
    
    /* delete items alerts */
    $this->add_JSScript('deleteModelMessage="'.string_html2Text($this->get_translation('deletemodelmessage')).'";');
    $this->add_JSScript('deletePageMessage="'.string_html2Text($this->get_translation('deletepagemessage')).'";');
    $this->add_JSScript('movePageMessage="'.string_html2Text($this->get_translation('movepagemessage')).'";');
    $this->add_JSScript('movePageFailedMessage="'.string_html2Text($this->get_translation('movepagefailedmessage')).'";');
  }

  /* Admin_Site extension configuration methods */
  
  /*
   * initialise object in Admin_Site / view configuration mode
   * @return void
   * @access public
   */
  public function initialise_configDisplay() {
    $this->isConfig = true;
    
    /* load pages */ 
    $this->get_adminPages();
  }
  
  /*
   * display object in Admin_Site / view configuration mode
   * @return void
   * @access public
   */
  public function display_configDisplay() {
    $this->load_file('html/configuration/view.html.inc');
  }
  
  /*
   * initialise object in Admin_Site / edit configuration mode
   * @param Object $form
   * @return void
   * @access public
   */
  public function initialise_configEdition($form) {
    global $camyks;
    
    $this->isConfig = true;
    
    /* load data */
    $this->W3CValidatorStatus = $this->config->get_w3cValidatorList();
    $this->OGMetaStatus = $this->config->get_ogMetaStatusList();
    $this->Error404FallBacks = $this->config->get_404FallbackList();
    
    /* update form */
    $this->editform = &$form;
    $this->editform->set_object($this->config);
    $this->editform->add_hidden('keyPageCnt', count($this->config->get_value('keyPages')));
    $this->editform->add_hidden('navAddCnt', count($this->config->get_value('navigation_additional')));
        
    /* load pages */ 
    $this->get_adminPages();
  
    /* add scripts */
    $this->add_JSEngineFile('tool/string.js');
    $this->add_JSFile('ConfigEditor.js');
    $this->add_JSLoadScript('ConfigEditor.set_param("form", "'.$this->editform->name.'");');
    $this->add_JSLoadScript('ConfigEditor.initialise();');
    
    if (isset($camyks->inputs['PageChooser'])) {
	  $this->pc = true;
      $camyks->inputs['PageChooser']->initialise('pageidname', null, 'ConfigEditor.update_selectedPage');
	} else {
	  $this->pc = false;
	}
  }
  
  /*
   * display object in Admin_Site / edit configuration mode
   * @return void
   * @access public
   */
  public function display_configEdition() {
    $this->load_file('html/configuration/edit.html.inc');
  }
    
  /*
   * execute object in Admin_Site / save configuration mode
   * @return void
   * @access public
   */
  public function save_configuration() {
    $this->config->get_fromHeader();
    return $this->config->save();
  }
}
?>