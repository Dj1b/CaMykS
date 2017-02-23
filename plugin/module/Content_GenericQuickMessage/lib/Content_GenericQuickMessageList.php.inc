<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Nov 2007
 * Last Modif Date	: Nov 2007
 *
 * Content_GenericQuickMessageList object for Content_GenericQuickMessage module
 *
 * Available status values :
 * - [0]closed : deny new message
 * - [1]registered : allow new message from GUAE registered users only
 * - [2]unregistered : allow new direct message
 *
 * Available validation values :
 * - [0]none : messages are directly online
 * - [1]admin : messages are validated by an admin
 *
 */

class Content_GenericQuickMessageList extends ModuleLibrary {
  
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericQuickMessageList ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('validation', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('notification', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('displayed', 'db', 'int', 'tinyint unsigned', '', 8);
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
    $this->_libItems['name']->check_value('symbolic_name', 'messagelist');
    return true;
  }

  /* specific tool methods */

  /*
   * return status values list
   * @return array
   * @access public 
   */ 
  function get_statusValueList() {
    return array(0=>$this->get_translation('liststatusvalue0'),
		 1=>$this->get_translation('liststatusvalue1'),
		 2=>$this->get_translation('liststatusvalue2'));
  }

  /*
   * return validation values list
   * @return array
   * @access public 
   */ 
  function get_validationValueList() {
    return array(0=>$this->get_translation('listvalidationvalue0'),
		 1=>$this->get_translation('listvalidationvalue1'));
  }

  /*
   * get validated list messages
   * @return void
   * @access public
   */
  function get_validatedMessages() {
    $this->vars['messages'] = $this->_libParent->qmitem->get_objectList(false, 'status=2 and listid='.$this->id, 8, -1, 'ndate', 'desc' );
  }
}
?>