<?php
/**
 * @brief Condor client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Condor.php.inc
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
 * Return Condor client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_CondorClientDevice($deviceCode='') {
    $deviceList = array(
        'PGN521'    => array('platform_model' => 'Griffe G4 Plus',  'plateform_year' => 2015),
        'PHQ520'    => array('platform_model' => 'Griffe G5',       'plateform_year' => 2016),
        'PGN527'    => array('platform_model' => 'Plume P4 Plus',   'plateform_year' => 2017),
        'PGN528'    => array('platform_model' => 'Plume P6 Pro',    'plateform_year' => 2017),
        'PGN523'    => array('platform_model' => 'Plume P7 Plus',   'plateform_year' => 2016),
        'PGN605'    => array('platform_model' => 'Plume P8',        'plateform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Condor',
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
