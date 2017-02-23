<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author               : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Lib
 * Create Date          : Sep 2008
 * Last Modif Date      : Sep 2008
 *
 * Content_GoogleSearchResultsViewerItem object for Content_GoogleSearchResultsViewer module
*/

class Content_GoogleSearchResultsViewerItem extends ModuleLibrary {
  /* Constructor */
  function Content_GoogleSearchResultsViewerItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');

    /* layout content */
    $this->add_newItem('layout', 'db', 'text', 'varchar', 16, '');

    /* google search results description */
    $this->add_newItem('sr_searchdomain', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('sr_width', 'db', 'int', 'int unsigned', '', 0 );

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
    $this->_libItems['name']->check_value('symbolic_name', 'google_search');
    /* return result */
    return true;
  }
}
?>