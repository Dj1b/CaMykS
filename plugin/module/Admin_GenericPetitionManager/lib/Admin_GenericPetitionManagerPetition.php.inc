<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.petition@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 *
 * Admin_GenericPetitionManagerPetition object for Admin_GenericPetitionManager Module
 */

class Admin_GenericPetitionManagerPetition extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericPetitionManagerPetition ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
    $this->add_newItem('description', 'db', 'text', 'text', '', '', true);

    /* temp items */
    $this->add_newItem('signs', 'temp', 'integer', '', '', '');
    
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
    if ( isset( $params['status'] ) and $params['status'] > -1 )
      $search[] = 'status='.$params['status'];
    return implode(',', $search);
  }
  
  /* specific tool methods */
    
  /*
   * return petitions status list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_multiStatusList($full=false) {
    $list = array();
    if($full)
      $list['-1'] = $this->get_translation('petitionsstatus_all');
    $list['0'] = $this->get_translation('petitionsstatus_disabled');
    $list['1'] = $this->get_translation('petitionsstatus_opened');
    $list['2'] = $this->get_translation('petitionsstatus_closed');
    return $list;
  }
  
  /*
   * return single petition status list
   * @return array
   * @access public
   */
  function get_statusList() {
    return array(0 => $this->get_translation('petitionstatus_disabled'),
		 1 => $this->get_translation('petitionstatus_opened'),
		 2 => $this->get_translation('petitionstatus_closed'));
  }
  
  /*
   * return petition list with given params
   * @params array $params
   * @return array
   * @access private
   */
  function get_list($params=array()) {
    global $camyks;
    $p = array('status'=>-1, 'limit'=>-1, 'count'=>-1, 'order'=>'id', 'orderway'=>'');
    $params = array_merge($p, $params);
    $w = $this->build_whereStatement($params);
    return $this->get_objectList($camyks->current_language, $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
  } 

  /*
   * return petition title list with given params
   * @params array $params
   * @return array
   * @access private
   */
  function get_titleList($params=array()) {
    global $camyks;
    $p = array('status'=>-1);
    $params = array_merge($p, $params);
    $w = $this->build_whereStatement($params);
    return $this->get_nameList('title', $w);
  } 
  
  /*
   * return petition count with given params
   * @params array $params
   * @return array
   * @access private
   */
  function count($params=array()) {
    global $camyks;
    $p = array('status'=>-1);
    $params = array_merge($p, $params);
    return $this->get_objectCount($this->build_whereStatement($params));
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
    if ( is_string($params['status']) and $params['status'] != '')
      $w[] = 'status '.$params['status'];
    elseif($params['status'] != -1 )
      $w[] = 'status = '.$params['status'];
    
    return implode(' and ', $w);
  }

  /*
   * load signature count
   * @return void
   * @access private
   */
  function get_signCount() {
    $c = $this->_libParent->count_signsByPetitions(array($this->id));
    $this->vars['signs'] = isset($c[$this->id])?$c[$this->id]:0;
  }
}
?>