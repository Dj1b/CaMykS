<?php
/**
 * @brief Cherry client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Cherry.php.inc
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
 * Return Cherry client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_CherryClientDevice($deviceCode='') {
    $deviceList = array(
        /* Cherry mobiles */
        'Flare_J3_Lite' => array('platform_model' => 'Flare J3 Lite', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Cherry Mobiles',
        'platform_country'  => 'ph',
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
