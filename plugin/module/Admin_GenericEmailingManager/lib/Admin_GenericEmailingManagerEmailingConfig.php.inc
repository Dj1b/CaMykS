<?php
/**
 * @brief Admin_GenericEmailingManager Module emailing configuration library
 * @details Plugin, Module Library
 * @file plugin/module/Admin_GenericEmailingManager/lib/Admin_GenericEmailingManagerEmailingConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericEmailingManagerEmailingConfig class.
 */
final class Admin_GenericEmailingManagerEmailingConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Config items */
        $this->add_newItem('emailing_id', 'integer', 0);
        $this->add_newItem('content_images', 'array', array());
        $this->add_newItem('content_links', 'array', array());

        $this->add_newItem('emailing_current', 'integer', 0);
        $this->add_newItem('emailing_list', 'array', array());

        /* generic initialisation */
        parent::init_config();
    }
}
?>
