<?php
/**
 * @brief Content_GooglePoIMapViewer module, content library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GooglePoIMapViewerItem class.
 */
final class Content_GooglePoIMapViewerItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Main attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('categories', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('category_select', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('country_select', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('content', 'db', 'text', 'text', '', '', true);
        $this->add_newItem('default_zoom', 'db', 'int', 'tinyint unsigned', '', 1);

        /* Geo attributes */
        $this->add_newItem('geo_status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('geo_icon', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('geo_zoom', 'db', 'int', 'tinyint unsigned', '', 1);

        /* Temporary attributes */
        $this->add_newItem('category_cnt', 'temp', 'int', '', '', 0);
        $this->add_newItem('categories_', 'temp', 'array', '', '', array());

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* Check name */
        $this->_libItems['name']->check_value('symbolic', 'map');

        /* Check categories */
        $categories = array();
        for ($i=0; $i< $this->_libItems['category_cnt']->value; $i++) {
            if (isset($_REQUEST['category'.$i]))
                $categories[] = $_REQUEST['category'.$i];
        }
        $this->_libItems['categories']->value = implode(',', $categories);

        /* Return result */
        return true;
    }

    /**
     * Load library data from items.
     * @return void
     */
    public function get_fromItems() {
        /* ModuleLibrary generic method */
        parent::get_fromItems();

        /* Decompile categories value */
        if ($this->vars['categories'] == '')
            $this->vars['categories_'] = array();
        else
            $this->vars['categories_'] = explode(',', $this->vars['categories']);
    }
}
?>
