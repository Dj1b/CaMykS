<?php
/**
 * @brief Alcatel client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Alcatel.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.11
 * @date Creation: Apr 2018
 * @date Modification: Apr 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Alcatel client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AlcatelClientDevice($deviceCode='') {
    $deviceList = array(
        /* Alcatel tablets */
        'ONETOUCH POP 7 LTE'    => array('platform_model' => 'OneTouch Pop 7 LTE',  'platform_year' => 2014, 'platform_type' => 'tablet',    'platform_format' => 'tablet'),
        '9003X'                 => array('platform_model' => 'OneTouch Pixi 4 7.0', 'platform_year' => 2016, 'platform_type' => 'tablet',    'platform_format' => 'tablet'),
        '9009G'                 => array('platform_model' => 'OneTouch 1T 7',       'platform_year' => 2019, 'platform_type' => 'tablet',    'platform_format' => 'tablet'),

        /* Alcatel mobiles */
        'Orange KLIF' => array('system_title' => 'Firefox OS',          'platform_year' => 2015),

        'A460G' => array('platform_model' => 'OneTouch Pixi Pulsar',    'platform_year' => 2015),

        '4007X' => array('platform_model' => 'OneTouch Pixi',           'platform_year' => 2013),
        '4009D' => array('platform_model' => 'OneTouch Pixi 3 (3.5\')', 'platform_year' => 2014),
        '4009X' => array('platform_model' => 'OneTouch Pixi 3 (3.5\')', 'platform_year' => 2014),
        '4010D' => array('platform_model' => 'OneTouch T\'POP',         'platform_year' => 2013),
        '4010X' => array('platform_model' => 'OneTouch T\'POP',         'platform_year' => 2013),
        '4013D' => array('platform_model' => 'OneTouch Pixi 3 (4\')',   'platform_year' => 2015),
        '4013X' => array('platform_model' => 'OneTouch Pixi 3 (4\')',   'platform_year' => 2015),
        '4015D' => array('platform_model' => 'OneTouch Pop C1',         'platform_year' => 2014),
        '4016D' => array('platform_model' => 'OneTouch Pop C1',         'platform_year' => 2014),
        '4016X' => array('platform_model' => 'OneTouch Pixi 2',         'platform_year' => 2014),
        '4017D' => array('platform_model' => 'OneTouch Pixi 4',         'platform_year' => 2016),
        '4017X' => array('platform_model' => 'OneTouch Pixi 4',         'platform_year' => 2016),
        '4018D' => array('platform_model' => 'OneTouch Pop C1',         'platform_year' => 2014),
        '4018M' => array('platform_model' => 'OneTouch Pop D1',         'platform_year' => 2014),
        '4030A' => array('platform_model' => 'OneTouch S\'Pop',         'platform_year' => 2013),
        '4030D' => array('platform_model' => 'OneTouch S\'Pop',         'platform_year' => 2013),
        '4032D' => array('platform_model' => 'OneTouch Pop C2',         'platform_year' => 2015),
        '4032X' => array('platform_model' => 'OneTouch Pop C2',         'platform_year' => 2015),
        '4033X' => array('platform_model' => 'OneTouch Pop C3',         'platform_year' => 2013),
        '4034D' => array('platform_model' => 'Pixi 4',                  'platform_year' => 2016),
        '5015D' => array('platform_model' => 'OneTouch Pop 3',          'platform_year' => 2015),
        '5015X' => array('platform_model' => 'OneTouch Pop 3',          'platform_year' => 2015),
        '5020X' => array('platform_model' => 'OneTouch M\'Pop',         'platform_year' => 2013),
        '5023F' => array('platform_model' => 'PIxi 4 Plus Power',       'platform_year' => 2016),
        '5024D' => array('platform_model' => '1S',                      'platform_year' => 2019),
        '5026D' => array('platform_model' => '3C',                      'platform_year' => 2018),
        '5035D' => array('platform_model' => 'OneTouch X\'Pop',         'platform_year' => 2013),
        '5036D' => array('platform_model' => 'OneTouch Pop C5',         'platform_year' => 2013),
        '5038A' => array('platform_model' => 'OneTouch Pop D5',         'platform_year' => 2014),
        '5038X' => array('platform_model' => 'OneTouch Pop D5',         'platform_year' => 2014),
        '5042D' => array('platform_model' => 'OneTouch Pop 2',          'platform_year' => 2014),
        '5042G' => array('platform_model' => 'OneTouch Pop 2',          'platform_year' => 2014),
        '5042X' => array('platform_model' => 'OneTouch Pop 2',          'platform_year' => 2014),
        '5044D' => array('platform_model' => 'U5',                      'platform_year' => 2017),
        '5046D' => array('platform_model' => 'A3',                      'platform_year' => 2017),
        '5050S' => array('platform_model' => 'OneTouch Pop S3',         'platform_year' => 2014),
        '5050X' => array('platform_model' => 'OneTouch Pop S3',         'platform_year' => 2014),
        '5050Y' => array('platform_model' => 'OneTouch Pop S3',         'platform_year' => 2014),
        '5051D' => array('platform_model' => 'OneTouch Pop 4 (5\')',    'platform_year' => 2016),
        '5051X' => array('platform_model' => 'OneTouch Pop 4 (5\')',    'platform_year' => 2016),
        '5054D' => array('platform_model' => 'OneTouch Pop 3 (5.5\')',  'platform_year' => 2016),
        '5056D' => array('platform_model' => 'OneTouch Pop 4 (5.5\')',  'platform_year' => 2016),
        '5056O' => array('platform_model' => 'OneTouch Allura',         'platform_year' => 2017),
        '5056X' => array('platform_model' => 'OneTouch Pop 4 (5.5\')',  'platform_year' => 2016),
        '5070D' => array('platform_model' => 'OneTouch Pop Star 4G',    'platform_year' => 2015),
        '5070X' => array('platform_model' => 'OneTouch Pop Star 4G',    'platform_year' => 2015),
        '5080A' => array('platform_model' => 'Shine Lite',              'platform_year' => 2016),
        '5085D' => array('platform_model' => 'A5 Led',                  'platform_year' => 2017),
        '5085J' => array('platform_model' => 'A5 Led',                  'platform_year' => 2017),
        '5086D' => array('platform_model' => 'A5',                      'platform_year' => 2018),
        '5090Y' => array('platform_model' => 'A7',                      'platform_year' => 2017),
        '5095K' => array('platform_model' => 'OneTouch Pop 4S',         'platform_year' => 2016),
        '5095Y' => array('platform_model' => 'OneTouch Pop 4S',         'platform_year' => 2016),
        '5099D' => array('platform_model' => '3V',                      'platform_year' => 2018),
        '5099I' => array('platform_model' => '3V',                      'platform_year' => 2018),
        '5099Y' => array('platform_model' => '3V',                      'platform_year' => 2018),
        '6010D' => array('platform_model' => 'OneTouch Star',           'platform_year' => 2013),
        '6010X' => array('platform_model' => 'OneTouch Star',           'platform_year' => 2013),
        '6012D' => array('platform_model' => 'OneTouch Idol Mini',      'platform_year' => 2014),
        '6012X' => array('platform_model' => 'OneTouch Idol Mini',      'platform_year' => 2014),
        '6016D' => array('platform_model' => 'OneTouch Idol 2 Mini',    'platform_year' => 2014),
        '6016X' => array('platform_model' => 'OneTouch Idol 2 Mini',    'platform_year' => 2014),
        '6030D' => array('platform_model' => 'OneTouch Idol',           'platform_year' => 2013),
        '6032A' => array('platform_model' => 'OneTouch Idol Alpha',     'platform_year' => 2013),
        '6033A' => array('platform_model' => 'OneTouch Idol Ultra',     'platform_year' => 2013),
        '6034R' => array('platform_model' => 'OneTouch Idol S',         'platform_year' => 2013),
        '6036Y' => array('platform_model' => 'OneTouch Idol 2 Mini S',  'platform_year' => 2014),
        '6037Y' => array('platform_model' => 'OneTouch Idol 2',         'platform_year' => 2014),
        '6039K' => array('platform_model' => 'OneTouch Idol 3 (4.7\')', 'platform_year' => 2015),
        '6039S' => array('platform_model' => 'OneTouch Idol 3 (4.7\')', 'platform_year' => 2015),
        '6039Y' => array('platform_model' => 'OneTouch Idol 3 (4.7\')', 'platform_year' => 2015),
        '6040D' => array('platform_model' => 'OneTouch Idol X',         'platform_year' => 2013),
        '6040X' => array('platform_model' => 'OneTouch Idol X',         'platform_year' => 2013),
        '6043D' => array('platform_model' => 'OneTouch Idol X+',        'platform_year' => 2013),
        '6044D' => array('platform_model' => 'OneTouch Pop Up',         'platform_year' => 2015),
        '6045Y' => array('platform_model' => 'OneTouch Idol 3 (5.5\')', 'platform_year' => 2015),
        '6050Y' => array('platform_model' => 'OneTouch Idol 2S',        'platform_year' => 2014),
        '6055K' => array('platform_model' => 'Idol 4',                  'platform_year' => 2016),
        '6055P' => array('platform_model' => 'Idol 4',                  'platform_year' => 2016),
        '6070K' => array('platform_model' => 'Idol 4S',                 'platform_year' => 2016),
        '6070X' => array('platform_model' => 'Idol 4S',                 'platform_year' => 2016),
        '7041D' => array('platform_model' => 'OneTouch Pop C7',         'platform_year' => 2013),
        '7041X' => array('platform_model' => 'OneTouch Pop C7',         'platform_year' => 2013),
        '7044X' => array('platform_model' => 'OneTouch Pop 2 (5\')',    'platform_year' => 2015),
        '7045Y' => array('platform_model' => 'OneTouch Pop S7',         'platform_year' => 2014),
        '7047D' => array('platform_model' => 'OneTouch Pop C9',         'platform_year' => 2014),
        '7048X' => array('platform_model' => 'OneTouch Go Play',        'platform_year' => 2015),
        '7050Y' => array('platform_model' => 'OneTouch Pop S9',         'platform_year' => 2014),
        '7070X' => array('platform_model' => 'Pop 4',                   'platform_year' => 2016),
        '8000D' => array('platform_model' => 'OneTouch Scribe',         'platform_year' => 2013),
        '8008D' => array('platform_model' => 'OneTouch Scribe HD',      'platform_year' => 2013),
        '8020D' => array('platform_model' => 'OneTouch Hero',           'platform_year' => 2013),
        '8020X' => array('platform_model' => 'OneTouch Hero',           'platform_year' => 2013),
        '8030Y' => array('platform_model' => 'OneTouch Hero 2',         'platform_year' => 2014),
        '8050D' => array('platform_model' => 'A2 XL',                   'platform_year' => 2017),
        '9001D' => array('platform_model' => 'Pixi 4',                  'platform_year' => 2016),
        '9001X' => array('platform_model' => 'Pixi 4',                  'platform_year' => 2016),
        '9008D' => array('platform_model' => 'A3 XL',                   'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Alcatel',
        'platform_country'  => 'fr',
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
