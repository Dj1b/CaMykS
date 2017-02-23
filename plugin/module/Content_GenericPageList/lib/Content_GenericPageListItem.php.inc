<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Nov 2007
 * Last Modif Date	: Nov 2007
 *
 * Content_GenericPageListItem object for Content_GenericPageList module
 */

class Content_GenericPageListItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericPageListItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('root', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('title', 'db', 'text', 'varchar', 64, '', true );
    $this->add_newItem('listorder', 'db', 'text', 'varchar', 16, '');
    /* unused, added just in case... */
    $this->add_newItem('maxdisplayed', 'db', 'int', 'int unsigned', '', 0);
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
    $this->_libItems['name']->check_value('symbolic_name', 'pagelist');
    return true;
  }

  /* specific methods */

  /*
   * return layout list
   * @return array
   * @access public
   */
  function get_layoutList() {
    return array('bordered'=>$this->get_translation('layout_bordered'),
		 'borderedalt'=>$this->get_translation('layout_borderedalt'),
		 'noborder'=>$this->get_translation('layout_noborder'));
  }

  /*
   * return list order list
   * @return array
   * @access public
   */
  function get_listOrderList() {
    return array('normal'=>$this->get_translation('order_normal'),
		 'reverse'=>$this->get_translation('order_reverse'));
  }
}
?>