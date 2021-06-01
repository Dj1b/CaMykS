<?php
/**
 * @brief Content_GenericGallery module, item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericGalleryItem class.
 */
final class Content_GenericGalleryItem extends ModuleLibrary {
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
        $this->add_newItem('listid', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('position', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'etext', 'varchar', 128, '', true);
        $this->add_newItem('description', 'db', 'etext', 'text', '', '', true);
        $this->add_newItem('image', 'file', 'image', '', '', '');
        $this->add_newItem('thumb', 'file', 'thumb', '', '', '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* Check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'image');

        /* Check position */
        if ($this->id == 0)
            $this->_libItems['position']->value = $this->get_objectCount('listid='.$this->_libItems['listid']->value);

        /* Return success */
        return true;
    }
}
?>
