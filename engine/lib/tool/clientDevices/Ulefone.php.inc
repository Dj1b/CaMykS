<?php
/**
 * @brief Ulefone client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.10
 * @date Creation: Mar 2019
 * @date Modification: May 2021
 * @copyright 2019 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Ulefone client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_UlefoneClientDevice($deviceCode='') {
    $deviceList = array(
        /* S series */
        's10_pro'       => array('platform_model' => 'S10 Pro',         'platform_year' => 2018),
        's11'           => array('platform_model' => 'S11',             'platform_year' => 2019),

        /* Armor series */
        'armor_x'       => array('platform_model' => 'Armor X',         'platform_year' => 2018),
        'armor_6'       => array('platform_model' => 'Armor 6',         'platform_year' => 2019),
        'armor_6s'      => array('platform_model' => 'Armor 6S',        'platform_year' => 2019),
        'armor x5'      => array('platform_model' => 'Armor X5',        'platform_year' => 2019),
        'armor_x6'      => array('platform_model' => 'Armor X6',        'platform_year' => 2019),
        'armor 7'       => array('platform_model' => 'Armor 7',         'platform_year' => 2020),
        'armor 7e'      => array('platform_model' => 'Armor 7E',        'platform_year' => 2020),
        'armor x7 pro'  => array('platform_model' => 'Armor X7 Pro',    'platform_year' => 2020),

        /* Note series */
        'note 8p'       => array('platform_model' => 'Note 8P',         'platform_year' => 2020),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Ulefone',
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
?>
