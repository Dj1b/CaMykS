<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Nov 2017
 * Last Modif Date  : Nov 2017
 *
 * Plugin Config Generic Object
 */

abstract class PluginConfig {

  /* vars */
  /* global type */
  public $object_type;
  /* main name */
  public $_libName;
  /* parent module */
  public $_libParent;
  /* content */
  public $_libItems;
  /* library description */
  public $_libDesc;
  /* error management */
  public $_libError;
  /* object name */
  public $name;
  /* exported vars */
  public $vars;
  
  /*
   * constructor
   * @param string $name
   * @param Plugin $plugin
   */
  public function __construct($name, &$plugin) {
    global $camyks;
    $this->object_type = 'PluginConfig';
    $this->name = $name;
    $this->_libParent = $plugin;
    $this->_libItems = array();
    $this->_libName = get_class($this);
    $this->_libDesc = ucwords($plugin->plugin_type).':'.$this->_libParent->name.' Lib:'.$this->_libName;
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
  public function install() {
    return $this->initialise() and $this->save();
  }


  /*
   * uninstall config object
   * @return boolean
   * @access public
   */
  public function uninstall() {
    // return $this->delete();
    return true;
  }


  
  /* 
   * finish config object initialisation
   * @return void
   * @access public
   */
  public function init_config() {
  }

  /* 
   * insert a new item in object
   * @param string $name
   * @param string $type
   * @param string $default
   * @return boolean
   * @access public
   */
  public function add_newItem ( $name, $type, $default=null ) {
    global $camyks;
    /* check item name */
    if ( isset ( $this->_libItems[$name] ) ) {
      $camyks->log_internalerror($this,
				 'Plugin Config Item Definition Error',
				 'Item with name "'.$name.'" already exists in this module config');
      return false;
    }
    $this->_libItems[$name] = new PluginConfigItem( $name, $type, $default );
    return true;
  }


  /*
   * initialise object
   * @return boolean
   * @access public
   */
  public function initialise() {
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
  public function get() {
    if (file_exists($this->_libFile)) {
        
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
  public function save() {
    if (isset($this->vars) and $this->check_data()) {
      /* build config content */
      $content = file_getPHPFileHeader($this->name . ' '. $this->_libName.' file', '1.0');
      $content .= '$this->vars = ' . var_export($this->vars, true) . ';';
      $content .= file_getPHPFileFooter();
      
      /* create folder */
      if (!file_exists($this->_libFolder)) {
	    folder_completePath($this->_libFolder);
      }
      
      /* write file */
      if (file_write($this->_libFile, $content, true))
	    return true;
    }
    return false;
  }
  
  /*
   * delete object file
   * @return boolean
   * @access public
   */
  public function delete() {
    if (file_exists($this->_libFile)) 
      return unlink($this->_libFile);
    return true;
  }

  /*
   * reset object into file
   * @return boolean success
   * @access public
   */
  public function reset() {
    $this->initialise();
    return $this->save();
  }
  
  /*
   * check object items values
   * @return boolean
   * @access public
   */
  public function check_data() {
    return true;
  }

  /*
   * get object items values from header
   * @return void
   * @access public
   */
  public function get_fromHeader() {
    foreach ($this->_libItems as $item) {
      $this->vars[$item->_name] = $item->get_fromHeader();
    }
  }
  
  /* get value 
   * @param string $param
   * @param mixed $default
   * @return mixed
   * @access public
   */
  public function get_value($param='', $default=false) {
    if ($this->vars == null) $this->get();
    if (!isset($this->vars[$param]))
      return $default;
    return $this->_libItems[$param]->check_value($this->vars[$param]);
  }

  /* tool methods */

  /*
   * return locale (to be updated for themes and templates)
   * @param string $str
   * @param mixed $args
   * @return string
   * @access public
   */
  public function get_translation($str, $args=null) {
    return $this->_libParent->get_translation($str, $args);
  }
}
?>