<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Mar 2007
 * Last Modif Date  : Feb 2018
 *
 * Module Library Item master object
 */

abstract class ModuleLibraryItem {

  /*
   * get value from array
   * @param array $data
   * @return void
   * @access public
   */
  public function get_fromArray($data) {
    $this->value = isset($data[$this->name]) ? $data[$this->name] : $this->default;
  }

  /*
   * get value from header
   * @param string $name
   * @return string
   * @access public
   */
  public function get_valueFromHeader($name) {
    return isset($_REQUEST[$name]) ? $_REQUEST[$name] : $this->default;
  }

  /*
   * get date value from header
   * @param string $name
   * @return integer
   * @access public
   */
  public function get_dateFromHeader($name) {
    if (isset($_REQUEST[$name])) {
      return $_REQUEST[$name] == -1 ? $this->default : (int)$_REQUEST[$name];
    } else if (!isset($_REQUEST[$name.'_year'])) {
      return $this->default;
    } else if ($_REQUEST[$name.'_year'] == 0) {
      return 0;
    } else {
      return mktime(isset($_REQUEST[$name.'_hours']) ? (int)$_REQUEST[$name.'_hours'] : 1,
		     isset($_REQUEST[$name.'_minutes']) ? (int)$_REQUEST[$name.'_minutes'] : 0,
		     isset($_REQUEST[$name.'_seconds']) ? (int)$_REQUEST[$name.'_seconds'] : 0,
		     isset($_REQUEST[$name.'_month']) ? (int)$_REQUEST[$name.'_month'] : 1,
		     isset($_REQUEST[$name.'_day']) ? (int)$_REQUEST[$name.'_day'] : 1,
		     isset($_REQUEST[$name.'_year']) ? (int)$_REQUEST[$name.'_year']:date('Y'));
    }
  }
  
  /*
   * delete php tags from item value
   * @param string $value
   * @return string
   * @access public
   */
  public function parse_PHPTags ($value){
    $tags = array();
    $tags[] = '/<\?[^\?>]*\?>/';
    $tags[] = '/<\?/';
    $tags[] = '/<qss[^>]*>/';
    $tags[] = '/<qss/';
    $tags[] = '/<script[^>]*>[^<]<\/script>/';
    $tags[] = '/<script/';
    return preg_replace ($tags, '', $value);
  }
  
  /* list data type specific methods */
  
  /*
   * compile value 
   * @param array $value
   * @return string
   * @access protected
   */
  protected function compile_listValue($value) {
    /* check value */
    if (!is_array($value))
      return '';
        
    /* define available list separators */
    $listSeparators = array(':', ';', ',', '/', '#', '$');
    
    $v = implode($value);
    
    /* check separator to use */
    $sep = '';
    foreach ($listSeparators as $i) {
      if (strpos($v, $i) === false) {
        $sep = $i;
        break;
      }
    }
    
    if ($sep == '')
      return '';
    
    /* build result */
    return $sep.implode($sep, $value).$sep;
  }
  
  /*
   * uncompile list value
   * @param string $value
   * @return array
   * @access protected
   */
  protected function uncompile_listValue($value) {
    /* assume that it is already uncompiled */
    if (is_array($value))
      return $value;
    
    /* check value */
    if (!is_string($value))
      return array();
    $value = trim($value);
    if ($value == '')
      return array();
    
    /* detect separator */
    $sep = substr($value, 0, 1);
    
    /* check separator */
    if ($sep != substr($value, -1))
      return array();
    
    /* remove first & last separator */
    $v = substr($value, 1, -1);
    if (trim($v) == '')
      return array();
    
    /* return uncompiled value */
    return explode($sep,  $v);
  }
}
?>