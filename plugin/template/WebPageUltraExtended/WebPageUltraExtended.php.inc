<?php
/**
 * @brief WebPageUltraExtended Template.
 * <br /> Template designed 6-modules websites.
 * @details Plugin / Template Engine
 * @file plugin/template/WebPageUltraExtended/WebPageUltraExtended.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2008
 * @date Modification: Aug 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * WebPageUltraExtended Template class.
 */
final class WebPageUltraExtended extends Template {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('WebPageUltraExtended', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* overwrite Template information */
        $this->title = 'WebPage Ultra Extended';
        $this->modules = 6;

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }
}
?>
