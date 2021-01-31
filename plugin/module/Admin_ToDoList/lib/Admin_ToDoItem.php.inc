<?php
/**
 * @brief Admin_ToDoList Module task library.
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
 * Admin_ToDoItem class.
 */
final class Admin_ToDoItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('from_user', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('to_user', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('creation_date', 'db', 'date', 'bigint', '', time());
        $this->add_newItem('limit_date', 'db', 'date', 'bigint', '', 0);
        $this->add_newItem('title', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('content', 'db', 'text', 'text', '', '');
        $this->add_newItem('sticked', 'db', 'text', 'text', '', '');
        $this->add_newItem('closed', 'db', 'int', 'tinyint', '', 0);

        /* Temporary attributes */
        $this->add_newItem('users', 'temp', 'array', '', '', array());
        $this->add_newItem('comments', 'temp', 'array', '', '', array());

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Load object.
     * @return boolean success
     */
    public function get($language=true) {
        global $camyks;
        /* update from user default value */
        $this->_libItems['from_user']->default = $camyks->adminUser->login;
        /* generic get */
        parent::get();
        /* specific get */
        $this->get_specificValues();
        $this->get_fromItems();
        return true;
    }

    /**
     * Delete object.
     * @return boolean success
     */
    public function delete_fromDatabase() {
        $c = new Admin_ToDoComment(0, $this->_libParent);
        if ($c->delete_selectedItemsFromDatabase(array('todo' => $this->id))) {
            return parent::delete_fromDatabase();
        }
        return false;
    }

    /* Specific tool methods */

    /**
     * Load specific values for this object.
     * @return void
     */
    public function get_specificValues() {
        /* get all user list */
        $this->_libItems['users']->value = AdminUser::static_getList();
        if ($this->id > 0) {
            /* get comment list */
            $c = new Admin_ToDoComment(0, $this->_libParent);
            $this->_libItems['comments']->value = $c->get_objectlist(false, 'todo='.$this->id, -1, -1, 'creation_date', 'desc');
        }
    }
}
?>
