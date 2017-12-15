<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Creation Date	: Jun 2005
 * Last Modif Date  : Nov 2017
 *
 * Database connection object
 */

final class Database_connection { 
  /* connection object */
  private $connection;
  
  /* variables */
  private $dbName;
  
  /* statistics */
  private $statistics;
  private $reportStats;
  private $queries;
  private $reportQueries;
    
  /*
   * object constructor
   * @param string $host the datebase host name
   * @param string $login the database login value
   * @param string $pwd the database password for the given login
   * @param string $driver the driver to use as database connection
   * @return void
   * @access public
   */
  public function __construct($host='localhost', $login='root', $pwd='', $driver='') {
    global $camyks;
    
    $cDriver = explode(':', strtolower($driver));
    $cDriver = $cDriver[0];
        
    switch ($cDriver) {
         case 'pdo':
            require_once 'PDODBConnection.php.inc';
            $this->connection = new PDODBConnection();
            break;
        case 'mysqli':
            require_once 'MySQLiDBConnection.php.inc';
            $this->connection = new MySQLiDBConnection();
            break;
        case 'sqlite3':
            require_once 'SQLite3DBConnection.php.inc';
            $this->connection = new SQLite3DBConnection();
            break;
        case 'mysql':
        default:
            require_once 'MySQLDBConnection.php.inc';
            $this->connection = new MySQLDBConnection();
            break;
    }
    
    /* initialise statistics */
    $this->statistics = array('queries'=>0, 'fetchedLines'=>0, 'updatedLines'=>0);
    $this->queries = array();
    $this->reportStats = $camyks->get_executionVariable('_cDBStats');
    $this->reportQueries = $camyks->get_executionVariable('_cDBQueries');
        
    /* connect to database */
    $this->connection->connect_server($host, $login, $pwd, $driver);
    
    /* register connection to CaMykS */
    $camyks->register_dbConnection($this);
  }
  
  /* server/connection related methods */
  
  /*
   * select database
   * @param string $name the database name
   * @return boolean
   * @access public
   */
  public function select($name) {
    $this->dbName = $name;
    return $this->connection->select_database($name);
  }
  
  /* 
   * close mysql connnection
   * @return boolean
   * @access public
   */
  public function close() {
    global $camyks;
        
    if ($this->reportStats == 'logs') {
      $s = 'Queries : '.$this->statistics['queries'].' - Fetched lines : '.$this->statistics['fetchedLines'].' - Updated lines : '.$this->statistics['updatedLines'];
      $camyks->log_information($camyks, 'Database connection statistics report', $s);
    } elseif ($this->reportStats == 'html') {
      echo '<div style="display:none">'."\n";
  	  echo 'Queries : '.$this->statistics['queries'].' - Fetched lines : '.$this->statistics['fetchedLines'].' - Updated lines : '.$this->statistics['updatedLines'];
  	  echo '</div>';
    } elseif ($this->reportStats == 'session') {
      $stats = $camyks->get_sessionValue('_cDBStatsResult', array());
      $stats[$this->dbName] = $this->statistics;
      $camyks->set_sessionValue('_cDBStatsResult', $stats);
    } elseif ($this->reportStats == 'shared') {
      $camyks->set_sharedData('_cDBStatsResult', $this->dbName, $this->statistics);
    }
    
    if ($this->reportQueries == 'logs') {
      $s = implode("<br />\n", $this->queries);
      $camyks->log_information($camyks, 'Database connection queries report', $s);
    } elseif ($this->reportQueries == 'html') {
      echo '<div style="display:none">'."\n";
  	  echo implode("<br />\n", $this->queries);
  	  echo '</div>';
    } elseif ($this->reportQueries == 'session') {
      $queries = $camyks->get_sessionValue('_cDBQueriesResult', array());
      $queries[$this->dbName] = $this->queries;
      $camyks->set_sessionValue('_cDBQueriesResult', $queries);
    } elseif ($this->reportQueries == 'shared') {
      $camyks->set_sharedData('_cDBQueriesResult', $this->dbName, $this->queries);
    }
    
    return $this->connection->disconnect_server();
  }
	
  /*
   * check if connection is active
   * @return boolean
   * @access public
   */
  public function is_active () {
    return $this->connection->is_connectionActive();
  }
  
  /*
   * return stats report result
   * return string
   * @access public
   */
  public function get_statsReportResult() {
    return $this->statistics;
  }
  
  /*
   * return stats queries result
   * return string
   * @access public
   */
  public function get_statsQueriesResult() {
    return $this->queries;
  }
  
  /*
   * return version
   * @return string
   * @access public
   */
  public function get_serverVersion() {
    return $this->connection->get_serverVersion();
  }
  
  /* database related methods */
  
  /* 
   * create a database
   * @param string $name
   * @param string $charset
   * @return boolean
   * @access public
   */
  public function database_create($name, $charset='utf8') {
    return $this->connection->create_database($name, $charset);
  }

  /*
   * check if a base exits
   * @param string $name
   * @return boolean
   * @access public
   */
  public function database_exists($name) {
    return $this->connection->database_exists($name);
  }

  /*
   * dump database
   * @param mixed $file
   * @return mixed
   * @access public
   */
  public function database_dump($file=false) {
    return $this->connection->dump_database($file);
  }

  /*
   * return database size
   * @return integer
   * @access public
   */
  public function database_getSize() {
    return $this->connection->get_databaseSize();
  }

  /*
   * return database summary
   * @return integer
   * @access public
   */
  public function database_getSummary() {
    return $this->connection->get_databaseSummary();
  } 
  
  /* table related methods */
  
  /*
   * return database table list
   * @return array
   * @access public
   */
  public function get_tableList() {
    return $this->connection->get_tableList();
  }
    
  /*
   * create a table in the database
   * @param string $name
   * @param array $fields
   * @param string $charset
   * @param boolean $autoId
   * @param array $primaryKeys
   * @return boolean success
   * @access private
   */
  public function create_table($name, $fields, $charset='utf8', $autoId=true, $primaryKeys=array('id')) {
    return $this->connection->create_table($name, $fields, $charset, $autoId, $primaryKeys);
  }
  
  /* query related method */
  
  /*
   * execute query
   * @param string $sql
   * @param string $resName
   * @return boolean success
   * @access public
   */
  public function execute_query($sql='', $resName='defaultRes') {
    $this->statistics['queries']++;
    if ($this->reportQueries)
      $this->queries[] = $sql;
    return $this->connection->execute_query($sql, $resName);
  }
  
  /*
   * return id generated by last query
   * @param string $resName
   * @return integer
   * @access public
   */
  public function get_queryGeneratedId($resName='defaultRes') {
    return $this->connection->get_queryGeneratedId($resName);
  }
  
  /*
   * return next query data line
   * @param string $resName
   * @return array
   * @access public
   */
  public function get_queryDataLine($resName='defaultRes') {
    if ($l = $this->connection->get_queryDataLine($resName)) {
      $this->statistics['fetchedLines']++;
      return $l;
    }
    return false;
  }
  
  /*
   * return next query data line with numeric index
   * @param string $resName
   * @return array
   * @access public
   */
  public function get_queryNumDataLine($resName='defaultRes') {
    if ($l = $this->connection->get_queryNumDataLine($resName)) {
      $this->statistics['fetchedLines']++;
      return $l;
    }
    return false;
  }
  
  /*
   * return latest query error
   * @param string $resName
   * @return string
   * @access public
   */
  public function get_queryError($resName='defaultRes') {
    return $this->connection->get_queryError($resName);
  }
  
  /*
   * return latest query affected rows
   * @param string $resName
   * @return integer
   * @access public
   */
  public function get_queryAffectedRows($resName='defaultRes') {
    $v = $this->connection->get_queryAffectedRows($resName);
    $this->statistics['updatedLines'] += $v;
    return $v;
  }
  
  /*
   * return latest query field count
   * @param string $resName
   * @return integer 
   * @access public
   */
  public function get_queryFieldCount($resName='defaultRes') {
    return $this->connection->get_queryFieldCount($resName);
  }
  
  /*
   * return latest query field type
   * @param integer $fIndex
   * @param string $resName
   * @return string
   * @access public
   */
  public function get_queryFieldType($fIndex=0, $resName='defaultRes') {
    return $this->connection->get_queryFieldType($fIndex, $resName);
  }
  
  /*
   * close ressource
   * @param string $resName
   * @return boolean result
   * @access public
   */
  public function close_ressource($resName='defaultRes') {
    return $this->connection->close_ressource($resName);
  }
   
  
  /* data related methods */
  
  /*
   * return escaped string
   * @param string $string
   * @return string
   * @access public
   */
  public function escape_string($string='') {
    return $this->connection->escape_string($string);
  }
  
  /* static methods */
  
  /*
   * return available driver list
   * method is static to be called without having a working database connection
   * @return array
   * @access public
   */
  public static function get_availableDriverList() {
    $list = array();
    
    if (function_exists('mysql_connect'))
      $list['MySQL'] = 'MySQL';
    if (class_exists('MySQLi'))
      $list['MySQLi'] = 'MySQLi';
    if (class_exists('PDO'))
      $list['PDO:MySQL'] = 'PDO:MySQL';
    if (class_exists('SQLite3'))
      $list['SQLite3'] = 'SQLite3';
    
    return $list;
  }
  
  /* deprecated methods */
  
  /*
   * close connection alias
   * @return void
   * @access public
   */
  public function kill() {
    $this->close();
  }
}
?>