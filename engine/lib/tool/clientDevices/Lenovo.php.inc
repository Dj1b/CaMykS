<?php
/**
 * @brief Lenovo client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Lenovo.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Lenovo client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LenovoClientDevice($deviceCode='') {
    $deviceList = array(
        /* Lenovo tablets */
        'B8000-F'   => array('platform_model' => 'Yoga',                'platform_type' => 'tablet', 'platform_format'  => 'tablet'),
        'A2107A-H'  => array('platform_model' => 'IdeaTab A2107A-H',    'platform_type' => 'tablet', 'platform_format'  => 'tablet'),
        
        /* Lenovo phones */
        'P70-A'     => array('platform_model' => 'P70'),
        'A2010-a'   => array('platform_model' => 'A2010', ),
        'K53a48'    => array('platform_model' => 'K6 Note', ),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Lenovo',
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