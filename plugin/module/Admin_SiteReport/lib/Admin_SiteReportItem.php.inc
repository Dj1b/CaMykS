<?php
/*
 * CaMykS Engine
 * Developed by		   : camyks.net
 * Author		   : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	   : 1.0a
 * Object Version 	   : 1.0
 * Object Type             : Plugin / Module Lib 
 * Creation Date	   : Apr 2007
 * Last Modif Date	   : Jul 2008
 *
 * Admin_SiteReportItem object for Admin_SiteReport Module
 */

class Admin_SiteReportItem extends ModuleLibrary {
  /* variables */
  var $updatedItems;

  /*
   * constructor
   * @param integer $id
   * @param Module &module
   */
  function Admin_SiteReportItem ( $id, &$module ) {
    global $camyks;
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('language', 'db', 'text', 'varchar', 3, $camyks->site_conf['site_default_language']);
    $this->add_newItem('type', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('creation_date', 'db', 'date', 'bigint', '', time()); 
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, ''); 
    $this->add_newItem('content', 'db', 'text', 'text', '', '');
    $this->add_newItem('link', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('answer_target', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('answer_date', 'db', 'date', 'bigint', '', 0);
    $this->add_newItem('answer_admin', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('answer_comment', 'db', 'text', 'text', '', '');
    $this->add_newItem('attached_file', 'file', 'attachedfile', '', '', '');
    /* generic initialiaation */
    $this->init_library();
    /* specific data */
    $this->updatedItems = array ('answer_date', 'answer_admin', 'answer_comment' );
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data() {
    /* delete answer info if answer date is null */
    if ( $this->_libItems['answer_date']->value == 0 ) {
      $this->_libItems['answer_admin']->value = '';
      $this->_libItems['answer_comment']->value = '';
    } else if ( $this->_libItems['answer_date']->value == 1) {
      $this->_libItems['answer_date']->value = time();
    }
    return true;
  }
  
  /* specific methods */

  /*
   * update some items values from object to database
   * @return boolean success
   * @access private
   */
  function update_databaseItems() {
    return $this->update_databaseSpecificItems($this->updatedItems);
  }

  /*
   * load attached file
   * @return void
   * @access private
   */
  function load_attachedFile() {
    if(!isset($this->vars['attached_file']) or $this->vars['attached_file']=='' ) {
      $this->attachedFile = false;
      return;
    }
    $this->attachedFile = new FSFile( $this->vars['attached_file']);
    if ( $this->attachedFile->exists === false )
      $this->attachedFile = false;
  }

  /*
   * delete attached file
   * @return boolean result
   * @access private
   */
  function delete_attachedFile(){
    if ( $this->id > 0 )
      return $this->_libItems['attached_file']->delete($this->id);
    return true;
  }
}
?>