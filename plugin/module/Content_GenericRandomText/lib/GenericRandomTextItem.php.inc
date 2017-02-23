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
 * GenericRandomTextItem object for Content_GenericRandomText module
*/
class GenericRandomTextItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function GenericRandomTextItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('listid', 'db', 'int', 'bigint', '', 0);
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('content', 'db', 'text', 'text', '', '');
    $this->add_newItem('weight', 'db', 'int', 'tinyint unsigned', '', 1);
    /* generic init */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary methods */  

  /*
   * check object values
   * @return boolean success
   * @access private
   */
  function check_data( ) {
    global $camyks;
    
    /* check name */
    if ( $this->_libItems['name']->value == '' ) {
      $this->_libItems['name']->value = 'randomtextitem'.$this->id;
    }
    
    /* check weight */
    if ( !($this->_libItems['weight']->value >= 0 ) )
      $this->_libItems['weight']->value = 1;
    
    return true;
  }

  /*
   * delete object from database
   * @return mixed
   * @access private
   */
  function delete( ) {
    global $camyks;
    /* build sql query */
    $sql = 'delete from '.$this->_libSQLTable.' where id='.$this->id.' and listid='.$this->_libItems['listid']->value;

    /* return result of execute sql query */
    if ( mysql_query($sql))
      return mysql_affected_rows();
    return $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ );
  }
}
?>