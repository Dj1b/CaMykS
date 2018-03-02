<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Engine / Object Lib
 * Creation Date    : Jul 2007
 * Last Modif Date  : Feb 2018
 *
 * Module Library File Item Object
 */

class MLFileItem extends ModuleLibraryItem {
  /* engine variables */
  public $name;
  public $folder;
  public $path;
  public $default;
  /* running variables */
  public $value;
  public $upload;
  public $delete;

  /*
   * constructor
   * @param string $name
   * @param string $folder
   * @param string $path
   * @param string $url
   */
  public function __construct($name, $folder, $path, $url) {
    $this->name = $name;
    $this->folder = $folder;
    $this->path = $path;
    $this->url = $url;
    /* engine values */
    $this->uploadedFileName = '';
    $this->upload = false;
    $this->delete = false;
  }
    
  /*
   * initialise object
   * @return void
   * @access public
   */
  public function initialise() {
    $this->value = '';
  }

  /*
   * get object value
   * @param integer $_libObjId, the parent object id
   * @return boolean
   * @access public
   */
  public function get($_libObjId) {
      /* get file path */
    if (($file = $this->exists($this->path.'/'.$this->get_folder($_libObjId).'/', $this->name.$_libObjId)) != '')  {
      $this->value = $this->url.'/'.$this->get_folder($_libObjId).'/'.$file;
    }
    return true;
  }

  /*
   * save file item
   * @param integer $_libObjId, the parent object id
   * @return boolean
   * @access public
   */
  public function save($_libObjId) {  
    if ($this->upload or $this->delete) {
      /* create parent library object folder */
      folder_completePath ($this->path.'/'.$this->get_folder($_libObjId),  0771);
      /* try to delete old file */
      $this->delete($_libObjId);
    }
    
    if ($this->upload) {
      /* get file extension */
      if ( preg_match( '/.*\.([^\.]*)/', $this->uploadedFileName, $ext ) ) 
        $ext = $ext[1];
      else
        $ext = '';
      
      /* add file */
      $path = $this->path.'/'.$this->get_folder($_libObjId).'/'.$this->name.$_libObjId.'.'.$ext;
      if (!move_uploaded_file($this->uploadedTempName, $path) and $this->get($_libObjId))
        return false;
            
      /* auto rotate picture with orientation in exif */
      $this->update_orientation($path);
    }
    
    return true;
  }

  /*
   * delete file
   * @param integer $_libObjId, the parent object id
   * @return boolean
   * @access public
   */
  public function delete($_libObjId) {
    if (($file = $this->exists( $this->path.'/'.$this->get_folder($_libObjId).'/', $this->name.$_libObjId )) != '')
      unlink($this->path.'/'.$this->get_folder($_libObjId).'/'.$file);
    return true;
  }

  /*
   * delete object folder and its content
   * @return boolean
   * @access public
   */
  public function reset() {
    return folder_delete($this->path.'/'.$this->get_folder(), true);
  }

  /*
   * install object
   * @return boolean
   * @access public
   */
  public function install() {
    /* create folders in site plugin */
    return folder_completePath($this->path.'/'.$this->get_folder(),  0771);
  }

  /*
   * uninstall object
   * @return boolean
   * @access public
   */
  public function uninstall() {
    /* TO DO */
    return true;
  }

  /* 
   * get object value from header
   * @param string $prefix
   * @return void
   * @access public
   */
  public function get_fromHeader($prefix='') {
    /* set header name value */
    $name = $prefix.$this->name;
        
    /* load values */
    if (isset($_FILES[$name]) and $_FILES[$name]['name'] != '') {
      $this->uploadedFileName = $_FILES[$name]['name'];
      $this->uploadedTempName = $_FILES[$name]['tmp_name'];
      $this->upload = true;
    } else if (isset($_REQUEST[$name.'_deletefile']) and $_REQUEST[$name.'_deletefile']==1)
      $this->delete = true;
  }

  /*
   * return object values as structured array $name=>$value
   * @return array
   * @access public
   */
  public function get_exportedValue() {
    return array($this->name=>$this->value);
  }

  /*
   * return object file existence
   * @param string $path the folder path
   * @param string $filebase the file name base
   * @return string
   * @access public
   */
  public function exists($path, $filebase) {
    $filelist = glob($path.$filebase.'.*');

    if (count($filelist) == 0)
      return '';
    else
      return substr($filelist[0], strlen($path));
  }
  
  /*
   * return real file name while uploading it
   * @return string
   * @access public
   */
  public function get_uploadedFileName() {
      return $this->uploadedFileName;
  }
  
  /*
   * return temporary file
   * @return string
   * @access public
   */
  public function get_temporaryFileName() {
    return $this->uploadedTempName;
  }
  
  /*
   * get updated folder
   * @param integer $id
   * @return path
   * @access public
   */
  public function get_folder($_libObjId=0) {
    return preg_replace('/%%ID%%/', $_libObjId, $this->folder);
  }
  
  /*
   * check orientation and auto rotate picture
   * @param string $picture
   * @return boolean result
   * @access protected
   */
  protected function update_orientation($picture='') {
        
    /* load picture exif */
    $exif = @exif_read_data($picture);
        
    /* no exif data, quit */
    if ($exif === false)
      return true;
    
    /* check orientation from exif */
    if (isset($exif['Orientation']))
      $orientation = $exif['Orientation'];
    elseif (isset($exif['COMPUTED']['Orientation']))-
      $orientation = $exif['COMPUTED']['Orientation'];
    else
      return true;
    
    /* orientation is correct, quit */
    if ($orientation == 1)
      return true;
        
    /* rotate picture to follow given orientation */
    $img = new CImage($picture);
    $img->update_JPGQuality(90);
    
    switch($orientation) {
        case 3:
            $img->rotate(array('angle'=>180));
            break;
        case 6:
            $img->rotate(array('angle'=>-90));
            break;
        case 8:
            $img->rotate(array('angle'=>90));
            break;
    }
    
    $img->save_image($picture);
    return true;
  }
}
?>