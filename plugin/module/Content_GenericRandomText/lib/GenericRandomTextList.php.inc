<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Mar 2007
 * Last Modif Date	: Mar 2007
 *
 * GenericRandomTextList object for Content_GenericRandomText module
*/
class GenericRandomTextList extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function GenericRandomTextList ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('sessionkeep', 'db', 'int', 'tinyint', '', 0);
    /* generic init */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary methods */

  /*
   * check object values
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    /* check name */
    if ( $this->_libItems['name']->value == '' ) {
      $this->_libItems['name']->value = 'genericrandomtextlist'.$this->id;
    }
    return true;
  }
  
  /* specific tool methods */
  
  /*
   * load item list
   * @return void
   * @access private
   */
  function get_itemlist( ) {
    $this->vars['items'] = $this->_libParent->gitem->get_objectList(false, 'listid='.$this->id);
  }
}
?>