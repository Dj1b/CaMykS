<?php
/**
 * @brief Quanta client devices specific methods
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
 * Return Quanta client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_QuantaClientDevice($deviceCode='') {
    $deviceList = array(
        'Le Pan TC802A' => array('platform_model' => 'Le Pan Mini', 'platform_year' => '2013', 'platform_type' => 'tablet', 'platform_format' => 'tablet',),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Quanta',
        'platform_country'  => 'tw',
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
