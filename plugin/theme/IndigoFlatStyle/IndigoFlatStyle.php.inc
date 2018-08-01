<?php
/**
 * @brief IndigoFlatStyle Theme.
 * <br /> Main admin CaMykS theme.
 * @details Plugin / Theme Engine
 * @file plugin/theme/IndigoFlatStyle/IndigoFlatStyle.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Oct 2014
 * @date Modification: Aug 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * IndigoFlatStyle Theme class.
 */
final class IndigoFlatStyle extends Theme {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('IndigoFlatStyle', $path_type);

        /* overwrite Plugin information */
        $this->title = 'Indigo Flat';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* update useEnhanceSelectInputs value */
        $this->useEnhancedSelectInputs = false;

        /* check for responsive admin mode */
        $this->isAdminResponsive = true;
    }
}
?>
