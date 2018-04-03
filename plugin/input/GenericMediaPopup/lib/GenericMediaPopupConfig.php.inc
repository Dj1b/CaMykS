<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Input Config
 * Creation Date	: Mar 2018
 * Last Modif Date	: Mar 2018
 *
 * GenericMediaPopup configuration object
 */

final class GenericMediaPopupConfig extends PluginConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  public function __construct($name, &$parent) {
    parent::__construct($name, $parent);
    
    $this->add_newItem('insertion', 'int', 0);  // 0 : manual / 1 : automatic
    $this->add_newItem('styleSource', 'string', 'plugin');   // plugin / theme
    
    /* controls */
    $this->add_newItem('clickBkgdToClose', 'int', 1);
    $this->add_newItem('enableCloseButton', 'int', 1);
    $this->add_newItem('enableKeyboard', 'int', 1);
    $this->add_newItem('maxWidth', 'int', 0);
    
    /* diaporama controls */
    $this->add_newItem('enableDiaporama', 'int', 1);
    $this->add_newItem('diaporamaButtonsShift', 'int', 0);
    
    /* flash controls */
    $this->add_newItem('enableFlash', 'int', 0);
    $this->add_newItem('flvControlerColor', 'string', '1F1F1F');
    $this->add_newItem('flvControlerAlpha', 'float', 0.85);
    $this->add_newItem('flvControlerHeight', 'float', 20);
    
    /* generic initialisation */
    parent::init_config();
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
}
?>