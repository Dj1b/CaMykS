<?php
/**
 * @brief Nubia client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Nubia.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Aug 2020
 * @date Modification: Aug 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Nubia client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_NubiaClientDevice($deviceCode='') {
    $deviceList = array(
        /* Nubia mobiles */
        'NX591J'	=> array('platform_model' => 'Z17 Lite', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Nubia',
        'platform_country'  => 'cn',
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
