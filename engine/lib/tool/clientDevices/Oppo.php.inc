<?php
/**
 * @brief Oppo client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Oppo.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: Jul 2018
 * @date Modification: Jun 2019
 * @copyright 2018 - 2019 CaMykS Team
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
        'R9s'       => array('platform_model' => 'R9S',         'platform_year' => 2016),
        'CPH1607'   => array('platform_model' => 'R9s',         'platform_year' => 2016),
        'A37f'      => array('platform_model' => 'A37f',        'platform_year' => 2016),
        'A37fw'     => array('platform_model' => 'A37fw',       'platform_year' => 2017),
        'CPH1837'   => array('platform_model' => 'A3',          'platform_year' => 2018),
        'CPH1729'   => array('platform_model' => 'A83',         'platform_year' => 2018),
        'CPH1803'   => array('platform_model' => 'A3s',         'platform_year' => 2018),
        'CPH1819'   => array('platform_model' => 'F7',          'platform_year' => 2018),
        'CPH1861'   => array('platform_model' => 'Realme 1',    'platform_year' => 2018),
        'RMX1811'   => array('platform_model' => 'Realme C1',   'platform_year' => 2018),
        'RMX1825'   => array('platform_model' => 'Realme 3',    'platform_year' => 2019),
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
