<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Jul 2017
 * Last Modif Date  : Jul 2017
 *
 * Admin_SystemNotificationsWebsite object for Admin_SystemNotifications Module
 */

class Admin_SystemNotificationsWebsite extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_SystemNotificationsWebsite ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    
    /* admin items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 1);
    $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('baseURL', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('pageURL', 'db', 'text', 'varchar', 32, 'request.php');
    $this->add_newItem('login', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('password', 'db', 'text', 'varchar', 32, '');
    
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
  
    if ($this->id == 0) {
      $this->_libItems['cdate']->value = time();
    } else {
      $old = $this->get_newObject($this->id);
      $old->get();
      $old->get_fromItems();
      $this->_libItems['cdate']->value = $old->vars['cdate'];    
    }
    
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
      0 => $this->get_translation('websitestatus_disabled'),
	  1 => $this->get_translation('websitestatus_enabled'),
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
      $list['-1'] = $this->get_translation('websites_all');
    $list['0'] = $this->get_translation('websitesstatus_disabled');
    $list['1'] = $this->get_translation('websitesstatus_enabled');
    return $list;
  }
  
  /* specific tool methods */
    
  /*
   * return config value
   * @param mixed $param
   * @return string
   * @access private
   */
  function get_configValue($param=array()) {
  	return $this->_libParent->get_configValue($param);
  }
  
  /* multi object handling methods */
  
  /*
   * return object list
   * @param array $params
   * @return array
   * @access private
   */
  function get_list($params=array()) {
    global $camyks;
    
    /* default params list */
    $dParams = array('status'=>-1, 'language'=>$camyks->current_language,
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
    $p = array('status'=>-1,);
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
}
?>