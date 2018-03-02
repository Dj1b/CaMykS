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
 * History :
 *
 * Module Library Database Item Object
 */

class MLDatabaseItem extends ModuleLibraryItem {
  /* engine variables */
  public $name;
  public $datatype; /* text / etext / int / float / date / password / list */
  public $datadesc;
  public $datadesc2;
  public $default;
  /* running variables */
  public $value;

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
    $this->name = $name;
    $this->datatype = $datatype;
    $this->datadesc = $desc;
    $this->datadesc2 = $desc2;
    $this->default = isset($default) ? $default : $this->get_defaultValue();
  }
  
  /* 
   * initialise object with default value
   * @return void
   * @access public
   */
  public function initialise() {
    $this->value = $this->default;
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
      $this->value = $this->get_dateFromHeader($name);
      break;
    case 'text':
    case 'etext':
      $v = (string)$this->get_valueFromHeader($name);
      $v = $this->parse_PHPTags($v);
      if ($this->datadesc2 > 0)
		$v = substr($v, 0, $this->datadesc2);
      $this->value = $v;
      break;
    case 'int':
      $this->value = (int)$this->get_valueFromHeader($name);
      break;
    case 'float':
      $this->value = preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $this->get_valueFromHeader($name)));
      break;
    default:
      $this->value = $this->get_valueFromHeader($name);
      break;
    }
  }
  
  /*
   * get object value from given array
   * @return void
   * @access public
   */
  public function get_fromArray($data) {
    global $camyks;
    
    /* check if value exists in array */
    if (!isset($data[$this->name])) {
      $this->value = $this->default;
      return;
    }

    /* set value from type */ 
    switch ($this->datatype) {
    case 'etext':
      $this->value = $camyks->decode_value($data[$this->name]);
      break;
    case 'text':
      $this->value = stripslashes($data[$this->name]);
      break;
    case 'int':
   	case 'date':
   	  $this->value = (int)$data[$this->name];
      break;
    case 'float':
      $this->value = (float)$data[$this->name];
      break;
    case 'list':
      $this->value = $this->uncompile_listValue($data[$this->name]);
      break;
    default:
      $this->value = $data[$this->name];
      break;
    }
  }

  /*
   * return database description
   * @return mixed
   * @access public
   */
  public function get_databaseDescription() {
    return array(
        'name'      => $this->name,
        'type'      => $this->datatype,
        'desc1'     => $this->datadesc,
        'desc2'     => $this->datadesc2,
        'default'   => $this->default,
    );
  }

  /*
   * return database value
   * @return mixed
   * @access public
   */
  public function get_databaseValue($language=null) {
    global $camyks;
    switch ($this->datatype) {
    case 'int':
    case 'date':
      return ''.$this->value;
    case 'float':
      return preg_replace('/,/', '.', (string)$this->value);
    case 'text':
      return '"'.addslashes($this->value).'"';
    case 'etext':
      return '"'.$camyks->encode_value( $this->value ). '"';
    case 'password':
      return '"'.$this->value.'"';
    case 'list':
      return '"'.$this->compile_listValue($this->value).'"';
    }
  }

  /*
   * return default value
   * @return mixed
   * @access public
   */
  public function get_defaultValue() {
    switch ($this->datatype) {
      case 'int':
      case 'float':
        return 0;
      case 'text':
      case 'etext':
      case 'password':
        return '';
      case 'date':
        return time();
      case 'list':
        return array();
    }
  }

  /*
   * return value as structured array name=>value
   * @return array
   * @access public
   */
  public function get_exportedValue() {
    return array($this->name => $this->value);
  }
  
  /*
   * check value case of given type
   * @param string $type
   * @param mixed $default
   * @return void
   * @access public
   */
  public function check_value($type=null, $default=null) {
    if (!isset($type))
      $type = $this->datatype;

    if (!isset($default))
      $default = $this->default;

    switch ($type) {
      /* generic type */
      case 'int':
      case 'float':
      case 'text':
      case 'etext':
      case 'date':
        break;
      /* specific type */
      case 'symbolic_name':
        $v = $this->value;
        $v = preg_replace('/([^_a-zA-Z0-9]+)/', '', $v);
        if ($v == '') {
	      $v = $default;
        }
        $this->value = $v;
        break;
    }
  }
}
?>