<?php
/**
 * @brief Admin_GenericGlossaryManager Module, category library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2010
 * @date Modification: Feb 2020
 * @copyright 2010 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericGlossaryManagerCategory class.
 */
final class Admin_GenericGlossaryManagerCategory extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* content items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);

        /* temp items */
        $this->add_newItem('definitions', 'temp', 'int', '', '', 0);

        /* generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Build SQL condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        if (isset($params['status']) and $params['status'] > -1)
            return 'status = '.$params['status'];
        return '';
    }

    /* Specific methods */

    /**
     * Check category is deletable.
     * @return boolean result
     */
    public function is_deletable() {
        return (isset($this->vars['definitions']) and $this->vars['definitions'] == 0);
    }

    /**
     * Return categories status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if($full)
            $list['-1'] = $this->get_translation('categoriesstatus_all');
        $list['0'] = $this->get_translation('categoriesstatus_disabled');
        $list['1'] = $this->get_translation('categoriesstatus_enabled');
        return $list;
    }

    /**
     * Return single category status list.
     * @return array
     */
    function get_statusList() {
        return array(
            0 => $this->get_translation('categorystatus_disabled'),
            1 => $this->get_translation('categorystatus_enabled'),
        );
    }

    /**
     * Return categories title list.
     * @param array $params
     * @return array
     */
    public function get_titleList($params=array()) {
        global $camyks;

        /* default params */
        $dParams = array('language'=>$camyks->current_language, 'status'=>-1, 'ids'=>-1);

        /* merge params */
        $params = array_merge($dParams, $params);

        /* initialise where statement */
        $w = array();

        /* check status */
        if ($params['status'] != -1)
            $w[] = 'status = '. $params['status'];

        /* check id list */
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

        /* get load list */
        return $this->get_nameList('title', $w, $params['language']);
    }
}
?>
