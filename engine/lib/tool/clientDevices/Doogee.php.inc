<?php
/**
 * @brief Doogee client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.18
 * @date Creation: Sep 2018
 * @date Modification: Nov 2021
 * @copyright 2018 - 2021 CaMykS Team
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
        'X5max_PRO'     => array('platform_model' => 'X5 Max Pro',  'platform_year' => 2016),
        'MIX2'          => array('platform_model' => 'Mix 2',       'platform_year' => 2017),
        'MIX'           => array('platform_model' => 'Mix',         'platform_year' => 2017),
        'MIX Lite'      => array('platform_model' => 'Mix Lite',    'platform_year' => 2017),
        'BL5000'        => array('platform_model' => 'BL5000',      'platform_year' => 2017),
        'X30'           => array('platform_model' => 'X30',         'platform_year' => 2017),
        'BL12000 PRO'   => array('platform_model' => 'BL12000 Pro', 'platform_year' => 2018),
        'MIX 3'         => array('platform_model' => 'MIX 3',       'platform_year' => 2018),
        'X20L'          => array('platform_model' => 'X20L',        'platform_year' => 2018),
        'X60L'          => array('platform_model' => 'X60L',        'platform_year' => 2018),
        'X70'           => array('platform_model' => 'X70',         'platform_year' => 2018),
        'S55_Lite'      => array('platform_model' => 'S55 Lite',    'platform_year' => 2018),
        'S60Lite'       => array('platform_model' => 'S60 Lite',    'platform_year' => 2018),
        'N20'           => array('platform_model' => 'N20',         'platform_year' => 2019),
        'S90'           => array('platform_model' => 'S90',         'platform_year' => 2019),
        'N20Pro'        => array('platform_model' => 'N20 Pro',     'platform_year' => 2020),
        'S40Pro'        => array('platform_model' => 'S40 Pro',     'platform_year' => 2020),
        'S58Pro'        => array('platform_model' => 'S58 Pro',     'platform_year' => 2020),
        'S59'           => array('platform_model' => 'S59',         'platform_year' => 2020),
        'S88Pro'        => array('platform_model' => 'S88 Pro',     'platform_year' => 2020),
        'X95'           => array('platform_model' => 'X95',         'platform_year' => 2020),
        'X95Pro'        => array('platform_model' => 'X95 Pro',     'platform_year' => 2020),
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
