<?php
/**
 * @brief Content_GoogleMapsViewer module, content library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jul 2008
 * @date Modification: Jul 2025
 * @copyright 2008 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GoogleMapsViewerItem class.
 */
final class Content_GoogleMapsViewerItem extends ModuleLibrary {
    /*
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');

        /* Localized attributes */
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
        $this->add_newItem('description', 'db', 'text', 'text', '', '', true);

        /* Layout attributes */
        $this->add_newItem('layout', 'db', 'text', 'varchar', 16, '');

        /* Google maps attributes */
        $this->add_newItem('map_baseurl', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('map_width', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newItem('map_height', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newItem('map_zoom', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('map_code', 'db', 'text', 'varchar', 64, '');

        /* Google maps link attributes */
        $this->add_newItem('link_enabled', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('link_class', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('link_color', 'db', 'text', 'varchar', 6, '000000');
        $this->add_newItem('link_size', 'db', 'int', 'tinyint unsigned', '', 11);
        $this->add_newItem('link_bold', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('link_italic', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('link_underline', 'db', 'int', 'tinyint unsigned', '', 0);

        /* Generic initialisation */
        $this->init_library();
    }
}
?>
