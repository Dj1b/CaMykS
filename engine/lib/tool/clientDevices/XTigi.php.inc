<?php
/**
 * @brief X-Tigi client devices specific methods.
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2020
 * @date Modification: Sep 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return X-Tigi client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_XTigiClientDevice($deviceCode='') {
    $deviceList = array(
        /* X-Tigi tablets */
        'JOY7_TV'       => array('platform_model' => 'Joy7 TV',     'platform_year' => 2018, 'platform_type' => 'tablet', 'platform_format' => 'tablet',),
        'JOY10 Mate'    => array('platform_model' => 'Joy 10 Mate', 'platform_year' => 2019, 'platform_type' => 'tablet', 'platform_format' => 'tablet',),

        /* X-Tigi mobiles */
        'V18'           => array('platform_model' => 'V18',         'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'X-Tigi',
        'platform_country'  => 'hk',
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
