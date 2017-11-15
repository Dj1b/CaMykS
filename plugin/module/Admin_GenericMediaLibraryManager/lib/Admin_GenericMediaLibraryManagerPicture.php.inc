<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date	: Jun 2015
 * Last Modif Date	: Nov 2017
 *
 * Admin_GenericMediaLibraryManagerPicture object for Admin_GenericMediaLibraryManager Module
 */

class Admin_GenericMediaLibraryManagerPicture extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericMediaLibraryManagerPicture ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    
    /* content items */
    $this->add_newItem('gallery', 'db', 'int', 'int unsigned', '', 0);
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('sortPosition', 'db', 'int', 'smallint unsigned', '', 0);
    $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
    
    /* file items */
    $this->add_newItem('original', 'file', 'originals', '', '', '');
    $this->add_newItem('picture', 'file', 'pictures', '', '', '');
    $this->add_newItem('thumb', 'file', 'thumbs', '', '', '');
    
    /* define pictures & thumbs folders */
    $this->foldersUpdated = false;
    $this->autoDisabled = false;
    $this->update_imageFolders();
    $this->isNew = false;

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary method */

  /*
   * check object data
   * @return boolean result
   * @access public
   */
  function check_data() {
    
    /* check for auto disable picture object without a picture file */
    if (!$this->_libItems['original']->upload) {
  	  if ($this->id == 0) {
  	    $this->_libItems['status']->value = 0;
  	    $this->autoDisabled = true;
  	  }
  	  else {
  	    $obj = $this->get_newObject($this->id);
  	    $obj->get();
  	    $obj->get_fromItems();
  	    if ($obj->vars['original'] == '') {
  	      $this->_libItems['status']->value = 0;
  	      $this->autoDisabled = true;
  	    }
  	  }
  	}  
  
    /* check for position */
    if ($this->id == 0) {
        $this->_libItems['sortPosition']->value = $this->get_newPosition();
        $this->isNew = true;
    }
    return true;
  }
  
  /* 
   * save object 
   * @return boolean success
   * @access private
   */
  function save() {
   /* check data validity */
    if ( $this->check_data() ) {
      return $this->save_databaseItems()
        and $this->save_databaseLocalisedItems()
        and $this->update_imageFolders()
	    and $this->save_textItems() 
	    and $this->save_fileItems()
	    and $this->check_forGalleryDefaultPicture();
    }
    return false;
  }
  
  /*
   * get file items
   * @param string $language
   * @return boolean result
   * @access private
   */
  function get_fileItems($language=null) {
    return $this->update_imageFolders() and parent::get_fileItems();
  }

  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    $search = array();
    if ( isset( $params['status'] ) and $params['status'] > -1 )
      $search[] = 'status='.$params['status'];
    if ( isset( $params['gallery'] ) and $params['gallery'] > -1 )
      $search[] = 'gallery='.$params['gallery'];
    return implode(',', $search);
  }

  /* specific tool methods */
    
  /*
   * return single object status list
   * @return array
   * @access private
   */
  function get_statusList() {
    return array(0 => $this->get_translation('picturestatus_inactive'),
                 1 => $this->get_translation('picturestatus_active'),
    );
  }

  /*
   * return multi object status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_multiStatusList($full=false) {
    $list = array();
    if ($full)
      $list['-1'] = $this->get_translation('pictures_all');
    $list['0'] = $this->get_translation('picturesstatus_inactive');
    $list['1'] = $this->get_translation('picturesstatus_active');
    return $list;
  }
  
  /*
   * load config value 
   * @param string $param
   * @return mixed
   * @access private
   */
  function get_configValue($param='') {
    return $this->_libParent->get_configValue($param);
  }
  
  /*
   * update image folders
   * @return boolean success
   * @access private
   */
  function update_imageFolders() {
    if ($this->foldersUpdated) return true;

    if ($this->_libItems['gallery']->value > 0 ) {
      $basePath = 'PictureGallery'.$this->_libItems['gallery']->value;
      $this->_libItems['original']->folder = $basePath.'/'.$this->_libItems['original']->folder;
      $this->_libItems['picture']->folder = $basePath.'/'.$this->_libItems['picture']->folder;
      $this->_libItems['thumb']->folder = $basePath.'/'.$this->_libItems['thumb']->folder;

      $this->foldersUpdated = true;
    }
    return true;
  }

  /*
   * get document count by categories
   * @param array $categories
   * @return array
   * @access public
   */
  function get_pictureCountByGalleries($galleries=null) {

    $list = array();
    /* check categories */
    if ( is_array($galleries) and count($galleries) == 0)
      return $list;

    /* build sql query */
    $sql = 'select gallery,  count(id) as cnt from '.$this->_libSQLTable;
    if (  is_array($galleries) and count($galleries)>0 ) {
      $sql .= ' where gallery in ('.implode(',', $galleries).')';
    }
    $sql .= ' group by gallery';

    /* execute sql query */
    if ( $this->execute_DBQuery($sql, __LINE__ ))
      /* get data from database */
      while ( $data = $this->get_DBQueryDataLine())
	    $list[$data['gallery']] = $data['cnt'];
	    
    /* send results */
    return $list;
  }
  
  /* 
   * check parent gallery for picture as default one
   * @return true
   * @access private
   */
  function check_forGalleryDefaultPicture() {
    $this->get_fromItems();
    
    if ($this->isNew == false or $this->vars['status']==0 or $this->vars['gallery']==0)
      return true;
    
    $gallery = &$this->_libParent->pictureGalleryItem;
    $gallery->id = $this->vars['gallery'];
    $gallery->get();
    $gallery->get_fromItems();
    $gallery->check_forDefaultPicture($this->id);
    return true;
  }
  
  /*
   * optimise picture
   * @return 
   * @access private
   */
  function optimise_picture() {
    /* delete old one */
    $this->_libItems['picture']->delete($this->id);
    
    /* create image path */
    $pictPath = $this->_libItems['picture']->path . '/' . $this->_libItems['picture']->folder;
    folder_completePath($pictPath);
       
    /* create virtual image */
    $img = new CImage($this->vars['original']);
    $img->update_JPGQuality($this->get_configValue('picture_jpgQuality'));
        
    $w = $this->get_configValue('picture_pictureWidth');
    $h = $this->get_configValue('picture_pictureHeight');
    
    if ( $this->get_configValue('picture_resizeMode') == 0) {    
     if ($img->width >= $img->height) {
        /* resize and crop to exact size horizontal picture */
        $img->resize($w, $h, 1);    
        $img->crop($w, $h, '', $this->get_configValue('picture_backgroundColor'));
        $img->sharp();
      } else {
        /* resize and crop to exact size vertical picture */
        $img->resize($w, $h, 2);    
        $img->crop($w, $h, '', $this->get_configValue('picture_backgroundColor'));
        $img->sharp();
      }
    } else {
       if ($img->width <= $this->get_configValue('picture_pictureWidth')
          and $img->height <= $this->get_configValue('picture_pictureHeight')) {
        /* picture is smaller than final size : do nothing */
        
      } else {
        /* resize and crop to max size */
        $img->resize($w, $h, 2);    
        $img->sharp();
      }
    }

    return $img->save_image($pictPath.'/picture'.$this->id, $this->get_fileTypeValue());
  }
  
  /*
   * optimise thumb
   * @return CRequestAnswer object
   * @access private
   */
  function optimise_thumb() {
    /* delete old one */
    $this->_libItems['thumb']->delete($this->id);
    
    /* create image path */
    $thumbPath = $this->_libItems['thumb']->path . '/' . $this->_libItems['thumb']->folder;
    folder_completePath($thumbPath);

    /* create virtual image */
    $img = new CImage($this->vars['original']);
    $img->update_JPGQuality($this->get_configValue('picture_jpgQuality'));
        
    $w = $this->get_configValue('picture_thumbWidth');
    $h = $this->get_configValue('picture_thumbHeight');
    
    $img->resize($w, $h, 1);    
    $img->crop($w, $h);
    $img->sharp();

    return $img->save_image($thumbPath.'/thumb'.$this->id, $this->get_fileTypeValue());
  }
  
  /*
   * check if image object has a new original picture
   * @return boolean result
   * @access public
   */
  function has_newPicture() {
    return ($this->_libItems['original']->upload);
  }
  
  /*
   * return image type value
   * @return string
   * @access private
   */
  function get_fileTypeValue() {
    $l = array(0 => '', 1=>'jpg', 2=>'gif', 4=>'png');
    return $l[$this->get_configValue('images_fileType')];
  }
  
  /*
   * check if picture is default picture
   * @return boolean result
   * @access private
   */
  function is_defaultPicture() {
    if ($this->_libParent->pictureGalleryItem->id == $this->vars['gallery'])
      return ($this->_libParent->pictureGalleryItem->vars['defaultPicture'] == $this->id);
    return false;
  }
  
  /*
   * return picture radio button to select default picture
   * @return boolean result
   * @access private
   */
  function get_isDefaultIconRadio() {
    return '<input type="radio" name="defaultPicture" value="'.$this->id.'"'.($this->is_defaultPicture()?' checked="checked"':'').($this->vars['status']==0?' disabled="disabled"':'').' />';
  }
  
  /*
   * return icon indicating if picture is default picture
   * @return boolean result
   * @access private
   */
  function get_isDefaultPictureIcon() {
    if ($this->is_defaultPicture())
        return '<img src="'.$this->_libParent->theme->get_pictURL('target', 12, 'std').'" alt="'.$this->get_translation('ismainimage').'" title="'.$this->get_translation('ismainimage').'" border="0" />';
    return '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="'.$this->get_translation('isnotmainimage').'" title="'.$this->get_translation('isnotmainimage').'" border="0" />';
  }
  
  /*
   * return object list
   * @param array $params
   * @return array
   * @access private
   */
  function get_list($params=array()) {
  	global $camyks;
    
    /* default params list */
    $dParams = array('status'=>-1, 'gallery'=>-1, 'galleries'=>-1, 'ids'=>-1, 'language'=>$camyks->current_language,
    	'limit'=>-1, 'count'=>-1, 'order'=>'sortPosition', 'orderway'=>'asc');
    	
    /* merge params */
    $params = array_merge($dParams, $params);
    
    /* build where statement */
    $w = $this->build_whereStatement($params);
    
    /* return list */
    return $this->get_objectList($params['language'], $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
  }
  
  /*
   * return first object list for given galleries
   * @param array $params
   * @return array
   * @access private
   */
  function get_firstList($params=array()) {
    global $camyks;
    
    /* default params list */
    $dParams = array('status'=>-1, 'gallery'=>-1, 'galleries'=>-1, 'ids'=>-1, 'language'=>$camyks->current_language,
    	'limit'=>-1, 'count'=>-1, 'order'=>'sortPosition', 'orderway'=>'asc');
    	
    /* merge params */
    $params = array_merge($dParams, $params);
    
    /* check galleries */
    if ($params['galleries']==-1 or count($params['galleries']) == 0)
      return array();
        
    /* build where statement */
    $w = $this->build_whereStatement($params);
    
    /* build sql query */
    $sql = 'select id, gallery from '.$this->_libSQLTable;
    $sql .= ' where '.$w;
    $sql .= ' group by gallery';
    $sql .= ' order by sortPosition asc';
        
    /* execute sql query */
    $idList = array();
    if ($this->execute_DBQuery($sql, __LINE__ ))
      while ($data = $this->get_DBQueryDataLine())
        $idList[] = $data['id'];
        
    /* return list */
    return $this->get_list(array('ids'=>$idList, 'language'=>$params['language']));
  }
  
  /*                                                                                 
   * return product count with given params                                         
   * @params array $params                                                           
   * @return array                                                                   
   * @access private                                                                 
   */
  function count($params=array()) {
    global $camyks;
    $p = array('status'=>-1, 'gallery'=>-1, 'ids'=>-1);
    $params = array_merge($p, $params);
    $where = $this->build_whereStatement($params);
    
	return $this->get_objectCount($where);
  }
  
  /*                                                                                 
   * build where statement from params                                               
   * @param array $params                                                            
   * @return string                                                                  
   * @access private                                                                 
   */
  function build_whereStatement($params=array()) {  
    $w = array();
    
    /* check status */
    if ($params['status'] != -1)
      $w[] = 'status = '.$params['status'].'';
    
    /* check gallery / galleries */
    if ($params['galleries'] != -1) {
      if (is_array($params['galleries'])) {
        switch (count($params['galleries'])) {
          case 0: return 'false'; break;
          case 1: 
           foreach ($params['galleries'] as $id)
             $w[] = 'gallery = '.$id;
           break;
         default:
            $w[] = 'gallery in ('.implode(',', $params['galleries']).')';
        }
      } else
        return 'false';
    } elseif ($params['gallery'] != -1)
      $w[] = 'gallery = '.$params['gallery'];
     
    /* check picture ids */
    if ($params['ids'] != -1 and $params['ids'] != '') {
      if (is_string($params['ids']))
        $params['ids'] = explode(',', $params['ids']);
      
      if (is_array($params['ids'])) {
        if( count($params['ids']) == 0) {
          $w[] = 'false';
        } elseif (count($params['ids']) == 1) {
          $w[] = 'id = '.$params['ids'][0];  
        } else {
          $w[] = 'id in ('.implode(',', $params['ids']).')';
        }
      }
    }
    
	/* return result */
    return implode(' and ', $w);
  }
  
  /* sort position management methods */
  
  /*
   * get object new position
   * @return integer
   * @access private
   */
  function get_newPosition() {
    /* build sql */
    $sql = 'select sortPosition';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where gallery='.$this->_libItems['gallery']->value;
    $sql .= ' order by sortPosition desc limit 1';
    
    /* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__ ))
      if ($data = $this->get_DBQueryDataLine())
        return $data['sortPosition']+1;
    return 0;
  }
  
  /*
   * is not first
   * @return boolean result
   * @access private
   */
  function is_notFirst() {  
  	return $this->vars['sortPosition'] > 0;
  }

  /*
   * is not last
   * @return boolean result
   * @access private
   */
  function is_notLast() {
	if (!isset($this->_libParent->pictureList))
	  return false;
	return $this->vars['sortPosition'] < $this->_libParent->pictureList->objectCount-1;
  }
  
  /*
   * update page position to upper
   * @return boolean success
   * @access public
   */
  function update_moveUp() {
    return $this->update_movePosition(-1);
  }

  /*
   * update page position to lower
   * @return boolean success
   * @access public
   */
  function update_moveDown() {
    return $this->update_movePosition(1);
  }

  /*
   * update page position
   * @param integer $pos
   * @return boolean success
   * @access public
   */
  function update_movePosition($pos) {
    global $camyks;

    /* get all parent pages */
    $sql = 'select id, sortPosition';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where gallery='.$this->_libItems['gallery']->value;
    $sql .= ' order by sortPosition';
    if ( !$this->execute_DBQuery($sql, __LINE__ ))
      return false;

    $items = array();
    $position = -1;
    while ($data = $this->get_DBQueryDataLine()) {
      if ( $data['id'] == $this->id )
	    $position = count($items);
      $items[] = $data;
    }

    /* check new position value */
    if ( $position == -1 or ($position+$pos<0) or $position+$pos>=count($items))
      return false;

    /* update position */
    $temp = $items[$position];
    $items[$position] = $items[$position+$pos];
    $items[$position+$pos] = $temp;

    /* update all pages which the position is not correct */
    foreach ($items as $index => $item ) {
      if ( $index != $item['sortPosition'] ) {
	      $sql = 'update '.$this->_libSQLTable;
	      $sql .= ' set sortPosition='.$index;
	      $sql .= ' where id='.$item['id'];
	      if ( !$this->execute_DBQuery($sql, __LINE__ ))
	        return false;
      }
    }
    return true;
  }
}
?>