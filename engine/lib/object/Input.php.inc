<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Object Lib
 * Creation Date	: Jun 2005
 * Last Modif Date	: May 2007
 * History :
 * * 05-06-xx : Initial File
 * * 07-05-xx : Request mode support
 *
 * Input engine object
 */

class Input extends Plugin {
  /* vars */
  var $title;
  
  /* constructor */
  function Input ( $name, $path_type ) {
    /* Plugin Init */
    parent::Plugin( $name, 'input', $path_type );
    /* internal vars */
    $this->title = $this->name;
    $this->selected_layout = 'input.html.inc';
    /* add language */
    $this->add_translation();
  }

  /* methods */


  /*
   * generic initialisation
   * @return boolean
   * @access public
   */
  function initialise($params=array()) {
    global $camyks;
    return true;
  }

  /*
   * generic display
   * @return boolean
   * @access public
   */
  function display ( ) {
    $this->load_file('html/'.$this->selected_layout);
    return true;
  }
  
  /***************** REQUEST MODE **********************/
  
  /*
   * generic request
   * @return boolean
   * @access public
   */
  function execute_request() {
    echo 'This plugin doesn\'t support requests.';
    return true;
  }

  /***************** LOCALES METHODS *************************/
  /*
   * load correct language file
   * @return void
   * @access public
   */
  function add_translation ( ) {
    global $camyks;
    $camyks->add_translation ( $this->plugin_path.'/locale');
  }

  /*
   * get locale value
   * @param string $value
   * @param mixed $data
   * @return string
   * @access public
   */
  function get_translation ( $value, $data=null ) {
    global $camyks;
    return $camyks->get_translation('input_'.strtolower($this->name).'_'.$value, $data);
  }
}
?>