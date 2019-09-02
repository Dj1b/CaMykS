<?php
/**
 * @brief Wileyfox client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Wileyfox.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jul 2019
 * @date Modification: Jul 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Wileyfox client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_WileyfoxClientDevice($deviceCode='') {
    $deviceList = array(
        'Storm'         => array('platform_year' => 2015),
        'Swift'         => array('platform_year' => 2015),
        'Spark'         => array('platform_year' => 2016),
        'Spark +'       => array('platform_year' => 2016),
        'Spark X'       => array('platform_year' => 2016),
        'Swift 2'       => array('platform_year' => 2016),
        'Swift X'       => array('platform_year' => 2016),
        'Swift Plus'    => array('platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Wileyfox',
        'platform_country'  => 'gb',
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
