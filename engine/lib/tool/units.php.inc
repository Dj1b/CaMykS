<?php
/**
 * @brief Units specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/units.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2019
 * @date Modification: Feb 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Load units locales.
 * @param string $language
 * @return void
 */
function units_loadLocales($language='') {
    global $camyks;

    /* check lang value */
    if ($language=='') $language = $camyks->current_language;

    /* load locales */
    $camyks->add_generic_translation('units', $language);
}

/**
 * Return unit title.
 * @param string $unit
 * @param string $language
 * @return string
 */
function unit_getTitle($unit='', $language='') {
    global $camyks;

    /* load locales */
    units_loadLocales();

    /* check locale */
    if (isset($camyks->trads['unit_'.$unit]))
        return $camyks->get_translation('unit_'.$unit);
    return $unit;
}
?>
