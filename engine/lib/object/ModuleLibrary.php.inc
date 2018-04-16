<?php
/**
 * @brief ModuleLibrary
 * @details Engine / Object Library
 * @file engine/lib/object/ModuleLibrary.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @details  Use to manage localised (or not) content from database, files or text objects
 */

/**
 * ModuleLibrary class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
abstract class ModuleLibrary {
    /**
     * @var string $object_type
     * @brief Object type.
     */
    public $object_type = 'ModuleLibrary';

    /**
     * @var string $_libName
     * @brief Object name.
     */
    public $_libName;

    /**
     * @var Module $_libParent
     * @brief Parent module.
     */
    public $_libParent;

    /**
     * @var string $_libParentFile
     * @brief Object library file.
     */
    protected $_libParentFile;

    /**
     * @var array $_libItems
     * @brief Object item list.
     */
    public $_libItems = array();

    /**
     * @var array $_libItemTypes
     * @brief Object item list by type.
     */
    public $_libItemTypes = array('db' => array(), 'dbl' => array(), 'text' => array(), 'file' => array(), 'temp' => array());

    /**
     * @var Database_connection $_libDBConnector
     * @brief Database connection.
     */
    protected $_libDBConnector;

    /**
     * @var string $_libSQLTable
     * @brief Object table name in database.
     */
    public $_libSQLTable;

    /**
     * @var string $_libSQLTable
     * @brief Object table name for localised data in database.
     */
    public $_libSQLLocaleTable;

    /**
     * @var string $_libDesc
     * @brief Library description.
     */
    public $_libDesc;

    /**
     * @var string $_libError
     * @brief Last error.
     */
    public $_libError;

    /**
     * @var boolean $_libError
     * @brief Is library installed.
     */
    public $_libIsInstalled = null;

    /**
     * @var integer $id
     * @brief Object instance id.
     */
    public $id;

    /**
     * @var array $vars
     * @brief Object item values.
     */
    public $vars = array();

    /**
     * Class constructor.
     * @param integer $id
     * @param Object $module
     * @param mixed $wf_version
     */
    public function __construct($id, &$module, $wf_version=false) {
        $this->ModuleLibrary($id, $module, $wf_version);
    }

    /**
     * Old style constructor.
     * @param integer $id
     * @param Object $module
     * @param mixed $wf_version
     */
    public function ModuleLibrary($id, &$module, $wf_version=false) {
        global $camyks;
        $this->id = $id;
        $this->_libParent = $module;
        $c = new ReflectionClass($this);
        $this->_libParentFile = $c->getFileName();
        $this->_libName = get_class($this);
        $this->_libDBConnector = &$camyks->get_dbConnection();
        $this->_libSQLTable = strtolower($this->_libName);
        $this->_libWFVersion = $wf_version;
    }

    /**
     * Finish library object initialisation.
     * @return void
     */
    public function init_library() {
        $this->_libSQLLocaleTable = $this->_libSQLTable.'locale';
        $this->_libDesc = 'Module:'.$this->_libParent->name.' Lib:'.$this->_libName;
    }

    /**
     * Insert a new item in object.
     * @param string $name
     * @param string $itemtype
     * @param string $info0
     * @param string $info1
     * @param mixed $info2
     * @param mixed $default
     * @param boolean $localised
     * @
     */
    protected function add_newItem ($name, $itemtype, $info0, $info1, $info2,  $default=null, $localised=false) {
        global $camyks;

        /* check item name */
        if (isset ($this->_libItems[$name])) {
            $camyks->log_internalerror(
                $this,
                'Module Library Item Definition Error',
                'Item with name "'.$name.'" allready exists in this library items'
            );
            return false;
        }

        /* insertion */
        switch ($itemtype) {
            case 'db' :
                /* insert database item */
                if ($localised) {
                    $this->_libItems[$name] = new MLDatabaseLocalizedItem(
                        $name,
                        $info0,
                        $info1,
                        $info2,
                        $default
                    );
                    $this->_libItemTypes['dbl'][] = $name;
                } else {
                    $this->_libItems[$name] = new MLDatabaseItem(
                        $name,
                        $info0,
                        $info1,
                        $info2,
                        $default
                    );
                    $this->_libItemTypes['db'][] = $name;
                }
                break;
            case 'text' :
                /* insert text item */
                if ($localised) {
                    $this->_libItems[$name] = new MLTextLocalizedItem(
                        $name,
                        $info0,
                        $this->_libParent->plugin_var_path,
                        $default
                    );
                } else {
                    $this->_libItems[$name] = new MLTextItem(
                        $name,
                        $info0,
                        $this->_libParent->plugin_var_path,
                        $default
                    );
                }
                $this->_libItemTypes['text'][] = $name;
                break;
            case 'file':
                /* insert file item */
                if ($localised) {
                     $this->_libItems[$name] = new MLFileLocalizedItem(
                        $name,
                        $info0,
                        $this->_libParent->plugin_var_path,
                        $this->_libParent->plugin_var_url
                    );
                } else {
                    $this->_libItems[$name] = new MLFileItem(
                        $name,
                        $info0,
                        $this->_libParent->plugin_var_path,
                        $this->_libParent->plugin_var_url
                    );
                }
                $this->_libItemTypes['file'][] = $name;
                break;
            case 'temp':
                /* insert temporary item */
                $this->_libItems[$name] = new MLTemporaryItem(
                    $name,
                    $info0,
                    $default
                );
                $this->_libItemTypes['temp'][] = $name;
                break;
        }
    }

    /********************* MAIN METHODS ************************/

    /**
     * Initialise new object.
     * @return boolean success
     */
    public function initialise() {
        $this->id = 0;
        foreach ($this->_libItems as $n=>$item) {
            $this->_libItems[$n]->initialise();
        }
        return true;
    }

    /**
     * Load object.
     * @param mixed $language
     * @return boolean success
     */
    public function get($language=true) {
        global $camyks;

        /* new object */
        if ($this->id == 0)
            return $this->initialise();

        if ($language === false) {
            /* get object database items only */
            return $this->get_databaseItems();
        } else if ($language === true and count($camyks->get_confValue('editing_languages'))>1 ) {
            /* get complete object */
            return $this->get_databaseItems()
                and $this->get_databaseLocalisedItems()
                and $this->get_textItems()
                and $this->get_fileItems()
                and $this->get_tempItems();
        } else {
            /* get complete object, but available in only one language */
            if ($language === true) {
                $languages = $camyks->get_confValue('editing_languages');
                $language = $languages[0];
            }
            return $this->get_allDatabaseItems($language)
                and $this->get_textItems($language)
                and $this->get_fileItems($language)
                and $this->get_tempItems();
        }
    }

    /**
     * Load object from header POST/GET values
     * @param string $prefix
     * @return void
     */
    public function get_fromHeader($prefix='') {
        foreach ($this->_libItems as $n=>$item)
            $this->_libItems[$n]->get_fromHeader($prefix);
    }

    /**
     * Save object.
     * @return boolean success
     */
    public function save() {
        /* check data validity */
        if ($this->check_data()) {
            return $this->save_databaseItems()
                and $this->save_databaseLocalisedItems()
                and $this->save_textItems()
                and $this->save_fileItems();
        }
        return false;
    }

    /**
     * Delete object.
     * @return boolean success
     */
    public function delete() {
        return $this->delete_databaseItems()
            and $this->delete_databaseLocalisedItems()
            and $this->delete_textItems()
            and $this->delete_fileItems();
    }

    /**
     * Delete all objects.
     * @return boolean success
     */
    public function reset() {
        return $this->reset_databaseItems()
            and $this->reset_databaseLocalisedItems()
            and $this->reset_textItems()
            and $this->reset_fileItems();
    }

    /**
     * Install object.
     * @return boolean success
     */
    public function install() {
        return $this->install_databaseItems()
            and $this->install_databaseLocalisedItems()
            and $this->install_textItems()
            and $this->install_fileItems();
    }

    /**
     * Uninstall object
     * @return boolean success.
     */
    public function uninstall() {
        return $this->uninstall_databaseItems()
            and $this->uninstall_databaseLocalisedItems();
    }

    /**
     * Check if object is installed.
     * @return boolean result
     */
    public function is_installed() {
        if ($this->_libIsInstalled === null) {
            $this->_libIsInstalled = $this->check_databaseInstallation();
        }
        return $this->_libIsInstalled;
    }

    /**
     * Check if object is marked, to be overwrite.
     * @return boolean result
     */
    public function is_marked() {
        return false;
    }

    /**
     * Return a new object.
     * @param integer $id
     * @return Object
     */
    public function &get_newObject($id=0) {
        eval('$obj = new '.get_class($this).'('.$id.', $this->_libParent);');
        return $obj;
    }

    /*********************** DATABASE I/O ************************/

    /**
     * Load object items from database.
     * @return boolean success
     */
    public function get_databaseItems() {
        global $camyks;
        /* build sql query */
        $sql = 'select *';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where id='.$this->id;
        /* check workflow version if needed */
        if ($this->_libWFVersion !== false) {
            $sql .= ' and wf_version='.$this->_libWFVersion;
        }

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get data from database */
            if ($data = $this->get_DBQueryDataLine()) {
                $this->get_fromArray($data, $this->_libItemTypes['db']);
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    /**
     * Save object database items.
     * @return boolean success
     */
    public function save_databaseItems() {
        if ($this->id == 0)
            return $this->insert_databaseItems();
        return $this->update_databaseItems();
    }

    /**
     * Create object instance into database.
     * @return boolean success
     */
    private function insert_databaseItems() {
        global $camyks;
        /* init */
        $isfirst = true;
        /* build sql query */
        $sql = 'insert into `'.$this->_libSQLTable.'` (';
        foreach ($this->_libItemTypes['db'] as $n) {
            if ($isfirst) {
                $isfirst = false;
            } else {
                $sql .= ', ';
            }
            $sql .= '`'.$n.'`';
        }
        $sql .= ') VALUES (';
       $isfirst = true;
       foreach ($this->_libItemTypes['db'] as $n) {
            if ($isfirst) {
                $isfirst = false;
            } else {
                $sql .= ', ';
            }
            $sql .= $this->_libItems[$n]->get_databaseValue();
        }
        $sql .= ')';
        $sql .= $this->get_DBInsertExtra();
        $sql .= ';';

        /* return result of sql query execution */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            $this->id = $this->get_DBQueryGeneratedId();
            return true;
        }
        return false;
    }

    /**
     * Update object values to database
     * @return boolean success
     */
    private function update_databaseItems() {
        global $camyks;

        /* check for no database item */
        if (count($this->_libItemTypes['db'])==0)
            return true;

        $isfirst = true;

        /* build sql query */
        $sql = 'update `'.$this->_libSQLTable.'`';
        foreach ($this->_libItemTypes['db'] as $n) {
            if ($isfirst) {
                $isfirst = false;
                $sql .= ' SET';
            } else {
                $sql .= ', ';
            }
            $sql .= ' `'.$n.'`='.$this->_libItems[$n]->get_databaseValue();
        }
        $sql .= ' where id='.$this->id;

        /* check workflow version if needed */
        if ($this->_libWFVersion !== false) {
            $sql .= ' and wf_version='.$this->_libWFVersion;
        }

        /* return result of sql query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Delete object from database.
     * @return boolean success
     */
    public function delete_databaseItems() {
        global $camyks;
        /* build sql query */
        $sql = 'delete from '.$this->_libSQLTable.' where id='.$this->id;
        /* check workflow version if needed */
        if ($this->_libWFVersion !== false) {
            $sql .= ' and wf_version='.$this->_libWFVersion;
        }
        /* return result of execute sql query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Reset all objects from database
     * @return boolean success
     */
    public function reset_databaseItems() {
        global $camyks;
        /* build sql query */
        $sql = 'truncate '.$this->_libSQLTable;
        /* return result of execute sql query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Install table in database.
     * @return boolean success
     */
    public function install_databaseItems() {
        global $camyks;

        /* initialise field list */
        $fields = array();

        /* prepare data fields */
        foreach ($this->_libItemTypes['db'] as $n) {
            $fields[] = $this->_libItems[$n]->get_databaseDescription();
        }

        /* execute table creation */
        return $this->create_DBTable($this->_libSQLTable, $fields, $camyks->get_mysqlEncodingValue());
    }

    /**
     * Delete table from database
     * @return boolean success
     */
    public function uninstall_databaseItems() {
        global $camyks;

        /* build sql query */
        $sql = 'drop table '.$this->_libSQLTable;

        /* return result of sql query execution */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Check if table is installed.
     * @return boolean result
     */
    public function check_databaseInstallation() {
        global $camyks;

        /* check database presence in plugin manager module */
        if (isset($camyks->modules['Admin_PluginManager']))
            return $camyks->modules['Admin_PluginManager']->check_tableExists($this->_libSQLTable);

        /* load table list */
        $tl = $camyks->db_conn->get_tableList();

        /* check if main table is in installed table list */
        return in_array($this->_libSQLTable, $tl);
    }

    /**
     * Return sql query for database items object list gathering.
     * @param string $where
     * @param int $limit
     * @param int $count
     * @param string $order
     * @param string $sens
     * @return string
     */
    public function get_objectList_databaseItemsSQLQuery($where='', $limit=-1, $count=-1, $order='id', $sens='') {
        /* build sql query */
        $sql = 'select *';
        $sql .= ' from '.$this->_libSQLTable.' as m';

        /* add where conditions to sql query  */
        if (trim($where) != '') {
            $sql .= ' where '. $this->check_SQLCondition($where);
        }

        /* check order to sql query */
        if (is_string($order)) {
            $order = array($order=>$sens);
        }

        if (is_array($order)) {
            /* add multi order to sql query */
            $osql = array();
            foreach($order as $o => $s) {
                if ($o == 'special') {
                    $osql[] = $s;
                } elseif (($o == 'id' or in_array($o, $this->_libItemTypes['db'])) and in_array(strtolower($s), array ('', 'asc', 'desc'))) {
                    $osql[] = $o.' '.$s;
                }
        }
        if (count($osql) > 0)
            $sql .= ' order by '.implode(', ', $osql);
        }

        /* add limit to sql query */
        if ($limit >=0 and $count > 0) {
            $sql .= ' limit '.$limit.', '.$count;
        } else if ($limit > 0) {
            $sql .= ' limit '.$limit;
        } else if ($count > 0) {
            $sql .= ' limit '.$count;
        }

        return $sql;
    }

    /**
     * Update specific items values from object to database.
     * @param array $updatedItems
     * @return boolean success
     */
    public function update_databaseSpecificItems($updatedItems) {
        global $camyks;
        $isfirst = true;
        /* build sql query */
        $sql = 'update `'.$this->_libSQLTable.'`';
        foreach ($updatedItems as $n) {
            if (in_array($n, $this->_libItemTypes['db'])) {
                $item = $this->_libItems[$n] ;
                if ($isfirst) {
                    $isfirst = false;
                    $sql .= ' SET';
                } else {
                    $sql .= ',';
                }
                $sql .= ' `'.$n.'`='.$item->get_databaseValue();
            }
        }
        $sql .= ' where id='.$this->id;

        /* check workflow version if needed */
        if ($this->_libWFVersion !== false) {
            $sql .= ' and wf_version='.$this->_libWFVersion;
        }

        /* return result of sql query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /*********************** LOCALISED DATABASE I/O **************/

    /**
     * Load database localised items
     * @return boolean success
     */
    public function get_databaseLocalisedItems () {
        global $camyks;

        /* check if object add some databaselocalised item */
        if (count($this->_libItemTypes['dbl']) == 0)
            return true;

        /* build sql query */
        $sql = 'select * ';
        $sql .= ' from '. $this->_libSQLLocaleTable;
        $sql .= ' where objectid='.$this->id;

        /* check workflow version if needed */
        if ($this->_libWFVersion !== false) {
            $sql .= ' and objectwf_version='.$this->_libWFVersion;
        }

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get result of sql query */
            while ($data = $this->get_DBQueryDataLine()) {
                $this->get_fromArray($data, $this->_libItemTypes['dbl']);
            }
            return true;
        }
        return false;
    }

    /**
     * Save database localised items.
     * @return boolean success
     */
    public function save_databaseLocalisedItems() {
        global $camyks;

        /* check if object add some databaselocalised item */
        if (count($this->_libItemTypes['dbl']) == 0)
            return true;

        if ($this->delete_databaseLocalisedItems()) {
            /* build sql query */
            $sql = 'insert into `'.$this->_libSQLLocaleTable.'` (';
            $sql .= ' `objectid`';

            /* check workflow version if needed */
            if ($this->_libWFVersion !== false) {
                $sql .= ', `objectwf_version`';
            }

            $sql .= ', `language`';
            foreach ($this->_libItemTypes['dbl'] as $n) {
                $sql .= ', `'.$n.'`';
            }
            $sql .= ') VALUES';
            $isFirst = true;
            foreach ($camyks->get_confValue('editing_languages') as $l) {
                if ($isFirst) {
                    $isFirst = false;
                } else {
                    $sql .= ', ';
                }
                $sql .= ' (';
                $sql .= ' '.$this->id;

                /* check workflow version if needed */
                if ($this->_libWFVersion !== false) {
                    $sql .= ', '.$this->_libWFVersion;
                }
                $sql .= ', "'.$l.'"';
                foreach ($this->_libItemTypes['dbl'] as $n) {
                    $sql .= ', '.$this->_libItems[$n]->get_databaseValue($l);
                }
                $sql .= ')';
            }
            /* return result of sql query execution */
            return ($this->execute_DBQuery($sql, __LINE__));
        }
        return false;
    }

    /**
     * Delete object localised items from database.
     * @return boolean success
     */
    public function delete_databaseLocalisedItems() {
        global $camyks;

        /* check if object add some databaselocalised item */
        if (count($this->_libItemTypes['dbl']) == 0)
            return true;

        /* build sql query */
        $sql = 'delete from '.$this->_libSQLLocaleTable.' where objectid='.$this->id;

        /* check workflow version if needed */
        if ($this->_libWFVersion !== false) {
            $sql .= ' and objectwf_version='.$this->_libWFVersion;
        }

        /* return result of execute sql query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Reset objects localised items from database.
     * @return boolean success
     */
    public function reset_databaseLocalisedItems() {
        global $camyks;

        /* check if object add some databaselocalised item */
        if (count($this->_libItemTypes['dbl']) == 0)
            return true;

        /* build sql query */
        $sql = 'truncate '.$this->_libSQLLocaleTable;

        /* return result of execute sql query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Install object localised items.
     * @return boolean success
     */
    public function install_databaseLocalisedItems() {
        global $camyks;

        /* check if object add some databaselocalised item */
        if (count($this->_libItemTypes['dbl']) == 0)
            return true;

        /* initialise field list */
        $fields = array();

        /* prepare engine fields */
        $fields[] = array('name'=>'objectid', 'type'=>'int', 'desc1'=>'bigint unsigned', 'desc2'=>'', 'default'=>'');
        $fields[] = array('name'=>'language', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>'3', 'default'=>'');

        /* prepare data fields */
        foreach ($this->_libItemTypes['dbl'] as $n) {
            $fields[] = $this->_libItems[$n]->get_databaseDescription();
        }

        /* execute table creation */
        return $this->create_DBTable($this->_libSQLLocaleTable, $fields, $camyks->get_mysqlencodingvalue());
    }

    /**
     * Return SQL query for database localised items object list gathering.
     * @param array $ids
     * @return string
     */
    public function get_objectList_databaseLocalisedItemsSQLQuery($ids) {
        /* build sql query */
        $sql = 'select *';
        $sql .= ' from '.$this->_libSQLLocaleTable;
        $sql .= ' where objectid in ('.implode(',', $ids).')';
        return $sql;
    }

    /*********************** MIXED DATABASE I/O ******************/

    /**
     * Load database unlocalised and localised items at once for given language.
     * @param string $language
     * @return boolean success
     */
    public function get_allDatabaseItems($language) {
        global $camyks;
        /* no database item : get simple database items */
        if (count($this->_libItemTypes['dbl']) == 0)
            return $this->get_databaseItems();

        /* build sql query */
        $sql = 'select *';
        $sql .= ' from '. $this->_libSQLTable.', '.$this->_libSQLLocaleTable;
        $sql .= ' where '.$this->_libSQLTable.'.id='.$this->id;
        $sql .= ' and '.$this->_libSQLTable.'.id='.$this->_libSQLLocaleTable.'.objectid';
        $sql .= ' and '.$this->_libSQLLocaleTable.'.language="'.$language.'"';

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get result of sql query */
            if ($data =$this->get_DBQueryDataLine()) {
                $matchitems = array_merge($this->_libItemTypes['db'], $this->_libItemTypes['dbl']);
                $this->get_fromArray($data, $matchitems);
                return true;
            } else {
                /* no object found : try to get simple database items */
                $this->get_databaseItems();
            }
        }
        return false;
    }

    /**
     * Return SQL query for database items object list gathering
     * @param string $language
     * @param string $where
     * @param integer $limit
     * @param integer $count
     * @param mixed $order
     * @param string $sens
     */
    public function get_objectList_allDatabaseItemsSQLQuery($language, $where='', $limit=-1, $count=-1, $order='id', $sens='') {
        /* build sql query */
        $sql = 'select *';
        $sql .= ' from '. $this->_libSQLTable.' as m, '.$this->_libSQLLocaleTable.' as l';
        $sql .= ' where m.id=l.objectid';
        $sql .= ' and l.language="'.$language.'"';

        /* add where conditions to sql query  */
        if ($where != '') {
            $sql .= ' and('. $this->check_SQLCondition($where).')';
        }

        /* add order to sql query */
        if (is_string($order)) {
            $order = array($order=>$sens);
        }

        if (is_array($order)) {
            /* add multi order to sql query */
            $osql = array();
            foreach($order as $o => $s) {
                if ($o == 'special') {
                    $osql[] = $s;
                } elseif (in_array(strtolower($s), array ('', 'asc', 'desc'))) {
                    if ($o=='id' or in_array($o, $this->_libItemTypes['db']))
                        $osql[] = 'm.'.$o.' '.$s;
                    elseif (in_array($o, $this->_libItemTypes['dbl']))
                        $osql[] = 'l.'.$o.' '.$s;
                }
            }
            if (count($osql) > 0)
                $sql .= ' order by '.implode(', ', $osql);
        }

        /* add limit to sql query */
        if ($limit >=0 and $count > 0) {
            $sql .= ' limit '.$limit.', '.$count;
        } else if ($limit > 0) {
            $sql .= ' limit '.$limit;
        } else if ($count > 0) {
            $sql .= ' limit '.$count;
        }
        return $sql;
    }

    /*********************** TEXT ITEMS I/O **********************/

    /**
     * Load text files path
     * @param string $language
     * @return boolean success
     */
    public function get_textItems($language=null) {
        foreach ($this->_libItemTypes['text'] as $text) {
        $this->_libItems[$text]->get($this->id, $language);
        }
        return true;
    }

    /**
     * Save text items
     * @return boolean success
     */
    public function save_textItems() {
        foreach ($this->_libItemTypes['text'] as $text) {
            $this->_libItems[$text]->save($this->id, $this->_libName);
        }
        return true;
    }

    /**
     * Delete text items
     * @return boolean success
     */
    public function delete_textItems() {
        foreach ($this->_libItemTypes['text'] as $text) {
            $this->_libItems[$text]->delete($this->id);
        }
        return true;
    }

    /**
     * Reset text items.
     * @return boolean success
     */
    public function reset_textItems() {
        foreach ($this->_libItemTypes['text'] as $text) {
            $this->_libItems[$text]->reset();
        }
        return true;
    }

    /**
     * Install text items folders.
     * @return boolean success
     */
    public function install_textItems() {
        foreach ($this->_libItemTypes['text'] as $text) {
            $this->_libItems[$text]->install();
        }
        return true;
    }

    /*********************** FILE ITEMS I/O *********************/

    /*
     * Load files url.
     * @param string $language
     * @return boolean success
     */
    public function get_fileItems($language=null){
        foreach ($this->_libItemTypes['file'] as $file) {
            $this->_libItems[$file]->get($this->id, $language);
        }
        return true;
    }

    /*
     * Save file items.
     * @return boolean success
     */
    public function save_fileItems() {
        foreach ($this->_libItemTypes['file'] as $file) {
            $this->_libItems[$file]->save($this->id);
        }
        return true;
    }

    /*
     * Delete file items.
     * @return boolean success
     */
    public function delete_fileItems() {
        foreach ($this->_libItemTypes['file'] as $file) {
            $this->_libItems[$file]->delete($this->id);
        }
        return true;
    }

    /*
     * Reset file items.
     * @return boolean success
     */
    public function reset_fileItems() {
        foreach ($this->_libItemTypes['file'] as $file) {
            $this->_libItems[$file]->reset();
        }
        return true;
    }

    /*
     * Install file items folders.
     * @return boolean success
     */
    public function install_fileItems() {
        foreach ($this->_libItemTypes['file'] as $file) {
            $this->_libItems[$file]->install();
        }
        return true;
    }

    /*********************** TEMP ITEMS I/O *********************/

    /*
     * Load temp items.
     * @return boolean success
     */
    public function get_tempItems() {
        foreach ($this->_libItemTypes['temp'] as $temp) {
            $this->_libItems[$temp]->get();
        }
        return true;
    }

    /*********************** DATA I/O ****************************/

    /**
     * Load each item value from an array
     * @param array $data
     * @param array $match
     * @param boolean $onlyAvailable
     * @return void
     */
    public function get_fromArray($data, $match=null, $onlyAvailable=false) {
        if ($match == null) {
            foreach ($this->_libItems as $name => &$item) {
                if ($onlyAvailable == false or isset($data[$name]))
                    $item->get_fromArray($data);
            }
            return;
        }

        foreach ($match as $n)
            if ($onlyAvailable == false or isset($data[$name]))
                $this->_libItems[$n]->get_fromArray($data);
    }

    /**
     * Export vars to be easily usable.
     * @return void
     */
    public function get_fromItems() {
        $vars = array();
        foreach ($this->_libItems as $item) {
            $vars = array_merge($vars, $item->get_exportedValue());
        }
        $this->vars = $vars;
    }

    /**
     * Check content data validity (to be overwritten).
     * @return boolean result
     */
    public function check_data() {
        return true;
    }

    /*********************** SESSION I/O *************************/

    /**
     * Load object data from session.
     * @param string $name
     * @param boolean $onlyAvailable
     * @return void
     */
    public function load_fromSession($name='ObjectData', $onlyAvailable=false) {
        global $camyks;

        $this->get_fromArray($camyks->get_sessionValue($name, array()), null, $onlyAvailable);
    }

    /**
     * Save object data in session.
     * @param string $name
     * @return void
     */
    public function save_toSession($name='ObjectData') {
        global $camyks;

        $camyks->set_sessionValue($name, $this->vars);
    }

    /**
     * Delete object from session.
     * @param string $name
     * @return void
     */
    public function delete_fromSession($name='ObjectData') {
        global $camyks;

        $camyks->set_sessionValue($name, array());
    }

    /* shortcut to parent methods */

    /**
     * Return complete file url.
     * @param string $file
     * @param boolean $full
     * @param string $default
     * @return string
     */
    public function get_fileURL($file, $full=true, $default='') {
        return $this->_libParent->get_fileURL($file, $full, $default);
    }

    /**
     * Load a file.
     * @param string $file
     * @return void
     */
    public function load_file($file) {
        return $this->_libParent->load_file($file);
    }

    /**
     * Return plugin var file.
     * @param string $file
     * @param boolean $full
     * @param string $default
     * @return string
     */
    public function get_varFileURL($file, $full=true, $default='') {
        return $this->_libParent->get_varFileURL($file, $full, $default);
    }

    /**
     * Return file from var plugin folder.
     * @param string $file
     * @return string
     */
    public function load_varFile($file) {
        return $this->_libParent->load_varFile($file);
    }

    /**
     * Return localised string.
     * @param string $str
     * @param mixed $args
     * @return string
     */
    public function get_translation($str, $args=null) {
        return $this->_libParent->get_translation($str, $args);
    }

    /*********************** TOOL METHODS ************************/

    /**
     * Build SQL condition.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $query = array();
        foreach($params as $item=>$value) {
            if (isset($this->_libItemTypes['db'][$item])) {
                $this->_libItemTypes['db'][$item]->value = $value;
                $query[] = $item . '='. $this->_libItems[$item]->get_databaseValue();
            }
        }
        return implode(' AND ', $query);
    }

    /**
     * Replace id reference in test string for joined SQL query.
     * @param string $where
     * @param boolean $localeOnly
     * @return string
     */
    private function check_SQLCondition($where, $localeOnly=false){
        if ($localeOnly)
            return preg_replace('#\bid\b#', 'l.objectid', $where);
        return preg_replace('#\bid\b#', 'm.id', $where);
    }

    /******************** LIST & COUNT METHODS **********************/

    /**
     * Return object list using the most optimised sub method.
     * @param mixed $language
     * @param string $where
     * @param integer $limit
     * @param integer $count
     * @param string $order
     * @param string $sens
     * @return array
     */
    public function get_objectList($language=false, $where='', $limit=-1, $count=-1, $order='id', $sens='') {
        global $camyks;

        if ($language === false) {
            return $this->get_quickObjectList ($where, $limit, $count, $order, $sens);
        } else if ($language === true and count($this->_libItemTypes['dbl']) == 0) {
            return $this->get_unlocalisedObjectList ($where, $limit, $count, $order, $sens);
        } else if ($language === true and count($camyks->get_confValue('editing_languages')) > 1) {
            return $this->get_completeObjectList($where, $limit, $count, $order, $sens);
        } else {
            if ($language === true) {
                /* set language to the only language available */
                $languages = $camyks->get_confValue('editing_languages');
                $language = $languages[0];
            }
            return $this->get_localisedObjectList($language, $where, $limit, $count, $order, $sens);
        }
    }

    /**
     * Return object id list.
     * @param mixed $language
     * @param string $where
     * @param string $orderBy
     * @param string $orderWay
     * @return array
     */
    public function get_objectIdList($language=false, $where='', $orderBy='', $orderWay='asc') {
        global $camyks;

        /* init list */
        $ids = array();

        /* build sql query */
        $sql = 'select id';
        $sql .= ' from '.$this->_libSQLTable.' as m';
        if ($where != '' and $language !== false and $language != '')
            $sql .= ', '.$this->_libSQLLocaleTable.' as l';
        if ($where != '')
            $sql .= ' where '.$where;

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get data from database */
            while ($data = $this->get_DBQueryDataLine())
                $ids[] = $data['id'];
        }

        /* add sorting condition */
        if ($orderBy != '')
            $sql .= ' order by '.$orderBy.' '.$orderWay;

        /* return result */
        return $ids;
    }

    /**
     * Return items id:element list.
     * @param string $element
     * @param string $where
     * @param string $language
     * @param string $orderBy
     * @param string $orderWay
     * @return array
     */
    public function get_nameList($element='name', $where='', $language='', $orderBy='', $orderWay='asc') {
        global $camyks;

        /* initialise items list */
        $items = array();

        /* check element name */
        if ($element == '') {
            $element = 'name';
        }

        /* check if element exists in main information items */
        if (in_array($element, $this->_libItemTypes['db'])) {
            /* build sql query */
            $sql = 'select id, '.$element;
            $sql .= ' from '.$this->_libSQLTable;

            /* add where conditions to sql query  */
            if ($where != '') {
                $sql .= ' where '. $where;
            }

            /* add sorting condition */
            if ($orderBy != '')
                $sql .= ' order by '.$orderBy.' '.$orderWay;

            /* execute sql query */
            if ($this->execute_DBQuery($sql, __LINE__)) {
                /* get data from database */
                while ($data = $this->get_DBQueryDataLine()) {
                    $this->_libItems[$element]->get_fromArray($data);
                    $items[$data['id']] = $this->_libItems[$element]->value;
                }
            }

        /* check if element exists in localised information items */
        } else if (in_array($element, $this->_libItemTypes['dbl'])) {
            /* check language value */
            if ($language == '')
                $language = $camyks->current_language;

            /* build sql query */
            $sql = 'select objectid, language, '.$element;
            $sql .= ' from '.$this->_libSQLTable.' as m, '.$this->_libSQLLocaleTable.' as l';
            $sql .= ' where language="'.$language.'"';
            $sql .= ' and m.id = l.objectid';

            /* add where conditions to sql query  */
            if ($where != '') {
                $sql .= ' and '.$this->check_SQLCondition($where, true);
            }

            /* add sorting condition */
            if ($orderBy != '') {
                if ($orderBy == 'id') $orderBy = 'm.id';
                    $sql .= ' order by '.$orderBy.' '.$orderWay;
            }

            /* execute sql query */
            if ($this->execute_DBQuery($sql, __LINE__)) {
                /* get data from database */
                while ($data = $this->get_DBQueryDataLine()) {
                    $this->_libItems[$element]->get_fromArray($data);
                    $items[$data['objectid']] = $this->_libItems[$element]->value[$language];
                }
            }
        }
        return $items;
    }

    /**
     * Return object count.
     * @param string $where
     * @param mixed $language
     * @return integer
     */
    public function get_objectCount($where='', $language=false) {
        global $camyks;

        /* build sql query */
        $sql = 'select count(m.id) as cnt';
        $sql .= ' from '.$this->_libSQLTable.' as m';

        /* check language */
        if (count($this->_libItemTypes['dbl']) > 0 and $language !== false) {
            $sql .= ', '. $this->_libSQLLocaleTable.' as l';
            $l = 'l.language="'.$language.'" and m.id = l.objectid';
            $where = $this->check_SQLCondition($where);
            if ($where == '')
                $where = $l;
            else
                $where .= ' and '.$l;
        }

        /* add where conditions to sql query  */
        if ($where != '') {
            $sql .= ' where '. $where;
        }

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get data from database */
            if ($data = $this->get_DBQueryDataLine()) {
                return $data['cnt'];
            }
        }
        return 0;
    }

    /**
     * get_objectList sub methods : return database items only
     * @param string $where
     * @param integer $limit
     * @param integer $count
     * @param mixed $order
     * @param string $sens
     * @return array
     */
    private function get_quickObjectList($where='', $limit=-1, $count=-1, $order='id', $sens='') {
        global $camyks;
        $items = array();

        /* build sql query */
        $sql = $this->get_objectList_databaseItemsSQLQuery($where, $limit, $count, $order, $sens);

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get data from database */
            while ($data = $this->get_DBQueryDataLine()) {
                $item = $this->get_newObject($data['id']);
                $item->get_fromArray($data, $this->_libItemTypes['db']);
                $item->get_textItems();
                $item->get_fileItems();
                $item->get_tempItems();
                $item->get_fromItems();
                $items[$data['id']] = $item;
            }
        }
        return $items;
    }

    /**
     * get_objectList sub methods : return complete items : unlocalised items only
     * @param string $where
     * @param integer $limit
     * @param integer $count
     * @param mixed $order
     * @param string $sens
     * @return array
     */
    private function get_unlocalisedObjectList($where='', $limit=-1, $count=-1, $order='id', $sens='') {
        global $camyks;
        $items = array();

        /* build sql query */
        $sql = $this->get_objectList_databaseItemsSQLQuery($where, $limit, $count, $order, $sens);

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get data from database */
            while ($data = $this->get_DBQueryDataLine()) {
                $item = $this->get_newObject($data['id']);
                $item->get_fromArray($data, $this->_libItemTypes['db']);
                $item->get_textItems();
                $item->get_fileItems();
                $item->get_tempItems();
                $item->get_fromItems();
                $items[$data['id']] = $item;
            }
        }
        return $items;
    }

    /**
     * get_objectList sub methods : return complete objects
     * @param string $where
     * @param integer $limit
     * @param integer $count
     * @param mixed $order
     * @param string $sens
     * @return array
     */
    private function get_completeObjectList($where='', $limit=-1, $count=-1, $order='id', $sens='') {
        global $camyks;

        $items = array();
        $ids = array();

        /* build sql query */
        $sql = $this->get_objectList_databaseItemsSQLQuery($where, $limit, $count, $order, $sens);

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get data from database */
            while ($data = $this->get_DBQueryDataLine()) {
                $item = $this->get_newObject($data['id']);
                $ids[] = $data['id'];
                $item->get_fromArray($data, $this->_libItemTypes['db']);
                if ($item->get_textItems()
                        and $item->get_fileItems()
                        and $item->get_tempItems()) {
                    $items[$data['id']] = $item;
                }
            }
        }

        /* no item in list */
        if (count($ids) == 0) {
            return $items;
        }

        /* get localised datas */
        if (count($this->_libItemTypes['dbl']) > 0) {
            /* build sql query */
            $sql = $this->get_objectList_databaseLocalisedItemsSQLQuery($ids);
            /* execute sql query */
            if ($this->execute_DBQuery($sql, __LINE__)) {
                /* get data from database */
                while ($data = $this->get_DBQueryDataLine()) {
                    $items[$data['objectid']]->get_fromArray($data, $this->_libItemTypes['dbl']);
                    $items[$data['objectid']]->get_fromItems();
                }
            }
        }
        return $items;
    }

    /**
     * get_objectList sub methods : return single language objects
     * @param mixed $language
     * @param string $where
     * @param integer $limit
     * @param integer $count
     * @param mixed $order
     * @param string $sens
     * @return array
     */
    private function get_localisedObjectList ($language=null, $where='', $limit=-1, $count=-1, $order='id', $sens='') {
        global $camyks;
        $items = array();

        /* check language value */
        if (!isset ($language))
            return $items;

        if (count($this->_libItemTypes['dbl']) == 0) {
            /* no localised database item : get database items only */
            $sql = $this->get_objectList_databaseItemsSQLQuery($where, $limit, $count, $order, $sens);
            $match = $this->_libItemTypes['db'];
            $objectid ='id';
        } else {
            /* localised database item : get all database items */
            $sql = $this->get_objectList_allDatabaseItemsSQLQuery($language, $where, $limit, $count, $order, $sens);
            $match = array_merge($this->_libItemTypes['db'], $this->_libItemTypes['dbl']);
            $objectid = 'objectid';
        }

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get data from database */
            while ($data = $this->get_DBQueryDataLine()) {
                $item = $this->get_newObject($data[$objectid]);
                $item->get_fromArray($data, $match);
                if ($item->get_textItems($language)
                        and $item->get_fileItems($language)
                        and $item->get_tempItems()) {
                    $item->get_fromItems();
                    $items[$data[$objectid]] = $item;
                }
            }
        }
        return $items;
    }

    /**
     * Return unique item values list.
     * @param string $element
     * @param string $where
     * @param boolean $structured
     * @return array
     */
    public function get_uniqueItemList ($element='name', $where='', $structured=false) {
        global $camyks;

        /* initialise items list */
        $items = array();

        /* check element name */
        if ($element == '') {
            $element = 'name';
        }

        /* check if element exists in main information items */
        if (in_array($element, $this->_libItemTypes['db'])) {
            /* build sql query */
            $sql = 'select '.$element;
            $sql .= ' from '.$this->_libSQLTable.' as m';

            /* add where conditions to sql query  */
            if ($where != '') {
                $sql .= ' where '. $where;
            }

            /* add group condition */
            $sql .= ' group by '.$element;

            /* add sorting condition */
            $sql .= ' order by '.$element;

            /* execute sql query */
            if ($this->execute_DBQuery($sql, __LINE__)) {
                /* get data from database */
                while ($data = $this->get_DBQueryDataLine()) {
                    if ($structured)
                        $items[$data[$element]] = $data[$element];
                    else
                        $items[] = $data[$element];
                }
            }

        /* check if element exists in localised information items */
        } else if (in_array($element, $this->_libItemTypes['dbl'])) {

            /* build sql query */
            $sql = 'select '.$element;
            $sql .= ' from '.$this->_libSQLLocaleTable.' as l';
            $sql .= ' where language="'.$camyks->current_language.'"';

            /* add where conditions to sql query  */
            if ($where != '') {
                $sql .= ' and '.$this->check_SQLCondition($where);
            }

            /* add group condition */
            $sql .= ' group by '.$element;

            /* add sorting condition */
            $sql .= ' order by '.$element;

            /* execute sql query */
            if ($this->execute_DBQuery($sql, __LINE__)) {
                /* get data from database */
                while ($data = $this->get_DBQueryDataLine()) {
                    if ($structured)
                        $items[$data[$element]] = $data[$element];
                    else
                        $items[] = $data[$element];
                }
            }
        }
        return $items;
    }

    /* shortcuts to database methods */

    /**
     * Execute database query.
     * @param string $sql
     * @param integer $line
     * @param integer $file
      * @param string $resName
     */
    public function execute_DBQuery($sql='', $line=-1, $file='', $resName=null) {
        global $camyks;
        if ($line == -1) $line = __LINE__;
        if ($file == '') $file = $this->_libParentFile;
        return $this->_libDBConnector->execute_query($sql, $resName) or $camyks->log_sqlerror($this, $sql, $file, $line);
    }

    /**
     * Return id generated by last query.
     * @param string $resName
     * @return integer
     */
    public function get_DBQueryGeneratedId($resName=null) {
        return $this->_libDBConnector->get_queryGeneratedId($resName);
    }

    /**
     * Return next query data line.
     * @param string $resName
     * @return integer
     */
    public function get_DBQueryDataLine($resName=null) {
        return $this->_libDBConnector->get_queryDataLine($resName);
    }

    /**
     * Return next query data line with numeric index.
     * @param string $resName
     * @return integer
     */
    public function get_DBQueryNumDataLine($resName=null) {
        return $this->_libDBConnector->get_queryNumDataLine($resName);
    }

    /**
     * Return latest query error.
     * @param string $resName
     * @return string
     */
    public function get_DBQueryError($resName=null) {
        return $this->_libDBConnector->get_queryError($resName);
    }

    /**
     * Return latest query affected rows.
     * @param string $resName
     * @return integer
     */
    public function get_DBQueryAffectedRows($resName=null) {
        return $this->_libDBConnector->get_queryAffectedRows($resName);
    }

    /**
     * Return espaced string.
     * @param string $string
     * @return string
     */
    public function escape_string($string) {
        return $this->_libDBConnector->escape_string($string);
    }

    /**
     * Return latest query affected rows.
     * @return integer
     */
    public function get_DBInsertExtra() {
        return $this->_libDBConnector->get_insertExtra();
    }

    /**
     * Create a table in database.
     * @param string $name
     * @param array $fields
     * @param string $charset
     * @return boolean success
     */
    public function create_DBTable($name, $fields, $charset='utf8') {
        return $this->_libDBConnector->create_table($name, $fields, $charset);
    }
}
?>
