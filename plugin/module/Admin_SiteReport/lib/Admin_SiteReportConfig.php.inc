<?php
/**
 * @brief Admin_SiteReport Module, configuration library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2008
 * @date Modification: May 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SiteReportConfig class.
 */
final class Admin_SiteReportConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* File configuration attributes */
        $this->add_newItem('file_allowed', 'boolean', false);
        $this->add_newItem('file_maxsize', 'int', 128);

        /* Generic initialisation */
        parent::init_config();
    }
}
?>
