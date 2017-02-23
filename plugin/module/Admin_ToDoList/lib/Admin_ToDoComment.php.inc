<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version 	: 1.0
 * Object Type          : Plugin / Module Lib 
 * Creation Date	: Apr 2007
 * Last Modif Date	: May 2007
 *
 * Admin_ToDoComment object for Admin_ToDoList Module
 */

class Admin_ToDoComment extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_ToDoComment ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('todo', 'db', 'int', 'bigint', '', 0);
    $this->add_newItem('from_user', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('creation_date', 'db', 'date', 'bigint', '', time()); 
    $this->add_newItem('content', 'db', 'etext', 'text', '', '');
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean success
   * @access private
   */
  function check_data ( ) {
    if ( trim($this->_libItems['content']->value) == '' ) {
      return false;
    }
    return true;
  }
}
?>