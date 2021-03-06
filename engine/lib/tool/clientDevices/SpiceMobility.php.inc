<?php
/**
 * @brief Spice Mobility client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/SpiceMobility.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Mar 2019
 * @date Modification: Jun 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return SpiceMobility client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_SpiceMobilityClientDevice($deviceCode='') {
    $deviceList = array(
        'Mi-349'    => array('platform_model' => 'Smart Flo Edge', 'platform_year' => 2013),
        'F302'      => array('platform_model' => 'F302', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Spice Mobility',
        'platform_country'  => 'in',
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
