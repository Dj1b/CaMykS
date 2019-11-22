<?php
/**
 * @brief Fairphone client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Fairphone.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Nov 2019
 * @date Modification: Nov 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Fairphone client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_FairphoneClientDevice($deviceCode='') {
    $deviceList = array(
        /* Fairphone mobiles */
        'FP1'   => array('platform_model' => 'FP1',     'platform_year' => 2013),
        'FP1U'  => array('platform_model' => 'FP1U1',   'platform_year' => 2014),
        'FP2'   => array('platform_model' => 'FP2',     'platform_year' => 2015),
        'FP3'   => array('platform_model' => 'FP3',     'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Fairphone',
        'platform_country'  => 'nl',
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
