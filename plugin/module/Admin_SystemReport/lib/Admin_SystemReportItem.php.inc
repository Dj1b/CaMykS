<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Engine
 * Create Date		: May 2007
 * Last Modif Date	: May 2007
 *
 * Admin_SystemReportItem object for Admin_SystemReport module
 */
class Admin_SystemReportItem extends ModuleLibrary {
  /* constructor */
  function Admin_SystemReportItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('type', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('_date', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('url', 'db', 'text', 'varchar', 255, $_SERVER['REQUEST_URI']);
    $this->add_newItem('objecttype', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('objectname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('errordesc1', 'db', 'text', 'text', '', '');
    $this->add_newItem('errordesc2', 'db', 'text', 'text', '', '');
    $this->add_newItem('errorfile', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('errorline', 'db', 'int', 'int unsigned', '', 0);
    $this->add_newitem('answeruser', 'db', 'text', 'varchar', 16, '');
    $this->add_newitem('answercomment', 'db', 'text', 'text', '', '');
    $this->add_newitem('answerdate', 'db', 'date', 'bigint unsigned', '', 0);
  }

  /* overwrite ModuleLibrary object */
  
  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    $search = array();
    if ( isset( $params['status']) and $params['status']!='' and $params['status'] > -1 )
      $search[] = 'status='.(int)$params['status'];
    if ( isset( $params['type']) and $params['type']!='all')
      $search[] = 'type="'.$this->escape_string($params['type']).'"';
    return implode(' and ', $search);
  }
  
  /*
   * check if object is checked 
   * @return boolean result
   * @access private
   */
  function is_marked() {
    return ($this->vars['status'] == 0);
  }

  /* specific methods */
  
  /*
   * return status list
   * @return array
   * @access private
   */
  function get_statusList() {
    return array(0 => $this->get_translation('reportstatus_pending'),
        1 => $this->get_translation('reportstatus_settled'),
    );
  }
  
  /*
   * return multi object status list
   * @param boolean $more
   * @return array
   * @access private
   */
  function get_multiStatusList($more=false) {
    $list = array();
    if ( $more )
      $list['-1'] = $this->get_translation('reports_all');
      
    return $list + array(0 => $this->get_translation('reportstatus_pending'),
        1 => $this->get_translation('reportstatus_settled'),
    );
  }

  /*
   * build item with given values
   * @param string $type
   * @param object $object
   * @param string $errordesc1
   * @param string $errordesc2
   * @param string $errorfile
   * @param string $errorline
   * @return void
   * @access private
   */
  function update_values ( $type, &$object, $errordesc1='', $errordesc2='', $errorfile='', $errorline=0 ) {
    $this->get();
    $this->_libItems['type']->value = $type;
    $this->_libItems['objecttype']->value = isset($object->object_type)?$object->object_type:'';
    $this->_libItems['objectname']->value = get_class($object);
    $this->_libItems['errordesc1']->value = $errordesc1;
    $this->_libItems['errordesc2']->value = $errordesc2;
    $this->_libItems['errorfile']->value = $errorfile;
    $this->_libItems['errorline']->value = $errorline;
  }

  /*
   * get unique type list
   * @param boolean $more
   * @return array
   * @access private
   */
  function get_typelist($more=false) {
    global $camyks;
    
    $list = array();
    if ( $more )
      $list['all'] = $this->get_translation('reports_all');
    
    /* build sql query */
    $sql = 'select type';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' group by type';
    /* execute sql query */
    $camyks->db_conn->execute_query($sql);
    /* get data from database */
    while ( $data = $camyks->db_conn->get_queryDataLine()) {
      $list[$data['type']] = $data['type'];
    }
    return $list;
  }

  /*
   * mark report object as read
   * @return boolean success
   * @access private
   */
  function update_withAnswer( ) {
    global $camyks;

    /* get comment */
    $this->_libItems['answercomment']->get_fromheader();

    /* build sql query */
    $sql = 'update '.$this->_libSQLTable;
    $sql .= ' set status=1';
    $sql .= ', answerdate='.time();
    $sql .= ', answeruser="'.$camyks->adminUser->login.'"';
    $sql .= ', answercomment="'.$this->_libItems['answercomment']->value.'"';
    $sql .= ' where id='.$this->id;
    /* return result of sql execution */
    return $camyks->db_conn->execute_query($sql);
  }

  /*
   * mark given reports as read
   * @return boolean success
   * @access private
   */
  function update_reports( $list=array() ) {
    global $camyks;
    /* do not execute sql for an empty list */
    if ( count($list) == 0 )
      return true;
    /* build sql query */
    $sql = 'update '.$this->_libSQLTable;
    $sql .= ' set status=1';
    $sql .= ', answerdate='.time();
    $sql .= ', answeruser="'.$camyks->adminUser->login.'"';
    $sql .= ' where id in('.implode(',', $list).')';
    $sql .= ' and status=0';
    
    /* return result of sql execution */
    return $camyks->db_conn->execute_query($sql);
  }

  /*
   * delete given reports
   * @return boolean success
   * @access private
   */
  function delete_reports( $list=array() ) {
    global $camyks;
    /* do not execute sql for an empty list */
    if ( count($list) == 0 )
      return true;
    /* build sql query */
    $sql = 'delete from '.$this->_libSQLTable;
    $sql .= ' where id in('.implode(',', $list).')';
    /* return result of sql execution */
    return $camyks->db_conn->execute_query($sql);
  }
}
?>