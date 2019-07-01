<?php
/**
 * @brief Wiko client devices specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientDevices/Wiko.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: Jul 2018
 * @date Modification: Jun 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return Wiko client device information from a known list.
 * @param mixed $deviceCode
 * @return array
 */
function get_WikoClientDevice($deviceCode='') {
    $deviceList = array(
        'barry'             => array('platform_model' => 'Barry',           'platform_year' => 2014),
        'birdy'             => array('platform_model' => 'Birdy',           'platform_year' => 2014),
        'bloom'             => array('platform_model' => 'Bloom',           'platform_year' => 2014),
        'bloom2'            => array('platform_model' => 'Bloom 2',         'platform_year' => 2015),
        's8030(2g)'         => array('platform_model' => 'Cink',            'platform_year' => 2012),
        'cink king'         => array('platform_model' => 'Cink King',       'platform_year' => 2012),
        'cink five'         => array('platform_model' => 'Cink Five',       'platform_year' => 2013),
        'cink peax'         => array('platform_model' => 'Cink Peax',       'platform_year' => 2013),
        'cink_peax_2'       => array('platform_model' => 'Cink Peax 2',     'platform_year' => 2013),
        'darkfull'          => array('platform_model' => 'Darkfull',        'platform_year' => 2013),
        's9203'             => array('platform_model' => 'Darknight',       'platform_year' => 2014),
        'darkmoon'          => array('platform_model' => 'Darkmoon',        'platform_year' => 2013),
        'darkside'          => array('platform_model' => 'Darkside',        'platform_year' => 2013),
        'fever'             => array('platform_model' => 'Fever',           'platform_year' => 2015),
        'fizz'              => array('platform_model' => 'Fizz',            'platform_year' => 2014),
        'freddy'            => array('platform_model' => 'Freddy',          'platform_year' => 2016),
        'v3903'             => array('platform_model' => 'Freddy 4G',       'platform_year' => 2016),
        'getaway'           => array('platform_model' => 'Getaway',         'platform_year' => 2014),
        'goa'               => array('platform_model' => 'Goa',             'platform_year' => 2014),
        'harry'             => array('platform_model' => 'Harry',           'platform_year' => 2017),
        'highway 4g'        => array('platform_model' => 'Highway 4G',      'platform_year' => 2014),
        'highway pure'      => array('platform_model' => 'Highway Pure',    'platform_year' => 2015),
        'highway signs'     => array('platform_model' => 'Highway Signs',   'platform_year' => 2014),
        'highway star'      => array('platform_model' => 'Highway Star',    'platform_year' => 2015),
        'star4g'            => array('platform_model' => 'Highway Star 4G', 'platform_year' => 2015),
        'star 4g'           => array('platform_model' => 'Highway Star 4G', 'platform_year' => 2015),
        'iggy'              => array('platform_model' => 'Iggy',            'platform_year' => 2013),
        'jerry'             => array('platform_model' => 'Jerry',           'platform_year' => 2016),
        'jerry2'            => array('platform_model' => 'Jerry 2',         'platform_year' => 2017),
        'jerry max'         => array('platform_model' => 'Jerry Max',       'platform_year' => 2017),
        'v2800an'           => array('platform_model' => 'K Kool',          'platform_year' => 2016),
        'jimmy'             => array('platform_model' => 'Jimmy',           'platform_year' => 2014),
        'kenny'             => array('platform_model' => 'Kenny',           'platform_year' => 2017),
        'kite'              => array('platform_model' => 'Kite',            'platform_year' => 2014),
        'lenny'             => array('platform_model' => 'Lenny',           'platform_year' => 2014),
        'lenny2'            => array('platform_model' => 'Lenny 2',         'platform_year' => 2015),
        'lenny3'            => array('platform_model' => 'Lenny 3',         'platform_year' => 2016),
        'lenny3 max'        => array('platform_model' => 'Lenny 3 Max',     'platform_year' => 2016),
        'lenny4'            => array('platform_model' => 'Lenny 4',         'platform_year' => 2017),
        'lenny4 plus'       => array('platform_model' => 'Lenny 4 Plus',    'platform_year' => 2017),
        'ozzy'              => array('platform_model' => 'Ozzy',            'platform_year' => 2013),
        'pulp'              => array('platform_model' => 'Pulp',            'platform_year' => 2015),
        'pulp 4g'           => array('platform_model' => 'Pulp 4G',         'platform_year' => 2015),
        'pulp fab'          => array('platform_model' => 'Pulp Fab',        'platform_year' => 2015),
        'pulp fab 4g'       => array('platform_model' => 'Pulp Fab 4G',     'platform_year' => 2015),
        'rainbow'           => array('platform_model' => 'Rainbow',         'platform_year' => 2014),
        'rainbow 4g'        => array('platform_model' => 'Rainbow 4G',      'platform_year' => 2014),
        'rainbow dual'      => array('platform_model' => 'Rainbow Dual',    'platform_year' => 2014),
        'rainbow jam'       => array('platform_model' => 'Rainbow Jam',     'platform_year' => 2015),
        'rainbow jam 4g'    => array('platform_model' => 'Rainbow Jam 4G',  'platform_year' => 2015),
        'rainbow lite'      => array('platform_model' => 'Rainbow Lite',    'platform_year' => 2015),
        'rainbow lite 4g'   => array('platform_model' => 'Rainbow Lite 4G', 'platform_year' => 2015),
        'rainbow up'        => array('platform_model' => 'Rainbow Up',      'platform_year' => 2015),
        'rainbow up 4g'     => array('platform_model' => 'Rainbow Up 4G',   'platform_year' => 2015),
        'ridge'             => array('platform_model' => 'Ridge',           'platform_year' => 2015),
        'ridge 4g'          => array('platform_model' => 'Ridge 4G',        'platform_year' => 2015),
        'ridge 4g-fever'    => array('platform_model' => 'Ridge 4G Fever',  'platform_year' => 2015),
        'ridge fab 4g'      => array('platform_model' => 'Ridge Fab 4G',    'platform_year' => 2015),
        'robby'             => array('platform_model' => 'Robby',           'platform_year' => 2016),
        'robby2'            => array('platform_model' => 'Robby2',          'platform_year' => 2017),
        'selfy 4g'          => array('platform_model' => 'Selfie 4G',       'platform_year' => 2015),
        'selfy 4g'          => array('platform_model' => 'Selfie 4G',       'platform_year' => 2015),
        'slide'             => array('platform_model' => 'Slide',           'platform_year' => 2014),
        'slide2'            => array('platform_model' => 'Slide 2',         'platform_year' => 2015),
        'stairway'          => array('platform_model' => 'Stairway',        'platform_year' => 2013),
        'sublim'            => array('platform_model' => 'Sublim',          'platform_year' => 2013),
        'sunny'             => array('platform_model' => 'Sunny',           'platform_year' => 2016),
        'sunny max'         => array('platform_model' => 'Sunny Max',       'platform_year' => 2016),
        'sunny2'            => array('platform_model' => 'Sunny 2',         'platform_year' => 2017),
        'sunny2 plus'       => array('platform_model' => 'Sunny 2 Plus',    'platform_year' => 2017),
        'sunset'            => array('platform_model' => 'Sunset',          'platform_year' => 2014),
        'sunset2'           => array('platform_model' => 'Sunset 2',        'platform_year' => 2015),
        'tommy'             => array('platform_model' => 'Tommy',           'platform_year' => 2016),
        'tommy2'            => array('platform_model' => 'Tommy 2',         'platform_year' => 2017),
        'tommy2 plus'       => array('platform_model' => 'Tommy 2 Plus',    'platform_year' => 2017),
        'tommy3'            => array('platform_model' => 'Tommy 3',         'platform_year' => 2018),
        'u feel'            => array('platform_model' => 'U Feel',          'platform_year' => 2016),
        'u feel 4g'         => array('platform_model' => 'U Feel 4g',       'platform_year' => 2016),
        'u feel fab'        => array('platform_model' => 'U Feel Fab',      'platform_year' => 2016),
        'u feel go'         => array('platform_model' => 'U Feel Go',       'platform_year' => 2016),
        'u feel prime'      => array('platform_model' => 'U Feel Prime',    'platform_year' => 2016),
        'u feel lite'       => array('platform_model' => 'U Feel Lite',     'platform_year' => 2016),
        'u pulse'           => array('platform_model' => 'U Pulse',         'platform_year' => 2017),
        'u pulse lite'      => array('platform_model' => 'U Pulse Lite',    'platform_year' => 2017),
        'view'              => array('platform_model' => 'View',            'platform_year' => 2017),
        'view prime'        => array('platform_model' => 'View Prime',      'platform_year' => 2017),
        'view xl'           => array('platform_model' => 'View XL',         'platform_year' => 2017),
        'violet'            => array('platform_model' => 'Violet',          'platform_year' => 2017),
        'wax'               => array('platform_model' => 'Wax',             'platform_year' => 2014),
        'wim'               => array('platform_model' => 'Wim',             'platform_year' => 2017),
        'wim lite'          => array('platform_model' => 'Wim Lite',        'platform_year' => 2017),

        'w_k300'            => array('platform_model' => 'Jerry 3',         'platform_year' => 2018),
        'w_k600'            => array('platform_model' => 'Tommy 3',         'platform_year' => 2018),
        'w_c800'            => array('platform_model' => 'View 2',          'platform_year' => 2018),
        'w_c800s'           => array('platform_model' => 'View 2',          'platform_year' => 2018),
        'w-v600'            => array('platform_model' => 'Harry 2',         'platform_year' => 2018),
    );

    /* Check for returning list */
    if ($deviceCode === false)
      return $deviceList;

    /* Initialise result. */
    $result = array(
        'platform_company'  => 'Wiko',
        'platform_country'  => 'fr',
        'platform_model'    => ucwords($deviceCode),
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
