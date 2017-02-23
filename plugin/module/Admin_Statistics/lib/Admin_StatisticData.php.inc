<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0a
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : May 2007
 * Last Modif Date  : Sep 2014
 *
 * Admin_StatisticData object for Admin_Statistics Module
 */

class Admin_StatisticData extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param &Module $module 
   */
  function Admin_StatisticData ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('statid', 'db', 'int', 'bigint', '', 0);
    $this->add_newItem('statcount', 'db', 'int', 'bigint', '', 1);
    $this->add_newItem('statdate', 'db', 'date', 'bigint', '', time()); 
    $this->add_newItem('statdatemonth', 'db', 'date', 'bigint', '', 0 );
    $this->add_newItem('statdateyear', 'db', 'date', 'bigint', '', 0 );
    $this->add_newItem('main', 'db', 'text', 'varchar', 64, ''); 
    $this->add_newItem('data1', 'db', 'text', 'varchar', 64, ''); 
    $this->add_newItem('data2', 'db', 'text', 'varchar', 64, ''); 

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object data values
   * @return boolean
   * @access private
   */
  function check_data() {
    if ( $this->id == 0 ) {
      $this->_libItems['statdatemonth']->value = date_getThisMonthValue();
      $this->_libItems['statdateyear']->value = date_getThisYearValue();
    }
    return true;
  }

  /* specific tool methods */


  /*
   * save single statistic
   * @return boolean
   * @access private
   */
  function update_singleStatistic() {
    return $this->save();
  }

  /*
   * save mixed statistic
   * @return boolean
   * @access private
   */
  function update_mixedStatistic() {
    
    /* update date value */
    $this->set_daydate();

    /* build sql query */
    $sql = 'select id, statcount, statdate, statdatemonth, statdateyear';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where statid='.$this->_libItems['statid']->value;
    $sql .= ' and statdate='.$this->_libItems['statdate']->value;
    $sql .= ' and main="'.$this->_libItems['main']->value.'"';
    $sql .= ' and data1="'.$this->_libItems['data1']->value.'"';
    $sql .= ' and data2="'.$this->_libItems['data2']->value.'"';
    /* execute sql query */
    if ( $this->execute_DBQuery($sql, __LINE__)) {
      if ( $data = $this->get_DBQueryDataLine()) {
	    $this->id = $data['id'];
	    $this->_libItems['statcount']->value = $data['statcount']+1;
	    $this->_libItems['statdatemonth']->value = $data['statdatemonth'];
	    $this->_libItems['statdateyear']->value = $data['statdateyear'];
      }
      /* save object */
      return $this->save();
    }
    return false;
  }

  /*
   * save total statistic
   * @return boolean
   * @access private
   */
  function update_totalStatistic() {
    /* build sql query */
    $sql = 'select id, statcount, statdate';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where statid='.$this->_libItems['statid']->value;
    $sql .= ' and main="'.$this->_libItems['main']->value.'"';
    $sql .= ' and data1="'.$this->_libItems['data1']->value.'"';
    $sql .= ' and data2="'.$this->_libItems['data2']->value.'"';
    /* execute sql query */
    if ( $this->execute_DBQuery($sql, __LINE__ ) ) {
      if ( $data = $this->get_DBQueryDataLine()) {
	    $this->id = $data['id'];
	    $this->_libItems['statcount']->value = $data['statcount']+1;
	    $this->_libItems['statdate']->value = $data['statdate'];
	    $this->_libItems['statdatemonth']->value = $data['statdatemonth'];
	    $this->_libItems['statdateyear']->value = $data['statdateyear'];
      }
      /* save object */
      return $this->save();
    }
    return false;
  }

  /*
   * set date to day date
   * @return void
   * @access private
   */
  function set_daydate() {
    $v = $this->_libItems['statdate']->value;
    $this->_libItems['statdate']->value = mktime(0, 0, 0, date('m', $v), date('d', $v), date('Y', $v));
  }
  
  /*
   * get statistics 
   * @param integer $statId
   * @param array $params
   * @return array
   * @access private
   */
  function get_statistics($statId, $params=array()) {
  
    /* define default params */
    $dParams = array('scale'=>'day', 'main'=>-1, 'date_from'=>-1, 'date_to'=>-1, 'duration'=>-1);
    
    /* merge params */
    $params = array_merge($dParams, $params);
    
    /* check scale value */
    if (!in_array($params['scale'], array('day', 'month', 'year', 'total')))
      $params['scale'] = 'day';
    
    /* build where statement */
    $s = array();
    
    /* check statId */
    $s[] = 'statid = '.$statId;
    
    /* check main value */
    if ($params['main'] > -1)
      $s[] = 'main = '. $params['main'];
        
    /* check dates */
    if ($params['date_from'] > -1) {
      $s[] = 'statdate >= '.$params['date_from'];
      if ($params['date_to'] > -1)
        $s[] = 'statdate < '.$params['date_to'];
      elseif ($params['duration'] > -1) {
        switch ($params['scale']) {
          case 'day' : $v = mktime(0, 0, 0, 1, $params['duration'], 1970); break;
          case 'month' : $v = mktime(0, 0, 0, $params['duration'], 1, 1970); break;
          case 'year': $v = mktime(0, 0, 0, 1, 1, 1970 + $params['duration']); break;
          default : $v = 0;
        }
        $s[] = 'statdate < '.($params['date_from']+$v);
      }
    } elseif ($params['duration'] > -1) {
      switch ($params['scale']) {
        case 'day' : $v = mktime(0, 0, 0, 1, $params['duration'], 1970); break;
        case 'month' : $v = mktime(0, 0, 0, $params['duration'], 1, 1970); break;
        case 'year': $v = mktime(0, 0, 0, 1, 1, 1970 + $params['duration']); break;
        default : $v = 0;
      }
      $s[] = 'statdate >='.(time()-$v);
    }
    
    /* compile params */
    $s = implode(' and ', $s);
        
    /* load data */
    switch ($params['scale']) {
      case 'day': return $this->get_statisticsByDayValue($s);
      case 'month': return $this->get_statisticsByMonthValue($s);
      case 'year': return $this->get_statisticsByYearValue($s);
      case 'total': return $this->get_statisticsTotalValue($s);
    }
    return array();
  }
  
  /*
   * get total value for a stat
   * @param string $where
   * @return integer
   * @access private
   */
  function get_statisticsTotalValue( $where='' ) {

    /* build sql query */
    $sql = 'select sum(statcount) as cnt';
    $sql .= ' from '.$this->_libSQLTable;
    if ( $where != '' )
      $sql .= ' where '. $where;
      
    /* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__ ))
      if ($data = $this->get_DBQueryDataLine())
	    return ( $data['cnt'] > 0 ? $data['cnt'] : 0 );
    return 0;
  }

  /*
   * get statistic value by day
   * @param string $where
   * @return integer
   * @access private
   */
  function get_statisticsByDayValue ($where='' ) {
    return $this->get_statisticsByDateValue( $where, 'statdate');
  }


  /*
   * get statistic value by month
   * @param string $where
   * @return integer
   * @access private
   */
  function get_statisticsByMonthValue ($where='' ) {
    return $this->get_statisticsByDateValue( $where, 'statdatemonth');
  }

  /*
   * get statistic value by year
   * @param string $where
   * @return integer
   * @access private
   */
  function get_statisticsByYearValue ( $where='' ) {
    return $this->get_statisticsByDateValue($where, 'statdateyear');
  }

  /*
   * get statistic value by date
   * @param string $where
   * @param string $object
   * @return integer
   * @access private
   */
  function get_statisticsByDateValue ( $where='', $object='statdate' ) {
    $values = array();
    $values['max'] = 0;
    $values['values'] = array();
    /* build sql query */
    $sql = 'select '.$object.', sum(statcount) as cnt';
    $sql .= ' from '.$this->_libSQLTable;
    if ( $where != '' )
      $sql .= ' where '. $where;
    $sql .= ' group by '.$object;
    $sql .= ' order by statdate asc';

    /* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__ )) {
      while ( $data = $this->get_DBQueryDataLine()) {
	    if ( $data['cnt']>$values['max'] ) 
	      $values['max'] = $data['cnt'];
	    $values['values'][$data[$object]] = $data['cnt'];
      }
    }
    return $values;
  }

  /* 
   * get subitems total values
   * @param string $where
   * @param integer $limit
   * @return void
   * @access private
   */
  function get_mixedStatisticList( $where, $limit=0 ) {
    
    $stats = array();
    /* build sql query */
    $sql = 'select main, sum(statcount) as cnt';
    $sql .= ' from '.$this->_libSQLTable;
    if ( $where != '' )
      $sql .= ' where '. $where;
    $sql .= ' group by main';
    $sql .= ' order by cnt desc';
    if ( $limit > 0 )
      $sql .= ' limit '. $limit;

    /* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__))
      while ( $data = $this->get_DBQueryDataLine()){
	    $stats[$data['main']] = $data['cnt'];
      }
    return $stats;
  } 
}
?>