<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 *
 * Content_GenericSiteMapItem object for Content_GenericSiteMap module
 */
class Content_GenericSiteMapItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericSiteMapItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('columns', 'db', 'int', 'tinyint unsigned', '', 2);
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
    $this->_libItems['name']->check_value('symbolic_name', 'sitemap');

    /* check columns value */
    if ( !$this->_libItems['columns']->value>0 )
      $this->_libItems['columns']->value = 1;
    return true;
  }
}
?>