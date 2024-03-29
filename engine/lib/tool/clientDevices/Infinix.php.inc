<?php
/**
 * @brief Infinix client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.28
 * @date Creation: Feb 2019
 * @date Modification: Mar 2023
 * @copyright 2019 - 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Infinix client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_InfinixClientDevice($deviceCode='') {
    $deviceList = array(
        /* Note serie */
        'NOTE 3'        => array('platform_model' => 'Note 3',      'platform_year' => 2015),
        'NOTE 3 Pro'    => array('platform_model' => 'Note 3 Pro',  'platform_year' => 2016),
        'X571'          => array('platform_model' => 'Note 4 Pro',  'platform_year' => 2017),
        'X572'          => array('platform_model' => 'Note 4',      'platform_year' => 2017),
        'X692'          => array('platform_model' => 'Note 8',      'platform_year' => 2020),

        /* Hot serie */
        'HOT 4'         => array('platform_model' => 'Hot 4',       'platform_year' => 2016),
        'HOT 4 Lite'    => array('platform_model' => 'Hot 4 Lite',  'platform_year' => 2016),
        'HOT 4 Pro'     => array('platform_model' => 'Hot 4 Pro',   'platform_year' => 2017),
        'X551'          => array('platform_model' => 'Hot Note',    'platform_year' => 2015),
        'X559'          => array('platform_model' => 'Hot 5 Lite',  'platform_year' => 2017),
        'X559C'         => array('platform_model' => 'Hot 5',       'platform_year' => 2017),
        'X573'          => array('platform_model' => 'Hot S3',      'platform_year' => 2018),
        'X606'          => array('platform_model' => 'Hot 6',       'platform_year' => 2018),
        'X606C'         => array('platform_model' => 'Hot 6',       'platform_year' => 2018),
        'X606D'         => array('platform_model' => 'Hot 6',       'platform_year' => 2018),
        'X608'          => array('platform_model' => 'Hot 6 Pro',   'platform_year' => 2018),
        'X623'          => array('platform_model' => 'Hot 6X',      'platform_year' => 2018),
        'X624B'         => array('platform_model' => 'Hot 7',       'platform_year' => 2019),
        'X650'          => array('platform_model' => 'Hot 8',       'platform_year' => 2019),
        'X650B'         => array('platform_model' => 'Hot 8',       'platform_year' => 2019),
        'X650C'         => array('platform_model' => 'Hot 8',       'platform_year' => 2019),
        'X650D'         => array('platform_model' => 'Hot 8',       'platform_year' => 2019),
        'X680'          => array('platform_model' => 'Hot 9',       'platform_year' => 2020),
        'X680B'         => array('platform_model' => 'Hot 9 Play',  'platform_year' => 2020),
        'X682B'         => array('platform_model' => 'Hot 10',      'platform_year' => 2020),
        'X688C'         => array('platform_model' => 'Hot 10 Play', 'platform_year' => 2021),

        /* Smart serie */
        'X5515'         => array('platform_model' => 'Smart 2',     'platform_year' => 2018),
        'X609'          => array('platform_model' => 'Smart 2 HD',  'platform_year' => 2018),
        'X653'          => array('platform_model' => 'Smart 4',     'platform_year' => 2019),
        'X653C'         => array('platform_model' => 'Smart 4',     'platform_year' => 2019),
        'X657'          => array('platform_model' => 'Smart 5',     'platform_year' => 2020),
        'X657C'         => array('platform_model' => 'Smart 5',     'platform_year' => 2020),

        /* Zero serie */
        'Zero 3'        => array('platform_year' => 2015),
        'Zero 4 Plus'   => array('platform_year' => 2017),

        /* S serie */
        'X626'          => array('platform_model' => 'S4',          'platform_year' => 2019),
        'X626B'         => array('platform_model' => 'S4',          'platform_year' => 2019),
        'X652A'         => array('platform_model' => 'S5',          'platform_year' => 2019),
        'X652B'         => array('platform_model' => 'S5 Lite',     'platform_year' => 2019),
        'X652C'         => array('platform_model' => 'S5 Lite',     'platform_year' => 2019),
        'X660C'         => array('platform_model' => 'S5 Pro',      'platform_year' => 2020),

    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Infinix',
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
