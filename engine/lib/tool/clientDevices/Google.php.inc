<?php
/**
 * @brief Google client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.15
 * @date Creation: Aug 2018
 * @date Modification: Nov 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Google client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_GoogleClientDevice($deviceCode='') {
    $deviceList = array(
        /* Google tablets */
        'Nexus 10'      => array('platform_year' => 2012, 'platform_type' => 'tablet', 'platform_format' => 'tablet',),
        'Nexus 7'       => array('platform_year' => 2013, 'platform_type' => 'tablet', 'platform_format' => 'tablet',),

        /* Google mobiles */
        'Nexus'         => array('platform_year' => 2010),
        'Nexus One'     => array('platform_year' => 2010),
        'Nexus S'       => array('platform_year' => 2010),
        'Nexus 4'       => array('platform_year' => 2012),
        'Nexus 5'       => array('platform_year' => 2013),
        'Nexus 5X'      => array('platform_year' => 2015),
        'Nexus 6P'      => array('platform_year' => 2015),
        'Pixel'         => array('platform_year' => 2016),
        'Pixel XL'      => array('platform_year' => 2016),
        'Pixel 2'       => array('platform_year' => 2017),
        'Pixel 2 XL'    => array('platform_year' => 2017),
        'Pixel 3'       => array('platform_year' => 2018),
        'Pixel 3 XL'    => array('platform_year' => 2018),
        'Pixel 3a'      => array('platform_year' => 2018),
        'Pixel 3a XL'   => array('platform_year' => 2018),
        'Pixel 4'       => array('platform_year' => 2019),
        'Pixel 4 XL'    => array('platform_year' => 2019),
        'Pixel 4a'      => array('platform_year' => 2020),
        'Pixel 5'       => array('platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Google',
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
