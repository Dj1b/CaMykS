<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Jul 2007
 * Last Modif Date  : May 2015
 * History :
 * * 07-07-xx : Initial file
 *
 * Module Library Localized File Item Object
 */

class MLFileLocalizedItem extends MLFileItem {
  /* engine variables */
  var $name;
  var $folder;
  var $path;
  var $url;
  /* running variables */
  var $value;
  var $upload;

  /* constructor */
  function MLFileLocalizedItem ( $name, $folder, $path, $url ) {
    $this->name = $name;
    $this->folder = $folder;
    $this->path = $path;
    $this->url = $url;
    /* engine values */
    $this->uploadedFileName = array();
    $this->upload = array();
    $this->delete = array();
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
    foreach ( $camyks->_conf['editing_languages'] as $l ) {
      $this->value[$l] = '';
    }
  }

  /*
   * get object value
   * @param integer $_libObjId the parent object id
   * @param string $language the language to get
   * @return boolean
   * @aaccess public
   */
  function get( $_libObjId, $language=null ) {
    global $camyks;
    
    $path = $this->path.'/'.$this->get_folder($_libObjId).'/';
    $url = $this->url.'/'.$this->get_folder($_libObjId).'/';
    
    if ( isset( $language ) ) {
      /* get specific language */
      if ( ($file = $this->exists( $path , $this->name.$_libObjId.'_'.$language )) != '' )
	    $this->value[$language] = $url.$file;
      else
	    $this->value[$language] = '';
    } else {
      /* get all language */
      foreach ( $camyks->_conf['editing_languages'] as $language ) {
	    if ( ($file = $this->exists( $path , $this->name.$_libObjId.'_'.$language )) != '' )
	      $this->value[$language] = $url.$file;
	    else
	      $this->value[$language] = '';	
      }
    }
    return true;
  }
  
  /*
   * save text item
   * @param integer $_libObjId the parent object id
   * @return void
   * @access public
   */
  function save( $_libObjId ) {
    $ok = true;
        
    /* check if there is at least one file to upload or delete */
    if ( count( $this->upload ) == 0 and count($this->delete) == 0 )
      return true;
      
    /* create parent library object folder */
    folder_completePath ( $this->path.'/'.$this->get_folder($_libObjId),  0771);
    
    /* try to delete removed files */
    foreach ( $this->delete as $l ) {
      $this->delete( $_libObjId, $l );
    }
    
    /* update files */
    foreach ( $this->upload as $l ) {
      /* try to delete old file */
      $this->delete( $_libObjId, $l );

      /* get file extension */
      if ( preg_match( '/.*\.([^\.]*)/', $_FILES[$this->name.'_'.$l]['name'], $ext ) ) 
	    $ext = $ext[1];
      else
	    $ext = '';
      
      /* add file */
      $path = $this->path.'/'.$this->get_folder($_libObjId).'/';
      $path .= $this->name.$_libObjId.'_'.$l.'.'.$ext;
      if (! move_uploaded_file($_FILES[$this->name.'_'.$l]['tmp_name'], $path) ) 
	    $ok = false;
	  $this->get($_libObjId, $l);
	  
	  /* auto rotate picture with orientation in exif */
      $this->update_orientation($path);
    }
    return $ok;
  }

  /*
   * delete file
   * @param integer $_libObjId the parent object id
   * @param string $language the language
   * @return boolean
   * @access public
   */
  function delete( $_libObjId, $language=null ) {
    global $camyks;
    $path = $this->path.'/'.$this->folder.'/';
    
    if ( isset( $language )) {
      /* delete given language file */
      if ( ($file = $this->exists( $path , $this->name.$_libObjId.'_'.$language )) != '' ) 
	    unlink( $this->path.'/'.$this->get_folder($_libObjId).'/'.$file );
    } else {
      /* delete all files */
      foreach ( $camyks->_conf['editing_languages'] as $language ) {
	    if ( ($file = $this->exists( $path , $this->name.$_libObjId.'_'.$language )) != '' ) 
	      unlink( $this->path.'/'.$this->get_folder($_libObjId).'/'.$file );
      }
    }
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
    global $camyks;
    
    /* set header value name */
    $name = $prefix.$this->name;
    
    /* load values */
    foreach ( $camyks->_conf['editing_languages'] as $language ) {
      if ( isset( $_FILES[ $name.'_'.$language ] ) and $_FILES[$name.'_'.$language]['name'] != '' ) {
        $this->uploadedFileName[$language] = $_FILES[$name.'_'.$language]['name'];
		$this->upload[] = $language;
	  } else if ( isset( $_REQUEST[$name.'_'.$language.'_deletefile']) and $_REQUEST[$name.'_'.$language.'_deletefile']==1 )
      	$this->delete[] = $language;
    }
  }
  
  /*
   * return values as structured array 
   * @return array
   * @access public
   */
  function get_exportedValue ( ) {
    $a = array();
    if ( count( $this->value ) == 0) {
        /* nothing to do */
    } else if ( count( $this->value ) == 1 ) {
      foreach ( $this->value as $l => $v ) {
				$a[$this->name] = $v;
				$a[$this->name.'_'.$l] = $v;
      } 
    } else {
      foreach ( $this->value as $l => $v )
		$a[$this->name.'_'.$l] = $v;
    }
    return $a;
  }
  
  /*
   * return real file name while uploading it
   * @param mixed $language
   * @return string
   * @access private
   */
  function get_uploadedFileName($language=false) {
  	if ($language === false)
  		return $this->uploadedFileName;
  	if (isset($this->uploadedFileName[$language]))
  		return $this->uploadedFileName[$language];
  	return '';
  }
}
?>