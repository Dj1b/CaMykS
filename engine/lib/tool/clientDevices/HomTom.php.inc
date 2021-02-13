<?php
/**
 * @brief HomTom client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Oct 2018
 * @date Modification: Feb 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return HomTom client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_HomTomClientDevice($deviceCode='') {
    $deviceList = array(
        'HT5'       => array('platform_model' => 'HT5',         'platform_year' => 2015),
        'HT7'       => array('platform_model' => 'HT7',         'platform_year' => 2015),
        'HT7Pro'    => array('platform_model' => 'HT7Pro',      'platform_year' => 2016),
        'HT3'       => array('platform_model' => 'HT3',         'platform_year' => 2016),
        'HT3Pro'    => array('platform_model' => 'HT3 Pro',     'platform_year' => 2016),
        'HT16'      => array('platform_model' => 'HT16',        'platform_year' => 2016),
        'HT16Pro'   => array('platform_model' => 'HT16 Pro',    'platform_year' => 2016),
        'HT17'      => array('platform_model' => 'HT17',        'platform_year' => 2016),
        'HT17Pro'   => array('platform_model' => 'HT17 Pro',    'platform_year' => 2016),
        'HT20'      => array('platform_model' => 'HT20',        'platform_year' => 2016),
        'HT20Pro'   => array('platform_model' => 'HT20 Pro',    'platform_year' => 2016),
        'HT10'      => array('platform_model' => 'HT10',        'platform_year' => 2017),
        'HT26'      => array('platform_model' => 'HT26',        'platform_year' => 2017),
        'HT27'      => array('platform_model' => 'HT27',        'platform_year' => 2017),
        'HT30'      => array('platform_model' => 'HT30',        'platform_year' => 2017),
        'HT30Pro'   => array('platform_model' => 'HT30 Pro',    'platform_year' => 2017),
        'HT37'      => array('platform_model' => 'HT37',        'platform_year' => 2017),
        'HT37Pro'   => array('platform_model' => 'HT37 Pro',    'platform_year' => 2017),
        'HT50'      => array('platform_model' => 'HT50',        'platform_year' => 2017),
        'HT70'      => array('platform_model' => 'HT70',        'platform_year' => 2018),

        'Z11'       => array('platform_model' => 'Zoji Z11',    'platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'HomTom',
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
