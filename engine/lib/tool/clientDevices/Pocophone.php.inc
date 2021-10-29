<?php
/**
 * @brief Pocophone (Xiaomi subsidiary) client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: Feb 2020
 * @date Modification: Sep 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Pocophone client device known list.
 * @return array
 */
function get_PocophoneClientDevices() {
    return array(
        'f1'            => array('platform_model' => 'F1',      'platform_year' => 2018),
        'f2 pro'        => array('platform_model' => 'F2 Pro',  'platform_year' => 2020),
        'm2004j19pi'    => array('platform_model' => 'M2',      'platform_year' => 2020),
        'm2007j20cg'    => array('platform_model' => 'X3',      'platform_year' => 2020),
        'm2007j20ci'    => array('platform_model' => 'X3',      'platform_year' => 2020),
        'm2010j19cg'    => array('platform_model' => 'M3',      'platform_year' => 2020),
        'm2012k11ag'    => array('platform_model' => 'F3',      'platform_year' => 2021),
        'm2102j20sg'    => array('platform_model' => 'X3 Pro',  'platform_year' => 2021),
        'x3 pro'        => array('platform_model' => 'X3 Pro',  'platform_year' => 2021),
    );
}

/**
 * Return Pocophone client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_PocophoneClientDevice($deviceCode='') {
    $deviceList = get_PocophoneClientDevices();

    /* Check for returning list */
    if ($deviceCode === false)
        return $deviceList;
    else
        $deviceCode = strtolower($deviceCode);

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Pocophone',
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

/**
 * Check if given device is a Pocophone known device.
 * @return array
 */
function is_PocophoneKnownDevice($deviceCode='') {
    $deviceList = get_PocophoneClientDevices();
    return (array_key_exists($deviceCode, $deviceList));
}
?>
