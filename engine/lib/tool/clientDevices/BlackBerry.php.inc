<?php
/**
 * @brief Blackberry client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/BlackBerry.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Aug 2018
 * @date Modification: Sep 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Blackberry client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_BlackberryClientDevice($deviceCode='') {
    $deviceList = array(
        'BBB100-2'  => array('platform_model' => 'KeyOne',  'platform_year' => 2017),
        'BBF100-1'  => array('platform_model' => 'Key2',    'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Blackberry',
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
