<?php
/**
 * @brief FNF client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/FNF.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2019
 * @date Modification: Jun 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return FNF client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_FNFClientDevice($deviceCode='') {
    $device = strtolower($deviceCode);
    $deviceList = array(
        'ifive x'           => array('platform_model' => 'iFive X',         'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2013),
        'ifive x2'          => array('platform_model' => 'iFive X2',        'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2013),
        'ifive2s'           => array('platform_model' => 'iFive 2S',        'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2013),
        'ifive3'            => array('platform_model' => 'iFive 3',         'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2013),
        'ifive100'          => array('platform_model' => 'iFive 100',       'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2014),
        'ifive air'         => array('platform_model' => 'iFive Air',       'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
        'ifive mini3'       => array('platform_model' => 'iFive Mini 3',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
        'ifive mini 3gs'    => array('platform_model' => 'iFive Mini 3GS',  'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
        'ifive mini4'       => array('platform_model' => 'iFive Mini 4',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
        'ifive mini 4s'     => array('platform_model' => 'iFive Mini 4S',   'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'FNF',
        'platform_country'  => 'cn',
        'platform_model'    => $deviceCode,
        'platform_type'     => 'handheld',
        'platform_format'   => 'handheld',
    );

    /* Check if device is a known device. */
    if (!array_key_exists($device, $deviceList))
        return $result;

    /* Return result. */
    return array_merge($result, $deviceList[$device]);
}
?>
