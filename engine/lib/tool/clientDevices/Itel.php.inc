<?php
/**
 * @brief Itel client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Itel.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Jan 2019
 * @date Modification: Mar 2020
 * @copyright 2019 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Itel client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_ItelClientDevice($deviceCode='') {
    $deviceList = array(
        'it1407'        => array('platform_model' => 'IT1407',      'platform_year' => 2016),
        'it1506'        => array('platform_model' => 'IT1506',      'platform_year' => 2016),
        'it1508'        => array('platform_model' => 'IT1508',      'platform_year' => 2016),
        'it1508 Plus'   => array('platform_model' => 'IT1508 Plus', 'platform_year' => 2016),
        'it1701'        => array('platform_model' => 'IT1701',      'platform_year' => 2017),
        'S11'           => array('platform_model' => 'S11',         'platform_year' => 2017),
        'S32'           => array('platform_model' => 'S32',         'platform_year' => 2017),
        'P32'           => array('platform_model' => 'P32',         'platform_year' => 2018),
        'W5504'         => array('platform_model' => 'P33',         'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Itel',
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
