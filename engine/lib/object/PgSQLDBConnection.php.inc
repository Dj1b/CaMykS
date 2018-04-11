<?php
/**
 * @brief Postgre Database connection object
 * @details Engine / Object Library
 * @file engine/lib/object/PgSQLDBConnection.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Complete create_database(), dump_database() and get_databaseSummary() methods.
 */

/**
 * PgSQLDBConnection class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class PgSQLDBConnection extends CDBConnection {
    /* server related methods */

    /**
     * Connect to server.
     * @param string $host
     * @param string $login
     * @param string $pwd
     * @param string $driver
     * @return boolean success
     */
    public function connect_server($host='localhost', $login='', $pwd='', $driver='') {
        /* save element util having database name */
        $this->host = $host;
        $this->login = $login;
        $this->pwd = $pwd;

        $this->active = true;
        $this->connection = false;

        /* return as success */
        return true;
    }

    /**
     * Close server connection.
     * @return boolean success
     */
    public function disconnect_server() {
        $this->active = false;
        if ($this->is_connectionActive() and $this->connection) {
            return pg_close($this->connection) and ($this->connection = false);
        }
        return true;
    }

    /**
     * Return database engine version.
     * @return string
     */
    public function get_serverVersion() {
        if ($this->is_connectionActive()) {
            $v = pg_version($this->connection);
            return $v['client'];
        }
        return '';
    }

    /* database related methods */

    /**
     * Select database.
     * @param string $name the database name
     * @return boolean
     */
    public function select_database($name) {
        /* check connection is already active */
        if ($this->connection !== false)
          return $this->active;

        /* build connection params */
        $connParams = "";
        if ($this->host != '') $connParams .= "host=".$this->host;
        if ($name != '') $connParams .= " dbname=".$name;
        if ($this->login != '') $connParams .= " user=".$this->login;
        if ($this->pwd != '') $connParams .= " password=".$this->pwd;
        $connParams .= " options='--client_encoding=UTF8'";

        /* database server connection */
        $this->connection = @pg_pconnect($connParams);

        /* record dbName on success */
        if ($this->connection !== false)
            $this->dbName = $name;

        /* check if connection is made successfully */
        $this->active = $this->connection !== false;
        return $this->active;
    }

    /**
     * Create a database.
     * @param string $name
     * @param string $charset
     * @return boolean
     * @todo Complete method.
     */
    public function create_database($name, $charset='utf8') {
        return false; // current can't create database from PHP
    }

    /**
     * Check if a base exists.
     * @param string $name
     * @return boolean
     */
    public function database_exists($name) {
        /* try to connect to database */
        return $this->select_database($name);
    }

    /**
     * Dump database.
     * @param mixed $file
     * @return mixed
     * @todo Complete method.
     */
    public function dump_database($file=false) {
        /* TO DO */
    }

    /**
     * Return database size.
     * @return integer
     */
    public function get_databaseSize() {
        $this->execute_query('SELECT pg_database.datname, pg_database_size(pg_database.datname) AS size FROM pg_database;');
        if ($v = $this->get_queryDataLine())
            return $v['size'];
        return 0;
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

    /* table related methods */

    /**
     * Return available table list.
     * @return array
     */
    public function get_tableList() {
        global $camyks;

        /* initialise table list */
        $list = array();

        /* load list from database */
        $sql = 'SELECT * FROM pg_catalog.pg_tables as t where t.schemaname="public";';
        if ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            while ($data = $this->get_queryNumDataLine()) {
                $list[] = $data[1];
            }
        }

        /* return result */
        return $list;
    }

    /**
     * Create a table in the database
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

        /* add auto id */
        if ($autoId)
            $sql .= ' id SERIAL not null,';

        /* add fields description */
        foreach ($fields as $field) {
            $s = ' `'.$field['name'].'` ';
            switch ($field['type']) {
                case 'int':
                    /* determine data type from field */
                    $f = trim(strtolower($field['desc1']));
                    switch ($f) {
                        case 'tinyint':
                        case 'tinyint unsigned':
                        case 'smallint':
                            $s .= 'SMALLINT';
                            break;
                        case 'smallint unsigned':
                        case 'mediumint':
                        case 'mediumint unsigned':
                            $s .= 'INTEGER';
                            break;
                        case 'bigint unsigned':
                            $s .= 'NUMERIC(20)';
                            break;
                        default:
                        case 'bigint':
                        case 'int unsigned':
                            $s .= 'BIGINT';
                            break;
                    }
                    $s .= ' NOT NULL';
                    break;
                case 'float':
                    $s .= 'REAL OT NULL';
                    break;
                case 'text':
                case 'etext':
                case 'password':
                case 'list':
                    if ($field['desc1'] == 'varchar')
                        $s .= ' VARCHAR('.$field['desc2'].')';
                    else
                        $s .= ' TEXT';
                    $s .= ' NOT NULL';
                    break;
                case 'date':
                    $s .= 'NUMERIC(20) NOT NULL';
                    break;
            }
            $sql .= $s.',';
        }

        $sql .= ' PRIMARY KEY(`'.implode('`,`', $primaryKeys).'`))';

        /* return result of sql query execution */
        return ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /* query related methods */

    /**
     * Execute query.
     * @param string $sql
     * @param string $resName
     * @return boolean success
     */
    public function execute_query($sql='', $resName='defaultRes') {
        /* check connection */
        if ($this->connection === false)
          return false;

        /* update query */
        $sql = $this->replace_quotes($sql);
        $sql = $this->convert_query($sql);

        /* execute query */
        $this->queryRes[$resName] = pg_query($this->connection, $sql);
        return ($this->queryRes[$resName] !== false);
    }

    /**
     * Return id generated by last query.
     * @param string $resName
     * @return integer
     */
    public function get_queryGeneratedId($resName='defaultRes') {
        $r = $this->get_queryNumDataLine($resName);
        if ($r != false and isset($r[0]))
            return $r[0];
        return 0;
    }

    /**
     * Return next query data line.
     * @param string $resName
     * @return array
     */
    public function get_queryDataLine($resName='defaultRes') {
        if (isset($this->queryRes[$resName]) and !is_bool($this->queryRes[$resName]))
            return pg_fetch_assoc($this->queryRes[$resName]);
        return false;
    }

    /**
     * Return next query data line with numeric indexes.
     * @param string $resName
     * @return array
     */
    public function get_queryNumDataLine($resName='defaultRes') {
        if (isset($this->queryRes[$resName]) and !is_bool($this->queryRes[$resName]))
            return pg_fetch_row($this->queryRes[$resName]);
        return false;
    }

    /**
     * Return latest query error.
     * @param string $resName
     * @return string
     */
    public function get_queryError($resName='defaultRes') {
        if (isset($this->queryRes[$resName]) and !is_bool($this->queryRes[$resName])) {
            return @pg_result_error($this->queryRes[$resName]);
        }
        return false;
    }

    /**
     * Return latest query affected rows.
     * @param string $resName
     * @return integer
     */
    public function get_queryAffectedRows($resName='defaultRes') {
        if (isset($this->queryRes[$resName]) and !is_bool($this->queryRes[$resName]))
            return pg_affected_rows($this->queryRes[$resName]);
        return 0;
    }

    /**
     * Return latest query field count.
     * @param string $resName
     * @return integer
     */
    public function get_queryFieldCount($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return pg_num_fields($this->queryRes[$resName]);
        return false;
    }

    /**
     * Return latest query field type.
     * @param integer $fIndex
     * @param string $resName
     * @return string
     */
    public function get_queryFieldType($fIndex=0, $resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return pg_field_type($this->queryRes[$resName], $fIndex);
        return false;
    }

    /**
     * Close ressource.
     * @param string $resName
     * @return boolean result
     */
    public function close_ressource($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return pg_free_result($this->queryRes[$resName]);
        return true;
    }

    /* data related methods */

    /**
     * Return escaped string.
     * @param string $string
     * @return string
     */
    public function escape_string($string) {
        if ($this->connection != null)
            return pg_escape_string($this->connection, $string);
        return parent::escape_string($string);
    }

    /* special methods */

    /**
     * Return specific insert extra from driver.
     * @return string
     */
    public function get_insertExtra() {
        return ' returning id';
    }

    /**
     * Replace quotes.
     * @param string $sql
     * @return string
     */
    private function replace_quotes($sql='') {
        /* replace double quotes by single quotes */
        $sql = preg_replace('/"/', '\'', $sql);

        /* replace special quotes by double quotes */
        $sql = preg_replace('/`/', '"', $sql);

        /* return query */
        return $sql;
    }

    /**
     * Convert query from mysql compatible to pgsql database.
     * @param string $sql
     * @return string
     */
    private function convert_query($sql='') {
        /* update limit x,y values to limit y offset x values */
        if (preg_match('/limit [0-9]+[ ,]+[0-9]+/', $sql))
            $sql = preg_replace('/limit ([0-9]+)[ ,]+([0-9]+)/', 'limit $2 offset $1', $sql);

        /* return query */
        return $sql;
    }
}