<?php
/**
 * @brief Acer client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Acer.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Apr 2018
 * @date Modification: Mar 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Acer client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AcerClientDevice($deviceCode='') {
    $deviceList = array(
        /* Acer tablets */
        'A500'      => array('platform_model' => 'Iconia Tab A500',     'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),

        /* Acer mobiles */
        'Z130'      => array('platform_model' => 'Liquid Z3',           'platform_year' => 2013),
        'T03'       => array('platform_model' => 'Liquid Z630',         'platform_year' => 2015),
        'T04'       => array('platform_model' => 'Liquid Z630S',        'platform_year' => 2016),
        'T08'       => array('platform_model' => 'Liquid Zest Plus',    'platform_year' => 2016),
        'B3-A40'    => array('platform_model' => 'Iconia One 10',       'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Acer',
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
