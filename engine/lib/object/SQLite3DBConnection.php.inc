<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0b1
 * Creation Date    : Nov 2017
 * Last Modif Date  : Nov 2017
 *
 * SQLite3 Database connection object
 */

final class SQLite3DBConnection extends CDBConnection {
  
  protected $dbName;
  private $dbPath;
  private $dbExtension;
  private $dbEncryptionKey;

  /*
   * Class constructor
   * @return void
   * @access public
   */
  public function __construct() {
    global $camyks;
    parent::__construct();
    
    /* prepare database file path & extension */
    $this->dbName = '';
    $this->dbPath = $camyks->site_var_path.'/databases/';
    $this->dbExtension = '.sqlite3.inc';
    
    /* define connection object */
    $this->connection = null;
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
    $this->active = class_exists('SQLite3');
    $this->dbEncryptionKey = $pwd;
    return true;
  }
  
  /*
   * close server connection
   * @return boolean success
   * @access public
   */
  public function disconnect_server() {
    if ($this->connection != null) {
      $this->connection->close();
      $this->connection = null;
      $this->active = false;
    }
    return true;
  }
  
  /*
   * return version
   * @return string
   * @access public
   */
  public function get_serverVersion() {
    $version = SQLite3::version();
    return $version['versionString'];
  }
  
  /* database related methods */
  
  /*
   * select table
   * @param string $name the database name
   * @return boolean
   * @access public
   */
  public function select_database($name) {
    
    $this->dbName = $this->get_fullDatabaseName($name);
    
    try {
      /* open connection */
      $this->connection = @(new SQLite3($this->dbName, SQLITE3_OPEN_READWRITE, $this->dbEncryptionKey));
    } catch (SQLite3Exception $error) {
      die ($error);
      return false;
    }
    
    /* return connection test : to do */
    return true; 
  }
  
  /* 
   * create a database
   * @param string $name
   * @param string $charset
   * @return boolean
   * @access public
   */
  public function create_database($name, $charset='utf8') {
    /* complete folder path */
    folder_completePath($this->dbPath);
    
    try {
      /* open database file in create mode */
      @(new SQLite3($this->get_fullDatabaseName($name), SQLITE3_OPEN_CREATE|SQLITE3_OPEN_READWRITE, $this->dbEncryptionKey));
    } catch (SQLite3Exception $error) {
      return false;
    }
    
    /* return connection test : to do */
    return true; 
  }

  /*
   * check if a base exits
   * @param string $name
   * @return boolean
   * @access public
   */
  public function database_exists($name) {
    return file_exists($this->get_fullDatabaseName($name));
  }
  
  /*
   * dump database
   * @param mixed $file
   * @return mixed
   * @access public
   */
  public function dump_database($file=false) {
    /*
    if (!isset($this->dbName)) {
      return false;
    }
    
    $content = '';
    
    /* write header comments *
    $content = "-- ************************\n";
    $content .= "-- Database \"".$this->dbName."\" dump\n";
    $content .= "-- ".date('r')."\n";
    $content .= "-- ************************\n\n";
    
    /* get list of all table *
    if ($this->execute_query('show tables', 'tableList')) {
    
      /* write tables to content *
      while ($table = $this->get_queryNumDataLine('tableList')) {
      
        /* write table *
        if ($this->execute_query('show create table '.$table[0], 'createTable')) {
          if ($createTable = $this->get_queryNumDataLine('createTable')) {
    
            /* write table comments *
            $content .= "-- ************************\n";
            $content .= "-- Table \"".$table[0]."\"\n";
            $content .= "-- ************************\n";
     
            /* write table creation *
            $content .= $createTable[1].";\n\n";
    
            /* write table content *
            if ($this->execute_query('select * from '.$table[0], 'tableItemList')) {
              while ($insertData = $this->get_queryNumDataLine('tableItemList')) {
                $content .= "insert into ".$table[0]." values(";
                for ($i=0; $i < $this->get_queryFieldCount('tableItemList'); $i++) {
                  if ($i != 0)
                    $content .=  ", ";
                  if ($this->get_queryFieldType($i, 'tableItemList') == "string" || $this->get_queryFieldType($i, 'tableItemList') == "blob")
                    $content .=  "'" . addslashes($insertData[$i]) . "'";
                  else
                    $content .= addslashes($insertData[$i]);
                }
                $content .=  ");\n"; 
              }
            }
          }
          $content .= "\n\n";
        }
      }
    }
    
    /* write content to file and return file writting result or return content *
    if ( $file !== false ) {
      return file_write ($file, $content);
    } else {
      return $content;
    }
    */
  }
  
  /*
   * return database size
   * @return integer
   * @access public
   */
  public function get_databaseSize() {
    $file = new FSFile($this->dbName);
    return $file->size;
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
        /*
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
        */
    );
    
    /* build tables list *
    $sql = 'show table status';
    
    /* execute sql query *
    if ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) { 
      /* get data from database *
      while ($data = $this->get_queryDataLine()) {
        $summary['tables'][] = $data['Name'];
        $summary['lineCount'] += $data['Rows'];
      }
    }
    
    /* build table status *
    $sql = 'check table '.implode(',', $summary['tables']);
        
    /* execute sql query *
    if ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) { 
      /* get data from database *
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
  
  /* table related methods */
      
  /*
   * return available table list
   * @return array
   * @access public
   */
  public function get_tableList() {
    global $camyks;
    
    /* initialise table list */
    $list = array();
    
    /* load list from database */
    if ($this->execute_query('SELECT name FROM sqlite_master WHERE type = "table" AND name NOT LIKE "sqlite%";') or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) { 
      while ($data = $this->get_queryNumDataLine()) {
        $list[] = $data[0];
      }
    }
    
    /* return result */
    return $list;
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
    global $camyks;

    /* build sql query */
    $sql = 'CREATE TABLE IF NOT EXISTS '.$name.' (';
    
    $items = array();
    
    /* add auto id */
    if ($autoId)
      $items[] = ' id INTEGER '.(in_array('id', $primaryKeys)?'PRIMARY KEY ':'').'AUTOINCREMENT';
    
    /* add fields description */
    foreach ($fields as $field) {
      $s = ' `'.$field['name'].'` ';
      switch ( $field['type'] ) {
        case 'int':
        case 'date':
          $s .= 'INTEGER';
          break;
        case 'float':
          $s .= 'REAL';
          break;
        case 'text':
        case 'etext':
        case 'password':
        case 'list':
          $s .= 'TEXT';
          break;
      }
      $items[] = $s;
    }
    
    $sql .= implode(', ',$items).');';
                
    /* return result of sql query execution */
    return ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
  }
  
  /* query related methods */
    
  /*
   * execute query
   * @param string $sql
   * @param string $resName
   * @return boolean success
   * @access public
   */
  public function execute_query($sql='', $resName='defaultRes') {
  
    if (string_startsWith($sql, array('select'), true)) {
      /* execute a sql query with results */
      $this->queryRes[$resName] = $this->connection->query($sql);
      return ($this->queryRes[$resName] !== false);
    } else {
      /* execute a resultless query */
      return $this->connection->exec($sql);
    }
    
  }

  /*
   * return id generated by last query
   * @param string $resName
   * @return integer
   * @access public
   */
  public function get_queryGeneratedId($resName='defaultRes') {
    return $this->connection->lastInsertRowID();
  }

  /*
   * return next query data line
   * @param string $resName
   * @return array
   * @access public
   */
  public function get_queryDataLine($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->fetchArray(SQLITE3_ASSOC);
    return false;
  }
  
  /*
   * return next query data line with numeric indexes
   * @param string $resName
   * @return array
   * @access public
   */
  public function get_queryNumDataLine($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->fetchArray(SQLITE3_NUM);
    return false;
  }

  /*
   * return latest query error
   * @param string $resName
   * @return string
   * @access public
   */
  public function get_queryError($resName='defaultRes') {
    return $this->connection->lastErrorMsg();
  }

  /*
   * return latest query affected rows
   * @param string $resName
   * @return integer
   * @access public
   */
  public function get_queryAffectedRows($resName='defaultRes') {
    return $this->connection->changes();
  }
  
  /*
   * return latest query field count
   * @param string $resName
   * @return integer 
   * @access public
   */
  public function get_queryFieldCount($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->numColumns();
    return '';
  }
  
  /*
   * return latest query field type
   * @param integer $fIndex
   * @param string $resName
   * @return string
   * @access public
   */
  public function get_queryFieldType($fIndex=0, $resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->get_compatibleType($this->queryRes[$resName]->columnType($fIndex));
    return false;
  }
  
  /*
   * close ressource
   * @param string $resName
   * @return boolean result
   * @access public
   */
  public function close_ressource($resName='defaultRes') {
    if (isset($this->queryRes[$resName]))
      return $this->queryRes[$resName]->finalize();
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
    return SQLite3::escapeString($string);
  }
  
  /*
   * return sqlite3 compatible type from given type
   * @param integer $type
   * @return string
   * @access private
   */
  private function get_compatibleType($type=1) {
    switch ($type) {    
      /* int */
      case SQLITE3_INTEGER: return 'int';
      
      /* float */
      case SQLITE3_FLOAT: return 'real';
  
      /* blobs */
      case SQLITE3_BLOB: return 'blob';
      
      /* texts */
      case SQLITE3_TEXT: return 'string';
      
      /* null */
      case SQLITE3_NULL: return 'null';
    }
    return '';
  }
  
  /* private tool methods */
  
  /*
   * return full database path
   * @param string $dbName
   * @return string
   * @access private
   */
  private function get_fullDatabaseName($dbName) {
    /* check name : to do */
    $name = $dbName;
    
    /* return database path */
    return $this->dbPath.$name.$this->dbExtension;
  }
}