<?php
/**
 * @brief Admin_GenericGlossaryManager Module, definition library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2010
 * @date Modification: Feb 2020
 * @copyright 2010 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericGlossaryManagerDefinition class.
 */
final class Admin_GenericGlossaryManagerDefinition extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* content items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('category', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newItem('word', 'db', 'text', 'varchar', 128, '', true);
        $this->add_newItem('description', 'db', 'text', 'text', '', '', true);
        $this->add_newItem('link', 'db', 'text', 'varchar', '255', '');

        /* generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary method */

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();
        if (isset($params['status']) and $params['status'] > -1)
            $search[] = 'status='.$params['status'];
        if (isset($params['category']) and $params['category'] > 0)
            $search[] = 'category='.$params['category'];
        return implode(',', $search);
    }

    /* specific tool methods */

    /**
     * Return document count by categories.
     * @param array $categories
     * @return array
     */
    public function count_byCategories($categories=null) {
        global $camyks;

        $list = array();
        /* check categories */
        if (is_array($categories) and count($categories) == 0)
            return $list;

        /* build sql query */
        $sql = 'select category, count(id) as cnt from '.$this->_libSQLTable;
        if (is_array($categories) and count($categories)>0)
            $sql .= ' where category in ('.implode(',', $categories).')';
        $sql .= ' group by category';

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__))
            /* get data from database */
            while ($data = $this->get_DBQueryDataLine())
                $list[$data['category']] = $data['cnt'];
        /* send results */
        return $list;
    }

    /**
     * Return definitions status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if($full)
            $list['-1'] = $this->get_translation('definitionsstatus_all');
        $list['0'] = $this->get_translation('definitionsstatus_disabled');
        $list['1'] = $this->get_translation('definitionsstatus_enabled');
        return $list;
    }

    /**
     * Return single definition status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('definitionstatus_disabled'),
            1 => $this->get_translation('definitionstatus_enabled'),
        );
    }

    /**
     * Return definition list with given params.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;
        $p = array('letters'=>'', 'category'=>0, 'status'=>-1, 'limit'=>-1, 'count'=>-1, 'categories'=>'');
        $params = array_merge($p, $params);
        $w = $this->build_whereStatement($params);
        return $this->get_objectList($camyks->current_language, $w, $params['limit'], $params['count'], 'word', 'asc');
    }

    /**
     * Return definition count with given params.
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;
        $p = array('letters'=>'', 'category'=>0, 'status'=>-1, 'categories'=>'');
        $params = array_merge($p, $params);
        return $this->get_objectCount($this->build_whereStatement($params));
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    public function build_whereStatement($params=array()) {
        $w = array();
        /* check status */
        if ($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* check letters */
        if ($params['letters'] != '') {
            if (strlen($params['letters']) == 1)
                $w[] = 'word like "'.$params['letters'].'%"';
            else
                $w[] = 'word REGEXP "^['.$params['letters'].'].*$"';
        }

        /* check category */
        if ($params['category'] > 0)
            $w[] = 'category = '.$params['category'];

        /* check categories */
        if ($params['categories'] != '') {
            if (is_string($params['categories']))
                $params['categories'] = explode(',', $params['categories']);
            if (count($params['categories']) == 0)
                return '0=1';
            if (count($params['categories']) == 1)
                $w[] = 'category = '.$params['categories'][0];
            else
                $w[] = 'category in ('.implode(',',$params['categories']).')';
        }
        return implode(' and ', $w);
    }
}
?>
