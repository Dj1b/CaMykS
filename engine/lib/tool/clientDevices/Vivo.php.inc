<?php
/**
 * @brief Vivo client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Vivo.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: May 2018
 * @date Modification: Nov 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Vivo client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_VivoClientDevice($deviceCode='') {
    $deviceList = array(
        '1601'          => array('platform_model' => 'V5',          'platform_year' => 2016),
        '1603'          => array('platform_model' => 'Y55L',        'platform_year' => 2016),
        '1606'          => array('platform_model' => 'V5 Plus',     'platform_year' => 2016),
        '1613'          => array('platform_model' => 'Y25',         'platform_year' => 2017),
        '1609'          => array('platform_model' => 'Y66',         'platform_year' => 2017),
        '1016'          => array('platform_model' => 'Y55S',        'platform_year' => 2017),
        '1017'          => array('platform_model' => 'V7 Plus',     'platform_year' => 2017),
        '1716'          => array('platform_model' => 'V7 Plus',     'platform_year' => 2017),
        '1718'          => array('platform_model' => 'V7',          'platform_year' => 2017),
        '1714'          => array('platform_model' => 'Y69',         'platform_year' => 2018),
        '1723'          => array('platform_model' => 'V9',          'platform_year' => 2018),
        '1724'          => array('platform_model' => 'Y71',         'platform_year' => 2018),
        '1812'          => array('platform_model' => 'Y81i',        'platform_year' => 2018),
        '1816'          => array('platform_model' => 'Y91i',        'platform_year' => 2019),
        '1901'          => array('platform_model' => 'X27',         'platform_year' => 2019),
        '1902'          => array('platform_model' => 'X27 Pro',     'platform_year' => 2019),

        'Y11T'          => array('platform_model' => 'Y11T',        'platform_year' => 2013),
        'Y17'           => array('platform_model' => 'Y17',         'platform_year' => 2014),
        'Y23L'          => array('platform_model' => 'Y23L',        'platform_year' => 2014),
        'Y622'          => array('platform_model' => 'Y622',        'platform_year' => 2014),
        'Y623'          => array('platform_model' => 'Y623',        'platform_year' => 2014),
        'Y627'          => array('platform_model' => 'Y627',        'platform_year' => 2014),
        'Y913'          => array('platform_model' => 'Y913',        'platform_year' => 2014),
        'Y927'          => array('platform_model' => 'Y927',        'platform_year' => 2014),
        'Y928'          => array('platform_model' => 'Y928',        'platform_year' => 2014),
        'Y923'          => array('platform_model' => 'Y927',        'platform_year' => 2015),
        'Y15S'          => array('platform_model' => 'Y15S',        'platform_year' => 2015),
        'Y29L'          => array('platform_model' => 'Y29L',        'platform_year' => 2015),
        'Y33'           => array('platform_model' => 'Y33',         'platform_year' => 2015),
        'Y35'           => array('platform_model' => 'Y35',         'platform_year' => 2015),
        'Y35A'          => array('platform_model' => 'Y35A',        'platform_year' => 2015),
        'Y37'           => array('platform_model' => 'Y37',         'platform_year' => 2015),
        'Y37A'          => array('platform_model' => 'Y37A',        'platform_year' => 2015),
        'Y51'           => array('platform_model' => 'Y51',         'platform_year' => 2015),
        'Y51A'          => array('platform_model' => 'Y51A',        'platform_year' => 2015),
        'Y21'           => array('platform_model' => 'Y21',         'platform_year' => 2016),
        'Y21L'          => array('platform_model' => 'Y21L',        'platform_year' => 2016),
        'Y31A'          => array('platform_model' => 'Y31A',        'platform_year' => 2016),
        'Y31L'          => array('platform_model' => 'Y31L',        'platform_year' => 2016),
        'Y51L'          => array('platform_model' => 'Y51L',        'platform_year' => 2016),
        'Y51T L'        => array('platform_model' => 'Y51T L',      'platform_year' => 2016),
        'Y55'           => array('platform_model' => 'Y55',         'platform_year' => 2016),
        'Y55A'          => array('platform_model' => 'Y55A',        'platform_year' => 2016),
        'Y66L'          => array('platform_model' => 'Y66L',        'platform_year' => 2016),
        'Y55A'          => array('platform_model' => 'Y55A',        'platform_year' => 2016),
        'Y67'           => array('platform_model' => 'Y67',         'platform_year' => 2016),
        'Y53'           => array('platform_model' => 'Y53',         'platform_year' => 2017),
        'Y67A'          => array('platform_model' => 'Y67A',        'platform_year' => 2017),
        'Y67L'          => array('platform_model' => 'Y67L',        'platform_year' => 2017),
        'Y75A'          => array('platform_model' => 'Y75A',        'platform_year' => 2017),
        'Y79A'          => array('platform_model' => 'Y79A',        'platform_year' => 2017),

        'X520L'         => array('platform_model' => 'Xplay 3S',    'platform_year' => 2013),
        'X3S'           => array('platform_model' => 'X3S',         'platform_year' => 2014),
        'X5'            => array('platform_model' => 'X5',          'platform_year' => 2014),
        'X5Max'         => array('platform_model' => 'X5 Max',      'platform_year' => 2014),
        'X5Max S'       => array('platform_model' => 'X5 Max S',    'platform_year' => 2014),
        'X5Max V'       => array('platform_model' => 'X5 Max V',    'platform_year' => 2014),
        'X5Pro'         => array('platform_model' => 'X5 Pro',      'platform_year' => 2014),
        'X5Pro D'       => array('platform_model' => 'X5 Pro D',    'platform_year' => 2014),
        'X5Pro V'       => array('platform_model' => 'X5 Pro V',    'platform_year' => 2014),
        'X6A'           => array('platform_model' => 'X6A',         'platform_year' => 2015),
        'X6D'           => array('platform_model' => 'X6D',         'platform_year' => 2015),
        'X6L'           => array('platform_model' => 'X6L',         'platform_year' => 2015),
        'X6 plus'       => array('platform_model' => 'X6 plus',     'platform_year' => 2015),
        'Xplay5A'       => array('platform_model' => 'Xplay 5A',    'platform_year' => 2016),
        'Xplay5S'       => array('platform_model' => 'Xplay 5S',    'platform_year' => 2016),
        'X6S A'         => array('platform_model' => 'X6S A',       'platform_year' => 2016),
        'X6Plus D'      => array('platform_model' => 'X6 Plus D',   'platform_year' => 2016),
        'X6SPlus A'     => array('platform_model' => 'X6S Plus A',  'platform_year' => 2016),
        'X6SPlus D'     => array('platform_model' => 'X6S Plus D',  'platform_year' => 2016),
        'X7'            => array('platform_model' => 'X7',          'platform_year' => 2016),
        'X7 Plus'       => array('platform_model' => 'X7 Plus',     'platform_year' => 2016),
        'X9'            => array('platform_model' => 'X9',          'platform_year' => 2016),
        'X9 Plus'       => array('platform_model' => 'X9 Plus',     'platform_year' => 2016),
        'X9S'           => array('platform_model' => 'X9S',         'platform_year' => 2017),
        'X9s Plus'      => array('platform_model' => 'X9S Plus',    'platform_year' => 2017),
        'X20'           => array('platform_model' => 'X20',         'platform_year' => 2017),
        'X20A'          => array('platform_model' => 'X20A',        'platform_year' => 2017),
        'X20Plus A'     => array('platform_model' => 'X20 Plus A',  'platform_year' => 2017),
        'Xplay6'        => array('platform_model' => 'Xplay 6',     'platform_year' => 2018),

        'V1928A'        => array('platform_model' => 'V1928A',      'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Vivo',
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
