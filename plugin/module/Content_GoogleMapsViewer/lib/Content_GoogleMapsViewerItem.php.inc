<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author               : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Lib
 * Create Date          : Jul 2008
 * Last Modif Date      : Jul 2008
 *
 * Content_GoogleMapsViewerItem object for Content_GoogleMapsViewer module
*/

class Content_GoogleMapsViewerItem extends ModuleLibrary {
  /* Constructor */
  function Content_GoogleMapsViewerItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    /* localized content */
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true );
    $this->add_newItem('description', 'db', 'text', 'text', '', '', true );
    /* layout content */
    $this->add_newItem('layout', 'db', 'text', 'varchar', 16, '');
    /* google maps description */
    $this->add_newItem('map_baseurl', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('map_width', 'db', 'int', 'int unsigned', '', 0 );
    $this->add_newItem('map_height', 'db', 'int', 'int unsigned', '', 0 );
    $this->add_newItem('map_zoom', 'db', 'int', 'tinyint unsigned', '', 0 );
    $this->add_newItem('map_code', 'db', 'text', 'varchar', 64, '' );
    /* google maps link description */
    $this->add_newItem('link_enabled', 'db', 'int', 'tinyint unsigned', '', 0 );
    $this->add_newItem('link_class', 'db', 'int', 'tinyint unsigned', '', 1 );
    $this->add_newItem('link_color', 'db', 'text', 'varchar', 6, '000000' );
    $this->add_newItem('link_size', 'db', 'int', 'tinyint unsigned', '', 11 );
    $this->add_newItem('link_bold', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('link_italic', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('link_underline', 'db', 'int', 'tinyint unsigned', '', 0);

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
    /* return result */
    return true;
  }
}
?>