<?php
/**
 * @brief Huawei client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Huawei.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
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
        'ALE-L21'   => array('platform_model' => 'P8 Lite',         'plateform_year' => 2015),
        'GRA-L09'   => array('platform_model' => 'P8',              'plateform_year' => 2015),
        'EVA-L09'   => array('platform_model' => 'P9',              'plateform_year' => 2016),
        'EVA-L19'   => array('platform_model' => 'P9 (Dual Sim)',   'plateform_year' => 2016),
        'VNS-L31'   => array('platform_model' => 'P9 Lite',         'plateform_year' => 2016),
        'VIE-L29'   => array('platform_model' => 'P9 Plus',         'plateform_year' => 2016),
        'VTR-L29'   => array('platform_model' => 'P10',             'plateform_year' => 2017),
        'NXT-L09'   => array('platform_model' => 'Mate 8',          'plateform_year' => 2015),
        'NXT-L29'   => array('platform_model' => 'Mate 8',          'plateform_year' => 2015),
        'MHA-L09'   => array('platform_model' => 'Mate 8',          'plateform_year' => 2016),
        'RNE-L21'   => array('platform_model' => 'Mate 10 Lite',    'plateform_year' => 2017),
        'BLA-L29'   => array('platform_model' => 'Mate 10 Pro',     'plateform_year' => 2017),
        'BLA-L29S'  => array('platform_model' => 'Mate 10 Pro',     'plateform_year' => 2017),
        'CRR-L09'   => array('platform_model' => 'Mate S',          'plateform_year' => 2015),
        'NEM-L51'   => array('platform_model' => 'Honor 5C',        'plateform_year' => 2016),
        'BLN-L21'   => array('platform_model' => 'Honor 6X',        'plateform_year' => 2017),
        'PLK-L01'   => array('platform_model' => 'Honor 7',         'plateform_year' => 2015),
        'FRD-L09'   => array('platform_model' => 'Honor 8',         'plateform_year' => 2016),
        'FRD-L19'   => array('platform_model' => 'Honor 8',         'plateform_year' => 2016),
        'Y635-L01'  => array('platform_model' => 'Y635',            'plateform_year' => 2015),
        'Y520-U22'  => array('platform_model' => 'Ascend',          'plateform_year' => 2014),
        'Y600-U151' => array('platform_model' => 'Ascend',          'plateform_year' => 2014),
        'Y360-U03'  => array('platform_model' => 'Y3',              'plateform_year' => 2015),
        'CUN-L21'   => array('platform_model' => 'Y5',              'plateform_year' => 2016),
        'SCL-L01'   => array('platform_model' => 'Y6',              'plateform_year' => 2015),
        'LYO-L01'   => array('platform_model' => 'Y6 II Compact',   'plateform_year' => 2016),
        'NMO-L31'   => array('platform_model' => 'GT3',             'plateform_year' => 2016),
        'CAN-L11'   => array('platform_model' => 'Nova',            'plateform_year' => 2016),
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
