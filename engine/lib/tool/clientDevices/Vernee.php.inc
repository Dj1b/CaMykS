<?php
/**
 * @brief Vernee client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Vernee.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2018
 * @date Modification: Apr 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Vernee client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_VerneeClientDevice($deviceCode='') {
    $deviceList = array(
        'Apollo 2'      => array('platform_year' => 2018),
        'Apollo X'      => array('platform_year' => 2017),
        'M5'            => array('platform_year' => 2017),
        'Mars pro'      => array('platform_model'=> 'Mars Pro', 'platform_year' => 2017),
        'Thor E'        => array('platform_year' => 2017),
        'Thor Plus'     => array('platform_year' => 2017),
        'Apollo Lite'   => array('platform_year' => 2016),
        'Thor'          => array('platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Vernee',
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
