<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Engine / Object Lib
 * Creation Date	: Jun 2005
 * Last Modif Date	: Feb 2018
 *
 * Input engine object
 */

class Input extends Plugin {
  /* vars */
  public $title;
  public $selected_layout;
  
  /* 
   * constructor
   * @param string $name
   * @param string $path_type
   * @return void
   * @access public
   */
  public function __construct($name, $path_type) {
    /* Plugin Init */
    parent::Plugin($name, 'input', $path_type);
    
    /* initialise internal vars */
    $this->title = $this->name;
    $this->selected_layout = 'input.html.inc';
    
    /* add language */
    $this->add_translation();
  }
  
  /*
   * alias to constructor
   * @param string $name
   * @param string $path_type
   * @return void
   * @access public
   */
  public function input($name, $path_type) {
    $this->__construct($name, $path_type);
  }

  /* basic methods */

  /*
   * generic initialisation
   * @param array $params
   * @return boolean
   * @access public
   */
  public function initialise($params=array()) {
    global $camyks;
    return true;
  }

  /*
   * generic display
   * @return boolean
   * @access public
   */
  public function display() {
    $this->load_file('html/'.$this->selected_layout);
    return true;
  }
  
  /* request mode methods */
  
  /*
   * execute input object in request mode
   * @return boolean
   * @access public
   */
  public function execute_request() {
    global $camyks;    
    
    /* throw a fatal error, if not overwritten */
    $camyks->add_generic_translation();
    $camyks->throwFatalError(array(
        'title'         => $camyks->get_translation('error_fatalerror'),
        'description'   => $camyks->get_translation('error_plugin_doesnt_support_requests_desc'),
        'content1'      => $camyks->get_translation('error_plugin_doesnt_support_requests_content'),
        'back_title'    => $camyks->get_translation('error_plugin_doesnt_support_requests_back_title'),
        'back_link'     => $camyks->get_confValue('url'),
    ));
  }

  /* locales related methods */
  
  /*
   * load correct language file
   * @return void
   * @access public
   */
  public function add_translation() {
    global $camyks;
    $camyks->add_translation($this->plugin_path.'/locale');
  }

  /*
   * get locale value
   * @param string $value
   * @param mixed $data
   * @return string
   * @access public
   */
  public function get_translation($value, $data=null) {
    global $camyks;
    return $camyks->get_translation('input_'.strtolower($this->name).'_'.$value, $data);
  }
  
  /* tool methods */
  
  /*
   * update selected layout
   * @param string $layout
   * @access public
   */
  public function set_selectedLayout($layout='') {
    $this->selected_layout = $layout;
  }
}
?>