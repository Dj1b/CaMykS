<?php
/**
 * @brief Admin_MyShortcuts module, shortcut library.
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
 * Admin_UserShortcut Module class.
 */
final class Admin_UserShortcut extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content items */
        $this->add_newItem('type', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('user', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('_date', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('url', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean success
     */
    public function check_data() {
        global $camyks;

        $this->_libItems['name']->value = trim($this->_libItems['name']->value);
        if ($this->_libItems['name']->value == '')
            return false;
        if ($this->id == 0) {
            $this->_libItems['_date']->value = time();
            $this->_libItems['user']->value = $camyks->adminUser->login;
        } else {
            $c = $this->get_newObject($this->id);
            $c->get();
            $c->get_fromItems();
            $this->_libItems['_date']->value = $c->vars['_date'];
            $this->_libItems['user']->value = $c->vars['user'];
        }
        return true;
    }

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        global $camyks;

        $search = array();
        $search[] = '(user="'.$camyks->adminUser->login.'")';
        return implode(' and ', $search);
    }
}
?>
