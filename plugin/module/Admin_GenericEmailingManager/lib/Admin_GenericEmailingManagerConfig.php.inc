<?php
/**
 * @brief Admin_GenericEmailingManager module, configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jan 2013
 * @date Modification: Jul 2025
 * @copyright 2012 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericEmailingManagerConfig class.
 */
final class Admin_GenericEmailingManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Unsubscribing params */
        $this->add_newItem('unsubscribe_backpage', 'string', '');

        /* Generic initialisation */
        parent::init_config();
    }
}
?>
