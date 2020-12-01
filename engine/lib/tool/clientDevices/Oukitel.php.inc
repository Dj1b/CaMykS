<?php
/**
 * @brief Oukitel client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.9
 * @date Creation: Jan 2019
 * @date Modification: Nov 2020
 * @copyright 2019 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Oukitel client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_OukitelClientDevice($deviceCode='') {
    $deviceList = array(
        'K6000 Plus'    => array('platform_model' => 'K6000 Plus',  'platform_year' => 2016),
        'K6000 Pro'     => array('platform_model' => 'K6000 Pro',   'platform_year' => 2016),
        'K8000'         => array('platform_model' => 'K8000',       'platform_year' => 2016),
        'K10000 Max'    => array('platform_model' => 'K10000 Max',  'platform_year' => 2017),
        'K6'            => array('platform_model' => 'K6',          'platform_year' => 2017),
        'K7'            => array('platform_model' => 'K7',          'platform_year' => 2018),
        'WP1'           => array('platform_model' => 'WP1',         'platform_year' => 2018),
        'K12'           => array('platform_model' => 'K12',         'platform_year' => 2019),
        'C15 Pro'       => array('platform_model' => 'C15 Pro',     'platform_year' => 2019),
        'C17 Pro'       => array('platform_model' => 'C17 Pro',     'platform_year' => 2019),
        'WP5'           => array('platform_model' => 'WP5',         'platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Oukitel',
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
