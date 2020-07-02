<?php
/**
 * @brief Acer client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Acer.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.12
 * @date Creation: Apr 2018
 * @date Modification: Jun 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Acer client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AcerClientDevice($deviceCode='') {
    $deviceList = array(
        /* Acer Chrombooks */
        'Chromebook R13'    => array('platform_model' => 'Chromebook R13',  'platform_type' => 'computer',  'platform_format' => 'desktop', 'platform_year' => 2016),

        /* Acer tablets */
        'A500'          => array('platform_model' => 'Iconia Tab A500',     'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A1-810'        => array('platform_model' => 'Iconia A1-810',       'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2013),
        'B3-A20'        => array('platform_model' => 'Iconia Tab One 10',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'B1-770'        => array('platform_model' => 'Iconia Tab One 7',    'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'B1-850'        => array('platform_model' => 'Iconia Tab One 8',    'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'B3-A30'        => array('platform_model' => 'Iconia Tab One 10',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'B3-A40'        => array('platform_model' => 'Iconia Tab One 10',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        'B3-A40FHD'     => array('platform_model' => 'Iconia Tab One 10',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        'B3-A50'        => array('platform_model' => 'Iconia Tab One 10',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2018),

        /* Acer mobiles */
        'Liquid'        => array('platform_model' => 'Liquid',              'platform_year' => 2009),
        'Z2_WVGA_QXH'   => array('platform_model' => 'Liquid Z2',           'platform_year' => 2013),
        'Z6PLUS'        => array('platform_model' => 'Liquid Z6 plus',      'platform_year' => 2016),

        'E310'          => array('platform_model' => 'Liquid Mini',         'platform_year' => 2011),
        'E320'          => array('platform_model' => 'Liquid Express',      'platform_year' => 2011),
        'E330'          => array('platform_model' => 'Liquid Glow',         'platform_year' => 2012),
        'E350'          => array('platform_model' => 'Liquid Gallant',      'platform_year' => 2012),
        'S500'          => array('platform_model' => 'Cloud Mobile',        'platform_year' => 2012),
        'Z110'          => array('platform_model' => 'Liquid Z110 Duo',     'platform_year' => 2012),
        'I110'          => array('platform_model' => 'Liquid C1',           'platform_year' => 2013),
        'S510'          => array('platform_model' => 'Liquid S1 Duo',       'platform_year' => 2013),
        'V360'          => array('platform_model' => 'Liquid E1 Duo',       'platform_year' => 2013),
        'V370'          => array('platform_model' => 'Liquid E2 Duo',       'platform_year' => 2013),
        'Z130'          => array('platform_model' => 'Liquid Z3',           'platform_year' => 2013),
        'E39'           => array('platform_model' => 'Liquid E700',         'platform_year' => 2014),
        'V380'          => array('platform_model' => 'Liquid E3 Duo',       'platform_year' => 2014),
        'Z160'          => array('platform_model' => 'Liquid Z4 Duo',       'platform_year' => 2014),
        'Z150'          => array('platform_model' => 'Liquid Z5 Duo',       'platform_year' => 2014),
        'Z200'          => array('platform_model' => 'Liquid Z200',         'platform_year' => 2014),
        'Z410'          => array('platform_model' => 'Liquid Z410',         'platform_year' => 2014),
        'Z500'          => array('platform_model' => 'Liquid Z500',         'platform_year' => 2014),
        'S56'           => array('platform_model' => 'Liquid Jade S',       'platform_year' => 2015),
        'S57'           => array('platform_model' => 'Liquid Jade Z',       'platform_year' => 2015),
        'T02'           => array('platform_model' => 'Liquid Z530',         'platform_year' => 2015),
        'T03'           => array('platform_model' => 'Liquid Z630',         'platform_year' => 2015),
        'Z220'          => array('platform_model' => 'Liquid Z220',         'platform_year' => 2015),
        'Z520'          => array('platform_model' => 'Liquid Z520',         'platform_year' => 2015),
        'T04'           => array('platform_model' => 'Liquid Z630S',        'platform_year' => 2016),
        'T07'           => array('platform_model' => 'Liquid Zest',         'platform_year' => 2016),
        'T08'           => array('platform_model' => 'Liquid Zest Plus',    'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Acer',
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
