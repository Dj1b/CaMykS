<?php
/**
 * @brief Admin_GenericSearchEngineManager module, indexed object library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.0
 * @date Creation: Sep 2026
 * @date Modification: Oct 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericSearchEngineManagerIndexedObject class.
 */
final class Admin_GenericSearchEngineManagerIndexedObject extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('module', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('moduleObjectType', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('moduleObjectId', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('firstIndexDate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('lastIndexDate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('publicationDate', 'db', 'date', 'bigint unsigned', '', 0);
        $this->add_newItem('expirationDate', 'db', 'date', 'bigint unsigned', '', 0);
        $this->add_newItem('linkType', 'db', 'text', 'varchar', 12, '');
        $this->add_newItem('linkURL', 'db', 'text', 'varchar', 255, '', true);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Action methods */

    /**
     * Load object.
     * @param string $module
     * @param string $moduleObjectType
     * @param string $moduleObjectId
     * @return void
     */
    public function load($module, $moduleObjectType, $moduleObjectId) {
        if (!$this->load_fromInfo($module, $moduleObjectType, $moduleObjectId)) {
            $this->initialise();
            $this->_libItems['module']->value = $module;
            $this->_libItems['moduleObjectType']->value = $moduleObjectType;
            $this->_libItems['moduleObjectId']->value = $moduleObjectId;
            $this->_libItems['firstIndexDate']->value = time();
            $this->_libItems['publicationDate']->value = 0;
            $this->_libItems['expirationDate']->value = 0;
        }
    }

    /**
     * Load object from information.
     * @param string $module
     * @param string $moduleObjectType
     * @param string $moduleObjectId
     * @return void
     */
    public function load_fromInfo($module, $moduleObjectType, $moduleObjectId) {
        /* Build SQL query */
        $sql = 'select * from '.$this->_libSQLTable;
        $sql .= ' where module="'.addslashes($module).'"';
        $sql .= ' and moduleObjectType="'.addslashes($moduleObjectType).'"';
        $sql .= ' and moduleObjectId='.(int)$moduleObjectId;

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__, __FILE__)) {
            if ($data = $this->get_DBQueryDataLine()) {
                $this->id = $data['id'];
                $this->get_fromArray($data);
                $this->get_databaseLocalisedItems();
                $this->get_fromItems();
                return true;
            }
        }

        /* Return failure */
        return false;
    }

    /**
     * Update object with last index date as now.
     * @param string $linkType
     * @param array $linkURLs
     * @param mixed $publicationDate
     * @param integer $expirationDate
     * @return boolean success
     */
    public function set_asUpdated($linkType, $linkURLs, $publicationDate=0, $expirationDate=0) {
        global $camyks;

        /* Normalise dates */
        if (is_array($publicationDate)) {
            $expirationDate = isset($publicationDate['expirationDate']) ? (int)$publicationDate['expirationDate'] : 0;
            $publicationDate = isset($publicationDate['publicationDate']) ? (int)$publicationDate['publicationDate'] : 0;
        } else {
            $publicationDate = (int)$publicationDate;
            $expirationDate = (int)$expirationDate;
        }

        /* Initialise update */
        $update = array('lastIndexDate');
        $this->_libItems['lastIndexDate']->value = time();

        /* Check publication date */
        if ($this->vars['publicationDate'] != $publicationDate) {
            $this->_libItems['publicationDate']->value = $publicationDate;
            $update[] = 'publicationDate';
        }

        /* Check expiration date */
        if ($this->vars['expirationDate'] != $expirationDate) {
            $this->_libItems['expirationDate']->value = $expirationDate;
            $update[] = 'expirationDate';
        }

        /* Check link type */
        if ($this->vars['linkType'] != $linkType) {
            if (!in_array($linkType, array('page', 'anchor', 'file')))
                return false;
            $this->_libItems['linkType']->value = $linkType;
            $update[] = 'linkType';
        }

        /* Check link urls */
        if (!is_array($linkURLs))
            return false;
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            if (!isset($linkURLs[$l]))
                return false;
            if ($update !== true and (!isset($this->vars['linkURL_'.$l]) or $this->vars['linkURL_'.$l] != $linkURLs[$l])) {
                $this->_libItems['linkURL']->value = $linkURLs;
                $update = true;
            }
        }

        /* Update object */
        if ($update === true)
            return $this->save();
        return $this->update_databaseSpecificItems($update);
    }

    /**
     * Delete given objects and their localised data.
     * @param array $objectIds
     * @return boolean success
     */
    public function delete_objects($objectIds=array()) {
        /* Check object ids */
        if (!is_array($objectIds) or count($objectIds) === 0)
            return true;

        /* Sanitise ids */
        $ids = array();
        foreach ($objectIds as $id) {
            if ((int)$id > 0)
                $ids[] = (int)$id;
        }
        if (count($ids) === 0)
            return true;

        /* Delete main table items */
        $sql = 'delete from '.$this->_libSQLTable.' where id in ('.implode(',', $ids).');';
        if (!$this->execute_DBQuery($sql, __LINE__, __FILE__))
            return false;

        /* Delete locale table items */
        $sql = 'delete from '.$this->_libSQLLocaleTable.' where objectid in ('.implode(',', $ids).');';
        return $this->execute_DBQuery($sql, __LINE__, __FILE__);
    }

    /**
     * Return object statistics by module.
     * @return array
     */
    public function get_moduleStatistics() {
        /* Initialise result */
        $result = array();

        /* Build SQL query */
        $sql = 'select module, count(distinct moduleObjectType) as types, count(distinct moduleObjectId) as objects from '.$this->_libSQLTable;
        $sql .= ' group by module;';

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__, __FILE__)) {
            while ($data = $this->get_DBQueryDataLine()) {
                $result[$data['module']] = $data;
            }
        }

        /* Return result */
        return $result;
    }

    /* Mark: Multi object methods */

    /**
     * Return default parameters.
     * @param array
     */
    private function get_defaultParams() {
        return array(
            'ids'               => -1,
            'module'            => '',
            'moduleObjectType'  => '',
        );
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* Check ids */
        if (is_array($params['ids'])) {
            if (count($params['ids']) == 0)
                return false;
            if (count($params['ids']) == 1)
                foreach ($params['ids'] as $id)
                    $w[] = 'id = '.(int)$id;
            else
                $w[] = 'id in ('.implode(',', $params['ids']).')';
        }

        /* Check module */
        if ($params['module'] != '')
            $w[] = 'module = "'.addslashes($params['module']).'"';

        /* Check moduleObjectType */
        if ($params['moduleObjectType'] != '')
            $w[] = 'moduleObjectType = "'.addslashes($params['moduleObjectType']).'"';

        /* Return result */
        return implode(' and ', $w);
    }

    /**
     * Return object list.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;

        /* Build default params list */
        $dParams = array('language'=>$camyks->current_language, 'limit'=>-1, 'count'=>-1, 'order'=>'id', 'orderway'=>'asc');

        /* Merge params */
        $params = array_merge($this->get_defaultParams(), $dParams, $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Return list */
        return $this->get_objectList($params['language'], $where, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /**
     * Return object id list.
     * @param array $params
     * @return array
     */
    public function get_idList($params=array()) {
        /* Merge params */
        $params = array_merge($this->get_defaultParams(), $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);
        if ($where === false)
            return array();

        /* Return id list */
        return $this->get_objectIdList(false, $where);
    }

    /**
     * Return alert count.
     * @params array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;

        /* Merge params */
        $params = array_merge($this->get_defaultParams(), $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Return list */
        return $this->get_objectCount($where);
    }

    /* Mark: Update methods */

    /**
     * Update to version 1.1.
     * @return boolean success
     */
    public function update_toVersion1_1() {
        $sql = 'show columns from `'.$this->_libSQLTable.'` like "publicationDate"';
        if ($this->execute_DBQuery($sql, __LINE__, __FILE__)) {
            if ($this->get_DBQueryDataLine())
                return true;
        }
        $sql = 'alter table `'.$this->_libSQLTable.'` add column publicationDate bigint unsigned default 0 after lastIndexDate;';
        if (!$this->execute_DBQuery($sql, __LINE__, __FILE__))
            return false;
        $sql = 'alter table `'.$this->_libSQLTable.'` add column expirationDate bigint unsigned default 0 after publicationDate;';
        return $this->execute_DBQuery($sql, __LINE__, __FILE__);
    }
}
?>
