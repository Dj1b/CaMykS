<?php
/**
 * @brief Amazon client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.5
 * @date Creation: Oct 2018
 * @date Modification: Jun 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Amazon client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AmazonClientDevice($deviceCode='') {
    $deviceList = array(
        /* Amazon tablets - (Kindle) Fire series */
        'KFMUWI'    => array('platform_model'    => 'Fire 7',                           'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2019),
        'KFAUWI'    => array('platform_model'    => 'Fire 7 (7th Gen)',                 'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2017),
        'KFFOWI'    => array('platform_model'    => 'Fire 7 (5th Gen)',                 'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2015),
        'KFOT'      => array('platform_model'    => 'Fire 7',                           'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2012),

        /* Amazon tablets - (Kindle) Fire HD series */
        'KFMAWI'    => array('platform_model'    => 'Fire HD 10',                       'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2019),
        'KFKAWI'    => array('platform_model'    => 'Fire HD 8',                        'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2018),
        'KFSUWI'    => array('platform_model'    => 'Fire HD 10',                       'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2017),
        'KFDOWI'    => array('platform_model'    => 'Fire HD 8',                        'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2017),
        'KFGIWI'    => array('platform_model'    => 'Fire HD 8 (6th Gen)',              'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2016),
        'KFTBWI'    => array('platform_model'    => 'Fire HD 10 (5th Gen)',             'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2015),
        'KFMEWI'    => array('platform_model'    => 'Fire HD 8 (5th Gen)',              'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2015),
        'KFASWI'    => array('platform_model'    => 'Fire HD 7 (4th Gen)',              'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2014),
        'KFARWI'    => array('platform_model'    => 'Fire HD 6 (4th Gen)',              'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2014),
        'KFSOWI'    => array('platform_model'    => 'Fire HD 7 (3rd Gen)',              'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2013),
        'KFJWI'     => array('platform_model'    => 'Fire HD 8.9',                      'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2012),
        'KFTT'      => array('platform_model'    => 'Fire HD 7',                        'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2012),
        'KFTRWI'    => array('platform_model'    => 'Fire HD 10',                       'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2021),
        'KFTRPWI'   => array('platform_model'    => 'Fire HD 10 Plus',                  'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2021),

        /* Amazon tablets - (Kindle) Fire HDX series */
        'KFSAWI'    => array('platform_model'    => 'Fire HDX 8.9 (4th Gen)',           'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2014),
        'KFSAWA'    => array('platform_model'    => 'Fire HDX 8.9 (4th Gen)',           'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2014),
        'KFTHWI'    => array('platform_model'    => 'Kindle Fire HDX 7',                'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2013),
        'KFAPWA'    => array('platform_model'    => 'Kindle Fire HDX 8.9 (3rd Gen)',    'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2013),
        'KFAPWI'    => array('platform_model'    => 'Kindle Fire HDX 8.9 (3rd Gen)',    'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2013),
        'KFTHWA'    => array('platform_model'    => 'Kindle Fire HDX 7 (3rd Gen)',      'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2013),
        'KFTHWI'    => array('platform_model'    => 'Kindle Fire HDX 7 (3rd Gen)',      'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2013),
        'KFJWA'     => array('platform_model'    => 'Kindle Fire HDX 7 (2nd Gen)',      'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2012),
        'KFJWI'     => array('platform_model'    => 'Kindle Fire HDX 7 (2nd Gen)',      'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2012),

        /* Amazon mobiles */
        'SD4930UR'  => array('platform_model'    => 'Fire Phone', 'platform_year' => 2014),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Amazon',
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
