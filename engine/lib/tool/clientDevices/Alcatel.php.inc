<?php
/**
 * @brief Alcatel client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Alcatel.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Alcatel client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AlcatelClientDevice($deviceCode='') {
    $deviceList = array(
        '4015D' => array('platform_model' => 'One Touch Idol 3',        'plateform_year' => 2014),
        '5050X' => array('platform_model' => 'One Touch Pop S3',        'plateform_year' => 2014),
        '5070D' => array('platform_model' => 'One Touch Pop Star 4G',   'plateform_year' => 2015),
        '5070X' => array('platform_model' => 'One Touch Pop Star 4G',   'plateform_year' => 2015),
        '6045Y' => array('platform_model' => 'One Touch Pop C1',        'plateform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Alcatel',
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
