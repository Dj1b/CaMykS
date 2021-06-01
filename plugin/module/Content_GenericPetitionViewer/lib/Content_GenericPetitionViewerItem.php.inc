<?php
/**
 * @brief Content_GenericPetitionViewer module, item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2010
 * @date Modification: May 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericPetitionViewerItem class.
 */
final class Content_GenericPetitionViewerItem extends ModuleLibrary {
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
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('petition', 'db', 'int', 'bigint unsigned', '', 1);
        $this->add_newItem('signcount', 'db', 'int', 'tinyint unsigned', '', 10);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        global $camyks;
        /* Check name */
        $this->_libItems['name']->check_value('symbolic', 'petition');

        /* Return success */
        return true;
    }
}
?>
