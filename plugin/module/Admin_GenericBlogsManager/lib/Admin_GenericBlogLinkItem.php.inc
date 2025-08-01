<?php
/**
 * @brief Admin_GenericBlogsManager module, link library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2008
 * @date Modification: Jul 2025
 * @copyright 2008 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericBlogLinkItem class.
 */
final class Admin_GenericBlogLinkItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        /* Define object attributes */
        $this->add_newItem('title', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('link', 'db', 'text', 'varchar', 255, 'http://');
        $this->add_newItem('author', 'db', 'text', 'varchar', 32, '');
        $this->add_newitem('ndate', 'db', 'date', 'bigint unsigned', '', time());

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Initialise object.
     * @return void
     */
    public function initialise() {
        global $camyks;
        /* Generic initialisation */
        parent::initialise();
        /* Specific initialisation */
        $this->_libItems['author']->value = $camyks->adminUser->login;
    }

    /* Mark: Specific tool methods */

    /**
     * Retun link list from given author list.
     * @param array $authors
     * @return array
     */
    public function get_linkListByAuthor($authors) {
        if (count($authors) == 0)
            return $this->get_objectList();
        elseif (count($authors) == 1)
            return $this->get_objectList(false, 'author="'.$authors[0].'"');
        else
            return $this->get_objectList(false, 'author in ("'.implode('", "', $authors).'")');
    }
}
?>
