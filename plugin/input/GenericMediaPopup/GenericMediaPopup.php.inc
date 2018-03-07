<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date	: Mar 2018
 * Last Modif Date	: Mar 2018
 * 
 * GenericMediaPopup
 * Supported format : 
 * - Picture : Gif, Jpg, PNG
 * - Video : FLV
 * - Animation : SWF
 * - HTML page : htm, html
 * - Youtube video ( http://youtu.be/xxxxxxxxxxxx )
 * - 
 */

final class GenericMediaPopup extends Input {

  private $loaded;
  private $diaporamaPictures;

  /* 
   * constructor
   * @param string $path_type
   */
  function __construct($path_type) {
    global $camyks;
    parent::Input('GenericMediaPopup', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'http://www.camyks.net';
    
    /* register plugin as TinyMCE extension */
    if ($camyks->mode == CAMYKS_MODE_ADMIN)
      $this->register_asExtension('TinyMCEv3');
    
    /* register plugin as Admin_Site extension */
    $this->register_asExtension('Admin_Site');
      
    /* plugin variables */ 
    $this->loaded = false;
    $this->diaporamaPictures = array();
    
    /* load configuration library */
    $this->load_library('GenericMediaPopupConfig');
    
    /* load config */
    $this->config = new GenericMediaPopupConfig('config', $this);
    $this->config->get();
    
    /* check for automatique adding */
    if ($camyks->mode == CAMYKS_MODE_SITE and $this->config->vars['insertion'] == 1) {
      $this->register_asCaMykSEventHandler('onPageLoad');
    }
  }
  
  /* overwrite input methods */

  /*
   * initialise input
   * @param array $params
   * @return void
   * @access public
   */
  public function initialise ($params=array()) {
    global $camyks;
    
    /* build default params */
    $defaultParams = array(
        'objectName'            => 'mp',
        'styleSource'           => 'plugin',
        'styleFile'             => '',
        'clickBkgdToClose'      => 1,
        'enableKeyboard'        => 1,
        'enableFlash'           => 1,
        'enableCloseButton'     => 1,
        'flvControlerColor'     => '1F1F1F',
        'flvControlerAlpha'     => 0.85,
        'flvControlerHeight'    => 20,
        'enableDiaporama'       => 1,
        'diaporamaButtonsShift' => 0,
        'maxWidth'              => 0,
        'directOpenOnMobile'    => 0,
        'isMobile'              => -1, // -1 : undefined / 0 : not mobile / 1 : is mobile //
        'buttonPictures'        => array(
            'close'     => $this->get_fileURL('img/close.gif'),
            'closeOver' => $this->get_fileURL('img/close_r.gif'),
            'left'      => $this->get_fileURL('img/left.gif'),
            'leftOver'  => $this->get_fileURL('img/left_r.gif'),
            'right'     => $this->get_fileURL('img/right.gif'),
            'rightOver' => $this->get_fileURL('img/right_r.gif'),
        ),
    );
    $this->params = array_merge($defaultParams, $this->config->vars, $params);
    
    /* insert style file */
    if ($this->params['styleSource'] == 'theme') {
      /* insert style file from theme */
      if ($this->params['styleFile'] != '') {
        if ( $this->params['theme'] != '' and isset($camyks->themes[$this->params['theme']]))
          $this->theme = &$camyks->themes[$this->params['theme']];
        else
          $this->theme = &$camyks->themes[$camyks->get_confValue('site_default_theme')];
        $this->theme->add_styleFile($this->params['styleSource']);
      }
    } else {
      /* insert style file from input */
      if ($this->params['styleFile'] != '')
        $this->add_styleFile($this->params['styleFile']);
      else
        $this->add_styleFile('mediapopup.css');
    }
    
	/* add scripts */
	$name = $this->params['objectName'];
	
	$this->add_JSFile('mediapopup.js');
	$this->add_JSScript('var '.$name.' = new MediaPopup("'.$name.'");');
	if ( $this->params['enableFlash'] == 1 ) {
	  $this->add_JSFile('swfobject.js');
      $this->add_JSScript($name.'.set_param("flvControlerHeight", '.$this->params['flvControlerHeight'].');');
	  $this->add_JSScript($name.'.set_param("flvControlerColor", "'.$this->params['flvControlerColor'].'");');
	  $this->add_JSScript($name.'.set_param("flvControlerAlpha", '.number_format($this->params['flvControlerAlpha'], 2, '.', '').');');
	  $this->add_JSScript($name.'.set_param("flashMovieURL", "'.$this->get_fileURL('flashPlayer/main.swf').'");');
	  $this->add_JSScript($name.'.set_param("flashControlsURL", "'.$this->get_fileURL('flashPlayer/controls.swf').'");');
	}
	if ( $this->params['directOpenOnMobile'] == 1) {
	  $this->add_JSScript($name.'.set_param("directOpenOnMobile", '.$this->params['directOpenOnMobile'].');');
	  $this->add_JSScript($name.'.set_param("isMobile", '.$this->params['isMobile'].');');
	}
	$this->add_JSScript($name.'.set_param("clickBkgdToClose", '.$this->params['clickBkgdToClose'].');');
	$this->add_JSScript($name.'.set_param("enableKeyboard", '.$this->params['enableKeyboard'].');');
	if ($this->params['maxWidth'] > 0)
	  $this->add_JSScript($name.'.set_param("maxWidth", '.$this->params['maxWidth'].');');
    if ($this->params['enableCloseButton'] == 1) {
	  $this->add_JSScript($name.'.set_param("pictures", "closeButton", "'.$this->params['buttonPictures']['close'].'");');
   	  $this->add_JSScript($name.'.set_param("pictures", "closeButtonOver", "'.$this->params['buttonPictures']['closeOver'].'");');
   	}
   	if ($this->params['enableDiaporama'] == 1) {
	  $this->add_JSScript($name.'.set_param("pictures", "leftButton", "'.$this->params['buttonPictures']['left'].'");');
      $this->add_JSScript($name.'.set_param("pictures", "leftButtonOver", "'.$this->params['buttonPictures']['leftOver'].'");');
  	  $this->add_JSScript($name.'.set_param("pictures", "rightButton", "'.$this->params['buttonPictures']['right'].'");');
	  $this->add_JSScript($name.'.set_param("pictures", "rightButtonOver", "'.$this->params['buttonPictures']['rightOver'].'");');
      $this->add_JSScript($name.'.set_param("diaporamaButtonsShift", '.$this->params['diaporamaButtonsShift'].');');
	}
	$this->add_JSScript($name.'.set_param("baseURL", "'.$camyks->get_confValue('url').'");');
	$cnt = 0;	
	foreach ($this->diaporamaPictures as $picture) 
      $this->add_JSScript($name.'.set_param("diaporama", '.$cnt++.', {picture:"'.$picture['url'].'", title:"'.$picture['title'].'"});');
		
	$this->add_JSScript('var __myMediaPopupObject = '.$name.';');
	$this->add_JSLoadScript($name.'.initialise();');
	$this->add_JSWindowEventScript('resize', $name.'.refresh_position();');
  
    $this->loaded = true;
  }
    
  /*
   * execute handler on body closing
   * @return string
   * @access public
   */
  public function execute_onCaMykSPageLoad() {
    $this->initialise();
  }
  
  /* specific tool methods */
  
  /*
   * add picture to diaporama
   * @param string $url
   * @param string $title
   * @return void
   * @access private
   */
  public function add_pictureToDiaporama($url, $title) {
   $this->diaporamaPictures[] = array('url'=>$url, 'title'=>$title);
   if ($this->loaded)
      $this->add_JSScript($this->params['objectName'].'.set_param("diaporama", '.(count($this->diaporamaPictures)-1).', {picture:"'.$url.'", title:"'.$title.'"});');
  }
  
  /* TinyMCE extension methods */
  
  /*
   * return TinyMCE plugin params
   * @return array
   * @access public
   */
  public function get_tinyMCEPluginParams() {
  	global $camyks;
  	$this->add_JSFile('tinymce_plugin/editor_plugin.js');
  	$this->add_JSFile('tinymce_plugin/langs/'.$camyks->current_language.'.js');
  	return array(
    		'name'=>'genericmediapopup',
    		'buttons'=>array('insertMediaPopupLink'));
  }
  
  /* Admin_Site extension configuration methods */
  
  /*
   * initialise object in Admin_Site / view configuration mode
   * @return void
   * @access public
   */
  public function initialise_configDisplay() {
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
    
    /* update form */
    $this->form = &$form;
    $this->form->set_object($this->config);
  
    /* add scripts *
    $this->add_JSFile('GenericMediaPopupConfig.js');
    $this->add_JSLoadScript('GenericMediaPopupConfig.set_param("form", '.$this->form->name.');');
    $this->add_JSLoadScript('GenericMediaPopupConfig.initialise();');
    */
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