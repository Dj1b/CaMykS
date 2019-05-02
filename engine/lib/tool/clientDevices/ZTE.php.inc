<?php
/**
 * @brief ZTE client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/ZTE.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: May 2018
 * @date Modification: Apr 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return ZTE client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_ZTEClientDevice($deviceCode='') {
    $deviceList = array(
        'BLADE V7 LITE' => array('platform_model' => 'Blade V7 Lite',   'platform_year' => 2016),
        'Z833'          => array('platform_model' => 'Avid Trio',       'platform_year' => 2016),
        'A2017G'        => array('platform_model' => 'Axon 7',          'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'ZTE',
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
