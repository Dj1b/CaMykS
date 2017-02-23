<?php
/*
 * CaMykS Engine
 * Developed by		   : camyks.net
 * Author		   : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	   : 1.0a
 * Object Version 	   : 1.0
 * Object Type             : Plugin / Module Lib 
 * Creation Date	   : Apr 2007
 * Last Modif Date	   : Apr 2007
 *
 * Admin_MessagePanelItem object for Admin_MessagePanel Module
 */

class Admin_MessagePanelItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_MessagePanelItem ( $id, &$module ) {
    global $camyks;
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('creation_date', 'db', 'date', 'bigint', '', time());
    $this->add_newItem('user', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('content', 'db', 'text', 'text', '', '');
    /* generic initialisation */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access public
   */
  function check_data() {
    if ( trim( $this->_libItems['title']->value ) == '' 
	 or trim ( $this->_libItems['content']->value ) == '' ) {
      return false;
    }
    return true;
  }
  
  /* specific tool methods */
  
  /* 
   * return database last object date value
   * no param
   * return date
   */
  function get_lastObjectDate ( ) {
    global $camyks;
    /* build sql query */
    $sql = 'select creation_date';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' order by creation_date desc';
    $sql .= ' limit 1';
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* return data from database */
      if ( $data = mysql_fetch_assoc( $req ) )
	return $data['creation_date'];
    return 0;   
  }
}
?>