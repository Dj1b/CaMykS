<?php
/**
 * @brief Admin_Statistics module, configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: May 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_StatisticConfig class.
 */
final class Admin_StatisticConfig extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Define items */
        $this->add_newItem('user', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('object', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('mode', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('value', 'db', 'text', 'varchar', 255, '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Save object
     * @return void
     */
    public function save() {
        /* Load object id */
        $this->get_configId();

        /* Execute saving */
        parent::save();
    }

    /* Mark: Specific public methods */

    /**
     * Return configuration list.
     * @param string $name
     * @param string $mode
     * @return array
     */
    public function get_configs($name, $mode='') {
        global $camyks;

        /* Initialise result */
        $configs = array();

        /* Build sql query */
        $sql = 'select *';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where user="'.$camyks->adminUser->login.'"';
        $sql .= ' and (object="colors"';
        $sql .= ' or (object="'.$name.'"';
        $sql .= ' and mode="'.$mode.'"))';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __FILE__, __LINE__)) {
            while ($data = $this->get_DBQueryDataLine()) {
                $item = $this->get_newObject();
                $item->id = $data['id'];
                $item->get_fromArray($data, $this->_libItemTypes['db']);
                $item->get_fromItems();
                $configs[$data['object']] = $item;
            }
        }

        /* Return result */
        return $configs;
    }

    /* Specific private methods */

    /**
     * Return configuration id.
     * @return void
     */
    private function get_configId() {
        global $camyks;

        /* Build sql query */
        $sql = 'select id ';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where user="'.$this->_libItems['user']->value.'"';
        $sql .= ' and object="'.$this->_libItems['object']->value.'"';
        $sql .= ' and mode="'.$this->_libItems['mode']->value.'"';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __FILE__, __LINE__)) {
            if ($data = $this->get_DBQueryDataLine()) {
                $this->id = $data['id'];
                return;
            }
        }

        /* Set default value */
        $this->id = 0;
    }
}
?>
