<?php
/**
 * @brief Karbonn client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Karbonn.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2018
 * @date Modification: Jun 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Karbonn client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_KarbonnClientDevice($deviceCode='') {
    $deviceList = array(
        'A96' => array('platform_model' => 'A96',   'platform_year' => 2014),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Karbonn',
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