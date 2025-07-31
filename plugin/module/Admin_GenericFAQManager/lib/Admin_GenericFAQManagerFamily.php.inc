<?php
/**
 * @brief Admin_GenericFAQManager module, family library.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Feb 2020
 * @date Modification: Jul 2025
 * @copyright 2020 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Class Admin_GenericFAQManagerFamily.
 */
final class Admin_GenericFAQManagerFamily extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'text', 'varchar', 64, '', true);
        $this->add_newItem('sortPosition', 'db', 'int', 'int unsigned', '', 0);

        /* Temp items */
        $this->add_newItem('questionList', 'temp', 'array', '', '', array());

        /* generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary method */

    /**
     * Check object data
     * @return boolean success
     */
    public function check_data() {
        /* Check sortPosition value */
        if ($this->id == 0) {
            $this->_libItems['sortPosition']->value = $this->get_newPosition();
        } else {
            $o = $this->get_newObject($this->id);
            $o->get();
            $o->get_fromItems();
            if ($o->vars['family'] == $this->_libItems['family']->value)
                $this->_libItems['sortPosition']->value = $o->vars['sortPosition'];
            else
                $this->_libItems['sortPosition']->value = $this->get_newPosition();
        }

        /* Return success */
        return true;
    }

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();

        if (isset($params['status']) and $params['status']!='' and $params['status'] > -1)
            $search[] = 'status='.$params['status'];

        return implode(' and ', $search);
    }

    /* Mark: Specific tool methods */

    /**
     * Return single object status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('familystatus_disabled'),
            1 => $this->get_translation('familystatus_enabled'),
        );
    }

    /**
     * Return multi object status list.
     * @param array $params
     * @return array
     */
    public function get_multiStatusList($params) {
        /* Merge params */
        $params = array_merge(array('addAll'=>false), $params);

        /* Build list */
        $list = array();
        if ($params['addAll'])
            $list['-1'] = $this->get_translation('families_all');
        $list['0'] = $this->get_translation('familiesstatus_disabled');
        $list['1'] = $this->get_translation('familiesstatus_enabled');

        /* Return list */
        return $list;
    }

    /**
     * Return object list
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;

        /* default params list */
        $dParams = array('status'=>-1, 'language'=>$camyks->current_language, 'limit'=>-1, 'count'=>-1, 'order'=>'sortPosition', 'orderway'=>'');

        /* merge params */
        $params = array_merge($dParams, $params);

        /* build where statement */
        $where = $this->build_whereStatement($params);

        /* return list */
        return $this->get_objectList($params['language'], $where, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /**
     * Return object title list.
     * @param array $params
     * @return array
     */
    public function get_titleList($params=array()) {
        global $camyks;

        $dParams = array('addAll'=>false, 'status'=>-1);
        $params = array_merge($dParams, $params);

        $list = array();
        if ($params['addAll'])
            $list['-1'] = $this->get_translation('families_all');

        return $list + $this->get_nameList('title');
    }

    /**
     * Return article count with given params
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;
        $p = array('status'=>-1);
        $params = array_merge($p, $params);
        $where = $this->build_whereStatement($params);

        return $this->get_objectCount($where);
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    public function build_whereStatement($params=array()) {
        $w = array();

        /* Check status */
        if ($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* Return result */
        return implode(' and ', $w);
    }

    /**
     * Return object new position.
     * @return integer
     */
    private function get_newPosition() {
        /* Build sql */
        $sql = 'select sortPosition';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' order by sortPosition desc limit 1';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__, __FILE__))
            if ($data = $this->get_DBQueryDataLine())
                return $data['sortPosition']+1;
        return 0;
    }

    /**
     * Check is not first.
     * @return boolean result
     */
    public function is_notFirst() {
        return $this->vars['sortPosition'] > 0;
    }

    /**
     * Check is not last.
     * @return boolean result
     */
    public function is_notLast() {
        $count = $this->_libParent->get_familyListCount();
        if ($count === false)
            return false;
        return $this->vars['sortPosition'] < $count-1;
    }

    /**
     * Update page position to upper.
     * @return boolean success
     */
    public function update_moveUp() {
        return $this->update_movePosition(-1);
    }

    /**
     * Update page position to lower.
     * @return boolean success
     */
    public function update_moveDown() {
        return $this->update_movePosition(1);
    }

    /**
     * Update page position.
     * @param integer $pos
     * @return boolean success
     */
    public function update_movePosition($pos) {
        global $camyks;

        /* get all parent pages */
        $sql = 'select id, sortPosition';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' order by sortPosition';
        if (!$this->execute_DBQuery($sql, __LINE__, __FILE__))
            return false;

        $items = array();
        $position = -1;
        while ($data = $this->get_DBQueryDataLine()) {
            if ($data['id'] == $this->id)
                $position = count($items);
            $items[] = $data;
        }

        /* check new position value */
        if ($position == -1 or ($position+$pos<0) or $position+$pos>=count($items))
            return false;

        /* update position */
        $temp = $items[$position];
        $items[$position] = $items[$position+$pos];
        $items[$position+$pos] = $temp;

        /* update all pages which the position is not correct */
        foreach ($items as $index => $item) {
            if ($index != $item['sortPosition']) {
                $sql = 'update '.$this->_libSQLTable;
                $sql .= ' set sortPosition='.$index;
                $sql .= ' where id='.$item['id'];
                if (!($this->execute_DBQuery($sql, __LINE__, __FILE__)))
                    return false;
            }
        }
        return true;
    }
}
?>
