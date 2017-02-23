<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: May 2008
 * Last Modif Date	: May 2008
 *
 * Content_GenericHTMLContentItem library for Content_GenericHTMLContent module 
*/

class Content_GenericHTMLContentItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $d
   * @param Module $module
   */
  function Content_GenericHTMLContentItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('content', 'text', 'content','', '', '',  true);
  }
  
  /* overwrite ModuleLibrary  methods */

  /*
   * check content data
   * @return boolean result
   * @access private
   */
  function check_data() {
    /* check symbolic name value */
    $this->_libItems['name']->check_value('symbolic_name', 'content');
    return true;
  }

  /* specific methods */

  /*
   * write content
   * @return void
   * @access private
   */
  function write_content() {
    if ( file_exists( $this->vars['content'] ) )
      include ( $this->vars['content'] );
  }
}
?>