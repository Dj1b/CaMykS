<?php
/**
 * @brief Content_GenericRandomText module, content list library.
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
 * GenericRandomTextList class.
 */
final class GenericRandomTextList extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('sessionkeep', 'db', 'int', 'tinyint', '', 0);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object values.
     * @return boolean result
     */
    public function check_data() {
        /* Check name */
        if ($this->_libItems['name']->value == '')
            $this->_libItems['name']->value = 'genericrandomtextlist'.$this->id;

        /* Return success */
        return true;
    }

    /* Specific tool methods */

    /**
     * Load item list.
     * @return void
     */
    public function get_itemlist() {
        $this->vars['items'] = $this->_libParent->gitem->get_objectList(false, 'listid='.$this->id);
    }
}
?>
