<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type	    : Engine / Object Library
 * Creation Date	: Oct 2007
 * Last Modif Date  : Nov 2017
 *	
 * Plugin Config Item Generic Object
 */

final class PluginConfigItem {
  /* vars */
  public $_name;
  private $_type;
  private $_default;

  /*
   * constructor
   * @param string $name
   * @param string $type
   * @param mixed $default
   */
  function __construct($name, $type, $default=null) {
    $this->_name = $name;
    $this->_type = $type;
    $this->_default = isset($default) ? $this->update_type($default) : $this->get_default();
  }

  /*
   * initialise object
   * @return void
   * @access public
   */
  function initialise() {
    return $this->_default;
  }
  
  /*
   * return checked value case of object type
   * @return mixed
   * @access public
   */
  function check_value($value) {
    switch ($this->_type) {
    case 'string':
      return stripslashes($value);
    case 'int':
    case 'integer':
    case 'float':
    case 'boolean':
    case 'array':
    default:
      return $value;
    }
  }

  /*
   * get object value from header
   * @return mixed
   * @access public
   */
  function get_fromHeader() {
    switch ($this->_type) {
    case 'array':
      $value = array();
      if (isset($_REQUEST[$this->_name.'_count_'])) {
	    for ($i=0; $i < $_REQUEST[$this->_name.'_count_']; $i++)
	      if (isset($_REQUEST[$this->_name.'_'.$i]))
	        $value[$i] = $_REQUEST[$this->_name.'_'.$i];
      } else {
	    $s = 0;
	    while (isset($_REQUEST[$this->_name.'_'.$s])) {
	      $value[$s] = $_REQUEST[$this->_name.'_'.$s];
	      $s++;
	    }
      }
      return $value;
    case 'date':
      $name = $this->_name;
      if ( isset ( $_REQUEST[$name] ) ) {
        return $_REQUEST[$name] == -1 ? $this->default : $_REQUEST[$name];
      } else if ( !isset ( $_REQUEST[$name.'_year']) ) {
        return $this->default;
      } else if ( $_REQUEST[$name.'_year'] == 0 ) {
        return 0;
      } else {
        return  mktime(isset($_REQUEST[$name.'_hours'] ) ? $_REQUEST[$name.'_hours'] : 1,
		       isset($_REQUEST[$name.'_minutes'] ) ? $_REQUEST[$name.'_minutes'] : 0,
		       isset($_REQUEST[$name.'_seconds'] ) ? $_REQUEST[$name.'_seconds'] : 0,
		       isset($_REQUEST[$name.'_month'] ) ? $_REQUEST[$name.'_month'] : 1,
		       isset($_REQUEST[$name.'_day'] ) ? $_REQUEST[$name.'_day'] : 1,
		       isset($_REQUEST[$name.'_year'] ) ? $_REQUEST[$name.'_year']:date('Y'));
      }
    case 'string':
    case 'int':
    case 'integer':
    case 'float':
    case 'boolean':
    default:
      return isset($_REQUEST[$this->_name])?$this->update_type($_REQUEST[$this->_name]):$this->_default;
    }
  }

  /*
   * get default value case of object type
   * @return mixed
   * @access public
   */
  function get_default() {
    switch ($this->_type) {
    case 'string':
      return '';
    case 'int':
    case 'integer':
    case 'float':
    case 'date':
      return 0;
    case 'boolean':
      return false;
    case 'array':
      return array();
    default:
      return null;
    }
  }
  
  /*
   * update value type
   * @param mixed $value
   * @return mixed
   * @access public
   */
  function update_type ( $value ) {
    switch ( $this->_type ) {
    case 'string':
      return (string)$value;
    case 'int':
    case 'integer':
      return (int)$value;
    case 'float':
      return preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $value));
    case 'boolean':
      return (bool)$value;
    default:
      return $value;
    }
  }
}
?>