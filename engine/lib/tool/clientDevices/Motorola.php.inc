<?php
/**
 * @brief Motorola client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Motorola.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.10
 * @date Creation: Apr 2018
 * @date Modification: Mar 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Motorola client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MotorolaClientDevice($deviceCode='') {
    $deviceList = array(
        'XT720'         => array('platform_model' => 'Milestone XT720',     'platform_year' => 2010),
        'XT1022'        => array('platform_model' => 'Moto E',              'platform_year' => 2014),
        'XT1031'        => array('platform_model' => 'Moto G',              'platform_year' => 2013),
        'XT1032'        => array('platform_model' => 'Moto G',              'platform_year' => 2013),
        'XT1033'        => array('platform_model' => 'Moto G',              'platform_year' => 2013),
        'XT1039'        => array('platform_model' => 'Moto 4G',             'platform_year' => 2013),
        'XT1072'        => array('platform_model' => 'Moto G 4G (2nd Gen)', 'platform_year' => 2013),
        'XT1092'        => array('platform_model' => 'Moto X (2nd Gen)',    'platform_year' => 2014),
        'XT1650'        => array('platform_model' => 'Moto Z',              'platform_year' => 2016),

        'Droid'         => array('platform_model' => 'Droid',               'platform_year' => 2009),
        'MB200'         => array('platform_model' => 'Dext',                'platform_year' => 2009),
        'Milestone'     => array('platform_model' => 'Milestone',           'platform_year' => 2009),
        'RAZR HD'       => array('platform_model' => 'Droid Razr HD',       'platform_year' => 2012),
        'Moto G'        => array('platform_model' => 'Moto G',              'platform_year' => 2013),
        'E2(4G-LTE)'    => array('platform_model' => 'Moto E (2nd Gen)',    'platform_year' => 2015),
        'G3'            => array('platform_model' => 'Moto G (3rd Gen)',    'platform_year' => 2015),
        'G (4)'         => array('platform_model' => 'Moto G (4th Gen)',    'platform_year' => 2016),
        'G (5)'         => array('platform_model' => 'Moto G5',             'platform_year' => 2017),
        'G (5) Plus'    => array('platform_model' => 'Moto G5 Plus',        'platform_year' => 2017),
        'G (5S)'        => array('platform_model' => 'Moto G5S',            'platform_year' => 2017),
        'x4'            => array('platform_model' => 'Moto X4',             'platform_year' => 2017),
        'C Plus'        => array('platform_model' => 'Moto C Plus',         'platform_year' => 2017),
        'g(6)'          => array('platform_model' => 'Moto G6',             'platform_year' => 2018),
        'g(6) play'     => array('platform_model' => 'Moto G6 Play',        'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Motorola',
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
