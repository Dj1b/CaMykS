<?php
/**
 * @brief Lenovo client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Lenovo.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.16
 * @date Creation: Apr 2018
 * @date Modification: Jun 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Lenovo client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LenovoClientDevice($deviceCode='') {
    $deviceList = array(
        /* Lenovo tablets */
        'A2107A-H'              => array('platform_model' => 'IdeaTab A2107A-H',    'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2013),
        'B8000-F'               => array('platform_model' => 'Yoga',                'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2013),
        'B8080-F'               => array('platform_model' => 'Yoga 10 HD+',         'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2014),
        'Tablet 2-830F'         => array('platform_model' => 'Yoga Tab 2',          'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2014),
        'Tablet 2-1050F'        => array('platform_model' => 'Yoga Tablet 2 10',    'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2014),
        'Tablet 2 Pro-1380F'    => array('platform_model' => 'Yoga Tablet 2 Pro',   'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2014),
        'A5500'                 => array('platform_model' => 'A8-50',               'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2014),
        'PB1-770P'              => array('platform_model' => 'PHAB Plus',           'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2015),
        'Tab2A710F'             => array('platform_model' => 'Tab 2 A7',            'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2015),
        'TAB 2 A10-70LC'        => array('platform_model' => 'Tab 2 A10',           'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2015),
        'YT3-X90F'              => array('platform_model' => 'Yoga Tab 3 Pro 10',   'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2015),
        'YB1-X90F'              => array('platform_model' => 'Yoga Book',           'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2016),
        'YT3-X50F'              => array('platform_model' => 'Yoga Tab 3',          'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2016),
        'YT-X703F'              => array('platform_model' => 'Yoga Tab 3 Plus',     'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2016),
        'TB3-710F'              => array('platform_model' => 'Tab 3 7\'',           'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2016),
        'TB3-850F'              => array('platform_model' => 'Tab 3 8\'',           'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2017),
        'TB-X304F'              => array('platform_model' => 'Tab 4',               'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2017),

        /* Lenovo phones */
        'A369i'     => array('platform_model' => 'A369i',                   'platform_year' => 2013),
        'A319'      => array('platform_model' => 'RocStar',                 'platform_year' => 2014),
        'A806'      => array('platform_model' => 'Golden Warrior A8',       'platform_year' => 2014),
        'A936'      => array('platform_model' => 'Golden Warrior Note 8',   'platform_year' => 2014),
        'K30-T'     => array('platform_model' => 'K3',                      'platform_year' => 2014),
        'K50-T5'    => array('platform_model' => 'K3 Note',                 'platform_year' => 2015),
        'K51c78'    => array('platform_model' => 'Vibe X3 Lite',            'platform_year' => 2015),
        'P70-A'     => array('platform_model' => 'P70',                     'platform_year' => 2015),
        'A2010-a'   => array('platform_model' => 'A2010',                   'platform_year' => 2015),
        'A7000-a'   => array('platform_model' => 'A7000',                   'platform_year' => 2015),
        'K52t38'    => array('platform_model' => 'K5 Note',                 'platform_year' => 2015),
        'K53a48'    => array('platform_model' => 'K6 Note',                 'platform_year' => 2016),
        'A1010a20'  => array('platform_model' => 'A Plus',                  'platform_year' => 2016),
        'A1000m'    => array('platform_model' => 'Vibe A',                  'platform_year' => 2016),
        'A2010l36'  => array('platform_model' => 'Vibe K5',                 'platform_year' => 2016),
        'A6020a46'  => array('platform_model' => 'Vibe K5 Plus',            'platform_year' => 2016),
        'A7010A48'  => array('platform_model' => 'Vibe K4 Note',            'platform_year' => 2016),
        'A7020a40'  => array('platform_model' => 'Vibe K5 Note',            'platform_year' => 2016),
        'A2016a40'  => array('platform_model' => 'Vibe B',                  'platform_year' => 2016),
        'A2020a40'  => array('platform_model' => 'Vibe C',                  'platform_year' => 2016),
        'K10A40'    => array('platform_model' => 'Vibe C2',                 'platform_year' => 2016),
        'K33a42'    => array('platform_model' => 'K6 Power',                'platform_year' => 2016),
        'K33a48'    => array('platform_model' => 'K6',                      'platform_year' => 2016),
        'K53a48'    => array('platform_model' => 'K6 Note',                 'platform_year' => 2016),
        'K53b36'    => array('platform_model' => 'K6 Plus',                 'platform_year' => 2016),
        'K10E70'    => array('platform_model' => 'K10',                     'platform_year' => 2017),
        'Z1'        => array('platform_model' => 'Zuk Z1',                  'platform_year' => 2015),
        'Z2131'     => array('platform_model' => 'Zuk Z2',                  'platform_year' => 2016),
        'Z2151'     => array('platform_model' => 'Zuk Edge',                'platform_year' => 2017),

        'Z2 Plus'   => array('platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Lenovo',
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
