<?php
/**
 * @brief Mecool client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Mecool.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: May 2019
 * @date Modification: May 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Mecool client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MecoolClientDevice($deviceCode='') {
    $deviceList = array(
        'M8S PRO L'    => array('platform_model' => 'M8S PRO L', 'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Mecool',
        'platform_model'    => $deviceCode,
        'platform_type'     => 'tvset', // TV Box
        'platform_format'   => 'desktop',
    );

    /* Check if device is a known device. */
    if (!array_key_exists($deviceCode, $deviceList))
        return $result;

    /* Return result. */
    return array_merge($result, $deviceList[$deviceCode]);
}
?>
