<?php
/**
 * @brief Logicom client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Logicom.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2018
 * @date Modification: May 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Logicom client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LogicomClientDevice($deviceCode='') {
    $deviceList = array(
        '501' => array('platform_model' => 'L-Element 501', 'platform_year' => 2014),
        '451' => array('platform_model' => 'L-Element 451', 'platform_year' => 2014),
        '403' => array('platform_model' => 'L-Element 403', 'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Logicom',
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