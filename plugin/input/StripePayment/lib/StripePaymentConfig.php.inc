<?php
/**
 * @brief StripePayment input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: May 2020
 * @date Modification: Jul 2025
 * @copyright 2020 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * StripePaymentConfig PluginConfig class.
 */
final class StripePaymentConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Running items */
        $this->add_newItem('runningMode', 'string', '');
        $this->add_newItem('displayTestCard', 'boolean', 0);

        /* Keys items */
        $this->add_newItem('testAPIKey_public', 'string', '');
        $this->add_newItem('testAPIKey_private', 'string', '');
        $this->add_newItem('test_displayTestCard', 'boolean', 0);
        $this->add_newItem('productionAPIKey_public', 'string', '');
        $this->add_newItem('productionAPIKey_private', 'string', '');

        /* generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific tool methods */

    /**
     * Return running mode value list.
     * @return array
     */
    public function get_runningModeList() {
        return array(
            'test'          => $this->get_translation('runningmode_test'),
            'production'    => $this->get_translation('runningmode_production'),
        );
    }

    /**
     * Return running mode value title.
     * @return string
     */
    public function get_runningModeTitle() {
        $l = $this->get_runningModeList();
        return $l[$this->vars['runningMode']];
    }

    /**
     * Return insert mode value list.
     * @return array
     */
    public function get_insertModeList() {
        return array(
            /* 'internal'  => $this->get_translation('insertmode_internal'), */
            'external'  => $this->get_translation('insertmode_external'),
        );
    }

    /**
     * Return insert mode value title.
     * @return string
     */
    public function get_insertModeTitle() {
        $l = $this->get_insertModeList();
        return $l[$this->vars['insertMode']];
    }
}
?>
