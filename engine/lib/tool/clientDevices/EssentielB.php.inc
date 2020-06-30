<?php
/**
 * @brief Essentiel B (Boulanger) client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/EssentielB.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2020
 * @date Modification: Jun 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Essentiel B client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_EssentielBClientDevice($deviceCode='') {
    $deviceList = array(
        /* Essentiel B tablets */
        'Smart_TAB_1003s' => array('platform_model' => 'Smart TAB 1003S', 'platform_year' => 2014),

        /* Essentiel B mobiles */
        'HEYOU5'  => array('platform_model' => 'Heyou 5', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Essentiel B',
        'platform_country'  => 'fr',
        'platform_model'    => $deviceCode,
        'platform_type'     => 'handheld',
        'platform_format'   => 'handheld',
    );

    /* Check if device is a known device. */
    if (!array_key_exists($deviceCode, $deviceList))
        return $result;

    /* Return result. */
    return array_merge($result, $deviceList[$deviceCode]);
}
?>
