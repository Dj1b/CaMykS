<?php
/**
 * @brief Nokia client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Nokia.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Jun 2018
 * @date Modification: Jan 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Nokia client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_NokiaClientDevice($deviceCode='') {
    $deviceList = array(
        'Lumia 920' => array('platform_model' => 'Lumia 920',       'platform_year' => 2012),
        'Lumia 535' => array('platform_model' => 'Lumia 535',       'platform_year' => 2014),
        'Lumia 830' => array('platform_model' => 'Lumia 830',       'platform_year' => 2014),

        'TA-1053'   => array('platform_model' => '5',               'platform_year' => 2017),
        'TA-1021'   => array('platform_model' => '6',               'platform_year' => 2017),

        'X2DS'      => array('platform_model' => 'X2 (Dual Sim)',   'platform_year' => 2014),
        '7 plus'    => array('platform_model' => '7 Plus',          'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Nokia',
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
