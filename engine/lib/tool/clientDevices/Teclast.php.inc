<?php
/**
 * @brief Teclast client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Nov 2020
 * @date Modification: Jan 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Teclast client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_TeclastClientDevice($deviceCode='') {
    $deviceList = array(
        /* Teclast tablets */
        'TLA002'  => array('platform_model' => 'M30', 'platform_year' => 2019, 'platform_type' => 'tablet',    'platform_format' => 'tablet'),
        'M40_EEA' => array('platform_model' => 'M40', 'platform_year' => 2020, 'platform_type' => 'tablet',    'platform_format' => 'tablet'),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Teclast',
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
