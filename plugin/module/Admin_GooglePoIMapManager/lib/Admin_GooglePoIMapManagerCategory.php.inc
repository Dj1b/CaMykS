<?php
/**
 * @brief Admin_GooglePoIMapManager module, category library.
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
 * Admin_GooglePoIMapManagerCategory class.
 */
final class Admin_GooglePoIMapManagerCategory extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Main attributes */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);

        /* Temporary attributes */
        $this->add_newItem('points', 'temp', 'integer', '', '', 0);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Specific methods */

    /**
     * Return category status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('categorystatus_inactive'),
            1 => $this->get_translation('categorystatus_active'),
        );
    }

    /**
     * Return category status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if ($full)
            $list['-1'] = $this->get_translation('categoriesstatus_all');
        $list['0'] = $this->get_translation('categoriesstatus_inactive');
        $list['1'] = $this->get_translation('categoriesstatus_active');
        return $list;
    }

    /**
     * Check if category is deletable.
     * @return boolean result
     */
    public function is_deletable() {
        return (isset($this->vars['points']) and $this->vars['points'] == 0);
    }

    /**
     * Return title list.
     * @param array $params
     * @return array
     */
    public function get_titleList($params) {
        /* Define default params */
        $dParams = array('status'=>-1, 'language'=>null, 'ids'=>-1, '_all'=>false);
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $w = array();

        /* Check status */
        if ($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* Check id list */
        if ($params['ids'] != -1) {
            if (is_string($params['ids']))
                $params['ids'] = explode(',', $params['ids']);
            if (count($params['ids']) == 0)
                return array();
            if (count($params['ids']) == 1)
                $w[] = 'id = '.$params['ids'][0];
            else
                $w[] = 'id in ('.implode(',', $params['ids']).')';
        }

        /* compile where statement */
        $w = implode(' and ', $w);

        /* Return object title list */
        $list = $this->get_nameList('title', $w, $params['language']);
        if ($params['_all'] == true)
            return array(0 => $this->get_translation('categoriesstatus_all'))+$list;
        return $list;
    }
}
?>
