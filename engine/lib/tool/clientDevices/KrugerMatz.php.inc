<?php
/**
 * @brief Krüger & Matz client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/KrugerMatz.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jul 2019
 * @date Modification: Jul 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return KrugerMatz client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_KrugerMatzClientDevice($deviceCode='') {
    $deviceList = array(
        'flow'  => array('platform_model' => 'Flow', 'platform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Krüger & Matz',
        'platform_country'  => 'pl',
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
