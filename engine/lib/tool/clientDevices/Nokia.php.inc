<?php
/**
 * @brief Nokia client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Nokia.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.24
 * @date Creation: Jun 2018
 * @date Modification: Aug 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Nokia client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_NokiaClientDevice($deviceCode='') {
    $deviceList = array(
        'Lumia 920'     => array('platform_model' => 'Lumia 920',       'platform_year' => 2012),
        'Lumia 925'     => array('platform_model' => 'Lumia 925',       'platform_year' => 2013),
        'Lumia 530'     => array('platform_model' => 'Lumia 530',       'platform_year' => 2014),
        'Lumia 535'     => array('platform_model' => 'Lumia 535',       'platform_year' => 2014),
        'Lumia 735'     => array('platform_model' => 'Lumia 735',       'platform_year' => 2014),
        'Lumia 830'     => array('platform_model' => 'Lumia 830',       'platform_year' => 2014),
        'Lumia 830'     => array('platform_model' => 'Lumia 830',       'platform_year' => 2014),
        'Lumia 950 XL'  => array('platform_model' => 'Lumia 950 XL',    'platform_year' => 2015),
        'Lumia 640'     => array('platform_model' => 'Lumia 640',       'platform_year' => 2015),
        'Lumia 640 LTE' => array('platform_model' => 'Lumia 640 LTE',   'platform_year' => 2015),

        'TA-1004'       => array('platform_model' => '8',               'platform_year' => 2017),
        'TA-1005'       => array('platform_model' => '8 Sirocco',       'platform_year' => 2017),
        'TA-1012'       => array('platform_model' => '8',               'platform_year' => 2017),
        'TA-1021'       => array('platform_model' => '6',               'platform_year' => 2017),
        'TA-1024'       => array('platform_model' => '5',               'platform_year' => 2017),
        'TA-1032'       => array('platform_model' => '3',               'platform_year' => 2017),
        'TA-1033'       => array('platform_model' => '6',               'platform_year' => 2017),
        'TA-1053'       => array('platform_model' => '5',               'platform_year' => 2017),

        'X2DS'          => array('platform_model' => 'X2 (Dual Sim)',   'platform_year' => 2014),
        '8 Sirocco'     => array('platform_model' => '8 Sirocco',       'platform_year' => 2017),
        '1'             => array('platform_model' => '1',               'platform_year' => 2018),
        '2.1'           => array('platform_model' => '2.1',             'platform_year' => 2018),
        '2.2'           => array('platform_model' => '2.2',             'platform_year' => 2019),
        '3.1'           => array('platform_model' => '3.1',             'platform_year' => 2018),
        '3.1 Plus'      => array('platform_model' => '3.1 Plus',        'platform_year' => 2018),
        '3.2'           => array('platform_model' => '3.2',             'platform_year' => 2018),
        '4.2'           => array('platform_model' => '4.2',             'platform_year' => 2019),
        '5.1 Plus'      => array('platform_model' => '5.1 Plus',        'platform_year' => 2018),
        '6.1'           => array('platform_model' => '6.1',             'platform_year' => 2018),
        '7 plus'        => array('platform_model' => '7 Plus',          'platform_year' => 2018),
        '7.1'           => array('platform_model' => '7.1',             'platform_year' => 2018),
        '7.2'           => array('platform_model' => '7.2',             'platform_year' => 2019),
        '8.1'           => array('platform_model' => '8.1',             'platform_year' => 2019),
        '9'             => array('platform_model' => '9 PureView',      'platform_year' => 2019),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Nokia',
        'platform_country'  => 'fi',
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
