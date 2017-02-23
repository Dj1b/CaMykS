<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Jul 2007
 * Last Modif Date	: Jul 2007
 *
 * Content_GenericMenuItem object for Content_GenericMenu module
 */

class Content_GenericMenuItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericMenuItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('root', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('levels', 'db', 'int', 'tinyint unsigned', '', 0);
    /* generic initialisation */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data () {
    /* check symbolic name value */
    $this->_libItems['name']->check_value('symbolic_name', 'menu');
    return true;
  }
}
?>