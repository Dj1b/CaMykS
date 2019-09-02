<?php
/**
 * @brief OnePlus client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/OnePlus.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.10
 * @date Creation: Apr 2018
 * @date Modification: Aug 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return known OnePlus client device list
 * @return array
 */
function get_OnePlusClientDevices() {
    return array(
        'A0001'     => array('platform_model' => 'One',     'platform_year' => 2014),
        '2'         => array('platform_model' => '2',       'platform_year' => 2015),
        'A2001'     => array('platform_model' => '2',       'platform_year' => 2015),
        'A2003'     => array('platform_model' => '2',       'platform_year' => 2015),
        'A2005'     => array('platform_model' => '2',       'platform_year' => 2015),
        'E1003'     => array('platform_model' => 'X',       'platform_year' => 2015),
        'A3000'     => array('platform_model' => '3',       'platform_year' => 2016),
        'A3003'     => array('platform_model' => '3T',      'platform_year' => 2016),
        'A3010'     => array('platform_model' => '3T',      'platform_year' => 2016),
        'A5000'     => array('platform_model' => '5',       'platform_year' => 2017),
        'A5010'     => array('platform_model' => '5T',      'platform_year' => 2017),
        'A6000'     => array('platform_model' => '6',       'platform_year' => 2018),
        'A6003'     => array('platform_model' => '6',       'platform_year' => 2018),
        'A6010'     => array('platform_model' => '6T',      'platform_year' => 2018),
        'A6013'     => array('platform_model' => '6T',      'platform_year' => 2018),
        'GM1901'    => array('platform_model' => '7',       'platform_year' => 2019),
        'GM1903'    => array('platform_model' => '7',       'platform_year' => 2019),
        'GM1905'    => array('platform_model' => '7',       'platform_year' => 2019),
        'GM1911'    => array('platform_model' => '7 Pro',   'platform_year' => 2019),
        'GM1913'    => array('platform_model' => '7 Pro',   'platform_year' => 2019),
        'GM1915'    => array('platform_model' => '7 Pro',   'platform_year' => 2019),
        'GM1917'    => array('platform_model' => '7 Pro',   'platform_year' => 2019),
    );
}

/**
 * Return OnePlus client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_OnePlusClientDevice($deviceCode='') {
    $deviceList = get_OnePlusClientDevices();

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'OnePlus',
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

/*
 * Check if given device is a OnePlus know device
 * @return array
 */
function is_OnePlusKnownDevice($deviceCode='') {
    $deviceList = get_OnePlusClientDevices();
    return (array_key_exists($deviceCode, $deviceList));
}
?>
