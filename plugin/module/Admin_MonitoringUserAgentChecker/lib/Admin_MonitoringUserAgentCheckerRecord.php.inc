<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version  	: 1.0a
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date	: Dec 2014
 * Last Modif Date	: Dec 2014
 * History :
 * * 12-19-14 : Initial files
 *
 * Admin_MonitoringUserAgentCheckerRecord object for Admin_MonitoringUserAgentChecker Module
 */

class Admin_MonitoringUserAgentCheckerRecord extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_MonitoringUserAgentCheckerRecord ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('user_agent', 'db', 'text', 'text', '', '', '');
    $this->add_newItem('platform_type', 'db', 'text', 'varchar', 16, '', '');
    $this->add_newItem('fvisit', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('lvisit', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('nvisit', 'db', 'int', 'int unsigned', '', 1);

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary method */

  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    $search = array();

    if ( isset( $params['user_agent']) and $params['user_agent'] != '')
    	$search[] = '(user_agent like "%'.$params['user_agent'].'%")';
    
    if ( isset( $params['platform_type']) and $params['platform_type'] != '-1'){
    	if($params['platform_type'] == 'other')
    		$search[] = '(platform_type like "%other%") OR (platform_type like "%undefined%")';
    	else
 		   	$search[] = '(platform_type like "%'.$params['platform_type'].'%")';
    }
      
    
    if ( isset( $params['status']) and $params['status'] != '-1')
      $search[] = '(status ='.$params['status'].')';
    
    return implode(' and ', $search);
  }

  /* specific tool methods */
    
  /*
   * return single record platform list
   * @return array
   * @access public
   */
  function get_platformTypesList($all) {
  	if($all)
  		return array('-1' => $this->get_translation('platform_type_all'), 
  				'handheld' => $this->get_translation('platform_type_handheld'),
  				'tablet' => $this->get_translation('platform_type_tablet'),
  				'computer' => $this->get_translation('platform_type_computer'),
				'bot' => $this->get_translation('platform_type_bot'),
				'tool' => $this->get_translation('platform_type_tool'),
				'hack' => $this->get_translation('platform_type_hack'),
				'fake' => $this->get_translation('platform_type_fake'),
  				'other' => $this->get_translation('platform_type_other'));
  	else return array(
  	            'handheld' => $this->get_translation('platform_type_handheld'),
  				'tablet' => $this->get_translation('platform_type_tablet'),
  				'computer' => $this->get_translation('platform_type_computer'),
				'bot' => $this->get_translation('platform_type_bot'),
				'tool' => $this->get_translation('platform_type_tool'),
				'hack' => $this->get_translation('platform_type_hack'),
				'fake' => $this->get_translation('platform_type_fake'),
  				'other' => $this->get_translation('platform_type_other'),
  				'undefined' => $this->get_translation('platform_type_other'));
  }
  
  /*
   * return single record status list
   * @return array
   * @access private
   */
  function get_statusList() {
  	return array('-1' => $this->get_translation('record_all'), 
  			'0' => $this->get_translation('recordstatus_notverified'), 
  			'1' => $this->get_translation('recordstatus_verified'));
  }
  
  /*
   * return signe object format list
   * @return array
   * @access private
   */
  function get_platformFormatList() {
    return array(
        'handheld' => $this->get_translation('platform_format_handheld'),
  		'tablet' => $this->get_translation('platform_format_tablet'),
  		'desktop' => $this->get_translation('platform_format_desktop'),
    );
  }
  
  /*
   * get from user agent value
   * @param string $ua
   * @return boolean result
   * @access private
   */
  function get_fromUserAgent($ua) {
    /* build sql query */
    $sql = 'select *';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where user_agent = "'.addSlashes($ua).'"';
    
    /* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__ ) ) {
      /* get result of sql query */
      if ( $data = $this->get_DBQueryDataLine()) {
	    $this->id = $data['id'];
		$this->get_fromArray($data, $this->_libItemTypes['db']);
        return true;
      }
    }
    return false;
  }
  
  /*
   * build where statement from params
   * @param array $params
   * @return string
   * @access private
   */
  function build_whereStatement($params=array()) {
    $w = array();
    
    /* check user agent */
    if ($params['status'] > -1)
    	$w[] = 'status = '.(int)$params['status'].'';

    /* check user agent */
    if ($params['user_agent'] != '')
    	$w[] = '(user_agent like "%'.$params['user_agent'].'%")';
    
    /* check user agent */
    if ($params['platform_type'] != '')
    	$w[] = '(platform_type = "'.$params['platform_type'].'")';
        
    return implode(' and ', $w);
  }
  
  /*
   * return record count with given params
   * @params array $params
   * @return array
   * @access private
   */
  function count($params=array()) {
  	global $camyks;
  	$p = array('user_agent'=>'', 'platform_type'=>'', 'status'=>-1);
  	$params = array_merge($p, $params);
  	
  	return $this->get_objectCount($this->build_whereStatement($params));
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
    $dParams = array('user_agent'=>'', 'platform_type'=>'','status'=>-1, 'limit'=>-1, 'count'=>-1, 'order'=>'lvisit', 'orderway'=>'desc');
    /* merge params */
    $params = array_merge($dParams, $params);
    /* build where statement */
    $w = $this->build_whereStatement($params);
    /* return list */
    return $this->get_objectList(false, $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
  }

  /*
   * check if stored user agent is correct
   * @return string
   * @access private
   */
  function is_userAgentCorrect() {
  	$uaInfos = client_getUAInfos($this->vars['user_agent']);
  	$new_platform_type = $uaInfos['platform_type'];
  	 
  	if ($new_platform_type != '' && $this->vars['platform_type'] != $new_platform_type)
  	  return '(*)';
  	else
  	  return '';
  }
}
?>