<?php
/**
 * @brief Content_GenericHTMLContent module, item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2008
 * @date Modification: May 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericHTMLContentItem class.
 */
final class Content_GenericHTMLContentItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        /* Content attribute */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('content', 'text', 'content','', '', '',    true);
    }

    /* Override ModuleLibrary methods */

    /**
     * Check content data.
     * @return boolean result
     */
    public function check_data() {
        /* Check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'content');
        return true;
    }

    /* Specific methods */

    /**
     * Write content
     * @return void
     */
    public function write_content() {
        if (file_exists($this->vars['content']))
            include ($this->vars['content']);
    }
}
?>
