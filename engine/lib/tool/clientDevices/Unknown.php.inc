<?php
/**
 * @brief Unknown client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2021
 * @date Modification: Jan 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Unknown client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_UnknownClientDevice($deviceCode='') {
    $deviceList = array(
        'Phh-Treble'            => array('platform_model' => 'Flashed mobile with Phh-Treble generic ROM'),
        'Unspecified Device'    => array('platform_model' => 'Unspecified Device'),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => '(Unknown)',
        'platform_country'  => '',
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
