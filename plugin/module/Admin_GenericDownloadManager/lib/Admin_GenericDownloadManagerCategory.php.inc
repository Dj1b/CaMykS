<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Creation Date	: May 2008
 * Last Modif Date	: Apr 2009
 *
 * Admin_GenericDownloadManagerCategory object for Admin_GenericDownloadManager Module
 */

class Admin_GenericDownloadManagerCategory extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericDownloadManagerCategory ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );

    /* main items */
    $this->add_newItem('active', 'db', 'int', 'tinyint unsigned', '', 1);
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
   
    /* temp items */
    $this->add_newItem('docs', 'temp', 'int', '', '', 0);

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    if ( isset( $params['active'] ) and $params['active'] > -1 )
      return 'active='.$params['active'];
    return '';
  }

  /* specific methods */
  
  /*
   * is category deletable
   * @return boolean result
   * @access public
   */
  function is_deletable() {
    return ( isset($this->vars['docs']) and $this->vars['docs'] == 0 );
  }
}
?>