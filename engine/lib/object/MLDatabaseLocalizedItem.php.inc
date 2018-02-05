<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Apr 2007
 * Last Modif Date  : Jan 2018
 *
 * Module Library Database Item Object
 */

class MLDatabaseLocalizedItem extends MLDatabaseItem {
  /* engine vars */
  var $name;
  var $datatype; /* text / etext / int / float / date / password  */
  var $datadesc;
  var $datadesc2;
  var $default;
  /* running vars */
  var $value;

  /* constructor */
  function MLDatabaseLocalizedItem ( $name, $datatype, $desc, $desc2='', $default=null ) {
    $this->name = $name;
    $this->datatype = $datatype;
    $this->datadesc = $desc;
    $this->datadesc2 = $desc2;
    $this->value = array();
    $this->default = isset ($default) ? $default : $this->get_defaultValue();
  }
  
  /* methods */

  /*
   * initialise object
   * @return void
   * @access public
   */
  function initialise() {
    global $camyks;
    foreach ($camyks->get_confValue('editing_languages') as $l ) {
      $this->value[$l] = $this->default;
    }
  }

  /*
   * get object value from header
   * @return void
   * @access public
   */
  function get_fromHeader($prefix = '') {
    global $camyks;
    
    /* set header value name */
    $name = $prefix.$this->name;
    
    /* load value */
    switch ( $this->datatype ) {
    case 'date':
      foreach ( $camyks->get_confValue('editing_languages') as $l ) {
	    $this->value[$l] = $this->get_dateFromHeader( $name.'_'.$l );
      }
      break;
    case 'text':
    case 'etext':
      foreach ( $camyks->get_confValue('editing_languages') as $l ) {
	    $v = (string)$this->get_valueFromHeader( $name.'_'.$l );
	    $v = $this->parse_PHPTags( $v );
	    if ( $this->datadesc2>0 )
	      $v = substr( $v, 0, $this->datadesc2 );
	    $this->value[$l] = $v;
      }
      break;
    case 'int':
      foreach ( $camyks->get_confValue('editing_languages') as $l ) {
	    $this->value[$l] = (int)$this->get_valueFromHeader( $name.'_'.$l );
      }
      break;
    case 'float':
      foreach ( $camyks->get_confValue('editing_languages') as $l ) {
	    $this->value[$l] = $this->get_valueFromHeader( $name.'_'.$l );
	    $this->value[$l] = preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $this->value[$l]));
      }
      break;
    default:
      foreach ( $camyks->get_confValue('editing_languages') as $l ) {
	    $this->value[$l] = $this->get_valueFromHeader( $name.'_'.$l );
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
  function get_fromArray( $data ) {
    global $camyks;
    
    /* check language */
    if (isset ( $data['language']))
      $l = $data['language'];
    else
      $l = $camyks->current_language;
      
    /* set value */
    switch ( $this->datatype ) {
    case 'etext':
      $this->value[$l] = isset($data[$this->name.'_'.$l])?$camyks->decode_value($data[$this->name.'_'.$l]):(isset($data[$this->name])?$camyks->decode_value($data[$this->name]):$this->default);
      break;
    case 'text':
      $this->value[$l] = isset ($data[$this->name.'_'.$l])?stripslashes($data[$this->name.'_'.$l]):(isset ($data[$this->name])?stripslashes($data[$this->name]):$this->default);
      break;
    case 'int':
    case 'date':
      $this->value[$l] = isset ($data[$this->name.'_'.$l])?(int)$data[$this->name.'_'.$l]:(isset ($data[ $this->name])?(int)$data[$this->name]:$this->default);
      break;
    case 'list':
      $this->value[$l] = isset($data[$this->name.'_'.$l])?$this->uncompile_listValue($data[$this->name.'_'.$l]):(isset($data[$this->name])?$this->uncompile_listValue($data[$this->name]):$this->default);
    default:
      $this->value[$l] = isset($data[$this->name.'_'.$l])?$data[$this->name.'_'.$l]:(isset($data[$this->name])?$data[$this->name]:$this->default);
      break;
    }
    return;
  }

  /*
   * get exported values
   * @return mixed
   * @access public
   */
  function get_exportedValue() {
    global $camyks;
    $v = array();
    if (count($this->value ) == 1) {
      foreach($this->value as $l=>$value) {
	    $v[$this->name.'_'.$l] = $value;
	    $v[$this->name] = $value;
      } 
    } else { 
      foreach($this->value as $l=>$value) {
	    $v[$this->name.'_'.$l] = $value;
      }
    }
    return $v;
  }

  /*
   * return database value
   * @param string $language
   * @return void
   * @access public
   */
  function get_databaseValue($language=null) {
    global $camyks;
    
    /* check if value exists in given language */
    if (!isset($this->value[$language]))
      return $this->default;
    
    /* return value case of type */
    switch ($this->datatype) {
      case 'int':
      case 'date':
        return ''.$this->value[$language];
      case 'float':
        return preg_replace('/,/', '.', (string)$this->value[$language]);
      case 'text':
        return '"'.addslashes($this->value[$language]).'"';
      case 'etext':
        return '"'.$camyks->encode_value($this->value[$language]).'"';
      case 'list':
        return '"'.$this->compile_listValue($this->value[$language]).'"';
    }
  }
}
?>