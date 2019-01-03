<?php
/**
 * @brief Archos client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Archos.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.6
 * @date Creation: Apr 2018
 * @date Modification: Dec 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Archos client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_ArchosClientDevice($deviceCode='') {
    $deviceList = array(
        /* Archos tablets */
        '101b Copper'               => array('platform_model' => '101b Copper',             'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        '101c Copper'               => array('platform_model' => '101c Copper',             'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        '101 Oxygen'                => array('platform_model' => '101 Oxygen',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        '101b Oxygen'               => array('platform_model' => '101b Oxygen',             'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        '133 Oxygen'                => array('platform_model' => '133 Oxygen',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        '156 Oxygen'                => array('platform_model' => '156 Oxygen',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        '97c Platinum'              => array('platform_model' => '97c Platinium',           'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        '101c Platinum'             => array('platform_model' => '101c Platinum',           'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        '101 Platinium 3G'          => array('platform_model' => '101 Platinium 3G',        'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        '101 Helium Lite'           => array('platform_model' => '101 Helium Lite',         'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        '101b Helium'               => array('platform_model' => '101b Helium',             'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        '101c Helium'               => array('platform_model' => '101c Helium',             'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        '79b Neon'                  => array('platform_model' => '79b Neon',                'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2014),
        '101d Neon'                 => array('platform_model' => '101d Neon',               'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        '101e Neon'                 => array('platform_model' => '101e Neon',               'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),
        '101 Xenon Lite'            => array('platform_model' => '101 Xenon Lite',          'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        '101b Xenon'                => array('platform_model' => '101b Xenon',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        '101b Xenon v2'             => array('platform_model' => '101b Xenon',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2015),
        '101c Xenon'                => array('platform_model' => '101c Xenon',              'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2017),
        '70 Oxygen'                 => array('platform_model' => '70 Oxygen',               'platform_type' => 'tablet',   'platform_format' => 'tablet',   'platform_year' => 2016),

        /* Archos phones */
        'AC50CE'                    => array('platform_model' => '50 Cesium',               'platform_year' => 2015),
        '45BHE'                     => array('platform_model' => '45b Helium',              'platform_year' => 2015),
        '50BHE'                     => array('platform_model' => '50b Helium',              'platform_year' => 2015),

        '50 Oxygen'                 => array('platform_model' => '50 Oxygen',               'platform_year' => 2013),
        '50b Oxygen'                => array('platform_model' => '50b Oxygen',              'platform_year' => 2014),
        '50c Oxygen'                => array('platform_model' => '50c Oxygen',              'platform_year' => 2014),
        '50d Oxygen'                => array('platform_model' => '50d Oxygen',              'platform_year' => 2016),
        '50 Oxygen Plus'            => array('platform_model' => '50 Oxygen Plus',          'platform_year' => 2015),
        '40 Cesium'                 => array('platform_model' => '40 Cesium',               'platform_year' => 2014),
        '35b Titanium'              => array('platform_model' => '35b Titanium',            'platform_year' => 2014),
        '40c Titanium'              => array('platform_model' => '40c Titanium',            'platform_year' => 2014),
        '40d Titanium'              => array('platform_model' => '40d Titanium',            'platform_year' => 2015),
        '59 Titanium'               => array('platform_model' => '59 Titanium',             'platform_year' => 2014),
        '60 Platinum'               => array('platform_model' => '60 Platinum',             'platform_year' => 2017),
        '45c Platinum'              => array('platform_model' => '45c Platinum',            'platform_year' => 2014),
        '45d Platinum'              => array('platform_model' => '45d Platinum',            'platform_year' => 2016),
        '50 Platinum 4G'            => array('platform_model' => '50 Platinum 4G',          'platform_year' => 2016),
        '50b Platinium'             => array('platform_model' => '50b Platinum',            'platform_year' => 2014),
        '50b Titanium 4G'           => array('platform_model' => '50b Platinum 4G',         'platform_year' => 2016),
        '50c Platinum'              => array('platform_model' => '50c Platinum',            'platform_year' => 2015),
        '52 Platinum'               => array('platform_model' => '52 Platinum',             'platform_year' => 2015),
        '55 Platinum'               => array('platform_model' => '55 Platinum',             'platform_year' => 2015),
        '55b Platinum'              => array('platform_model' => '55b Platinum',            'platform_year' => 2016),
        '40 Helium'                 => array('platform_model' => '40 Helium',               'platform_year' => 2015),
        '45b Helium'                => array('platform_model' => '40b Helium',              'platform_year' => 2015),
        '50 Helium Plus'            => array('platform_model' => '50 Helium Plus',          'platform_year' => 2015),
        '50b Helium 4G'             => array('platform_model' => '50b Helium 4G',           'platform_year' => 2015),
        '50e Helium'                => array('platform_model' => '50e Helium',              'platform_year' => 2015),
        '50f Helium'                => array('platform_model' => '50f Helium',              'platform_year' => 2016),
        '55 Helium'                 => array('platform_model' => '55 Helium',               'platform_year' => 2016),
        '55 Helium Plus'            => array('platform_model' => '55 Helium Plus',          'platform_year' => 2015),
        '40 Neon'                   => array('platform_model' => '40 Neon',                 'platform_year' => 2016),
        '45 Neon'                   => array('platform_model' => '45 Neon',                 'platform_year' => 2014),
        '45b Neon'                  => array('platform_model' => '45b Neon',                'platform_year' => 2016),
        '50b Neon'                  => array('platform_model' => '50b Neon',                'platform_year' => 2014),
        '50c Neon'                  => array('platform_model' => '50c Neon',                'platform_year' => 2015),
        '50d Neon'                  => array('platform_model' => '50d Neon',                'platform_year' => 2016),
        '50e Neon'                  => array('platform_model' => '50e Neon',                'platform_year' => 2016),
        '50 Diamond'                => array('platform_model' => '50 Diamond',              'platform_year' => 2015),
        '55 Diamond Selfie'         => array('platform_model' => '55 Diamond Selfie',       'platform_year' => 2016),
        '55 Diamond Selfie Lite'    => array('platform_model' => '55 Diamond Selfie Lite',  'platform_year' => 2016),
        '50 Cobalt'                 => array('platform_model' => '50 Cobalt',               'platform_year' => 2015),
        '55 Cobalt Plus'            => array('platform_model' => '55 Cobalt Plus',          'platform_year' => 2016),
        '55B Cobalt'                => array('platform_model' => '55B Cobalt',              'platform_year' => 2017),
        '50 Saphir'                 => array('platform_model' => '50 Saphir',               'platform_year' => 2016),
        '59 Xenon'                  => array('platform_model' => '59 Xenon',                'platform_year' => 2015),
        '62 Xenon'                  => array('platform_model' => '62 Xenon',                'platform_year' => 2015),
        '64 Xenon'                  => array('platform_model' => '64 Xenon',                'platform_year' => 2014),

        'Diamond Plus'              => array('platform_model' => 'Diamond Plus',            'platform_year' => 2015),
        'Diamond S'                 => array('platform_model' => 'Diamond S',               'platform_year' => 2015),

        'Access 40 3G'              => array('platform_model' => 'Access 40 3G',            'platform_year' => 2017),
        'Access 45 3G'              => array('platform_model' => 'Access 45 3G',            'platform_year' => 2017),
        'Access 50 Color 3G'        => array('platform_model' => 'Access 50 Color 3G',      'platform_year' => 2017),
        'Access 50 4G'              => array('platform_model' => 'Access 50 4G',            'platform_year' => 2017),
        'Access 55 3G'              => array('platform_model' => 'Access 55 3G',            'platform_year' => 2017),
        'Sense 47 X'                => array('platform_model' => 'Sense 47X',               'platform_year' => 2017),
        'Sense 50 DC'               => array('platform_model' => 'Sense 50DC',              'platform_year' => 2017),
        'Sense 50 X'                => array('platform_model' => 'Sense 50X',               'platform_year' => 2017),
        'Sense 55 S'                => array('platform_model' => 'Sense 50S',               'platform_year' => 2017),
        'Sense 55 DC'               => array('platform_model' => 'Sense 55DC',              'platform_year' => 2017),
        'Core 50'                   => array('platform_model' => 'Core 50',                 'platform_year' => 2017),
        'Core 50 Lite'              => array('platform_model' => 'Core 50 Lite',            'platform_year' => 2017),
        'Core 50P'                  => array('platform_model' => 'Core 50P',                'platform_year' => 2017),
        'Core 55 4G'                => array('platform_model' => 'Core 55 4G',              'platform_year' => 2017),
        'Core 55P'                  => array('platform_model' => 'Core 55P',                'platform_year' => 2017),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Archos',
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
