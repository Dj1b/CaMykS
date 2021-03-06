<?php
/**
 * @brief Umidigi client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: May 2019
 * @date Modification: Apr 2021
 * @copyright 2019 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Umidigi client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_UmidigiClientDevice($deviceCode='') {
    $deviceList = array(
        'Z'         => array('platform_model' => 'Z',           'platform_year' => 2016),
        'Z Pro'     => array('platform_model' => 'Z Pro',       'platform_year' => 2016),
        'Z1 Pro'    => array('platform_model' => 'Z1 Pro',      'platform_year' => 2017),
        'C Note'    => array('platform_model' => 'C Note',      'platform_year' => 2017),
        'C Note 2'  => array('platform_model' => 'C Note 2',    'platform_year' => 2017),
        'A1 Pro'    => array('platform_model' => 'A1 Pro',      'platform_year' => 2018),
        'A3 Pro'    => array('platform_model' => 'A3 Pro',      'platform_year' => 2018),
        'A5 Pro'    => array('platform_model' => 'A5 Pro',      'platform_year' => 2018),
        'S2 Lite'   => array('platform_model' => 'S2 Lite',     'platform_year' => 2018),
        'S3 Pro'    => array('platform_model' => 'S3 Pro',      'platform_year' => 2019),
        'Power'     => array('platform_model' => 'Power',       'platform_year' => 2019),
        'X'         => array('platform_model' => 'X',           'platform_year' => 2019),
        'BISON'     => array('platform_model' => 'Bison',       'platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Umidigi',
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
