<?php
/**
 * @brief ReCaptcha Input configuration object
 * @details Plugin / Input Library
 * @file plugin/input/ReCaptcha/lib/ReCaptchaConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2018
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
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
