<?php
/**
 * @brief OnePlus client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/OnePlus.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return OnePlus client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_OnePlusClientDevice($deviceCode='') {
    $deviceList = array(
        'A3003' => array('platform_model' => '3T'),
        'A3010' => array('platform_model' => '3T'),
        'A5000' => array('platform_model' => '5'),
        'E1003' => array('platform_model' => 'X'),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'OnePlus',
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