<?php
/**
 * @brief Realme client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Realme.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2020
 * @date Modification: Jun 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Realme client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_RealmeClientDevice($deviceCode='') {
    $deviceList = array(
        /* Realme mobiles */
        'RMX1811'   => array('platform_model' => 'C1',      'platform_year' => 2018),
        'RMX1825'   => array('platform_model' => '3',       'platform_year' => 2019),
        'RMX1911'   => array('platform_model' => '5',       'platform_year' => 2019),
        'RMX1931'   => array('platform_model' => 'X2 Pro',  'platform_year' => 2019),
        'RMX1971'   => array('platform_model' => '5 Pro',   'platform_year' => 2019),
        'RMX1991'   => array('platform_model' => 'X2',      'platform_year' => 2019),
        'RMX1992'   => array('platform_model' => 'X2',      'platform_year' => 2019),
        'RMX1993'   => array('platform_model' => 'X2',      'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Realme',
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
