<?php
/**
 * @brief Umi client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Umi.php.inc
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
 * Return Umi client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_UmiClientDevice($deviceCode='') {
    $deviceCode = strtolower($deviceCode);
    $deviceList = array(
        'diamond'   => array('platform_model' => 'Diamond',     'platform_year' => 2016),
        'diamond x' => array('platform_model' => 'Diamond X',   'platform_year' => 2016),
        'london'    => array('platform_model' => 'London',      'platform_year' => 2016),
        'max'       => array('platform_model' => 'Max',         'platform_year' => 2016),
        'touch'     => array('platform_model' => 'Touch',       'platform_year' => 2016),
        'touch 4g'  => array('platform_model' => 'Touch 4G',    'platform_year' => 2016),
        'touch x'   => array('platform_model' => 'Touch X',     'platform_year' => 2016),
        'super'     => array('platform_model' => 'Super',       'platform_year' => 2016),
        'emax'      => array('platform_model' => 'eMAX',        'platform_year' => 2015),
        'emax mini' => array('platform_model' => 'eMAX Mini',   'platform_year' => 2015),
        'hammer'    => array('platform_model' => 'Hammer',      'platform_year' => 2015),
        'hammer s'  => array('platform_model' => 'Hammer S',    'platform_year' => 2015),
        'rome'      => array('platform_model' => 'Rome',        'platform_year' => 2015),
        'rome x'    => array('platform_model' => 'Rome X',      'platform_year' => 2015),
        'iron'      => array('platform_model' => 'Iron',        'platform_year' => 2015),
        'iron pro'  => array('platform_model' => 'Iron Pro',    'platform_year' => 2015),
        'c1'        => array('platform_model' => 'C1',          'platform_year' => 2014),
        'x3'        => array('platform_model' => 'X3',          'platform_year' => 2014),
        'x1 pro'    => array('platform_model' => 'X1 Pro',      'platform_year' => 2014),
        'x2'        => array('platform_model' => 'X2',          'platform_year' => 2013),
        'X1S'       => array('platform_model' => 'X1S',         'platform_year' => 2013),
        'x1'        => array('platform_model' => 'X1',          'platform_year' => 2013),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Umi',
        'platform_model'    => ucwords($deviceCode),
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
