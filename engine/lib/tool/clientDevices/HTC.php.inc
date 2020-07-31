<?php
/**
 * @brief HTC client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/HTC.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.20
 * @date Creation: Aug 2018
 * @date Modification: Jul 2020
 * @copyright 2018 - 2020 CaMykS Team
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
        'dream'                 => array('platform_model' => 'Dream',               'platform_year' => 2008),
        'bahamas'               => array('platform_model' => 'Bahamas',             'platform_year' => 2009),
        'Hero'                  => array('platform_model' => 'Hero',                'platform_year' => 2009),
        'TATTOO A3288'          => array('platform_model' => 'Tattoo',              'platform_year' => 2009),
        'ADR6300'               => array('platform_model' => 'Incredible',          'platform_year' => 2010),
        'Legend'                => array('platform_model' => 'Legend',              'platform_year' => 2010),
        'IncredibleS'           => array('platform_model' => 'Incredible S',        'platform_year' => 2011),
        'Explorer A310e'        => array('platform_model' => 'Explorer A310e',      'platform_year' => 2011),
        'T329t'                 => array('platform_model' => 'Proto',               'platform_year' => 2012 , 'browser_title' => 'Android browser',),
        '8088;'                 => array('platform_model' => 'One Max',             'platform_year' => 2013),
        'M8Sx'                  => array('platform_model' => 'One (E8)',            'platform_year' => 2014),
        'One M8'                => array('platform_model' => 'One (M8)',            'platform_year' => 2014),
        'One mini 2'            => array('platform_model' => 'One mini 2',          'platform_year' => 2014),
        'D820u'                 => array('platform_model' => 'Desire 820 Dual SIM', 'platform_year' => 2014),
        'Desire 626'            => array('platform_model' => 'Desire 626',          'platform_year' => 2015),
        '2PQ93'                 => array('platform_model' => 'One A9',              'platform_year' => 2015),
        'One M9'                => array('platform_model' => 'One M9',              'platform_year' => 2015),
        'Desire 530'            => array('platform_model' => 'Desire 530',          'platform_year' => 2016),
        '2PYB2'                 => array('platform_model' => 'Bolt',                'platform_year' => 2016),
        'Desire 628 dual sim'   => array('platform_model' => 'Desire 628 Dual SIM', 'platform_year' => 2016),
        'D10i'                  => array('platform_model' => 'Desire 10 Pro',       'platform_year' => 2016),
        'Desire 650'            => array('platform_model' => 'Desire 650',          'platform_year' => 2017),
        'U-3u'                  => array('platform_model' => 'U11',                 'platform_year' => 2017),
        'U11'                   => array('platform_model' => 'U11',                 'platform_year' => 2017),
        'U11 plus'              => array('platform_model' => 'U11+',                'platform_year' => 2017),
        '2Q4D100'               => array('platform_model' => 'U11+',                'platform_year' => 2017),
        'U Ultra'               => array('platform_model' => 'U Ultra',             'platform_year' => 2017),
        '2Q4R100'               => array('platform_model' => 'U11 Eyes',            'platform_year' => 2018),
        'Desire 12+'            => array('platform_model' => 'Desire 12+',          'platform_year' => 2018),
        'U12+'                  => array('platform_model' => 'U12+',                'platform_year' => 2018),
        'U12 life'              => array('platform_model' => 'U12 life',            'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'HTC',
        'platform_country'  => 'tw',
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
