<?php
/**
 * @brief Admin_GenericPetitionManager Module petition library
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericPetitionManagerPetition class.
 */
final class Admin_GenericPetitionManagerPetition extends ModuleLibrary {
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
        $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
        $this->add_newItem('description', 'db', 'text', 'text', '', '', true);

        /* Temporary attributes */
        $this->add_newItem('signs', 'temp', 'integer', '', '', '');

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

        return implode(',', $search);
    }

    /* specific tool methods */

    /**
     * Return petitions status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if($full)
            $list['-1'] = $this->get_translation('petitionsstatus_all');
        $list['0'] = $this->get_translation('petitionsstatus_disabled');
        $list['1'] = $this->get_translation('petitionsstatus_opened');
        $list['2'] = $this->get_translation('petitionsstatus_closed');
        return $list;
    }

    /**
     * Return single petition status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('petitionstatus_disabled'),
            1 => $this->get_translation('petitionstatus_opened'),
            2 => $this->get_translation('petitionstatus_closed'),
        );
    }

    /**
     * Return petition list with given params.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;
        $p = array('status'=>-1, 'limit'=>-1, 'count'=>-1, 'order'=>'id', 'orderway'=>'');
        $params = array_merge($p, $params);
        $w = $this->build_whereStatement($params);
        return $this->get_objectList($camyks->current_language, $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /**
     * Return petition title list with given params.
     * @param array $params
     * @return array
     */
    public function get_titleList($params=array()) {
        global $camyks;
        $p = array('status'=>-1);
        $params = array_merge($p, $params);
        $w = $this->build_whereStatement($params);
        return $this->get_nameList('title', $w);
    }

    /**
     * Return petition count with given params.
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;
        $p = array('status'=>-1);
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

        /* Check status */
        if (is_string($params['status']) and $params['status'] != '')
            $w[] = 'status '.$params['status'];
        elseif($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        return implode(' and ', $w);
    }

    /**
     * Load signature count.
     * @return void
     */
    public function get_signCount() {
        $c = $this->_libParent->count_signsByPetitions(array($this->id));
        $this->vars['signs'] = isset($c[$this->id]) ? $c[$this->id] : 0;
    }
}
?>
