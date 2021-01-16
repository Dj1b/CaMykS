<?php
/**
 * @brief Tecno client devices specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.27
 * @date Creation: Oct 2018
 * @date Modification: Jan 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Tecno client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_TecnoClientDevice($deviceCode='') {
    $deviceList = array(
        /* Tecno tablets */
        'P904'      => array('platform_model' => 'DroiPad 10D',     'platform_year' => 2016, 'platform_type' => 'tablet', 'platform_format' => 'tablet'),

        /* Tecno mobiles */
        'C9'        => array('platform_model' => 'C9',              'platform_year' => 2016),
        'J8'        => array('platform_model' => 'Boom',            'platform_year' => 2016),
        'W4'        => array('platform_model' => 'W4',              'platform_year' => 2016),
        'K7'        => array('platform_model' => 'Spark',           'platform_year' => 2017),
        'K9'        => array('platform_model' => 'Spark Plus',      'platform_year' => 2017),
        'L9 Plus'   => array('platform_model' => 'L9 Plus',         'platform_year' => 2017),
        'R6'        => array('platform_model' => 'R6',              'platform_year' => 2017),
        'W3'        => array('platform_model' => 'W3',              'platform_year' => 2017),
        'W2'        => array('platform_model' => 'W2',              'platform_year' => 2017),
        'CF7'       => array('platform_model' => 'Camon 11',        'platform_year' => 2018),
        'CF8'       => array('platform_model' => 'Camon 11 Pro',    'platform_year' => 2018),
        'KA7'       => array('platform_model' => 'Spark 2',         'platform_year' => 2018),
        'LA6'       => array('platform_model' => 'Pouvoir 1',       'platform_year' => 2018),
        'LA7'       => array('platform_model' => 'Pouvoir 2',       'platform_year' => 2018),
        'LA7 Pro'   => array('platform_model' => 'Pouvoir 2 Pro',   'platform_year' => 2018),
        'AX8'       => array('platform_model' => 'Phantom 8',       'platform_year' => 2018),
        'B1p'       => array('platform_model' => 'Pop 2 Power',     'platform_year' => 2018),
        'F1'        => array('platform_model' => 'F1',              'platform_year' => 2018),
        'F2'        => array('platform_model' => 'F2',              'platform_year' => 2018),
        'Camon CX'  => array('platform_model' => 'Camon CX',        'platform_year' => 2018),
        'CA7'       => array('platform_model' => 'Camon X',         'platform_year' => 2018),
        'KB7'       => array('platform_model' => 'Spark 3',         'platform_year' => 2019),
        'KB7j'      => array('platform_model' => 'Spark 3',         'platform_year' => 2019),
        'KB8'       => array('platform_model' => 'Spark 3 Pro',     'platform_year' => 2019),
        'AB7'       => array('platform_model' => 'Phantom 9',       'platform_year' => 2019),
        'KC6'       => array('platform_model' => 'Spark 4 Air',     'platform_year' => 2019),
        'KC8'       => array('platform_model' => 'Spark 4',         'platform_year' => 2019),
        'LB7'       => array('platform_model' => 'Pouvoir 3',       'platform_year' => 2019),
        'CC7'       => array('platform_model' => 'Camon 12',        'platform_year' => 2019),
        'CD8j'      => array('platform_model' => 'Camon 15',        'platform_year' => 2019),
        'BA2'       => array('platform_model' => 'Pop 2 Plus',      'platform_year' => 2019),
        'CD7'       => array('platform_model' => 'Camon 15',        'platform_year' => 2020),
        'KD6'       => array('platform_model' => 'Spark 5 Air',     'platform_year' => 2020),
        'KD7'       => array('platform_model' => 'Spark 5',         'platform_year' => 2020),
        'BC2'       => array('platform_model' => 'Pop 4',           'platform_year' => 2020),
        'LC7'       => array('platform_model' => 'Pouvoir 4',       'platform_year' => 2020),
        'LC8'       => array('platform_model' => 'Pouvoir 4 Pro',   'platform_year' => 2020),

        'Phantom6-Plus' => array('platform_model' => 'Phantom 6 Plus',  'platform_year' => 2016),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Tecno',
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
