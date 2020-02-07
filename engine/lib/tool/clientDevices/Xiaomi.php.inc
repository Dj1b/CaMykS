<?php
/**
 * @brief Xiaomi client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Xiaomi.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.37
 * @date Creation: May 2018
 * @date Modification: Feb 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Xiaomi client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_XiaomiClientDevice($deviceCode='') {
    $deviceList = array(
        /* Tablets */
        'mi pad'                => array('platform_model' => 'Mi Pad',              'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2014),
        'mi pad 2'              => array('platform_model' => 'Mi Pad 2',            'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2015),
        'mi pad 3'              => array('platform_model' => 'Mi Pad 3',            'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2017),
        'mi pad 4'              => array('platform_model' => 'Mi Pad 4',            'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2018),

        /* Phones, Mi series */
        'mi one'                => array('platform_model' => 'Mi One',              'platform_year' => 2011),
        'mi one c1'             => array('platform_model' => 'Mi One C1',           'platform_year' => 2012),
        'mi 2'                  => array('platform_model' => 'Mi 2',                'platform_year' => 2012),
        'mi 1sc'                => array('platform_model' => 'Mi 1S',               'platform_year' => 2012),
        'mi 2a'                 => array('platform_model' => 'Mi 2A',               'platform_year' => 2013),
        'mi 2s'                 => array('platform_model' => 'Mi 2S',               'platform_year' => 2013),
        'mi 2sc'                => array('platform_model' => 'Mi 2S',               'platform_year' => 2013),
        'mi 3'                  => array('platform_model' => 'Mi 3',                'platform_year' => 2013),
        'mi 3c'                 => array('platform_model' => 'Mi 3C',               'platform_year' => 2013),
        'mi 4'                  => array('platform_model' => 'Mi 4',                'platform_year' => 2014),
        'mi 4w'                 => array('platform_model' => 'Mi 4W',               'platform_year' => 2014),
        'mi 4lte'               => array('platform_model' => 'Mi 4',                'platform_year' => 2014),
        'mi mix'                => array('platform_model' => 'Mi Mix',              'platform_year' => 2014),
        'mi note lte'           => array('platform_model' => 'Mi Note',             'platform_year' => 2015),
        'mi note pro'           => array('platform_model' => 'Mi Note Pro',         'platform_year' => 2015),
        'mi 4i'                 => array('platform_model' => 'Mi 4I',               'platform_year' => 2015),
        'mi 4s'                 => array('platform_model' => 'Mi 4S',               'platform_year' => 2016),
        'mi 5'                  => array('platform_model' => 'Mi 5',                'platform_year' => 2016),
        'mi 5s'                 => array('platform_model' => 'Mi 5S',               'platform_year' => 2016),
        'mi 5s plus'            => array('platform_model' => 'Mi 5S Plus',          'platform_year' => 2016),
        'mi note 2'             => array('platform_model' => 'Mi Note 2',           'platform_year' => 2016),
        'mi max'                => array('platform_model' => 'Mi Max',              'platform_year' => 2016),
        'mi 5c'                 => array('platform_model' => 'Mi 5C',               'platform_year' => 2017),
        'mi 5x'                 => array('platform_model' => 'Mi 5X',               'platform_year' => 2017),
        'mi a1'                 => array('platform_model' => 'Mi A1',               'platform_year' => 2017),
        'mi 6'                  => array('platform_model' => 'Mi 6',                'platform_year' => 2017),
        'mi a1'                 => array('platform_model' => 'Mi A1',               'platform_year' => 2017),
        'mi max 2'              => array('platform_model' => 'Mi Max 2',            'platform_year' => 2017),
        'mi mix 2'              => array('platform_model' => 'Mi Mix 2',            'platform_year' => 2017),
        'mi note 3'             => array('platform_model' => 'Mi Note 3',           'platform_year' => 2017),
        'mi 7'                  => array('platform_model' => 'Mi 7',                'platform_year' => 2018),
        'mi 8'                  => array('platform_model' => 'Mi 8',                'platform_year' => 2018),
        'mi a2'                 => array('platform_model' => 'Mi A2',               'platform_year' => 2018),
        'mi a2 lite'            => array('platform_model' => 'Mi A2 Lite',          'platform_year' => 2018),
        'mi max 3'              => array('platform_model' => 'Mi Max 3',            'platform_year' => 2018),
        'mi mix 2s'             => array('platform_model' => 'Mi Mix 2S',           'platform_year' => 2018),
        'mi 8 lite'             => array('platform_model' => 'Mi 8 Lite',           'platform_year' => 2018),
        'mi a3'                 => array('platform_model' => 'Mi A3',               'platform_year' => 2019),
        'mi mix 3'              => array('platform_model' => 'Mi Mix 3',            'platform_year' => 2019),
        'mi mix 3 5g'           => array('platform_model' => 'Mi Mix 3 5G',         'platform_year' => 2019),
        'mi 9'                  => array('platform_model' => 'Mi 9',                'platform_year' => 2019),
        'mi 9 se'               => array('platform_model' => 'Mi 9 SE',             'platform_year' => 2019),
        'mi 9 lite'             => array('platform_model' => 'Mi 9 Lite',           'platform_year' => 2019),
        'mi 9t'                 => array('platform_model' => 'Mi 9T',               'platform_year' => 2019),
        'mi 9t pro'             => array('platform_model' => 'Mi 9T Pro',           'platform_year' => 2019),
        'mi note 10'            => array('platform_model' => 'Mi Note 10',          'platform_year' => 2019),

        /* Phones, Redmi series */
        '2014811'               => array('platform_model' => 'Redmi 2',             'platform_year' => 2014),
        'redmi note 2'          => array('platform_model' => 'Redmi Note 2',        'platform_year' => 2015),
        'redmi note 2 prime'    => array('platform_model' => 'Redmi Note 2 Prime',  'platform_year' => 2015),
        'redmi note 3'          => array('platform_model' => 'Redmi Note 3',        'platform_year' => 2015),
        'hm note 1lte'          => array('platform_model' => 'Redmi Note 3',        'platform_year' => 2015),
        'redmi note 3 pro'      => array('platform_model' => 'Redmi Note 3 Pro',    'platform_year' => 2015),
        'redmi note 4'          => array('platform_model' => 'Redmi Note 4',        'platform_year' => 2016),
        'redmi 3s'              => array('platform_model' => 'Redmi 3S',            'platform_year' => 2016),
        'redmi 3x'              => array('platform_model' => 'Redmi 3X',            'platform_year' => 2016),
        'redmi 4'               => array('platform_model' => 'Redmi 4',             'platform_year' => 2016),
        'redmi 4 prime'         => array('platform_model' => 'Redmi 4 Prime',       'platform_year' => 2016),
        'redmi pro'             => array('platform_model' => 'Redmi Pro',           'platform_year' => 2016),
        'redmi 4x'              => array('platform_model' => 'Redmi 4X',            'platform_year' => 2017),
        'redmi note 4x'         => array('platform_model' => 'Redmi Note 4X',       'platform_year' => 2017),
        'redmi 5'               => array('platform_model' => 'Redmi 5',             'platform_year' => 2017),
        'redmi 5a'              => array('platform_model' => 'Redmi 5A',            'platform_year' => 2017),
        'redmi y1'              => array('platform_model' => 'Redmi Y1',            'platform_year' => 2017),
        'redmi y1 lite'         => array('platform_model' => 'Redmi Y1 Lite',       'platform_year' => 2017),
        'redmi note 5a'         => array('platform_model' => 'Redmi Note 5A',       'platform_year' => 2018),
        'redmi note 5a prime'   => array('platform_model' => 'Redmi Note 5A Prime', 'platform_year' => 2018),
        'redmi note 5'          => array('platform_model' => 'Redmi Note 5',        'platform_year' => 2018),
        'redmi note 5 pro'      => array('platform_model' => 'Redmi Note 5 Pro',    'platform_year' => 2018),
        'redmi note 6 pro'      => array('platform_model' => 'Redmi Note 6 Pro',    'platform_year' => 2018),
        'redmi 5 plus'          => array('platform_model' => 'Redmi 5 Plus',        'platform_year' => 2018),
        'redmi 6'               => array('platform_model' => 'Redmi 6',             'platform_year' => 2018),
        'redmi 6a'              => array('platform_model' => 'Redmi 6A',            'platform_year' => 2018),
        'redmi 6 pro'           => array('platform_model' => 'Redmi 6 Pro',         'platform_year' => 2018),
        'redmi s2'              => array('platform_model' => 'Redmi S2',            'platform_year' => 2018),
        'redmi 7'               => array('platform_model' => 'Redmi 7',             'platform_year' => 2019),
        'redmi 7a'              => array('platform_model' => 'Redmi 7A',            'platform_year' => 2019),
        'redmi note 7'          => array('platform_model' => 'Redmi Note 7',        'platform_year' => 2019),
        'redmi note 8'          => array('platform_model' => 'Redmi Note 8',        'platform_year' => 2019),
        'redmi note 8t'         => array('platform_model' => 'Redmi Note 8',        'platform_year' => 2019),
        'redmi note 8 pro'      => array('platform_model' => 'Redmi Note 8 Pro',    'platform_year' => 2019),

        'pocophone f1'          => array('platform_model' => 'Pocophone F1',        'platform_year' => 2018),
        'poco f1'               => array('platform_model' => 'Pocophone F1',        'platform_year' => 2018),

        'skr h0'                => array('platform_model' => 'Black Shark',         'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
        return $deviceList;
    else
        $deviceCode = strtolower($deviceCode);

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Xiaomi',
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
