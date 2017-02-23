<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Dictionnary
 * Create Date		: Jul 2007
 * Last Modif Date	: Jul 2007
 *
 * Content_SimpleImageItem object for Content_SimpleImage module
 */

class Content_SimpleImageItem extends ModuleLibrary {  
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_SimpleImageItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('title', 'db', 'etext', 'varchar', 128, '', true);
    $this->add_newItem('description', 'db', 'etext', 'text', '', '', true);
    $this->add_newItem('image', 'file', 'img', '', '', '', true);
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object values
   * @return boolean result
   * @access private
   */
  function check_data () {
    /* check symbolic name value */
    $this->_libItems['name']->check_value('symbolic_name', 'image');
    return true;
  }
}
?>