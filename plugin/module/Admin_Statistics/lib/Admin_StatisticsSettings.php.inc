<?php
/**
 * @brief Admin_Statistics Module configuration library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_StatisticsSettings class.
 */
final class Admin_StatisticsSettings extends PluginConfig {
    /**
     * Class constructor.
     * @param sting $name
     * @param Plugin $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Object items */
        $this->add_newItem('stat_sitepage', 'int', 0);
        $this->add_newItem('stat_visits', 'int', 0);
        $this->add_newItem('stat_firstpage', 'int', 0);
        $this->add_newItem('stat_referer', 'int', 0);
        $this->add_newItem('stat_webbots', 'int', 0);
        $this->add_newItem('stat_webtools', 'int', 0);

        $this->add_newItem('stat_filteredips', 'array', array());

        /* generic initialisation */
        parent::init_config();
    }
}
?>
