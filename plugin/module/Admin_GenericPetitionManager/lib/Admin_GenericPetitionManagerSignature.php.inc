<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 *
 * Admin_GenericPetitionManagerSignature object for Admin_GenericPetitionManager Module
 */

class Admin_GenericPetitionManagerSignature extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericPetitionManagerSignature ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('petition', 'db', 'date', 'bigint unsigned', '', 0);
    $this->add_newItem('signdate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('title', 'db', 'text', 'varchar', 6, '');
    $this->add_newItem('firstname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('lastname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('email', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('address', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('zipcode', 'db', 'text', 'varchar', 12, '');
    $this->add_newItem('city', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('country', 'db', 'text', 'varchar', 3, '');
    $this->add_newItem('birthdate', 'db', 'date', 'bigint', '', time());
   
    /* temp items */
    $this->add_newItem('confirm', 'temp', 'integer', '', '', 0);

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean success
   * @access public
   */
  function check_data() {
    
    /* check security code 
    if ( !isset($_REQUEST['secode']))
      return false;
    $secode = $_REQUEST['secode'];
    
    
    / set secure code 
    if( $this->id == 0 ) { 
      if ( $secode !=  substr(session_id(), 1, 8))
        return false;
    }
    
    /* check mandatory values */
    $this->_libItems['firstname']->value = trim($this->_libItems['firstname']->value);
    if ($this->_libItems['firstname']->value == '' ) {
      $this->_libError = $this->get_translation('error_firstnamemustbeset');
      return false;
    }
    
    $this->_libItems['lastname']->value = trim($this->_libItems['lastname']->value);
    if ($this->_libItems['lastname']->value == '' ) {
      $this->_libError = $this->get_translation('error_lastnamemustbeset');
      return false;
    }
    
    $this->_libItems['city']->value = trim($this->_libItems['city']->value);
    if ($this->_libItems['city']->value == '' ) {
      $this->_libError = $this->get_translation('error_citymustbeset');
      return false;
    }
    
    $this->_libItems['zipcode']->value = trim($this->_libItems['zipcode']->value);
    if ($this->_libItems['zipcode']->value == '' ) {
      $this->_libError = $this->get_translation('error_zipcodemustbeset');
      return false;
    }
    
    $this->_libItems['email']->value = trim($this->_libItems['email']->value);
    if ($this->_libItems['email']->value == '' ) {
      $this->_libError = $this->get_translation('error_emailmustbeset');
      return false;
    }
        
    if (mail_isValidEmail($this->_libItems['email']->value) == false) {
      $this->_libError = $this->get_translation('error_emailmustbevalid');
      return false;    
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
    $where = array();

    if ( isset( $_REQUEST['petition_id']) and $_REQUEST['petition_id'])
      $where[] = 'petition = '.$_REQUEST['petition_id'];

    if ( isset( $params['status'] ) and $params['status'] > -1 )
      $where[] = 'status='.$params['status'];
    return implode(' and ', $where);
  }

  /* specific methods */
  
  /*
   * return categories status list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_multiStatusList($full=false) {
    $list = array();
    if($full)
      $list['-1'] = $this->get_translation('signaturesstatus_all');
    $list['0'] = $this->get_translation('signaturesstatus_disabled');
    $list['1'] = $this->get_translation('signaturesstatus_enabled');
    return $list;
  }
  
  /*
   * return single signature status list
   * @return array
   * @access public
   */
  function get_statusList() {
    return array(0 => $this->get_translation('signaturestatus_disabled'),
		 1 => $this->get_translation('signaturestatus_enabled'));
  }
  
  /*
   * get signature count by petition
   * @param array $petitions
   * @return array
   * @access public
   */
  function count_byPetitions($petitions=null) {
    global $camyks;
    
    $list = array();
    /* check petitions */
    if ( is_array($petitions) and count($petitions) == 0)
      return $list;
    
    /* build sql query */
    $sql = 'select petition,  count(id) as cnt from '.$this->_libSQLTable;
    if (  is_array($petitions) and count($petitions)>0 )
      $sql .= ' where petition in ('.implode(',', $petitions).')';
    $sql .= ' group by petition';
    
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* get data from database */
      while ( $data = mysql_fetch_assoc( $req ))
	$list[$data['petition']] = $data['cnt'];
    /* send results */
    return $list;
  }

  /*
   * return signature list with given params
   * @params array $params
   * @return array
   * @access private
   */
  function get_list($params=array()) {
    global $camyks;
    $p = array('status'=>-1, 'petition'=>-1, 'limit'=>-1, 'count'=>-1, 'order'=>'id', 'orderway'=>'');
    $params = array_merge($p, $params);
    $w = $this->build_whereStatement($params);
    return $this->get_objectList($camyks->current_language, $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
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
    
    /* check petition */
    if ( is_numeric($params['petition']) and $params['petition'] != -1)
      $w[] = 'petition = '.$params['petition'];
    elseif ( is_string($params['petition']) and $params['petition'] != '')
      $w[] = 'petition '.$params['petition'];
    elseif(is_array($params['petition'])) {
      if (count($params['petition']) == 0 )
	return 'false';
      elseif(count($params['petition']) == 1)
	$w[] = 'petition = '.$params['petition'][0];
      else
	$w[] = 'petition in ('.implode(', ', $params['petition']).')';
    }
    return implode(' and ', $w);
  }

  /*
   * save object from site
   * @return success
   * @access private
   */
  function save_fromSite() {
    $this->id = 0;
    $this->get_fromHeader();
    $this->_libItems['status']->value = 1;
    return $this->save();
  }
}
?>