<?php
/**
 * @brief Blackview client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Blackview.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jul 2018
 * @date Modification: Nov 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Blackview client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_BlackviewClientDevice($deviceCode='') {
    $deviceList = array(
        '9000Pro-F' => array('platform_model' => '9000Pro F',   'platform_year' => 2017),
        '8000Pro'   => array('platform_model' => '8000Pro',     'platform_year' => 2017),
        '9500'      => array('platform_model' => '9500',        'platform_year' => 2018),
        '9500Pro'   => array('platform_model' => '9500Pro',     'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Blackview',
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
