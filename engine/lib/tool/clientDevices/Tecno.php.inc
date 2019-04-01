<?php
/**
 * @brief Tecno client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Tecno.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Oct 2018
 * @date Modification: Mar 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Tecno client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_TecnoClientDevice($deviceCode='') {
    $deviceList = array(
        'K7'        => array('platform_model' => 'Spark',           'platform_year' => 2017),
        'K9'        => array('platform_model' => 'Spark Plus',      'platform_year' => 2017),
        'R6'        => array('platform_model' => 'R6',              'platform_year' => 2017),
        'W3'        => array('platform_model' => 'W3',              'platform_year' => 2017),
        'KA7'       => array('platform_model' => 'Spark 2',         'platform_year' => 2018),
        'LA7'       => array('platform_model' => 'Pouvoir 2',       'platform_year' => 2018),
        'LA7 Pro'   => array('platform_model' => 'Pouvoir 2 Pro',   'platform_year' => 2018),
        'Camon CX'  => array('platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Tecno',
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
