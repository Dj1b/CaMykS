<?php
/**
 * @brief HTC client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/HTC.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Aug 2018
 * @date Modification: Jan 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return HTC client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_HTCClientDevice($deviceCode='') {
    $deviceList = array(
        'Hero'                  => array('platform_model' => 'Hero',                'platform_year' => 2009),
        'IncredibleS'           => array('platform_model' => 'Incredible S',        'platform_year' => 2011),
        'T329t'                 => array('platform_model' => 'Proto',               'platform_year' => 2012 , 'browser_title' => 'Android browser',),
        '8088;'                 => array('platform_model' => 'One Max',             'platform_year' => 2013),
        'M8Sx'                  => array('platform_model' => 'One (E8)',            'platform_year' => 2014),
        'One M8'                => array('platform_model' => 'One (M8)',            'platform_year' => 2014),
        'D820u'                 => array('platform_model' => 'Desire 820 Dual SIM', 'platform_year' => 2014),
        'Desire 626'            => array('platform_model' => 'Desire 626',          'platform_year' => 2015),
        'One M9'                => array('platform_model' => 'One M9',              'platform_year' => 2015),
        'Desire 530'            => array('platform_model' => 'Desire 530',          'platform_year' => 2016),
        '2PYB2'                 => array('platform_model' => 'Bolt',                'platform_year' => 2016),
        'Desire 628 dual sim'   => array('platform_model' => 'Desire 628 Dual SIM', 'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'HTC',
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
