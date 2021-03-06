<?php
/**
 * @brief Coolpad client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Coolpad.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Apr 2018
 * @date Modification: Dec 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Coolpad client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_CoolpadClientDevice($deviceCode='') {
    $deviceList = array(
        '8298_I00'  => array('platform_model' => 'Note Lite 3',         'platform_year' => 2015),
        'Y82-520'   => array('platform_model' => 'Fengshang Y82-520',   'platform_year' => 2015),
        '3648A'     => array('platform_model' => '3648A',               'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Coolpad',
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
