<?php
/**
 * @brief Blackview client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.19
 * @date Creation: Jul 2018
 * @date Modification: Oct 2021
 * @copyright 2018 - 2021 CaMykS Team
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
        'BV6800Pro'     => array('platform_model' => 'BV6800 Pro',      'platform_year' => 2018),
        'BV9500'        => array('platform_model' => 'BV9500',          'platform_year' => 2018),
        'BV9500Pro'     => array('platform_model' => 'BV9500 Pro',      'platform_year' => 2018),
        'BV9600Pro'     => array('platform_model' => 'BV9600 Pro',      'platform_year' => 2018),
        'BV5500Pro'     => array('platform_model' => 'BV5500 Pro',      'platform_year' => 2019),
        'BV5900'        => array('platform_model' => 'BV5900',          'platform_year' => 2019),
        'BV9100'        => array('platform_model' => 'BV9100',          'platform_year' => 2019),
        'BV9500Plus'    => array('platform_model' => 'BV9500 Plus',     'platform_year' => 2019),
        'BV9700Pro'     => array('platform_model' => 'BV9700 Pro',      'platform_year' => 2019),
        'BV9800'        => array('platform_model' => 'BV9800',          'platform_year' => 2019),
        'BV9800Pro'     => array('platform_model' => 'BV9800 Pro',      'platform_year' => 2019),
        'BV4900'        => array('platform_model' => 'BV4900',          'platform_year' => 2020),
        'BV4900Pro'     => array('platform_model' => 'BV4900 Pro',      'platform_year' => 2020),
        'BV9900'        => array('platform_model' => 'BV9900',          'platform_year' => 2020),
        'BV9900Pro'     => array('platform_model' => 'BV9900 Pro',      'platform_year' => 2020),

        /* Blackview P series */
        'P10000 Pro'    => array('platform_model' => 'P10000 Pro',      'platform_year' => 2018),

        /* Blackview other mobiles */
        'A8 MAX'        => array('platform_model' => 'A8 Max',          'platform_year' => 2016),
        'S8'            => array('platform_model' => 'S8',              'platform_year' => 2016),
        'A60'           => array('platform_model' => 'A60',             'platform_year' => 2018),
        'A60Pro'        => array('platform_model' => 'A60Pro',          'platform_year' => 2019),
        'A80Pro'        => array('platform_model' => 'A80Pro',          'platform_year' => 2019),
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
