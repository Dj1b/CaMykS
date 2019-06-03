<?php
/**
 * @brief Wieppo client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Wieppo.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2019
 * @date Modification: May 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Wieppo client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_WieppoClientDevice($deviceCode='') {
    $deviceList = array(
        'S5'        => array('platform_model' => 'S5',      'platform_year' => 2017),
        'S6'        => array('platform_model' => 'S6',      'platform_year' => 2017),
        'S6 Lite'   => array('platform_model' => 'S6 Lite', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Wieppo',
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
