<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Creation Date    : Sep 2014
 * Last Modif Date  : Oct 2017
 *
 * PDO Database connection object
 */

final class PDODBConnection extends CDBConnection {

  /*
   * Class constructor
   * @return void
   * @access public
   */
  public function __construct() {
    parent::__construct();
  }

  /* server related methods */
  
  /*
   * connect to server
   * @param string $host
   * @param string $login
   * @param string $pwd
   * @return boolean success
   * @access public
   */
  public function connect_server($host='localhost', $login='', $pwd='', $driver='') {
    $driver = explode(':', $driver);
    if (!isset($driver[1]))
      return $this->active;
    $d = strtolower($driver[1]);
    
    /* database server connection */
    try {
      $this->connection = @(new PDO($d.':host='.$host.';', $login, $pwd));
      $this->active = 1;
    } catch (PDOException $e) {
      /* connection failed */
    }
    return $this->active;
  }
  
  /*
   * close server connection
   * @return boolean success
   * @access public
   */
  public function disconnect_server() {
    $this->connection = null;
  }
  
  /*
   * return version
   * @return string
   * @access public
   */
  public function get_serverVersion() {
    if ($this->is_connectionActive())
      return $this->connection->getAttribute(PDO::ATTR_SERVER_VERSION);
    return '';
  }
  
  /* database related methods */
  
  /*
   * select table
   * @param string $name the database name
   * @return boolean
   * @access public
   */
  public function select_database ( $name ) {
    if (!$this->is_connectionActive())
      return false;
    $this->dbName = $name;
    return $this->execute_query('use '.$name);
  }
  
  /* 
   * create a database
   * @param string $name
   * @param string $charset
   * @return boolean
   * @access public
   */
  public function create_database ( $name, $charset='utf8' ) {
    return $this->execute_query('CREATE DATABASE '.$name.' DEFAULT CHARACTER SET '.$charset);
  }

  /*
   * check if a base exits
   * @param string $name
   * @return boolean
   * @access public
   */
  public function database_exists ( $name ) {
    return $this->connection->execute_query('show databases like "'.$name.'"');
  }  
  
  /*
   * return database summary
   * @return array
   * @access public
   */
  public function get_databaseSummary() {
    global $camyks;
    
    $summary = array(
        'version'       => $this->get_serverVersion(),
        'size'          => $this->get_databaseSize(),
        'tables'        => array(),
        'tablesStatus'  => array(
            'status'    => array('OK'=>0, 'NotOK'=>0),
            'error'     => array(),
            'info'      => array(),
            'note'      => array(),
            'warning'   => array(),
        ),
        'needRepair'    => false,
        'lineCount'     => 0,
    );
    
    /* build tables list */
    $sql = 'show table status';
    
    /* execute sql query */
    if ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) { 
      /* get data from database */
      while ($data = $this->get_queryDataLine()) {
        $summary['tables'][] = $data['Name'];
        $summary['lineCount'] += $data['Rows'];
      }
    }
    
    /* build table status */
    $sql = 'check table '.implode(',', $summary['tables']);
        
    /* execute sql query */
    if ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) { 
      /* get data from database */
      while ($data = $this->get_queryDataLine()) {
        if ($data['Msg_type'] == 'status') {
          if ($data['Msg_text'] == 'OK')
            $summary['tablesStatus']['status']['OK'] ++;
          else {
            $summary['tablesStatus']['status']['NotOK'] ++;
            $summary['needRepair'] = true;
          }
        } else {
          $table = explode('.', $data['Table']);
          $table = isset($table[1])?$table[1]:$table[0];
          $summary['tablesStatus'][$data['Msg_type']][] = array('table' => $table, 'message'=>$data['Msg_text']);
        }
      }
    }
    
    /* return summary */
    return $summary;
  }
  
  /* query related methods */
    
  /*
   * execute query
   * @param string $sql
   * @return boolean success
   * @access public
   */
  public function execute_query($sql='', $resName='defaultRes') {
    if (string_startsWith($sql, array('select', 'show'), true)) {
      $this->queryRes[$resName] = $this->connection->prepare($sql);
      $this->queryRes[$resName]->execute();
      $this->queryError = $this->queryRes[$resName]->errorInfo();
      if ((int)$this->queryError[0] > 0)
        return false;
      return true;
    } else {
      $this->queryRes[$resName] = $this->connection->query($sql);
      $this->queryError = $this->connection->errorInfo();
      return ($this->queryRes[$resName] !== false);
    }
  }

  /*
   * return id generated by last query
   * @return integer
   * @access public
   */
  public function get_queryGeneratedId($resName='defaultRes') {
    return $this->connection->lastInsertId();
  }

  /*
   * return next query data line
   * @return array
   * @access public
   */
  public function get_queryDataLine($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->fetch(PDO::FETCH_ASSOC);
    return false;
  }
  
  /*
   * return next query data line with numeric indexes
   * @return array
   * @access public
   */
  public function get_queryNumDataLine($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->fetch(PDO::FETCH_NUM);
    return false;
  }

  /*
   * return latest query error
   * @return string
   * @access public
   */
  public function get_queryError($resName='defaultRes') {
    return $this->queryError[2];
  }

  /*
   * return latest query affected rows
   * @return integer
   * @access public
   */
  public function get_queryAffectedRows($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->rowCount();
    return false;
  }
  
  /*
   * return latest query field count
   * @return integer 
   * @access public
   */
  public function get_queryFieldCount($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->columnCount();
    return false;
  }
  
  /*
   * return latest query field type
   * @param integer $fIndex
   * @return string
   * @access public
   */
  public function get_queryFieldType($fIndex=0, $resName='defaultRes') {
    if (isset($this->queryRes[$resName])) {
      $meta = $this->queryRes[$resName]->getColumnMeta($fIndex);
      if (isset($meta['native_type']))
        return $this->get_compatibleType($meta['native_type']);
      return $this->get_compatibleType('DEFAULT');
    }
    return 'string';
  }
  
  /*
   * close ressource
   * @param string $resName
   * @return boolean result
   * @access public
   */
  public function close_ressource($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->closeCursor();
    return true;
  }
  
  /* data related methods */
  
  /*
   * return escaped string
   * @param string $string
   * @return string
   * @access public
   */
  public function escape_string($string) {
    return $this->connection->quote($string);
  }
  
  /*
   * return mysql compatible type from given type
   * @param integer $type
   * @return string
   * @access private
   *
   * MySQL can return :
   * var_string
   * longlong
   * newdecimal
   * geometry
   * 
   * SQLLite may return :
   */
  private function get_compatibleType($type='default') {
    switch (strtolower($type)) {
      /* int */
      case 'tiny': case 'short': case 'long': case 'longlong': case 'integer': return 'int';
      
      /* real */
      case 'float': case 'double': case 'decimal': return 'real';
      
      /* date & time */
      case 'timestamp': return 'timestamp';
      case 'date': return 'date';
      case 'time': return 'time';
      case 'datetime': return 'datetime';
      
      /* blobs */
      case 'tiny_blob': case 'medium_blob': case 'blob': case 'long_blob': return 'blob';
      
      /* strings */
      case 'var_string': case 'string': return 'string';
      
      /* null */
      case 'null': return 'null';

      /* default value for not defined types */
      case 'default': return 'tinyint';
    }
    return $type;
  }
}