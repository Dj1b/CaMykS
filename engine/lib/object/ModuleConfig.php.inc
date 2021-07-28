<?php
/**
 * @brief Alias to PluginConfig to keep retro-compatibility with old websites.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Oct 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Remove this library once all ModuleConfig object have been updated to PluginConfig.
 */

/**
 * ModuleConfig class.
 */
abstract class ModuleConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $module
     * @return void
     */
    public function __construct($name, &$module) {
        parent::__construct($name, $module);
    }

    /**
     * Old style class constructor.
     * @param string $name
     * @param Module $module
     * @return void
     */
    public function ModuleConfig($name, &$module) {
        parent::__construct($name, $module);
    }
}
?>
