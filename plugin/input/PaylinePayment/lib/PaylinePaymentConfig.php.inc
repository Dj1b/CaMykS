<?php
/**
 * @brief PaylinePayment input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2026
 * @date Modification: Apr 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PaylinePaymentConfig PluginConfig class.
 */
final class PaylinePaymentConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Running mode */
        $this->add_newItem('runningMode', 'string', 'HOMOLOGATION');

        /* Payline API keys */
        $this->add_newItem('merchantId', 'string', '');
        $this->add_newItem('contractNumber', 'string', '');

        $this->add_newItem('homologation_accessKey', 'string', '');
        $this->add_newItem('production_accessKey', 'string', '');

        /* generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific tool methods */

    /**
     * Return running mode value list.
     * @return array
     */
    public function get_modeList() {
        return array(
            'HOMOLOGATION'  => $this->get_translation('runningmode_homologation'),
            'PRODUCTION'    => $this->get_translation('runningmode_production'),
        );
    }

    /**
     * Return running mode value title.
     * @return string
     */
    public function get_modeTitle() {
        $l = $this->get_modeList();
        return isset($l[$this->vars['runningMode']]) ? $l[$this->vars['runningMode']] : '';
    }

    /**
     * Return access key related to current running mode.
     * @return string
     */
    public function get_accessKey() {
        return ($this->vars['runningMode'] === 'PRODUCTION' ? $this->vars['production_accessKey'] : $this->vars['homologation_accessKey']);
    }
}
?>
