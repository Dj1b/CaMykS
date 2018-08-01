<?php
/**
 * @brief SunnyBlocksStyle Theme.
 * <br /> Sunny theme.
 * @details Plugin / Theme Engine
 * @file plugin/theme/SunnyBlocksStyle/SunnyBlocksStyle.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2008
 * @date Modification: Aug 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SunnyBlocksStyle Theme class.
 */
final class SunnyBlocksStyle extends Theme {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('SunnyBlocksStyle', $path_type);

        /* overwrite Plugin information */
        $this->title = 'Sunny Blocks';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }
}
?>
