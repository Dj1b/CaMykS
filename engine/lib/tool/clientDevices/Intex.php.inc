<?php
/**
 * @brief Intex client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Intex.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2019
 * @date Modification: Sep 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Intex client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_IntexClientDevice($deviceCode='') {
    $deviceList = array(
        /* Intex mobiles */
        'Aqua 5.5 VR'  => array('platform_model' => 'Aqua 5.5 VR',    'platform_year' => 2016,),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Intex',
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
