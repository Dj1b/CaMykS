<?php
/**
 * @brief Content_GenericGallery module, list library.
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
 * Content_GenericGalleryList class.
 */
final class Content_GenericGalleryList extends ModuleLibrary {
    /**
     * var array $imagelist
     * @brief Image list.
     */
    public $items = array();

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

        /* Smart Gallery configuration */
        $this->add_newItem('theme', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('thumbCount', 'db', 'int', 'tinyint unsigned', '', 6);
        $this->add_newItem('thumbWidth', 'db', 'int', 'tinyint unsigned', '', 80);
        $this->add_newItem('thumbHeight', 'db', 'int', 'tinyint unsigned', '', 60);
        $this->add_newItem('imageWidth', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newItem('imageHeight', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newItem('imageTitle', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('imageDesc', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('slidingMethod', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('slidingAccel', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('slidingSpeed', 'db', 'int', 'tinyint unsigned', '', 30);
        $this->add_newItem('slidingInterval', 'db', 'int', 'tinyint unsigned', '', 25);

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
        $this->_libItems['name']->check_value('symbolic_name', 'gallery');

        /* Return success */
        return true;
    }

    /* Specific tool methods */

    /**
     * Load items.
     * @param string $lg
     * @return void
     */
    public function get_itemList($lg=false) {
        $this->items = $this->_libParent->imageitem->get_objectList($lg, 'listid='.$this->id);
    }
}
?>
