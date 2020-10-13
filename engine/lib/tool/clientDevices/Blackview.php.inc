<?php
/**
 * @brief Blackview client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.13
 * @date Creation: Jul 2018
 * @date Modification: Oct 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Blackview client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_BlackviewClientDevice($deviceCode='') {
    $deviceList = array(
        /* Blackview BV series */
        'BV6000'        => array('platform_model' => 'BV6000',          'platform_year' => 2016),
        'BV7000 Pro'    => array('platform_model' => 'BV7000 Pro',      'platform_year' => 2017),
        'BV8000Pro'     => array('platform_model' => 'BV8000 Pro',      'platform_year' => 2017),
        'BV9000Pro F'   => array('platform_model' => 'BV9000 Pro F',    'platform_year' => 2017),
        'BV5800'        => array('platform_model' => 'BV5800',          'platform_year' => 2018),
        'BV9500'        => array('platform_model' => 'BV9500',          'platform_year' => 2018),
        'BV9500Pro'     => array('platform_model' => 'BV9500 Pro',      'platform_year' => 2018),
        'BV9600Pro'     => array('platform_model' => 'BV9600 Pro',      'platform_year' => 2018),
        'BV5500Pro'     => array('platform_model' => 'BV5500 Pro',      'platform_year' => 2019),
        'BV5900'        => array('platform_model' => 'BV5900',          'platform_year' => 2019),
        'BV9500Plus'    => array('platform_model' => 'BV9500 Plus',     'platform_year' => 2019),
        'BV9800Pro'     => array('platform_model' => 'BV9800 Pro',      'platform_year' => 2019),

        /* Blackview P series */
        'P10000 Pro'    => array('platform_model' => 'P10000 Pro',      'platform_year' => 2018),

        /* Blackview other mobiles */
        'S8'            => array('platform_model' => 'S8',              'platform_year' => 2016),
        'A60Pro'        => array('platform_model' => 'A60Pro',          'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Blackview',
        'platform_country'  => 'hk',
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
