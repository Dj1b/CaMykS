<?php
/**
 * @brief Kyocera client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Kyocera.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Aug 2018
 * @date Modification: Dec 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Kyocera client devices list.
 * @return array
 */
function get_KyoceraClientDevices() {
    return array(
        '302KC'     => array('platform_model' => 'Digno T',             'platform_year' => 2014),
        'KC-S701'   => array('platform_model' => 'Torque KC-S701',      'platform_year' => 2015),

        'E6810'     => array('platform_model' => 'DuraForce Pro XLTE',  'platform_year' => 2016),
        'E6830'     => array('platform_model' => 'DuraForce Pro',       'platform_year' => 2016),
        'E6910'     => array('platform_model' => 'DuraForce Pro 2',     'platform_year' => 2018),
    );
}

/**
 * Return Kyocera client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_KyoceraClientDevice($deviceCode='') {
    $deviceList = get_KyoceraClientDevices();

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Kyocera',
        'platform_country'  => 'jp',
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

/**
 * Check if given device is a Kyocera know device
 * @return array
 */
function is_KyoceraKnownDevice($deviceCode='') {
    $deviceList = get_KyoceraClientDevices();
    return (array_key_exists($deviceCode, $deviceList));
}
?>
