<?php
/**
 * @brief Memup client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Memup.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2019
 * @date Modification: May 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Memup client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_MemupClientDevice($deviceCode='') {
    $deviceList = array(
        '704C'          => array('platform_model' => 'SlidePad 704C',       'platform_year' => 2012),
        '704CE'         => array('platform_model' => 'SlidePad 704CE',      'platform_year' => 2012),
        '708C'          => array('platform_model' => 'SlidePad 708C',       'platform_year' => 2012),
        'NG708'         => array('platform_model' => 'SlidePad NG 708',     'platform_year' => 2012),
        'NG808'         => array('platform_model' => 'SlidePad NG 808',     'platform_year' => 2012),
        'NG9708'        => array('platform_model' => 'SlidePad NG 9708',    'platform_year' => 2012),
        'NG9716'        => array('platform_model' => 'SlidePad NG 9716',    'platform_year' => 2012),
        'NG9716DC'      => array('platform_model' => 'SlidePad NG 9716DC',  'platform_year' => 2012),
        'Elite 9708'    => array('platform_model' => 'SlidePad Elite 9708', 'platform_year' => 2013),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Memup',
        'platform_model'    => $deviceCode,
        'platform_type'     => 'tablet',
        'platform_format'   => 'tablet',
    );

    /* Check if device is a known device. */
    if (!array_key_exists($deviceCode, $deviceList))
        return $result;

    /* Return result. */
    return array_merge($result, $deviceList[$deviceCode]);
}
?>
