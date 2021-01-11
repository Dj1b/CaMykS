<?php
/**
 * @brief Admin_GenericDirectoryManager Module category library.
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
 * Admin_GenericDirectoryManagerCategory class.
 */
final class Admin_GenericDirectoryManagerCategory extends ModuleLibrary {
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
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);

        /* Temporary items */
        $this->add_newItem('contacts', 'temp', 'int', '', '', 0);

        /* Perform generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        if (isset($params['status']) and $params['status'] > -1)
            return 'status='.$params['status'];
        return '';
    }

    /* Specific methods */

    /**
     * Check is category deletable.
     * @return boolean result
     */
    public function is_deletable() {
        return (isset($this->vars['contacts']) and $this->vars['contacts'] == 0);
    }

    /**
     * Return categories status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if ($full)
            $list['-1'] = $this->get_translation('categoriesstatus_all');
        $list['0'] = $this->get_translation('categoriesstatus_disabled');
        $list['1'] = $this->get_translation('categoriesstatus_enabled');
        return $list;
    }

    /**
     * Return single category status list.
     * @return array
     */
    public function get_statusList() {
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

        /* Build default params */
        $dParams = array('language'=>$camyks->current_language, 'status'=>-1, 'ids'=>-1);

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Initialise where statement */
        $w = array();

        /* Check status */
        if ($params['status'] != -1)
            $w[] = 'status = '. $params['status'];

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

        /* Compile where statement */
        $w = implode(' and ', $w);

        /* Return list */
        return $this->get_nameList('title', $w, $params['language']);
    }
}
?>
