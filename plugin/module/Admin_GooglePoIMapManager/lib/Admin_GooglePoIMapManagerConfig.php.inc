<?php
/**
 * @brief Admin_GooglePoIMapManager module, configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GooglePoIMapManagerConfig class.
 */
final class Admin_GooglePoIMapManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Map configuration */
        $this->add_newItem('google_mapapikey', 'string', '');

        /* Generic initialisation */
        parent::init_config();
    }
}
?>
