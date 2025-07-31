<?php
/**
 * @brief Content_GenericBlogsViewer module, content item.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2008
 * @date Modification: Jul 2025
 * @copyright 2008 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericBlogsViewerItem class.
 */
final class Content_GenericBlogsViewerItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('list_count', 'db', 'int', 'tinyint unsigned', '', 5);
        $this->add_newItem('list_layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('list_panel', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('item_layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('item_panel', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('panel_insert', 'db', 'etext', 'text', '', '');
        $this->add_newItem('comment_message', 'db', 'etext', 'text', '', '');
        $this->add_newItem('enablerss', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('authors', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('snsp_status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('snsp_items', 'db', 'text', 'text', '', '');
        $this->add_newItem('gpc_status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('gpc_source', 'db', 'int', 'tinyint unsigned', '', 0);

        /* Temporary attributes */
        $this->add_newItem('authors_', 'temp', 'array', '', '', array());

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        global $camyks;

        /* Check name */
        $this->_libItems['name']->check_value('symbolic', 'blog');

        /* Check authors value */
        $authorsCount = isset($_REQUEST['authorsCount']) ? (int)$_REQUEST['authorsCount'] : 0;

        $authors = array();
        for ($i=0; $i< $authorsCount; $i++) {
            if (isset($_REQUEST['author'.$i]))
                $authors[] = $_REQUEST['author'.$i];
        }
        $this->_libItems['authors']->value = implode(',', $authors);

        /* Return success */
        return true;
    }

    /**
     * Load library data.
     * @return void
     */
    public function get_fromItems() {
        /* ModuleLibrary generic method */
        parent::get_fromItems();

        /* Decompile authors value */
        if ($this->vars['authors'] == '')
            $this->vars['authors_'] = array();
        else
            $this->vars['authors_'] = explode(',', $this->vars['authors']);
    }

    /* Mark: Update methods */

    /**
     * Update library to version 1.01.
     * @return boolean success
     */
    public function update_toVersion1_01() {
        global $camyks;

        /* Build sql query */
        $sql = 'alter ignore table '.$this->_libSQLTable;
        $sql .= ' add column snsp_status tinyint unsigned default 0,';
        $sql .= ' add column snsp_items text default "",';
        $sql .= ' add column gpc_status tinyint unsigned default 0,';
        $sql .= ' add column gpc_source tinyint unsigned default 0;';

        /* Execute sql query */
        return $this->execute_DBQuery($sql, __LINE__, __FILE__);
    }
}
?>
