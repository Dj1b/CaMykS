<?php
/**
 * @brief Infinix client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Infinix.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.5
 * @date Creation: Feb 2019
 * @date Modification: Sep 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Infinix client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_InfinixClientDevice($deviceCode='') {
    $deviceList = array(
        /* Hot serie */
        'X551'      => array('platform_model' => 'Hot Note',    'platform_year' => 2015),
        'X559'      => array('platform_model' => 'Hot 5 Lite',  'platform_year' => 2017),
        'X559C'     => array('platform_model' => 'Hot 5',       'platform_year' => 2017),
        'X572'      => array('platform_model' => 'Note 4',      'platform_year' => 2017),
        'X606D'     => array('platform_model' => 'Hot 6',       'platform_year' => 2018),
        'X608'      => array('platform_model' => 'Hot 6 Pro',   'platform_year' => 2018),

        /* Smart serie */
        'X5515'     => array('platform_model' => 'Smart 2',     'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Infinix',
        'platform_country'  => 'hk',
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
