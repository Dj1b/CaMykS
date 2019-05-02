<?php
/**
 * @brief Torque client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Torque.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2019
 * @date Modification: Apr 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Torque client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_TorqueClientDevice($deviceCode='') {
    $deviceList = array(
        'Edge'    => array('platform_model' => 'DROIDZ Edge', 'platform_year' => 2013),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Torque',
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
