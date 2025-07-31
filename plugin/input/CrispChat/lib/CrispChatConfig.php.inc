<?php
/**
 * @brief CrispChat input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.2
 * @date Creation: Jul 2020
 * @date Modification: Jul 2025
 * @copyright 2020 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CrispChatConfig PluginConfig class.
 */
final class CrispChatConfig extends PluginConfig {

    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Crisp chat params */
        $this->add_newItem('websiteId', 'string', '');

        /* generic initialisation */
        parent::init_config();
    }
}
?>
