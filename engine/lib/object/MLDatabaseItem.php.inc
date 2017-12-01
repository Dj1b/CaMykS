<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Apr 2007
 * Last Modif Date  : Apr 2016
 * History :
 * * 07-04-xx : Initial file
 *
 * Module Library Database Item Object
 */

class MLDatabaseItem extends ModuleLibraryItem {
  /* engine variables */
  var $name;
  var $datatype; /* text / etext / int / float / date / password / list */
  var $datadesc;
  var $datadesc2;
  var $default;
  /* running variables */
  var $value;

  /* constructor */
  function MLDatabaseItem ( $name, $datatype, $desc, $desc2='', $default=null ) {
    $this->name = $name;
    $this->datatype = $datatype;
    $this->datadesc = $desc;
    $this->datadesc2 = $desc2;
    $this->default = isset ( $default ) ? $default : $this->get_defaultValue();
  }
  
  /* methods */


  /* 
   * initialise object with default value
   * @return void
   * @access public
   */
  function initialise() {
    $this->value = $this->default;
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
      $this->value = $this->get_dateFromHeader( $name );
      break;
    case 'text':
    case 'etext':
      $v = (string)$this->get_valueFromHeader( $name );
      $v = $this->parse_PHPTags( $v );
      if ( $this->datadesc2>0 )
		$v = substr( $v, 0, $this->datadesc2 );
      $this->value = $v;
      break;
    case 'int':
      $this->value = (int)$this->get_valueFromHeader( $name );
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
  function get_fromArray($data) {
    global $camyks;
        
    switch ( $this->datatype ) {
    case 'etext':
      $this->value = isset($data[ $this->name ]) ? $camyks->decode_value($data[ $this->name ]) : $this->default;
      break;
    case 'text':
      $this->value = isset($data[ $this->name ]) ? stripslashes($data[ $this->name ]) : $this->default;
      break;
    case 'int':
   	case 'date':
   	  $this->value = isset($data[ $this->name ]) ? (int)$data[ $this->name ] : $this->default;
      break;
    case 'float':
      $this->value = isset($data[ $this->name ]) ? (float)$data[ $this->name ] : $this->default;
      break;
    case 'list':
      $this->value = isset($data[ $this->name]) ? $this->uncompile_listValue($data[$this->name]) : $this->default;
      break;
    default:
      $this->value = isset($data[ $this->name ]) ? $data[ $this->name ] : $this->default;
      break;
    }
    return;
  }

  /*
   * return database description
   * @return mixed
   * @access public
   */
  function get_databaseDescription( ) {
    return array(
        'name'      => $this->name,
        'type'      => $this->datatype,
        'desc1'     => $this->datadesc,
        'desc2'     => $this->datadesc2,
        'default'   => $this->default,
    );  
  
    /*
    $s = ' `'.$this->name.'` ';
    $s .= strtoupper ( $this->datadesc );
    if ( $this->datadesc2 != '' ) {
      $s .= '('.$this->datadesc2.')';
    }
    switch ( $this->datatype ) {
    case 'int':
    case 'float':
      $s .= ' default '.$this->default;
      break;
    case 'text':
    case 'etext':
      if ( $this->datadesc == 'varchar')
        $s .= ' default "'.addslashes($this->default).'"';
      break;
    case 'password':
      $s .= ' default ""';
      break;
    case 'date':
      $s .= ' default 0';
      break;
    case 'list':
      $s .= ' default ""';
      break;
    }
    return $s;
    */
  }

  /*
   * return database value
   * @return mixed
   * @access public
   */
  function get_databaseValue($language=null) {
    global $camyks;
    switch ( $this->datatype ) {
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
  function get_defaultValue () {
    switch ( $this->datatype ) {
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
  function get_exportedValue ( ) {
    return array($this->name => $this->value);
  }
  
  /*
   * check value case of given type
   * @param string $type
   * @param mixed $default
   * @return void
   * @access public
   */
  function check_value ( $type=null, $default=null ) {
    if ( !isset($type) )
      $type = $this->datatype;

    if ( !isset($default) )
      $default = $this->default;

    switch ( $type ) {
      /* generic type */
    case 'int':
      
      break;
    case 'float':
      
      break;
    
    case 'text':
    case 'etext':

      break;
    case 'date':
      
      break;
      /* specific type */
    case 'symbolic_name':
      $v = $this->value;
      $v = preg_replace ( '/([^_a-zA-Z0-9])/', '', $v  );
      if ( $v == '' ) {
	    $v = $default;
      }
      $this->value = $v;
      break;
    }
  }
}
?>