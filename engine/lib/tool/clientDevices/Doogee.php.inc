<?php
/**
 * @brief Doogee client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Doogee.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.6
 * @date Creation: Sep 2018
 * @date Modification: Aug 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Doogee client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_DoogeeClientDevice($deviceCode='') {
    $deviceList = array(
        'X5max_PRO' => array('platform_model' => 'X5 Max Pro',  'platform_year' => 2016),
        'MIX Lite'  => array('platform_model' => 'Mix Lite',    'platform_year' => 2017),
        'BL5000'    => array('platform_model' => 'BL5000',      'platform_year' => 2017),
        'X20L'      => array('platform_model' => 'X20L',        'platform_year' => 2018),
        'X60L'      => array('platform_model' => 'X60L',        'platform_year' => 2018),
        'X70'       => array('platform_model' => 'X70',         'platform_year' => 2018),
        'S90'       => array('platform_model' => 'S90',         'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Doogee',
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
