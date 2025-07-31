<?php
/**
 * @brief SiteMonitoringToolbar input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Nov 2017
 * @date Modification: Jul 2025
 * @copyright 2017 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SiteMonitoringToolbarConfig PluginConfig class.
 */
final class SiteMonitoringToolbarConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        $this->add_newItem('accessRestriction', 'integer', 0);
        $this->add_newItem('buttonLocation', 'string', 'top:right');
        $this->add_newItem('appliedTheme', 'string', 'dark');

        /* generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific tool methods */

    /**
     * Return access restriction value list.
     * @return array
     */
    public function get_accessRestrictionList() {
        return array(
            0 => $this->get_translation('accessrestriction_webmasteronly'),
            1 => $this->get_translation('accessrestriction_adminonly'),
            2 => $this->get_translation('accessrestriction_all'),
        );
    }

    /**
     * Return access restriction value.
     * @return string
     */
    public function get_accessRestrictionValue() {
        $l = $this->get_accessRestrictionList();
        return $l[$this->vars['accessRestriction']];
    }

    /**
     * Return button location value list.
     * @return array
     */
    public function get_buttonLocationList() {
        return array(
            'top:left'                => $this->get_translation('buttonlocation_topleft'),
            'top:right'             => $this->get_translation('buttonlocation_topright'),
            'bottom:left'         => $this->get_translation('buttonlocation_bottomleft'),
            'bottom:right'        => $this->get_translation('buttonlocation_bottomright'),
        );
    }

    /**
     * Return button location value.
     * @return string
     */
    public function get_buttonLocationValue() {
        $l = $this->get_buttonLocationList();
        return $l[$this->vars['buttonLocation']];
    }

    /**
     * Return available theme value list.
     * @return array
     */
    public function get_availableThemeList() {
        return array(
            'dark'        => $this->get_translation('availabletheme_dark'),
            'blue'        => $this->get_translation('availabletheme_blue'),
            'purple'    => $this->get_translation('availabletheme_purple'),
        );
    }

    /**
     * Return available theme value.
     * @return string
     */
    public function get_availableThemeValue() {
        $l = $this->get_availableThemeList();
        return $l[$this->vars['appliedTheme']];
    }
}
?>
