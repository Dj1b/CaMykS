<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version 	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date	: May 2007
 * Last Modif Date  : May 2007
 *
 * Admin_StatisticConfig object for Admin_Statistics Module
 */

class Admin_StatisticConfig extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param &Module $module
   */
  function Admin_StatisticConfig ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('user', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('object', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('mode', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('value', 'db', 'text', 'varchar', 255, ''); 

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */
  
  /*
   * save object
   * @return void
   * @access private
   */
  function save() {
    /* get object id */ 
    $this->get_configId();
    /* generic save */ 
    parent::save();
  }
  
  /* specific tool methods */

  /*
   * get config id
   * @return void
   * @access private
   */
  function get_configId () {
    global $camyks;
    /* build sql query */
    $sql = 'select id ';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where user="'.$this->_libItems['user']->value.'"';
    $sql .= ' and object="'.$this->_libItems['object']->value.'"';
    $sql .= ' and mode="'.$this->_libItems['mode']->value.'"';
    /* execute sql query */
    if ($this->execute_DBQuery($sql, __FILE__, __LINE__ )) {
      if ($data = $this->get_DBQueryDataLine()) {
	    $this->id = $data['id'];
	    return;
      }
    }
    $this->id = 0;
  }
  
  /*
   * get configs
   * @param string $name
   * @param string $mode
   * @return array
   * @access private
   */
  function get_configs ( $name, $mode='' ) {
    global $camyks;
    $configs = array();
    /* build sql query */
    $sql = 'select *';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where user="'.$camyks->adminUser->login.'"';
    $sql .= ' and ( object="colors"';
    $sql .= ' or ( object="'.$name.'"';
    $sql .= ' and mode="'.$mode.'" ))';
    /* execute sql query */
    if ($this->execute_DBQuery($sql, __FILE__, __LINE__ )) {
      while ($data = $this->get_DBQueryDataLine()) {
	    $item = $this->get_newObject();
	    $item->id = $data['id'];
	    $item->get_fromArray( $data, $this->_libItemTypes['db'] );
	    $item->get_fromItems();
	    $configs[$data['object']]=$item;
      }
    }
    return $configs;
  }
}
?>