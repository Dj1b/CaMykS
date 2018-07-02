<?php
/**
 * @brief Apple client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Apple.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2018
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
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
        'iPhone1_1'     => array('platform_model' => 'iPhone',          'platform_year' => 2007),
        'iPhone1_2'     => array('platform_model' => 'iPhone 3G',       'platform_year' => 2008),
        'iPhone2_1'     => array('platform_model' => 'iPhone 3GS',      'platform_year' => 2009),
        'iPhone3_1'     => array('platform_model' => 'iPhone 4',        'platform_year' => 2010),
        'iPhone3_2'     => array('platform_model' => 'iPhone 4',        'platform_year' => 2010),
        'iPhone3_3'     => array('platform_model' => 'iPhone 4',        'platform_year' => 2010),
        'iPhone4_1'     => array('platform_model' => 'iPhone 4S',       'platform_year' => 2011),
        'iPhone5_1'     => array('platform_model' => 'iPhone 5',        'platform_year' => 2012),
        'iPhone5_2'     => array('platform_model' => 'iPhone 5',        'platform_year' => 2012),
        'iPhone5_3'     => array('platform_model' => 'iPhone 5C',       'platform_year' => 2013),
        'iPhone6_1'     => array('platform_model' => 'iPhone 5S',       'platform_year' => 2013),
        'iPhone6_2'     => array('platform_model' => 'iPhone 5S',       'platform_year' => 2013),
        'iPhone7_1'     => array('platform_model' => 'iPhone 6 Plus',   'platform_year' => 2014),
        'iPhone7_2'     => array('platform_model' => 'iPhone 6',        'platform_year' => 2014),
        'iPhone8_1'     => array('platform_model' => 'iPhone 6S ',      'platform_year' => 2015),
        'iPhone8_2'     => array('platform_model' => 'iPhone 6S Plus',  'platform_year' => 2015),
        'iPhone8_4'     => array('platform_model' => 'iPhone SE',       'platform_year' => 2016),
        'iPhone9_1'     => array('platform_model' => 'iPhone 7',        'platform_year' => 2016),
        'iPhone9_3'     => array('platform_model' => 'iPhone 7',        'platform_year' => 2016),
        'iPhone9_2'     => array('platform_model' => 'iPhone 7 Plus',   'platform_year' => 2016),
        'iPhone9_4'     => array('platform_model' => 'iPhone 7 Plus',   'platform_year' => 2016),
        'iPhone10_1'    => array('platform_model' => 'iPhone 8',        'platform_year' => 2017),
        'iPhone10_4'    => array('platform_model' => 'iPhone 8',        'platform_year' => 2017),
        'iPhone10_2'    => array('platform_model' => 'iPhone 8 Plus',   'platform_year' => 2017),
        'iPhone10_5'    => array('platform_model' => 'iPhone 8 Plus',   'platform_year' => 2017),
        'iPhone10_3'    => array('platform_model' => 'iPhone X',        'platform_year' => 2017),
        'iPhone10_6'    => array('platform_model' => 'iPhone X',        'platform_year' => 2017),
        
        /* iPads */
        'iPad1_1'       => array('platform_model' => 'iPad',                'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2010),
        'iPad2_1'       => array('platform_model' => 'iPad 2',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2011),
        'iPad2_2'       => array('platform_model' => 'iPad 2',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2011),
        'iPad2_3'       => array('platform_model' => 'iPad 2',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2011),
        'iPad2_4'       => array('platform_model' => 'iPad 2',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2011),
        'iPad3_1'       => array('platform_model' => 'iPad 3',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3_2'       => array('platform_model' => 'iPad 3',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3_3'       => array('platform_model' => 'iPad 3',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3_4'       => array('platform_model' => 'iPad 4',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3_5'       => array('platform_model' => 'iPad 4',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad3_6'       => array('platform_model' => 'iPad 4',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad4_1'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4_2'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4_3'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad5_3'       => array('platform_model' => 'iPad Air 2',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad5_4'       => array('platform_model' => 'iPad Air 2',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad6_3'       => array('platform_model' => 'iPad Pro (9.7\')',    'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        'iPad6_4'       => array('platform_model' => 'iPad Pro (9.7\')',    'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        'iPad6_7'       => array('platform_model' => 'iPad Pro (12.9\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad6_8'       => array('platform_model' => 'iPad Pro (12.9\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad6_11'      => array('platform_model' => 'iPad 5',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad6_12'      => array('platform_model' => 'iPad 5',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7_1'       => array('platform_model' => 'iPad Pro 2 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7_2'       => array('platform_model' => 'iPad Pro 2 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7_3'       => array('platform_model' => 'iPad Pro 2 (10.5\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7_4'       => array('platform_model' => 'iPad Pro 2 (10.5\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7_5'       => array('platform_model' => 'iPad 6',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad7_6'       => array('platform_model' => 'iPad 6',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),

        /* iPads Mini */
        'iPad2_5'       => array('platform_model' => 'iPad Mini',           'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad2_6'       => array('platform_model' => 'iPad Mini',           'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad2_7'       => array('platform_model' => 'iPad Mini',           'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2012),
        'iPad4_4'       => array('platform_model' => 'iPad Mini 2',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4_5'       => array('platform_model' => 'iPad Mini 2',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4_6'       => array('platform_model' => 'iPad Mini 2',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4_7'       => array('platform_model' => 'iPad Mini 3',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad4_8'       => array('platform_model' => 'iPad Mini 3',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad4_9'       => array('platform_model' => 'iPad Mini 3',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad5_1'       => array('platform_model' => 'iPad Mini 4',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad5_2'       => array('platform_model' => 'iPad Mini 4',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        
        /* iPods */
        'iPod1,1'       => array('platform_model' => 'iPod Touch',          'platform_year' => 2007),
        'iPod2,1'       => array('platform_model' => 'iPod Touch 2',        'platform_year' => 2008),
        'iPod3,1'       => array('platform_model' => 'iPod Touch 3',        'platform_year' => 2009),
        'iPod4,1'       => array('platform_model' => 'iPod Touch 4',        'platform_year' => 2010),
        'iPod5,1'       => array('platform_model' => 'iPod Touch 5',        'platform_year' => 2012),
        'iPod7,1'       => array('platform_model' => 'iPod Touch 6',        'platform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Apple',
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