<?php
/**
 * @brief Alias to PluginConfig to keep retro-compatibility with old websites.
 * @details Engine / Object Library
 * @file engine/lib/object/ModuleConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Oct 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Remove this library once all ModuleConfig object have been updated to PluginConfig.
 */

/**
 * ModuleConfig class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
abstract class ModuleConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $module
     */
    public function ModuleConfig($name, &$module) {
        parent::__construct($name, $module);
    }
}
?>