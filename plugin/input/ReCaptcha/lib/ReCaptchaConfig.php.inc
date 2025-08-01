<?php
/**
 * @brief ReCaptcha input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jan 2018
 * @date Modification: Jul 2025
 * @copyright 2018 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ReCaptchaConfig PluginConfig class.
 */
final class ReCaptchaConfig extends PluginConfig {

    /*
     * Class constructor.
     * @param string $name
     * @param Module $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        $this->add_newItem('publicKey', 'string', '');
        $this->add_newItem('privateKey', 'string', '');

        /* generic initialisation */
        parent::init_config();
    }
}
?>
