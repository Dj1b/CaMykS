<?php
/**
 * @brief Apple client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Apple.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2018
 * @date Modification: Oct 2018
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
        'iPhone1.1'     => array('platform_model' => 'iPhone',          'platform_year' => 2007),
        'iPhone1.2'     => array('platform_model' => 'iPhone 3G',       'platform_year' => 2008),
        'iPhone2.1'     => array('platform_model' => 'iPhone 3GS',      'platform_year' => 2009),
        'iPhone3.1'     => array('platform_model' => 'iPhone 4',        'platform_year' => 2010),
        'iPhone3.2'     => array('platform_model' => 'iPhone 4',        'platform_year' => 2010),
        'iPhone3.3'     => array('platform_model' => 'iPhone 4',        'platform_year' => 2010),
        'iPhone4.1'     => array('platform_model' => 'iPhone 4S',       'platform_year' => 2011),
        'iPhone5.1'     => array('platform_model' => 'iPhone 5',        'platform_year' => 2012),
        'iPhone5.2'     => array('platform_model' => 'iPhone 5',        'platform_year' => 2012),
        'iPhone5.3'     => array('platform_model' => 'iPhone 5C',       'platform_year' => 2013),
        'iPhone6.1'     => array('platform_model' => 'iPhone 5S',       'platform_year' => 2013),
        'iPhone6.2'     => array('platform_model' => 'iPhone 5S',       'platform_year' => 2013),
        'iPhone7.1'     => array('platform_model' => 'iPhone 6 Plus',   'platform_year' => 2014),
        'iPhone7.2'     => array('platform_model' => 'iPhone 6',        'platform_year' => 2014),
        'iPhone8.1'     => array('platform_model' => 'iPhone 6S ',      'platform_year' => 2015),
        'iPhone8.2'     => array('platform_model' => 'iPhone 6S Plus',  'platform_year' => 2015),
        'iPhone8.4'     => array('platform_model' => 'iPhone SE',       'platform_year' => 2016),
        'iPhone9.1'     => array('platform_model' => 'iPhone 7',        'platform_year' => 2016),
        'iPhone9.3'     => array('platform_model' => 'iPhone 7',        'platform_year' => 2016),
        'iPhone9.2'     => array('platform_model' => 'iPhone 7 Plus',   'platform_year' => 2016),
        'iPhone9.4'     => array('platform_model' => 'iPhone 7 Plus',   'platform_year' => 2016),
        'iPhone10.1'    => array('platform_model' => 'iPhone 8',        'platform_year' => 2017),
        'iPhone10.4'    => array('platform_model' => 'iPhone 8',        'platform_year' => 2017),
        'iPhone10.2'    => array('platform_model' => 'iPhone 8 Plus',   'platform_year' => 2017),
        'iPhone10.5'    => array('platform_model' => 'iPhone 8 Plus',   'platform_year' => 2017),
        'iPhone10.3'    => array('platform_model' => 'iPhone X',        'platform_year' => 2017),
        'iPhone10.6'    => array('platform_model' => 'iPhone X',        'platform_year' => 2017),

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
        'iPad4.1'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4.2'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad4.3'       => array('platform_model' => 'iPad Air',            'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2013),
        'iPad5.3'       => array('platform_model' => 'iPad Air 2',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad5.4'       => array('platform_model' => 'iPad Air 2',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        'iPad6.3'       => array('platform_model' => 'iPad Pro (9.7\')',    'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        'iPad6.4'       => array('platform_model' => 'iPad Pro (9.7\')',    'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        'iPad6.7'       => array('platform_model' => 'iPad Pro (12.9\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad6.8'       => array('platform_model' => 'iPad Pro (12.9\')',   'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        'iPad6.11'      => array('platform_model' => 'iPad 5',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad6.12'      => array('platform_model' => 'iPad 5',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.1'       => array('platform_model' => 'iPad Pro 2 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.2'       => array('platform_model' => 'iPad Pro 2 (12.9\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.3'       => array('platform_model' => 'iPad Pro 2 (10.5\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.4'       => array('platform_model' => 'iPad Pro 2 (10.5\')', 'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        'iPad7.5'       => array('platform_model' => 'iPad 6',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),
        'iPad7.6'       => array('platform_model' => 'iPad 6',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2018),

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
