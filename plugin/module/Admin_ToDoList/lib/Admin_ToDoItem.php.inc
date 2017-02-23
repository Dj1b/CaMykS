<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version 	: 1.0
 * Object Type          : Plugin / Module Lib 
 * Creation Date	: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Admin_ToDoItem object for Admin_ToDoList Module
*/

class Admin_ToDoItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_ToDoItem ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('from_user', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('to_user', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('creation_date', 'db', 'date', 'bigint', '', time()); 
    $this->add_newItem('limit_date', 'db', 'date', 'bigint', '', 0); 
    $this->add_newItem('title', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('content', 'db', 'text', 'text', '', '');
    $this->add_newItem('sticked', 'db', 'text', 'text', '', '');
    $this->add_newItem('closed', 'db', 'int', 'tinyint', '', 0);
    /* temporary content */
    $this->add_newItem('users', 'temp', 'array', '', '', array());
    $this->add_newItem('comments', 'temp', 'array', '', '', array());
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * get object
   * @return boolean success
   * @access private
   */
  function get ($language=true) {
    global $camyks;
    /* update from user default value */
    $this->_libItems['from_user']->default = $camyks->adminUser->login;
    /* generic get */
    parent::get();
    /* specific get */
    $this->get_specificValues();
    $this->get_fromItems();
    return true;
  }
  
  /*
   * delete object
   * @return boolean success
   * @access private
   */
  function delete_fromDatabase() {
    $c = new Admin_ToDoComment( 0, $this->_libParent );
    if ( $c->delete_selectedItemsFromDatabase( array('todo' => $this->id ) ) ) {
      return parent::delete_fromDatabase();
    }
    return false;
  }
  
  /* specific tool methods */

  /*
   * get specific values for this object
   * @return void
   * @access private
   */
  function get_specificValues ( ){
    /* get all user list */
    $this->_libItems['users']->value = AdminUser::static_getList();
    if ( $this->id > 0 ) {
      /* get comment list */
      $c = new Admin_ToDoComment( 0, $this->_libParent );
      $this->_libItems['comments']->value = $c->get_objectlist ( false, 'todo='.$this->id, -1, -1, 'creation_date', 'desc' );
    }
  }
}
?>