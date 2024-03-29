<?php
/**
 * @brief OnePlus client devices specific methods.
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.23
 * @date Creation: Apr 2018
 * @date Modification: Nov 2021
 * @copyright 2018 - 2021 CaMykS Team
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
        'A0001'     => array('platform_model' => 'One',         'platform_year' => 2014),
        'A2001'     => array('platform_model' => '2',           'platform_year' => 2015),
        'A2003'     => array('platform_model' => '2',           'platform_year' => 2015),
        'A2005'     => array('platform_model' => '2',           'platform_year' => 2015),
        'E1003'     => array('platform_model' => 'X',           'platform_year' => 2015),
        'A3000'     => array('platform_model' => '3',           'platform_year' => 2016),
        'A3003'     => array('platform_model' => '3T',          'platform_year' => 2016),
        'A3010'     => array('platform_model' => '3T',          'platform_year' => 2016),
        'A5000'     => array('platform_model' => '5',           'platform_year' => 2017),
        'A5010'     => array('platform_model' => '5T',          'platform_year' => 2017),
        'A6000'     => array('platform_model' => '6',           'platform_year' => 2018),
        'A6003'     => array('platform_model' => '6',           'platform_year' => 2018),
        'A6010'     => array('platform_model' => '6T',          'platform_year' => 2018),
        'A6013'     => array('platform_model' => '6T',          'platform_year' => 2018),
        'GM1900'    => array('platform_model' => '7',           'platform_year' => 2019),
        'GM1901'    => array('platform_model' => '7',           'platform_year' => 2019),
        'GM1903'    => array('platform_model' => '7',           'platform_year' => 2019),
        'GM1905'    => array('platform_model' => '7',           'platform_year' => 2019),
        'GM1910'    => array('platform_model' => '7 Pro',       'platform_year' => 2019),
        'GM1911'    => array('platform_model' => '7 Pro',       'platform_year' => 2019),
        'GM1913'    => array('platform_model' => '7 Pro',       'platform_year' => 2019),
        'GM1915'    => array('platform_model' => '7 Pro',       'platform_year' => 2019),
        'GM1917'    => array('platform_model' => '7 Pro',       'platform_year' => 2019),
        'HD1900'    => array('platform_model' => '7T',          'platform_year' => 2019),
        'HD1901'    => array('platform_model' => '7T',          'platform_year' => 2019),
        'HD1903'    => array('platform_model' => '7T',          'platform_year' => 2019),
        'HD1905'    => array('platform_model' => '7T',          'platform_year' => 2019),
        'HD1907'    => array('platform_model' => '7T',          'platform_year' => 2019),
        'HD1910'    => array('platform_model' => '7T Pro',      'platform_year' => 2019),
        'HD1911'    => array('platform_model' => '7T Pro',      'platform_year' => 2019),
        'HD1913'    => array('platform_model' => '7T Pro',      'platform_year' => 2019),
        'HD1925'    => array('platform_model' => '7T Pro 5G',   'platform_year' => 2019),
        'IN2010'    => array('platform_model' => '8',           'platform_year' => 2020),
        'IN2013'    => array('platform_model' => '8',           'platform_year' => 2020),
        'IN2020'    => array('platform_model' => '8',           'platform_year' => 2020),
        'IN2023'    => array('platform_model' => '8 Pro',       'platform_year' => 2020),
        'KB2000'    => array('platform_model' => '8T',          'platform_year' => 2020),
        'KB2001'    => array('platform_model' => '8T',          'platform_year' => 2020),
        'KB2003'    => array('platform_model' => '8T',          'platform_year' => 2020),
        'AC2001'    => array('platform_model' => 'Nord',        'platform_year' => 2020),
        'AC2003'    => array('platform_model' => 'Nord',        'platform_year' => 2020),
        'BE2013'    => array('platform_model' => 'Nord N100',   'platform_year' => 2020),
        'LE2110'    => array('platform_model' => '9',           'platform_year' => 2021),
        'LE2120'    => array('platform_model' => '9 Pro',       'platform_year' => 2021),
        'LE2123'    => array('platform_model' => '9 Pro',       'platform_year' => 2021),
        'LE2125'    => array('platform_model' => '9 Pro',       'platform_year' => 2021),

        '2'         => array('platform_model' => '2',           'platform_year' => 2015),
        '7 Pro'     => array('platform_model' => '7 Pro',       'platform_year' => 2019),
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
