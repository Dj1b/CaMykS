<?php
/**
 * @brief Carrefour client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Carrefour.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2019
 * @date Modification: Mar 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Carrefour client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_CarrefourClientDevice($deviceCode='') {
    $deviceList = array(
        /* Carrefour tablets */
        'CT1010'    => array('platform_model' => 'Touch Tablet CT1010',     'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2012),
        'CT820'     => array('platform_model' => 'Touch Tablet Neo 2',      'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2013),
        'CT1020W'   => array('platform_model' => 'Touch Tablet CT1020W',    'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2013),
        'CT1030'    => array('platform_model' => 'Touch Tablet CT1030',     'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2014),
        'CT726'     => array('platform_model' => 'Touch Tablet 7+',         'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2015),
        'CT1005'    => array('platform_model' => 'Touch Tablet CT1005',     'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2015),

        /* Carrefour mobiles */
        'CMB501'    => array('platform_model' => 'Smart 5', 'platform_year' => 2014),
        'CMB510'    => array('platform_model' => 'Smart 5 4G', 'platform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Carrefour',
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
