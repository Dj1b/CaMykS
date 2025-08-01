<?php
/**
 * @brief Content_GenericSiteMap module, content library.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jul 2008
 * @date Modification: Jul 2025
 * @copyright 2008 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
final class Content_GenericSiteMapItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('columns', 'db', 'int', 'tinyint unsigned', '', 2);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object values.
     * @return boolean result
     */
    public function check_data() {
        /* Check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'sitemap');

        /* Check columns value */
        if (!($this->_libItems['columns']->value > 0))
            $this->_libItems['columns']->value = 1;

        /* Return success */
        return true;
    }
}
?>
