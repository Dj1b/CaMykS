<?php
/**
 * @brief Sony client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Sony.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.36
 * @date Creation: Apr 2018
 * @date Modification: Oct 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Sony client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_SonyClientDevice($deviceCode='') {
    $deviceList = array(
        /* Sony tablets */
        'SGP321'    => array('platform_model' => 'Xperia Z Tablet',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2013),
        'SGP511'    => array('platform_model' => 'Xperia Z2 Tablet',            'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'SGP512'    => array('platform_model' => 'Xperia Z2 Tablet',            'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'SGP611'    => array('platform_model' => 'Xperia Z3 Tablet Compact',    'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'SGP621'    => array('platform_model' => 'Xperia Z3 Tablet Compact',    'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'SGP712'    => array('platform_model' => 'Xperia Z4 Tablet',            'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),

        /* Sony phones */
        'LT28i'     => array('platform_model' => 'Xperia ion',              'platform_year' => 2012),

        'C1505'     => array('platform_model' => 'Xperia E',                'platform_year' => 2013),
        'C2105'     => array('platform_model' => 'Xperia L',                'platform_year' => 2013),
        'C5303'     => array('platform_model' => 'Xperia SP',               'platform_year' => 2013),
        'C6603'     => array('platform_model' => 'Xperia Z',                'platform_year' => 2013),
        'D6503'     => array('platform_model' => 'Xperia Z2',               'platform_year' => 2014),
        'D2005'     => array('platform_model' => 'Xperia E1',               'platform_year' => 2014),
        'D2203'     => array('platform_model' => 'Xperia E3',               'platform_year' => 2014),
        'D2303'     => array('platform_model' => 'Xperia M2',               'platform_year' => 2014),
        'D2305'     => array('platform_model' => 'Xperia M2',               'platform_year' => 2014),
        'D2306'     => array('platform_model' => 'Xperia M2',               'platform_year' => 2014),
        'D2403'     => array('platform_model' => 'Xperia M2 Aqua',          'platform_year' => 2014),
        'D5303'     => array('platform_model' => 'Xperia T2 Ultra',         'platform_year' => 2014),
        'D5503'     => array('platform_model' => 'Xperia Z1 Compact',       'platform_year' => 2014),
        'D5803'     => array('platform_model' => 'Xperia Z3 Compact',       'platform_year' => 2014),
        'D6603'     => array('platform_model' => 'Xperia Z3',               'platform_year' => 2014),
        'D6683'     => array('platform_model' => 'Xperia Z3 Dual Sim',      'platform_year' => 2015),
        'E5303'     => array('platform_model' => 'Xperia C4',               'platform_year' => 2015),
        'E5603'     => array('platform_model' => 'Xperia M5',               'platform_year' => 2015),
        'E5633'     => array('platform_model' => 'Xperia M5',               'platform_year' => 2015),
        'E5823'     => array('platform_model' => 'Xperia Z5 Compact',       'platform_year' => 2015),
        'E6533'     => array('platform_model' => 'Xperia Z3+',              'platform_year' => 2015),
        'E6633'     => array('platform_model' => 'Xperia Z5',               'platform_year' => 2015),
        'E6653'     => array('platform_model' => 'Xperia Z5',               'platform_year' => 2015),
        'E6683'     => array('platform_model' => 'Xperia Z5',               'platform_year' => 2015),
        'E6853'     => array('platform_model' => 'Xperia Z5 Premium',       'platform_year' => 2015),
        'F5121'     => array('platform_model' => 'Xperia X',                'platform_year' => 2016),
        'F5122'     => array('platform_model' => 'Xperia X',                'platform_year' => 2016),
        'F3111'     => array('platform_model' => 'Xperia XA',               'platform_year' => 2016),
        'F3112'     => array('platform_model' => 'Xperia XA',               'platform_year' => 2016),
        'F3211'     => array('platform_model' => 'Xperia XA Ultra',         'platform_year' => 2016),
        'F3311'     => array('platform_model' => 'Xperia E5',               'platform_year' => 2016),
        'F5121'     => array('platform_model' => 'Xperia X',                'platform_year' => 2016),
        'F5321'     => array('platform_model' => 'Xperia X Compact',        'platform_year' => 2016),
        'F8331'     => array('platform_model' => 'Xperia XZ',               'platform_year' => 2016),
        'F8332'     => array('platform_model' => 'Xperia XZ',               'platform_year' => 2016),
        'G3112'     => array('platform_model' => 'Xperia XA1',              'platform_year' => 2017),
        'G3121'     => array('platform_model' => 'Xperia XA1',              'platform_year' => 2017),
        'G3212'     => array('platform_model' => 'Xperia XA1 Ultra',        'platform_year' => 2017),
        'G3221'     => array('platform_model' => 'Xperia XA1 Ultra',        'platform_year' => 2017),
        'G3311'     => array('platform_model' => 'Xperia L1',               'platform_year' => 2017),
        'G3312'     => array('platform_model' => 'Xperia L1',               'platform_year' => 2017),
        'G3412'     => array('platform_model' => 'Xperia XA1 Plus',         'platform_year' => 2017),
        'G3416'     => array('platform_model' => 'Xperia XA1 Plus',         'platform_year' => 2017),
        'G3421'     => array('platform_model' => 'Xperia XA1 Plus',         'platform_year' => 2017),
        'G3423'     => array('platform_model' => 'Xperia XA1 Plus',         'platform_year' => 2017),
        'G8141'     => array('platform_model' => 'Xperia XZ Premium',       'platform_year' => 2017),
        'G8142'     => array('platform_model' => 'Xperia XZ Premium',       'platform_year' => 2017),
        'G8341'     => array('platform_model' => 'Xperia XZ1',              'platform_year' => 2017),
        'G8342'     => array('platform_model' => 'Xperia XZ1',              'platform_year' => 2017),
        'G8343'     => array('platform_model' => 'Xperia XZ1',              'platform_year' => 2017),
        'G8441'     => array('platform_model' => 'Xperia XZ1 Compact',      'platform_year' => 2017),
        'H3113'     => array('platform_model' => 'Xperia XA2',              'platform_year' => 2018),
        'H3311'     => array('platform_model' => 'Xperia L2',               'platform_year' => 2018),
        'H3213'     => array('platform_model' => 'Xperia XA2 Ultra',        'platform_year' => 2018),
        'H3413'     => array('platform_model' => 'Xperia XA2 Plus',         'platform_year' => 2018),
        'H4113'     => array('platform_model' => 'Xperia XA2',              'platform_year' => 2018),
        'H4133'     => array('platform_model' => 'Xperia XA2',              'platform_year' => 2018),
        'H4213'     => array('platform_model' => 'Xperia XA2 Ultra',        'platform_year' => 2018),
        'H4413'     => array('platform_model' => 'Xperia XA2 Plus',         'platform_year' => 2018),
        'H8216'     => array('platform_model' => 'Xperia XZ2',              'platform_year' => 2018),
        'H8266'     => array('platform_model' => 'Xperia XZ2',              'platform_year' => 2018),
        'H8314'     => array('platform_model' => 'Xperia XZ2',              'platform_year' => 2018),
        'H8324'     => array('platform_model' => 'Xperia XZ2 Compact',      'platform_year' => 2018),
        'H8416'     => array('platform_model' => 'Xperia XZ3',              'platform_year' => 2018),
        'H9436'     => array('platform_model' => 'Xperia XZ3',              'platform_year' => 2018),
        'H9493'     => array('platform_model' => 'Xperia XZ3',              'platform_year' => 2018),
        'I4113'     => array('platform_model' => 'Xperia 10',               'platform_year' => 2019),
        'I4213'     => array('platform_model' => 'Xperia 10 Plus',          'platform_year' => 2019),

        'SOV31'     => array('platform_model' => 'Xperia Z4',               'platform_year' => 2015),
        'SOV32'     => array('platform_model' => 'Xperia Z5',               'platform_year' => 2015),
        'SOV33'     => array('platform_model' => 'Xperia X Performance',    'platform_year' => 2016),
        'SOV34'     => array('platform_model' => 'Xperia XZ',               'platform_year' => 2016),
        'SOV35'     => array('platform_model' => 'Xperia XZs',              'platform_year' => 2017),
        'SOV36'     => array('platform_model' => 'Xperia XZ1',              'platform_year' => 2018),
        'SOV37'     => array('platform_model' => 'Xperia XZ2',              'platform_year' => 2018),

        'SO-03H'    => array('platform_model' => 'Xperia Z5 Premium',       'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Sony',
        'platform_country'  => 'jp',
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
