<?php
/**
 * @brief Wortmann client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Wortmann.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2019
 * @date Modification: Mar 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Wortmann client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_WortmannClientDevice($deviceCode='') {
    $deviceList = array(
        '1001'  => array('platform_model' => 'Terra Pad 1001',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2012),
        '1002'  => array('platform_model' => 'Terra Pad 1002',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2013),
        '1003'  => array('platform_model' => 'Terra Pad 1003',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2014),
        '1004'  => array('platform_model' => 'Terra Pad 1004',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2016),
        '1005'  => array('platform_model' => 'Terra Pad 1005',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Wortmann',
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
