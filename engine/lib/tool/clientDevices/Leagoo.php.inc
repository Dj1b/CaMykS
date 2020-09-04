<?php
/**
 * @brief Leagoo client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Leagoo.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jan 2019
 * @date Modification: Jul 2020
 * @copyright 2019 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Leagoo client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LeagooClientDevice($deviceCode='') {
    $deviceList = array(
        'Alfa 1'        => array('platform_year' => 2016),
        'Alfa 2'        => array('platform_year' => 2016),
        'Alfa 4'        => array('platform_year' => 2015),
        'Alfa 5'        => array('platform_year' => 2015),
        'Alfa 6'        => array('platform_year' => 2015),
        'Alfa 8'        => array('platform_year' => 2015),

        'Elite 1'       => array('platform_year' => 2015),
        'Elite 2'       => array('platform_year' => 2015),
        'Elite 3'       => array('platform_year' => 2015),
        'Elite 4'       => array('platform_year' => 2016),
        'Elite 5'       => array('platform_year' => 2015),
        'Elite 6'       => array('platform_year' => 2016),
        'Elite L1'      => array('platform_year' => 2015),
        'Elite Y'       => array('platform_year' => 2016),

        'Kiicaa Mix'    => array('platform_year' => 2017),
        'Kiicaa Power'  => array('platform_year' => 2017),

        'Lead 1'        => array('platform_year' => 2014),
        'Lead 2'        => array('platform_year' => 2014),
        'Lead 3'        => array('platform_year' => 2014),
        'Lead 4'        => array('platform_year' => 2014),
        'Lead 5'        => array('platform_year' => 2014),
        'Lead 6'        => array('platform_year' => 2015),
        'Lead 7'        => array('platform_year' => 2015),

        'S8_Pro'        => array('platform_model' => 'S8 Pro', 'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Leagoo',
        'platform_country'  => 'cn',
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
