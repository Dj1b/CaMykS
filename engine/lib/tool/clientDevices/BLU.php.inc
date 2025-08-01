<?php
/**
 * @brief BLU client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2025
 * @date Modification: Apr 2025
 * @copyright 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Artizlee client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_BLUClientDevice($deviceCode='') {
    /* Update device code */
    $deviceCode = strtoupper($deviceCode);

    $deviceList = array(
        /* BLU mobiles */
        'C5 2019'    => array('platform_model' => 'C5',  'platform_year' => 2029),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'BLU',
        'platform_country'  => 'us',
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
