<?php
/**
 * @brief YavinPayment input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: May 2026
 * @date Modification: May 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * YavinPaymentConfig PluginConfig class.
 */
final class YavinPaymentConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Running attributes */
        $this->add_newItem('runningMode', 'string', 'test');

        /* Keys attributes */
        $this->add_newItem('testAPIKey', 'string', '');
        $this->add_newItem('productionAPIKey', 'string', '');

        /* Settings attributes */
        $this->add_newItem('settingAllowTitres', 'boolean', 0);
        $this->add_newItem('settingAdminEmail', 'string', '');

        /* Vendor attributes */
        $this->add_newItem('vendorBrandName', 'string', '');
        $this->add_newItem('vendorSoftwareName', 'string', '');
        $this->add_newItem('vendorSoftwareVersion', 'string', '');


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
        return isset($l[$this->vars['runningMode']]) ? $l[$this->vars['runningMode']] : '';
    }
}
?>
