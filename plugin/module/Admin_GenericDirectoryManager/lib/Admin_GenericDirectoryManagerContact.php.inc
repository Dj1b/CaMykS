<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Jul 2010
 * Last Modif Date  : Jul 2010
 *
 * Admin_GenericDirectoryManagerContact object for Admin_GenericDirectoryManager Module
 */

class Admin_GenericDirectoryManagerContact extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericDirectoryManagerContact ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('category', 'db', 'int', 'int unsigned', '', 0);
    $this->add_newItem('title', 'db', 'text', 'varchar', 6, '');
    $this->add_newItem('firstname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('lastname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('company', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('phone', 'db', 'text', 'varchar', 24, '');
    $this->add_newItem('mobile', 'db', 'text', 'varchar', 24, '');
    $this->add_newItem('fax', 'db', 'text', 'varchar', 24, '');
    $this->add_newItem('address1', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('address2', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('address3', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('address4', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('zipcode', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('city', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('state', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('country', 'db', 'text', 'varchar', 4, '');

    $this->add_newItem('website', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('email', 'db', 'text', 'varchar', 255, '');

    $this->add_newItem('description', 'db', 'text', 'text', '', '', true);

    $this->add_newItem('facebook', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('twitter', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('linkedin', 'db', 'text', 'varchar', 255, '');
    
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
    if ( isset( $params['category'] ) and $params['category'] > 0 )
      $search[] = 'category='.$params['category'];
    return implode(',', $search);
  }
  
  /* specific tool methods */
  
  /*
   * get document count by categories
   * @param array $categories
   * @return array
   * @access public
   */
  function count_byCategories($categories=null) {
    global $camyks;
    
    $list = array();
    /* check categories */
    if ( is_array($categories) and count($categories) == 0)
      return $list;
    
    /* build sql query */
    $sql = 'select category,  count(id) as cnt from '.$this->_libSQLTable;
    if (  is_array($categories) and count($categories)>0 )
      $sql .= ' where category in ('.implode(',', $categories).')';
    $sql .= ' group by category';
    
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* get data from database */
      while ( $data = mysql_fetch_assoc( $req ))
	$list[$data['category']] = $data['cnt'];
    /* send results */
    return $list;
  }
  
  /*
   * return contacts status list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_multiStatusList($full=false) {
    $list = array();
    if($full)
      $list['-1'] = $this->get_translation('contactsstatus_all');
    $list['0'] = $this->get_translation('contactsstatus_disabled');
    $list['1'] = $this->get_translation('contactsstatus_enabled');
    return $list;
  }
  
  /*
   * return single contact status list
   * @return array
   * @access public
   */
  function get_statusList() {
    return array(0 => $this->get_translation('contactstatus_disabled'),
		 1 => $this->get_translation('contactstatus_enabled'));
  }
  
  /*
   * return contact list with given params
   * @params array $params
   * @return array
   * @access private
   */
  function get_list($params=array()) {
    global $camyks;
    $p = array('letters'=>'', 'category'=>0, 'status'=>-1, 'limit'=>-1, 'count'=>-1, 'categories'=>'');
    $params = array_merge($p, $params);
    $w = $this->build_whereStatement($params);
    return $this->get_objectList($camyks->current_language, $w, $params['limit'], $params['count'], 'word', 'asc');
  } 
  
  /*
   * return contact count with given params
   * @params array $params
   * @return array
   * @access private
   */
  function count($params=array()) {
    global $camyks;
    $p = array('letters'=>'', 'category'=>0, 'status'=>-1, 'categories'=>'');
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
    if ( $params['status'] != -1 )
      $w[] = 'status = '.$params['status'];
    
    /* check letters */
    if ($params['letters'] != '') {
      if (strlen($params['letters']) == 1)
	$w[] = 'word like "'.$params['letters'].'%"';
      else
	$w[] = 'word REGEXP "^['.$params['letters'].'].*$"';
    }
    
    /* check category */
    if ($params['category'] > 0)
      $w[] = 'category = '.$params['category'];
    
    /* check categories */
    if ($params['categories'] != '') {
      if (is_string($params['categories']))
	$params['categories'] = explode(',', $params['categories']);
      if (count($params['categories']) == 0)
	return '0=1';
      if (count($params['categories']) == 1)
	$w[] = 'category = '.$params['categories'][0];
      else
	$w[] = 'category in ('.implode(',',$params['categories']).')';
    }
    return implode(' and ', $w);
  }

  /*
   * return contact name name display for admin list
   * @return string
   * @access private
   */
  function get_nameListDisplay() {
    if ($this->vars['company'] == '')
      return $this->vars['firstname'].' '.$this->vars['lastname'];
    return $this->vars['company'];
  }
}
?>