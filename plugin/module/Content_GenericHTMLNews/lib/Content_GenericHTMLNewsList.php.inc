<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author               : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Lib
 * Create Date          : Dec 2007
 * Last Modif Date      : Dec 2007
 *
 * Content_GenericHTMLNewsList object for Content_GenericHTMLNews module
*/

class Content_GenericHTMLNewsList extends ModuleLibrary {
  /* 
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericHTMLNewsList ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('count_list', 'db', 'int', 'tinyint unsigned', '', 5);
    $this->add_newItem('layout_list', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('layout_item', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('enablerss', 'db', 'int', 'tinyint unsigned', '', 1 );
    /* generic ModuleLibrary initialisation */
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