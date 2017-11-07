<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Object
 * Creation Date	: Jun 2007
 * Last Modif Date      : Jun 2007
 *
 * FileSystem File Object
 */

class FSFile {
  /* file name */
  var $filename;
  /* parent folder path */
  var $path; 
  /* full file path */
  var $fullpath;
  /* file existence value */
  var $exists;
  /* size in octet/byte */
  var $size;
  /* human readable size */
  var $hsize;
  /* file mime */
  var $mime;
  /* type : first part of mime */
  var $type;
  /* file extension */
  var $ext;
  /* file last opening time */
  var $atime;
  /* file last modification time */
  var $mtime;
  /* file last inode change time */
  var $ctime;
  /* mime description */
  var $mimedesc;
  /* type description */
  var $typedesc;
  /* more information list */
  var $moreinfos;


  /*
   * object constructor
   * @param string $path the path to the file
   * @param string $file the file name
   * @return void
   * @access public
   */
  function FSFile($path='', $file=null) {
    if (isset($file)) {
      $this->filename = $file;
      $this->path = $path;
      $this->fullpath = $path.'/'.$file;
    } else {
      $this->fullpath = $path;
      $p = explode('/', $path );
      $this->filename = array_pop( $p );
      $this->path = implode('/', $p);
    }
    $this->exists = file_exists( $this->fullpath );
    $this->moreinfos = array();
    $this->get();
  }

  /* methods */

  /*
   * get file description
   * @return void
   * @access private
   */
  function get() {
    if ( $this->exists === false ) {
      return;
    }
    /* get file extension */
    if ( preg_match( '/.*\.([^\.]*)/', $this->filename, $ext ) ) 
      $this->ext = $ext[1];
    else
      $this->ext = '';

    /* get mime */
    $this->get_mime();
    /* get stat values */
    $this->get_stat();
    /* get description */
    $this->get_descriptions();
    /* get more infos */
    $this->get_moreInfos();
  }

  /*
   * get file mime
   * @return void
   * @access public
   */
  function get_mime() {
    $this->mime = file_getMime( $this->fullpath, $this->ext );
    $t = explode( '/', $this->mime );
    $this->type = $t[0];
  }


  /* 
   * get file stat
   * @return void
   * @access public
   */
  function get_stat() {
    $stat = stat( $this->fullpath );
    $this->size = $stat['size'];
    $this->atime = $stat['atime'];
    $this->mtime = $stat['mtime'];
    $this->ctime = $stat['ctime'];
    $this->inode = $stat['ino'];
  }

  /*
   * get file description
   * @return void
   * @access public
   */
  function get_descriptions() {
    $this->typedesc = file_getTypeDescription( $this->mime, $this->ext );
    $this->mimedesc = file_getMimeDescription( $this->mime );
    $this->hsize = file_getFileSize( $this->size );
  }

  /*
   * get more info from file
   * @return void
   * @access public
   */
  function get_moreInfos() {
    if ( $this->type == 'image' ) {
      $this->get_imageInfos();
    }
  }

  /*
   * get more info from image file 
   * @return void
   * @access public
   */
  function get_imageInfos() {
    $this->moreinfos = array_merge($this->moreinfos, file_getImageSize( $this->fullpath ));
  }

  /*
   * get mime relative icon
   * @param int $size
   * @param string $styles
   * @return string
   * @access public
   */
  function get_mimeIcon($size=32, $styles='') {
    return file_getMimeIcon($this->mime, $size, $styles);
  }
  
  /*
   * get mime relative icon URL
   * @param int $size
   * @return string
   * @access public
   */
  function get_mimeIconURL($size=32) {
    return file_getMimeIconURL($this->mime, $size);
  }

  /*
   * start file download
   * @param string title overwrite title value
   * @return void
   * @access public
   */
  function download($title=null) {    
    header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
    header('Content-Type: application/octet-stream');
    header('Content-Description: File Transfer');
    header('Content-Length: '.$this->size);
    if (isset($title)) {
      if (!preg_match('/\.'.$this->ext.'$/', $title))
        $title .= '.'.$this->ext;
    } else {
      $title  = $this->filename;
    }
    header('Content-Disposition: attachment; filename="'.$title.'";');
    file_readfile($this->fullpath);
  }
  
  /*
   * send file
   * @param string $title
   * @return void
   * @access public
   */
  function send($title=null) {
    header('Content-Type: '.$this->mime.'');
    if (isset($title)) {
      if (!preg_match('/\.'.$this->ext.'$/', $title))
        $title .= '.'.$this->ext;
    } else {
      $title  = $this->filename;
    }
    header('Content-Disposition: inline; filename="'.$title.'"');
    file_readfile($this->fullpath);
  }
  
  /*
   * return md5 of file
   * @param boolean $raw_output
   * @return string
   * @access public
   */
  function md5($raw_output=false) {
    return md5_file($this->fullpath, $raw_output);
  }
  
  /*
   * return file as base64 data
   * @return string
   * @access public
   */
  public function get_base64Data() {
    return 'data:'.$this->mime.';base64,'.base64_encode(file_get_contents($this->fullpath));
  }
}
?>