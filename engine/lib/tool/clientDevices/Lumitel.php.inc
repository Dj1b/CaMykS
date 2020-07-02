<?php
/**
 * @brief Lumitel client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Lumitel.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: May 2020
 * @date Modification: May 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Lumitel client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LumitelClientDevice($deviceCode='') {
    $deviceList = array(
        /* Lumitel mobiles */
        'L9502'  => array('platform_model' => 'L9502', 'platform_year' => 2019),
        'L9503'  => array('platform_model' => 'L9503', 'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Lumitel',
        'platform_country'  => 'bi',
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
