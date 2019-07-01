<?php
/**
 * @brief Lyf client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Lyf.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Apr 2018
 * @date Modification: Jun 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Lyf client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LyfClientDevice($deviceCode='') {
    $deviceList = array(
        'LYF/F61F'  => array('platform_model' => 'JioPhone F61F',   'platform_year' => 2017),
        'LYF/F90M'  => array('platform_model' => 'JioPhone F90M',   'platform_year' => 2017),
        'LYF/F120B' => array('platform_model' => 'JioPhone F120B',  'platform_year' => 2017),
        'LYF/F220B' => array('platform_model' => 'JioPhone F220B',  'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Lyf',
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
