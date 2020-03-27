<?php
/**
 * @brief Poptel client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Poptel.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2019
 * @date Modification: Mar 2020
 * @copyright 2019 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Poptel client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_PoptelClientDevice($deviceCode='') {
    /* Update device code */
    $deviceCode = strtoupper($deviceCode);

    $deviceList = array(
        /* Poptel mobiles */
        'P10'       => array('platform_model' => 'P10',         'platform_year' => 2018),
        'P9000_MAX' => array('platform_model' => 'P9000 Max',   'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Poptel',
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
