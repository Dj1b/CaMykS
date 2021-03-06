<?php
/**
 * @brief Micromax client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Micromax.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Apr 2018
 * @date Modification: Aug 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Micromax client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MicromaxClientDevice($deviceCode='') {
    $deviceList = array(
        'A62'   => array('platform_model' => 'Bolt A62',            'platform_year' => 2013),
        'A96'   => array('platform_model' => 'Canvas Power A96',    'platform_year' => 2014),
        'Q335'  => array('platform_model' => 'Bolt Q335',           'platform_year' => 2015),
        'Q350'  => array('platform_model' => 'Canvas Spark Q350',   'platform_year' => 2016),
        'Q380'  => array('platform_model' => 'Canvas Spark Q380',   'platform_year' => 2015),
        'Q440'  => array('platform_model' => 'Bharat 4',            'platform_year' => 2017),
        'C1'    => array('platform_model' => 'Canvas 1',            'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Micromax',
        'platform_country'  => 'in',
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
