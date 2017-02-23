<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Lib
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 *
 * Content_GenericPetitionViewerItem object for Content_GenericPetitionViewer module
*/

class Content_GenericPetitionViewerItem extends ModuleLibrary {
  /* Constructor */
  function Content_GenericPetitionViewerItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('petition', 'db', 'int', 'bigint unsigned', '', 1 );
    $this->add_newItem('signcount', 'db', 'int', 'tinyint unsigned', '', 10 );

    /* generic init */
    $this->init_library();
  }
 
  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    global $camyks;
    /* check name */
    $this->_libItems['name']->check_value('symbolic', 'petition');

    /* return result */
    return true;
  }

  /* specific methods */

}
?>