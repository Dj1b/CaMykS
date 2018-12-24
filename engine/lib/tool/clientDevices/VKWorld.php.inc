<?php
/**
 * @brief VKWorld client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Lyf.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2018
 * @date Modification: Dec 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return VKWorld client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_VKWorldClientDevice($deviceCode='') {
    $deviceList = array(
        'VK-A88'    => array('platform_model' => 'VK-A88',      'platform_year' => 2014),
        'VK460'     => array('platform_model' => 'VK460',       'platform_year' => 2014),
        'VK700'     => array('platform_model' => 'VK700',       'platform_year' => 2015),
        'VK700X'    => array('platform_model' => 'VK700X',      'platform_year' => 2015),
        'VK700 Pro' => array('platform_model' => 'VK700 Pro',   'platform_year' => 2015),
        'VK6050'    => array('platform_model' => 'VK6050',      'platform_year' => 2015),
        'VK6050s'   => array('platform_model' => 'VK6050S',     'platform_year' => 2015),
        'VK6735'    => array('platform_model' => 'VK6735',      'platform_year' => 2015),
        'VK700-Max' => array('platform_model' => 'VK700-Max',   'platform_year' => 2016),
        'VK800X'    => array('platform_model' => 'VK800X',      'platform_year' => 2016),
        'VK6735X'   => array('platform_model' => 'VK6735X',     'platform_year' => 2016),

        'Mix Plus'  => array('platform_model' => 'Mix Plus',    'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'VKWorld',
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
