<?php
/**
 * @brief Admin_ToDoList Module comment library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_ToDoComment class.
 */
final class Admin_ToDoComment extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('todo', 'db', 'int', 'bigint', '', 0);
        $this->add_newItem('from_user', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('creation_date', 'db', 'date', 'bigint', '', time());
        $this->add_newItem('content', 'db', 'etext', 'text', '', '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean success
     */
    public function check_data() {
        if (trim($this->_libItems['content']->value) == '') {
            return false;
        }
        return true;
    }
}
?>
