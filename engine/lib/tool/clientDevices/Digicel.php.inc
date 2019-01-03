<?php
/**
 * @brief Digicel client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Digicel.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2018
 * @date Modification: Dec 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Digicel client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_DigicelClientDevice($deviceCode='') {
    $deviceList = array(
        'DL750'     => array('platform_year' => 2014),
        'DL755'     => array('platform_year' => 2014),
        'DL800'     => array('platform_year' => 2014),
        'DL810'     => array('platform_year' => 2014),
        'DL900'     => array('platform_year' => 2014),
        'DL910'     => array('platform_year' => 2015),
        'DL1000'    => array('platform_year' => 2015),
        'DL1'       => array('platform_year' => 2016),
        'DL1plus'   => array('platform_model' => 'DL1 Plus',    'platform_year' => 2016),
        'DL 1 lite' => array('platform_model' => 'DL1 Lite',    'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Digicel',
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
