<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Engine / Object Lib
 * Creation Date	: Apr 2007
 * Last Modif Date      : Apr 2007
 * History:
 * * 07-04-xx : Initial file
 *
 * Module Library Text Item Object
 */

class MLTextItem extends ModuleLibraryItem {
  /* engine variables */
  var $name;
  var $folder;
  var $path;
  var $default;
  /* running variables */
  var $value;

  /* constructor */
  function MLTextItem ( $name, $folder, $path, $default='' ) {
    $this->name = $name;
    $this->folder = $folder;
    $this->path = $path;
    $this->default = '';
  }
  
  /* methods */

  /*
   * initialise object
   * @return void
   * @access public
   */
  function initialise() {
    $this->value = $this->default;
  }

  /*
   * get object value
   * @param integer $_libObjId the parent object id
   * @return boolean
   * @access public
   */
  function get( $_libObjId ) {
    /* get file path */
    $this->value = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'.html.inc';
    return true;
  }

  /*
   * save text item
   * @param integer $_libObjId the parent object id
   * @param string $_libName the file header title
   * @return boolean
   * @access public
   */
  function save( $_libObjId, $_libName='Generic Content' ) {
    /* update folder path if needed */
    if ( folder_completePath ( $this->path.'/'.$this->folder,  0771) ) {
      /* write file */
      $header = file_getPHPFileHeader( $_libName.' file', '1.0' );
      $header .= file_getPHPFileFooter();
      $this->filepath = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'.html.inc';
      if ( file_exists($this->filepath ) or $this->value != '' ) {
	return file_write( $this->filepath, $header.$this->value );
      }
      return true;
    }
    return false;
  }

  /*
   * delete object
   * @return boolean
   * @access public
   */
  function delete( ) {
    /* TO DO */
    /* currently, the link to file is broken, we don't delete file */
    return true;
  }

  /*
   * delete item folder and its content
   * @return boolean
   * @access public
   */
  function reset( ) {
    return folder_delete( $this->path.'/'.$this->folder, true );
  }

  /*
   * install objet library
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
    $name = $prefix.$this->name;
  
    $this->value = $this->get_valueFromHeader( $name );
    $this->value = $this->parse_PHPTags( $this->value );
    /* check magic_quote_gpc */
    if ( ini_get('magic_quotes_gpc') ) {
      $this->value = stripslashes( $this->value );
    }
  }

  /*
   * return values as structured array : $name=>$value
   * @return array
   * @access public
   */
  function get_exportedValue ( ) {
    return array( $this->name=>$this->value );
  }
}
?>