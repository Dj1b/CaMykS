<?php
/**
 * @brief Realme (Oppo subsidiary) client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.11
 * @date Creation: Apr 2020
 * @date Modification: Sep 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Realme client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_RealmeClientDevice($deviceCode='') {
    $deviceList = array(
        /* Realme mobiles */
        'RMX1811'   => array('platform_model' => 'C1',              'platform_year' => 2018),
        'RMX1825'   => array('platform_model' => '3',               'platform_year' => 2019),
        'RMX1851'   => array('platform_model' => '3 Pro',           'platform_year' => 2019),
        'RMX1901'   => array('platform_model' => 'X',               'platform_year' => 2019),
        'RMX1911'   => array('platform_model' => '5',               'platform_year' => 2019),
        'RMX1921'   => array('platform_model' => 'XT',              'platform_year' => 2019),
        'RMX1931'   => array('platform_model' => 'X2 Pro',          'platform_year' => 2019),
        'RMX1971'   => array('platform_model' => '5 Pro',           'platform_year' => 2019),
        'RMX1991'   => array('platform_model' => 'X2',              'platform_year' => 2019),
        'RMX1992'   => array('platform_model' => 'X2',              'platform_year' => 2019),
        'RMX1993'   => array('platform_model' => 'X2',              'platform_year' => 2019),
        'RMX2001'   => array('platform_model' => '6',               'platform_year' => 2020),
        'RMX2002'   => array('platform_model' => '6i',              'platform_year' => 2020),
        'RMX2027'   => array('platform_model' => 'C3',              'platform_year' => 2020),
        'RMX2030'   => array('platform_model' => '5i',              'platform_year' => 2020),
        'RMX2061'   => array('platform_model' => '6 Pro',           'platform_year' => 2020),
        'RMX2075'   => array('platform_model' => 'X50 Pro',         'platform_year' => 2020),
        'RMX2086'   => array('platform_model' => 'X3 SuperZoom',    'platform_year' => 2020),
        'RMX2144'   => array('platform_model' => 'X50',             'platform_year' => 2020),
        'RMX2155'   => array('platform_model' => '7',               'platform_year' => 2021),
        'RMX2170'   => array('platform_model' => '7 Pro',           'platform_year' => 2021),
        'RMX2185'   => array('platform_model' => 'C11',             'platform_year' => 2020),
        'RMX2189'   => array('platform_model' => 'C12',             'platform_year' => 2021),
        'RMX2202'   => array('platform_model' => 'GT 5G',           'platform_year' => 2021),
        'RMX3085'   => array('platform_model' => '8',               'platform_year' => 2021),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Realme',
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
