<?php
/**
 * @brief Vestel client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Mar 2019
 * @date Modification: Jan 2021
 * @copyright 2019 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Vestel client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_VestelClientDevice($deviceCode='') {
    $deviceList = array(
        'Venus_V3_5570' => array('platform_model' => 'Venus V3 5570',   'platform_year' => 2015),
        'Venus Z40'     => array('platform_model' => 'Venus Z40',       'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Vestel',
        'platform_country'  => 'tr',
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
