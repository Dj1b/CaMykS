<?php
/**
 * @brief Admin_GenericDownloadManager Module configuration library
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
 * Admin_GenericDownloadManagerConfig class.
 */
final class Admin_GenericDownloadManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Define object attributes */
        $this->add_newItem('main_stats', 'boolean', false);
        $this->add_newItem('file_size', 'float', 8 );
        $this->add_newItem('link_mode', 'integer', 0);

        /* Generic initialisation */
        parent::init_config();
    }
}
?>
