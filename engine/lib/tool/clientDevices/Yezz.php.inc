@@ -1,85 +0,0 @@
<?php
/**
 * @brief Yezz client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Yezz.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Mar 2019
 * @date Modification: Dec 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Yezz client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_YezzClientDevice($deviceCode='') {
    $deviceList = array(
        /* Yezz tablets */
        'T7FD'      => array('platform_model' => 'Epic', 'platform_type' => 'tablet',   'platform_format' => 'tablet', 'platform_year' => 2014),

        /* Yezz mobiles */
        'A4'        => array('platform_model' => 'Andy A4',         'platform_year' => 2013),
        'A5'        => array('platform_model' => 'Andy A5',         'platform_year' => 2013),
        'A6M'       => array('platform_model' => 'Andy A6M',        'platform_year' => 2013),
        'AC4.5'     => array('platform_model' => 'Andy AC4.5',      'platform_year' => 2013),
        'C4E'       => array('platform_model' => 'Andy C4E',        'platform_year' => 2013),
        'A4M'       => array('platform_model' => 'Andy AM',         'platform_year' => 2014),
        'A4.5'      => array('platform_model' => 'Andy A4.5',       'platform_year' => 2014),
        'A5EI'      => array('platform_model' => 'Andy A5EI',       'platform_year' => 2014),
        'A5QP'      => array('platform_model' => 'Andy A5QP',       'platform_year' => 2014),
        'AC4EI'     => array('platform_model' => 'Andy AC4EI',      'platform_year' => 2014),
        'AC5EI'     => array('platform_model' => 'Andy AC5EI',      'platform_year' => 2014),
        'C3.5EI'    => array('platform_model' => 'Andy C3.5EI',     'platform_year' => 2014),
        'C5EI'      => array('platform_model' => 'Andy C5EI',       'platform_year' => 2014),
        'C5QL'      => array('platform_model' => 'Andy C5QL',       'platform_year' => 2014),
        'C5V'       => array('platform_model' => 'Andy C5V',        'platform_year' => 2014),
        'C5VP'      => array('platform_model' => 'Andy C5VP',       'platform_year' => 2014),
        '3.5EH'     => array('platform_model' => 'Andy 3.5EH',      'platform_year' => 2014),
        '3.5EI'     => array('platform_model' => 'Andy 3.5EI',      'platform_year' => 2014),
        '4E'        => array('platform_model' => 'Andy 4E',         'platform_year' => 2014),
        '4EI'       => array('platform_model' => 'Andy 4EI',        'platform_year' => 2014),
        '4.5M'      => array('platform_model' => 'Andy 4.5M',       'platform_year' => 2014),
        '5EI'       => array('platform_model' => 'Andy 5EI',        'platform_year' => 2014),
        '55EI'      => array('platform_model' => 'Andy 5.5EI',      'platform_year' => 2014),
        '5T'        => array('platform_model' => 'Andy 5T',         'platform_year' => 2014),
        '5TL'       => array('platform_model' => 'Andy 5TL',        'platform_year' => 2014),
        '6Q'        => array('platform_model' => 'Andy 6Q',         'platform_year' => 2014),
        'A5EL'      => array('platform_model' => 'Andy A5EL',       'platform_year' => 2015),
        '35E2I'     => array('platform_model' => 'Andy 3.5E2I',     'platform_year' => 2015),
        '3.5EI3'    => array('platform_model' => 'Andy 3.5EI3',     'platform_year' => 2015),
        '4E2I'      => array('platform_model' => 'Andy 4E2I',       'platform_year' => 2015),
        '4EL2 LTE'  => array('platform_model' => 'Andy 4EL2 LTE',   'platform_year' => 2015),
        '45EL'      => array('platform_model' => 'Andy 4.5EL',      'platform_year' => 2015),
        '5EI3'      => array('platform_model' => 'Andy 5EI3',       'platform_year' => 2015),
        '5EL'       => array('platform_model' => 'Andy 5EL',        'platform_year' => 2015),
        '5EL2 LTE'  => array('platform_model' => 'Andy 5EL2 LTE',   'platform_year' => 2015),
        '4E4'       => array('platform_model' => 'Andy 4E4',        'platform_year' => 2016),
        '5E3'       => array('platform_model' => 'Andy 5E3',        'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Yezz',
        'platform_country'  => 'us',
        'platform_model'    => 'Andy '.$deviceCode,
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
