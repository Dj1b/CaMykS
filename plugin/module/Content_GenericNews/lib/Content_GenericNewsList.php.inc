<?php
/*
 * CaMyks Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Mar 2007
 * Last Modif Date	: Mar 2007
 *
 * Content_GenericNewsList object for Content_GenericNews module
*/

class Content_GenericNewsList extends ModuleLibrary {
  /* Constructor */
  function Content_GenericNewsList ( $id = 0, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('count_list', 'db', 'int', 'tinyint unsigned', '', 10);
    $this->add_newItem('layout_list', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout_item', 'db', 'text', 'varchar', 32, '');
    /* generic init */
    $this->init_library();
  }
 
  /* overwrite ModuleLibrary methods */

  /*
   * check object data values
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    global $camyks;

    /* check name */
    $this->_libItems['name']->check_value('symbolic', 'newslist');

    /* check item displayed value */
    if ( !( $this->_libItems['count_list']->value > 0 ) ){
      $this->_libItems['count_list']->initialise();
    }
    return true;
  }
}
?>