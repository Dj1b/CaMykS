<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Lib
 * Creation Date    : Jun 2010
 * Last Modif Date  : Jun 2010
 *
 * Content_GenericGlossaryViewerItem object for Content_GenericGlossaryViewer module
*/

class Content_GenericGlossaryViewerItem extends ModuleLibrary {
  /* Constructor */
  function Content_GenericGlossaryViewerItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('pagemode', 'db', 'int', 'tinyint unsigned', '', 1 );
    $this->add_newItem('wordcount', 'db', 'int', 'tinyint unsigned', '', 20 );
    $this->add_newItem('categories', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('content', 'db', 'text', 'text', '', '', true);
    $this->add_newItem('gpc_source', 'db', 'int', 'tinyint unsigned', '', 0);

    /* temp items */
    $this->add_newItem('category_cnt', 'temp', 'int', '', '', 0);
    $this->add_newItem('categories_', 'temp', 'array', '', '', array());

    /* generic init */
    $this->init_library();
  }
 
  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    global $camyks;
    /* check name */
    $this->_libItems['name']->check_value('symbolic', 'glossary');

    /* check categories */
    $categories = array();
    for ( $i=0; $i< $this->_libItems['category_cnt']->value; $i++ ) {
      if ( isset( $_REQUEST['category'.$i]) )
	$categories[] = $_REQUEST['category'.$i];
    }
    $this->_libItems['categories']->value = implode(',', $categories);

    /* return result */
    return true;
  }

  /*
   * get library data from item to a human readable array
   * @return void
   * @access private
   */
  function get_fromItems() {
    /* ModuleLibrary generic method */
    parent::get_fromItems();

    /* decompile categories value */
    if ( $this->vars['categories'] == '' )
      $this->vars['categories_'] = array();
    else
      $this->vars['categories_'] = explode(',', $this->vars['categories']);
  }

  /* specific methods */

  /* 
   * return page mode list
   * @param boolean $allowPageMode
   * @return array
   * @access private
   */
  function get_pageModeList($allowPageMode=false) {
    $list = array();
    if ($allowPageMode == true)
      $list[0] = $this->get_translation('configpagemode_bypage');
    $list +=  array(1 => $this->get_translation('configpagemode_byletter'),
		    2 => $this->get_translation('configpagemode_bygroup1'),
		    3 => $this->get_translation('configpagemode_bygroup2'),
		    4 => $this->get_translation('configpagemode_bygroup3'));
    return $list;
  }

  /*
   * return GPC source list
   * @return array
   * @access private
   */
  function get_gpcSourceList() {
    global $camyks;
    return array(0=>$camyks->get_translation('theme'),
		 1=>$this->get_translation('gpc_name'));
  }
}
?>