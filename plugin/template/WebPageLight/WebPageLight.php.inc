<?php
/**
 * @brief WebPageLight Template.
 * <br /> Template designed 3-modules websites.
 * @details Plugin / Template Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Dec 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * WebPageLight Template class.
 */
final class WebPageLight extends Template {
    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('WebPageLight', $path_type);

        /* Override Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Override Template information */
        $this->title = 'WebPage Light';
        $this->modules = 3;

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }
}
?>
