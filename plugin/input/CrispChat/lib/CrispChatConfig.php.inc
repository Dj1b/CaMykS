<?php
/**
 * @brief CrispChat Input configuration object
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jul 2020
 * @date Modification: Jul 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CrispChatConfig PluginConfig class.
 */
final class CrispChatConfig extends PluginConfig {

    /*
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
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
