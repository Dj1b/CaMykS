<?php
/**
 * @brief Vodafone client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Vodafone.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Mar 2019
 * @date Modification: Jun 2020
 * @copyright 2019 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Vodafone client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_VodafoneClientDevice($deviceCode='') {
    $deviceList = array(
        /* Vodafone tablets */
        'VF-1397'   => array('platform_model' => 'Tab Speed 6', 'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2015),

        /* Vodafone mobiles */
        '890N'      => array('platform_model' => 'Smart 4 Turbo', 'platform_year' => 2014),
        'VF685'     => array('platform_model' => 'Smart 4 Mini', 'platform_year' => 2014),
        'VF695'     => array('platform_model' => 'Smart first 6', 'platform_year' => 2014),

    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Vodafone',
        'platform_country'  => 'gb',
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
