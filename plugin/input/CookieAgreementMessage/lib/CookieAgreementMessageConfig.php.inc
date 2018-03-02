<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Input Config
 * Creation Date	: Feb 2018
 * Last Modif Date	: Feb 2018
 *
 * CookieAgreementMessageConfig configuration object
 */

final class CookieAgreementMessageConfig extends PluginConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  public function CookieAgreementMessageConfig($name, &$parent) {
    parent::__construct($name, $parent);
    
    $this->add_newItem('insertion', 'int', 0);  // 0 : manual / 1 : automatic
    $this->add_newItem('message', 'array', array());
    $this->add_newItem('styleSource', 'string', 'plugin');   // plugin / theme
 	$this->add_newItem('aboutCookie', 'string', '');          // empty / URL / true: send to default cookie page
	$this->add_newItem('remindTTL', 'int', 365);         // days to remind agreement

    $this->add_newItem('location', 'string', 'top'); // top / top-left / top-right / bottom / bottom-left / bottom-right
    

    /* generic initialisation */
    parent::init_config();
  }
  
  /* overwrite pluginConfig methods */
  
  /*
   * get object items values from header
   * @return void
   * @access public
   */
  public function get_fromHeader() {
    global $camyks;
    parent::get_fromHeader();
    
    /* load message for each available languages */
    $this->vars['message'] = array();
    foreach ($camyks->get_confValue('editing_languages') as $language) {
      $this->vars['message'][$language] = isset($_REQUEST['message_'.$language])?$_REQUEST['message_'.$language]:'';
    }
  }
  
  /* specific tool methods */
  
  /*
   * return insertion value list
   * @return array
   * @access public
   */
  public function get_insertionList() {
    return array(
      0 => $this->get_translation('insertion_manual'),
      1 => $this->get_translation('insertion_automatic'),
    );
  }
  
  /*
   * return insertion value title
   * @return string
   * @access public
   */
  public function get_insertionTitle() {
    $l = $this->get_insertionList();
    return $l[$this->vars['insertion']];
  }
  
  /*
   * return style source value list
   * @return array
   * @access public
   */
  public function get_styleSourceList() {
    return array(
      'plugin'  => $this->get_translation('stylesource_plugin'),
      'theme'   => $this->get_translation('stylesource_theme'),
    );
  }
  
  /*
   * return style source value title
   * @return string
   * @access public
   */
  public function get_styleSourceTitle() {
    $l = $this->get_styleSourceList();
    return $l[$this->vars['styleSource']];
  }
  
  /*
   * return location value list
   * @return array
   * @access public
   */
  public function get_locationList() {
    return array(
      'top'             => $this->get_translation('location_top'),
      'top-left'        => $this->get_translation('location_topleft'),
      'top-right'       => $this->get_translation('location_topright'),
      'bottom'          => $this->get_translation('location_bottom'),
      'bottom-left'     => $this->get_translation('location_bottomleft'),
      'bottom-right'    => $this->get_translation('location_bottomright'),
    );
  }
  
  /*
   * return location value title
   * @return string
   * @access public
   */
  public function get_locationTitle() {
    $l = $this->get_locationList();
    return $l[$this->vars['location']];
  }  
}
?>