<?php
/**
 * @brief Admin_SecurityTools Module Configuration object
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SecurityTools/lib/Admin_SecurityToolsConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2007
 * @date Modification: Jan 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SecurityToolsConfig PluginConfig class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class Admin_SecurityToolsConfig extends PluginConfig {
    /**
     * Class Constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* object items */
        $this->add_newItem('ipfilter', 'boolean', false);
        $this->add_newItem('urlfilter', 'boolean', false);
        $this->add_newItem('backup', 'boolean', false);
        $this->add_newItem('backup_method', 'string', 'manual');
        $this->add_newItem('backup_compression', 'string', 'tgz');
        $this->add_newItem('backup_nextdate', 'int', 0 );
        $this->add_newItem('backup_type', 'string', 'complete');
        $this->add_newItem('backup_temp', 'string', '');

        /* generic initialisation */
        parent::init_config();
    }
}
?>
