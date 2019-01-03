<?php
/**
 * @brief Admin_GenericEmailingManager Module configuration library
 * @details Plugin, Module Library
 * @file plugin/module/Admin_GenericEmailingManager/lib/Admin_GenericEmailingManagerConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2013
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericEmailingManagerConfig class.
 */
final class Admin_GenericEmailingManagerConfig extends PluginConfig {
    /**
     * Class constructor
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Unsubscribing params */
        $this->add_newItem('unsubscribe_backpage', 'string', '');

        /* Generic initialisation */
        parent::init_config();
    }
}
?>
