<?php
/**
 * @brief MaraPhones client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2021
 * @date Modification: Sep 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return MaraPhones client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MaraPhonesClientDevice($deviceCode='') {
    $deviceList = array(
        'Z1' => array('platform_model' => '20 Pro 5G', 'platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Mara Phones',
        'platform_country'  => 'rw',
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
