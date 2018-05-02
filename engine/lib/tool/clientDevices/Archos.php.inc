<?php
/**
 * @brief Archos client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Archos.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Archos client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_ArchosClientDevice($deviceCode='') {
    $deviceList = array(
        '45BHE'=> array('platform_model' => 'Helium 45b',   'plateform_year' => 2015),
        '50BHE'=> array('platform_model' => 'Helium 50b',   'plateform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Archos',
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
