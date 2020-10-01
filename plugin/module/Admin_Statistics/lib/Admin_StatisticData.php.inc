<?php
/**
 * @brief Admin_Statistics Module data library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_StatisticData class.
 */
final class Admin_StatisticData extends ModuleLibrary {
    /**
     * Clas constructor
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Define items */
        $this->add_newItem('statid', 'db', 'int', 'bigint', '', 0);
        $this->add_newItem('statcount', 'db', 'int', 'bigint', '', 1);
        $this->add_newItem('statdate', 'db', 'date', 'bigint', '', time());
        $this->add_newItem('statdatemonth', 'db', 'date', 'bigint', '', 0);
        $this->add_newItem('statdateyear', 'db', 'date', 'bigint', '', 0);
        $this->add_newItem('main', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('data1', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('data2', 'db', 'text', 'varchar', 64, '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data values.
     * @return boolean
     */
    public function check_data() {
        if ($this->id == 0) {
            $this->_libItems['statdatemonth']->value = date_getThisMonthValue();
            $this->_libItems['statdateyear']->value = date_getThisYearValue();
        }
        return true;
    }

    /* Specific public methods */

    /**
     * Save single statistic.
     * @return boolean
     */
    public function update_singleStatistic() {
        return $this->save();
    }

    /**
     * Save mixed statistic.
     * @return boolean
     */
    public function update_mixedStatistic() {
        /* Update date value */
        $this->set_daydate();

        /* Build sql query */
        $sql = 'select id, statcount, statdate, statdatemonth, statdateyear';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where statid='.$this->_libItems['statid']->value;
        $sql .= ' and statdate='.$this->_libItems['statdate']->value;
        $sql .= ' and main="'.addSlashes($this->_libItems['main']->value).'"';
        $sql .= ' and data1="'.addSlashes($this->_libItems['data1']->value).'"';
        $sql .= ' and data2="'.addSlashes($this->_libItems['data2']->value).'"';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            if ($data = $this->get_DBQueryDataLine()) {
                $this->id = $data['id'];
                $this->_libItems['statcount']->value = $data['statcount']+1;
                $this->_libItems['statdatemonth']->value = $data['statdatemonth'];
                $this->_libItems['statdateyear']->value = $data['statdateyear'];
            }
            /* Save object */
            return $this->save();
        }
        return false;
    }

    /**
     * Save total statistic.
     * @return boolean
     */
    public function update_totalStatistic() {
        /* Build sql query */
        $sql = 'select id, statcount, statdate';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where statid='.$this->_libItems['statid']->value;
        $sql .= ' and main="'.addSlashes($this->_libItems['main']->value).'"';
        $sql .= ' and data1="'.addSlashes($this->_libItems['data1']->value).'"';
        $sql .= ' and data2="'.addSlashes($this->_libItems['data2']->value).'"';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            if ($data = $this->get_DBQueryDataLine()) {
                $this->id = $data['id'];
                $this->_libItems['statcount']->value = $data['statcount']+1;
                $this->_libItems['statdate']->value = $data['statdate'];
                $this->_libItems['statdatemonth']->value = $data['statdatemonth'];
                $this->_libItems['statdateyear']->value = $data['statdateyear'];
            }
            /* Save object */
            return $this->save();
        }
        return false;
    }

    /**
     * Return statistics.
     * @param integer $statId
     * @param array $params
     * @return array
     */
    public function get_statistics($statId, $params=array()) {

        /* Define default params */
        $dParams = array('scale'=>'day', 'main'=>-1, 'date_from'=>-1, 'date_to'=>-1, 'duration'=>-1);

        /* merge params */
        $params = array_merge($dParams, $params);

        /* Check scale value */
        if (!in_array($params['scale'], array('day', 'month', 'year', 'total')))
            $params['scale'] = 'day';

        /* Build where statement */
        $s = array();

        /* Check statId */
        $s[] = 'statid = '.$statId;

        /* Check main value */
        if ($params['main'] > -1)
            $s[] = 'main = '. $params['main'];

        /* Check dates */
        if ($params['date_from'] > -1) {
            $s[] = 'statdate >= '.$params['date_from'];
            if ($params['date_to'] > -1)
                $s[] = 'statdate < '.$params['date_to'];
            elseif ($params['duration'] > -1) {
                switch ($params['scale']) {
                case 'day' : $v = mktime(0, 0, 0, 1, $params['duration'], 1970); break;
                case 'month' : $v = mktime(0, 0, 0, $params['duration'], 1, 1970); break;
                case 'year': $v = mktime(0, 0, 0, 1, 1, 1970 + $params['duration']); break;
                default : $v = 0;
                }
                $s[] = 'statdate < '.($params['date_from']+$v);
            }
        } elseif ($params['duration'] > -1) {
            switch ($params['scale']) {
                case 'day' : $v = mktime(0, 0, 0, 1, $params['duration'], 1970); break;
                case 'month' : $v = mktime(0, 0, 0, $params['duration'], 1, 1970); break;
                case 'year': $v = mktime(0, 0, 0, 1, 1, 1970 + $params['duration']); break;
                default : $v = 0;
            }
            $s[] = 'statdate >='.(time()-$v);
        }

        /* Compile params */
        $s = implode(' and ', $s);

        /* Load data */
        switch ($params['scale']) {
            case 'day': return $this->get_statisticsByDayValue($s);
            case 'month': return $this->get_statisticsByMonthValue($s);
            case 'year': return $this->get_statisticsByYearValue($s);
            case 'total': return $this->get_statisticsTotalValue($s);
        }
        return array();
    }

    /**
     * Return total value for a stat.
     * @param string $where
     * @return integer
     */
    public function get_statisticsTotalValue($where='') {

        /* Build sql query */
        $sql = 'select sum(statcount) as cnt';
        $sql .= ' from '.$this->_libSQLTable;
        if ($where != '')
            $sql .= ' where '. $where;

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__))
            if ($data = $this->get_DBQueryDataLine())
                return ($data['cnt'] > 0 ? $data['cnt'] : 0);
        return 0;
    }

    /**
     * Return statistic value by day.
     * @param string $where
     * @return integer
     */
    public function get_statisticsByDayValue($where='') {
        return $this->get_statisticsByDateValue($where, 'statdate');
    }


    /**
     * Return statistic value by month.
     * @param string $where
     * @return integer
     */
    public function get_statisticsByMonthValue($where='') {
        return $this->get_statisticsByDateValue($where, 'statdatemonth');
    }

    /**
     * Return statistic value by year.
     * @param string $where
     * @return integer
     */
    public function get_statisticsByYearValue($where='') {
        return $this->get_statisticsByDateValue($where, 'statdateyear');
    }

    /**
     * Return statistic value by date.
     * @param string $where
     * @param string $object
     * @return integer
     */
    public function get_statisticsByDateValue($where='', $object='statdate') {
        $values = array();
        $values['max'] = 0;
        $values['values'] = array();

        /* Build sql query */
        $sql = 'select '.$object.', sum(statcount) as cnt';
        $sql .= ' from '.$this->_libSQLTable;
        if ($where != '')
            $sql .= ' where '. $where;
        $sql .= ' group by '.$object;
        $sql .= ' order by statdate asc';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            while ($data = $this->get_DBQueryDataLine()) {
                if ($data['cnt']>$values['max'])
                $values['max'] = $data['cnt'];
                $values['values'][$data[$object]] = $data['cnt'];
            }
        }
        return $values;
    }

    /**
     * Return subitems total values.
     * @param string $where
     * @param integer $limit
     * @return void
     */
    public function get_mixedStatisticList($where, $limit=0) {
        $stats = array();

        /* Build sql query */
        $sql = 'select main, sum(statcount) as cnt';
        $sql .= ' from '.$this->_libSQLTable;
        if ($where != '')
            $sql .= ' where '. $where;
        $sql .= ' group by main';
        $sql .= ' order by cnt desc';
        if ($limit > 0)
            $sql .= ' limit '. $limit;

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine()) {
                $stats[$data['main']] = $data['cnt'];
            }
        return $stats;
    }

    /* Specific private methods */

    /**
     * Set date to day date.
     * @return void
     */
    private function set_daydate() {
        $v = $this->_libItems['statdate']->value;
        $this->_libItems['statdate']->value = mktime(0, 0, 0, date('m', $v), date('d', $v), date('Y', $v));
    }
}
?>
