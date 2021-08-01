<?php
/**
 * @brief Ace client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jul 2021
 * @date Modification: Jul 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Ace client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_AceClientDevice($deviceCode='') {
    $deviceList = array(
        'BUZZ 1'        => array('platform_model' => 'Buzz 1', 'platform_year' => '2019'),
        'BUZZ 1 LITE'   => array('platform_model' => 'Buzz 1 Lite', 'platform_year' => '2019'),
        'BUZZ 1 PLUS'   => array('platform_model' => 'Buzz 1 Plus', 'platform_year' => '2019'),
        'BUZZ 3'        => array('platform_model' => 'Buzz 3', 'platform_year' => '2021'),
        'BUZZ 3 LITE'   => array('platform_model' => 'Buzz 3 Lite', 'platform_year' => '2021'),
        'BUZZ 3 PLUS'   => array('platform_model' => 'Buzz 3 Plus', 'platform_year' => '2021'),

        'URBAN 1'       => array('platform_model' => 'Urban 1', 'platform_year' => '2019'),
        'URBAN 1 PRO'   => array('platform_model' => 'Urban 1 Pro', 'platform_year' => '2019'),
        'URBAN 3'       => array('platform_model' => 'Urban 3', 'platform_year' => '2021'),

        'CLEVER 1'      => array('platform_model' => 'Clever 1', 'platform_year' => '2019'),
        'CLEVER 3'      => array('platform_model' => 'Clever 3', 'platform_year' => '2021'),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Ace',
        'platform_country'  => 'dz',
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
