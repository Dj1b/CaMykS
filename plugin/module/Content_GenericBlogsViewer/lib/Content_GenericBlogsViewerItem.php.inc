<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author               : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Lib
 * Create Date          : Apr 2008
 * Last Modif Date      : Jan 2010
 *
 * Content_GenericBlogsViewerItem object for Content_GenericBlogsViewer module
*/

class Content_GenericBlogsViewerItem extends ModuleLibrary {
  /* Constructor */
  function Content_GenericBlogsViewerItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '' );
    $this->add_newItem('list_count', 'db', 'int', 'tinyint unsigned', '', 5);
    $this->add_newItem('list_layout', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('list_panel', 'db', 'int', 'tinyint unsigned', '', 1 );
    $this->add_newItem('item_layout', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('item_panel', 'db', 'int', 'tinyint unsigned', '', 1 );
    $this->add_newItem('panel_insert', 'db', 'etext', 'text', '', '' );
    $this->add_newItem('comment_message', 'db', 'etext', 'text', '', '' );
    $this->add_newItem('enablerss', 'db', 'int', 'tinyint unsigned', '', 1 );
    $this->add_newItem('authors', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('snsp_status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('snsp_items', 'db', 'text', 'text', '', '');
    $this->add_newItem('gpc_status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('gpc_source', 'db', 'int', 'tinyint unsigned', '', 0);

    /* temp content */
    $this->add_newItem('authors_', 'temp', 'array', '', '', array());

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
    $this->_libItems['name']->check_value('symbolic', 'blog');

    /* check authors value */
    $authorsCount = isset($_REQUEST['authorsCount'])?$_REQUEST['authorsCount']:0;

    $authors = array();
    for ( $i=0; $i< $authorsCount; $i++ ) {
      if ( isset( $_REQUEST['author'.$i]) )
	$authors[] = $_REQUEST['author'.$i];
    }
    $this->_libItems['authors']->value = implode(',', $authors);

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

    /* decompile authors value */
    if ( $this->vars['authors'] == '' )
      $this->vars['authors_'] = array();
    else
      $this->vars['authors_'] = explode(',', $this->vars['authors']);
  }

  /*
   * update library to version 1.01
   * @return boolean success
   * @access private
   */
  function update_toVersion1_01() {
    global $camyks;
    /* build sql query */
    $sql = 'alter ignore table '.$this->_libSQLTable;
    $sql .= ' add column snsp_status tinyint unsigned default 0,';
    $sql .= ' add column snsp_items text default "",';
    $sql .= ' add column gpc_status tinyint unsigned default 0,';
    $sql .= ' add column gpc_source tinyint unsigned default 0;';

    /* execute sql query */
    return (mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__));
  }
}
?>