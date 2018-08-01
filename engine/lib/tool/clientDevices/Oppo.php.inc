<?php
/**
 * @brief Oppo client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Oppo.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2018
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Oppo client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_OppoClientDevice($deviceCode='') {
    $deviceList = array(
        '1201'      => array('platform_model' => 'Neo 5',       'platform_year' => 2015),
        'F1f'       => array('platform_model' => 'F1',          'platform_year' => 2016),
        'A37fw'     => array('platform_model' => 'A37fw',       'platform_year' => 2017),
        'CPH1861'   => array('platform_model' => 'Realme 1',    'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Oppo',
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
