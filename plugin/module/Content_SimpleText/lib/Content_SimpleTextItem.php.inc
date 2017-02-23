<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Jul 2007
 * Last Modif Date	: Jul 2007
 *
 * Content_SimpleTextItem object for Content_SimpleText module
 */
class Content_SimpleTextItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_SimpleTextItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('title', 'db', 'etext', 'varchar', 128, '', true);
    $this->add_newItem('content', 'db', 'etext', 'text', '', '', true);
    $this->add_newItem('htmlencode', 'db', 'int', 'tinyint unsigned', '', 0);
    /* generic initialisation */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary methods */

  /*
   * check object values
   * @return boolean result
   * @access private
   */
  function check_data () {
    /* check symbolic name value */
    $this->_libItems['name']->check_value('symbolic_name', 'text');
    return true;
  }
  
  /* specific update methods */
  
  /*
   * update library to version 1.01
   * @return boolean success
   * @access private
   */
  function update_toVersion1_01() {
    global $camyks;
    /* build sql query */
    $sql = 'alter ignore table '.$this->_libSQLTable.' add column htmlencode tinyint unsigned default 0;';
    /* execute sql query */
    return (mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__));
  }
}
?>