<?php
/**
 * @brief Xtouch client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Xtouch.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2019
 * @date Modification: Oct 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Xtouch client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_XtouchClientDevice($deviceCode='') {
    $deviceList = array(
        /* Xtouch mobiles */
        'A4'        => array('platform_year' => 2018),
        'E4'        => array('platform_year' => 2018),
        'X10'       => array('platform_year' => 2018),
        'UNIX_PRO'  => array('platform_model' => 'Unix Pro', 'platform_year' => 2017),
        'A2 Plus'   => array('platform_year' => 2017),
        'A2'        => array('platform_year' => 2016),
        'A2 Air'    => array('platform_year' => 2016),
        'Unix'      => array('platform_year' => 2016),
        'T3'        => array('platform_year' => 2016),
        'R3 LTE'    => array('platform_year' => 2016),
        'E1'        => array('platform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Xtouch',
        'platform_country'  => 'cn',
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
