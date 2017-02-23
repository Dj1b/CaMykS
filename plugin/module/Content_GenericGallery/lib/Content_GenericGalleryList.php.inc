<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Jul 2007
 * Last Modif Date	: Jul 2007
 *
 * Content_GenericGalleryList object for Content_GenericGallery module
 */

class Content_GenericGalleryList extends ModuleLibrary {
  /* variables */
  var $items;
  
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericGalleryList ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    
    /* Smart Gallery configuration */
    $this->add_newItem('theme', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('thumbCount', 'db', 'int', 'tinyint unsigned', '', 6);
    $this->add_newItem('thumbWidth', 'db', 'int', 'tinyint unsigned', '', 80);
    $this->add_newItem('thumbHeight', 'db', 'int', 'tinyint unsigned', '', 60);
    $this->add_newItem('imageWidth', 'db', 'int', 'int unsigned', '', 0);
    $this->add_newItem('imageHeight', 'db', 'int', 'int unsigned', '', 0);
    $this->add_newItem('imageTitle', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('imageDesc', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('slidingMethod', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('slidingAccel', 'db', 'int', 'tinyint unsigned', '', 1);
    $this->add_newItem('slidingSpeed', 'db', 'int', 'tinyint unsigned', '', 30);
    $this->add_newItem('slidingInterval', 'db', 'int', 'tinyint unsigned', '', 25);
    
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data () {
    /* check symbolic name value */
    $this->_libItems['name']->check_value('symbolic_name', 'gallery');
    return true;
  }

  /* specific tool methods */

  /*
   * get items
   * @param string $lg
   * @return void
   * @access private
   */
  function get_itemList( $lg=false ) {
    $this->items = $this->_libParent->imageitem->get_objectList($lg, 'listid='.$this->id );
  }
}
?>