<?php
/**
 * @brief Apple client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Jul 2018
 * @date Modification: Mar 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Apple client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AppleClientDevice($deviceCode='') {
    $deviceList = array(
        /* iPhones */
        'iPhone1.1'     => array('platform_model' => 'iPhone',              'platform_year' => 2007),
        'iPhone1.2'     => array('platform_model' => 'iPhone 3G',           'platform_year' => 2008),
        'iPhone2.1'     => array('platform_model' => 'iPhone 3GS',          'platform_year' => 2009),
        'iPhone3.1'     => array('platform_model' => 'iPhone 4',            'platform_year' => 2010),
        'iPhone3.2'     => array('platform_model' => 'iPhone 4',            'platform_year' => 2010),
        'iPhone3.3'     => array('platform_model' => 'iPhone 4',            'platform_year' => 2010),
        'iPhone4.1'     => array('platform_model' => 'iPhone 4S',           'platform_year' => 2011),
        'iPhone5.1'     => array('platform_model' => 'iPhone 5',            'platform_year' => 2012),
        'iPhone5.2'     => array('platform_model' => 'iPhone 5',            'platform_year' => 2012),
        'iPhone5.3'     => array('platform_model' => 'iPhone 5C',           'platform_year' => 2013),
        'iPhone6.1'     => array('platform_model' => 'iPhone 5S',           'platform_year' => 2013),
        'iPhone6.2'     => array('platform_model' => 'iPhone 5S',           'platform_year' => 2013),
        'iPhone7.1'     => array('platform_model' => 'iPhone 6 Plus',       'platform_year' => 2014),
        'iPhone7.2'     => array('platform_model' => 'iPhone 6',            'platform_year' => 2014),
        'iPhone8.1'     => array('platform_model' => 'iPhone 6S ',          'platform_year' => 2015),
        'iPhone8.2'     => array('platform_model' => 'iPhone 6S Plus',      'platform_year' => 2015),
        'iPhone8.4'     => array('platform_model' => 'iPhone SE',           'platform_year' => 2016),
        'iPhone9.1'     => array('platform_model' => 'iPhone 7',            'platform_year' => 2016),
        'iPhone9.3'     => array('platform_model' => 'iPhone 7',            'platform_year' => 2016),
        'iPhone9.2'     => array('platform_model' => 'iPhone 7 Plus',       'platform_year' => 2016),
        'iPhone9.4'     => array('platform_model' => 'iPhone 7 Plus',       'platform_year' => 2016),
        'iPhone10.1'    => array('platform_model' => 'iPhone 8',            'platform_year' => 2017),
        'iPhone10.4'    => array('platform_model' => 'iPhone 8',            'platform_year' => 2017),
        'iPhone10.2'    => array('platform_model' => 'iPhone 8 Plus',       'platform_year' => 2017),
        'iPhone10.5'    => array('platform_model' => 'iPhone 8 Plus',       'platform_year' => 2017),
        'iPhone10.3'    => array('platform_model' => 'iPhone X',            'platform_year' => 2017),
        'iPhone10.6'    => array('platform_model' => 'iPhone X',            'platform_year' => 2017),
        'iPhone11.2'    => array('platform_model' => 'iPhone XS',           'platform_year' => 2018),
        'iPhone11.4'    => array('platform_model' => 'iPhone XS Max',       'platform_year' => 2018),
        'iPhone11.6'    => array('platform_model' => 'iPhone XS Max',       'platform_year' => 2018),
        'iPhone11.8'    => array('platform_model' => 'iPhone XR',           'platform_year' => 2018),
        'iPhone12.1'    => array('platform_model' => 'iPhone 11',           'platform_year' => 2019),
        'iPhone12.3'    => array('platform_model' => 'iPhone 11 Pro',       'platform_year' => 2019),
        'iPhone12.5'    => array('platform_model' => 'iPhone 11 Pro Max',   'platform_year' => 2019),
        'iPhone12.8'    => array('platform_model' => 'iPhone SE',           'platform_year' => 2019),
        'iPhone13.1'    => array('platform_model' => 'iPhone 12 Mini',      'platform_year' => 2020),
        'iPhone13.2'    => array('platform_model' => 'iPhone 12',           'platform_year' => 2020),
        'iPhone13.3'    => array('platform_model' => 'iPhone 12 Pro',       'platform_year' => 2020),
        'iPhone13.4'    => array('platform_model' => 'iPhone 12 Pro Max',   'platform_year' => 2020),

        /* iPads */
        'iPad1.1'       => array('platform_model' => 'iPad',                'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2010),
        'iPad2.1'       => array('platform_model' => 'iPad 2',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2011),
        'iPad2.2'       => array('platform_model' => 'iPad 2',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2011),
        'iPad2.3'       => array('platform_model' => 'iPad 2',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2011),
        'iPad2.4'       => array('platform_model' => 'iPad 2',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2011),
        'iPad3.1'       => array('platform_model' => 'iPad 3',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3.2'       => array('platform_model' => 'iPad 3',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3.3'       => array('platform_model' => 'iPad 3',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3.4'       => array('platform_model' => 'iPad 4',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3.5'       => array('platform_model' => 'iPad 4',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3.6'       => array('platform_model' => 'iPad 4',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad6.11'      => array('platform_model' => 'iPad 5',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad6.12'      => array('platform_model' => 'iPad 5',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.5'       => array('platform_model' => 'iPad 6',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad7.6'       => array('platform_model' => 'iPad 6',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad7.11'      => array('platform_model' => 'iPad 7',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2019),
        'iPad7.12'      => array('platform_model' => 'iPad 7',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2019),
        'iPad11.6'      => array('platform_model' => 'iPad 8',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2019),
        'iPad11.7'      => array('platform_model' => 'iPad 8',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2019),

        /* iPads Pro */
        'iPad6.3'       => array('platform_model' => 'iPad Pro (9.7\')',    'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        'iPad6.4'       => array('platform_model' => 'iPad Pro (9.7\')',    'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        'iPad6.7'       => array('platform_model' => 'iPad Pro (12.9\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad6.8'       => array('platform_model' => 'iPad Pro (12.9\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad7.1'       => array('platform_model' => 'iPad Pro 2 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.2'       => array('platform_model' => 'iPad Pro 2 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.3'       => array('platform_model' => 'iPad Pro 2 (10.5\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.4'       => array('platform_model' => 'iPad Pro 2 (10.5\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad8.1'       => array('platform_model' => 'iPad Pro 3 (11\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad8.2'       => array('platform_model' => 'iPad Pro 3 (11\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad8.3'       => array('platform_model' => 'iPad Pro 3 (11\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad8.4'       => array('platform_model' => 'iPad Pro 3 (11\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad8.5'       => array('platform_model' => 'iPad Pro 3 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad8.6'       => array('platform_model' => 'iPad Pro 3 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad8.7'       => array('platform_model' => 'iPad Pro 3 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad8.8'       => array('platform_model' => 'iPad Pro 3 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad8.9'       => array('platform_model' => 'iPad Pro 4 (11\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2020),
        'iPad8.10'      => array('platform_model' => 'iPad Pro 4 (11\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2020),
        'iPad8.11'      => array('platform_model' => 'iPad Pro 4 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2020),
        'iPad8.12'      => array('platform_model' => 'iPad Pro 4 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2020),

        /* iPads Air */
        'iPad4.1'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4.2'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4.3'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad5.3'       => array('platform_model' => 'iPad Air 2',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad5.4'       => array('platform_model' => 'iPad Air 2',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad11.3'      => array('platform_model' => 'iPad Air 3',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2019),
        'iPad11.4'      => array('platform_model' => 'iPad Air 3',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2019),
        'iPad13.1'      => array('platform_model' => 'iPad Air 4',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2020),
        'iPad13.2'      => array('platform_model' => 'iPad Air 4',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2020),

        /* iPads Mini */
        'iPad2.5'       => array('platform_model' => 'iPad Mini',           'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad2.6'       => array('platform_model' => 'iPad Mini',           'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad2.7'       => array('platform_model' => 'iPad Mini',           'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad4.4'       => array('platform_model' => 'iPad Mini 2',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4.5'       => array('platform_model' => 'iPad Mini 2',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4.6'       => array('platform_model' => 'iPad Mini 2',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4.7'       => array('platform_model' => 'iPad Mini 3',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad4.8'       => array('platform_model' => 'iPad Mini 3',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad4.9'       => array('platform_model' => 'iPad Mini 3',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad5.1'       => array('platform_model' => 'iPad Mini 4',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad5.2'       => array('platform_model' => 'iPad Mini 4',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad11.1'      => array('platform_model' => 'iPad Mini 5',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2019),
        'iPad11.2'      => array('platform_model' => 'iPad Mini 5',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2019),

        /* iPods */
        'iPod1.1'       => array('platform_model' => 'iPod Touch',          'platform_year' => 2007),
        'iPod2.1'       => array('platform_model' => 'iPod Touch 2',        'platform_year' => 2008),
        'iPod3.1'       => array('platform_model' => 'iPod Touch 3',        'platform_year' => 2009),
        'iPod4.1'       => array('platform_model' => 'iPod Touch 4',        'platform_year' => 2010),
        'iPod5.1'       => array('platform_model' => 'iPod Touch 5',        'platform_year' => 2012),
        'iPod7.1'       => array('platform_model' => 'iPod Touch 6',        'platform_year' => 2015),
        'iPod9.1'       => array('platform_model' => 'iPod Touch 7',        'platform_year' => 2019),

        /* Watches */
        'Watch1.1'      => array('platform_model' => 'Watch Series 0 38mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2015),
        'Watch1.2'      => array('platform_model' => 'Watch Series 0 42mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2015),
        'Watch2.6'      => array('platform_model' => 'Watch Series 1 38mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2016),
        'Watch2.7'      => array('platform_model' => 'Watch Series 1 42mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2016),
        'Watch2.3'      => array('platform_model' => 'Watch Series 2 38mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2016),
        'Watch2.4'      => array('platform_model' => 'Watch Series 2 42mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2016),
        'Watch3.1'      => array('platform_model' => 'Watch Series 3 38mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2017),
        'Watch3.2'      => array('platform_model' => 'Watch Series 3 42mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2017),
        'Watch3.3'      => array('platform_model' => 'Watch Series 3 38mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2017),
        'Watch3.4'      => array('platform_model' => 'Watch Series 3 42mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2017),
        'Watch4.1'      => array('platform_model' => 'Watch Series 4 40mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2018),
        'Watch4.2'      => array('platform_model' => 'Watch Series 4 44mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2018),
        'Watch4.3'      => array('platform_model' => 'Watch Series 4 40mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2018),
        'Watch4.4'      => array('platform_model' => 'Watch Series 4 44mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2018),
        'Watch5.1'      => array('platform_model' => 'Watch Series 5 40mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2019),
        'Watch5.2'      => array('platform_model' => 'Watch Series 5 44mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2019),
        'Watch5.3'      => array('platform_model' => 'Watch Series 5 40mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2019),
        'Watch5.4'      => array('platform_model' => 'Watch Series 5 44mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2019),
        'Watch5.9'      => array('platform_model' => 'Watch SE 40mm',       'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2020),
        'Watch5.10'     => array('platform_model' => 'Watch SE 44mm',       'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2020),
        'Watch5.11'     => array('platform_model' => 'Watch SE 40mm',       'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2020),
        'Watch5.12'     => array('platform_model' => 'Watch SE 44mm',       'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2020),
        'Watch6.1'      => array('platform_model' => 'Watch Series 6 40mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2020),
        'Watch6.2'      => array('platform_model' => 'Watch Series 6 44mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2020),
        'Watch6.3'      => array('platform_model' => 'Watch Series 6 40mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2020),
        'Watch6.4'      => array('platform_model' => 'Watch Series 6 44mm', 'platform_type' => 'watch',   'platform_format' => 'watch',   'platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Apple',
        'platform_country'  => 'us',
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
