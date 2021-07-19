<?php
/**
 * @brief Content_GenericRandomText module, content item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GenericRandomTextItem class.
 */
final class GenericRandomTextItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('listid', 'db', 'int', 'bigint', '', 0);
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('content', 'db', 'text', 'text', '', '');
        $this->add_newItem('weight', 'db', 'int', 'tinyint unsigned', '', 1);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object values.
     * @return boolean success
     */
    public function check_data() {
        global $camyks;

        /* Check name */
        if ($this->_libItems['name']->value == '')
            $this->_libItems['name']->value = 'randomtextitem'.$this->id;

        /* Check weight */
        if (!($this->_libItems['weight']->value >= 0))
            $this->_libItems['weight']->value = 1;

        return true;
    }

    /**
     * Delete object from database.
     * @return mixed
     */
    public function delete() {
        global $camyks;

        /* Build sql query */
        $sql = 'delete from '.$this->_libSQLTable.' where id='.$this->id.' and listid='.$this->_libItems['listid']->value.';';

        /* Return result of execute sql query */
        return $this->execute_DBQuery($sql, __LINE__);
    }
}
?>
