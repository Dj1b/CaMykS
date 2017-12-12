<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Create Date		: Mar 2007
 * Last Modif Date	: Dec 2017
 *
 * Generic Text Syntax Coloring Engine
 */

final class SyntaxColoringEngine extends Input {
  /* variables */
  private $text;
  public $mode;
  public $content;
  private $modes;
  private $loaded;

  /*
   * constructor
   * @param sting path_type
   */
  public function __construct($path_type) {
    parent::Input('SyntaxColoringEngine', $path_type);
    
    /* set plugin version */
    $this->version = '1.0';
    
    /* set plugin package */
    $this->plugin_package = 'Default';
    
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* initialise plugin variables */
    $this->modes = array('none', 'javascript', 'css');
  }
  
  /* overwrite input methods */

  /*
   * initialise input
   * @param string $text
   * @param string $mode
   * @return void
   * @access public
   */
  public function initialise ($text=null, $mode=null) {
    global $camyks;    
    $this->content='';
    $this->loaded = array();
    
    /* colorise text */
    if ( isset($text) and isset($mode)) {
      $this->execute ($text, $mode);
    }
    
    /* Input generic initialisation */
    parent::initialise();
  }
  
  /*
   * display input
   * @param string $text
   * @param string $mode
   * @return void
   * @access public
   */
  public function display ( $text=null, $mode=null ) {
    /* update data */
    if ( isset ($text) and isset($mode) ) {
      $this->execute ($text, $mode);
    }
    
    /* Input generic display */
    parent::display();
  }

  /* specific methods */
  /*
   * execute colorisation
   * @param string $text
   * @param string $mode
   * @return void
   * @access public
   */
  public function execute($text=null, $mode=null, $params=array()) {
    if (isset($text) and isset($mode)) {
      if (in_array($mode, $this->modes)) {
	    /* load sub engine if needed */
	    if (!in_array( $mode, $this->loaded)) {
	      $this->load_file('mode/'.$mode.'.php.inc');
	      $this->loaded[] = $mode;
	    }
	    /* set mode */
	    eval('$this->mode = new SyntaxColoringEngine_'.$mode.'();');
	    
	    /* color */
	    $this->content = $this->mode->execute($text, $params);
	    return;
      }
    }
    $this->content = '';
    return;
  }
}
?>