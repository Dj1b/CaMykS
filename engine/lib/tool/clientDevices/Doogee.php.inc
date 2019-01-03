<?php
/**
 * @brief Doogee client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Doogee.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2018
 * @date Modification: Dec 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Doogee client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_DoogeeClientDevice($deviceCode='') {
    $deviceList = array(
        'MIX Lite'  => array('platform_model' => 'Mix Lite',    'platform_year' => 2017),
        'BL5000'    => array('platform_model' => 'BL5000',      'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Doogee',
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
