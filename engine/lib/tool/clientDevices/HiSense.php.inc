<?php
/**
 * @brief HiSense client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/HiSense.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2018
 * @date Modification: Oct 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return HiSense client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_HiSenseClientDevice($deviceCode='') {
    $deviceList = array(
        'L675'      => array('platform_model' => 'L675',                'platform_year' => 2016),
        'L678'      => array('platform_model' => 'Staraddict 5',        'platform_year' => 2016),
        'F17 Pro'   => array('platform_model' => 'Infinity F17 Pro',    'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Hisense',
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
