<?php
/**
 * @brief ZTE client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/ZTE.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: May 2018
 * @date Modification: Dec 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return ZTE client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_ZTEClientDevice($deviceCode='') {
    $deviceList = array(
        'Z7'            => array('platform_model' => 'Nubia 27',        'platform_year' => 2014),
        'BLADE V7 LITE' => array('platform_model' => 'Blade V7 Lite',   'platform_year' => 2016),
        'Z833'          => array('platform_model' => 'Avid Trio',       'platform_year' => 2016),
        'A2017G'        => array('platform_model' => 'Axon 7',          'platform_year' => 2016),
        'Blade A452'    => array('platform_model' => 'Blade A452',      'platform_year' => 2016),
        'BLADE V9'      => array('platform_model' => 'Blade V9',        'platform_year' => 2018),
        'Z559DL'        => array('platform_model' => 'Blade T2',        'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'ZTE',
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
