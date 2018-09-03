<?php
/**
 * @brief AdminPage Template.
 * <br /> Template designed for admin mode.
 * @details Plugin / Template Engine
 * @file plugin/template/AdminPage/AdminPage.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2005
 * @date Modification: Aug 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * AdminPage Template class.
 */
final class AdminPage extends Template {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('AdminPage', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'System';

        /* overwrite Template information */
        $this->title = 'Admin';
        $this->modules = 2;

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* specific tool methods */

    /**
     * Return signature image URL.
     * @return string
     */
    protected function get_signPicture() {
        global $camyks;
        $default = $this->get_fileURL('img/sign_fr.png');
        return $this->get_fileURL('img/sign_'.$camyks->current_language.'.png', null, $default);
    }
}
?>
