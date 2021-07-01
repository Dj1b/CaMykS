<?php
/**
 * @brief Klipad client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Apr 2020
 * @date Modification: Jun 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Klipad client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_KlipadClientDevice($deviceCode='') {
    $deviceList = array(
        /* Klipad mobiles */
        'V356'      => array('platform_model' => 'V356', 'platform_year' => 2018),
        'KL600'     => array('platform_model' => 'KL600', 'platform_year' => 2018),
        'KL601'     => array('platform_model' => 'KL601', 'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Klipad',
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
