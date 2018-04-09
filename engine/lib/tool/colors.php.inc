<?php
/**
 * @brief Specific methods related to colors
 * @details Engine / Tool Library
 * @file engine/lib/tool/colors.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2017
 * @date Modification: Apr 2018
 * @copyright 2017 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Load colors locales.
 * @param string $language
 * @return void
 */
function colors_loadLocales($language='') {
    global $camyks;
    
    /* check lang value */
    if ($language=='') $language = $camyks->current_language;
    
    /* load locales */
    $camyks->add_generic_translation('colors', $language);
}

/**
 * Return color title.
 * @param string $color
 * @param string $language
 * @return string
 */
function color_getTitle($color='', $language='') {
    global $camyks;
    
    /* load locales */
    colors_loadLocales();
    
    /* check locale */
    if (isset($camyks->trads['color_'.$color]))
        return $camyks->get_translation('color_'.$color);
    return $color;
}
?>