<?php
/**
 * @brief Content_GenericMenu module, menu item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jul 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericMenuItem class.
 */
final class Content_GenericMenuItem extends ModuleLibrary {
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
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('root', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('levels', 'db', 'int', 'tinyint unsigned', '', 0);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * check object data
     * @return boolean result
     */
    public function check_data() {
        /* Check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'menu');

        /* Return success */
        return true;
    }
}
?>
