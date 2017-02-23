<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Library
 * Create Date		: May 2007
 * Last Modif Date	: May 2007
 *
 * Admin_UserShortcut object for Admin_MyShortcuts module
 */
class Admin_UserShortcut extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_UserShortcut ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content items */
    $this->add_newItem('type', 'db', 'int', 'tinyint', '', 0 );
    $this->add_newItem('user', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('_date', 'db', 'date', 'bigint', '', time());
    $this->add_newItem('url', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean success
   * @access private
   */
  function check_data( ) {
    $this->_libItems['name']->value = trim( $this->_libItems['name']->value );
    if ( $this->_libItems['name']->value == '' ) 
      return false;
    if ( $this->id == 0 )
      $this->_libItems['_date']->value = time();
    return true;
  }
}
?>