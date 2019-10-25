<?php
/**
 * @brief Logicom client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Logicom.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: Apr 2018
 * @date Modification: Oct 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Logicom client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LogicomClientDevice($deviceCode='') {
    $deviceList = array(
        /* Logicom tablets */
        'TAB1043'       => array('platform_model' => 'Tab 1043',        'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2016),
        'M bot Tab 103' => array('platform_model' => 'M bot Tab 103',   'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2017),

        /* Logicom mobiles */
        '501'           => array('platform_model' => 'L-Element 501',   'platform_year' => 2014),
        '451'           => array('platform_model' => 'L-Element 451',   'platform_year' => 2014),
        '403'           => array('platform_model' => 'L-Element 403',   'platform_year' => 2016),
        'Le Starter L'  => array('platform_model' => 'Le Starter L',    'platform_year' => 2017),
        'Le_Hello'      => array('platform_model' => 'Le Hello',        'platform_year' => 2018),
        'Le_Hola'       => array('platform_model' => 'Le Hola',         'platform_year' => 2019),
        'Le Smooth'     => array('platform_model' => 'Le Smooth',       'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Logicom',
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
