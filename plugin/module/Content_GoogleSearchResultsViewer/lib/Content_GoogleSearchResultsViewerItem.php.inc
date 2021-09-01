<?php
/**
 * @brief Content_GoogleSearchResultsViewer module, content library.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GoogleSearchResultsViewerItem class.
 */
final class Content_GoogleSearchResultsViewerItem extends ModuleLibrary {
    /**
     * Constructor
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        /* content */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');

        /* layout content */
        $this->add_newItem('layout', 'db', 'text', 'varchar', 16, '');

        /* google search results description */
        $this->add_newItem('sr_searchdomain', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('sr_width', 'db', 'int', 'int unsigned', '', 0);

        /* generic init */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data
     * @return boolean result
     */
    public function check_data() {
        /* Check name */
        $this->_libItems['name']->check_value('symbolic_name', 'google_search');

        /* Return success */
        return true;
    }
}
?>
