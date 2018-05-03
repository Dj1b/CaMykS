<?php
/**
 * @brief Yotaphone client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Yotaphone.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2018
 * @date Modification: May 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Yotaphone client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_YotaphoneClientDevice($deviceCode='') {
    $deviceList = array(
        'YD201' => array('platform_model' => '2',   'platform_year' => 2014),
        'YD206' => array('platform_model' => '2',   'platform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Yotaphone',
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