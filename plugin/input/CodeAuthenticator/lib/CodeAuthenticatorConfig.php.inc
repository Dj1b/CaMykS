<?php
/**
 * @brief CodeAuthenticator Input, configuration object library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CodeAuthenticatorConfig PluginConfig class.
 */
final class CodeAuthenticatorConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Code related params */
        $this->add_newItem('code_length', 'integer', 6);

        /* Secret related params */
        $this->add_newItem('secret_length', 'integer', 16);

        /* generic initialisation */
        parent::init_config();
    }

    /* Tool methods */

    /**
     * Return available secret length list.
     * @return array
     */
    public function get_secretLengthList() {
        return array(
            16 => 16,
            32 => 32,
            64 => 64,
            128 => 128,
        );
    }
}
?>
