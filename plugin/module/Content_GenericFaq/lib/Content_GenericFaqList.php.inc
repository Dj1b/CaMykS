<?php
/**
 * @brief Content_GenericFaq module, faq list library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Apr 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericFaqList class.
 */
final class Content_GenericFaqList extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('count_list', 'db', 'int', 'tinyint unsigned', '', 10 );
        $this->add_newItem('layout_list', 'db', 'text', 'varchar', 16, '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data value.
     * @return boolean result
     */
    public function check_data() {
        global $camyks;

        /* Check name */
        $this->_libItems['name']->check_value('symbolic', 'faq');

        /* Check item displayed value */
        if (!($this->_libItems['count_list']->value > 0))
            $this->_libItems['count_list']->initialise();

        /* Return is correct */
        return true;
    }
}
?>
