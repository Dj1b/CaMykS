<?php
/**
 * @brief Essentiel B (Boulanger) client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Jun 2020
 * @date Modification: Jul 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Essentiel B client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_EssentielBClientDevice($deviceCode='') {
    $deviceList = array(
        /* Essentiel B tablets */
        'Smart_TAB_1003s'   => array('platform_model' => 'Smart Tab 1003S', 'platform_year' => 2014, 'platform_type' => 'tablet',    'platform_format' => 'tablet'),
        'SmartTab1005'      => array('platform_model' => 'Smart Tab 1005', 'platform_year' => 2017, 'platform_type' => 'tablet',    'platform_format' => 'tablet'),

        /* Essentiel B mobiles */
        'HEYOU5'    => array('platform_model' => 'HEYou 5',     'platform_year' => 2017),
        'HEYOU40'   => array('platform_model' => 'HEYou 40',    'platform_year' => 2020),
        'HEYOU50'   => array('platform_model' => 'HEYou 50',    'platform_year' => 2019),
        'HEYOU60'   => array('platform_model' => 'HEYou 60',    'platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Essentiel B',
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
