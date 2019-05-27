<?php
/**
 * @brief Admin_SystemNotifications Module website library
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SystemNotifications/lib/Admin_SystemNotificationsWebsite.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2017
 * @date Modification: May 2019
 * @copyright 2017 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemNotificationsWebsite class.
 */
final class Admin_SystemNotificationsWebsite extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* admin items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('baseURL', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('pageURL', 'db', 'text', 'varchar', 32, 'request.php');
        $this->add_newItem('login', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('password', 'db', 'text', 'varchar', 32, '');

        /* generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean success
     */
    public function check_data() {
        if ($this->id == 0) {
            $this->_libItems['cdate']->value = time();
        } else {
            $old = $this->get_newObject($this->id);
            $old->get();
            $old->get_fromItems();
            $this->_libItems['cdate']->value = $old->vars['cdate'];
        }
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

    /* Specific properties definition method */

    /**
     * Return status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('websitestatus_disabled'),
            1 => $this->get_translation('websitestatus_enabled'),
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
            $list['-1'] = $this->get_translation('websites_all');
        $list['0'] = $this->get_translation('websitesstatus_disabled');
        $list['1'] = $this->get_translation('websitesstatus_enabled');
        return $list;
    }

    /* specific tool methods */

    /**
     * Return config value.
     * @param mixed $param
     * @return mixed
     */
    private function get_configValue($param=array()) {
        return $this->_libParent->get_configValue($param);
    }

    /* Multi object handling methods */

    /**
     * Return object list.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;

        /* default params list */
        $dParams = array('status'=>-1, 'language'=>$camyks->current_language, 'limit'=>-1, 'count'=>-1, 'order'=>'sortPosition', 'orderway'=>'asc');

        /* merge params */
        $params = array_merge($dParams, $params);

        /* build where statement */
        $w = $this->build_whereStatement($params);

        /* return list */
        return $this->get_objectList($params['language'], $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /**
     * Return object count.
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;

        /* default params list */
        $dParams = array('status'=>-1,);

        /* merge params */
        $params = array_merge($dParams, $params);

        /* build where statement */
        $where = $this->build_whereStatement($params);

        /* return result */
        return $this->get_objectCount($where);
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

    /**
     * Perform notification check.
     * @return array
     */
    public function check_notifications() {
        /* build request */
        $request = array(
            'url' => $this->vars['baseURL'].'/'.$this->vars['pageURL'].'?module='.$this->_libParent->name.'&mode=loadNotifications',
        );

        /* check for post values */
        if ($this->vars['login'] != '') {
            $request['values'] = array('login' => $this->vars['login'], 'password' => $this->vars['password']);
            $request['method'] = 'POST';
        }

        /* execute request */
        return http_getContents($request);
    }
}
?>
