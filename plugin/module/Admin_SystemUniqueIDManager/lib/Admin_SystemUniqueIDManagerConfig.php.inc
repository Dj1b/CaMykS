<?php
/**
 * @brief Admin_SystemUniqueIDManager Module configuration library
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2015
 * @date Modification: Jan 2021
 * @copyright 2015 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemUniqueIDManagerConfig class.
 */
final class Admin_SystemUniqueIDManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);
        
        /* Generating attributes */
        $this->add_newItem('generating_method', 'integer', 0);
        $this->add_newItem('generating_length', 'integer', 10);
        $this->add_newItem('generating_maxAttempts', 'integer', 25);
        
        /* Perform generic initialisation */
        parent::init_config();
    }    
}
?>