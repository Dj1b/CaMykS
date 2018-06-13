<?php
/**
 * @brief Admin_SystemLogManager Module configuration object
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SystemLogManager/lib/Admin_SystemLogManagerConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2018
 * @date Modification: Jun 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemLogManagerConfig PluginConfig class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class Admin_SystemLogManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        $this->add_newItem('logging_period', 'int', 0);
        $this->add_newItem('logging_lastFilesKept', 'int', 20);

        /* generic initialisation */
        parent::init_config();
    }

    /* specific methods */

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