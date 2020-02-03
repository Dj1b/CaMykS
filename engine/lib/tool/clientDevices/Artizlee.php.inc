<?php
/**
 * @brief Artizlee client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Artizlee.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2020
 * @date Modification: Jan 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Artizlee client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_ArtizleeClientDevice($deviceCode='') {
    /* Update device code */
    $deviceCode = strtoupper($deviceCode);

    $deviceList = array(
        /* Artizlee mobiles */
        'ATL-21A'    => array('platform_model' => '21',  'platform_year' => 2017),
        'ATL-21T'    => array('platform_model' => '21',  'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Artizlee',
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
