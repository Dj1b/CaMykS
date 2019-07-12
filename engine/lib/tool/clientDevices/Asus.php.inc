<?php
/**
 * @brief Asus client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Asus.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.14
 * @date Creation: Apr 2018
 * @date Modification: Jul 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Asus client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AsusClientDevice($deviceCode='') {
    $deviceList = array(
        /* Asus tablets */
        'K007'      => array('platform_model' => 'MeMO Pad 7',              'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'K01E'      => array('platform_model' => 'MeMO Pad',                'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'ME173X'    => array('platform_model' => 'MeMO Pad HD 7',           'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2013),
        'P01M'      => array('platform_model' => 'ZenPad 8',                'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'P01MA'     => array('platform_model' => 'ZenPad 8',                'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'P023'      => array('platform_model' => 'ZenPad 10',               'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'P00C'      => array('platform_model' => 'ZenPad 10',               'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'P028'      => array('platform_model' => 'ZenPad 10',               'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2018),

        /* Asus phones */
        'A500KL'    => array('platform_model' => 'ZenFone 5\'',             'platform_year' => 2014),
        'T00K'      => array('platform_model' => 'ZenFone 5\' Lite',        'platform_year' => 2014),
        'Z00ED'     => array('platform_model' => 'ZenFone 2',               'platform_year' => 2015),
        'Z00ED'     => array('platform_model' => 'ZenFone 2',               'platform_year' => 2015),
        'Z00LD'     => array('platform_model' => 'ZenFone 2 Laser',         'platform_year' => 2015),
        'ZD551KL'   => array('platform_model' => 'ZenFone Selfie',          'platform_year' => 2015),
        'Z00UD'     => array('platform_model' => 'ZenFone Selfie',          'platform_year' => 2015),
        'Z00UDH'    => array('platform_model' => 'ZenFone Selfie',          'platform_year' => 2015),
        'ZB500KL'   => array('platform_model' => 'ZenFone Go',              'platform_year' => 2016),
        'ZB552KL'   => array('platform_model' => 'ZenFone Go',              'platform_year' => 2016),
        'ZC520TL'   => array('platform_model' => 'ZenFone 3 Max',           'platform_year' => 2016),
        'ZC550KL'   => array('platform_model' => 'ZenFone Max',             'platform_year' => 2016),
        'ZE520KL'   => array('platform_model' => 'ZenFone 3',               'platform_year' => 2016),
        'ZE552KL'   => array('platform_model' => 'ZenFone 3',               'platform_year' => 2016),
        'Z012D'     => array('platform_model' => 'ZenFone 3',               'platform_year' => 2016),
        'Z017D'     => array('platform_model' => 'ZenFone 3',               'platform_year' => 2016),
        'ZS570KL'   => array('platform_model' => 'ZenFone 3 Deluxe',        'platform_year' => 2016),
        'Z01BD'     => array('platform_model' => 'ZenFone 3 Laser',         'platform_year' => 2016),
        'X00DD'     => array('platform_model' => 'ZenFone 3 Max',           'platform_year' => 2016),
        'X008D'     => array('platform_model' => 'ZenFone 3 Max',           'platform_year' => 2016),
        'ZC553KL'   => array('platform_model' => 'ZenFone 3 Max',           'platform_year' => 2016),
        'ZU680KL'   => array('platform_model' => 'ZenFone 3 Ultra',         'platform_year' => 2016),
        'X007D'     => array('platform_model' => 'ZenFone Go',              'platform_year' => 2017),
        'ZE554KL'   => array('platform_model' => 'ZenFone 4',               'platform_year' => 2017),
        'X00LD'     => array('platform_model' => 'ZenFone 4',               'platform_year' => 2017),
        'X00HD'     => array('platform_model' => 'ZenFone 4',               'platform_year' => 2017),
        'Z01KDA'    => array('platform_model' => 'ZenFone 4',               'platform_year' => 2017),
        'X00ID'     => array('platform_model' => 'ZenFone 4 Max',           'platform_year' => 2017),
        'ZC520KL'   => array('platform_model' => 'ZenFone 4 Max',           'platform_year' => 2017),
        'ZS551KL'   => array('platform_model' => 'ZenFone 4 Pro',           'platform_year' => 2017),
        'Z01GS'     => array('platform_model' => 'ZenFone 4 Pro',           'platform_year' => 2017),
        'ZD553KL'   => array('platform_model' => 'ZenFone 4 Selfie',        'platform_year' => 2017),
        'ZD552KL'   => array('platform_model' => 'ZenFone 4 Selfie Pro',    'platform_year' => 2017),
        'Z01MD'     => array('platform_model' => 'ZenFone 4 Selfie Pro',    'platform_year' => 2017),
        'Z01MDA'    => array('platform_model' => 'ZenFone 4 Selfie Pro',    'platform_year' => 2017),
        'A002'      => array('platform_model' => 'ZenFone AR',              'platform_year' => 2017),
        'ZB501KL'   => array('platform_model' => 'ZenFone Live',            'platform_year' => 2017),
        'A007'      => array('platform_model' => 'ZenFone Live',            'platform_year' => 2017),
        'ZS620KL'   => array('platform_model' => 'ZenFone 5Z',              'platform_year' => 2017),
        'ZS620KL'   => array('platform_model' => 'ZenFone 5Z',              'platform_year' => 2017),
        'ZE553KL'   => array('platform_model' => 'ZenFone Zoom S',          'platform_year' => 2017),
        'X018D'     => array('platform_model' => 'Zenfone Max Plus M1',     'platform_year' => 2017),
        'X00TD'     => array('platform_model' => 'Zenfone Max Pro M1',      'platform_year' => 2018),
        'X00QD'     => array('platform_model' => 'Zenfone 5',               'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Asus',
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
