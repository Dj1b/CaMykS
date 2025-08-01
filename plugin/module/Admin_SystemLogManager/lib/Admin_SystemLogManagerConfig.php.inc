<?php
/**
 * @brief Admin_SystemLogManager module, configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jun 2018
 * @date Modification: Jul 2025
 * @copyright 2018 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemLogManagerConfig PluginConfig class.
 */
final class Admin_SystemLogManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        $this->add_newItem('logging_period', 'int', 0);
        $this->add_newItem('logging_lastFilesKept', 'int', 20);

        /* generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific methods */

    /**
     * Return logging period value list
     * @return array
     */
    public function get_loggingPeriodList() {
        return array(
            0 => $this->get_translation('loggingperiod_daily'),
            1 => $this->get_translation('loggingperiod_weekly'),
            2 => $this->get_translation('loggingperiod_monthly'),
        );
    }
}
?>
