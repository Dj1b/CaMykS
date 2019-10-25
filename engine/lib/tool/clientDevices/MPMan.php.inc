<?php
/**
 * @brief MPMan client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/MPMan.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2019
 * @date Modification: Oct 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return MPMan client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MPManClientDevice($deviceCode='') {
    $deviceList = array(
        /* MPMan tablets */
        'MP11 COTA' => array('platform_model' => 'MP11 Octa',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'MPMan',
        'platform_country'  => 'kr',
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
