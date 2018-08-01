<?php
/**
 * @brief Vernee client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Vernee.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2018
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Vernee client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_VerneeClientDevice($deviceCode='') {
    $deviceList = array(
        'Apollo Lite'   => array('platform_year' => 2016),
        'Apollo 2'      => array('platform_year' => 2018),
        'Thor'          => array('platform_year' => 2016),
        'Thor E'        => array('platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Vernee',
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