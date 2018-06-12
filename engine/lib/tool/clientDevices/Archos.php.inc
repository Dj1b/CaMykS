<?php
/**
 * @brief Archos client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Archos.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Apr 2018
 * @date Modification: Jun 2018
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
        '45BHE'                 => array('platform_model' => 'Helium 45b',          'platform_year' => 2015),
        '50BHE'                 => array('platform_model' => 'Helium 50b',          'platform_year' => 2015),
        '50e Neon'              => array('platform_model' => '50e Neon',            'platform_year' => 2016),
        
        'Access 40 3G'          => array('platform_model' => 'Access 40 3G',        'platform_year' => 2017),
        'Access 45 3G'          => array('platform_model' => 'Access 45 3G',        'platform_year' => 2017),
        'Access 50 Color 3G'    => array('platform_model' => 'Access 50 Color 3G',  'platform_year' => 2017),
        'Access 50 4G'          => array('platform_model' => 'Access 50 4G',        'platform_year' => 2017),
        'Access 55 3G'          => array('platform_model' => 'Access 55 3G',        'platform_year' => 2017),
        'Sense 47 X'            => array('platform_model' => 'Sense 47X',           'platform_year' => 2017),
        'Sense 50 DC'           => array('platform_model' => 'Sense 50DC',          'platform_year' => 2017),
        'Sense 50 X'            => array('platform_model' => 'Sense 50X',           'platform_year' => 2017),
        'Sense 55 S'            => array('platform_model' => 'Sense 50S',           'platform_year' => 2017),
        'Sense 55 DC'           => array('platform_model' => 'Sense 55DC',          'platform_year' => 2017),
        'Core 50'               => array('platform_model' => 'Core 50',             'platform_year' => 2017),
        'Core 50 Lite'          => array('platform_model' => 'Core 50 Lite',        'platform_year' => 2017),
        'Core 50P'              => array('platform_model' => 'Core 50P',            'platform_year' => 2017),
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
