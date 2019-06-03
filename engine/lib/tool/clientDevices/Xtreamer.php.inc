<?php
/**
 * @brief Xtreamer client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Xtreamer.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: May 2019
 * @date Modification: May 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Xtreamer client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_XtreamerClientDevice($deviceCode='') {
    $deviceList = array(
        /* Xtreamer tablets */
        'X7-Q4'     => array('platform_model' => 'X7-Q4',   'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2012),
        'X9-8DB1'   => array('platform_model' => 'X9-8DB1', 'platform_type' => 'tablet', 'platform_format' => 'tablet', 'platform_year' => 2012),

        /* Xtreamer mobiles */
        'Aiki-4'    => array('platform_model' => 'Aiki 4',  'platform_year' => 2012),
        'Aiki-4S'   => array('platform_model' => 'Aiki 4S', 'platform_year' => 2012),
        'Aiki-5'    => array('platform_model' => 'Aiki 5',  'platform_year' => 2012),
        'Aiki-5S'   => array('platform_model' => 'Aiki 5S', 'platform_year' => 2012),
        'Bang'      => array('platform_model' => 'Ban G',   'platform_year' => 2013),
        'Joyz'      => array('platform_model' => 'Joyz',    'platform_year' => 2013),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Xtreamer',
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
