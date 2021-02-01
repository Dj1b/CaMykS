<?php
/**
 * @brief Chuwi client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2019
 * @date Modification: Jan 2021
 * @copyright 2019 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Chuwi client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_ChuwiClientDevice($deviceCode='') {
    $deviceList = array(
        /* Chuwi tablets */
        'Hi10 pro'  => array('platform_model' => 'Hi10 Pro',    'platform_year' => 2016, 'platform_type' => 'tablet', 'platform_format' => 'tablet'),
        'Hi9Air'    => array('platform_model' => 'Hi9 Air',     'platform_year' => 2019, 'platform_type' => 'tablet', 'platform_format' => 'tablet'),

    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Chuwi',
        'platform_country'  => 'cn',
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
