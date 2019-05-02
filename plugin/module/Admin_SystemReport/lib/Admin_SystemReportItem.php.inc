<?php
/**
 * @brief Admin_SystemReport Module report library
 * @details Plugin, Module Library
 * @file plugin/module/Admin_SystemReport/lib/Admin_SystemReportItem.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Apr 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemReportItem class.
 */
final class Admin_SystemReportItem extends ModuleLibrary {
    /**
     * Class constructor.
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* content items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('type', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('_date', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('url', 'db', 'text', 'varchar', 255, $_SERVER['REQUEST_URI']);
        $this->add_newItem('objecttype', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('objectname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('errordesc1', 'db', 'text', 'text', '', '');
        $this->add_newItem('errordesc2', 'db', 'text', 'text', '', '');
        $this->add_newItem('errorfile', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('errorline', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newitem('answeruser', 'db', 'text', 'varchar', 16, '');
        $this->add_newitem('answercomment', 'db', 'text', 'text', '', '');
        $this->add_newitem('answerdate', 'db', 'date', 'bigint unsigned', '', 0);
    }

    /* Override ModuleLibrary methods */

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();
        if (isset($params['status']) and $params['status']!='' and $params['status'] > -1)
            $search[] = 'status='.(int)$params['status'];
        if (isset($params['type']) and $params['type']!='all')
            $search[] = 'type="'.$this->escape_string($params['type']).'"';
        return implode(' and ', $search);
    }

    /**
     * check if object is checked
     * @return boolean result
     */
    public function is_marked() {
        return ($this->vars['status'] == 0);
    }

    /* specific methods */

    /**
     * Return status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('reportstatus_pending'),
            1 => $this->get_translation('reportstatus_settled'),
        );
    }

    /**
     * Return multi object status list.
     * @param boolean $more
     * @return array
     */
    public function get_multiStatusList($more=false) {
        $list = array();
        if ($more)
            $list['-1'] = $this->get_translation('reports_all');

        return $list + array(
            0 => $this->get_translation('reportstatus_pending'),
            1 => $this->get_translation('reportstatus_settled'),
        );
    }

    /**
     * Build item with given values.
     * @param string $type
     * @param object $object
     * @param string $errordesc1
     * @param string $errordesc2
     * @param string $errorfile
     * @param string $errorline
     * @return void
     */
    public function update_values($type, &$object, $errordesc1='', $errordesc2='', $errorfile='', $errorline=0) {
        $this->get();
        $this->_libItems['type']->value = $type;
        $this->_libItems['objecttype']->value = isset($object->object_type) ? $object->object_type : '';
        $this->_libItems['objectname']->value = get_class($object);
        $this->_libItems['errordesc1']->value = $errordesc1;
        $this->_libItems['errordesc2']->value = $errordesc2;
        $this->_libItems['errorfile']->value = $errorfile;
        $this->_libItems['errorline']->value = $errorline;
    }

    /**
     * Return unique type list.
     * @param boolean $more
     * @return array
     */
    public function get_typelist($more=false) {
        global $camyks;

        $list = array();
        if ($more)
            $list['all'] = $this->get_translation('reports_all');

        /* Build sql query */
        $sql = 'select type';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' group by type';

        /* Execute sql query */
        $camyks->db_conn->execute_query($sql);

        /* Load data from database */
        while ($data = $camyks->db_conn->get_queryDataLine()) {
            $list[$data['type']] = $data['type'];
        }

        /* Return list */
        return $list;
    }

    /**
     * Mark report object as read.
     * @return boolean success
     */
    public function update_withAnswer() {
        global $camyks;

        /* Load comment from header */
        $this->_libItems['answercomment']->get_fromHeader();

        /* Build sql query */
        $sql = 'update '.$this->_libSQLTable;
        $sql .= ' set status=1';
        $sql .= ', answerdate='.time();
        $sql .= ', answeruser="'.$camyks->adminUser->login.'"';
        $sql .= ', answercomment="'.addSlashes($this->_libItems['answercomment']->value).'"';
        $sql .= ' where id='.$this->id;

        /* Return result of sql execution */
        return $camyks->db_conn->execute_query($sql);
    }

    /**
     * Mark given reports as read.
     * @return boolean success
     */
    public function update_reports($list=array()) {
        global $camyks;

        /* Check for empty list */
        if (count($list) == 0)
            return true;

        /* Build sql query */
        $sql = 'update '.$this->_libSQLTable;
        $sql .= ' set status=1';
        $sql .= ', answerdate='.time();
        $sql .= ', answeruser="'.$camyks->adminUser->login.'"';
        $sql .= ' where id in('.implode(',', $list).')';
        $sql .= ' and status=0';

        /* Return result of sql execution */
        return $camyks->db_conn->execute_query($sql);
    }

    /**
     * Delete given reports.
     * @return boolean success
     */
    public function delete_reports($list=array()) {
        global $camyks;

        /* Check for empty list */
        if (count($list) == 0)
            return true;

        /* Build sql query */
        $sql = 'delete from '.$this->_libSQLTable;
        $sql .= ' where id in('.implode(',', $list).')';

        /* Return result of sql execution */
        return $camyks->db_conn->execute_query($sql);
    }

    /**
     * Count reports by type.
     * @param array $params
     * @return array
     */
    public function count_reportsByType($params=array()) {
        /* Build default params */
        $defaultParams = array('status'=>-1, 'ids'=>-1);
        $params = array_merge($defaultParams, $params);

        /* Initialise result list */
        $result = array();

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Build sql query */
        $sql = 'select count(id) as cnt, type';
        $sql .= ' from '.$this->_libSQLTable;
        if ($where != '')
            $sql .= ' where '.$where;
        $sql .= ' group by type';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__))
            /* Load data from database */
            while ($data = $this->get_DBQueryDataLine())
                $result[$data['type']] = $data['cnt'];

        /* Return results */
        return $result;
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* check status */
        if ($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* return result */
        return implode(' and ', $w);
    }
}
?>
