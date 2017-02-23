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
 * Content_GenericGalleryItem object for Content_GenericGallery module
 */

class Content_GenericGalleryItem extends ModuleLibrary {  
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericGalleryItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('listid', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('position', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('title', 'db', 'etext', 'varchar', 128, '', true);
    $this->add_newItem('description', 'db', 'etext', 'text', '', '', true);
    $this->add_newItem('image', 'file', 'image', '', '', '');
    $this->add_newItem('thumb', 'file', 'thumb', '', '', '');
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
    $this->_libItems['name']->check_value('symbolic_name', 'image');
    /* check position */
    if ( $this->id == 0 ) {
      $this->_libItems['position']->value = $this->get_objectCount('listid='.$this->_libItems['listid']->value);
    }
    return true;
  }
}
?>