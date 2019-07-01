<?php
/**
 * @brief HiSense client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/HiSense.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.5
 * @date Creation: Jul 2018
 * @date Modification: Jun 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return HiSense client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_HiSenseClientDevice($deviceCode='') {
    $deviceList = array(
        'EG950'     => array('platform_model' => 'EG950',               'platform_year' => 2012),
        'T950'      => array('platform_model' => 'T950',                'platform_year' => 2012),
        'EG929'     => array('platform_model' => 'EG929',               'platform_year' => 2013),
        'EG939'     => array('platform_model' => 'EG939',               'platform_year' => 2013),
        'T958'      => array('platform_model' => 'T958',                'platform_year' => 2013),
        'EG978'     => array('platform_model' => 'EG978',               'platform_year' => 2013),
        'U936'      => array('platform_model' => 'U936',                'platform_year' => 2013),
        'U939'      => array('platform_model' => 'U939',                'platform_year' => 2013),
        'U970'      => array('platform_model' => 'Infinity Prime 1',    'platform_year' => 2013),
        'U971'      => array('platform_model' => 'Infinity Prime 1',    'platform_year' => 2013),
        'U978'      => array('platform_model' => 'U978',                'platform_year' => 2013),
        'U980'      => array('platform_model' => 'MIRA II',             'platform_year' => 2013),
        'EG980'     => array('platform_model' => 'EG980',               'platform_year' => 2014),
        'H910'      => array('platform_model' => 'H910',                'platform_year' => 2014),
        'L691'      => array('platform_model' => 'L691',                'platform_year' => 2014),
        'T928'      => array('platform_model' => 'T928',                'platform_year' => 2014),
        'U98'       => array('platform_model' => 'U98',                 'platform_year' => 2014),
        'U609'      => array('platform_model' => 'U609',                'platform_year' => 2014),
        'U966'      => array('platform_model' => 'Copacabana',          'platform_year' => 2014),
        'U980B'     => array('platform_model' => 'U980B',               'platform_year' => 2014),
        'X1'        => array('platform_model' => 'X1',                  'platform_year' => 2014),
        'X8T'       => array('platform_model' => 'X8T',                 'platform_year' => 2014),
        'X68T'      => array('platform_model' => 'X68T',                'platform_year' => 2014),
        'E621T'     => array('platform_model' => 'E621T',               'platform_year' => 2015),
        'F20'       => array('platform_model' => 'F20',                 'platform_year' => 2015),
        'G610'      => array('platform_model' => 'G610',                'platform_year' => 2015),
        'HU602'     => array('platform_model' => 'Glory',               'platform_year' => 2015),
        'L695'      => array('platform_model' => 'L695',                'platform_year' => 2015),
        'L682'      => array('platform_model' => 'Infinity Pulse',      'platform_year' => 2015),
        'U601'      => array('platform_model' => 'Glory',               'platform_year' => 2015),
        'U602'      => array('platform_model' => 'Glory',               'platform_year' => 2015),
        'U610'      => array('platform_model' => 'U610',                'platform_year' => 2015),
        'U688'      => array('platform_model' => 'U688',                'platform_year' => 2015),
        'U961'      => array('platform_model' => 'Pure 1 Mini',         'platform_year' => 2015),
        'U988'      => array('platform_model' => 'U988',                'platform_year' => 2015),
        'U989 Pro'  => array('platform_model' => 'U989 Pro ',           'platform_year' => 2015),
        'C1'        => array('platform_model' => 'C1',                  'platform_year' => 2016),
        'F22'       => array('platform_model' => 'F22',                 'platform_year' => 2016),
        'F31'       => array('platform_model' => 'F3 Pro',              'platform_year' => 2016),
        'L671'      => array('platform_model' => 'Infinity PureShot',   'platform_year' => 2016),
        'L675'      => array('platform_model' => 'Infinity Lite S',     'platform_year' => 2016),
        'L675 Pro'  => array('platform_model' => 'L675 Pro',            'platform_year' => 2016),
        'L676'      => array('platform_model' => 'L676',                'platform_year' => 2016),
        'L678'      => array('platform_model' => 'Staraddict 5',        'platform_year' => 2016),
        'L681'      => array('platform_model' => 'L681',                'platform_year' => 2016),
        'L695'      => array('platform_model' => 'L695',                'platform_year' => 2016),
        'L697'      => array('platform_model' => 'L697',                'platform_year' => 2016),
        'C20'       => array('platform_model' => 'Kingkong 2',          'platform_year' => 2016),
        'E51'       => array('platform_model' => 'Infinity H3S',        'platform_year' => 2016),
        'T963'      => array('platform_model' => 'T963',                'platform_year' => 2016),
        'U989'      => array('platform_model' => 'Infinity U989',       'platform_year' => 2016),
        'C30'       => array('platform_model' => 'Rock',                'platform_year' => 2017),
        'C30 Lite'  => array('platform_model' => 'C30 Lite',            'platform_year' => 2017),
        'E76'       => array('platform_model' => 'Infinity Elegance',   'platform_year' => 2017),
        'F10'       => array('platform_model' => 'F10',                 'platform_year' => 2017),
        'F23'       => array('platform_model' => 'F23',                 'platform_year' => 2017),
        'F30'       => array('platform_model' => 'F30',                 'platform_year' => 2017),
        'F32'       => array('platform_model' => 'F32',                 'platform_year' => 2017),
        'F102'      => array('platform_model' => 'F102',                'platform_year' => 2017),
        'L830'      => array('platform_model' => 'L830',                'platform_year' => 2017),
        'T5'        => array('platform_model' => 'T5',                  'platform_year' => 2017),
        'T5 Plus'   => array('platform_model' => 'T5 Plus',             'platform_year' => 2017),
        'T5 Pro'    => array('platform_model' => 'T5 Pro',              'platform_year' => 2017),
        'T203'      => array('platform_model' => 'T203',                'platform_year' => 2017),
        'U601S'     => array('platform_model' => 'U601S',               'platform_year' => 2017),
        'U601S Pro' => array('platform_model' => 'U601S Pro',           'platform_year' => 2017),
        'U962'      => array('platform_model' => 'U962',                'platform_year' => 2017),
        'U963'      => array('platform_model' => 'U963',                'platform_year' => 2017),
        'U972'      => array('platform_model' => 'Infinity U972',       'platform_year' => 2017),
        'U972 Pro'  => array('platform_model' => 'U972 Pro',            'platform_year' => 2017),
        'F17 Pro'   => array('platform_model' => 'Infinity F17 Pro',    'platform_year' => 2018),
        'F24'       => array('platform_model' => 'Infinity F24',        'platform_year' => 2018),
        'F26'       => array('platform_model' => 'F26',                 'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Hisense',
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
