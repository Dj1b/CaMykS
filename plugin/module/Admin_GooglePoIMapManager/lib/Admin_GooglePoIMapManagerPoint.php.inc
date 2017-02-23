<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Mar 2010
 * Last Modif Date  : Mar 2010
 *
 * Admin_GooglePoIMapManagerPoint object for Admin_GooglePoIMapManager Module
 */

class Admin_GooglePoIMapManagerPoint extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GooglePoIMapManagerPoint ( $id, &$module ) {
    global $camyks;
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('category', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('icon', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('address1', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('address2', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('address3', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('country', 'db', 'text', 'varchar', 3, $camyks->get_confValue('site_default_language'));
    $this->add_newItem('latitude', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('longitude', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
    $this->add_newItem('description', 'db', 'text', 'text', '', '', true);
    
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
    if ( isset( $params['status']) and $params['status']!='' and $params['status'] > -1 )
      $search[] = 'status='.$params['status'];
    if ( isset( $params['category']) and $params['category']!='' and $params['category'] > -1 )
      $search[] = 'category='.$params['category'];
    if ( isset( $params['country']) and $params['country']!='')
      $search[] = 'country="'.$params['country'].'"';
    return implode(' and ', $search);
  }
  
  /* specific tool methods */
  
  /*
   * return status
   * @return boolean result
   * @access public
   */
  function is_active() {
    return ($this->vars['status']==1);
  }
   
  /*
   * return point status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_statusList() {
    return array(0 => $this->get_translation('pointstatus_inactive'),
		 1 => $this->get_translation('pointstatus_active'));
  }

  /*
   * return point status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_multiStatusList($full=false) {
    $list = array();
    if ($full)
      $list['-1'] = $this->get_translation('pointsstatus_all');
    $list['0'] = $this->get_translation('pointsstatus_inactive');
    $list['1'] = $this->get_translation('pointsstatus_active');
    return $list;
  }
 
  /*
   * get point count by category
   * @param array $categories
   * @return array
   * @access public
   */
  function get_pointCountByCategories($categories=null) {
    global $camyks;

    $list = array();
    
    /* check types */
    if ( is_array($categories) and count($categories) == 0)
      return $list;
    
    /* build sql query */
    $sql = 'select category, count(id) as cnt from '.$this->_libSQLTable;
    if (  is_array($categories) and count($categories)>0 ) {
      $sql .= ' where category in ('.implode(',', $categories).')';
    }
    $sql .= ' group by category';
    
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__))
      /* get data from database */
      while ( $data = mysql_fetch_assoc( $req ))
	$list[$data['category']] = $data['cnt'];
    
    /* send results */
    return $list;
  }

  /*
   * return point list
   * @param array $params
   * @return array
   * @access private
   */
  function get_list($params=array()) {
    /* set default params */
    $dParams = array('status'=>-1, 'category'=>-1, 'country'=>'', 'language'=>false, 'order'=>'id', 'orderway'=>'', 'categories'=>'');
    /* merge params */
    $params = array_merge($dParams, $params);
    /* build where statement */
    $where = $this->build_whereStatement($params);
    /* return object list */
    return $this->get_objectList($params['language'], $where, -1, -1, $params['order'], $params['orderway']);
  }

  /*
   * return points country list
   * @param array $params
   * @return array
   * @access private
   */
  function get_countryList($params=array()) {
    /* set default params */
    $dParams = array('status'=>-1, 'category'=>-1, 'country'=>'', 'structured'=>false);
    /* merge params */
    $params = array_merge($dParams, $params);
    /* build where statement */
    $where = $this->build_whereStatement($params);
    /* return country list */
    return $this->get_uniqueItemList('country', $s, $params['structured']);
  }

  /*
   * build where statement from params
   * @param array $params
   * @return string
   * @access private
   */
  function build_whereStatement($params=array()) {
    $s = array();    
    /* check status */
    if ($params['status'] > -1)
      $s[] = 'status='.$params['status'];

    /* check category */
    if ($params['category'] > -1)
      $s[] = 'category='.$params['category'];

    /* check categories */
    if ($params['categories'] != '') {
      if (is_string($params['categories']))
	$params['categories'] = explode(',', $params['categories']);
      if (count($params['categories']) == 1)
	$s[] = 'category='.$params['categories'][0];
      else
	$s[] = 'category in ('.implode(', ', $params['categories']).')';
    }
    /* check country */
    if ($params['country'] != '')
      $s[] = 'country="'.$params['country'].'"';
    /* return compiled result */
    return implode(' and ', $s);
  }
}
?>