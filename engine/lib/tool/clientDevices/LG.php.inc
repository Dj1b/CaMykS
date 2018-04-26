<?php
/**
 * @brief LG client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/LG.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return LG client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_LGClientDevice($deviceCode='') {
    $deviceList = array(
        'D160'  => array('platform_model' => 'L40',),
        'D290'  => array('platform_model' => 'L Fino',),
        'D315'  => array('platform_model' => 'F70',),
        'D320'  => array('platform_model' => 'L70',),
        'D405'  => array('platform_model' => 'L90',),
        'D505'  => array('platform_model' => 'Optimus F6',),
        'D620'  => array('platform_model' => 'G2 Mini',),
        'D722'  => array('platform_model' => 'G3 S',),
        'D802'  => array('platform_model' => 'Nexus 5',),
        'D821'  => array('platform_model' => 'G2',),
        'D855'  => array('platform_model' => 'G3',),
        'D855'  => array('platform_model' => 'G Flex',),
        'E410'  => array('platform_model' => 'Optimus L1 II',),
        'E430'  => array('platform_model' => 'Optimus L3 II',),
        'E440'  => array('platform_model' => 'Optimus L4 II',),
        'E460'  => array('platform_model' => 'Optimus L5 II',),
        'E610'  => array('platform_model' => 'Optimus L5',),
        'E960'  => array('platform_model' => 'Nexus 4',),
        'H815'  => array('platform_model' => 'G4',),
        'H870D' => array('platform_model' => 'G6',),
        'L160L' => array('platform_model' => 'Optimus LTE2',),
        'M700'  => array('platform_model' => 'Q6 Alpha',),
        'M160'  => array('platform_model' => 'K4',              'platform_year' => 2017),
        'P715'  => array('platform_model' => 'Optimus L7 II',),
        'P875'  => array('platform_model' => 'Optimus F5',),
        'LS996' => array('platform_model' => 'G Flex 2', ),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'LG',
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