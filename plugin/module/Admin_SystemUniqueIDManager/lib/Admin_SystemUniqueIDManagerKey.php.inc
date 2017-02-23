<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Jan 2015
 * Last Modif Date  : Jan 2015
 *
 * Admin_SystemUniqueIDManagerKey object for Admin_SystemUniqueIDManager Module
 */

class Admin_SystemUniqueIDManagerKey extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_SystemUniqueIDManagerKey ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    
    /* admin items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('uniqueID', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('plugin', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('object', 'db', 'text', 'varchar', 16, '');
    
    /* generic initialisation */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary method */
  
  /*
   * check object data
   * @return boolean success
   * @access private
   */
  function check_data() {
    /* check object status from data */
    if ( $this->_libItems['plugin']->value != '' and $this->_libItems['object']->value != '')
      $this->_libItems['status']->value = 1;
    
    /* add creating date */
    if ($this->id == 0)
      $this->_libItems['cdate']->value = time();
    
    /* check for generating a new unique id*/
    if ($this->_libItems['uniqueID']->value == '')
      return ($this->generate_uniqueIdValue());
    return true;
  }
  
  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    $search = array();
    if ( isset( $params['status']) and $params['status']!='' and $params['status'] > -1 )
      $search[] = 'status='.$params['status'];
    return implode(' and ', $search);
  }
  
  /* specific properties definition method */
  
  /*
   * return status list
   * @return array
   * @access private
   */
  function get_statusList() {
    return array(
      0 => $this->get_translation('keystatus_free'),
	  1 => $this->get_translation('keystatus_used'),
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
    if ($more)
      $list['-1'] = $this->get_translation('keys_all');
    $list['0'] = $this->get_translation('keysstatus_free');
    $list['1'] = $this->get_translation('keysstatus_useded');
    return $list;
  }
  
  /*
   * return generating method list
   * @return array
   * @access public
   */
  function get_generatingMethodList() {
    return array( 
      0 => $this->get_translation('keygeneratingmethod_md5'),
      1 => $this->get_translation('keygeneratingmethod_crc32'),
      2 => $this->get_translation('keygeneratingmethod_sha'),
      3 => $this->get_translation('keygeneratingmethod_uniqid'),
    );
  }
  
  /* specific tool methods */
  
  /*
   * load free item from database
   * @return boolean success
   * @access private
   */
  function load_freeItem() {
    $l = $this->get_list(array('status'=>0, 'limit'=>1));
    if ( count($l) == 0)
      return false;
      
    foreach ($l as $i) {
      $this->id = $i->id;
      $this->get_fromArray($i->vars);
      $this->get_fromItems();
    }
     
    return true;
  }
  
  /*
   * check if object is deletable
   * @return boolean result
   * @access public
   */
  function is_deletable() {
    /* check plugin and object values */
    if ($this->vars['plugin'] == '' or $this->vars['object'] == '')
      return true;
    
    /* check plugin and object objects */
    
    /* key is still in use, do not delete */
    return false;
  }
  
  /*
   * return object list
   * @param array $params
   * @return array
   * @access private
   */
  function get_list($params=array()) {
    global $camyks;
    
    /* default params list */
    $dParams = array('status'=>-1, 'price'=>-1, 'language'=>$camyks->current_language,
		    'limit'=>-1, 'count'=>-1, 'order'=>'sortPosition', 'orderway'=>'asc');
    /* merge params */
    $params = array_merge($dParams, $params);
    /* build where statement */
    $w = $this->build_whereStatement($params);
    /* return list */
    return $this->get_objectList($params['language'], $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
  }
  
  /*                                                                                 
   * return uniqueID count with given params                                         
   * @params array $params                                                           
   * @return array                                                                   
   * @access private                                                                 
   */
  function count($params=array()) {
    global $camyks;
    $p = array('status'=>-1, 'price'=>-1);
    $params = array_merge($p, $params);
    $where = $this->build_whereStatement($params);
    
    /* return result */
    return $this->get_objectCount($where);
  }
  
  /*                                                                                 
   * build where statement from params                                               
   * @param array $params                                                            
   * @return string                                                                  
   * @access private                                                                 
   */
  function build_whereStatement($params=array()) {
    $w = array();
    
    /* check status */
    if ($params['status'] != -1)
      $w[] = 'status = '.$params['status'];
    
	/* return result */
    return implode(' and ', $w);
  }
  
  /*
   * return config value
   * @param mixed $param
   * @return string
   * @access private
   */
  function get_configValue($param=array()) {
  	return $this->_libParent->get_configValue($param);
  }
  
  /*
   * generate a new unique key
   * @return mixed
   * @access private
   */
  function generate_uniqueIdValue() {
    $c = 0;
    /* check if max attempts limit is exceeded */
    while($c++ < $this->get_configValue('generating_maxAttempts')) {
      /* generate code from selected method */
      switch ($this->get_configValue('generating_method')) {
        case 0: $code = md5(session_id().microtime()); break;
        case 1 : $code = abs(crc32(session_id().microtime())); break;
        case 2 : $code = sha1(session_id().microtime()); break;
        case 3 : $code = uniqid(null, true); break;
      }
    
      /* truncate value to defined max length */
      $code = substr($code, 0, $this->get_configValue('generating_length'));
      
      /* check if exists in database */
      $sql = 'select uniqueID from '.$this->_libSQLTable;
      $sql .= ' where uniqueID = "'.$code.'"';
      if ($this->execute_DBQuery($sql, __LINE__, __FILE__)) {
      	if (!$this->get_DBQueryDataLine()) {    
      	  $this->_libItems['uniqueID']->value = $code;
      	  return true;
     	}
      }
      
      /* make a pause to change the microtime value */
      usleep(20);
    }
    
    /* attempt limit exceeded */
    $camyks->log_executionerror($this, $this->get_translation('keygenerator_attemptlimitexceeded'));
    
    /* attempts limit exceeded, return failure */
    return false;
  }
}
?>