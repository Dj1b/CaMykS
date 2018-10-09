<?php
/**
 * @brief Huawei client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Huawei.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.15
 * @date Creation: Apr 2018
 * @date Modification: Oct 2018
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
        /* Huawei tablets */
        'M2-A01W'           => array('platform_model' => 'MediaPad M2', 'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'GEM-703LT'         => array('platform_model' => 'MediaPad X2', 'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'BEETHOVEN-W09'     => array('platform_model' => 'MediaPad M3', 'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'BEETHOVEN-DL09'    => array('platform_model' => 'MediaPad M3', 'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'AGS-W09'           => array('platform_model' => 'MediaPad T3', 'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        'CMR-W09'           => array('platform_model' => 'MediaPad M5', 'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),


        /* Huawei phones */
        'ALE-L21'   => array('platform_model' => 'P8 Lite',         'platform_year' => 2015),
        'ALE-CL00'  => array('platform_model' => 'P8 Lite',         'platform_year' => 2015),
        'ALE-L02'   => array('platform_model' => 'P8 Lite',         'platform_year' => 2015),
        'PRA-LX1'   => array('platform_model' => 'P8 Lite',         'platform_year' => 2017),
        'GRA-L09'   => array('platform_model' => 'P8',              'platform_year' => 2015),
        'EVA-L09'   => array('platform_model' => 'P9',              'platform_year' => 2016),
        'EVA-L19'   => array('platform_model' => 'P9 (Dual Sim)',   'platform_year' => 2016),
        'VNS-L31'   => array('platform_model' => 'P9 Lite',         'platform_year' => 2016),
        'VNS-L53'   => array('platform_model' => 'P9 Lite',         'platform_year' => 2016),
        'PRA-LX3'   => array('platform_model' => 'P9 Lite',         'platform_year' => 2017),
        'VIE-L29'   => array('platform_model' => 'P9 Plus',         'platform_year' => 2016),
        'VTR-L09'   => array('platform_model' => 'P10',             'platform_year' => 2017),
        'VTR-L29'   => array('platform_model' => 'P10',             'platform_year' => 2017),
        'WAS-LX1A'  => array('platform_model' => 'P10 Lite',        'platform_year' => 2017),
        'VKY-L29'   => array('platform_model' => 'P10 Plus',        'platform_year' => 2017),
        'EML-L29'   => array('platform_model' => 'P20',             'platform_year' => 2018),
        'ANE-LX1'   => array('platform_model' => 'P20 Lite',        'platform_year' => 2018),
        'ANE-LX3'   => array('platform_model' => 'P20 Lite',        'platform_year' => 2018),
        'CLT-L29'   => array('platform_model' => 'P20 Pro',         'platform_year' => 2018),
        'NXT-L09'   => array('platform_model' => 'Mate 8',          'platform_year' => 2015),
        'NXT-L29'   => array('platform_model' => 'Mate 8',          'platform_year' => 2015),
        'MHA-L09'   => array('platform_model' => 'Mate 8\'',        'platform_year' => 2016),
        'MHA-L29'   => array('platform_model' => 'Mate 9',          'platform_year' => 2016),
        'RNE-L21'   => array('platform_model' => 'Mate 10 Lite',    'platform_year' => 2017),
        'BLA-A09'   => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-AL00'  => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-L09S'  => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-L29'   => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-L29S'  => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'CRR-L09'   => array('platform_model' => 'Mate S',          'platform_year' => 2015),
        'BND-L34'   => array('platform_model' => 'Mate SE',         'platform_year' => 2016),
        'NEM-L51'   => array('platform_model' => 'Honor 5C',        'platform_year' => 2016),
        'KIW-L21'   => array('platform_model' => 'Honor 5X',        'platform_year' => 2015),
        'JMM-L22'   => array('platform_model' => 'Honor 6C Pro',    'platform_year' => 2017),
        'BLN-L21'   => array('platform_model' => 'Honor 6X',        'platform_year' => 2017),
        'PLK-L01'   => array('platform_model' => 'Honor 7',         'platform_year' => 2015),
        'FRD-L09'   => array('platform_model' => 'Honor 8',         'platform_year' => 2016),
        'FRD-L19'   => array('platform_model' => 'Honor 8',         'platform_year' => 2016),
        'PRA-TL10'  => array('platform_model' => 'Honor 8 Lite',    'platform_year' => 2016),
        'DUK-L09'   => array('platform_model' => 'Honor 8 Pro',     'platform_year' => 2017),
        'STF-L09'   => array('platform_model' => 'Honor 9',         'platform_year' => 2017),
        'LLD-L31'   => array('platform_model' => 'Honor 9 Lite',    'platform_year' => 2017),
        'COL-L29'   => array('platform_model' => 'Honor 10',        'platform_year' => 2018),
        'BKL-L09S'  => array('platform_model' => 'Honor View 10',   'platform_year' => 2018),
        'AUM-L29'   => array('platform_model' => 'Honor 7A Pro',    'platform_year' => 2018),
        'Y635-L01'  => array('platform_model' => 'Y635',            'platform_year' => 2015),
        'Y520-U22'  => array('platform_model' => 'Ascend',          'platform_year' => 2014),
        'Y600-U151' => array('platform_model' => 'Ascend',          'platform_year' => 2014),
        'U9201L'    => array('platform_model' => 'Ascend P1',       'platform_year' => 2012),
        'Y520-U22'  => array('platform_model' => 'Ascend Y520',     'platform_year' => 2014),
        'Y600-U151' => array('platform_model' => 'Ascend Y600',     'platform_year' => 2014),
        'Y360-U03'  => array('platform_model' => 'Y3',              'platform_year' => 2015),
        'Y635-L21'  => array('platform_model' => 'Y635',            'platform_year' => 2015),
        'CUN-L21'   => array('platform_model' => 'Y5',              'platform_year' => 2016),
        'CUN-L03'   => array('platform_model' => 'Y5 II',           'platform_year' => 2016),
        'SCL-L01'   => array('platform_model' => 'Y6',              'platform_year' => 2015),
        'SCL-U31'   => array('platform_model' => 'Y6',              'platform_year' => 2015),
        'MYA-L41'   => array('platform_model' => 'Y6',              'platform_year' => 2017),
        'LYO-L01'   => array('platform_model' => 'Y6 II Compact',   'platform_year' => 2016),
        'TRT-LX2'   => array('platform_model' => 'Y7',              'platform_year' => 2017),
        'TRT-LX3'   => array('platform_model' => 'Y7',              'platform_year' => 2017),
        'TRT-L53'   => array('platform_model' => 'Y7\'',            'platform_year' => 2018),
        'FLA-LX2'   => array('platform_model' => 'Y9',              'platform_year' => 2018),
        'NMO-L31'   => array('platform_model' => 'GT3',             'platform_year' => 2016),
        'BLL-L22'   => array('platform_model' => 'GR5',             'platform_year' => 2017),
        'CAN-L11'   => array('platform_model' => 'Nova',            'platform_year' => 2016),
        'PRA-LX2'   => array('platform_model' => 'Nova Lite',       'platform_year' => 2017),
        'PIC-AL00'  => array('platform_model' => 'Nova 2',          'platform_year' => 2017),
        'PIC-LX9'   => array('platform_model' => 'Nova 2',          'platform_year' => 2017),
        'BAC-AL00'  => array('platform_model' => 'Nova 2 Plus',     'platform_year' => 2017),
        'BAC-L03'   => array('platform_model' => 'Nova 2 Plus',     'platform_year' => 2017),
        'BAC-L21'   => array('platform_model' => 'Nova 2 Plus',     'platform_year' => 2017),
        'BAC-L22'   => array('platform_model' => 'Nova 2 Plus',     'platform_year' => 2017),
        'BAC-L23'   => array('platform_model' => 'Nova 2 Plus',     'platform_year' => 2017),
        'BAC-TL00'  => array('platform_model' => 'Nova 2 Plus',     'platform_year' => 2017),
        'LDN-LX2'   => array('platform_model' => 'Nova 2 Lite',     'platform_year' => 2018),
        'ALE-L23'   => array('platform_model' => 'G Elite',         'platform_year' => 2015),
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
