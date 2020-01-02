<?php
/**
 * @brief Orbic client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Orbic.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Dec 2019
 * @date Modification: Dec 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Orbic client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_OrbicClientDevice($deviceCode='') {
    /* Update device code */
    $deviceCode = strtoupper($deviceCode);

    $deviceList = array(
        /* Orbic mobiles */
        'RC501L'    => array('platform_model' => 'Reliance',    'platform_year' => 2016),
        'RC555L'    => array('platform_model' => 'Wonder',      'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Orbic',
        'platform_country'  => 'us',
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
