<?php
/**
 * @brief Verykool client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Verykool.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2019
 * @date Modification: Jun 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Verykool client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_VerykoolClientDevice($deviceCode='') {
    $deviceList = array(
        'LUNA_II'   => array('platform_model' => 'Luna II', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Verykool',
        'platform_country'  => 'us',
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
