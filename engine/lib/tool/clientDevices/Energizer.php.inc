<?php
/**
 * @brief Energizer client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Energizer.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Apr 2019
 * @date Modification: Jul 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Energizer client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_EnergizerClientDevice($deviceCode='') {
    $deviceList = array(
        '400'       => array('platform_model' => 'Energy 400',      'platform_year' => 2015),
        '400S'      => array('platform_model' => 'Energy 400S',     'platform_year' => 2016),
        'S500'      => array('platform_model' => 'Energy S500',     'platform_year' => 2017),
        'S500E'     => array('platform_model' => 'Energy S500E',    'platform_year' => 2017),
        'E520 LTE'  => array('platform_model' => 'Energy E520 LTE', 'platform_year' => 2017),
        'S550'      => array('platform_model' => 'Energy S550',     'platform_year' => 2017),
        'S600'      => array('platform_model' => 'Energy S600',     'platform_year' => 2017),
        'P550S'     => array('platform_model' => 'Power Max P550S', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Energizer',
        'platform_country'  => 'us',
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
