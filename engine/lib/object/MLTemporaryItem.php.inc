<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: May 2007
 * Last Modif Date  : Apr 2016
 * History:
 * * 07-05-xx : Initial file
 *
 * Module Library Temporary Item Object
 */

class MLTemporaryItem extends ModuleLibraryItem {
  /* engine vars */
  var $name;
  var $default;
  var $type;
  /* running vars */
  var $value;

  /* constructor */
  function MLTemporaryItem ( $name, $type='', $default='' ) {
    $this->name = $name;
    $this->default = $default;
    $this->type = $type;
  }
  
  /* methods */

  /*
   * initialise object
   * @return void
   * @access public
   */
  function initialise() {
    $this->value = $this->default;
  }
  
  /*
   * get object
   * @return void
   * @access public
   */
  function get() {
    $this->initialise();
  }

  /*
   * get object value from header
   * $param string $prefix
   * @return void
   * @access public
   */
  function get_fromHeader($prefix = '') {
    $name = $prefix.$this->name;
  
    switch ( $this->type ) {
    case 'date':
      $this->value = $this->get_dateFromHeader( $name );
      break;
    case 'text':
    case 'etext':
      $v = (string)$this->get_valueFromHeader( $name );
      $this->value = $this->parse_PHPTags( $v );
      break;
    case 'int':
      $this->value = (int)$this->get_valueFromHeader( $name );
      break;
    case 'float':
      $this->value = $this->get_valueFromHeader( $name );
      $this->value = preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $this->value));
      break;
    default:
      $this->value = $this->get_valueFromHeader( $name );
      break;
    }
  }

  /*
   * return values as structured array $name=>$value
   * @return array
   * @access public
   */
  function get_exportedValue() {
    return array($this->name => $this->value);
  }

  /*
   * get object value from given array
   * @return void
   * @access public
   */
  function get_fromArray( $data ) {
    $this->value = isset ($data[$this->name]) ? $data[ $this->name ] : $this->default;
    return;
  }
}
?>