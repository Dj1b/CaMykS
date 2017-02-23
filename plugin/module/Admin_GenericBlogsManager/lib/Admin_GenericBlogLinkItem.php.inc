<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author               : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Lib
 * Create Date          : Apr 2008
 * Last Modif Date      : Apr 2008
 *
 * Admin_GenericBlogLinkItem object for Admin_GenericBlogsManager module
*/
class Admin_GenericBlogLinkItem extends ModuleLibrary {  
  
  /*
   * Constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericBlogLinkItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('title', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('link', 'db', 'text', 'varchar', 255, 'http://');
    $this->add_newItem('author', 'db', 'text', 'varchar', 32, '' );
    $this->add_newitem('ndate', 'db', 'date', 'bigint unsigned', '', time());
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object data before saving
   * @return boolean result
   * @access private
   */  
  function check_data() {
    global $camyks;
    return true;
  }

  /* 
   * initialise object
   * @return void
   * @access private
   */
  function initialise() {
    global $camyks;
    /* generic initialisation */
    parent::initialise();
    /* specific initialisation */
    $this->_libItems['author']->value = $camyks->adminUser->login;
  }

  /* specific methods */
  
  /*
   * get link list from given author list
   * @param array $authors
   * @return array
   * @access private
   */
  function get_linkListByAuthor( $authors ) {
    if ( count($authors) == 0 )
      return $this->get_objectList();
    else if ( count($authors) == 1 )
      return $this->get_objectList(false, 'author="'.$authors[0].'"');
    else
      return $this->get_objectList(false, 'author in ("'.implode('", "', $authors).'")');
  }
}
?>