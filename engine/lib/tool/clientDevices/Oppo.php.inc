<?php
/**
 * @brief Oppo client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.32
 * @date Creation: Nov 2018
 * @date Modification: Oct 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Oppo client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_OppoClientDevice($deviceCode='') {
    $deviceList = array(
        '1201'      => array('platform_model' => 'Neo 5',           'platform_year' => 2015),
        'A33'       => array('platform_model' => 'A33',             'platform_year' => 2015),
        'A1601'     => array('platform_model' => 'F1s',             'platform_year' => 2016),
        'F1f'       => array('platform_model' => 'F1',              'platform_year' => 2016),
        'R9s'       => array('platform_model' => 'R9S',             'platform_year' => 2016),
        'CPH1607'   => array('platform_model' => 'R9s',             'platform_year' => 2016),
        'A37f'      => array('platform_model' => 'A37f',            'platform_year' => 2016),
        'A37fw'     => array('platform_model' => 'A37fw',           'platform_year' => 2017),
        'CPH1609'   => array('platform_model' => 'F3',              'platform_year' => 2017),
        'CPH1613'   => array('platform_model' => 'F3 Plus',         'platform_year' => 2017),
        'CPH1727'   => array('platform_model' => 'F5',              'platform_year' => 2017),
        'CPH1729'   => array('platform_model' => 'A83',             'platform_year' => 2017),
        'CPH1837'   => array('platform_model' => 'A3',              'platform_year' => 2018),
        'CPH1801'   => array('platform_model' => 'A71',             'platform_year' => 2018),
        'CPH1803'   => array('platform_model' => 'A3s',             'platform_year' => 2018),
        'CPH1819'   => array('platform_model' => 'F7',              'platform_year' => 2018),
        'CPH1823'   => array('platform_model' => 'F9',              'platform_year' => 2018),
        'CPH1861'   => array('platform_model' => 'Realme 1',        'platform_year' => 2018),
        'CPH1877'   => array('platform_model' => 'R17',             'platform_year' => 2018),
        'CPH1893'   => array('platform_model' => 'R17 Neo',         'platform_year' => 2018),
        'PADM00'    => array('platform_model' => 'A3',              'platform_year' => 2018),
        'PAFM00'    => array('platform_model' => 'Find X',          'platform_year' => 2018),
        'CPH1901'   => array('platform_model' => 'A7',              'platform_year' => 2019),
        'CPH1907'   => array('platform_model' => 'Reno 2',          'platform_year' => 2019),
        'CPH1909'   => array('platform_model' => 'A5s',             'platform_year' => 2019),
        'CPH1911'   => array('platform_model' => 'F11',             'platform_year' => 2019),
        'CPH1912'   => array('platform_model' => 'A5s',             'platform_year' => 2019),
        'CPH1917'   => array('platform_model' => 'Reno',            'platform_year' => 2019),
        'CPH1931'   => array('platform_model' => 'A5',              'platform_year' => 2019),
        'CPH1937'   => array('platform_model' => 'A9',              'platform_year' => 2019),
        'CPH1941'   => array('platform_model' => 'A9',              'platform_year' => 2019),
        'CPH1951'   => array('platform_model' => 'Reno 2 Z',        'platform_year' => 2019),
        'CPH1969'   => array('platform_model' => 'F11 Pro',         'platform_year' => 2019),
        'CPH1979'   => array('platform_model' => 'Reno Z',          'platform_year' => 2019),
        'CPH2009'   => array('platform_model' => 'Find X2 Pro',     'platform_year' => 2020),
        'CPH2021'   => array('platform_model' => 'A91',             'platform_year' => 2020),
        'CPH2025'   => array('platform_model' => 'X2 Pro',          'platform_year' => 2020),
        'CPH2067'   => array('platform_model' => 'A72',             'platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Oppo',
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
