<?php
/**
 * @brief Danew client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2019
 * @date Modification: Jan 2021
 * @copyright 2019 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Danew client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_DanewClientDevice($deviceCode='') {
    $deviceList = array(
        /* Danew tablets */
        'Dslide1013QC_v2'   => array('platform_model' => 'Dslide 1013QC v2',    'platform_year' => 2016, 'platform_type' => 'tablet', 'platform_format' => 'tablet'),

        /* Danew mobiles */
        'Konnect_601'       => array('platform_model' => 'Konnect 601',         'platform_year' => 2017),
        'Konnect_607'       => array('platform_model' => 'Konnect 607',         'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Danew',
        'platform_country'  => 'fr',
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
