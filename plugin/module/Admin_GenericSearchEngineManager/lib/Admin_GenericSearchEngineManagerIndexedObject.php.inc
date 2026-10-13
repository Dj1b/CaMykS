<?php
/**
 * @brief Admin_GenericSearchEngineManager module, indexed object library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2026
 * @date Modification: Sep 2026
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
                /*
                print_r($this->_libItems['linkURL']->value);
                print_r($this->vars);
                die();
                */

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
     * @return boolean success
     */
    public function set_asUpdated($linkType, $linkURLs) {
        global $camyks;

        /* Initialise update */
        $update = array('lastIndexDate');
        $this->_libItems['lastIndexDate']->value = time();

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
            'ids'           => -1,
            'module'        => '',
            'moduleType'    => '',
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
                    $w[] = 'id = '.$id;
            else
                $w[] = 'id in ('.implode(',', $params['ids']).')';
        }

        /* Check module */
        if ($params['module'] != '')
            $w[] = 'module = '.addslashes($params['module']);

        /* Check moduleType */
        if ($params['moduleType'] != '')
            $w[] = 'moduleType = '.addslashes($params['moduleType']);

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
}
?>
