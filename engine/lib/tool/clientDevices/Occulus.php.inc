<?php
/**
 * @brief Occulus client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Occulus.php.inc
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
 * Return Occulus client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_OcculusClientDevice($deviceCode='') {
    $deviceList = array(
        /* Occulus mobiles */
        'Quest'  => array('platform_model' => 'Quest', 'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Occulus',
        'platform_country'  => 'us',
        'platform_model'    => $deviceCode,
        'platform_type'     => 'vrheadset',
        'platform_format'   => 'handheld',
    );

    /* Check if device is a known device. */
    if (!array_key_exists($deviceCode, $deviceList))
        return $result;

    /* Return result. */
    return array_merge($result, $deviceList[$deviceCode]);
}
?>
