<?php
/**
 * @brief SQLite3 Database connection object.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Nov 2017
 * @date Modification: Jul 2025
 * @copyright 2014 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Complete dump_database() and get_databaseSummary() methods.
 */

/**
 * SQLite3DBConnection class.
 */
final class SQLite3DBConnection extends CDBConnection {
    /**
     * @var string $dbPath
     * @brief Database file path.
     */
    private $dbPath;

    /**
     * @var string $dbExtension
     * @brief Database file extension.
     */
    private $dbExtension = '.sqlite3.inc';

    /**
     * @var string $dbEncryptionKey
     * @brief Database encryption key.
     */
    private $dbEncryptionKey;

    /**
     * Class constructor.
     */
    public function __construct() {
        global $camyks;
        parent::__construct();
        /* defing database path */
        $this->dbPath = $camyks->site_var_path.'/databases/';
        /* define connection object */
        $this->connection = null;
    }

    /* Mark: Server related methods */

    /**
     * Connect to server.
     * @param string $host
     * @param string $login
     * @param string $pwd
     * @param string $driver
     * @return boolean success
     */
    public function connect_server($host='localhost', $login='', $pwd='', $driver='') {
        $this->active = class_exists('SQLite3');
        $this->dbEncryptionKey = $pwd;
        return true;
    }

    /**
     * Close server connection.
     * @return boolean success
     */
    public function disconnect_server() {
        if ($this->connection != null) {
            $this->connection->close();
            $this->connection = null;
        }
        $this->active = false;
        return true;
    }

    /**
     * Return database engine version.
     * @return string
     */
    public function get_serverVersion() {
        $version = SQLite3::version();
        return $version['versionString'];
    }

    /* mark: Database related methods */

    /**
     * Select database.
     * @param string $name the database name
     * @return boolean
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

    /**
     * Create a database.
     * @param string $name
     * @param string $charset
     * @return boolean
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

        /* return result */
        return true;
    }

    /**
     * Check if a base exists.
     * @param string $name
     * @return boolean
     */
    public function database_exists($name) {
        return file_exists($this->get_fullDatabaseName($name));
    }

    /**
     * Dump database.
     * @param mixed $file
     * @return mixed
     */
    public function dump_database($file=false) {

    }

    /**
     * Return database size.
     * @return integer
     */
    public function get_databaseSize() {
        $file = new FSFile($this->dbName);
        return $file->size;
    }

    /**
     * Return database summary.
     * @return array
     * @todo Complete method.
     */
    public function get_databaseSummary() {
        global $camyks;

        /* initialise summary */
        $summary = array(
            'version'       => $this->get_serverVersion(),
            'size'          => $this->get_databaseSize(),
        );

        /* completes summary */
        /* TO DO */

        /* return summary */
        return $summary;
    }

    /* Mark: Table related methods */

    /**
     * Return available table list.
     * @return array
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

    /* mark: Query related methods */

    /**
     * Eexecute query.
     * @param string $sql
     * @param string $resName
     * @return boolean success
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

    /**
     * Execute multiple queries at once.
     * @param string $sql
     * @param string $resName
     * @return boolean success
     */
    public function execute_multiQueries($sql='', $resName='defaultRes') {
        return $this->execute_query($sql, $resName);
    }

    /**
     * Return id generated by last query.
     * @param string $resName
     * @return integer
     */
    public function get_queryGeneratedId($resName='defaultRes') {
        return $this->connection->lastInsertRowID();
    }

    /**
     * Return next query data line.
     * @param string $resName
     * @return array
     */
    public function get_queryDataLine($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->fetchArray(SQLITE3_ASSOC);
        return false;
    }

    /**
     * Return next query data line with numeric indexes.
     * @param string $resName
     * @return array
     */
    public function get_queryNumDataLine($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->fetchArray(SQLITE3_NUM);
        return false;
    }

    /**
     * Return latest query error.
     * @param string $resName
     * @return string
     */
    public function get_queryError($resName='defaultRes') {
        return $this->connection->lastErrorMsg();
    }

    /**
     * Return latest query affected rows.
     * @param string $resName
     * @return integer
     */
    public function get_queryAffectedRows($resName='defaultRes') {
        return $this->connection->changes();
    }

    /**
     * Return latest query field count.
     * @param string $resName
     * @return integer
     */
    public function get_queryFieldCount($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->numColumns();
        return '';
    }

    /**
     * Return latest query field type.
     * @param integer $fIndex
     * @param string $resName
     * @return string
     */
    public function get_queryFieldType($fIndex=0, $resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->get_compatibleType($this->queryRes[$resName]->columnType($fIndex));
        return false;
    }

    /**
     * Close ressource.
     * @param string $resName
     * @return boolean result
     */
    public function close_ressource($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->finalize();
        return true;
    }

    /* Mark Data related methods */

    /**
     * Return escaped string.
     * @param string $string
     * @return string
     */
    public function escape_string($string) {
        return SQLite3::escapeString($string);
    }

    /**
     * Return sqlite3 compatible type from given type.
     * @param integer $type
     * @return string
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

    /* Mark: Private tool methods */

    /**
     * Return full database path.
     * @param string $dbName
     * @return string
     */
    private function get_fullDatabaseName($dbName) {
        /* check name : to do */
        $name = $dbName;

        /* return database path */
        return $this->dbPath.$name.$this->dbExtension;
    }
}
