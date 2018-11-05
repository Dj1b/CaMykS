<?php
/**
 * @brief Amazon client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Amazon.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Oct 2018
 * @date Modification: Oct 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Amazon client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AmazonClientDevice($deviceCode='') {
    $deviceList = array(
        'KFTHWI'    => array('platform_model'    => 'Kindle Fire HDX 7',        'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2013,),
        'KFFOWI'    => array('platform_model'    => 'Kindle Fire (5th Gen)',    'platform_type' => 'tablet',    'platform_format'   => 'tablet',    'platform_year' => 2015,),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Amazon',
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
