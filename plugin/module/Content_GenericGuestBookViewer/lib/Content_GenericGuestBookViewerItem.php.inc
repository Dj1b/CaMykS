<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Lib
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 *
 * Content_GenericGuestBookViewerItem object for Content_GenericGuestBookViewer module
*/

class Content_GenericGuestBookViewerItem extends ModuleLibrary {
  /* Constructor */
  function Content_GenericGuestBookViewerItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('formlayout', 'db', 'int', 'tinyint unsigned', '', 0 );
    $this->add_newItem('msgcount', 'db', 'int', 'tinyint unsigned', '', 10 );
    $this->add_newItem('gpcstyle', 'db', 'int', 'tinyint unsigned', '', 0 );
    $this->add_newItem('description', 'db', 'text', 'text', '', '', true );

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
    $this->_libItems['name']->check_value('symbolic', 'guestbook');
    /* return result */
    return true;
  }

  /* specific methods */
  
  /*
   * return GPC source list
   * @return array
   * @access private
   */
  function get_gpcStyleList() {
    global $camyks;
    return array(0=>$camyks->get_translation('theme'),
		 1=>$this->get_translation('gpc_name'));
  }

  /*
   * return message form layout value list
   * @return array
   * @access private
   */
  function get_formLayoutList() {
    return array(0 => $this->get_translation('formlayout_newpage'),
		 1 => $this->get_translation('formlayout_popup'));
  }

 /*
   * return layout list
   * @return array
   * @access public
   */
  function get_layoutList() {
    return array('nobox'=>$this->get_translation('layout_nobox'));
  }


}
?>