<?php
/**
 * @brief Interface object with the database driver and connection.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2005
 * @date Modification: Jul 2025
 * @copyright 2005 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Database_connection class.
 */
final class Database_connection {
    /**
     * @var Object $connection
     * @brief Connection with the driver and the database.
     */
    private $connection;

    /**
     * @var string $dbName
     * @brief Database name.
     */
    private $dbName;

    /**
     * @var array $statistics
     * @brief Statistics to record.
     */
    private $statistics;

    /**
     * @var string $reportStats
     * @brief Method to report statistics.
     */
    private $reportStats;

    /**
     * @var array $queries
     * @brief List of executed queries.
     */
    private $queries;

    /**
     * @var string $reportQueries
     * @brief Method to report queries.
     */
    private $reportQueries;

    /*
     * Class constructor.
     * @param string $host the datebase host name
     * @param string $login the database login value
     * @param string $pwd the database password for the given login
     * @param string $driver the driver to use as database connection
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
            case 'pgsql':
                require_once 'PgSQLDBConnection.php.inc';
                $this->connection = new PgSQLDBConnection();
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

    /**
     * Select database.
     * @param string $name
     * @return boolean
     */
    public function select($name) {
        $this->dbName = $name;
        return $this->connection->select_database($name);
    }

    /**
     * Close database connnection.
     * @return boolean
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

    /**
     * Check if connection is active.
     * @return boolean
     */
    public function is_active() {
        return $this->connection->is_connectionActive();
    }

    /**
     * Check connection status.
     * @param string $name
     * @return array
     */
    public function check_status($name) {
        return $this->connection->check_status($name);
    }

    /**
     * Return stats report result.
     * @return array
     */
    public function get_statsReportResult() {
        return $this->statistics;
    }

    /**
     * Return stats queries result.
     * @return array
     */
    public function get_statsQueriesResult() {
        return $this->queries;
    }

    /**
     * Return database engine version.
     * @return string
     */
    public function get_serverVersion() {
        return $this->connection->get_serverVersion();
    }

    /* database related methods */

    /**
     * Create a database.
     * @param string $name
     * @param string $charset
     * @return boolean
     */
    public function database_create($name, $charset='utf8') {
        return $this->connection->create_database($name, $charset);
    }

    /**
     * Check if a database exits
     * @param string $name
     * @return boolean
     */
    public function database_exists($name) {
        return $this->connection->database_exists($name);
    }

    /**
     * Dump database.
     * @param mixed $file
     * @return mixed
     */
    public function database_dump($file=false) {
        return $this->connection->dump_database($file);
    }

    /**
     * Return database size.
     * @return integer
     */
    public function database_getSize() {
        return $this->connection->get_databaseSize();
    }

    /**
     * Return database summary.
     * @return integer
     */
    public function database_getSummary() {
        return $this->connection->get_databaseSummary();
    }

    /* table related methods */

    /**
     * Return database table list.
     * @return array
     */
    public function get_tableList() {
        return $this->connection->get_tableList();
    }

    /**
     * Create a table in the database.
     * @param string $name
     * @param array $fields
     * @param string $charset
     * @param boolean $autoId
     * @param array $primaryKeys
     * @return boolean success
     */
    public function create_table($name, $fields, $charset='utf8', $autoId=true, $primaryKeys=array('id')) {
        return $this->connection->create_table($name, $fields, $charset, $autoId, $primaryKeys);
    }

    /* query related method */

    /**
     * Execute query.
     * @param string $sql
     * @param string $resName
     * @return boolean success
     */
    public function execute_query($sql='', $resName='defaultRes') {
        $this->statistics['queries']++;
        if ($this->reportQueries)
            $this->queries[] = $sql;
        return $this->connection->execute_query($sql, $resName);
    }

    /**
     * Execute multiple queries at once.
     * @param string $sql
     * @param string $resName
     * @return boolean success
     */
    public function execute_multiQueries($sql='', $resName='defaultRes') {
        $this->statistics['queries']++;
        if ($this->reportQueries)
            $this->queries[] = $sql;
        return $this->connection->execute_multiQueries($sql, $resName);
    }

    /**
     * Return id generated by last query.
     * @param string $resName
     * @return integer
     */
    public function get_queryGeneratedId($resName='defaultRes') {
        return $this->connection->get_queryGeneratedId($resName);
    }

    /**
     * Return next query data line.
     * @param string $resName
     * @return array
     */
    public function get_queryDataLine($resName='defaultRes') {
        if ($l = $this->connection->get_queryDataLine($resName)) {
            $this->statistics['fetchedLines']++;
            return $l;
        }
        return false;
    }

    /**
     * Return next query data line with numeric index.
     * @param string $resName
     * @return array
     */
    public function get_queryNumDataLine($resName='defaultRes') {
        if ($l = $this->connection->get_queryNumDataLine($resName)) {
            $this->statistics['fetchedLines']++;
            return $l;
        }
        return false;
    }

    /**
     * Return latest query error.
     * @param string $resName
     * @return string
     */
    public function get_queryError($resName='defaultRes') {
        return $this->connection->get_queryError($resName);
    }

    /**
     * Return latest query affected rows.
     * @param string $resName
     * @return integer
     */
    public function get_queryAffectedRows($resName='defaultRes') {
        $v = $this->connection->get_queryAffectedRows($resName);
        $this->statistics['updatedLines'] += $v;
        return $v;
    }

    /**
     * Return latest query field count.
     * @param string $resName
     * @return integer
     */
    public function get_queryFieldCount($resName='defaultRes') {
        return $this->connection->get_queryFieldCount($resName);
    }

    /**
     * Return latest query field type.
     * @param integer $fIndex
     * @param string $resName
     * @return string
     */
    public function get_queryFieldType($fIndex=0, $resName='defaultRes') {
        return $this->connection->get_queryFieldType($fIndex, $resName);
    }

    /**
     * Close ressource.
     * @param string $resName
     * @return boolean result
     */
    public function close_ressource($resName='defaultRes') {
        return $this->connection->close_ressource($resName);
    }

    /* data related methods */

    /**
     * Return escaped string.
     * @param string $string
     * @return string
     */
    public function escape_string($string='') {
        return $this->connection->escape_string($string);
    }

    /* special methods */

    /*
     * Return specific insert extra from driver.
     * @return string
     */
    public function get_insertExtra() {
        return $this->connection->get_insertExtra();
    }

    /* static methods */

    /**
     * Return available driver list.
     * <br />Method is static to be called without having a working database connection.
     * @return array
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
        if (function_exists('pg_connect'))
            $list['PgSQL'] = 'PgSQL';

        return $list;
    }

    /* deprecated methods */

    /**
     * Alias to close.
     * @see close()
     * @return void
     * @deprecated Use close() instead.
     */
    public function kill() {
        $this->close();
    }
}
?>
