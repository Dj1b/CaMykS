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
 * Content_GooglePoIMapViewerItem for Content_GooglePoIMapViewer module
*/

class Content_GooglePoIMapViewerItem extends ModuleLibrary {
  /*
   * Constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GooglePoIMapViewerItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );

    /* main content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('categories', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('category_select', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('country_select', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('content', 'db', 'text', 'text', '', '', true);
    $this->add_newItem('default_zoom', 'db', 'int', 'tinyint unsigned', '', 1);
    
    /* geo content */
    $this->add_newItem('geo_status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('geo_icon', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('geo_zoom', 'db', 'int', 'tinyint unsigned', '', 1);

    /* temp content */
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
    $this->_libItems['name']->check_value('symbolic', 'map');

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
}
?>