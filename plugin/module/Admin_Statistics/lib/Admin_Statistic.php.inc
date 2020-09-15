<?php
/**
 * @brief Admin_Statistics Module statistic library.
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
 * Admin_Statistic class.
 */
final class Admin_Statistic extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param &Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Define items */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('type', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('plugin', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('register_date', 'db', 'date', 'bigint', '', time());

        $this->add_newItem('title', 'temp', 'text', '', '', '');
        $this->add_newItem('plugintitle', 'temp', 'text', '', '', '');
        $this->add_newItem('item', 'temp', 'text', '', '', '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Specific public methods */

    /**
     * Update statistic data.
     * @param string $main
     * @param string $data1
     * @param string $data2
     * @return void
     */
    public function update_statistic($main='', $data1='', $data2='') {
        /* Load data object */
        $data = &$this->_libParent->statdata;
        $data->id = 0;
        $data->get();
        $data->_libItems['statid']->value=$this->id;
        $data->_libItems['main']->value=$main;
        $data->_libItems['data1']->value=$data1;
        $data->_libItems['data2']->value=$data2;

        switch ($this->_libItems['type']->value) {
            case 'single':
                $data->update_singleStatistic();
                break;
            case 'mixed':
            case 'detail':
            case 'dated':
                $data->update_mixedStatistic();
                break;
            case 'total':
                $data->update_totalStatistic();
                break;
        }
    }

    /**
     * Update title value.
     * @return void
     */
    public function get_statisticTitle() {
        global $camyks;
        $this->vars['title'] = $camyks->get_translation('mod_'.$this->vars['plugin'].'_stat_'.$this->vars['name']);
        $this->vars['plugintitle'] = $camyks->get_translation('mod_'.$this->vars['plugin'].'_title');
        $this->vars['item'] = $camyks->get_translation('mod_'.$this->vars['plugin'].'_stat_'.$this->vars['name'].'_main');
    }

    /**
     * Return object id from plugin and name.
     * @param string $plugin
     * @param string $name
     * @return mixed
     */
    public function get_idFromPluginAndName($plugin, $name) {
        /* Build sql query */
        $sql = 'select id from '.$this->_libSQLTable;
        $sql .= ' where plugin="'.$plugin.'" and name="'.$name.'"';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* get result of sql query */
            if ($data = $this->get_DBQueryDataLine()) {
                return $data['id'];
            }
        }
        return false;
    }
}
?>
