<?php
/**
 * @brief Crosscall client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Crosscall.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: May 2018
 * @date Modification: Jun 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Crosscall client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_CrosscallClientDevice($deviceCode='') {
    $deviceList = array(
        'action-x3'         => array('platform_model' => 'Action-X3',       'platform_year' => 2017),
        'action-x3 pro'     => array('platform_model' => 'Action-X3 Pro',   'platform_year' => 2017),
        'trekker-m1 core'   => array('platform_model' => 'Trekker-M1 Core', 'platform_year' => 2017),
        'trekker-m1'        => array('platform_model' => 'Trekker-M1',      'platform_year' => 2016),
        'trekker-s1'        => array('platform_model' => 'Trekker-S1',      'platform_year' => 2016),
        'trekker-x2'        => array('platform_model' => 'Trekker-X2',      'platform_year' => 2015),
        'trekker-x3'        => array('platform_model' => 'Trekker-X3',      'platform_year' => 2017),
        'trekker-x4'        => array('platform_model' => 'Trekker-X4',      'platform_year' => 2018),
        'trekker-x1'        => array('platform_model' => 'Trekker-X1',      'platform_year' => 2015),
        'odyssey-plus'      => array('platform_model' => 'Odyssey Plus',    'platform_year' => 2014),
        'odyssey-s1'        => array('platform_model' => 'Odyssey S1',      'platform_year' => 2016),
        'core-x3'           => array('platform_model' => 'Core-X3',         'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Crosscall',
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
