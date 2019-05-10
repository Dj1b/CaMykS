<?php
/**
 * @brief Lava client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Lava.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jul 2018
 * @date Modification: May 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Lava client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LavaClientDevice($deviceCode='') {
    $deviceList = array(
        'iris402'   => array('platform_model' => 'Iris 402',    'platform_year' => 2013),
        'iris349i'  => array('platform_model' => 'Iris 349i',   'platform_year' => 2014),
        'iris405+'  => array('platform_model' => 'Iris 405+',   'platform_year' => 2014),
        'a48_8gb'   => array('platform_model' => 'A48 (8GB)',   'platform_year' => 2016),
        'z50'       => array('platform_model' => 'Z50',         'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Lava',
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
