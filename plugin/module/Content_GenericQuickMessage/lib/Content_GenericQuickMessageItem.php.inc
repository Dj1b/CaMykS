<?php
/*
 * Camyks Engine
 * Company                 : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Module Lib
 * Create Date             : Nov 2007
 * Last Modif Date         : Nov 2007
 * History :
 * * 07-11-08 : Initial file
 *
 * Content_GenericQuickMessageItem object for Content_GenericQuickMessage module
 *
 * Available status values :
 * - [0]rejected : message is not displayed
 * - [1]waiting : message is waiting for approval
 * - [2]accepted : message is displayed
 */

class Content_GenericQuickMessageItem extends ModuleLibrary {
  
  /* constructor */
  function Content_GenericQuickMessageItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('listid', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 1);
    $this->add_newItem('ndate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('author', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('email', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('title', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('message', 'db', 'text', 'text', '', '');
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite methods */
  /*
   * check object data
   */
  function check_data () {
    global $camyks;
    /* check listid */
    if ( !($this->_libItems['listid']->value > 0 ) )
      return false;

    /* check if author is empty */
    $this->_libItems['author']->value = trim($this->_libItems['author']->value);
    if ( $this->_libItems['author']->value == '' ) {
      return false;
    }
    /* check if title is empty */
    $this->_libItems['title']->value = trim($this->_libItems['title']->value);
    if ( $this->_libItems['title']->value == '' ) {
      return false;
    }
    /* check if content is empty */
    $this->_libItems['message']->value = trim($this->_libItems['message']->value);
    if ( $this->_libItems['message']->value == '' ) {
      return false;
    }
    
    if ( $this->id == 0 ) {
      /* set date */
      $this->_libItems['ndate']->initialise();
      
      /* set automatic status */
      $list = $this->_libParent->get_listObject( $this->_libItems['listid']->value );
      if ( $list->vars['validation'] == 0 ) {
	$this->_libItems['status']->value = 2;
      } else if ( $list->vars['validation'] == 1 ) {
	$this->_libItems['status']->value = 1;
	if ( $list->vars['notification'] == 1 and $this->count_waitingMessages() == 0 ) {
	  $camyks->log_information( $this, 'New "Quick Messages" waiting for approval into "'.$list->vars['name'].'" message list.');
	}
      }
    }
    return true;
  }

  /* specific methods */

  /*
   * count "waiting" messages
   */ 
  function count_waitingMessages() {
    return $this->get_objectCount('listid='.$this->_libItems['listid']. 'and status=1');
  }

  /*
   * return available status list
   */
  function get_statusValueList() {
    return array(0=>$this->get_translation('itemstatusvalue0'),
		 1=>$this->get_translation('itemstatusvalue1'),
		 2=>$this->get_translation('itemstatusvalue2'));
  }
}
?>