<?php
/**
 * @brief MoneticoPaiement input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Sep 2020
 * @date Modification: Jul 2025
 * @copyright 2020 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MoneticoPaiementConfig PluginConfig class.
 */
final class MoneticoPaiementConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Running mode */
        $this->add_newItem('operation_mode', 'string', 'test');
        $this->add_newItem('company_code', 'string', '');
        $this->add_newItem('country_code', 'string', 'FR');

        /* Monetico keys */
        $this->add_newItem('tpeId_test', 'string', '');
        $this->add_newItem('bankKey_test', 'string', '');

        $this->add_newItem('tpeId_live', 'string', '');
        $this->add_newItem('bankKey_live', 'string', '');

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
            'test'	=> $this->get_translation('mode_test'),
            'live'	=> $this->get_translation('mode_live'),
        );
    }

    /**
     * Return ctx mode value title.
     * @return string
     */
    public function get_modeTitle() {
        $l = $this->get_modeList();
        return $l[$this->vars['operation_mode']];
    }
}
?>
