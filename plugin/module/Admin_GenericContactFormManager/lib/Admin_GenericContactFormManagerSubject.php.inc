<?php
/**
 * @brief Admin_GenericContactFormManager Module, subject library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericContactFormManagerSubject class.
 */
final class Admin_GenericContactFormManagerSubject extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* main items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'text', 'varchar', 48, '', true);

        /* Perform generic initialisation */
        $this->init_library();
    }

    /* Override methods */

    /**
     * Build SQL condition.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $query = array();

        /* check status */
        if (isset($params['status']) and $params['status']!=-1)
            $query[] = 'status = '.$params['status'];

        return implode(' AND ', $query);
    }

    /* Specific data methods */

    /**
     * Return objects status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if ($full)
            $list[-1] = $this->get_translation('subjectsstatus_all');
        $list[0] = $this->get_translation('subjectsstatus_disabled');
        $list[1] = $this->get_translation('subjectsstatus_enabled');
        return $list;
    }

    /**
     * Return object status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('subjectstatus_disabled'),
            1 => $this->get_translation('subjectstatus_enabled'),
        );
    }

    /**
     * Return object status value.
     * @param mixed $status
     * @return string
     */
    public function get_statusValue($status=false) {
        $list = $this->get_statusList();
        if ($status === false)
            $status = $this->vars['status'];
        return $list[$status];
    }

    /**
     * Return object status icon list.
     * @return array
     */
    public function get_statusIconList() {
        $theme = &$this->_libParent->theme;
        return array(
            0 => '<img src="'.$theme->get_pictURL('empty', 12, 'std').'" alt="" />',
            1 => '<img src="'.$theme->get_pictURL('valid', 12, 'std').'" alt="" />');
    }

    /**
     * Return object status icon.
     * @return array
     */
    public function get_statusIcon($status=false) {
        $icons = $this->get_statusIconList();
        if ($status === false)
            return $icons[$this->vars['status']];
        return $icons[$status];
    }

    /**
     * Return subject list with given params.
     * @params array $params
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
     * Return subject count with given params.
     * @params array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;
        $p = array('status'=>-1);
        $params = array_merge($p, $params);
        return $this->get_objectCount($this->build_whereStatement($params));
    }

    /**
     * Build where statement from params
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* check status */
        if (is_string($params['status']) and $params['status'] != '')
            $w[] = 'status '.addslashes($params['status']);
        elseif($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* Return result */
        return implode(' and ', $w);
    }
}
?>
