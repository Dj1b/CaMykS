<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Dec 2012
 * Last Modif Date  : Sep 2014
 *
 * Admin_GenericEmailingManagerEmail object for Admin_GenericEmailingManager Module
 */

class Admin_GenericEmailingManagerEmail extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericEmailingManagerEmail ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    
    /* content */
    $this->add_newItem('emailing', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('source', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('contact', 'db', 'int', 'bigint unsigned', '', 0);
    
    $this->add_newItem('sent_status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('sent_date', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('opened_status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('opened_date', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('click_count', 'db', 'int', 'smallint unsigned', '', 0);
    $this->add_newItem('firstclick_date', 'db', 'int', 'bigint unsigned', '', 0);    
    $this->add_newItem('unsubscribe_status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('invalid_status', 'db', 'int', 'tinyint unsigned', '', 0);
    
    $this->add_newItem('title', 'temp', 'string', '', '', '');
    
    /* generic initialisation */
    $this->init_library();
  }
  

  /* overwrite ModuleLibrary methods */
  
  /*                                                                                                                
   * build SQL condition                                                                                            
   * @param array $params                                                                                           
   * @return string                                                                                                 
   * @access public                                                                                                 
   */
  function build_SQLCondition( $params ) {
    $search = array();
    $search[] = 'emailing='.$this->_libParent->emailingItem->id;
    if (isset($params['search']) and $params['search'] != '') {
      $contactIds = $this->_libParent->get_contactIdList(array('search' => $params['search']));
      if (count($contactIds) == 0)
        $search[] = 'false';
      elseif (count($contactIds) == 1)
        $search[] = 'contact = '.$contactIds[0];
      else
        $search[] = 'contact in ('.implode(', ', $contactIds).')';
    }
    
    /* return fixed params */
    return implode(' and ', $search);
  }
  
  /* specific methods */
  
  /*
   * return emailing statistics summary
   * @param integer $emailing
   * @return array
   * @access private
   */
  function get_statisticsSummary($emailing) {
  
    /* build sql query */
    $sql = 'select count(id) as total_built, sum(sent_status) as total_sent, sum(opened_status) as total_opened, sum(click_count) as total_clicks, sum(unsubscribe_status) as total_unsubscribed, sum(invalid_status) as total_invalid';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where emailing='.$emailing;
    
    if ($this->execute_DBQuery($sql, __LINE__))
      /* get result of sql query */
      if ( $data = $this->get_DBQueryDataLine())
        return $data;
    return array();
  }
  
  /*
   * return status icon 
   * @return string
   * @access private
   */
  function get_statusIcon() {
    if ($this->vars['invalid_status'] == 1)
        return '<img src="'.$this->_libParent->theme->get_pictURL('minus', 12, 'std').'" alt="" border="0" />';
    if ($this->vars['unsubscribe_status'] == 1)
        return '<img src="'.$this->_libParent->theme->get_pictURL('cross', 12, 'std').'" alt="" border="0" />';
    if ($this->vars['opened_status'] == 0)
        return '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="" border="0" />';
    if ($this->vars['sent_status'] == 0)
        return '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="" border="0" />';
    return '<img src="'.$this->_libParent->theme->get_pictURL('valid', 12, 'std').'" alt="" border="0" />';
  }
  
  /*
   * return sent date value
   * @return string
   * @access private
   */
  function get_sentDateValue() {
    global $camyks;
    if ($this->vars['sent_status'] == 0)
        return $camyks->get_translation('no');
    return date_displayNumericDateHour($this->vars['sent_date']);
  }
  
  /*
   * return opened date value
   * @return string
   * @access private
   */
  function get_openedDateValue() {
    global $camyks;
    if ($this->vars['opened_status'] == 0)
        return $camyks->get_translation('no');
    return date_displayNumericDateHour($this->vars['opened_date']);
  }
  
  /*
   * return first click date value
   * @return string
   * @access private
   */
  function get_firstClickDateValue() {
    if ($this->vars['click_count'] == 0)
        return '--';
    return date_displayNumericDateHour($this->vars['firstclick_date']);
  }
  
  /*
   * update email as unsubscribed
   * @param integer $emailingId
   * @return boolean result
   * @access private
   */
  function update_asUnsubscribed($emailingId) {
    if (!$this->get())
      return false;
    $this->get_fromItems();
    
    /* check emailing value */
    if ($this->vars['emailing'] != $emailingId)
      return false;
    
    /* update email value */
    $this->_libItems['unsubscribe_status']->value = 1;
    return $this->update_databaseSpecificItems(array('unsubscribe_status'));
  }
  
  /*
   * mark email as invalid
   * @param integer $emailingId
   * @return boolean result
   * @access private
   */
  function mark_asInvalid() {
    /* update invalid status */
    $this->_libItems['invalid_status']->value = 1;
    
    /* update open status (may be opened by server) */
    $this->_libItems['opened_status']->value = 0;
    $this->_libItems['opened_date']->value = 0;
    
    return $this->update_databaseSpecificItems(array('invalid_status', 'opened_status', 'opened_date'));
  }
}
?>