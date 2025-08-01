<?php
/**
 * @brief Admin_GenericMediaLibraryManager module, configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Jun 2015
 * @date Modification: Jul 2025
 * @copyright 2015 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericMediaLibraryManagerConfig class.
 */
final class Admin_GenericMediaLibraryManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Configuration attributes */
        $this->add_newItem('picture_maxFileSize', 'float', 8);
        $this->add_newItem('picture_resizeMode', 'integer', 0);
        $this->add_newItem('picture_backgroundColor', 'string', '#FFFFFF');
        $this->add_newItem('picture_fileType', 'integer', 0);
        $this->add_newItem('picture_jpgQuality', 'integer', 70);
        $this->add_newItem('picture_pictureWidth', 'int', 800);
        $this->add_newItem('picture_pictureHeight', 'int', 600);
        $this->add_newItem('picture_thumbWidth', 'int', 120);
        $this->add_newItem('picture_thumbHeight', 'int', 100);

        /* Perform generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific tool methods */

    /**
     * Return resize mode list.
     * @return array
     */
    public function get_resizeModeList() {
        return array(
            0 => $this->get_translation('pictureresizemode_fixedsize'),
            1 => $this->get_translation('pictureresizemode_maxsize'),
        );
    }

    /**
     * Return image type value list.
     * @return array
     */
    public function get_fileTypeList() {
        return array(
            0 => $this->get_translation('imagefiletype_original'),
            1 => $this->get_translation('imagefiletype_forcedtojpg'),
            2 => $this->get_translation('imagefiletype_forcedtogif'),
            3 => $this->get_translation('imagefiletype_forcedtopng'),
        );
    }
}
?>
