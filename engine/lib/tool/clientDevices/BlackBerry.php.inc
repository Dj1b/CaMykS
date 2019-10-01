<?php
/**
 * @brief Blackberry client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/BlackBerry.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.6
 * @date Creation: Aug 2018
 * @date Modification: Sep 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Blackberry client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_BlackberryClientDevice($deviceCode='') {
    $deviceList = array(
        'BB Z30'    => array('platform_model' => 'BB Z30',  'platform_year' => 2013),

        'STH100-1'  => array('platform_model' => 'DTEK50',  'platform_year' => 2015),
        'STH100-2'  => array('platform_model' => 'DTEK50',  'platform_year' => 2015),
        'STR100-1'  => array('platform_model' => 'Leap',    'platform_year' => 2015),
        'STV100-1'  => array('platform_model' => 'Priv',    'platform_year' => 2015),
        'STV100-2'  => array('platform_model' => 'Priv',    'platform_year' => 2015),
        'STV100-3'  => array('platform_model' => 'Priv',    'platform_year' => 2015),
        'STV100-4'  => array('platform_model' => 'Priv',    'platform_year' => 2015),
        'STV100-5'  => array('platform_model' => 'Priv',    'platform_year' => 2015),
        'STV100-6'  => array('platform_model' => 'Priv',    'platform_year' => 2015),
        'BBA100-1'  => array('platform_model' => 'DTEK60',  'platform_year' => 2016),
        'BBA100-2'  => array('platform_model' => 'DTEK60',  'platform_year' => 2016),
        'BBB100-1'  => array('platform_model' => 'KeyOne',  'platform_year' => 2017),
        'BBB100-2'  => array('platform_model' => 'KeyOne',  'platform_year' => 2017),
        'BBB100-3'  => array('platform_model' => 'KeyOne',  'platform_year' => 2017),
        'BBB100-7'  => array('platform_model' => 'KeyOne',  'platform_year' => 2017),
        'BBC100-1'  => array('platform_model' => 'Aurora',  'platform_year' => 2017),
        'BBD100-1'  => array('platform_model' => 'Motion',  'platform_year' => 2017),
        'BBD100-2'  => array('platform_model' => 'Motion',  'platform_year' => 2017),
        'BBD100-6'  => array('platform_model' => 'Motion',  'platform_year' => 2017),
        'BBF100-1'  => array('platform_model' => 'Key2',    'platform_year' => 2018),
        'BBF100-2'  => array('platform_model' => 'Key2',    'platform_year' => 2018),
        'BBF100-6'  => array('platform_model' => 'Key2',    'platform_year' => 2018),
        'BBE100-4'  => array('platform_model' => 'Key2 LE', 'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Blackberry',
        'platform_country'  => 'ca',
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
