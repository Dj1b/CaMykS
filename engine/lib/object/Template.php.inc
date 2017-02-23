<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type      : Engine / Object Library
 * Creation Date	: Jun 2005
 * Las Modif Date	: Dec 2007
 *
 * Template engine object
*/

class Template extends Plugin {

  /*
   * constructor
   * @param string $name
   * @param string $path_type ( camyks or site )
   */
  function Template ( $name, $path_type ) {
    parent::Plugin( $name, 'template', $path_type );
  }
  
  /*
   * initialise object
   * @return void
   * @access public
   */
  function initialise() {    
    $this->add_styleFile('style.css');
  }
  
  /*
   * display object
   * @return void
   * @access public
   */
  function display () {
    $this->load_file ('main.html.inc');
  }
  
  /*
   * display object thumb
   * @return void
   * @access public
   */
  function display_thumb () {
    $this->load_file ('thumb.html.inc');
  }

  /*
   * display module object
   * @param integer $module
   * @return void
   * @access private
   */
  function display_module($module) {
    global $camyks;
    $camyks->contentPage->display_module($module);
  }
}
?>