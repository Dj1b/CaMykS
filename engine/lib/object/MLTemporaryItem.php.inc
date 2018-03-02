<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: May 2007
 * Last Modif Date  : Feb 2018
 *
 * Module Library Temporary Item Object
 */

final class MLTemporaryItem extends ModuleLibraryItem {
  /* engine vars */
  public $name;
  public $default;
  public $type;
  /* running vars */
  public $value;

  /* 
   * constructor
   * @param string $name
   * @param string $type
   * @param mixed $default
   * @return void
   * @access private
   */
  public function __construct($name, $type='', $default='') {
    $this->name = $name;
    $this->type = $type;
    $this->default = $default;
  }
  
  /*
   * initialise object
   * @return void
   * @access public
   */
  public function initialise() {
    $this->value = $this->default;
  }
  
  /*
   * get object
   * @return void
   * @access public
   */
  public function get() {
    $this->initialise();
  }

  /*
   * get object value from header
   * @param string $prefix
   * @return void
   * @access public
   */
  public function get_fromHeader($prefix = '') {
    $name = $prefix.$this->name;
  
    switch ($this->type) {
    case 'date':
      $this->value = $this->get_dateFromHeader($name);
      break;
    case 'text':
    case 'etext':
      $v = (string)$this->get_valueFromHeader($name);
      $this->value = $this->parse_PHPTags($v);
      break;
    case 'int':
      $this->value = (int)$this->get_valueFromHeader($name);
      break;
    case 'float':
      $this->value = $this->get_valueFromHeader($name);
      $this->value = preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $this->value));
      break;
    default:
      $this->value = $this->get_valueFromHeader($name);
      break;
    }
  }

  /*
   * return values as structured array $name=>$value
   * @return array
   * @access public
   */
  public function get_exportedValue() {
    return array($this->name => $this->value);
  }

  /*
   * get object value from given array
   * @param array $data
   * @return void
   * @access public
   */
  public function get_fromArray($data) {
    $this->value = isset ($data[$this->name]) ? $data[$this->name] : $this->default;
  }
}
?>