<?php
/**
 * @brief MassiveGreenStyle Theme.
 * <br /> Very green theme.
 * @details Plugin / Theme Engine
 * @file plugin/theme/MassiveGreenStyle/MassiveGreenStyle.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2009
 * @date Modification: Aug 2018
 * @copyright 2009 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MassiveGreenStyle Theme class.
 */
final class MassiveGreenStyle extends Theme {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('MassiveGreenStyle', $path_type);

        /* overwrite Plugin information */
        $this->title = 'Massive Green';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite theme methods */

    /**
     * Load theme parts as included file.
     * @return void
     */
    public function get_parts() {
        global $camyks;
        if (!$this->partsLoaded) {
            parent::get_parts();
            if(preg_match('/msie/i', $_SERVER['HTTP_USER_AGENT'])) {
                /* load IE specific CSS styles */
                $camyks->HTMLPage->add_styleFile($this->get_fileURL('parts_ie.css'));
            }
        }
    }
}
?>
