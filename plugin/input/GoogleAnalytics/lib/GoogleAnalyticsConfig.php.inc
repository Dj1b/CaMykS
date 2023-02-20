<?php
/**
 * @brief GoogleAnalytics Input, configuration object.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2018
 * @date Modification: Feb 2023
 * @copyright 2018 - 2023 CaMykS Team
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

        /* google params */
        $this->add_newItem('trackingId', 'string', '');
        $this->add_newItem('trackingMode', 'integer', 0);
        $this->add_newItem('trackingParams', 'string', '');

        /* internal params */
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
     * @return string
     */
    public function get_trackingModeTitle() {
        $l = $this->get_trackingModeList();
        return $l[$this->vars['trackingMode']];
    }
}
?>
