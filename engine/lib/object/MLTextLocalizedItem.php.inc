<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Jul 2007
 * Last Modif Date  : Feb 2018
 *
 * Module Library Localized Text Item Object
 */

final class MLTextLocalizedItem extends MLTextItem {

  /* 
   * constructor
   * @param string $name
   * @param string $folder
   * @param string $path
   * @param string $default
   */
  public function __construct($name, $folder, $path, $default='') {
    parent::__construct();
    $this->value = array();
  }
  
  /*
   * initialise object
   * @return void
   * @access public
   */
  public function initialise() {
    global $camyks;
    $this->value = array();
    foreach ($camyks->get_confValue('editing_languages') as $l)
      $this->value[$l] = $this->default;
  }

  /*
   * get object value
   * @param integer $_libObjId, the parent object id
   * @param string $language, the language version to get
   * @return boolean
   * @access public
   */
  public function get($_libObjId, $language=null) {
    global $camyks;
    $this->value = array();
    if (isset($language)) {
      $this->value[$language] = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$language.'.html.inc';
    } else {
      foreach ($camyks->get_confValue('editing_languages') as $l)
	    $this->value[$l] = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$l.'.html.inc';
    }
    return true;
  }

  /*
   * save object
   * @param integer $_libObjId, the parent object id
   * @param string $_libName, the file header title
   * @return boolean
   * @access public
   */
  public function save($_libObjId, $_libName='Generic Content') {
    global $camyks;
    
    /* initialise result */
    $ok = true;
    
    /* update folder path if needed */
    if (folder_completePath($this->path.'/'.$this->folder,  0771)) {
      /* prepare header */
      $header = file_getPHPFileHeader($_libName.' file', '1.0');
      $header .= file_getPHPFileFooter();
      
      /* write files */
      foreach ($camyks->get_confValue('editing_languages') as $l ) {
	    $this->filepath = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$l.'.html.inc';
	    if (file_exists($this->filepath) or $this->value[$l] != '') {   
	      if (!file_write($this->filepath, $header.$this->value[$l])) 
	        $ok = false;
	    }
      }
    }
    return $ok;
  }

  /* 
   * get object value from header
   * @param strin $prefix
   * @return void
   * @access public
   */
  public function get_fromHeader($prefix='') {
    global $camyks;
    
    $name = $prefix.$this->name;
    
    $this->value = array();
    foreach ($camyks->get_confValue('editing_languages') as $l) {
      $this->value[$l] = $this->get_valueFromHeader($name.'_'.$l);
      $this->value[$l] = $this->parse_PHPTags($this->value[$l]);
      /* check magic_quote_gpc */
      if (ini_get('magic_quotes_gpc')) {
	    $this->value[$l] = stripslashes($this->value[$l]);
      }
    }
  }

  /*
   * return values as structured array
   * @return array
   * @access public
   */
  public function get_exportedValue() {
    $a = array();
    if (count($this->value) == 1) {
      foreach ($this->value as $l => $v) {
	    $a[$this->name] = $v;
	    $a[$this->name.'_'.$l] = $v;
      }
    } else {
      foreach ($this->value as $l => $v) {
	    $a[$this->name.'_'.$l] = $v;
      }
    }
    return $a;
  }
}
?>