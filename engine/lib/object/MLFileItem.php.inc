<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Jul 2007
 * Last Modif Date  : May 2015
 * History :
 * * 07-07-xx : Initial file
 *
 * Module Library File Item Object
 */

class MLFileItem extends ModuleLibraryItem {
  /* engine variables */
  var $name;
  var $folder;
  var $path;
  var $default;
  /* running variables */
  var $value;
  var $upload;
  var $delete;

  /* constructor */
  function MLFileItem ( $name, $folder, $path, $url ) {
    $this->name = $name;
    $this->folder = $folder;
    $this->path = $path;
    $this->url = $url;
    /* engine values */
    $this->uploadedFileName = '';
    $this->upload = false;
    $this->delete = false;
  }
  
  /* methods */
  
  /*
   * initialise object
   * @return void
   * @access public
   */
  function initialise() {
    $this->value = '';
  }

  /*
   * get object value
   * @param integer $_libObjId the parent object id
   * @return boolean
   * @access public
   */
  function get( $_libObjId ) {
  	/* get file path */
    if ( ($file = $this->exists( $this->path.'/'.$this->get_folder($_libObjId).'/', $this->name.$_libObjId )) != '' )  {
      $this->value = $this->url.'/'.$this->get_folder($_libObjId).'/'.$file;
    }
    return true;
  }

  /*
   * save text item
   * @param integer $_libObjId the parent object id
   * @return boolean
   * @access public
   */
  function save( $_libObjId ) {  
    if ( $this->upload or $this->delete ) {
      /* create parent library object folder */
      folder_completePath ( $this->path.'/'.$this->get_folder($_libObjId),  0771);
      /* try to delete old file */
      $this->delete( $_libObjId );
    }
    
    if ( $this->upload ) {
      /* get file extension */
      if ( preg_match( '/.*\.([^\.]*)/', $_FILES[$this->name]['name'], $ext ) ) 
		$ext = $ext[1];
      else
		$ext = '';
      
      /* add file */
      $path = $this->path.'/'.$this->get_folder($_libObjId).'/'.$this->name.$_libObjId.'.'.$ext;
      
      return (move_uploaded_file($_FILES[$this->name]['tmp_name'], $path) and $this->get($_libObjId));
    }
    
    return true;
  }

  /*
   * delete file
   * @param integer $_libObjId the parent object id
   * @return boolean
   * @access public
   */
  function delete( $_libObjId ) {
    if ( ($file = $this->exists( $this->path.'/'.$this->get_folder($_libObjId).'/', $this->name.$_libObjId )) != '' ) 
      unlink( $this->path.'/'.$this->get_folder($_libObjId).'/'.$file );
    return true;
  }

  /*
   * delete object folder and its content
   * @return boolean
   * @access public
   */
  function reset( ) {
    return folder_delete( $this->path.'/'.$this->get_folder(), true );
  }

  /*
   * install object
   * @return boolean
   * @access public
   */
  function install() {
    /* create folders in site plugin */
    return folder_completePath ( $this->path.'/'.$this->get_folder(),  0771);
  }

  /*
   * uninstall object
   * @return boolean
   * @access public
   */
  function uninstall() {
    /* TO DO */
    return true;
  }

  /* 
   * get object value from header
   * @param string $prefix
   * @return void
   * @access public
   */
  function get_fromHeader($prefix='') {
    /* set header name value */
    $name = $prefix.$this->name;
        
    /* load values */
    if ( isset( $_FILES[ $this->name ] ) and $_FILES[$this->name]['name'] != '') {
      $this->uploadedFileName = $_FILES[$this->name]['name'];
      $this->upload = true;
    } else if ( isset( $_REQUEST[$this->name.'_deletefile']) and $_REQUEST[$this->name.'_deletefile']==1 )
      $this->delete = true;
  }

  /*
   * return object values as structured array $name=>$value
   * @return array
   * @access public
   */
  function get_exportedValue ( ) {
    return array( $this->name=>$this->value );
  }

  /*
   * return object file existence
   * @param string $path the folder path
   * @param string $filebase the file name base
   * @return string
   * @access public
   */
  function exists ( $path, $filebase ) {
    $filelist = glob($path.$filebase.'.*');

    if ( count( $filelist ) == 0 )
      return '';
    else
      return substr($filelist[0], strlen($path));
  }
  
  /*
   * return real file name while uploading it
   * @return string
   * @access private
   */
  function get_uploadedFileName() {
  	return $this->uploadedFileName;
  }
  
  /*
   * return temporary file
   * @return string
   * @access private
   */
  function get_temporaryFileName() {
    if (isset($_FILES[$this->name]['tmp_name']))
      return $_FILES[$this->name]['tmp_name'];
    return '';
  }
  
  /*
   * get updated folder
   * @param integer $id
   * @return path
   * @access private
   */
  function get_folder($_libObjId=0) {
    return preg_replace('/%%ID%%/', $_libObjId, $this->folder);
  }
}
?>