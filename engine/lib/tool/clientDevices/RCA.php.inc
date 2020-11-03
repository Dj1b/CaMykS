<?php
/**
 * @brief RCA client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2020
 * @date Modification: Oct 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return RCA client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_RCAClientDevice($deviceCode='') {
    $deviceList = array(
        /* RCA mobiles */
        'RCT6203W46'    => array('platform_model' => 'Pro10', 'platform_year' => 2014, 'platform_type' => 'tablet',    'platform_format' => 'tablet',),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'RCA',
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
