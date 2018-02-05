<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Engine / Object Lib
 * Creation Date	: Jul 2007
 * Last Modif Date      : Jul 2007
 * History :
 * * 07-07-xx : Initial File
 *
 * Module Library Localized Text Item Object
 */

class MLTextLocalizedItem extends MLTextItem {
  /* engine variables */
  var $name;
  var $folder;
  var $path;
  var $default;
  /* running variables */
  var $value;

  /* constructor */
  function MLTextLocalizedItem ( $name, $folder, $path, $default='' ) {
    $this->name = $name;
    $this->folder = $folder;
    $this->path = $path;
    $this->default = '';
    $this->value = array();
  }
  
  /* methods */

  /*
   * initialise object
   * @return void
   * @access public
   */
  function initialise() {
    global $camyks;
    $this->value = array();
    foreach ( $camyks->site_conf['editing_languages'] as $l )
      $this->value[$l] = $this->default;
  }

  /*
   * get object value
   * @param integer $_libObjId the parent object id
   * @param string $language the language version to get
   * @return boolean
   * @access public
   */
  function get( $_libObjId, $language=null ) {
    global $camyks;
    $this->value = array();
    if ( isset ( $language ) ) {
      $this->value[$language] = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$language.'.html.inc';
    } else {
      foreach ( $camyks->site_conf['editing_languages'] as $l )
	$this->value[$l] = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$l.'.html.inc';
    }
    return true;
  }

  /*
   * save object
   * @param integer $_libObjId the parent object id
   * @param string $_libName the file header title
   * @return boolean
   * @access public
   */
  function save( $_libObjId, $_libName='Generic Content' ) {
    global $camyks;
    $ok = true;
    /* update folder path if needed */
    if ( folder_completePath ( $this->path.'/'.$this->folder,  0771) ) {
    /* write file */
      $header = file_getPHPFileHeader( $_libName.' file', '1.0' );
      $header .= file_getPHPFileFooter();
      foreach ( $camyks->site_conf['editing_languages'] as $l ) {
	$this->filepath = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$l.'.html.inc';
	if ( file_exists( $this->filepath ) or $this->value[$l] != '' ) {   
	  if ( ! file_write( $this->filepath, $header.$this->value[$l] ) ) 
	    $ok = false;
	}
      }
    }
    return $ok;
  }

  /*
   * delete object
   * @return boolean
   * @access public
   */
  function delete( ) {
    /* TO DO */
    /* currently thelink to file is broken, we don't delete file */
    return true;
  }

  /*
   * delete object library
   * @return boolean
   * @access public
   */
  function reset( ) {
    return folder_delete( $this->path.'/'.$this->folder, true );
  }


  /*
   * install object library
   * @return boolean
   * @access public
   */
  function install() {
    /* create folders in site plugin */
    return folder_completePath ( $this->path.'/'.$this->folder,  0771);
  }

  /*
   * uninstall object library
   * @return boolean
   * @access public
   */
  function uninstall() {
    /* TO DO */
    return true;
  }

  /* 
   * get object value from header
   * @return void
   * @access public
   */
  function get_fromHeader($prefix='') {
    global $camyks;
    
    $name = $prefix.$this->name;
    
    $this->value = array();
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->value[$l] = $this->get_valueFromHeader( $name.'_'.$l );
      $this->value[$l] = $this->parse_PHPTags( $this->value[$l] );
      /* check magic_quote_gpc */
      if ( ini_get('magic_quotes_gpc') ) {
	    $this->value[$l] = stripslashes( $this->value[$l] );
      }
    }
  }

  /*
   * return values as structured array
   * @return array
   * @access public
   */
  function get_exportedValue() {
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