<?php
/**
 * @brief Admin_GenericDirectoryManager Module contact library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericDirectoryManagerContact class.
 */
final class Admin_GenericDirectoryManagerContact extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('category', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newItem('title', 'db', 'text', 'varchar', 6, '');
        $this->add_newItem('firstname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('lastname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('company', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('phone', 'db', 'text', 'varchar', 24, '');
        $this->add_newItem('mobile', 'db', 'text', 'varchar', 24, '');
        $this->add_newItem('fax', 'db', 'text', 'varchar', 24, '');
        $this->add_newItem('address1', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('address2', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('address3', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('address4', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('zipcode', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('city', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('state', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('country', 'db', 'text', 'varchar', 4, '');

        $this->add_newItem('website', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('email', 'db', 'text', 'varchar', 255, '');

        $this->add_newItem('description', 'db', 'text', 'text', '', '', true);

        $this->add_newItem('facebook', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('twitter', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('linkedin', 'db', 'text', 'varchar', 255, '');

        /* Perform generic initialisation */
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

    /* Specific tool methods */

    /**
     * Return document count by categories.
     * @param array $categories
     * @return array
     */
    public function count_byCategories($categories=null) {
        global $camyks;

        /* Initialise result */
        $list = array();

        /* Check categories */
        if (is_array($categories) and count($categories) == 0)
            return $list;

        /* Build SQL query */
        $sql = 'select category, count(id) as cnt from '.$this->_libSQLTable;
        if (is_array($categories) and count($categories)>0)
            $sql .= ' where category in ('.implode(',', $categories).')';
        $sql .= ' group by category';

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__))
            if ($data = $this->get_DBQueryDataLine())
                $list[$data['category']] = $data['cnt'];

        /* Send results */
        return $list;
    }

    /**
     * Return contacts status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if ($full)
            $list['-1'] = $this->get_translation('contactsstatus_all');
        $list['0'] = $this->get_translation('contactsstatus_disabled');
        $list['1'] = $this->get_translation('contactsstatus_enabled');
        return $list;
    }

    /**
     * Return single contact status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('contactstatus_disabled'),
            1 => $this->get_translation('contactstatus_enabled'),
        );
    }

    /**
     * Return contact list with given params.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;

        /* Build default params */
        $dParams = array('category'=>0, 'status'=>-1, 'limit'=>-1, 'count'=>-1, 'categories'=>'');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Return list */
        return $this->get_objectList($camyks->current_language, $where, $params['limit'], $params['count'], array('lastname'=>'asc', 'firstname'=>'asc'), '');
    }

    /**
     * Return contact count with given params.
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;

        /* Build default params */
        $dParams = array('category'=>0, 'status'=>-1, 'categories'=>'');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Return count */
        return $this->get_objectCount($this->build_whereStatement($params));
    }

    /**
     * Build where statement from params
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* Check status */
        if ($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* Check category */
        if ($params['category'] > 0)
            $w[] = 'category = '.$params['category'];

        /* Check categories */
        if ($params['categories'] != '') {
            if (is_string($params['categories']))
                $params['categories'] = explode(',', $params['categories']);
            if (count($params['categories']) == 0)
                return 'false';
            if (count($params['categories']) == 1)
                $w[] = 'category = '.$params['categories'][0];
            else
                $w[] = 'category in ('.implode(',',$params['categories']).')';
        }
        return implode(' and ', $w);
    }

    /**
     * Return contact name name display for admin list.
     * @return string
     */
    public function get_nameListDisplay() {
        return $this->vars['firstname'].' '.$this->vars['lastname'];
    }
}
?>
