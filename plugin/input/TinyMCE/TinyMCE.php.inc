<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Create Date		: Mar 2007
 * Last Modif Date	: Mar 2007
 * 
 * TinyMCE input : TinyMCE WebEditor Integration
 *
 * TinyMCE is an external system developped by Moxiecode Systems AB
 * More infos, visit TinyMCE website : http://tinymce.moxiecode.com/
 * Installed TinyMCE version: 2.1.0
 *
 * Actual built-in config :
 * * default : adapted to nearly all situation
 * * simple : really limited editor
 */

class TinyMCE extends Input {
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
  function TinyMCE ( $path_type ) {
    parent::Input('TinyMCE', $path_type);
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
    $this->configType = 'default';
    $this->configValue = '';
    $this->ta_name = 'tinymceta';
    $this->ta_sizex = '100%';
    $this->ta_sizey = '300px;';
  }
  
  /* overwrite input methods */

  /*
   * initialise input 
   * @return void
   * @access public
   */
  function initialise ($params=array()) {
    global $camyks;
    /* add javascript engine */
    $this->add_JSFile('tiny_mce/tiny_mce.js');
    /* add mail encoding javascript */
    $this->add_JSEngineFile('tool/mail.js');
    /* add current language */
    $this->add_JSPreScript('camyks_language="'.$camyks->current_language.'";');

    /* check config */
    if ( !(in_array($this->configType, array( 'file', 'text', 'default', 'simple' ) ) ) ) {
      $this->configType = 'default';
    }
    switch ( $this->configType ) {
    case 'file':
      $this->add_JSExternFile( $this->configValue );
      break;
    case 'text':
      $this->add_JSScript( $this->configValue );
      break;
    case 'default':
      /* get page theme */
      $this->load_themeCSSFile();
      /* get file manager input object */
      $this->load_fileManager();
      /* get page chooser input object */
      $this->load_pageChooser();
      $this->add_JSFile ( 'configs/default.js' );
    default:
      $this->add_JSFile ( 'configs/'.$this->configType.'.js' );
      break;
    }
    /* add more information for specific config */
    switch ( $this->configType ) {
    case 'default':
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
  function set_contentInfos ( $contentType='text', $contentValue='' ) {
    $this->contentType = $contentType;
    $this->contentValue = $contentValue;
    
    if ( $this->contentType == 'file' and file_exists ( $this->contentValue ) ) {

    } else {
      $this->contentType == 'text';
    }
  }
  
  /*
   * set config infos
   * @param string $configType
   * @param string $configValue
   * @return void
   * @access public
   */
  function set_configInfos ( $configType='default', $configValue='' ) {
    $this->configType = $configType;
    $this->configValue = $configValue;
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
      $this->add_JSScript('function image_callback( field_name, url, type, win ) {');
      $this->add_JSScript('icb_win = win;');
      $this->add_JSScript('icb_field = field_name;');
      $this->add_JSScript('icb_value=icb_win.document.forms[0].elements[icb_field].value;');
      $this->add_JSScript($this->filemanager->get_link( 'icb_value' ));
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
    /* check input availability */
    if ( isset ( $camyks->inputs['PageChooser'] ) ) {
      /* get input */
      $this->pagechooser = &$camyks->inputs['PageChooser'];
      $this->pagechooser->initialise('pagelink', '', 'page_updatevalue');
      /* add javascripts callback */
      $this->add_JSScript('function page_callback( field_name, win ) {');
      $this->add_JSScript('icb_win = win;');
      $this->add_JSScript('icb_field = field_name;');
      $this->add_JSScript('icb_value = icb_win.document.forms[0].elements[icb_field].value;');
      $this->add_JSScript($this->pagechooser->get_link( 'icb_value' ));
      $this->add_JSScript('}');
      $this->add_JSScript('function page_updatevalue ( url ) {');
      $this->add_JSScript('icb_win.document.forms[0].elements[icb_field].value = url;');
      $this->add_JSScript('setTimeout(\'icb_win.focus();\', 500);');
      $this->add_JSScript('}');    
    } else {
      $this->add_JSScript('function page_callback() {');
      $this->add_JSScript('alert("FileManager Input not found.");');
      $this->add_JSScript('}');      
    }
  }
}
?>