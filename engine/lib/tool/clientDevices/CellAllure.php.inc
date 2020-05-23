<?php
/**
 * @brief CellAllure client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/CellAllure.php.inc
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
 * Return CellAllure client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_CellAllureClientDevice($deviceCode='') {
    $deviceList = array(
        /* CellAllure mobiles */
        'Fashion C'  => array('platform_model' => 'Fashion C', 'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'CellAllure',
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
