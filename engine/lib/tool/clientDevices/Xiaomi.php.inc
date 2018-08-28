<?php
/**
 * @brief Xiaomi client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Xiaomi.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: May 2018
 * @date Modification: Aug 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Xiaomi client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_XiaomiClientDevice($deviceCode='') {
    $deviceList = array(
        /* tablets */
        'mi pad'        => array('platform_model' => 'MI PAD',          'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2014),

        /* phones */
        'mi 2'          => array('platform_model' => 'Mi 2',            'platform_year' => 2012),
        'mi 5'          => array('platform_model' => 'Mi 5',            'platform_year' => 2016),
        'mi a1'         => array('platform_model' => 'Mi A1',           'platform_year' => 2017),
        'mi note pro'   => array('platform_model' => 'Mi Note Pro',     'platform_year' => 2015),
        'redmi 4x'      => array('platform_model' => 'Redmi 4X',        'platform_year' => 2017),
        'redmi 3s'      => array('platform_model' => 'Redmi 3S',        'platform_year' => 2016),
        'redmi note 3'  => array('platform_model' => 'Redmi Note 3',    'platform_year' => 2015),
        'redmi note 4'  => array('platform_model' => 'Redmi Note 4',    'platform_year' => 2016),
        'redmi note 4x' => array('platform_model' => 'Redmi Note 4X',   'platform_year' => 2017),
        'redmi 5a'      => array('platform_model' => 'Redmi 5A',        'platform_year' => 2017),
        'redmi 5 plus'  => array('platform_model' => 'Redmi 5 Plus',    'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
        return $deviceList;
    else
        $deviceCode = strtolower($deviceCode);

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Xiaomi',
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
