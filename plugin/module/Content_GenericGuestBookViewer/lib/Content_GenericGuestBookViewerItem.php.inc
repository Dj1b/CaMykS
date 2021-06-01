<?php
/**
 * @brief Content_GenericGuestBookViewer module, item library.
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
 * Content_GenericGuestBookViewerItem class.
 */
final class Content_GenericGuestBookViewerItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attribute */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('formlayout', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('msgcount', 'db', 'int', 'tinyint unsigned', '', 10);
        $this->add_newItem('gpcstyle', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('description', 'db', 'text', 'text', '', '', true);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data
     * @return boolean result
     */
    public function check_data() {
        /* Check name */
        $this->_libItems['name']->check_value('symbolic', 'guestbook');

        /* Return success */
        return true;
    }

    /* Specific data methods */

    /**
     * Return GPC source list.
     * @return array
     */
    public function get_gpcStyleList() {
        global $camyks;

        return array(
            0 => $camyks->get_translation('theme'),
            1 => $this->get_translation('gpc_name'),
        );
    }

    /**
     * Return message form layout value list.
     * @return array
     */
    public function get_formLayoutList() {
        return array(
            0 => $this->get_translation('formlayout_newpage'),
            1 => $this->get_translation('formlayout_popup'),
        );
    }

    /**
     * Return layout list.
     * @return array
     */
    public function get_layoutList() {
        return array('nobox' => $this->get_translation('layout_nobox'));
    }
}
?>
