<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Create Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * TinyMCE input : TinyMCE WebEditor Integration
 *
 * TinyMCE is an external system developped by Moxiecode Systems AB
 * More infos, visit TinyMCE website : http://tinymce.moxiecode.com/
 * Installed TinyMCE version: 3.4.5
 */

class TinyMCEv3 extends Input {
  /* variables */
  var $contentType;
  var $contentValue;
  var $configType;
  var $configValue;
  var $ta_name;
  var $ta_cols;
  var $ta_rows;

  /*
   * constructor
   * @param string $path_type
   */
  function TinyMCEv3 ( $path_type ) {
    parent::Input('TinyMCEv3', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise plugin variables */
    $this->contentType = 'text';
    $this->contentValue = '';
    $this->contentLg = '';
    $this->configType = '';
    $this->configValue = '';
    $this->configMore = array();
    $this->ta_name = 'tinymceta';
    $this->ta_sizex = '100%';
    $this->ta_sizey = '300px;';
    
    /* recommended configs */
    $this->admin_configs = array('default', 'classic', 'simple', 'flash');
    $this->client_configs = array('classic_cs', 'simple_cs', 'textual');
    
    /* available configs */
    $this->specific_configs = array('file', 'text');
    $this->builtin_configs = array_merge(array('advanced'), $this->admin_configs, $this->client_configs);
    $this->configs = array_merge($this->specific_configs, $this->builtin_configs);
  }
  
  /* overwrite input methods */

  /*
   * initialise input 
   * @return void
   * @access public
   */
  function initialise($params=array()) {
    global $camyks;
    
    /* add javascript engine */
    $this->add_JSFile('tiny_mce/tiny_mce.js');
    /* add mail encoding javascript */
    $this->add_JSEngineFile('tool/mail.js');
    /* add current language */
    $this->add_JSPreScript('camyks_language="'.$camyks->current_language.'";');
    
    /* load external plugins */
    $extPlugins = $this->get_registeredExtensions();
    if ( $extPlugins === false ) {
    	$this->add_JSPreScript('camyks_ext_plugins=\'\';');
  		$this->add_JSPreScript('camyks_ext_buttons=\'\';');
    } else {
    	$camyks_ext_plugins = '';
    	$camyks_ext_buttons = array();
    	foreach($extPlugins as $plugin) {
    		$pluginParams = $plugin->get_tinyMCEPluginParams();   		
    		
    		/* add plugin to plugin list */
    		$camyks_ext_plugins .= ',-'.$pluginParams['name'];
    		/* add plugin buttons to buttons list */
    		$camyks_ext_buttons = array_merge($camyks_ext_buttons, $pluginParams['buttons']);
    	}
    	$this->add_JSPreScript('camyks_ext_plugins=\''.$camyks_ext_plugins.'\';');
  		$this->add_JSPreScript('camyks_ext_buttons=\''.implode(',', $camyks_ext_buttons).'\';');
    	$this->add_JSPreScript('camyks_plugin_url=\''.$camyks->get_confValue('url').'/'.$camyks->camyks_plugin_url.'\';');
    	$this->add_JSPreScript('camyks_data_url=\''.$camyks->get_confValue('url').'/'.$camyks->site_data_url.'\';');
    }
    
    
    /* add path mode values */
  	$mode = $camyks->get_confValue('file_path');
  		
  	/* check for boolean mode value */
  	if($mode === false)
  		$mode = 'relative';
  	elseif($mode === true)
  		$mode ='absolute';
  
  	/* return base url from mode */
  	switch ($mode) {
  		case 'absolute':
  		case 'absolute_long':
  			$this->add_JSPreScript('camyks_relative_urls=false;');
  			$this->add_JSPreScript('camyks_remove_host=false;');
  			break;
  		case 'absolute_short':
  			$this->add_JSPreScript('camyks_relative_urls=false;');
  			$this->add_JSPreScript('camyks_remove_host=true;');
  			break;
  		case 'relative':
  		default:
  			$this->add_JSPreScript('camyks_relative_urls=true;');
  			$this->add_JSPreScript('camyks_remove_host=true;');
  			break;
  	}
    
    /* check config */
    if (!in_array($this->configType, $this->configs )) {
        $this->configType = (isset($camyks->_conf['editor_default_config']) && in_array($camyks->_conf['editor_default_config'], $this->configs))?$camyks->_conf['editor_default_config']:'default';
    }
    switch ( $this->configType ) {
    /* specific configs */
    case 'file':
      $this->add_JSExternFile( $this->configValue );
      break;
    case 'text':
      $this->add_JSScript( $this->configValue );
      break;
    /* built-in configs */
    case 'default':
    case 'advanced':
    case 'classic':
    case 'simple':
      /* get file manager input object */
      if ( isset($this->configMore['fm_path']) and isset($this->configMore['fm_url']))
	    $this->load_fileManager($this->configMore['fm_path'],
				$this->configMore['fm_url'],
				isset($this->configMore['fm_title'])?$this->configMore['fm_title']:'');
      else 
	$this->load_fileManager();
    case 'flash':
      /* get page chooser input object */
      $this->load_pageChooser();
    case 'textual':
    case 'classic_cs':
    case 'simple_cs':
      /* get page theme */
      $this->load_themeCSSFile();
    default:
      $this->add_JSFile ( 'configs/'.$this->configType.'.js' );
      break;
    }
    
    
    /* Input generic initialisation */
    parent::initialise();
  }
  
  /*
   * display input
   * @param string $ta_name
   * @return void
   * @access public
   */
  function display ( $ta_name='' ) {
    /* display with new name */
    if ( $ta_name != '' ) {
      $this->ta_name = $ta_name;
    }
    /* Input generic display */
    parent::display();
  }
  
  /* specific methods */
  
  /*
   * set content infos
   * @param string $contentType
   * @param string $contentValue
   * @return void
   * @access public
   */
  function set_contentInfos ( $contentType='text', $contentValue='', $contentLg='' ) {
    $this->contentType = $contentType;
    $this->contentValue = $contentValue;
    $this->contentLg = $contentLg;
    
    if ($this->contentType == 'file' and !file_exists ( $this->contentValue )) {
      $this->contentType = 'text';
      $this->contentValue = '';
    }
  }
  
  /*
   * set config infos
   * @param string $configType
   * @param string $configValue
   * @return void
   * @access public
   */
  function set_configInfos ( $configType='default', $configValue='', $more=array() ) {
    $this->configType = $configType;
    $this->configValue = $configValue;
    $this->configMore = $more;
  } 

  /*
   * set textarea size
   * @param string $name
   * @param string $sx
   * @param string $sy
   * @return void
   * @access private
   */
  function set_textareaInfos( $name='tinymceta', $sx=null, $sy=null ) {
    $this->ta_name = $name;
    if ( isset ( $sx ) )
      $this->ta_sizex = $sx;
    if ( isset ( $sy ) ) 
      $this->ta_sizey = $sy;
  }

  /*
   * load page theme
   * @param integer $pageid
   * @return void
   * @access public
   */
  function load_themeCSSFile ( $pageid=null ) {
    global $camyks;
    $theme = '';

    if ( !isset($pageid) and isset( $_REQUEST['page_id'] ) ) 
      $pageid = $pageid;

    if ( isset ($pageid ) ) {
      /* get page information */
      $page = new ContentPage( $pageid );
      $page->get_fromDatabase();
      $theme = $page->theme;
    }

    if ( $theme == '' ) {
      $theme = $camyks->site_conf['site_default_theme'];
    }

    if ( isset ( $camyks->themes[ $theme ] ) ) {
      $theme = $camyks->themes[ $theme ]->get_editorCSSURL();
    } else {
      $theme = $this->theme->get_editorCSSURL();
    }
    
    /* add script before tinymce config init */
    $this->add_JSPreScript('camyks_css_file="'.$theme.'";');   
}

  /*
   * load filemanager input
   * @param string $fpath
   * @param string $furl
   * @param string $ftitle
   * @return void
   * @access public
   */
  function load_fileManager( $fpath='', $furl='', $ftitle='' ) {
    global $camyks;
    /* check input availability */
    if ( isset( $camyks->inputs['FileManager'] )) {
      
      /* get input */
      $this->filemanager = &$camyks->inputs['FileManager'];
      $this->filemanager->set_engineValues('requestlink');
      $this->filemanager->set_selectionValues('image_updatevalue');
      if ( $fpath != '' and $furl != '') {
	    $this->filemanager->set_folderValues ( $fpath, $furl, $ftitle );
      }
      $this->filemanager->initialise( );
      /* add javascripts callback */
      $this->add_JSScript('function image_callback( field_name, field_value, type, win ) {');
      $this->add_JSScript('icb_win = win;');
      $this->add_JSScript('icb_field = field_name;');
      $this->add_JSScript($this->filemanager->get_link( 'field_value' ));
      $this->add_JSScript('}');
      $this->add_JSScript('function image_updatevalue ( url ) {');
      $this->add_JSScript('icb_win.document.forms[0].elements[icb_field].value = url;');
      $this->add_JSScript('}');
    } else {
      /* send error message when input is not available */
      $this->add_JSScript('function image_callback() {');
      $this->add_JSScript('alert("FileManager Input not found.");');
      $this->add_JSScript('}');
    }
  }
  
  /*
   * load pagechooser input
   * @return void
   * @access public
   */
  function load_pageChooser( ) {
    global $camyks;
    $this->add_JSFile('editor.js');
  
  	/* check input availability */
    if ( isset ( $camyks->inputs['PageChooser'] ) ) {
      /* get input */
      $this->pagechooser = &$camyks->inputs['PageChooser'];
      $this->pagechooser->initialise('pagelink', '', 'page_updatevalue');
			$this->add_JSScript('isPageChooserAvailable = true;');
			/* add content languages */
    	$this->add_JSScript('editing_languages = new Array("'.implode('", "', $camyks->get_confValue('editing_languages')).'");', true);
			$this->add_JSScript('site_languages = new Array("'.implode('", "', $camyks->get_confValue('site_languages')).'");', true);
		} else {
			$this->add_JSScript('isPageChooserAvailable = false;');
		}
  }
  
  /*
   * return selected config list
   * @return array
   * @access public
   */
  function get_configList($mode='admin') {
     switch($mode) {
      case 'admin':
        $c = &$this->admin_configs;
        break;
      case 'client':
        $c = &$this->client_configs;
        break;
      case 'builtin':
        $c = &$this->builtin_configs;
        break;
     }
     $configs = array();
     foreach ( $c as $i ) {
       $configs[$c] = $this->get_translation('config_'.$c);
     }
     return $configs;
  }
}
?>