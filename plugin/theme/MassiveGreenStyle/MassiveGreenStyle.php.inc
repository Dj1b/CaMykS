<?php
/**
 * @brief MassiveGreenStyle theme.
 * <br /> Very green theme.
 * @details Plugin / Theme Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jan 2009
 * @date Modification: Jul 2025
 * @copyright 2009 - 2025 CaMykS Team
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
     */
    public function __construct($path_type) {
        parent::__construct('MassiveGreenStyle', $path_type);

        /* Override Plugin information */
        $this->title = 'Massive Green';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override theme methods */

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
