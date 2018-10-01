<?php
/**
 * @brief GoogleAnalytics Input configuration object
 * @details Plugin / Input Library
 * @file plugin/input/GoogleAnalytics/lib/GoogleAnalyticsConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2018
 * @date Modification: Sep 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GoogleAnalyticsConfig PluginConfig class.
 */
final class GoogleAnalyticsConfig extends PluginConfig {

    /*
     * Class constructor.
     * @param string $name
     * @param Module $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* google params */
        $this->add_newItem('trackingId', 'string', '');
        $this->add_newItem('trackingParams', 'string', '');

        /* internal params */
        $this->add_newItem('enableAdminStats', 'boolean', false);

        /* generic initialisation */
        parent::init_config();
    }
}
?>
