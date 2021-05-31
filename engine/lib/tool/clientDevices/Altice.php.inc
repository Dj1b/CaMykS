<?php
/**
 * @brief Altice client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Jul 2019
 * @date Modification: May 2021
 * @copyright 2019 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Altice client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AlticeClientDevice($deviceCode='') {
    $deviceList = array(
        'starxtrem6'    => array('platform_model' => 'StarXtrem 6',     'platform_year' => 2015),
        'startrail7'    => array('platform_model' => 'StarTrail 7',     'platform_year' => 2015),
        'sx41'          => array('platform_model' => 'SX41',            'platform_year' => 2017),
        'staraddict6'   => array('platform_model' => 'StarAddict 6',    'platform_year' => 2017),
        'starnaute4'    => array('platform_model' => 'StarNaute 4',     'platform_year' => 2017),
        's43'           => array('platform_model' => 'S43',             'platform_year' => 2020),

    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Altice',
        'platform_country'  => 'nl',
        'platform_model'    => $deviceCode,
        'platform_type'     => 'handheld',
        'platform_format'   => 'handheld',
    );

    /* Check if device is a known device. */
    if (!array_key_exists(strtolower($deviceCode), $deviceList))
        return $result;

    /* Return result. */
    return array_merge($result, $deviceList[strtolower($deviceCode)]);
}
?>
