<?php
/**
 * @brief Konrow client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Oct 2018
 * @date Modification: Oct 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Konrow client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_KonrowClientDevice($deviceCode='') {
    $deviceList = array(
        'BIGCOOL'   => array('platform_model' => 'BigCool', 'platform_year' => 2016),
        'Just5'     => array('platform_model' => 'Just5',   'platform_year' => 2017),
        'EASY5'     => array('platform_model' => 'Easy5',   'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Konrow',
        'platform_country'  => 'fr',
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
