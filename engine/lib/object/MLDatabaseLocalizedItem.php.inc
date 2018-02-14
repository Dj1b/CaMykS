<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Apr 2007
 * Last Modif Date  : Feb 2018
 *
 * Module Library Database Item Object
 */

final class MLDatabaseLocalizedItem extends MLDatabaseItem {

  /*
   * constructor
   * @param string $name
   * @param string $datatype
   * @param string $desc
   * @param mixed $desc2
   * @param mixed $default
   * @return void
   * @access public
   */
  public function __construct($name, $datatype, $desc, $desc2='', $default=null) {
    parent::__construct($name, $datatype, $desc, $desc2, $default);
    $this->value = array();
  }
  
  /*
   * initialise object
   * @return void
   * @access public
   */
  public function initialise() {
    global $camyks;
    foreach ($camyks->get_confValue('editing_languages') as $l) {
      $this->value[$l] = $this->default;
    }
  }

  /*
   * get object value from header
   * @param string $prefix
   * @return void
   * @access public
   */
  public function get_fromHeader($prefix='') {
    global $camyks;
    
    /* set header value name */
    $name = $prefix.$this->name;
    
    /* load value */
    switch ($this->datatype) {
    case 'date':
      foreach ($camyks->get_confValue('editing_languages') as $l) {
	    $this->value[$l] = $this->get_dateFromHeader($name.'_'.$l);
      }
      break;
    case 'text':
    case 'etext':
      foreach ($camyks->get_confValue('editing_languages') as $l) {
	    $v = (string)$this->get_valueFromHeader($name.'_'.$l);
	    $v = $this->parse_PHPTags($v);
	    if ($this->datadesc2 > 0)
	      $v = substr($v, 0, $this->datadesc2);
	    $this->value[$l] = $v;
      }
      break;
    case 'int':
      foreach ($camyks->get_confValue('editing_languages') as $l) {
	    $this->value[$l] = (int)$this->get_valueFromHeader($name.'_'.$l);
      }
      break;
    case 'float':
      foreach ($camyks->get_confValue('editing_languages') as $l) {
	    $this->value[$l] = $this->get_valueFromHeader($name.'_'.$l);
	    $this->value[$l] = preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $this->value[$l]));
      }
      break;
    default:
      foreach ($camyks->get_confValue('editing_languages') as $l) {
	    $this->value[$l] = $this->get_valueFromHeader($name.'_'.$l);
      }
      break;
    }
  }
  
  /*
   * get object values from array
   * @param array $data
   * @return void
   * @access public
   */
  public function get_fromArray($data) {
    global $camyks;
    
    /* check language */
    if (isset ($data['language']))
      $l = $data['language'];
    else
      $l = $camyks->current_language;
      
    /* check if value exists in array */
    if (isset($data[$this->name.'_'.$l]))
      $value = $data[$this->name.'_'.$l];
    elseif (isset($data[$this->name]))
      $value = $data[$this->name];
    else {
      $value = $this->default;
      return;
    }
      
    /* set value */
    switch ($this->datatype) {
    case 'etext':
      $this->value[$l] = $camyks->decode_value($value);
      break;
    case 'text':
      $this->value[$l] = stripslashes($value);
      break;
    case 'int':
    case 'date':
      $this->value[$l] = (int)$value;
      break;
    case 'list':
      $this->value[$l] = $this->uncompile_listValue($value);
    default:
      $this->value[$l] = $value;
      break;
    }
    return;
  }

  /*
   * get exported values
   * @return mixed
   * @access public
   */
  public function get_exportedValue() {
    global $camyks;
    $v = array();
    if (count($this->value) == 1) {
      foreach($this->value as $l => $value) {
	    $v[$this->name.'_'.$l] = $value;
	    $v[$this->name] = $value;
      } 
    } else { 
      foreach($this->value as $l => $value) {
	    $v[$this->name.'_'.$l] = $value;
      }
    }
    return $v;
  }

  /*
   * return database value
   * @param string $l
   * @return void
   * @access public
   */
  public function get_databaseValue($l=null) {
    global $camyks;
    
    /* check if value exists in given language */
    if (!isset($this->value[$l]))
      return $this->default;
    
    /* return value case of type */
    switch ($this->datatype) {
      case 'int':
      case 'date':
        return ''.$this->value[$l];
      case 'float':
        return preg_replace('/,/', '.', (string)$this->value[$l]);
      case 'text':
        return '"'.addslashes($this->value[$l]).'"';
      case 'etext':
        return '"'.$camyks->encode_value($this->value[$l]).'"';
      case 'list':
        return '"'.$this->compile_listValue($this->value[$l]).'"';
    }
  }
}
?>