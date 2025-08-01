<?php
/**
 * @brief MacOS7Style theme.
 * <br /> Vintage theme using Apple's System 7 design.
 * @details Plugin / Theme Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Dec 2008
 * @date Modification: Jul 2025
 * @copyright 2008 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MacOS7Style Theme class.
 */
final class MacOS7Style extends Theme {
    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('MacOS7Style', $path_type);

        /* Override Plugin information */
        $this->title = 'Mac OS 7';
        $this->version = '1.0';
        $this->plugin_package = 'Fun &amp; Games';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override Theme methods */

    /**
     * Build box title bar.
     * @param string $title
     * @return string
     */
    public function get_boxTitleBar($title='') {
        $title = trim(preg_replace('/&nbsp;/i', '', $title));
        if ($title=='')
            return $this->get_part('boxTitleBarE');
        return $this->get_part('boxTitleBar', array($title));
    }
}
?>
