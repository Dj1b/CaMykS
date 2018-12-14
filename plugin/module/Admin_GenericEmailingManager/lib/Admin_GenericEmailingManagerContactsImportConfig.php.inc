<?php
/**
 * @brief Admin_GenericEmailingManager Module contact input configuration library
 * @details Plugin, Module Library
 * @file plugin/module/Admin_GenericEmailingManager/lib/Admin_GenericEmailingManagerContactsImportConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2013
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericEmailingManagerContactsImportConfig class.
 */
final class Admin_GenericEmailingManagerContactsImportConfig extends ModuleConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* config items */
        $this->add_newItem('import_file', 'string', '');
        $this->add_newItem('cols_params', 'array', array());
        $this->add_newItem('import_current', 'integer', 0);
        $this->add_newItem('first_line', 'integer', 1);
        $this->add_newItem('row_count', 'integer', 0);

        /* generic initialisation */
        parent::init_config();
    }
}
?>
