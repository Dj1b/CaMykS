<?php
/**
 * @brief True client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/True.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Mar 2020
 * @date Modification: Mar 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return True client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_TrueClientDevice($deviceCode='') {
    $deviceList = array(
        /* True mobiles */
        'SMART TAB 4G Speedy 7.0"'  => array('platform_model' => 'SMART TAB 4G Speedy 7.0"', 'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'True',
        'platform_country'  => 'th',
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
