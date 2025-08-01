<?php
/**
 * @brief Admin_GenericEmailingManager module, emailing configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Dec 2012
 * @date Modification: Jul 2025
 * @copyright 2012 - 2025 CaMykS Team
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
     * @param Plugin $parent
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

    /* Mark: Override PluginConfig methods */

    /**
     * Check object items values.
     * @return boolean
     */
    public function check_data() {
        /* Update lib file before saving for new emailings */
        $this->_libFile = $this->_libFolder.'/'.$this->name.'.php.inc';

        /* Return success */
        return true;
    }
}
?>
