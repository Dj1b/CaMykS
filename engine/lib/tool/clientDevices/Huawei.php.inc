<?php
/**
 * @brief Huawei client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Huawei.php.inc
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
 * Return Huawei client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_HuaweiClientDevice($deviceCode='') {
    $deviceList = array(
        'ALE-L21'   => array('platform_model' => 'P8 Lite'),
        'GRA-L09'   => array('platform_model' => 'P8'),
        'EVA-L09'   => array('platform_model' => 'P9'),
        'EVA-L19'   => array('platform_model' => 'P9 (Dual Sim)'),
        'VNS-L31'   => array('platform_model' => 'P9 Lite'),
        'VIE-L29'   => array('platform_model' => 'P9 Plus'),
        'VTR-L29'   => array('platform_model' => 'P10'),
        'NXT-L09'   => array('platform_model' => 'Mate 8'),
        'NXT-L29'   => array('platform_model' => 'Mate 8'),
        'MHA-L09'   => array('platform_model' => 'Mate 8'),
        'RNE-L21'   => array('platform_model' => 'Mate 10 Lite'),
        'BLA-L29'   => array('platform_model' => 'Mate 10 Pro'),
        'BLA-L29S'  => array('platform_model' => 'Mate 10 Pro'),
        'CRR-L09'   => array('platform_model' => 'Mate S'),
        'CRR-L09'   => array('platform_model' => 'Mate S'),
        'NEM-L51'   => array('platform_model' => 'Honor 5C'),
        'BLN-L21'   => array('platform_model' => 'Honor 6X'),
        'PLK-L01'   => array('platform_model' => 'Honor 7'),
        'FRD-L09'   => array('platform_model' => 'Honor 8'),
        'FRD-L19'   => array('platform_model' => 'Honor 8'),
        'Y635-L01'  => array('platform_model' => 'Y635'),
        'Y520-U22'  => array('platform_model' => 'Ascend'),
        'Y600-U151' => array('platform_model' => 'Ascend'),
        'Y360-U03'  => array('platform_model' => 'Y3'),
        'CUN-L21'   => array('platform_model' => 'Y5'),
        'SCL-L01'   => array('platform_model' => 'Y6'),
        'LYO-L01'   => array('platform_model' => 'Y6 II Compact'),
        'NMO-L31'   => array('platform_model' => 'GT3'),
        'CAN-L11'   => array('platform_model' => 'Nova'),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Huawei',
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