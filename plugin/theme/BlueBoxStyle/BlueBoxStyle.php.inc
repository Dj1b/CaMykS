<?php
/**
 * @brief BlueBoxStyle Theme.
 * <br /> Theme with blue boxes.
 * @details Plugin / Theme Engine
 * @file plugin/theme/BlueBoxStyle/BlueBoxStyle.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2008
 * @date Modification: Aug 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * BlueBoxStyle Theme class.
 */
final class BlueBoxStyle extends Theme {
    /**
     * Class constructor.
     * @param string $path_type
     * @
     */
    public function __construct($path_type) {
        parent::__construct('BlueBoxStyle', $path_type);

        /* overwrite Plugin information */
        $this->title = 'Blue Box';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite Theme methods */

    /**
     * Send main css to camyks object.
     * @return void
     */
    public function get_main_css() {
        global $camyks;
        parent::get_main_css();

        /* load IE specific CSS styles */
        if (preg_match('/msie/i', $_SERVER['HTTP_USER_AGENT'])) {
            $camyks->HTMLPage->add_styleFile($this->get_fileURL('editor_ie.css'));
        }
    }

    /**
     * Load theme parts as included file.
     * @return void
     */
    public function get_parts() {
        global $camyks;
        if (!$this->partsLoaded) {
            parent::get_parts();
            if (preg_match('/msie/i', $_SERVER['HTTP_USER_AGENT'])) {
                /* load IE specific CSS styles */
                $camyks->HTMLPage->add_styleFile($this->get_fileURL('parts_ie.css'));
            }
        }
    }
}
?>
