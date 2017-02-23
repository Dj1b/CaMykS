<?php
/*
 * CaMykS Engine
 * Developed by		   : camyks.net
 * Author		   : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	   : 1.0a
 * Object Version 	   : 1.0
 * Object Type             : Plugin / Module Library
 * Creation Date	   : May 2007
 * Last Modif Date	   : May 2007
 *
 * Admin_StatisticDatedOptions object for Admin_Statistics Module
 */

class Admin_StatisticDatedOptions extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param &Module $module
   */
  function Admin_StatisticDatedOptions ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('coloralternate0', 'temp', 'text', 'varchar', 6, '5b8dcd'); 
    $this->add_newItem('coloralternate1', 'temp', 'text', 'varchar', 6, 'ffd802'); 
    $this->add_newItem('mainbydaycount', 'temp', 'int', 'tinyint', '', 12);
    $this->add_newItem('mainbymonthcount', 'temp', 'int', 'tinyint', '', 12);
    $this->add_newItem('mainbyyearcount', 'temp', 'int', 'tinyint', '', 6);

    /* generic initialisation */
    $this->init_library();
  }

  /* specific ModuleLibrary methods */

  /*
   * get values from given properties
   * @param string $properties
   * @return void
   * @access private
   */
  function get_valuesFromProperties ( $properties ) {
    $values = data_decode_properties ( $properties  );
    foreach ( $values as $name=>$value ) {
      if ( isset ( $this->_libItems[$name] ) ) {
	$this->_libItems[$name]->value = $value;
      }
    }
  }
  
  /*
   * get colors from given properties
   * @param string properties
   * @return void
   * @access private
   */
  function get_colorsFromProperties ( $properties ) {
    $colors = data_decode_properties ( $properties  );
    foreach ( $colors as $name=>$value ) {
      if ( isset ( $this->_libItems[$name] ) ) {
	$this->_libItems[$name]->value = $value;
      }
    }
  }
  
  /*
   * return values as properties
   * @return string
   * @access private
   */
  function get_valuesAsProperties ( ) {
    return '';
  }
  
  /*
   * return colors as properties
   * @return string
   * @access private
   */
  function get_colorsAsProperties () {
    return data_encode_properties(array('coloralternate0'=>$this->_libItems['coloralternate0']->value,
					'coloralternate1'=>$this->_libItems['coloralternate1']->value));
  }
  
  /*
   * build & return object config
   * @param integer $objectid
   * @return array
   * @access private
   */
  function build_config ( $objectid ) {
    /* build default config */
    $config = array ('maintotalwhere'=>'statid='.$objectid,
		     'mainbydaywhere'=>'statid='.$objectid,
		     'mainbydaydate'=>0,
		     'mainbymonthwhere'=>'statid='.$objectid,
		     'mainbymonthdate'=>0,
		     'mainbyyearwhere'=>'statid='.$objectid,
		     'mainbyyeardate'=>0);
		

    /* main tab statistics : by day */
    $d = mktime(0, 0, 0, date('m'), date('d')-$this->vars['mainbydaycount'], date('Y'));
    $config['mainbydaywhere'] .= ' and statdate >='. $d;

    /* main tab statistics : by month */
    $d = mktime(0, 0, 0, date('m')-$this->vars['mainbymonthcount'], 1, date('Y'));
    $config['mainbymonthwhere'] .= ' and statdate >='. $d;

    /* main tab statistics : by day */
    $d = mktime(0, 0, 0, 1, 1, date('Y')-$this->vars['mainbyyearcount']);
    $config['mainbyyearwhere'] .= ' and statdate >='. $d;
    return $config;
  }
}
?>