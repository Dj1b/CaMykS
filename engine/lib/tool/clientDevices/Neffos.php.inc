<?php
/**
 * @brief Neffos client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Neffos.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Mar 2019
 * @date Modification: Jun 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Neffos client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_NeffosClientDevice($deviceCode='') {
    $deviceList = array(
        /* C-Series mobiles */
        'C5'        => array('platform_model' => 'C5',      'platform_year' => 2016),
        'C5 Max'    => array('platform_model' => 'C5 Max',  'platform_year' => 2016),
        'C5A'       => array('platform_model' => 'C5A',     'platform_year' => 2018),
        'C5s'       => array('platform_model' => 'C5s',     'platform_year' => 2018),
        'C7'        => array('platform_model' => 'C7',      'platform_year' => 2018),
        'C7A'       => array('platform_model' => 'C7A',     'platform_year' => 2018),
        'C9'        => array('platform_model' => 'C9',      'platform_year' => 2018),
        'C9A'       => array('platform_model' => 'C9A',     'platform_year' => 2018),

        /* P-Series mobiles */
        'P1'        => array('platform_model' => 'P1',      'platform_year' => 2018),

        /* Y-Series mobiles */
        'Y5'        => array('platform_model' => 'Y5',      'platform_year' => 2016),
        'Y5L'       => array('platform_model' => 'Y5L',     'platform_year' => 2016),
        'Y50'       => array('platform_model' => 'Y50',     'platform_year' => 2016),
        'Y5i'       => array('platform_model' => 'Y5i',     'platform_year' => 2018),
        'Y5s'       => array('platform_model' => 'Y5s',     'platform_year' => 2018),
        'Y6'        => array('platform_model' => 'Y6',      'platform_year' => 2018),

        /* X-Series mobiles */
        'X1'        => array('platform_model' => 'X1',      'platform_year' => 2017),
        'X1 Lite'   => array('platform_model' => 'X1 Lite', 'platform_year' => 2017),
        'X1 Max'    => array('platform_model' => 'X1 Max',  'platform_year' => 2017),
        'X9'        => array('platform_model' => 'X1',      'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Neffos',
        'platform_country'  => 'fr',
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
