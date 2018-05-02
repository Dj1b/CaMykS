<?php
/**
 * @brief Sony client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Sony.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2018
 * @date Modification: May 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Sony client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_SonyClientDevice($deviceCode='') {
    $deviceList = array(
        'C1505' => array('platform_model' => 'Xperia E'),
        'C2105' => array('platform_model' => 'Xperia L'),
        'C5303' => array('platform_model' => 'Xperia SP'),
        'C6603' => array('platform_model' => 'Xperia Z'),
        'D6503' => array('platform_model' => 'Xperia Z2'),
        'D2005' => array('platform_model' => 'Xperia E1'),
        'D2203' => array('platform_model' => 'Xperia E3 (2014)'),
        'D2303' => array('platform_model' => 'Xperia M2'),
        'D2305' => array('platform_model' => 'Xperia M2'),
        'D2306' => array('platform_model' => 'Xperia M2'),
        'D5303' => array('platform_model' => 'Xperia T2 Ultra'),
        'D5503' => array('platform_model' => 'Xperia Z1 Compact'),
        'D5803' => array('platform_model' => 'Xperia Z3 Compact'),
        'D6603' => array('platform_model' => 'Xperia Z3'),
        'D6683' => array('platform_model' => 'Xperia Z3 Dual Sim'),
        'E5303' => array('platform_model' => 'Xperia C4',           'platform_year' => 2015),
        'E5823' => array('platform_model' => 'Xperia Z5 Compact'),
        'E6653' => array('platform_model' => 'Xperia Z5'),
        'F3111' => array('platform_model' => 'Xperia XA'),
        'F5121' => array('platform_model' => 'Xperia X'),
        'F8331' => array('platform_model' => 'Xperia XZ'),
        'G8141' => array('platform_model' => 'Xperia XZ Premium'),
        'H3311' => array('platform_model' => 'Xperia L2'),
        
        'SOV31' => array('platform_model' => 'Xperia Z4'),
        'SOV32' => array('platform_model' => 'Xperia Z5'),
        'SOV33' => array('platform_model' => 'Xperia X Performance'),
        'SOV34' => array('platform_model' => 'Xperia XZ'),
        'SOV35' => array('platform_model' => 'Xperia XZs'),
        'SOV36' => array('platform_model' => 'Xperia XZ1'),
        'SOV37' => array('platform_model' => 'Xperia XZ2'),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Sony',
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