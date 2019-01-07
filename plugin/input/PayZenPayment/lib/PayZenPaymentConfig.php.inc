<?php
/**
 * @brief PayZenPayment Input configuration object
 * @details Plugin / Input Library
 * @file plugin/input/PayZenPayment/lib/PayZenPaymentConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2018
 * @date Modification: Dec 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PayZenPaymentConfig PluginConfig class.
 */
final class PayZenPaymentConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Running mode */
        $this->add_newItem('ctx_mode', 'string', 'TEST');

        /* PayZen keys */
        $this->add_newItem('bankKey_test', 'string', '');
        $this->add_newItem('bankKey_live', 'string', '');

        /* PayZen config */
        $this->add_newItem('site_id', 'string', '');
        $this->add_newItem('hash_mode', 'string', 'SHA-1');

        /* generic initialisation */
        parent::init_config();
    }

    /* specific tool methods */

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
