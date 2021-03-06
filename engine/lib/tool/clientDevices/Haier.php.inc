<?php
/**
 * @brief Haier client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Haier.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Mar 2019
 * @date Modification: Jun 2020
 * @copyright 2019 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Haier client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_HaierClientDevice($deviceCode='') {
    $deviceList = array(
        /* Haier tablets */
        'CDP7TAB4C8'    => array('platform_model' => 'CDisplay E701', 'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2014),

        /* Haier mobiles */
        'G30'           => array('platform_model' => 'Voyage G30', 'platform_year' => 2015),
        'HM-G552-FL'    => array('platform_model' => 'G7', 'platform_year' => 2017),
        'HM-I560-FL'    => array('platform_model' => 'G7s', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Haier',
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
