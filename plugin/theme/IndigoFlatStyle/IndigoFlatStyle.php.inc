<?php
/**
 * @brief IndigoFlatStyle theme.
 * <br /> Main admin CaMykS theme.
 * @details Plugin / Theme Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Oct 2014
 * @date Modification: Jul 2025
 * @copyright 2014 - 2025 CaMykS Team
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
     */
    public function __construct($path_type) {
        parent::__construct('IndigoFlatStyle', $path_type);

        /* Override Plugin variables */
        $this->title = 'Indigo Flat';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Update useEnhanceSelectInputs value */
        $this->useEnhancedSelectInputs = false;

        /* Check for responsive admin mode */
        $this->isAdminResponsive = true;
    }
}
?>
