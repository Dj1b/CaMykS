<?php
/**
 * @brief Smartisan client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Smartisan.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2019
 * @date Modification: Apr 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Smartisan client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_SmartisanClientDevice($deviceCode='') {
    $deviceList = array(
        'OC105' => array('platform_model' => 'Nut 3',       'platform_year' => 2018),
        'OS105' => array('platform_model' => 'Nut Pro 2',   'platform_year' => 2017),
        'OD105' => array('platform_model' => 'Nut Pro',     'platform_year' => 2017),
        'OD103' => array('platform_model' => 'Nut Pro',     'platform_year' => 2017),
        'SM801' => array('platform_model' => 'T2',          'platform_year' => 2016),
        'SM901' => array('platform_model' => 'M1',          'platform_year' => 2016),
        'SM919' => array('platform_model' => 'M1L',         'platform_year' => 2016),
        'YQ603' => array('platform_model' => 'U1',          'platform_year' => 2015),
        'YQ601' => array('platform_model' => 'U1',          'platform_year' => 2015),
        'SM701' => array('platform_model' => 'T1',          'platform_year' => 2014),
        'SM705' => array('platform_model' => 'T1',          'platform_year' => 2014),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Smartisan',
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
