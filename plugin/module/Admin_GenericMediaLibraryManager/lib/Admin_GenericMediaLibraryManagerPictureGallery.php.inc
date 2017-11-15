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
 * Admin_GenericMediaLibraryManagerPictureGallery object for Admin_GenericMediaLibraryManager Module
 */

class Admin_GenericMediaLibraryManagerPictureGallery extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericMediaLibraryManagerPictureGallery ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );

    /* main items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
    $this->add_newItem('summary', 'db', 'text', 'text', '', '', true);
    $this->add_newItem('content', 'db', 'text', 'text', '', '', true);
    
    /* to do items */
    $this->add_newItem('defaultPicture', 'db', 'int', 'bigint unsigned', '', 0);
   
    /* temp items */
    $this->add_newItem('pictures', 'temp', 'int', '', '', 0);
    $this->add_newItem('defaultThumb', 'temp', 'text', '', '', '');
    
    /* init picture list */
    $this->pictures = array();

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    if ( isset( $params['status'] ) and $params['status'] > -1 )
      return 'status='.$params['status'];
    return '';
  }
  
  /*
   * delete
   * @return boolean success
   * @access private
   */
  function delete() {
    /* delete objects */
    if (!parent::delete())
      return false;
    
    /* delete pictures files */
    
    /* delete pictures db entries */
    
    /* return result */
    return true;
  }

  /* specific tool methods */
  
  /*
   * return single object status list
   * @return array
   * @access private
   */
  function get_statusList() {
    return array(0 => $this->get_translation('picturegallerystatus_inactive'),
                 1 => $this->get_translation('picturegallerystatus_public'),
                 2 => $this->get_translation('picturegallerystatus_private'),
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
      $list['-1'] = $this->get_translation('picturegalleries_all');
    $list['0'] = $this->get_translation('picturegalleriesstatus_inactive');
    $list['1'] = $this->get_translation('picturegalleriesstatus_public');
    $list['2'] = $this->get_translation('picturegalleriesstatus_private');
    return $list;
  }
  
  /*
   * return single object status list
   * @return array
   * @access private
   */
  function get_statusIconList() {
    return array(0 => '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="'.$this->get_translation('picturegallerystatus_inactive').'" />',
                 1 => '<img src="'.$this->_libParent->theme->get_pictURL('valid', 12, 'std').'" alt="'.$this->get_translation('picturegallerystatus_public').'" />',
                 2 => '<img src="'.$this->_libParent->theme->get_pictURL('minus', 12, 'std').'" alt="'.$this->get_translation('picturegallerystatus_private').'" />',
    );
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
    $dParams = array('status'=>-1, 'ids'=>-1, 'language'=>$camyks->current_language,
        'load_pictures'=>0, 'load_defaultThumb'=>0,
    	'limit'=>-1, 'count'=>-1, 'order'=>'cdate', 'orderway'=>'desc');
    	
    /* merge params */
    $params = array_merge($dParams, $params);
    
    /* build where statement */
    $w = $this->build_whereStatement($params);
    
    /* load list */
    $list = $this->get_objectList($params['language'], $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    
    /* check for load pictures option */
    if ( $params['load_pictures'] > 0 ) {
      $galleryIds = array();
      foreach ($list as $gallery)
        $galleryIds[] = $gallery->id;
      $pictures = $this->get_pictures(array('galleries'=>$galleryIds, 'status'=>$params['status']==-1?-1:1));
      foreach ($pictures as $picture) {
        if (!isset($list[$picture->vars['gallery']]))
          continue;
        $list[$picture->vars['gallery']]->pictures[$picture->id] = &$picture;
      }
    }
    
    /* check for load default thumb option */
    if ( $params['load_defaultThumb'] > 0 ) {
      if ($params['load_pictures'] > 0) {
        /* search thumbs in loaded pictures */
        foreach ($list as &$gallery) {
          if (isset($gallery->pictures[$gallery->vars['defaultPicture']]))
            $gallery->vars['defaultThumb'] = $gallery->pictures[$gallery->vars['defaultPicture']]->vars['thumb'];
          else {
            foreach ($gallery->pictures as $p) {
              $gallery->vars['defaultThumb'] = $p->vars['thumb'];
              break;
            }
          }
        }
        
      } else {
        /* search thumbs in default value */
        $pictureIds = array();
        foreach ($list as $gallery) {
          if ($gallery->vars['defaultPicture'] > 0)
            $pictureIds[] = $gallery->vars['defaultPicture'];
        }
        $pictures = $this->get_pictures(array('ids'=>$pictureIds));
        foreach ($pictures as $picture) {
          if (!isset($list[$picture->vars['gallery']]))
            continue;
          $list[$picture->vars['gallery']]->vars['defaultThumb'] = $picture->vars['thumb'];
        }
        
        /* search thumb for "no default value" */
        $galleryIds = array();
        foreach ($list as $gallery) {
          if ($gallery->vars['defaultThumb'] == '')
            $galleryIds[] = $gallery->id;
        }
        $pictures = $this->get_galleriesFirstPictures(array('galleries'=>$galleryIds, 'status'=>$params['status']==-1?-1:1));
        foreach ($pictures as $picture) {
          if (!isset($list[$picture->vars['gallery']]))
            continue;
          $list[$picture->vars['gallery']]->vars['defaultThumb'] = $picture->vars['thumb'];
        }
      }
    }
        
    /* return list */
    return $list;
  }
  
  /*                                                                                 
   * return product count with given params                                         
   * @params array $params                                                           
   * @return array                                                                   
   * @access private                                                                 
   */
  function count($params=array()) {
    global $camyks;
    $p = array('status'=>-1, 'ids'=>-1);
    $params = array_merge($p, $params);
    $where = $this->build_whereStatement($params);
    
	return $this->get_objectCount($where);
  }
  
  /*
   * return title list
   * @param array $params
   * @return array
   * @access private
   */
  function get_titleList($params=array()) {
    global $camyks;
    
    /* default params list */
    $dParams = array('status'=>-1, 'addNone'=>0, 'addAll'=>0, 'language'=>$camyks->current_language);
    	
    /* merge params */
    $params = array_merge($dParams, $params);
  
  	/* build where statement */
    $w = $this->build_whereStatement($params);
    
    $l = array();
    if ($params['addNone'] == 1)
      $l['-1'] = $this->get_translation('picturegallery_none');
    if ($params['addAll'] == 1)
      $l['0'] = $this->get_translation('picturegalleries_all');
      
    /* return title list */
    return $l + $this->get_nameList('title', $w, $params['language']);
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
      $w[] = 'status = '.$params['status'];

    /* return result */
    return implode(' and ', $w);
  }
  
  /*
   * load pictures
   * @param array $params
   * @return boolean success
   * @access public
   */
  function load_pictures($params=array()) {
    $dParams = array('gallery'=>$this->id);
    $params = array_merge($dParams, $params);
    $this->pictures = $this->_libParent->get_pictureList($params);
    return true;
  }
  
  /*
   * return pictures
   * @param array $params
   * @return array
   * @access public
   */
  function get_pictures($params=array()) {
    return $this->_libParent->get_pictureList($params);
  }
  
  /*
   * return first pictures for given galleries
   * @param array $params
   * @return arrray
   * @access public
   */
  function get_galleriesFirstPictures($params=array()) {
    return $this->_libParent->get_firstPicturesList($params);
  }
  
  /*
   * check for default picture
   * @param int $pictureId
   * @return void
   * @access public
   */
  function check_forDefaultPicture($pictureId=0) {
    if ($pictureId == 0) return;
    if ($this->vars['defaultPicture'] > 0)
      return;
    $this->_libItems['defaultPicture']->value = $pictureId;
    $this->update_databaseSpecificItems(array('defaultPicture'));
  } 
}
?>