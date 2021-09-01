<?php
/**
 * @brief Content_GenericQuickMessage module, list item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericQuickMessageItem class.
 */
final class Content_GenericQuickMessageList extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('validation', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('notification', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('displayed', 'db', 'int', 'tinyint unsigned', '', 8);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Overrude ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* Check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'messagelist');

        /* Return success */
        return true;
    }

    /* Specific tool methods */

    /**
     * Return status values list.
     * @return array
     */
    public function get_statusValueList() {
        return array(
            0 => $this->get_translation('liststatusvalue0'),
            1 => $this->get_translation('liststatusvalue1'),
            2 => $this->get_translation('liststatusvalue2'),
        );
    }

    /**
     * Return validation values list.
     * @return array
     */
    public function get_validationValueList() {
        return array(
            0=>$this->get_translation('listvalidationvalue0'),
            1=>$this->get_translation('listvalidationvalue1'),
        );
    }

    /**
     * Load validated list messages.
     * @return void
     */
    public function get_validatedMessages() {
        $this->vars['messages'] = $this->_libParent->qmitem->get_objectList(false, 'status=2 and listid='.$this->id, 8, -1, 'ndate', 'desc');
    }
}
?>
