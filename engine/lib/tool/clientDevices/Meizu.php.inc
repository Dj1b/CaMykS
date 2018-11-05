<?php
/**
 * @brief Meizu client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Meizu.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2018
 * @date Modification: Oct 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Meizu client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MeizuClientDevice($deviceCode='') {
    $deviceList = array(
        'MZ-PRO 6'  => array('platform_model' => 'Pro 6',   'platform_year' => 2016),
        'M3s'       => array('platform_model' => 'M3s',     'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Meizu',
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
