<?php
/**
 * @brief T-Mobile client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Apr 2019
 * @date Modification: Feb 2021
 * @copyright 2019 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return T-Mobile client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_TMobileClientDevice($deviceCode='') {
    $deviceList = array(
        'G1'        => array('platform_model' => 'G1',          'platform_year' => 2008),
        'G2_Touch'  => array('platform_model' => 'G2 Touch',    'platform_year' => 2009),
        'REVVL 2'   => array('platform_model' => 'Revvl 2',     'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'T-Mobile',
        'platform_country'  => 'de',
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
