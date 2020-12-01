<?php
/**
 * @brief Ampe client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jun 2018
 * @date Modification: Nov 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Ampe client devices list.
 * @return array
 */
function get_AmpeClientDevices() {
    return array(
        /* Ampe tablets */
        'A10-2cpu'      => array('platform_model' => 'A10 Dual Core',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A10-4core'     => array('platform_model' => 'A10 Quad Core',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A78'           => array('platform_model' => 'A78',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A78-8G'        => array('platform_model' => 'A78 8G',          'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A78 Dual core' => array('platform_model' => 'A78 Dual Core',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A79Q'          => array('platform_model' => 'A79Q',            'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A85'           => array('platform_model' => 'A85',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A96'           => array('platform_model' => 'A96',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2012),
        'A10-QM'        => array('platform_model' => 'A10 QM',          'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2013),
        'A76'           => array('platform_model' => 'A76',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2013),
        'A62'           => array('platform_model' => 'A62',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'A65'           => array('platform_model' => 'A65',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'A70'           => array('platform_model' => 'A70',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'A72'           => array('platform_model' => 'A72',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'A92-II'        => array('platform_model' => 'A92 II',          'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'A77'           => array('platform_model' => 'A77',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'A90-2core'     => array('platform_model' => 'A90 Dual Core',   'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
    );
}

/**
 * Return Ampe client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AmpeClientDevice($deviceCode='') {
    $deviceList = get_AmpeClientDevices();

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Ampe',
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

/**
 * Check if given device is a Ampe know device
 * @return array
 */
function is_AmpeKnownDevice($deviceCode='') {
    $deviceList = get_AmpeClientDevices();
    return (array_key_exists($deviceCode, $deviceList));
}
?>
