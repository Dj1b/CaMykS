<?php
/**
 * @brief Cubot client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Cubot.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.5
 * @date Creation: Mar 2019
 * @date Modification: Aug 2020
 * @copyright 2019 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Cubot client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_CubotClientDevice($deviceCode=false) {
    $deviceList = array(
        'C6W'           => array('platform_model' => 'C6W',         'platform_year' => 2013),
        'C7PLUS'        => array('platform_model' => 'C7 Plus',     'platform_year' => 2013),
        'C9+'           => array('platform_model' => 'C9 Plus',     'platform_year' => 2013),
        'C11'           => array('platform_model' => 'C11',         'platform_year' => 2013),
        'GT72E'         => array('platform_model' => 'GT72E',       'platform_year' => 2013),
        'GT72+'         => array('platform_model' => 'GT72+',       'platform_year' => 2013),
        'GT90'          => array('platform_model' => 'GT90',        'platform_year' => 2013),
        'GT99'          => array('platform_model' => 'GT99',        'platform_year' => 2013),
        'P9'            => array('platform_model' => 'P9',          'platform_year' => 2013),
        'GT88'          => array('platform_model' => 'GT88',        'platform_year' => 2014),
        'GT95'          => array('platform_model' => 'GT95',        'platform_year' => 2014),
        'P7'            => array('platform_model' => 'P7',          'platform_year' => 2014),
        'S108'          => array('platform_model' => 'S108',        'platform_year' => 2014),
        'X6'            => array('platform_model' => 'X6',          'platform_year' => 2014),
        'X9'            => array('platform_model' => 'X9',          'platform_year' => 2014),
        'X11'           => array('platform_model' => 'X11',         'platform_year' => 2015),
        'X12'           => array('platform_model' => 'X12',         'platform_year' => 2015),
        'X16'           => array('platform_model' => 'X16',         'platform_year' => 2015),
        'X17'           => array('platform_model' => 'X17',         'platform_year' => 2015),
        'X16 S'         => array('platform_model' => 'X16 S',       'platform_year' => 2016),
        'X17 S'         => array('platform_model' => 'X17 S',       'platform_year' => 2016),
        'H3'            => array('platform_model' => 'H3',          'platform_year' => 2017),
        'R9'            => array('platform_model' => 'R9',          'platform_year' => 2017),
        'X18'           => array('platform_model' => 'X18',         'platform_year' => 2017),
        'J3'            => array('platform_model' => 'J3',          'platform_year' => 2018),
        'R11'           => array('platform_model' => 'R11',         'platform_year' => 2018),
        'X18 PLUS'      => array('platform_model' => 'X18 Plus',    'platform_year' => 2018),
        'X19'           => array('platform_model' => 'X19',         'platform_year' => 2019),
        'X20 PRO'       => array('platform_model' => 'X20 Pro',     'platform_year' => 2019),

        'CHEETAH 2'     => array('platform_model' => 'Cheetah 2',   'platform_year' => 2016),
        'DINOSAUR'      => array('platform_model' => 'Dinosaur',    'platform_year' => 2016),
        'ECHO'          => array('platform_model' => 'Echo',        'platform_year' => 2016),
        'ECHO MAX'      => array('platform_model' => 'Echo Max',    'platform_year' => 2016),
        'KING KONG'     => array('platform_model' => 'King Kong',   'platform_year' => 2016),
        'KING KONG 3'   => array('platform_model' => 'King Kong 3', 'platform_year' => 2019),
        'MAGIC'         => array('platform_model' => 'Magic',       'platform_year' => 2017),
        'MANITO'        => array('platform_model' => 'Manito',      'platform_year' => 2016),
        'MAX'           => array('platform_model' => 'Max',         'platform_year' => 2016),
        'NOTE PLUS'     => array('platform_model' => 'Note Plus',   'platform_year' => 2017),
        'NOTE S'        => array('platform_model' => 'Note S',      'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
        return $deviceList;
    $deviceCode = strtoupper($deviceCode);

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Cubot',
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
