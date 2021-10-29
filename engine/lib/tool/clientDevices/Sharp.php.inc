<?php
/**
 * @brief Sharp client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.8
 * @date Creation: May 2018
 * @date Modification: Sep 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Sharp client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_SharpClientDevice($deviceCode='') {
    $deviceList = array(
        'SH-02H'    => array('platform_model' => 'Aquos Compact',   'platform_year' => 2015),
        'FS8001'    => array('platform_model' => 'Aquos M1',        'platform_year' => 2016),
        'FS8002'    => array('platform_model' => 'Z2',              'platform_year' => 2016),
        'SHV37'     => array('platform_model' => 'Aquos U',         'platform_year' => 2017),
        'SHV39'     => array('platform_model' => 'Aquos R',         'platform_year' => 2017),
        'SHV40'     => array('platform_model' => 'Aquos Sense',     'platform_year' => 2017),
        'FS8032'    => array('platform_model' => 'Aquos S3',        'platform_year' => 2018),
        'SH-D01'    => array('platform_model' => 'Aquos D10',       'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Sharp',
        'platform_country'  => 'jp',
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
