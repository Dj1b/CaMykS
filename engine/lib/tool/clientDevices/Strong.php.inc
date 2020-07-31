<?php
/**
 * @brief Strong client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Strong.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jul 2020
 * @date Modification: Jul 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Strong client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_StrongClientDevice($deviceCode='') {
    $deviceList = array(
        /* Strong mobiles */
        'SN6B6BL_EU012'  => array('platform_model' => 'SRT 2022', 'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Strong',
        'platform_country'  => 'de',
        'platform_model'    => $deviceCode,
        'platform_type'     => 'tvset',
        'platform_format'   => 'desktop',
    );

    /* Check if device is a known device. */
    if (!array_key_exists($deviceCode, $deviceList))
        return $result;

    /* Return result. */
    return array_merge($result, $deviceList[$deviceCode]);
}
?>
