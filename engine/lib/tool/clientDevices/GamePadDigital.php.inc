<?php
/**
 * @brief GamePad Digital client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/GamePadDigital.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2020
 * @date Modification: Jan 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return GamePad Digital client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_GamePadDigitalClientDevice($deviceCode='') {
    $deviceList = array(
        /* GamePadDigital game consoles */
        'XD'        => array('platform_model' => 'XD',      'platform_year' => 2015),
        'XD Plus'   => array('platform_model' => 'XD Plus', 'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'GamePad Digital',
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
