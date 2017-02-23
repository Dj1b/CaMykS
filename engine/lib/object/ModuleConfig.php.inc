<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Oct 2007
 * Last Modif Date  : Dec 2014
 * History :
 * * 07-10-xx : Initial file
 * * 08-04-16 : Add 'get_translation' method
 * * 14-12-05 : Add 'get_value' method
 *
 * Module Config Generic Object
 */

class ModuleConfig {
  /* vars */
  /* global type */
  var $object_type;
  /* main name */
  var $_libName;
  /* parent module */
  var $_libParent;
  /* content */
  var $_libItems;
  /* library description */
  var $_libDesc;
  /* error management */
  var $_libError;
  /* object name */
  var $name;
  /* exported vars */
  var $vars;
  
  /*
   * constructor
   * @param string $name
   * @param Module $module
   */
  function ModuleConfig ( $name, &$module ) {
    global $camyks;
    $this->object_type = 'ModuleConfig';
    $this->name = $name;
    $this->_libParent = $module;
    $this->_libItems = array();
    $this->_libName = get_class( $this );
    $this->_libDesc = 'Module:'.$this->_libParent->name.' Lib:'.$this->_libName;
    $this->_libFolder = $this->_libParent->plugin_var_path.'/'.$this->_libName; 
    $this->_libFile = $this->_libFolder.'/'.$this->name.'.php.inc';
    $this->vars = null;
  }

  /* methods */

  /*
   * install config object
   * @return boolean
   * @access public
   */
  function install() {
    return $this->initialise() and $this->save();
  }


  /*
   * uninstall config object
   * @return boolean
   * @access public
   */
  function uninstall() {
    // return $this->delete();
    return true;
  }


  
  /* 
   * finish config object initialisation
   * @return void
   * @access public
   */
  function init_config() {
  }

  /* 
   * insert a new item in object
   * @param string $name
   * @param string $type
   * @param string $default
   * @return boolean
   * @access public
   */
  function add_newItem ( $name, $type, $default=null ) {
    global $camyks;
    /* check item name */
    if ( isset ( $this->_libItems[$name] ) ) {
      $camyks->log_internalerror($this,
				 'Module Config Item Definition Error',
				 'Item with name "'.$name.'" already exists in this module config');
      return false;
    }
    $this->_libItems[$name] = new ModuleConfigItem( $name, $type, $default );
    return true;
  }


  /*
   * initialise object
   * @return boolean
   * @access public
   */
  function initialise() {
    foreach ( $this->_libItems as $name => $item ) {
      $this->vars[$name] = $item->initialise();
    }
    return true;
  }

  /*
   * get object from file
   * @return boolean
   * @access public
   */
  function get() {
    if ( file_exists( $this->_libFile ) ) {
      /* get file "vars" value */
      require $this->_libFile;
      /* check if vars value list exists */
      if ( !isset( $this->vars ))
	    return $this->initialise();
      
      /* complete items */
      foreach ( $this->_libItems as $name => $item ) {
	    if (!isset( $this->vars[$name]))
	        $this->vars[$name] = $item->initialise();
	    else
	        $this->vars[$name] = $item->check_value($this->vars[$name]);
      }
      return true;
    } else {
      return $this->initialise();
    }
    return true;
  }

  /*
   * save object to file
   * @return boolean
   * @access public
   */
  function save() {
    if ( isset($this->vars) and $this->check_data() ) {
      $content = file_getPHPFileHeader( $this->name . ' '. $this->_libName.' file', '1.0');
      $content .= '$this->vars = ' . var_export( $this->vars, true ) . ';';
      $content .= file_getPHPFileFooter();
      
      if ( !file_exists ( $this->_libFolder ) ) {
	    folder_completePath( $this->_libFolder );
      }
      
      if ( file_write( $this->_libFile, $content ) )
	return true;
    }
    return false;
  }
  
  /*
   * delete object file
   * @return boolean
   * @access public
   */
  function delete() {
    if ( file_exists( $this->_libFile ) ) 
      return unlink($this->_libFile);
    return true;
  }

  /*
   * reset object into file
   * @return void
   * @access public
   */
  function reset() {
    $this->initialise();
    $this->save();
  }
  
  /*
   * check object items values
   * @return boolean
   * @access public
   */
  function check_data() {
    return true;
  }

  /*
   * get object items values from header
   * @return void
   * @access public
   */
  function get_fromHeader() {
    foreach ( $this->_libItems as $item ) {
      $this->vars[$item->_name] = $item->get_fromHeader();
    }
  }
  
  /* get value 
   * @param string $param
   * @param mixed $default
   * @return mixed
   * @access public
   */
  function get_value($param='', $default=false) {
    if ($this->vars == null) $this->get();
    if (!isset($this->vars[$param]))
      return $default;
    return $this->_libItems[$param]->check_value($this->vars[$param]);
  }

  /* tool methods */

  /*
   * get locale
   * @param string $str
   * @param mixed $args
   * @return string
   * @access public
   */
  function get_translation( $str, $args=null ) {
    return $this->_libParent->get_translation( $str, $args );
  }

}
?>