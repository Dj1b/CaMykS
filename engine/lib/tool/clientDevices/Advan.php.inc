<?php
/**
 * @brief Advan client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Advan.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Aug 2019
 * @date Modification: Jan 2020
 * @copyright 2019 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Advan client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AdvanClientDevice($deviceCode='') {
    $deviceList = array(
        'S50H'      => array('platform_model' => 'S50H',    'platform_year' => 2017),
        '5041'      => array('platform_model' => 'S50K',    'platform_year' => 2017),
        '5061'      => array('platform_model' => 'i5C',     'platform_year' => 2017),
        '5062'      => array('platform_model' => 'S5E',     'platform_year' => 2017),
        'S5E_NXT'   => array('platform_model' => 'S5E NXT', 'platform_year' => 2017),
        'i5K'       => array('platform_model' => 'G1 Pro',  'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Advan',
        'platform_country'  => 'id',
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
