<?php
/**
 * @brief Admin_GooglePoIMapManager module, point library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Mar 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GooglePoIMapManagerPoint class.
 */
final class Admin_GooglePoIMapManagerPoint extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        global $camyks;

        /* Main attributes */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('category', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('icon', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('address1', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('address2', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('address3', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('country', 'db', 'text', 'varchar', 3, $camyks->get_confValue('site_default_language'));
        $this->add_newItem('latitude', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('longitude', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
        $this->add_newItem('description', 'db', 'text', 'text', '', '', true);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary method */

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();
        if (isset($params['status']) and $params['status']!='' and $params['status'] > -1)
            $search[] = 'status='.$params['status'];
        if (isset($params['category']) and $params['category']!='' and $params['category'] > -1)
            $search[] = 'category='.$params['category'];
        if (isset($params['country']) and $params['country']!='')
            $search[] = 'country="'.$params['country'].'"';
        return implode(' and ', $search);
    }

    /* Mark: Specific tool methods */

    /**
     * Return status.
     * @return boolean result
     */
    public function is_active() {
        return ($this->vars['status']==1);
    }

    /**
     * Return point status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('pointstatus_inactive'),
            1 => $this->get_translation('pointstatus_active'),
        );
    }

    /**
     * Return point status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if ($full)
            $list['-1'] = $this->get_translation('pointsstatus_all');
        $list['0'] = $this->get_translation('pointsstatus_inactive');
        $list['1'] = $this->get_translation('pointsstatus_active');
        return $list;
    }

    /**
     * Return point count by category.
     * @param array $categories
     * @return array
     */
    public function get_pointCountByCategories($categories=null) {
        global $camyks;

        $list = array();

        /* Check types */
        if (is_array($categories) and count($categories) == 0)
            return $list;

        /* Build sql query */
        $sql = 'select category, count(id) as cnt from '.$this->_libSQLTable;
        if (is_array($categories) and count($categories) > 0) {
            $sql .= ' where category in ('.implode(',', $categories).')';
        }
        $sql .= ' group by category';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine())
                $list[$data['category']] = $data['cnt'];

        /* Send results */
        return $list;
    }

    /**
     * Return point list.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        /* Define default params */
        $dParams = array('status'=>-1, 'category'=>-1, 'country'=>'', 'language'=>false, 'order'=>'id', 'orderway'=>'', 'categories'=>'');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Return object list */
        return $this->get_objectList($params['language'], $where, -1, -1, $params['order'], $params['orderway']);
    }

    /**
     * Return points country list.
     * @param array $params
     * @return array
     */
    public function get_countryList($params=array()) {
        /* Define default params */
        $dParams = array('status'=>-1, 'category'=>-1, 'country'=>'', 'structured'=>false);

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Return country list */
        return $this->get_uniqueItemList('country', $s, $params['structured']);
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $s = array();

        /* Check status */
        if ($params['status'] > -1)
            $s[] = 'status='.$params['status'];

        /* Check category */
        if ($params['category'] > -1)
            $s[] = 'category='.$params['category'];

        /* Check categories */
        if ($params['categories'] != '') {
            if (is_string($params['categories']))
                $params['categories'] = explode(',', $params['categories']);
            if (count($params['categories']) == 1)
                $s[] = 'category='.$params['categories'][0];
            else
                $s[] = 'category in ('.implode(', ', $params['categories']).')';
        }

        /* Check country */
        if ($params['country'] != '')
            $s[] = 'country="'.$params['country'].'"';

        /* Return compiled result */
        return implode(' and ', $s);
    }
}
?>
