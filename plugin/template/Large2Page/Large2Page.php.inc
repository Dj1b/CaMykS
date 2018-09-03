<?php
/**
 * @brief Large2Page Template.
 * <br /> Template designed for dual modules websites.
 * @details Plugin / Template Engine
 * @file plugin/template/Large2Page/Large2Page.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2007
 * @date Modification: Aug 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Large2Page Template class.
 */
final class Large2Page extends Template {
    /**
     * Class constructor
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Large2Page', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* overwrite Template information */
        $this->title = '2Large';
        $this->modules = 2;

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }
}
?>
