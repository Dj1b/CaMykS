<?php
/**
 * @brief PayBoxPayment input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jul 2018
 * @date Modification: Jul 2025
 * @copyright 2018 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PayBoxPaymentConfig PluginConfig class.
 */
final class PayBoxPaymentConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* running mode */
        $this->add_newItem('bankMode', 'string', 'test');

        /* paybox keys */
        $this->add_newItem('bankKey_Test', 'string', '');
        $this->add_newItem('bankKey_Live', 'string', '');

        /* paybox config */
        $this->add_newItem('site', 'string', '');
        $this->add_newItem('rang', 'string', '');
        $this->add_newItem('identifiant', 'string', '');

        /* paybox fixed config */
        $this->add_newItem('hash', 'string', 'SHA512');

        /* generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific tool methods */

    /**
     * Return mode value list.
     * @return array
     */
    public function get_modeList() {
        return array(
            'test' => $this->get_translation('mode_test'),
            'live' => $this->get_translation('mode_live'),
        );
    }

    /**
     * Return mode value title.
     * @return string
     */
    public function get_modeTitle() {
        $l = $this->get_modeList();
        return $l[$this->vars['bankMode']];
    }
}
?>
