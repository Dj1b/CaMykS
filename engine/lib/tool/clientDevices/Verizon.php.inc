<?php
/**
 * @brief Verizon client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2021
 * @date Modification: Apr 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Verizon client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_VerizonClientDevice($deviceCode='') {
    $deviceList = array(
        'QMV7A' => array('platform_model' => 'Ellipsis 7', 'platform_year' => '2013', 'platform_type' => 'tablet', 'platform_format' => 'tablet',),
        'QMV7B' => array('platform_model' => 'Ellipsis 7', 'platform_year' => '2013', 'platform_type' => 'tablet', 'platform_format' => 'tablet',),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Verizon',
        'platform_country'  => 'us',
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
