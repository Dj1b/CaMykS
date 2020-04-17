<?php
/**
 * @brief LG client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/LG.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.27
 * @date Creation: Apr 2018
 * @date Modification: Apr 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return LG client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LGClientDevice($deviceCode='') {
    $deviceList = array(
        /* LG Tablets */
        'V500'  => array('platform_model' => 'G Pad 8.3',   'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2013),
        'V400'  => array('platform_model' => 'G Pad 7.0',   'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2014),
        'V410'  => array('platform_model' => 'G Pad 7.0',   'platform_type' => 'tablet', 'platform_format'  => 'tablet',    'platform_year' => 2014),

        /* LG mobiles */
        'D160'      => array('platform_model' => 'L40',             'platform_year' => 2014),
        'D290'      => array('platform_model' => 'L Fino',          'platform_year' => 2014),
        'D315'      => array('platform_model' => 'F70',             'platform_year' => 2014),
        'D320'      => array('platform_model' => 'L70',             'platform_year' => 2014),
        'D335'      => array('platform_model' => 'L Bello',         'platform_year' => 2014),
        'D405'      => array('platform_model' => 'L90',             'platform_year' => 2014),
        'D505'      => array('platform_model' => 'Optimus F6',      'platform_year' => 2013),
        'D620'      => array('platform_model' => 'G2 Mini',         'platform_year' => 2014),
        'D722'      => array('platform_model' => 'G3 S',            'platform_year' => 2014),
        'D802'      => array('platform_model' => 'Nexus 5',         'platform_year' => 2013),
        'D821'      => array('platform_model' => 'G2',              'platform_year' => 2013),
        'D852'      => array('platform_model' => 'G3',              'platform_year' => 2014),
        'D855'      => array('platform_model' => 'G3',              'platform_year' => 2014),
        'D855'      => array('platform_model' => 'G Flex',          'platform_year' => 2014),
        'E410'      => array('platform_model' => 'Optimus L1 II',   'platform_year' => 2013),
        'E430'      => array('platform_model' => 'Optimus L3 II',   'platform_year' => 2013),
        'E440'      => array('platform_model' => 'Optimus L4 II',   'platform_year' => 2013),
        'E460'      => array('platform_model' => 'Optimus L5 II',   'platform_year' => 2013),
        'E610'      => array('platform_model' => 'Optimus L5',      'platform_year' => 2012),
        'E960'      => array('platform_model' => 'Nexus 4',         'platform_year' => 2012),
        'G710'      => array('platform_model' => 'G7 ThinQ',        'platform_year' => 2018),
        'G810'      => array('platform_model' => 'G8s ThinQ',       'platform_year' => 2019),
        'H340'      => array('platform_model' => 'Leon',            'platform_year' => 2015),
        'H812'      => array('platform_model' => 'G4',              'platform_year' => 2015),
        'H815'      => array('platform_model' => 'G4',              'platform_year' => 2015),
        'H818'      => array('platform_model' => 'G4',              'platform_year' => 2015),
        'H831'      => array('platform_model' => 'G5',              'platform_year' => 2016),
        'H850'      => array('platform_model' => 'G5',              'platform_year' => 2016),
        'H870'      => array('platform_model' => 'G6',              'platform_year' => 2017),
        'H870D'     => array('platform_model' => 'G6',              'platform_year' => 2017),
        'H870DS'    => array('platform_model' => 'G6',              'platform_year' => 2017),
        'H873'      => array('platform_model' => 'G6',              'platform_year' => 2017),
        'H930'      => array('platform_model' => 'V30',             'platform_year' => 2017),
        'H955'      => array('platform_model' => 'G Flex 2',        'platform_year' => 2015),
        'H990'      => array('platform_model' => 'V20',             'platform_year' => 2016),
        'L82VL'     => array('platform_model' => 'Stylo 2 LTE',     'platform_year' => 2016),
        'L160L'     => array('platform_model' => 'Optimus LTE2',    'platform_year' => 2012),
        'L414DL'    => array('platform_model' => 'Premier Pro',     'platform_year' => 2018),
        'LS996'     => array('platform_model' => 'G Flex 2',        'platform_year' => 2015),
        'K120'      => array('platform_model' => 'Spree',           'platform_year' => 2016),
        'K371'      => array('platform_model' => 'Phoenix 2',       'platform_year' => 2016),
        'K430'      => array('platform_model' => 'K10',             'platform_year' => 2017),
        'K580'      => array('platform_model' => 'X Cam',           'platform_year' => 2016),
        'M700'      => array('platform_model' => 'Q6 Alpha',        'platform_year' => 2017),
        'MP450'     => array('platform_model' => 'Stylo 3 Plus',    'platform_year' => 2017),
        'M160'      => array('platform_model' => 'K4',              'platform_year' => 2017),
        'M250'      => array('platform_model' => 'K10',             'platform_year' => 2017),
        'M327'      => array('platform_model' => 'X Charge',        'platform_year' => 2017),
        'M400'      => array('platform_model' => 'Stylus 3',        'platform_year' => 2017),
        'M470'      => array('platform_model' => 'Stylo 3 Plus',    'platform_year' => 2017),
        'P715'      => array('platform_model' => 'Optimus L7 II',   'platform_year' => 2013),
        'P875'      => array('platform_model' => 'Optimus F5',      'platform_year' => 2013),
        'P920'      => array('platform_model' => 'Optimus 3D',      'platform_year' => 2011),
        'Q710'      => array('platform_model' => 'Stylo 4',         'platform_year' => 2018),
        'SP200'     => array('platform_model' => 'Tribute Dynasty', 'platform_year' => 2018),
        'TP260'     => array('platform_model' => 'K20 Plus',        'platform_year' => 2019),
        'Q720'      => array('platform_model' => 'Stylo 5',         'platform_year' => 2019),
        'V405'      => array('platform_model' => 'V40',             'platform_year' => 2018),
        'VS986'     => array('platform_model' => 'G4',              'platform_year' => 2015),
        'VS987'     => array('platform_model' => 'G5',              'platform_year' => 2016),
        'X210'      => array('platform_model' => 'K7',              'platform_year' => 2016),
        'X410'      => array('platform_model' => 'K30',             'platform_year' => 2018),

    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'LG',
        'platform_country'  => 'kr',
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
