<?php
/*
 * @brief Admin_SiteReport module, type library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Apr 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SiteReportType class.
 */
final class Admin_SiteReportType extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attribute */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('title', 'db', 'etext', 'varchar', 64, '', true);

        /* Generic initialisation */
        $this->init_library();
    }
}
?>
