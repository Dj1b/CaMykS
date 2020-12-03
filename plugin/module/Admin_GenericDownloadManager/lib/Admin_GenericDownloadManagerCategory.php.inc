<?php
/**
 * @brief Admin_GenericDownloadManager Module category library
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2008
 * @date Modification: Dec 2020
 * @copyright 2008 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericDownloadManagerCategory class.
 */
final class Admin_GenericDownloadManagerCategory extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Define object attributes */
        $this->add_newItem('active', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);

        /* Define object temporary attributes */
        $this->add_newItem('docs', 'temp', 'int', '', '', 0);

        /* generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Build SQL condition for lists
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        if (isset($params['active']) and $params['active'] > -1)
            return 'active='.$params['active'];
        return '';
    }

    /* Specific tool methods */

    /**
     * Is category deletable
     * @return boolean result
     */
    public function is_deletable() {
        return (isset($this->vars['docs']) and $this->vars['docs'] == 0);
    }
}
?>
