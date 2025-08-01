<?php
/**
 * @brief Content_GenericQuickMessage module, content item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Nov 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericQuickMessageItem class.
 */
final class Content_GenericQuickMessageItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('listid', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('ndate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('author', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('email', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('title', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('message', 'db', 'text', 'text', '', '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean succes
     */
    public function check_data() {
        global $camyks;

        /* Check listid */
        if (!($this->_libItems['listid']->value > 0))
            return false;

        /* Check if author is empty */
        $this->_libItems['author']->value = trim($this->_libItems['author']->value);
        if ($this->_libItems['author']->value == '') {
            return false;
        }

        /* Check if title is empty */
        $this->_libItems['title']->value = trim($this->_libItems['title']->value);
        if ($this->_libItems['title']->value == '') {
            return false;
        }

        /* Check if content is empty */
        $this->_libItems['message']->value = trim($this->_libItems['message']->value);
        if ($this->_libItems['message']->value == '') {
            return false;
        }

        if ($this->id == 0) {
            /* Set date */
            $this->_libItems['ndate']->initialise();

            /* set automatic status */
            $list = $this->_libParent->get_listObject($this->_libItems['listid']->value);
            if ($list->vars['validation'] == 0) {
                $this->_libItems['status']->value = 2;
            } else if ($list->vars['validation'] == 1) {
                $this->_libItems['status']->value = 1;
                if ($list->vars['notification'] == 1 and $this->count_waitingMessages() == 0) {
                    $camyks->log_information($this, 'New "Quick Messages" waiting for approval into "'.$list->vars['name'].'" message list.');
                }
            }
        }
        return true;
    }

    /* mark: Specific methods */

    /**
     * Count waiting messages.
     * @return integer
     */
    public function count_waitingMessages() {
        return $this->get_objectCount('listid='.$this->_libItems['listid']. 'and status=1');
    }

    /**
     * Return available status list.
     * @return array
     */
    public function get_statusValueList() {
        return array(
            0 => $this->get_translation('itemstatusvalue0'),
            1 => $this->get_translation('itemstatusvalue1'),
            2 => $this->get_translation('itemstatusvalue2'),
        );
    }
}
?>
