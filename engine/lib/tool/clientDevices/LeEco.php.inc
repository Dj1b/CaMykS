<?php
/**
 * @brief LeEco client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/LeEco.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Dec 2019
 * @date Modification: Dec 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return LeEco client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LeEcoClientDevice($deviceCode='') {
    /* Update device code */
    $deviceCode = strtoupper($deviceCode);

    $deviceList = array(
        /* LeEco mobiles */
        'LEX722'    => array('platform_model' => 'Le Pro 3',  'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'LeEco',
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
