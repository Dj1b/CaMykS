<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version 	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : May 2007
 * Last Modif Date  : Sep 2014
 *
 * Admin_Statistic object for Admin_Statistics Module
 */

class Admin_Statistic extends ModuleLibrary {

  /*
   * constructor
   * @param integer $id
   * @param &Module $module
   */
  function Admin_Statistic ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('type', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('plugin', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('register_date', 'db', 'date', 'bigint', '', time()); 

    /* generic initialisation */
    $this->init_library();
  }

  /* specific tool methods */

  /*
   * update statistic data
   * @param string $main
   * @param string $data1
   * @param string $data2
   * @return void
   * @access private
   */
  function update_statistic ( $main='', $data1='', $data2='' ) {
    /* get data object */
    $data = &$this->_libParent->statdata;
    $data->id = 0;
    $data->get();
    $data->_libItems['statid']->value=$this->id;
    $data->_libItems['main']->value=$main;
    $data->_libItems['data1']->value=$data1;
    $data->_libItems['data2']->value=$data2;
    switch ( $this->_libItems['type']->value ) {
    case 'single':
      $data->update_singleStatistic();
      break;
    case 'mixed':
    case 'detail':
    case 'dated':
      $data->update_mixedStatistic();
      break;
    case 'total':
      $data->update_totalStatistic();
      break;      
    }
  }
  
  /*
   * update title value
   * @return void
   * @access private
   */
  function get_statisticTitle ( ) {
    global $camyks;
    $this->vars['title'] = $camyks->get_translation('mod_'.$this->vars['plugin'].'_stat_'.$this->vars['name']);
    $this->vars['plugintitle'] = $camyks->get_translation('mod_'.$this->vars['plugin'].'_title');
    $this->vars['item'] = $camyks->get_translation('mod_'.$this->vars['plugin'].'_stat_'.$this->vars['name'].'_main');
  }
  
  /*
   * return object id from plugin and name
   * @param string $plugin
   * @param string $name
   * @access private
   */
  function get_idFromPluginAndName($plugin, $name) {

    /* get statistic id */
    $sql = 'select id from '.$this->_libSQLTable;
    $sql .= ' where plugin="'.$plugin.'" and name="'.$name.'"';
    
    /* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__)){
      /* get result of sql query */
      if ( $data = $this->get_DBQueryDataLine()) {
        return $data['id'];
      }
    }
    return false;
  }
}
?>