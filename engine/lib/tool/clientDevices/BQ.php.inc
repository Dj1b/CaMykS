<?php
/**
 * @brief BQ client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/BQ.php.inc
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
 * Return BQ client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_BQClientDevice($deviceCode='') {
    $deviceList = array(
        /* BQ tablets */
        'Aquaris E10'       => array('platform_model' => 'Aquaris E10',         'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'Aquaris M10'       => array('platform_model' => 'Aquaris M10',         'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'Aquaris M10 FHD'   => array('platform_model' => 'Aquaris M10 FHD',     'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),

        '7010G'             => array('platform_model' => 'Max',                 'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        '1008G'             => array('platform_model' => 'Grace',               'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        '7021G'             => array('platform_model' => 'Hit',                 'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        '7008G'             => array('platform_model' => 'Clarion',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        '7022G'             => array('platform_model' => 'Canion',              'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        '7050G'             => array('platform_model' => 'Malta',               'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        '9052G'             => array('platform_model' => '9052G',               'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),

        /* BQ phones */
        'Aquaris 3.5'       => array('platform_model' =>  'Aquaris 3.5',        'platform_year' => 2013),
        'Aquaris 4'         => array('platform_model' =>  'Aquaris 4',          'platform_year' => 2013),
        'Aquaris 4.5'       => array('platform_model' =>  'Aquaris 4.5',        'platform_year' => 2014),
        'Aquaris E4'        => array('platform_model' =>  'Aquaris E4',         'platform_year' => 2014),
        'Aquaris E5'        => array('platform_model' =>  'Aquaris E5',         'platform_year' => 2014),
        'Aquaris E5 FHD'    => array('platform_model' =>  'Aquaris E5 FHD',     'platform_year' => 2014),
        'Aquaris E6'        => array('platform_model' =>  'Aquaris E6',         'platform_year' => 2014),
        'Aquaris 5'         => array('platform_model' =>  'Aquaris 5',          'platform_year' => 2015),
        'Aquaris A4.5'      => array('platform_model' =>  'Aquaris A4.5',       'platform_year' => 2015),
        'Aquaris E4.5'      => array('platform_model' =>  'Aquaris E4.5',       'platform_year' => 2015),
        'Aquaris M'         => array('platform_model' =>  'Aquaris M',          'platform_year' => 2015),
        'Aquaris M4.5'      => array('platform_model' =>  'Aquaris M4.5',       'platform_year' => 2015),
        'Aquaris M5'        => array('platform_model' =>  'Aquaris M5',         'platform_year' => 2015),
        'Aquaris M5.5'      => array('platform_model' =>  'Aquaris M5.5',       'platform_year' => 2015),
        'Aquaris X5'        => array('platform_model' =>  'Aquaris X5',         'platform_year' => 2015),
        'Aquaris X5 Plus'   => array('platform_model' =>  'Aquaris X5 Plus',    'platform_year' => 2015),
        'Aquaris M8'        => array('platform_model' =>  'Aquaris M8',         'platform_year' => 2016),
        'Aquaris U'         => array('platform_model' =>  'Aquaris U',          'platform_year' => 2016),
        'Aquaris U Lite'    => array('platform_model' =>  'Aquaris U Lite',     'platform_year' => 2016),
        'Aquaris U Plus'    => array('platform_model' =>  'Aquaris U Plus',     'platform_year' => 2016),
        'Aquaris U2'        => array('platform_model' =>  'Aquaris U2',         'platform_year' => 2017),
        'Aquaris U2 Lite'   => array('platform_model' =>  'Aquaris U2 Lite',    'platform_year' => 2017),
        'Aquaris V'         => array('platform_model' =>  'Aquaris V',          'platform_year' => 2017),
        'Aquaris V Plus'    => array('platform_model' =>  'Aquaris V Plus',     'platform_year' => 2017),
        'Aquaris X'         => array('platform_model' =>  'Aquaris X',          'platform_year' => 2017),
        'Aquaris X Pro'     => array('platform_model' =>  'Aquaris X Pro',      'platform_year' => 2017),
        'Aquaris X2'        => array('platform_model' =>  'Aquaris X2',         'platform_year' => 2018),
        'Aquaris X2 Pro'    => array('platform_model' =>  'Aquaris X2 Pro',     'platform_year' => 2018),

        '4010'              => array('platform_model' =>  'Aspen',              'platform_year' => 2015),
        '1045G'             => array('platform_model' =>  'Orion',              'platform_year' => 2016),
        '4026'              => array('platform_model' =>  'Up',                 'platform_year' => 2016),
        '5022'              => array('platform_model' =>  'Bond',               'platform_year' => 2016),
        '5032'              => array('platform_model' =>  'Element',            'platform_year' => 2016),
        '5071'              => array('platform_model' =>  'Belief',             'platform_year' => 2016),
        '5505'              => array('platform_model' =>  'Amsterdam',          'platform_year' => 2016),
        '5515'              => array('platform_model' =>  'Wide',               'platform_year' => 2016),
        '6050'              => array('platform_model' =>  'Jumbo',              'platform_year' => 2016),
        '4072'              => array('platform_model' =>  'Strike Mini',        'platform_year' => 2017),
        '4526'              => array('platform_model' =>  'Fox',                'platform_year' => 2017),
        '5033'              => array('platform_model' =>  'Shark',              'platform_year' => 2017),
        '5037'              => array('platform_model' =>  'Strike Power',       'platform_year' => 2017),
        '5044'              => array('platform_model' =>  'Strike',             'platform_year' => 2017),
        '5052'              => array('platform_model' =>  'Sense',              'platform_year' => 2017),
        '5058'              => array('platform_model' =>  'Strike Power Easy',  'platform_year' => 2017),
        '5082'              => array('platform_model' =>  'Sense 2',            'platform_year' => 2017),
        '5201'              => array('platform_model' =>  'Space',              'platform_year' => 2017),
        '5202'              => array('platform_model' =>  'Space Lite',         'platform_year' => 2017),
        '5005L'             => array('platform_model' =>  'Intense',            'platform_year' => 2018),
        '5012L'             => array('platform_model' =>  'Rich',               'platform_year' => 2018),
        '5022'              => array('platform_model' =>  'Bond',               'platform_year' => 2018),
        '5022'              => array('platform_model' =>  'Bond',               'platform_year' => 2018),
        '5591'              => array('platform_model' =>  'Jeans',              'platform_year' => 2018),
        '6000L'             => array('platform_model' =>  'Aurora',             'platform_year' => 2018),

    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'BQ',
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
