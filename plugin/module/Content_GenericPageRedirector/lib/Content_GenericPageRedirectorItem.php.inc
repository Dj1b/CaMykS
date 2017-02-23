<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type		: Plugin / Module Engine
 * Create Date		: Sep 2009
 * Last Modif Date	: Apr 2010
 *
 * Content_GenericPageRedirectorItem object for Content_GenericPageRedirector module
 */

class Content_GenericPageRedirectorItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericPageRedirectorItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('url', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('delay', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('method', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('layout', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('message', 'text', 'messages', '', '', '', true);

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
    $this->_libItems['name']->check_value('symbolic_name', 'redirector');
    return true;
  }

  /* specific methods */

  /*
   * return method list
   * @return array
   * @access private
   */
  function get_methodList() {
    return array(0=>$this->get_translation('method_jsmeta'),
		 3=>$this->get_translation('method_header'));
  }

  /*
   * return layout list
   * @return array
   * @access public
   */
  function get_layoutList() {
    return array('framed1'=>$this->get_translation('layout_framed1'),
		 'framed2'=>$this->get_translation('layout_framed2'),
		 'noframe'=>$this->get_translation('layout_noframe'));
  }
}
?>