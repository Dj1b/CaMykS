<?php
/**
 * @brief ScelliusPayment input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Aug 2021
 * @date Modification: Jul 2025
 * @copyright 2021 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ScelliusPaymentConfig PluginConfig class.
 */
final class ScelliusPaymentConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Running mode */
        $this->add_newItem('ctx_mode', 'string', 'TEST');

        /* Scellius keys */
        $this->add_newItem('bankKey_test', 'string', '');
        $this->add_newItem('bankKey_live', 'string', '');

        /* Scellius config */
        $this->add_newItem('site_id', 'string', '');
        $this->add_newItem('hash_mode', 'string', 'SHA-1');

        /* generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific tool methods */

    /**
     * Return ctx mode value list.
     * @return array
     */
    public function get_modeList() {
        return array(
            'TEST'          => $this->get_translation('mode_test'),
            'PRODUCTION'    => $this->get_translation('mode_production'),
        );
    }

    /**
     * Return ctx mode value title.
     * @return string
     */
    public function get_modeTitle() {
        $l = $this->get_modeList();
        return $l[$this->vars['ctx_mode']];
    }

    /**
     * Return hash mode value list.
     * @return array
     */
    public function get_hashModeList() {
        return array(
            'SHA-1'         => 'SHA-1',
            'HMAC-SHA-256'  => 'HMAC-SHA-256',
        );
    }

    /**
     * Return hash mode value title.
     * @return string
     */
    public function get_hashModeTitle() {
        $l = $this->get_hashModeList();
        return $l[$this->vars['hash_mode']];
    }
}
?>
