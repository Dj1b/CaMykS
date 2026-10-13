<?php
/**
 * @brief GoogleAnalytics input, configuration object.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Sep 2018
 * @date Modification: Oct 2025
 * @copyright 2018 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GoogleAnalyticsConfig PluginConfig class.
 */
final class GoogleAnalyticsConfig extends PluginConfig {

    /**
     * Class constructor.
     * @param string $name
     * @param Input $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Google params */
        $this->add_newItem('trackingId', 'string', '');
        $this->add_newItem('trackingMode', 'integer', 0);
        $this->add_newItem('trackingParams', 'string', '');

        /* Second Google params */
        $this->add_newItem('tracking2Id', 'string', '');
        $this->add_newItem('tracking2Mode', 'integer', 0);
        $this->add_newItem('tracking2Params', 'string', '');

        /* Internal params */
        $this->add_newItem('enableAdminStats', 'boolean', false);

        /* generic initialisation */
        parent::init_config();
    }

    /* Data related methods */

    /**
     * Return tracking mode value list.
     * @return array
     */
    public function get_trackingModeList() {
        return array(
            0 => 'Global site tag',
            1 => 'Google Tag Manager',
        );
    }

    /**
     * Return tracking mode title.
     * @param string $code
     * @return string
     */
    public function get_trackingModeTitle($code='') {
        $l = $this->get_trackingModeList();
        if (isset($l[$this->vars['tracking'.$code.'Mode']]))
            return $l[$this->vars['tracking'.$code.'Mode']];
        return $l[0];
    }
}
?>
