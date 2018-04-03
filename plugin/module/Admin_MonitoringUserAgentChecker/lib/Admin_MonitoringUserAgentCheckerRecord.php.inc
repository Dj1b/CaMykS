<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Dec 2014
 * Last Modif Date  : Mar 2018
 *
 * Admin_MonitoringUserAgentCheckerRecord object for Admin_MonitoringUserAgentChecker Module
 */

final class Admin_MonitoringUserAgentCheckerRecord extends ModuleLibrary {
    /*
     * constructor
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::ModuleLibrary($id, $module);
        /* content items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('user_agent', 'db', 'text', 'text', '', '', '');
        $this->add_newItem('platform_type', 'db', 'text', 'varchar', 16, '', '');
        $this->add_newItem('fvisit', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('lvisit', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('nvisit', 'db', 'int', 'int unsigned', '', 1);

        /* generic initialisation */
        $this->init_library();
    }

    /* overwrite ModuleLibrary method */

    /*
     * build sql condition for lists
     * @param array $params
     * @return string
     * @access public
     */
    public function build_SQLCondition($params) {
        $search = array();

        if (isset($params['status']) and $params['status'] != '-1')
            $search[] = '(status ='.$params['status'].')';

        if (isset($params['user_agent']) and $params['user_agent'] != '')
            $search[] = '(user_agent like "%'.$params['user_agent'].'%")';

        if (isset($params['platform_type']) and $params['platform_type'] != '-1') {
            if ($params['platform_type'] == 'other')
                $search[] = '(platform_type like "%other%") OR (platform_type like "%undefined%")';
            else
                $search[] = '(platform_type like "%'.$params['platform_type'].'%")';
        }

        return implode(' and ', $search);
    }

    /*
     * check object data before saving it
     * @return boolean result
     * @access public
     */
    public function check_data() {
        if ($this->id > 0) {
            /* load previous content */
            $old = $this->get_newObject($this->id);
            $old->get();
            $old->get_fromItems();

            /* copy previous values */
            $this->_libItems['status']->value = $old->vars['status'];
            $this->_libItems['cdate']->value = $old->vars['cdate'];
            $this->_libItems['platform_type']->value = $old->vars['platform_type'];
            $this->_libItems['fvisit']->value = $old->vars['fvisit'];
            $this->_libItems['lvisit']->value = $old->vars['lvisit'];
            $this->_libItems['nvisit']->value = $old->vars['nvisit'];
        }
        return true;
    }

    /* specific tool methods */

    /*
     * return single record platform list
     * @param boolean $all
     * @return array
     * @access public
     */
    public function get_platformTypesList($all=false) {
        /* build default list */
        $list = array(
            'handheld'  => $this->get_translation('platform_type_handheld'),
            'tablet'    => $this->get_translation('platform_type_tablet'),
            'computer'  => $this->get_translation('platform_type_computer'),
            'tvset'     => $this->get_translation('platform_type_tvset'),
            'bot'       => $this->get_translation('platform_type_bot'),
            'tool'      => $this->get_translation('platform_type_tool'),
            'hack'      => $this->get_translation('platform_type_hack'),
            'fake'      => $this->get_translation('platform_type_fake'),
            'other'     => $this->get_translation('platform_type_other'),
            'undefined' => $this->get_translation('platform_type_other'),
        );

        /* check for all value */
        if ($all)
            $list = array('-1' => $this->get_translation('platform_type_all')) + $list;

        /* return list */
        return $list;
    }

    /*
     * return single record status list
     * @return array
     * @access public
     */
    public function get_statusList() {
        return array(
            '-1'    => $this->get_translation('record_all'),
            '0'     => $this->get_translation('recordstatus_notverified'),
            '1'     => $this->get_translation('recordstatus_verified'),
        );
    }

    /*
     * return signe object format list
     * @return array
     * @access public
     */
    public function get_platformFormatList() {
        return array(
            'handheld'  => $this->get_translation('platform_format_handheld'),
            'tablet'    => $this->get_translation('platform_format_tablet'),
            'desktop'   => $this->get_translation('platform_format_desktop'),
        );
    }

    /*
     * get from user agent value
     * @param string $ua
     * @return boolean result
     * @access public
     */
    public function get_fromUserAgent($ua) {
        /* build sql query */
        $sql = 'select *';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where user_agent = "'.addSlashes($ua).'"';

        /* execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get result of sql query */
            if ($data = $this->get_DBQueryDataLine()) {
                $this->id = $data['id'];
                $this->get_fromArray($data, $this->_libItemTypes['db']);
                return true;
            }
        }
        return false;
    }

    /*
     * build where statement from params
     * @param array $params
     * @return string
     * @access private
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* check status */
        if ($params['status'] > -1)
            $w[] = 'status = '.(int)$params['status'].'';

        /* check user agent */
        if ($params['user_agent'] != '')
            $w[] = '(user_agent like "%'.$params['user_agent'].'%")';

        /* check user agent */
        if ($params['platform_type'] != '')
            $w[] = '(platform_type = "'.$params['platform_type'].'")';

        return implode(' and ', $w);
    }

    /*
     * return record count with given params
     * @params array $params
     * @return int
     * @access public
     */
    public function count($params=array()) {
        $p = array('user_agent'=>'', 'platform_type'=>'', 'status'=>-1);
        $params = array_merge($p, $params);
        return $this->get_objectCount($this->build_whereStatement($params));
    }

    /*
     * return record list
     * @param array $params
     * @return array
     * @access public
     */
    public function get_list($params=array()) {
        global $camyks;

        /* default params list */
        $dParams = array('user_agent'=>'', 'platform_type'=>'','status'=>-1, 'limit'=>-1, 'count'=>-1, 'order'=>'lvisit', 'orderway'=>'desc');
        /* merge params */
        $params = array_merge($dParams, $params);
        /* build where statement */
        $w = $this->build_whereStatement($params);
        /* return list */
        return $this->get_objectList(false, $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /*
     * return encoded user agent value
     * @return string
     * @access public
     */
    public function get_adminValue() {
        return string_text2Html($this->vars['user_agent']);
    }

    /* single object update methods */

    /*
     * update record type
     * @return boolean success
     * @access public
     */
    public function update_type() {
        /* load values */
        $this->get_fromItems();

        /* load new type */
        $uaInfos = client_getUAInfos($this->vars['user_agent']);
        $this->_libItems['platform_type']->value = $uaInfos['platform_type'];

        /* save object */
        return $this->update_databaseSpecificItems(array('platform_type'));
    }

    /*
     * mark record as verified
     * @return boolean success
     * @access public
     */
    public function mark_asVerified() {
        /* update status */
        $this->_libItems['status']->value = 1;

        /* save object */
        return $this->update_databaseSpecificItems(array('status'));
    }

    /*
     * update visit count
     * @return boolean success
     * @access public
     */
    public function update_visitCount() {
        /* update visit values */
        $this->_libItems['nvisit']->value ++;
        $this->_libItems['lvisit']->value = time();

        /* save object */
        return $this->update_databaseSpecificItems(array('nvisit', 'lvisit'));
    }
}
?>
