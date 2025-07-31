<?php
/**
 * @brief Admin_SecurityTools module, configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3.1
 * @date Creation: Oct 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SecurityToolsConfig PluginConfig class.
 */
final class Admin_SecurityToolsConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* object items */
        $this->add_newItem('ipfilter', 'boolean', false);
        $this->add_newItem('urlfilter', 'boolean', false);
        $this->add_newItem('uafilter', 'boolean', false);
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
