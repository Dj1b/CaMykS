<?php
/**
 * @brief Accent client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Accent.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Mar 2019
 * @date Modification: Mar 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Accent client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AccentClientDevice($deviceCode='') {
    $deviceList = array(
        'eagle7 3g' => array('platform_model' => 'Eagle 7 3G', 'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2014),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Accent',
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
