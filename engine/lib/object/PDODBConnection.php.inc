<?php
/**
 * @brief PDO Database connection object
 * @details Engine / Object Library
 * @file engine/lib/object/PDODBConnection.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2014
 * @date Modification: Apr 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PDODBConnection class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class PDODBConnection extends CDBConnection {
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

    /**
     * Close server connection.
     * @return boolean success
     */
    public function disconnect_server() {
        $this->active = false;
        $this->connection = null;
    }

    /**
     * Return database engine version.
     * @return string
     */
    public function get_serverVersion() {
        if ($this->is_connectionActive())
            return $this->connection->getAttribute(PDO::ATTR_SERVER_VERSION);
        return '';
    }

    /* database related methods */

    /**
     * Select database.
     * @param string $name the database name
     * @return boolean
     */
    public function select_database($name) {
        if (!$this->is_connectionActive())
            return false;
        $this->dbName = $name;
        return $this->execute_query('use '.$name);
    }

    /**
     * Create a database.
     * @param string $name
     * @param string $charset
     * @return boolean
     */
    public function create_database($name, $charset='utf8') {
        return $this->execute_query('CREATE DATABASE '.$name.' DEFAULT CHARACTER SET '.$charset);
    }

    /**
     * Check if a base exists.
     * @param string $name
     * @return boolean
     */
    public function database_exists($name) {
        return $this->connection->execute_query('show databases like "'.$name.'"');
    }

    /**
     * Dump database.
     * @param mixed $file
     * @return mixed
     */
    public function dump_database($file=false) {
        if (!isset($this->dbName)) {
            return false;
        }

        $content = '';

        /* write header comments */
        $content = "-- ************************\n";
        $content .= "-- Database \"".$this->dbName."\" dump\n";
        $content .= "-- ".date('r')."\n";
        $content .= "-- ************************\n\n";

        /* get list of all table */
        if ($this->execute_query('show tables', 'tableList')) {

            /* write tables to content */
            while ($table = $this->get_queryNumDataLine('tableList')) {

                /* write table */
                if ($this->execute_query('show create table '.$table[0], 'createTable')) {
                    if ($createTable = $this->get_queryNumDataLine('createTable')) {

                        /* write table comments */
                        $content .= "-- ************************\n";
                        $content .= "-- Table \"".$table[0]."\"\n";
                        $content .= "-- ************************\n";

                        /* write table creation */
                        $content .= $createTable[1].";\n\n";

                        /* write table content */
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

        /* write content to file and return file writting result or return content */
        if ($file !== false) {
            return file_write($file, $content);
        } else {
            return $content;
        }
    }

    /**
     * Return database size.
     * @return integer
     */
    public function get_databaseSize() {
        /* init size */
        $size = 0;

        /* get infos from database */
        if ($this->execute_query('show table status')) {
            /* set size with infos */
            while ($data = $this->get_queryDataLine()) {
                $size += $data["Data_length"] + $data["Index_length"];
            }
            return $size;
        }
        return 0;
    }

    /**
     * Return database information summary.
     * @return array
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
            'connections'   => '',
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

        /* get maximum allowed connections */
        $sql = 'show variables like "max_connections";';
        $max = 0;

        if ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get data from database */
            if ($data = $this->get_queryDataLine())
                $max = $data['Value'];
        }

        /* get current connections */
        $sql = 'show processlist;';
        $current = 0;

        if ($this->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get data from database */
            while ($data = $this->get_queryDataLine())
                $current++;
        }
        $summary['connections'] = $current . '/'. $max;

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
        if ($this->execute_query('show tables') or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
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

        /* add auto id */
        if ($autoId)
            $sql .= ' id BIGINT UNSIGNED NOT NULL auto_increment,';

        /* add fields description */
        foreach ($fields as $field) {
            $s = ' `'.$field['name'].'` ';
            $s .= strtoupper ($field['desc1']);
            if ($field['desc2'] != '') {
                $s .= '('.$field['desc2'].')';
            }
            switch ($field['type']) {
                case 'int':
                    $s .= ' default '.(int)$field['default'];
                    break;
                case 'float':
                    $s .= ' default '.(float)$field['default'];
                    break;
                case 'text':
                case 'etext':
                    if ($field['desc2'] == 'varchar')
                        $s .= ' default "'.addslashes($field['default']).'"';
                    break;
                case 'password':
                    $s .= ' default ""';
                    break;
                case 'date':
                    $s .= ' default 0';
                    break;
                case 'list':
                    $s .= ' default ""';
                    break;
            }
            $sql .= $s.',';
        }
        $sql .= ' PRIMARY KEY(`'.implode('`,`', $primaryKeys).'`))';
        $sql .= ' CHARACTER SET '.$charset.'';

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

    /**
     * Return id generated by last query.
     * @param string $resName
     * @return integer
     */
    public function get_queryGeneratedId($resName='defaultRes') {
        return $this->connection->lastInsertId();
    }

    /**
     * Return next query data line.
     * @param string $resName
     * @return array
     */
    public function get_queryDataLine($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->fetch(PDO::FETCH_ASSOC);
        return false;
    }

    /**
     * Return next query data line with numeric indexes.
     * @param string $resName
     * @return array
     */
    public function get_queryNumDataLine($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->fetch(PDO::FETCH_NUM);
        return false;
    }

    /**
     * Return latest query error.
     * @param string $resName
     * @return string
     */
    public function get_queryError($resName='defaultRes') {
        return $this->queryError[2];
    }

    /**
     * Return latest query affected rows.
     * @param string $resName
     * @return integer
     */
    public function get_queryAffectedRows($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->rowCount();
        return false;
    }

    /**
     * Return latest query field count.
     * @param string $resName
     * @return integer
     */
    public function get_queryFieldCount($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->columnCount();
        return false;
    }

    /**
     * Return latest query field type.
     * @param integer $fIndex
     * @param string $resName
     * @return string
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

    /**
     * Close ressource.
     * @param string $resName
     * @return boolean result
     */
    public function close_ressource($resName='defaultRes') {
        if (isset($this->queryRes[$resName]))
            return $this->queryRes[$resName]->closeCursor();
        return true;
    }

    /* data related methods */

    /**
     * Return escaped string.
     * @param string $string
     * @return string
     */
    public function escape_string($string) {
        return $this->connection->quote($string);
    }

    /**
     * Return mysql compatible type from given type.
     * @param integer $type
     * @return string
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