<?php
/**
 * @brief Motorola client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Motorola.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Motorola client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MotorolaClientDevice($deviceCode='') {
    $deviceList = array(
        'XT720'     => array('platform_model' => 'Milestone XT720', ),
        'XT1022'    => array('platform_model' => 'Moto E', ),
        'XT1032'    => array('platform_model' => 'Moto G', ),
        'XT1033'    => array('platform_model' => 'Moto G', ),
        'XT1039'    => array('platform_model' => 'Moto 4G', ),
        'XT1072'    => array('platform_model' => 'Moto G 4G (2nd Gen)', ),
        'XT1092'    => array('platform_model' => 'Moto X (2nd Gen)', ),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Motorola',
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