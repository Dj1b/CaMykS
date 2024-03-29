<?php
/**
 * @brief Condor client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.9
 * @date Creation: Apr 2018
 * @date Modification: Sep 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Condor client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_CondorClientDevice($deviceCode='') {
    $deviceList = array(
        /* Condor tablets */
        'TCV101G'           => array('platform_model' => 'Tab TCV-101G',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
        'TCV703G'           => array('platform_model' => 'Tab TCV-703G',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
        'TGW706'            => array('platform_model' => 'Tab TGW-706',     'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
        'TFX708G'           => array('platform_model' => 'Tab TFX-708G',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2015),
        'TGW710G'           => array('platform_model' => 'Tab TGW-710G',    'platform_type' => 'tablet',   'platform_format' => 'tablet',  'platform_year' => 2016),

        /* Condor phone */
        'PGN404'            => array('platform_model' => 'C7 Mini     ',    'platform_year' => 2014),
        'PGN518'            => array('platform_model' => 'Plume P6 Pro',    'platform_year' => 2015),
        'PGN521'            => array('platform_model' => 'Griffe G4 Plus',  'platform_year' => 2015),
        'PHQ520'            => array('platform_model' => 'Griffe G5',       'platform_year' => 2016),
        'PAM524'            => array('platform_model' => 'Griffe G5 Plus',  'platform_year' => 2016),
        'PGN527'            => array('platform_model' => 'Plume P4 Plus',   'platform_year' => 2017),
        'PGN522'            => array('platform_model' => 'Plume P6 Plus',   'platform_year' => 2016),
        'PGN528'            => array('platform_model' => 'Plume P6 Pro',    'platform_year' => 2017),
        'PGN523'            => array('platform_model' => 'Plume P7 Plus',   'platform_year' => 2016),
        'PGN605'            => array('platform_model' => 'Plume P8',        'platform_year' => 2015),
        'PGN610'            => array('platform_model' => 'Plume P8 Lite',   'platform_year' => 2015),
        'PGN611'            => array('platform_model' => 'Allure A8',       'platform_year' => 2016),
        'PGN612'            => array('platform_model' => 'Allure A8 Plus',  'platform_year' => 2017),
        'PGN613'            => array('platform_model' => 'Allure A55 Plus', 'platform_year' => 2017),
        'PGN507'            => array('platform_model' => 'Allure A9',       'platform_year' => 2015),
        'SP413'             => array('platform_model' => 'Griffe T1',       'platform_year' => 2017),
        'PHQ520'            => array('platform_model' => 'Griffe G6',       'platform_year' => 2018),

        'Allure M1'         => array('platform_model' => 'Allure M1',       'platform_year' => 2017),
        'Allure M1 Plus'    => array('platform_model' => 'Allure M1 Plus',  'platform_year' => 2017),
        'Allure X'          => array('platform_model' => 'Allure X',        'platform_year' => 2019),
        'Griffe T2'         => array('platform_model' => 'Griffe T2',       'platform_year' => 2017),
        'Plume P8 Pro'      => array('platform_model' => 'Plume P8 Pro',    'platform_year' => 2017),
        'Plume L2 Pro'      => array('platform_model' => 'Plume L2 Pro',    'platform_year' => 2018),
        'Allure M2'         => array('platform_model' => 'Allure M2',       'platform_year' => 2018),

    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Condor',
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
