<?php
/**
 * @brief Meizu client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Meizu.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.11
 * @date Creation: Sep 2018
 * @date Modification: Sep 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Meizu client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MeizuClientDevice($deviceCode='') {
    $deviceList = array(
        'm2 note'       => array('platform_model' => 'M2 Note', 'platform_year' => 2015),
        'PRO 5'         => array('platform_model' => 'Pro 5',   'platform_year' => 2015),
        'MZ-PRO 6'      => array('platform_model' => 'Pro 6',   'platform_year' => 2016),
        'M3s'           => array('platform_model' => 'M3s',     'platform_year' => 2016),
        'MZ-MEIZU_M5'   => array('platform_model' => 'M5',      'platform_year' => 2016),
        'M5'            => array('platform_model' => 'M5',      'platform_year' => 2016),
        'MX6'           => array('platform_model' => 'MX6',     'platform_year' => 2016),
        'MZ-M3X'        => array('platform_model' => 'M3X',     'platform_year' => 2016),
        'U20'           => array('platform_model' => 'U20',     'platform_year' => 2016),
        'M8 lite'       => array('platform_model' => 'M8 Lite', 'platform_year' => 2018),
        '16th'          => array('platform_model' => '16th',    'platform_year' => 2018),
        'Note9'         => array('platform_model' => 'Note 9',  'platform_year' => 2019),
        'C9 pro'        => array('platform_model' => 'C9 Pro',  'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Meizu',
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
