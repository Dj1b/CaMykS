<?php
/**
 * @brief DefaultPage Template.
 * <br /> Template designed for single module websites.
 * @details Plugin / Template Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Sep 2005
 * @date Modification: Jul 2025
 * @copyright 2005 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * DefaultPage Template class.
 */
final class DefaultPage extends Template {
    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('DefaultPage', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'System';

        /* Override Template variables */
        $this->title = 'Default';
        $this->modules = 1;

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }
}
?>
