<?php
/**
 * @brief PsionicStormStyle Theme.
 * <br /> Theme inspired by Protoss.
 * @details Plugin / Theme Engine
 * @file plugin/theme/PsionicStormStyle/PsionicStormStyle.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2008
 * @date Modification: Aug 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PsionicStormStyle Theme class.
 */
final class PsionicStormStyle extends Theme {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('PsionicStormStyle', $path_type);

        /* overwrite Plugin information */
        $this->title = 'Psionic Storm';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }
}
?>
