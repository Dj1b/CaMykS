<?php
/**
 * @brief Asus client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Asus.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Asus client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AsusClientDevice($deviceCode='') {
    $deviceList = array(
        /* Asus tablets */
        'K007'      => array('platform_model' => 'MeMO Pad 7',      'platform_type' => 'tablet',    'platform_format' => 'tablet',  'plateform_year' => 2015),
        'K01E'      => array('platform_model' => 'MeMO Pad',        'platform_type' => 'tablet',    'platform_format' => 'tablet',  'plateform_year' => 2014),
        'ME173X'    => array('platform_model' => 'MeMO Pad HD 7',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'plateform_year' => 2013),
        'P01MA'     => array('platform_model' => 'Zen Pad 8',       'platform_type' => 'tablet',    'platform_format' => 'tablet',  'plateform_year' => 2015),

        /* Asus phones */
        'Z00ED'     => array('platform_model' => 'Zenfon 2',        'plateform_year' => 2015),
        'Z00ED'     => array('platform_model' => 'Zenfon 2',        'plateform_year' => 2015),
        'Z00LD'     => array('platform_model' => 'Zenfon 2 Laser',  'plateform_year' => 2015),
        'X00DD'     => array('platform_model' => 'Zenfon 3 Max',    'plateform_year' => 2016),
        'X008D'     => array('platform_model' => 'Zenfon 3 Max',    'plateform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Asus',
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
