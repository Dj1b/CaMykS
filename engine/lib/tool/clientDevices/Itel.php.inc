<?php
/**
 * @brief Itel client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.13
 * @date Creation: Jan 2019
 * @date Modification: Jun 2021
 * @copyright 2019 - 2021 CaMykS Team
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
        'A14'           => array('platform_model' => 'A14',         'platform_year' => 2018),
        'P32'           => array('platform_model' => 'P32',         'platform_year' => 2018),
        'S13'           => array('platform_model' => 'S13',         'platform_year' => 2018),
        'W5001P'        => array('platform_model' => 'A33',         'platform_year' => 2019),
        'W5005'         => array('platform_model' => 'P15',         'platform_year' => 2019),
        'W5504'         => array('platform_model' => 'P33',         'platform_year' => 2019),
        'A16 Plus'      => array('platform_model' => 'A16 Plus',    'platform_year' => 2019),
        'L6002P'        => array('platform_model' => 'S15 Pro',     'platform_year' => 2020),
        'L6501'         => array('platform_model' => 'Vision 1',    'platform_year' => 2020),
        'W6004'         => array('platform_model' => 'A56',         'platform_year' => 2020),
        'W6004P'        => array('platform_model' => 'A56 Pro',     'platform_year' => 2020),
        'W6502'         => array('platform_model' => 'S16',         'platform_year' => 2020),
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
