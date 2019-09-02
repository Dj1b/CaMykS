<?php
/**
 * @brief Huawei client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Huawei.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.48
 * @date Creation: Apr 2018
 * @date Modification: Aug 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return known Huawei client device list
 * @return array
 */
function get_HuaweiClientDevices() {
    return array(
        /* Huawei tablets */
        'MediaPad T1 8.0 Pro'   => array('platform_model' => 'MediaPad T1 8.0 Pro',     'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2014),
        'T1-A21L'               => array('platform_model' => 'MediaPad T1 10 Pro',      'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'M2-A01W'               => array('platform_model' => 'MediaPad M2',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'GEM-703LT'             => array('platform_model' => 'MediaPad X2',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2015),
        'BEETHOVEN-W09'         => array('platform_model' => 'MediaPad M3',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'BEETHOVEN-DL09'        => array('platform_model' => 'MediaPad M3',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'BTV-DL09'              => array('platform_model' => 'MediaPad M3',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'FDR-A01w'              => array('platform_model' => 'MediaPad T2 10.0 Pro',    'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2016),
        'AGS-W09'               => array('platform_model' => 'MediaPad T3',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        'BG2-U01'               => array('platform_model' => 'MediaPad T3 7',           'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        'BG2-W09'               => array('platform_model' => 'MediaPad T3',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        'CMR-W09'               => array('platform_model' => 'MediaPad M5',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2017),
        'SHT-W09'               => array('platform_model' => 'MediaPad M5 8.4',         'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2018),
        'BAH2-W19'              => array('platform_model' => 'MediaPad M5 Lite',        'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2018),
        'AGS2-W09'              => array('platform_model' => 'MediaPad T5',             'platform_type' => 'tablet',    'platform_format' => 'tablet',  'platform_year' => 2018),

        /* Huawei P series */
        'ALE-L21'   => array('platform_model' => 'P8 Lite',         'platform_year' => 2015),
        'ALE-CL00'  => array('platform_model' => 'P8 Lite',         'platform_year' => 2015),
        'ALE-L02'   => array('platform_model' => 'P8 Lite',         'platform_year' => 2015),
        'PRA-LX1'   => array('platform_model' => 'P8 Lite',         'platform_year' => 2017),
        'GRA-L09'   => array('platform_model' => 'P8',              'platform_year' => 2015),
        'EVA-L09'   => array('platform_model' => 'P9',              'platform_year' => 2016),
        'EVA-L19'   => array('platform_model' => 'P9 (Dual Sim)',   'platform_year' => 2016),
        'VNS-L21'   => array('platform_model' => 'P9 Lite',         'platform_year' => 2016),
        'VNS-L31'   => array('platform_model' => 'P9 Lite',         'platform_year' => 2016),
        'VNS-L53'   => array('platform_model' => 'P9 Lite',         'platform_year' => 2016),
        'PRA-LX3'   => array('platform_model' => 'P9 Lite',         'platform_year' => 2017),
        'SLA-L22'   => array('platform_model' => 'P9 Lite Mini',    'platform_year' => 2017),
        'VIE-L09'   => array('platform_model' => 'P9 Plus',         'platform_year' => 2016),
        'VIE-L29'   => array('platform_model' => 'P9 Plus',         'platform_year' => 2016),
        'VTR-L09'   => array('platform_model' => 'P10',             'platform_year' => 2017),
        'VTR-L29'   => array('platform_model' => 'P10',             'platform_year' => 2017),
        'WAS-L03T'  => array('platform_model' => 'P10 Lite',        'platform_year' => 2017),
        'WAS-LX1A'  => array('platform_model' => 'P10 Lite',        'platform_year' => 2017),
        'WAS-LX2'   => array('platform_model' => 'P10 Lite',        'platform_year' => 2017),
        'WAS-TL10'  => array('platform_model' => 'P10 Lite',        'platform_year' => 2017),
        'VKY-L29'   => array('platform_model' => 'P10 Plus',        'platform_year' => 2017),
        'EML-AL00'  => array('platform_model' => 'P20',             'platform_year' => 2018),
        'EML-L09'   => array('platform_model' => 'P20',             'platform_year' => 2018),
        'EML-L29'   => array('platform_model' => 'P20',             'platform_year' => 2018),
        'ANE-LX1'   => array('platform_model' => 'P20 Lite',        'platform_year' => 2018),
        'ANE-LX2'   => array('platform_model' => 'P20 Lite',        'platform_year' => 2018),
        'ANE-LX2J'  => array('platform_model' => 'P20 Lite',        'platform_year' => 2018),
        'ANE-LX3'   => array('platform_model' => 'P20 Lite',        'platform_year' => 2018),
        'CLT-L04'   => array('platform_model' => 'P20 Pro',         'platform_year' => 2018),
        'CLT-L09'   => array('platform_model' => 'P20 Pro',         'platform_year' => 2018),
        'CLT-L29'   => array('platform_model' => 'P20 Pro',         'platform_year' => 2018),
        'ELE-L29'   => array('platform_model' => 'P30',             'platform_year' => 2019),
        'MAR-LX1A'  => array('platform_model' => 'P30 Lite',        'platform_year' => 2019),
        'VOG-L29'   => array('platform_model' => 'P30 Pro',         'platform_year' => 2019),
        'FIG-LA1'   => array('platform_model' => 'P Smart',         'platform_year' => 2017),
        'FIG-LX1'   => array('platform_model' => 'P Smart',         'platform_year' => 2017),
        'FIG-LX3'   => array('platform_model' => 'P Smart',         'platform_year' => 2017),
        'INE-LX1'   => array('platform_model' => 'P Smart+',        'platform_year' => 2018),
        'POT-LX1'   => array('platform_model' => 'P Smart',         'platform_year' => 2019),
        'STK-L21'   => array('platform_model' => 'P Smart Z',       'platform_year' => 2019),
        'STK-LX1'   => array('platform_model' => 'P Smart Z',       'platform_year' => 2019),
        'STK-LX3'   => array('platform_model' => 'P Smart Z',       'platform_year' => 2019),

        /* Huawei Mate series */
        'CRR-L09'   => array('platform_model' => 'Mate S',          'platform_year' => 2015),
        'BND-L34'   => array('platform_model' => 'Mate SE',         'platform_year' => 2016),
        'NXT-L09'   => array('platform_model' => 'Mate 8',          'platform_year' => 2015),
        'NXT-L29'   => array('platform_model' => 'Mate 8',          'platform_year' => 2015),
        'MHA-L09'   => array('platform_model' => 'Mate 8\'',        'platform_year' => 2016),
        'MHA-L29'   => array('platform_model' => 'Mate 9',          'platform_year' => 2016),
        'RNE-L21'   => array('platform_model' => 'Mate 10 Lite',    'platform_year' => 2017),
        'BLA-A09'   => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-AL00'  => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-L09'   => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-L09S'  => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-L29'   => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'BLA-L29S'  => array('platform_model' => 'Mate 10 Pro',     'platform_year' => 2017),
        'SNE-L21'   => array('platform_model' => 'Mate 20 Lite',    'platform_year' => 2018),
        'SNE-LX1'   => array('platform_model' => 'Mate 20 Lite',    'platform_year' => 2018),
        'HMA-L29'   => array('platform_model' => 'Mate 20',         'platform_year' => 2018),
        'LYA-L09'   => array('platform_model' => 'Mate 20 Pro',     'platform_year' => 2018),
        'LYA-L29'   => array('platform_model' => 'Mate 20 Pro',     'platform_year' => 2018),

        /* Huawei Honor series */
        'CHM-U01'   => array('platform_model' => 'Honor 4C',        'platform_year' => 2015),
        'LYO-L21'   => array('platform_model' => 'Honor 5A',        'platform_year' => 2016),
        'NEM-L22'   => array('platform_model' => 'Honor 5C',        'platform_year' => 2016),
        'NEM-L51'   => array('platform_model' => 'Honor 5C',        'platform_year' => 2016),
        'NEM-UL10'  => array('platform_model' => 'Honor 5C',        'platform_year' => 2016),
        'KIW-L21'   => array('platform_model' => 'Honor 5X',        'platform_year' => 2015),
        'DLI-L22'   => array('platform_model' => 'Honor 6A',        'platform_year' => 2017),
        'DLI-L42'   => array('platform_model' => 'Honor 6A Pro',    'platform_year' => 2017),
        'DIG-L21HN' => array('platform_model' => 'Honor 6C',        'platform_year' => 2017),
        'JMM-L22'   => array('platform_model' => 'Honor 6C Pro',    'platform_year' => 2017),
        'BLN-L21'   => array('platform_model' => 'Honor 6X',        'platform_year' => 2017),
        'PLK-L01'   => array('platform_model' => 'Honor 7',         'platform_year' => 2015),
        'BND-L21'   => array('platform_model' => 'Honor 7X',        'platform_year' => 2017),
        'BND-L24'   => array('platform_model' => 'Honor 7X',        'platform_year' => 2017),
        'DUA-L22'   => array('platform_model' => 'Honor 7S',        'platform_year' => 2018),
        'DUA-LX2'   => array('platform_model' => 'Honor 7S',        'platform_year' => 2018),
        'FRD-AL00'  => array('platform_model' => 'Honor 8',         'platform_year' => 2016),
        'FRD-L09'   => array('platform_model' => 'Honor 8',         'platform_year' => 2016),
        'FRD-L19'   => array('platform_model' => 'Honor 8',         'platform_year' => 2016),
        'PRA-TL10'  => array('platform_model' => 'Honor 8 Lite',    'platform_year' => 2016),
        'DUK-L09'   => array('platform_model' => 'Honor 8 Pro',     'platform_year' => 2017),
        'JSN-L21'   => array('platform_model' => 'Honor 8X',        'platform_year' => 2018),
        'JSN-L22'   => array('platform_model' => 'Honor 8X',        'platform_year' => 2018),
        'STF-L09'   => array('platform_model' => 'Honor 9',         'platform_year' => 2017),
        'LLD-L31'   => array('platform_model' => 'Honor 9 Lite',    'platform_year' => 2017),
        'COL-L29'   => array('platform_model' => 'Honor 10',        'platform_year' => 2018),
        'HRY-LX1'   => array('platform_model' => 'Honor 10 Lite',   'platform_year' => 2018),
        'AUM-L29'   => array('platform_model' => 'Honor 7A Pro',    'platform_year' => 2018),
        'COR-L29'   => array('platform_model' => 'Honor Play',      'platform_year' => 2018),
        'BKL-L09'   => array('platform_model' => 'Honor View 10',   'platform_year' => 2018),
        'BKL-L09S'  => array('platform_model' => 'Honor View 10',   'platform_year' => 2018),
        'PCT-L29'   => array('platform_model' => 'Honor View 20',   'platform_year' => 2019),

        /* Huawei Ascend series */
        'Y520-U22'  => array('platform_model' => 'Ascend',          'platform_year' => 2014),
        'Y600-U151' => array('platform_model' => 'Ascend',          'platform_year' => 2014),
        'U9201L'    => array('platform_model' => 'Ascend P1',       'platform_year' => 2012),
        'Y520-U22'  => array('platform_model' => 'Ascend Y520',     'platform_year' => 2014),
        'Y600-U151' => array('platform_model' => 'Ascend Y600',     'platform_year' => 2014),
        'MT7-L09'   => array('platform_model' => 'Ascend Mate 7',   'platform_year' => 2014),
        'MT7-TL00'  => array('platform_model' => 'Ascend Mate 7',   'platform_year' => 2014),
        'H1611'     => array('platform_model' => 'Ascend XT',       'platform_year' => 2016),

        /* Huawei Y series */
        'Y360-U03'  => array('platform_model' => 'Y3',              'platform_year' => 2015),
        'Y635-L01'  => array('platform_model' => 'Y635',            'platform_year' => 2015),
        'Y635-L21'  => array('platform_model' => 'Y635',            'platform_year' => 2015),
        'CUN-L21'   => array('platform_model' => 'Y5',              'platform_year' => 2015),
        'Y560-L01'  => array('platform_model' => 'Y5',              'platform_year' => 2015),
        'CUN-L03'   => array('platform_model' => 'Y5 II',           'platform_year' => 2016),
        'DRA-L21'   => array('platform_model' => 'Y5',              'platform_year' => 2018),
        'SCL-L01'   => array('platform_model' => 'Y6',              'platform_year' => 2016),
        'SCL-L21'   => array('platform_model' => 'Y6',              'platform_year' => 2016),
        'SCL-U31'   => array('platform_model' => 'Y6',              'platform_year' => 2016),
        'CAM-L21'   => array('platform_model' => 'Y6 II',           'platform_year' => 2016),
        'LYO-L01'   => array('platform_model' => 'Y6 II Compact',   'platform_year' => 2016),
        'MYA-L11'   => array('platform_model' => 'Y6',              'platform_year' => 2017),
        'MYA-L41'   => array('platform_model' => 'Y6',              'platform_year' => 2017),
        'ATU-L11'   => array('platform_model' => 'Y6',              'platform_year' => 2018),
        'ATU-L21'   => array('platform_model' => 'Y6',              'platform_year' => 2018),
        'ATU-L22'   => array('platform_model' => 'Y6',              'platform_year' => 2018),
        'MRD-LX1N'  => array('platform_model' => 'Y6',              'platform_year' => 2019),
        'TRT-LX1'   => array('platform_model' => 'Y7',              'platform_year' => 2017),
        'TRT-LX2'   => array('platform_model' => 'Y7',              'platform_year' => 2017),
        'TRT-LX3'   => array('platform_model' => 'Y7',              'platform_year' => 2017),
        'TRT-L53'   => array('platform_model' => 'Y7\'',            'platform_year' => 2018),
        'LDN-L01'   => array('platform_model' => 'Y7',              'platform_year' => 2018),
        'LDN-L21'   => array('platform_model' => 'Y7 Prime',        'platform_year' => 2018),
        'DUB-LX1'   => array('platform_model' => 'Y7 Prime',        'platform_year' => 2019),
        'FLA-LX2'   => array('platform_model' => 'Y9',              'platform_year' => 2018),

        /* Huawei Nova series */
        'CAN-L11'   => array('platform_model' => 'Nova',            'platform_year' => 2016),
        'MLA-L12'   => array('platform_model' => 'Nova Plus',       'platform_year' => 2016),
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
        'PAR-AL00'  => array('platform_model' => 'Nova 3',          'platform_year' => 2018),
        'PAR-TL00'  => array('platform_model' => 'Nova 3',          'platform_year' => 2018),

        /* Huawei G series */
        'ALE-L23'   => array('platform_model' => 'G Elite',         'platform_year' => 2015),
        'NMO-L31'   => array('platform_model' => 'GT3',             'platform_year' => 2016),
        'BLL-L22'   => array('platform_model' => 'GR5',             'platform_year' => 2017),

        /* Huawei other models */
        'DUB-AL00'  => array('platform_model' => 'Enjoy 9',         'platform_year' => 2018),
    );
}

/**
 * Return Huawei client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_HuaweiClientDevice($deviceCode='') {
    $deviceList = get_HuaweiClientDevices();

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Huawei',
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

/*
 * Check if given device is a Huawei know device
 * @return array
 */
function is_HuaweiKnownDevice($deviceCode='') {
    $deviceList = get_HuaweiClientDevices();
    return (array_key_exists($deviceCode, $deviceList));
}
?>