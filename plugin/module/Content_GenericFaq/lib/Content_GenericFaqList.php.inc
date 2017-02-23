<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Content_GenericFaqList object for Content_GenericFaq module
 */

class Content_GenericFaqList extends ModuleLibrary {
  /* constructor */
  function Content_GenericFaqList ( $id = 0, &$module ) {
    parent::ModuleLibrary( $id, $module);
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('count_list', 'db', 'int', 'tinyint unsigned', '', 10 );
    $this->add_newItem('layout_list', 'db', 'text', 'varchar', 16, '');
    
    /* generic init */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary methods */  

  /*
   * check object data value
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    global $camyks;

    /* check name */
    $this->_libItems['name']->check_value('symbolic', 'faq');
    
    /* check item displayed value */
    if ( !( $this->_libItems['count_list']->value > 0 ) ){
      $this->_libItems['count_list']->initialise();
    }
    return true;
  }
}
?>