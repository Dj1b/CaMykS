<?php
/**
 * @brief Client specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/client.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.15
 * @date Creation: Jun 2007
 * @date Modification: May 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Return client IP address.
 * @return string
 */
function client_getIp() {
    return (isset($_SERVER['HTTP_PC_REMOTE_ADDR'])?$_SERVER['HTTP_PC_REMOTE_ADDR']:$_SERVER['REMOTE_ADDR']);
}

/**
 * Return client user agent.
 * @return string
 */
function client_getUserAgent() {
    return (isset($_SERVER['HTTP_USER_AGENT'])?$_SERVER['HTTP_USER_AGENT']:'');
}

/**
 * Check if page is loaded in HTTPS(SSL).
 * @return boolean result
 */
function client_isHTTPS() {
    return (!empty($_SERVER['HTTPS']));
}

/**
 * Return client referer site.
 * @return string
 */
function client_getRefererSite() {
    return (isset($_SERVER['HTTP_REFERER'])?$_SERVER['HTTP_REFERER']:'');
}

/**
 * Check if the server is also the client.
 * @return boolean result
 */
function client_isServerClient() {
    return ($_SERVER['SERVER_ADDR'] == client_getIp());
}

/**
 * Check if client is marked as Do Not Track.
 * @return boolean result
 */
function client_getDoNotTrack() {
    return (isset($_SERVER['HTTP_DNT']) and $_SERVER['HTTP_DNT'] == 1);
}

/**
 * Return client informations.
 * @param mixte $ua
 * @return array
 */
function client_getUAInfos($ua=false) {
    $req = true;
    
    /* get user agent */
    if ($ua===false) $ua = client_getUserAgent();
    
    /* init result value */
    $infos = array();
    
    /*** check fake visitors */
    if (($c = client_getFakeInfosFromUserAgent($ua)) !== false)
        return $c;
    
    /*** check hacks */
    if (($c = client_getHackInfosFromUserAgent($ua)) !== false)
        return $c;
    
    /*** check tool */
    if (($c = client_getToolInfosFromUserAgent($ua)) !== false)
        return $c;
    
    /*** check bot */
    if (($c = client_getBotInfosFromUserAgent($ua)) !== false)
        return $c;
    
    /*** check generic bot/tool */
    if (($c = client_getGenericInfosFromUserAgent($ua)) !== false)
        return $c;
    
    /*** check plateform ***/
    
    /* load max versions to check and default fake value */
    $maxVersions = _client_getUAPropertiesMaxVersions();
    $fake = array('platform_type'     => 'fake');
    
    /* check Playstation 4 / Vita */
    if (preg_match('/\(PlayStation ([^ ]*) ([0-9\.]*)\)/i', $ua, $matches))
        return _client_mergeUAInfos($req, array(
            'platform_company'  => 'Sony',
            'platform_model'    => 'Playstation '.$matches[1],
            'platform_type'     => 'computer',
            'platform_format'   => 'desktop',
            'system_title'      => 'Playstation '.$matches[1],
            'system_version'    => $matches[2],
            'browser_title'     => 'PS '.$matches[1].' Browser',
            'browser_version'   => '--',
        ));
    
    /* check Playstation 3 */
    if (preg_match('/\(PLAYSTATION 3; ([0-9\.]*)\)$/', $ua, $matches))
        return _client_mergeUAInfos($req, array(
            'platform_company'  => 'Sony',
            'platform_model'    => 'Playstation 3',
            'platform_type'     => 'computer',
            'platform_format'   => 'desktop',
            'system_title'      => 'Playstation 3',
            'system_version'    => $matches[1],
            'browser_title'     => 'PS3 Browser',
            'browser_version'   => '--',
        ));
    
    /* check Playstation Portable */
    if (preg_match('/PSP \(PlayStation Portable\); ([0-9\.]*)\)?$/', $ua, $matches))
        return _client_mergeUAInfos($req, array(
            'platform_company'  => 'Sony',
            'platform_model'    => 'Playstation Portable',
            'platform_type'     => 'computer',
            'platform_format'   => 'handheld',
            'system_title'      => 'Playstation Portable',
            'system_version'    => $matches[1],
            'browser_title'     => 'PSP Browser',
            'browser_version'   => '--',
        ));
    
    /* check Black Berry */
    if (preg_match('/BlackBerry([^\/;]{1,})\/([0-9\.]*)/', $ua, $matches))
        return _client_mergeUAInfos($req, array(
            'platform_company'  => 'BlackBerry',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            'system_title'      => 'BlackBerry OS',
            'system_version'    => $matches[2],
            'browser_title'     => 'BB Browser',
            'browser_version'   => '--',
        ));
    if (preg_match('/BlackBerry ([^;]{1,});?.*Version\/([0-9\.]*) /', $ua, $matches))
        return _client_mergeUAInfos($req, array(
            'platform_company'  => 'BlackBerry',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            'system_title'      => 'BlackBerry OS',
            'system_version'    => $matches[2],
            'browser_title'     => 'BB Browser',
            'browser_version'   => '--',
        ));
    if (preg_match('/BB([^\/;]{1,});/', $ua, $matches))
        return _client_mergeUAInfos($req, array(
            'platform_company'  => 'BlackBerry',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            'system_title'      => 'BlackBerry OS',
            'system_version'    => $matches[1],
            'browser_title'     => 'BB Browser',
            'browser_version'   => '--',
        ));

    /* check Nokia - before iPhone */
    elseif (preg_match('/RX-51 N900/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Nokia',
            'platform_model'    => 'N900',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            'system_title'      => 'Maemo',
            'system_version'    => 5,
        ));
    elseif (preg_match('/Nokia(?: |_|\-|\/|)([^ _\-\/]+)/', $ua, $matches)) {
        $rep = array(
            'X2DS'  => array('platform_model' => 'X2 (Dual Sim)'),
        );

        $infos = array_merge($infos, array(
            'platform_company'  => 'Nokia',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$matches[1]])?$rep[$matches[1]]:array()
        );
    }
    elseif (preg_match('/Lumia ([a-zA-Z0-9]*)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Nokia',
            'platform_model'    => 'Lumia '.$matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    
    /* check iphone / ipod / ipad */
    elseif (preg_match('/(iPod|iPhone|iPad);?.*; CPU ([A-Za-z\ ]*)? ([0-9_]*)?.*(Version)\/([0-9\.]*)/', $ua, $matches)) {
        /* check version */
        $version = str_replace('_', '.', $matches[3]);
        if (version_compare($version, $maxVersions['system']['iOS']) > 0)
            return $fake;
        
        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => $matches[1],
            'platform_type'     => $matches[1]=='iPad'? 'tablet': 'handheld',
            'platform_format'   => $matches[1]=='iPad'? 'tablet': 'handheld',
            'system_title'      => 'iOS',
            'system_version'    => $version,
            'browser_title'     => 'Safari Mobile',
            'browser_version'   => $matches[5],
        ));
    } elseif (preg_match('/(iPod|iPhone|iPad);?.*; CPU ([A-Za-z\ ]*)? ([0-9_]*)/', $ua, $matches)) {
        /* check version */
        $version = str_replace('_', '.', $matches[3]);
        if (version_compare($version, $maxVersions['system']['iOS']) > 0)
            return $fake;

        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => $matches[1],
            'platform_type'     => $matches[1]=='iPad'? 'tablet': 'handheld',
            'platform_format'   => $matches[1]=='iPad'? 'tablet': 'handheld',
            'system_title'      => 'iOS',
            'system_version'    => $version,
        ));
    } elseif (preg_match('/(iPod|iPhone|iPad)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => $matches[1],
            'platform_type'     => $matches[1]=='iPad'? 'tablet': 'handheld',
            'platform_format'   => $matches[1]=='iPad'? 'tablet': 'handheld',
            'system_title'      => 'iOS',
        ));
    
    /* check Google */
    elseif (preg_match('/(Nexus( [^ \/;]+)?|Pixel) Build/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Google',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check HTC */
    elseif (preg_match('/HTC;([A-Za-z0-9 ]*)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'HTC',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',));
    elseif (preg_match('/HTC[ |_]([^\/\-]*)( Build|\-)/', $ua, $matches)) {
        $rep = array(
            'M8Sx'          => array('platform_model' => 'One', ),
            'IncredibleS'   => array('platform_model' => 'Incredible S'),
            'D820u'         => array('platform_model' => 'Desire 820 Dual SIM'),
            '8088;'         => array('platform_model' => 'One Max',     'platform_year' => 2013),
        );
        $model = preg_replace('/_/', ' ', $matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'HTC',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$matches[1]])?$rep[$matches[1]]:array()
        );
    } elseif (preg_match('/HTC([A-Za-z0-9]+)/', $ua, $matches)) {
        $rep = array(
            'T329t'         => array('platform_model' => 'Proto', 'browser_title' => 'Android browser',),
        );
        $model = preg_replace('/_/', ' ', $matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'HTC',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$matches[1]])?$rep[$matches[1]]:array()
        );
    } elseif (preg_match('/2PYB2/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'HTC',
            'platform_model'    => 'Bolt',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',));

    /* check LG */
    elseif (preg_match('/^LG(?:E|)(?: |_|\-|\/)([^ _\-\/]+)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'LG',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    elseif (preg_match('/LG-([A-Z][0-9]{3}[A-Z]?)/', $ua, $matches) or preg_match('/LG([A-Z]{1,2}[0-9]*)/', $ua, $matches)) {
        include_once ('clientDevices/LG.php.inc');
        $infos = array_merge($infos, get_LGClientDevice($matches[1]));
    }

    /* check Motorola */
    elseif (preg_match('/mot(?:-|orola |o|\-moto)([^ \/;]+)/i', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  =>'Motorola',
            'platform_model'    =>$matches[1],
            'platform_type'     =>'handheld',
            'platform_format'   =>'handheld',
        ));
    elseif (preg_match('/ (Droid|MB200|RAZR HD|Moto G)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Motorola',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    elseif (preg_match('/XT([0-9]{3,})/', $ua, $matches)) {
        include_once ('clientDevices/Motorola.php.inc');
        $infos = array_merge($infos, get_MotorolaClientDevice($matches[0]));
    }

    /* check palm */
    elseif (preg_match('/(Pre|Pixi)\/[0-9\.]*$/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Palm',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check samsung devices */
    elseif (preg_match('/(GT|SM|SGH|SHV)-([A-Z0-9]{4,})/', $ua, $matches)) {
        include_once ('clientDevices/Samsung.php.inc');
        $infos = array_merge($infos, get_SamsungClientDevice($matches[0]));

    } elseif (preg_match('/SAMSUNG\-(?:SGH\-|)([^\/]+)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Samsung',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    elseif (preg_match('/(Galaxy|E[0-9]) Build/', $ua, $matches)) {
        include_once ('clientDevices/Samsung.php.inc');
        $infos = array_merge($infos, get_SamsungClientDevice($matches[1]));
    } elseif (preg_match('/(klte)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Samsung',
            'platform_model'    => 'Galaxy S5',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Samsung PC */
    elseif (preg_match('/MASMJS|SMJB/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Samsung (PC)'
        ));

    /* check OnePlus - to be inserted before Sony */
    elseif (preg_match('/( ONE| ONEPLUS)? (A|E)([0-9]{4}) Build/i', $ua, $matches)) {
        include_once ('clientDevices/OnePlus.php.inc');
        $infos = array_merge($infos, get_OnePlusClientDevice($matches[2].$matches[3]));
    }

    /* check SonyEricsson */
    elseif (preg_match('/SonyEricsson([^ \/]+)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'SonyEricsson',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    
    /* check Sony mobiles and tablets */
    elseif (preg_match('/ ([C-H])([0-9]{4}) Build/', $ua, $matches)) {
        include_once ('clientDevices/Sony.php.inc');
        $infos = array_merge($infos, get_SonyClientDevice($matches[1].$matches[2]));
    }
    elseif (preg_match('/SOV3[0-9]/', $ua, $matches)) {
        include_once ('clientDevices/Sony.php.inc');
        $infos = array_merge($infos, get_SonyClientDevice($matches[0]));
    }
    
    /* check Sony PCs */
    elseif (preg_match('/MASE|MASEJS|MASP|MASPJS|MASA|MASAJS/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  =>'Sony (PC)',
        ));

    /* check Huawei */
    elseif (preg_match('/Build\/(HONOR|HUAWEI)([A-Z0-9\-]{7,})/i', $ua, $matches)) {
        include_once ('clientDevices/Huawei.php.inc');
        $infos = array_merge($infos, get_HuaweiClientDevice(trim($matches[2])));
    }
    elseif (preg_match('/(SCL\-L01) Build/', $ua, $matches)) {
        include_once ('clientDevices/Huawei.php.inc');
        $infos = array_merge($infos, get_HuaweiClientDevice(trim($matches[1])));
    }

    /* check Spice Mobility */
    elseif (preg_match('/Spice ([A-Z0-9\-]{5,})/i', $ua, $matches)) {
        $rep = array(
            'Mi-349'   => array('platform_model' => 'Smart Flo Edge'),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Spice Mobility',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Archos */
    elseif (preg_match('/(AC|Archos )([A-Za-z0-9\- ]{3,}) Build/', $ua, $matches)) {
        include_once ('clientDevices/Archos.php.inc');
        $infos = array_merge($infos, get_ArchosClientDevice(trim($matches[2])));
    } elseif (preg_match('/A40Ti/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Archos',
            'platform_model'    => 'A40Ti',
        ));

    /* check Lenovo */
    elseif (preg_match('/(IdeaTab|Lenovo)[ |_]([A-Z0-9\-]{3,})/i', $ua, $matches)) {
        include_once ('clientDevices/Lenovo.php.inc');
        $infos = array_merge($infos, get_LenovoClientDevice(trim($matches[2])));
    }

    /* check Lenovo PCs */
    elseif (preg_match('/MALC|MALCJS|MALN|MALNJS|LCJB|LEN2/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  =>'Lenovo (PC)',
        ));

    /* check Outikel mobiles */
    elseif (preg_match('/(K6000 Pro) Build/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Oukitel',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Asus mobiles and tablets */
    elseif (preg_match('/(K|ME|P)([0-9]{2})([A-Z0-9]{1,2}) Build/', $ua, $matches)) {
        include_once ('clientDevices/Asus.php.inc');
        $infos = array_merge($infos, get_AsusClientDevice(trim($matches[1].$matches[2].$matches[3])));
    } elseif (preg_match('/ASUS_([A-Z0-9]+) Build/', $ua, $matches)) {
        include_once ('clientDevices/Asus.php.inc');
        $infos = array_merge($infos, get_AsusClientDevice(trim($matches[1])));
    }

    /* check Asus PCs */
    elseif (preg_match('/MAAU|ASJB|ASU2JS|ASU2|NP0[6789]/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Asus (PC)',
        ));

    /* check Micromax */
    elseif (preg_match('/Micromax( |_)([^ \/\)]+)/', $ua, $matches)) {
        include_once ('clientDevices/Micromax.php.inc');
        $infos = array_merge($infos, get_MicromaxClientDevice($matches[2]));
    }

    /* check ITel */
    elseif (preg_match('/itel it([^ \/;]+( Plus)?)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'ITel',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Nintendo */
    elseif (preg_match('/Nintendo ([^ \/;\)]+)/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Nintendo',
            'platform_model'    => $matches[1],
            'platform_format'   => preg_match('/DS/', $matches[1])?'handheld':'desktop',
            'platform_type'     => preg_match('/DS/', $matches[1])?'handheld':'computer',
        ));
    }
    
    /* check Xbox / XBox One */
    elseif (preg_match('/Xbox(; Xbox [a-zA-Z0-9]*)?/i', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Microsoft',
            'platform_model'    => isset($matches[1])?substr($matches[1], 2):'Xbox 360',
            'platform_type'     => 'computer',
            'platform_format'   => 'desktop',
        ));

    /* check Amazon Kindle */
    elseif (preg_match('/Kindle([0-9\.]*)/', $ua, $matches))
        /* build info */
        $infos = array_merge($infos, array(
            'platform_company'  => 'Amazon',
            'platform_model'    => 'Kindle',
            'platform_type'     => 'tablet',
            'platform_format'   => 'tablet',
            'browser_title'     => 'Kindle browser',
            'browser_version'   => $matches[1],
        ));
    elseif (preg_match('/KFFOWI/', $ua, $matches))
        /* build info */
        $infos = array_merge($infos, array(
            'platform_company'  => 'Amazon',
            'platform_model'    => 'Kindle Fire (5th Gen)',
            'platform_type'     => 'tablet',
            'platform_format'   => 'tablet',
            'platform_year'     => 2015,
        ));
        
    /* check Macintosh */
    elseif (preg_match('/(?:Intel |PPC |)Mac OS X( Mach-O| [0-9\._]*|)/i', $ua, $matches)) {
        /* check version */
        $version = ($matches[1]!=' Mach-O')?substr(str_replace('_','.',$matches[1]), 1):'';
        if (version_compare($version, $maxVersions['system']['Mac OS X']) > 0)
         return $fake;

        /* build info */
        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => 'Macintosh',
            'platform_type'     => 'computer',
            'platform_format'   => 'desktop',
            'system_title'      => version_compare ($version, '10.12') >= 0 ? 'macOS' : 'Mac OS X',
            'system_version'    => $version
        ));
    }

    /* check Classic Macintosh */
    elseif (preg_match('/Mac_PowerPC|Macintosh/i', $ua, $matches)) {
        /* build info */
        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => 'Macintosh',
            'platform_type'     => 'computer',
            'platform_format'   => 'desktop',
            'system_title'      => 'Mac OS Classic',
            'system_version'    => '',
        ));
    }

    /* check Wiko */
    elseif (preg_match('/(DARKSIDE|LENNY|RIDGE 4G|U FEEL LITE|FEVER|JERRY|TOMMY|RAINBOW|SUNSET|PULP 4G)([0-9]*)?/i', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Wiko',
            'platform_model'    => ucwords(strtolower($matches[1])).(isset($matches[2])?' '.$matches[2]:''),
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check SpreadTrum */
    elseif (preg_match('/SpreadTrum/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'SpreadTrum',
            'platform_model'    => '',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Maximus MAX908 */
    elseif (preg_match('/MAX908/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Maximus',
            'platform_model'    => 'MAX908',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Alcatel */
    elseif (preg_match('/ ([0-9]{4}[A-Z]) Build/', $ua, $matches)) {
        include_once ('clientDevices/Alcatel.php.inc');
        $infos = array_merge($infos, get_AlcatelClientDevice($matches[1]));
    } elseif (preg_match('/Orange KLIF/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Alcatel',
            'platform_model'    => 'Orange KLIF',
            'system_title'      => 'Firefox OS',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check Lava Iris models */
    elseif (preg_match('/Iris([A-Z0-9]+)/i', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Lava',
            'platform_model'    => 'Iris '.$matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Tecno mobiles */
    elseif (preg_match('/Tecno ?([^;| ]*) Build/i', $ua, $matches)) {
        $rep = array(
            'K7'  => array('platform_model' => 'Spark (K7)'),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Tecno',
            'platform_model'    => isset($matches[1])?$matches[1]:'',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Yezz Andy models */
    elseif (preg_match('/Andy[_ ]([A-Z0-9]{2,})/i', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Yezz',
            'platform_model'    => 'Andy '.$matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check accent mobiles */
    elseif (preg_match('/Accent ?([^;| ]*)/i', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'=>'Accent',
            'platform_model'=>isset($matches[1])?ucwords(strtolower($matches[1])):'',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Memup SlidePad 704CE */
    elseif (preg_match('/SP704CE/i', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Memup',
            'platform_model'    => 'SP704CE',
            'platform_type'     => 'tablet',
            'platform_format'   => 'tablet',
        ));

    /* check Wing mobiles */
    elseif (preg_match('/Wing_([A-Za-z0-9]{2,})/i', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Wing',
            'platform_model'    => isset($matches[1])?ucwords(strtolower($matches[1])):'',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Leagoo mobiles */
    elseif (preg_match('/ Elite 2 Build/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Leagoo',
            'platform_model'    => 'Elite 2',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Wortmann TERRA PAD 1003 mobiles */
    elseif (preg_match('/TERRA PAD 1003/', $ua, $matches))
        $infos = array_merge($infos, array(
        'platform_company'  => 'Wortmann',
        'platform_model'    => 'Terra Pad 1003',
        'platform_type'     => 'tablet',
        'platform_format'   => 'tablet',
    ));

    /* check QMobile */
    elseif (preg_match('/A3 Build|LT700/', $ua, $matches)) {
        $rep = array(
            'A3 Build'  => array('platform_model' => 'A3'),
            'LT700'     => array('platform_model' => 'LT700'),
        );
        $model = trim($matches[0]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'QMobile',
            'platform_model'    => 'A3',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Haier mobiles */
    elseif (preg_match('/(CDP7TAB4C8|G30)/', $ua, $matches)) {
        $rep = array(
            'CDP7TAB4C8'    => array('platform_model' => 'CDisplay E701', 'platform_type'     => 'tablet', 'platform_format'   => 'tablet'),
            'G30'           => array('platform_model' => 'Voyage G30',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Haier',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Bloom */
    elseif (preg_match('/BLOOM Build/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Bloom',
            'platform_model'    => '',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Carrefour */
    elseif (preg_match('/CMB([0-9]{3})/', $ua, $matches)) {
        $rep = array(
            '510'=> array('platform_model' => 'Smart 5'),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Carrefour',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Orange */
    elseif (preg_match('/Nura 2/', $ua, $matches)) {
        $rep = array(
            '510'=> array('platform_model' => 'Smart 5'),
        );
        $model = trim($matches[0]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Orange',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    } elseif (preg_match('/Orange ([^.]*) Build/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Orange',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check Logicom */
    elseif (preg_match('/L-EMENT_?([0-9]{3})/', $ua, $matches)) {
        include_once ('clientDevices/Logicom.php.inc');
        $infos = array_merge($infos, get_LogicomClientDevice($matches[1]));
    }

    /* check Coolpad devices */
    elseif (preg_match('/(CP|Coolpad )([A-Z0-9_\-]+) Build/', $ua, $matches)) {
        include_once ('clientDevices/Coolpad.php.inc');
        $infos = array_merge($infos, get_CoolpadClientDevice($matches[2]));
    }

    /* check Vestel devices */
    elseif (preg_match('/(Venus_V3_5570)/', $ua, $matches)) {
        $rep = array(
            'Venus_V3_5570'=> array('platform_model' => 'Ven&uuml;s V3 5570',),
        );
        $infos = array_merge($infos, array(
            'platform_company'  => 'Vestel',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$matches[1]])?$rep[$matches[1]]:array()
        );
    }

    /* check Hewlett Packard OEM computers */
    elseif (preg_match('/HPCMHP|HPNTDF|HPNTDFJS|HPDTDF|HPDTDFJS/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Hewlett Packard (PC)',
        ));
    }

    /* check Dell OEM computers */
    elseif (preg_match('/MDDR|MDDRJS|MDDC|MDDCJS|MDDS|MDDSJS/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Dell (PC)',
        ));
    }

    /* check Toshiba OEM computers */
    elseif (preg_match('/MATM|MATMJS|MATB|MATBJS|MATP|MATPJS|TNJB|TAJB/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Toshiba (PC)',
        ));
    }

    /* check Acer mobiles */
    elseif (preg_match('/ (Z130|T03|T04) Build/', $ua, $matches)) {
        include_once ('clientDevices/Acer.php.inc');
        $infos = array_merge($infos, get_AcerClientDevice($matches[1]));
    }

    /* check Acer OEM computers */
    elseif (preg_match('/MAAR|MAARJS/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  =>'Acer (PC)',
        ));
    }

    /* check Medion OEM computers */
    elseif (preg_match('/MAMD/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  =>'Medion (PC)',
        ));
    }

    /* check MSI OEM computers */
    elseif (preg_match('/MAMI|MAMIJS|MAM3/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Medion (PC)',
        ));
    }

    /* check Gateway OEM computers */
    elseif (preg_match('/MAGW|MAGWJS/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  =>'Gateway (PC)',
        ));
    }

    /* check Fujitsu OEM computers */
    elseif (preg_match('/MAFS|MAFSJS/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  =>'Fujitsu (PC)',
        ));
    }

    /* check Compaq OEM computers */
    elseif (preg_match('/CPDTDF|CPNTDF|CMNTDF|CMNTDFJS/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  =>'Compaq (PC)',
        ));
    }

    /* check Polaroid tablets, to be inserted before Xiaomi */
    elseif (preg_match('/MID4X10/', $ua, $matches)) {
        $rep = array();
        $infos = array_merge($infos, array(
            'platform_company'  => 'Polaroid',
            'platform_model'    => $matches[0],
            'platform_type'     => 'tablet',
            'platform_format'   => 'tablet',
            ),
            isset($rep[$matches[0]])?$rep[$matches[0]]:array()
        );
    }

    /* check Xiaomi mobiles */
    elseif (preg_match('/(Redmi|MI) ?([A-Za-z0-9 ]{1,}) Build/i', $ua, $matches)) {
        include_once ('clientDevices/Xiaomi.php.inc');
        $infos = array_merge($infos, get_XiaomiClientDevice($matches[1].' '.$matches[2]));
    } elseif (preg_match('/HM NOTE 1LTE/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Xiaomi',
            'platform_model'    => 'Redmi Note 3',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Iris Sat mobiles */
    elseif (preg_match('/(I-S[0-9])/', $ua, $matches)) {
        $rep = array();
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Iris Sat',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }
    elseif (preg_match('/(VOX POP plus)/', $ua, $matches)) {
        $rep = array(
            'VOX POP plus' => array('platform_model' => 'Vox Pop Plus',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Iris Sat',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Umi mobiles */
    elseif (preg_match('/(IRON Pro)/', $ua, $matches)) {
        $rep = array(
            'IRON Pro' => array('platform_model' => 'IRON Pro',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Umi',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Kazam mobiles */
    elseif (preg_match('/KAZAM_(Trooper_450L)/', $ua, $matches)) {
        $rep = array(
            'Trooper_450L' => array('platform_model' => 'Trooper 450L',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Kazam',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Condor mobiles */
    elseif (preg_match('/P(GN|HQ)([0-9]{3}) Build/', $ua, $matches)) {
        include_once ('clientDevices/Condor.php.inc');
        $infos = array_merge($infos, get_CondorClientDevice('P'.$matches[1].$matches[2]));
    }

    /* check Smartisan mobiles */
    elseif (preg_match('/(SM[0-9]{3})/', $ua, $matches)) {
        $rep = array(
            'SM801' => array('platform_model' => 'T2',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Smartisan',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Gigabyte mobiles */
    elseif (preg_match('/(GSmart Rey R3)/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Gigabyte',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check Lyf mobiles */
    elseif (preg_match('/(LYF\/F[0-9]{2}[A-Z])\//', $ua, $matches)) {
        include_once ('clientDevices/Lyf.php.inc');
        $infos = array_merge($infos, get_LyfClientDevice($matches[1]));
    }

    /* check Cubot mobiles */
    elseif (preg_match('/(GT90)/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Cubot',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Infinix  mobiles */
    elseif (preg_match('/(X559)/', $ua, $matches)) {
        $rep = array(
            'X559'  => array('platform_model' => 'Hot 5 Lite',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Infinix',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Digital Alpha servers */
    elseif (preg_match('/ (Digital AlphaServer [A-Za-z0-9]*) /', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Digital Equipment Corporation (PC)',
            'platform_model'    => $model,
        ));
    }

    /* check Vodafone mobiles */
    elseif (preg_match('/Vodafone ([A-Za-z0-9]{3}N) Build/', $ua, $matches)) {
        $rep = array(
            '890N'  => array('platform_model' => 'Smart 4 Turbo (2014)',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Vodafone',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld'
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check SFR (France) mobiles */
    elseif (preg_match('/(STARTRAIL7) Build/', $ua, $matches)) {
        $rep = array(
            'STARTRAIL7'  => array('platform_model' => 'StarTrail 7',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'SFR',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check MobiWire mobiles */
    elseif (preg_match('/(Taima) Build/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'MobiWire',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check Oppo mobiles */
    elseif (preg_match('/(1201|A37fw|F1f) Build/', $ua, $matches)) {
        $rep = array(
            'F1f'   => array('platform_model' => 'F1',),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Oppo',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    } elseif (preg_match('/OPPO ([^.]+) Build/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Oppo',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }
    
    /* check Hisense mobiles */
    elseif (preg_match('/Hisense ([A-Z][0-9]{2,3}) Build/', $ua, $matches)) {
        $rep = array(
            'L678' => array('platform_model' => 'Staraddict 5'),
        );
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Hisense',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ),
            isset($rep[$model])?$rep[$model]:array()
        );
    }

    /* check Yotaphone mobiles */
    elseif (preg_match('/(YD20[0-9]) Build/', $ua, $matches)) {
        include_once ('clientDevices/Yotaphone.php.inc');
        $infos = array_merge($infos, get_YotaphoneClientDevice($matches[1]));
    }

    /* check Caterpillar mobiles */
    elseif (preg_match('/(S60) Build/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Caterpillar CAT',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check Vernee mobiles */
    elseif (preg_match('/(Apollo Lite) Build/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Vernee',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check eBest mobiles */
    elseif (preg_match('/EBEST ([^.]*) Build/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'eBest',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check Vivo mobiles */
    elseif (preg_match('/ vivo ([0-9]{4}) Build/', $ua, $matches)) {
        include_once ('clientDevices/Vivo.php.inc');
        $infos = array_merge($infos, get_VivoClientDevice($matches[1]));
    }

    /* check Sharp mobiles */
    elseif (preg_match('/(SH\-[0-9]{2}[A-Z]) Build/', $ua, $matches)) {
        include_once ('clientDevices/Sharp.php.inc');
        $infos = array_merge($infos, get_SharpClientDevice($matches[1]));
    }
    
    /* check Crosscall mobiles */
    elseif (preg_match('/(Action|Trekker|Odyssey)(\-|_| )([0-9\ A-Z]+) Build/i', $ua, $matches)) {
        include_once ('clientDevices/Crosscall.php.inc');
        $infos = array_merge($infos, get_CrosscallClientDevice(strtolower($matches[1].'-'.$matches[3])));
    }

    /*** check operating system ***/

    if (!isset($infos['system_title'])) {
        /* check Windows Phone */
        if (preg_match('/Windows Phone ?([^;]*);/', $ua, $matches))
            $infos = array_merge(array(
                'platform_type'     => 'handheld',
                'platform_format'   => 'handheld',
                'system_title'      => 'Windows Phone',
                'system_version'    => isset($matches[1])?$matches[1]:''
                ), $infos
            );

        /* check Android */
        elseif (preg_match('/(?:Android|Adr)[ \/]?([^;\) ]*)/', $ua, $matches)) {
            /* check version */
            $version = isset($matches[1])?$matches[1]:'';
            if ($version != '' and version_compare($version, $maxVersions['system']['Android']) > 0)
                return $fake;

            $infos = array_merge(array(
                'platform_type'     => (preg_match('/tablet/i',$ua) ? 'tablet' : 'handheld'),
                'platform_format'   => (preg_match('/tablet/i',$ua) ? 'tablet' : 'handheld'),
                'system_title'      => 'Android',
                'system_version'    => $version,
                ), $infos
            );
        }

        /* check determined linux os */
        elseif (preg_match('/(Debian|Ubuntu|DragonFly|SUSE|Slackware|CentOS|Fedora|Kubuntu|Edubuntu|Xubuntu|Gentoo|Red Hat|Mint|Mandriva|CrOS|Arch ?Linux|Caldera Systems OpenLinux)/i', $ua, $matches)) {
            $w = array('CrOS'=>'Chrome OS');
            $infos = array_merge(array(
                'platform_company'  => 'PC',
                'platform_model'    => '',
                'platform_type'     => 'computer',
                'platform_format'   => 'desktop',
                'system_title'      => isset($w[$matches[1]])?$w[$matches[1]]:ucwords($matches[1]).' (Linux)',
                'system_version'    => '',
            ), $infos);
        }
        
        /* check mobile gen os with notified version */
        elseif (preg_match('/(SymbianOS|webOS|KAIOS|Bada)(?:\/| )?([0-9][a-z0-9\._]*)/i', $ua, $matches)){
            $infos = array_merge(array(
                'platform_company'  => 'PC',
                'platform_model'    => '',
                'platform_type'     => 'handheld',
                'platform_format'   => 'handheld',
                'system_title'      => $matches[1],
                'system_version'    => isset($matches[2])?$matches[2]:''
            ), $infos);
        }
        
        /* check gen os with notified version */
        elseif (preg_match('/(AmigaOS|WebTV)(?:\/| )([0-9][a-z0-9\._]*)?/i', $ua, $matches))
            $infos = array_merge(array(
                'platform_company'  => 'PC',
                'platform_model'    => '',
                'platform_type'     => 'computer',
                'platform_format'   => 'desktop',
                'system_title'      => $matches[1],
                'system_version'    => isset($matches[2])?$matches[2]:''
            ), $infos);

        /* check gen os without notified version */
        elseif (preg_match('/(Linux|FreeBSD|SunOS|OpenBSD|SymbOS|OS\/2|BeOS|NetBSD|OpenSolaris|PalmSource)[^\.]/', $ua, $matches)) {
            $rep = array(
                'SymbOS'    => array('platform_company' => '', 'system_title' => 'SymbianOS', 'platform_type'     => 'handheld', 'platform_format'   => 'handheld',),
                'PalmSource'    => array('platform_company' => 'Palm', 'system_title' => 'PalmOS', 'platform_type'     => 'handheld', 'platform_format'   => 'handheld',),
            );

            $model = trim($matches[1]);

            $infos = array_merge($infos, array(
                'platform_company'  => 'PC',
                'platform_model'    => '',
                'platform_type'     => 'computer',
                'platform_format'   => 'desktop',
                'system_title'      => $matches[1],
                'system_version'    => '',
                ),
                isset($rep[$model])?$rep[$model]:array()
            );
        }

        /* check X11 gen unix  */
        elseif (preg_match('/X11/', $ua, $matches)) {
            $infos = array_merge($infos, array(
                'platform_company'  => 'PC',
                'platform_model'    => '',
                'platform_type'     => 'computer',
                'platform_format'   => 'desktop',
                'system_title'      => 'UNIX',
                'system_version'    => ''
                ),
                isset($rep[$matches[0]])?$rep[$matches[0]]:array()
            );
        }
        
        /* check Windows */
        else if (preg_match('/(?:Windows;)?[^.]*(?:Windows |Windows|Win |Win)([^;\)]+)/', $ua, $matches)) {
            // '/(?:Windows |Win)([^;]{1,});/'

            /* build known windows versions */
            $w = array('3.1'=>'3.1', '95'=>'95', '98'=>'98', '9x 4.90' => '98', '9x4.90' => '98', 'CE'=>'CE',
                'ME'=>'ME', 'NT'=>'NT', 'NT3.51'=> 'NT 3.51',  'NT 4.0'=>'NT 4.0', 'NT4.0'=>'NT 4.0', 'NT 5.0'=>'2000',
                '2000'=>'2000', 'NT 5.1'=>'XP', 'XP'=>'XP', 'NT 5.2'=>'XP Pro / Server 2003 / Home Server', 'NT 6.0'=>'Vista',
                'NT 6.1'=>'7', 'NT6.1'=>'7', 'NT 6.1'=>'7', 'NT 6.2'=>'8', 'NT 6.3'=>'8.1', 'NT 6.4'=>'10',
                'NT 10.0'=>'10', '10'=>'10',
            );

            /* build known windows fake versions */
            $wf = array('NT 7.0', 'NT 7.1', 'NT 8.0', 'NT 8.1', 'NT 9.0', 'NT 9.1', 'NT 10.1', 'NT 15.0');

            /* load version */
            $v = $matches[1];
            if (substr($v, 0, 1) == ' ') $v = trim(substr($v, 0, 7));
            $version = isset($w[$v])?$w[$v]:'';

            /* check fake version */
            if (in_array($v, $wf))
                return $fake;
                        
            $infos = array_merge(array(
                'platform_company'  => 'PC',
                'platform_model'    => '',
                'platform_type'     => 'computer',
                'platform_format'   => 'desktop',
                'system_title'      => 'Windows',
                'system_version'    => $version,
                ), $infos);
        }
    }

    /*** check browser ***/

    /* check opera mini */
    if (preg_match('/Opera Mini\/([0-9]+\.[0-9]+)/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Opera Mini',
            'browser_version'   => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ), $infos);

    /* check unsmartly written browser, case sensitive */
    elseif (preg_match('/(SE )(?:\/| )?([a-z0-9\._]*)?/', $ua, $matches)) {
        $rep = array('SE '=>'Sogou Explorer');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => isset($matches[2])?$matches[2]:'',
        ));
    }

    /* check unsmartly written browser, non case sensitive */
    elseif (preg_match('/(Maxthon|Opera|webissimo|NintendoBrowser|Acoo ?Browser|Deepnet Explorer|Avant Browser|BrowseX|OffByOne|KKman|LBBROWSER|Maemo Browser|BIDUBrowser|UBrowser|Airmail|EmbeddedWB|DX-Browser|Links|Sputnik|Instagram)(?:\/| )?([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array('BIDUBrowser'=>'Baidu Brower', 'AcooBrowser' => 'Acoo Browser', 'EmbeddedWB'=>'Delphi Embedded Web Browser');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => isset($matches[2])?$matches[2]:'',
        ));
    }

    /* check compatible level 2 browsers */
    elseif (preg_match('/(Yowser|MQQBrowser|Goanna)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array('MQQBrowser'=>'Mobile QQBrowser');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => isset($matches[2])?$matches[2]:'',
        ));
    }

    /* check Chrome/Safari/Firefox/Explorer compatible browsers, with specific details */
    elseif (preg_match('/(Viera)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array(
            'Viera'   => array('browser_title'=>'Viera', 'platform_type'     => 'tvset'),
        );
        $infos = array_merge($infos, array(
            'browser_title'     => isset($matches[1])?$matches[1]:'',
            'browser_version'   => isset($matches[2])?$matches[2]:'',
            ), (isset($rep[$matches[1]])?$rep[$matches[1]]:array())
        );
    }

    /* check Chrome/Safari/Firefox/Explorer compatible browsers, to be tested before usual browsers */
    elseif (preg_match('/(YaBrowser|OPR|IceDragon|Dragon|CriOS|Adventurer|Sleipnir|BoBrowser|Dolfin|ChromePlus|Phoenix|Shiretoko|NS8|MiuiBrowser|SamsungBrowser\/CrossApp|SamsungBrowser|Vivaldi|Qt|Iceweasel|Puffin|Firebird|FBAV|app-ipad-CoteMaison|QQBrowser|PaleMoon|Arora|Edge|Cheshire|MicroMessenger|Getter|Dooble|amaya|Roccat|QupZilla|MMS|Iron|ACHEETAHI|OPiOS|Beonex|LibertyBrowser|LinkedIn|SeaMonkey|Cyberfox|Focus|Fennec|K-Meleon|CoolNovo|QuickLook|GSA|Electron|NG|FxiOS|Lotus-Notes|Chimera|Epiphany|Iridium|HeadlessChrome|QwantiOS|Blazer|TenFourFox|Silk)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array('OPR'=>'Opera', 'CriOS'=>'Chrome', 'Dragon'=>'IceDragon', 'NS8'=>'Netscape', 'Firebird'=>'Thunderbird', 'FBAV'=>'Facebook App', 'app-ipad-CoteMaison'=>'C&ocirc;t&eacute; Maison App', 'amaya'=>'Amaya', 'MMS'=>'Opera Neon', 'ACHEETAHI'=>'CM Browser', 'OPiOS'=>'Opera mini', 'Focus'=>'Firefox Focus', 'GSA'=>'Google Search App', 'NG'=>'Browser NG', 'FxiOS'=>'Firefox', 'Lotus-Notes'=>'Lotus Notes', 'QwantiOS'=>'Qwant', 'Blazer'=> 'Palm Blazer', 'MicroMessenger' => 'WeChat');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => isset($matches[2])?$matches[2]:'',
        ));
    }

    /* check no version written browser */
    elseif (preg_match('/(HeadlessChrome|Iron|Advanced Browser|Magic Browser|Pinterest)/', $ua, $matches)) {
        $rep = array();
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
        ));
    }

    /* check some other browsers */
    elseif (preg_match('/(Edge|TencentTraveler)/i', $ua, $matches)) {
        $rep = array('TencentTraveler'=>'TT Explorer');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => '',
        ));
    }

    /* check gen computer browsers */
    elseif (preg_match('/(Chromium|Netscape|Camino|Minefield|Fennec|Firefox|Galeon|iCab|Konqueror|IEMobile|Shiira|NetNewsWire|Symphony|Lynx|Crazy Browser|UCBrowser|GoBrowser|Cobra|ELinks|HotJava|Tor Browser|Dillo|FDM|FortiMail|VSE|MultiZilla|UCWEB|Otter|Netbox|AvantGo)(?:\/| )?([a-z0-9\._]*)/', $ua, $matches)) {
        $rep = array('FDM'=>'Free Download Manager', 'VSE'=>'VSE Link Tester', 'UCWEB' => 'UC Browser');
        $infos = array_merge(array(
            'platform_type'     => 'computer',
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => str_replace('_','.',$matches[2]),
        ), $infos);
    }

    /* check chrome browser - separated from gen case of alternative browser using Chrome user agent */
    elseif (preg_match('/(Chrome)(?:\/| )?([a-z0-9\._]*)/', $ua, $matches)) {
        $infos = array_merge(array(
            'platform_type'     => 'computer',
            'browser_title'     => 'Chrome',
            'browser_version'   => str_replace('_','.',$matches[2]),
            ), $infos
        );

        /* Amigo's Mail.ru web browser based on chrome (and using chrome version) */
        if (preg_match('/(MRCHROME)/', $ua, $matches))
            $infos['browser_title'] = 'Amigo';
    }

    /* check gen mobile browsers */
    elseif (preg_match('/(Dorado WAP-Browser)(?:\/| )?([a-z0-9\._]*)/', $ua, $matches)) {
        $rep = array('Dorado WAP-Browser'=>'Dorado');
        $infos = array_merge(array(
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            'browser_title'     => $matches[1],
            'browser_version'   => str_replace('_','.',$matches[2]),
            ), $infos
        );
    }

    /* check OmniWeb, before safari */
    elseif (preg_match('/OmniWeb\/v?([^ \.]+)/', $ua, $matches)) {
        $versions = array('622' => '5.9', '626' => '5.11', '630' => '6');
        $infos = array_merge(array(
            'browser_title'     => 'OmniWeb',
            'browser_version'   => array_key_exists($matches[1], $versions) ? $versions[$matches[1]] : $matches[1],
            ), $infos
        );
    }

    /* check gen browser : ?? */
    elseif (preg_match('/Version\/([a-z0-9\._]*)( Mobile)? Safari\//', $ua, $matches)) {
        if ($infos['system_title'] == 'Android')
            $infos = array_merge(array(
                'browser_title'     => 'Chrome'.(isset($matches[2])?$matches[2]:''),
                'browser_version'   => str_replace('_','.',$matches[1])
                ), $infos
            );
        else
            $infos = array_merge(array(
                'browser_title'     => 'Safari'.(isset($matches[2])?$matches[2]:''),
                'browser_version'   => str_replace('_','.',$matches[1])
                ), $infos
            );
    }

    /* check no version detection browser */
    elseif (preg_match('/(Opera Mobi)/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => $matches[1],
            'browser_version'   => '',
            ), $infos
        );

    /* check undeterminated safari version */
    elseif (preg_match('/(Safari|AppleWebKit)/', $ua, $matches)) {
        if ($infos['system_title'] == 'Android') {
            $infos = array_merge(array(
                'browser_title'     => 'Android browser',
                'browser_version'   => '',
                ), $infos
            );
      } else {
            $infos = array_merge(array(
                'browser_title'     => 'Safari compatible',
                'browser_version'   => '',
                ), $infos
            );
        }
    }

    /* check msie */
    elseif (preg_match('/MSIE ?([a-z0-9\._]*)( |;|\-|\))/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Internet Explorer',
            'browser_version'   => str_replace('_','.',$matches[1]),
            ), $infos
        );

    /* check IE Mobile detection */
    elseif (preg_match('/(IEMobile)(?:\ )([a-z0-9\._]*)/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Internet Explorer Mobile',
            'browser_version'   => str_replace('_','.',$matches[2]),
            ), $infos
        );

    /* check trident compatible browsers */
    elseif (preg_match('/(Trident\/)([a-z0-9\._]*)/', $ua, $matches))
        if (preg_match('/rv:11.0/', $ua, $m))
            $infos = array_merge(array(
                'browser_title'     => 'Internet Explorer',
                'browser_version'   => '11.0',
                ), $infos
            );
        else
            $infos = array_merge(array(
                'browser_title'     => 'Trident compatible',
                'browser_version'   => str_replace('_','.',$matches[2]),
                ), $infos
            );

    /* check America Online Browser */
    elseif (preg_match('/America Online Browser ([a-z0-9\._]*);/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'America Online Browser',
            'browser_version'   => str_replace('_','.',$matches[1]),
            ), $infos
        );

    /* check Windows Media Player */
    elseif (preg_match('/^Windows-Media-Player\/([^\(]*)|Media Player Classic/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Microsoft Windows Media Player',
            'browser_version'   => isset($matches[1])?$matches[1]:'',
            'system_title'      => 'Windows',
            ), $infos
        );


    /* check FrontPage */
    elseif (preg_match('/^MSFrontPage\/([^\(]*)/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Microsoft FrontPage',
            'browser_version'   => $matches[1],
            'system_title'      => 'Windows',
            ), $infos
        );

    /* check MoonBrowser */
    elseif (preg_match('/MoonBrowser \(([^\(]*)\)/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Moon Browser',
            'browser_version'   => $matches[1],
            'system_title'      =>'Windows',
            ), $infos
        );

    /* check Barca */
    elseif (preg_match('/^Barca\/([^\(]*)/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Barca',
            'browser_version'   => $matches[1],
            'system_title'      => 'Windows',
            ), $infos
        );

    /* check Pizilla */
    elseif (preg_match('/^Pizilla\+\+ ver ([0-9\. ]*)$/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Pizilla',
            'browser_version'   => $matches[1],
            ), $infos
        );

    /* check Microsoft Data Access Internet Publishing Provider DAV */
    elseif (preg_match('/^Microsoft Data Access Internet Publishing Provider DAV$/', $ua, $matches))
        $infos = array_merge(array($infos,
            'browser_title'     => 'Office (2000 and superior) WebDav client ',
            'system_title'      => 'Windows',
        ));

    /* check Microsoft Office */
    elseif (preg_match('/^(Microsoft Office [A-Za-z0-9\ ]*)$/', $ua, $matches))
        $infos = array_merge(array($infos,
            'browser_title'     => $matches[1],
            'system_title'      => 'Windows',
        ));

    /* check HotJava */
    elseif (preg_match('/^HotJava\/([^\(]*)/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'HotJava',
            'browser_version'   => $matches[1],
            ), $infos
        );

    /* check MAUI WAP Browser  */
    elseif (preg_match('/^MAUI( |_)WAP( |_)Browser/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'MAUI WAP Browser',
            'browser_version'   => '',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            ), $infos
        );

    /* check other browsers with specific details */
    elseif (preg_match('/(AWeb|Blazer|DreamPassport|Liberate DTV|SlimBrowser|Zoo Tycoon 2 Client)(?:\/| )?([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array(
            'AWeb'                  => array('system_title'=>'Amiga'),
            'Blazer'                => array('platform_company'=>'Palm', 'system_title'=>'Palm OS', 'platform_type' => 'handheld', 'platform_format' => 'handheld',),
            'Liberate DTV'          => array('platform_company'=>'LiberateHealth',),
            'DreamPassport'         => array('platform_company'=>'Sega', 'platform_model'=>'DreamCast', 'system_title'=>'DreamCast OS'),
            'SlimBrowser'           => array('system_title' =>'Windows'),
            'Zoo Tycoon 2 Client'   => array('system_title' =>'Windows', 'browser_title'=>'Microsoft Zoo Tycoon 2 Client'),
        );
        $infos = array_merge($infos, array(
            'browser_title'     => isset($matches[1])?$matches[1]:'',
            'browser_version'   => isset($matches[2])?$matches[2]:'',
            ), (isset($rep[$matches[1]])?$rep[$matches[1]]:array())
        );
    }

    /* check Gecko compatible */
    elseif (preg_match('/Gecko/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Firefox compatible',
            ), $infos
        );

    /* check old netscape */
    elseif (preg_match('/^Mozilla\/([1-4].[0-9]{1,2})/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Netscape',
            'browser_version'   => $matches[1],
            ), $infos
        );

    /* set type to "visitor" if not defined and browser title set */
    if (!isset($infos['platform_type']) and isset($infos['browser_title']) and $infos['browser_title'] != '')
        $infos['platform_type'] = 'computer';
    if ((!isset($infos['platform_format']) or $infos['platform_format'] == '') and isset($infos['browser_title']) and $infos['browser_title'] != '')
        $infos['platform_format'] = 'desktop';

    if (!isset($infos['platform_format']) or $infos['platform_format'] == '' or $infos['platform_format'] == 'desktop') {
        /* check for generic mobile */
        if (preg_match('/mobile/i', $ua, $matches))
            $infos = array_merge($infos,array(
            'platform_format'   => 'handheld',
        ));

        /* check for generic tablet */
        elseif (preg_match('/tablet/i', $ua, $matches))
            $infos = array_merge($infos, array(
                'platform_format'   => 'tablet',
            ));
    }

    /* check browser and version */
    if (isset($infos['browser_version']) and isset($maxVersions['browser'][$infos['browser_title']]) and version_compare($infos['browser_version'], $maxVersions['browser'][$infos['browser_title']]) > 0)
        return $fake;

    /* return result */
    return _client_mergeUAInfos($req, $infos);
}

/**
 * Return bot index if bot.
 * @param string $ua
 * @return mixed
 */
function client_checkIsBot($ua=false) {
    /* get user agent */
    if (!$ua) $ua = client_getUserAgent();
    
    /* load known bots */
    $knownBots = client_getKnownBots();
    
    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownBots));
    $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';
    
    /* start detection and return result */
    if (preg_match($detectionPattern, strtolower($ua), $result))
        return $result[0];
    return false;
}

/**
 * Return bot info if bot.
 * @param string $bot
 * @return mixed
 */
function client_getBotInfos($bot='') {
    $knownBots = client_getKnownBots();
    
    if (isset($knownBots[$bot]))
        return $knownBots[$bot];
    return array();
}


/**
 * Return bot info from user agent.
 * @param string $ua
 * @return mixed
 */
function client_getBotInfosFromUserAgent($ua='') {
    $knownBots = client_getKnownBots();
    
    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownBots));
    $detectionPattern = preg_replace ('/(\/|\(|\)|\.|\+)/', '\\\$1', $detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';
    
    /* start detection and return result */
    if ( preg_match ( $detectionPattern, strtolower($ua), $result ) )
        return $knownBots[$result[0]];
    return false;
}

/**
 * Return known bots list.
 * @return array
 */
function client_getKnownBots() {
    include_once('clientBots/Bots.php.inc');
    return _client_getKnownBots();
}

/**
 * return tool index if tool
 * @param string $ua
 * @return mixed
 */
function client_checkIsTool($ua=false) {
    /* get user agent */
    if (!$ua) $ua = client_getUserAgent();
    
    /* load known tools */
    $knownTools = client_getKnownTools();
    
    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownTools));
    $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match($detectionPattern, strtolower($ua), $result))
        return $result[0];
    return false;
}

/**
 * Return tool info if tool.
 * @param string $tool
 * @return mixed
 */
function client_getToolInfos($tool='') {
    $knownTools = client_getKnownTools();

    if (isset($knownTools[$tool]))
        return $knownTools[$tool];
    return array();
}

/**
 * Return tool info from user agent.
 * @param string $ua
 * @return mixed
 */
function client_getToolInfosFromUserAgent($ua='') {
    $knownTools = client_getKnownTools();
    
    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownTools));
    $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match($detectionPattern, strtolower($ua), $result))
        return $knownTools[$result[0]];
    return false;
}

/**
 * Return given known tool list.
 * @return array
 */
function client_getKnownTools() {
    include_once('clientBots/Tools.php.inc');
    return _client_getKnownTools();
}

/*** generic tool/boot specific methods */

/**
 * Return generic index if generic.
 * @param string $ua
 * @return mixed
 */
function client_checkIsGeneric($ua=false) {
    /* get user agent */
    if (!$ua) $ua = client_getUserAgent();
    
    /* load known generic agents */
    $knownGenerics = client_getKnownGenerics();
    
    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownGenerics));
    $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match ( $detectionPattern, strtolower($ua), $result))
        return $result[0];
    return false;
}

/**
 * Return generic info if generic.
 * @param string $generic
 * @return mixed
 */
function client_getGenericInfos($generic='') {
    $knownGenerics = client_getKnownGenerics();

    if (isset($knownGenerics[$generic]))
        return $knownGenerics[$generic];
    return array();
}

/**
 * Return bot info from user agent.
 * @param string $ua
 * @return mixed
 */
function client_getGenericInfosFromUserAgent($ua='') {

    /* remove hotjava from java results */
    if (preg_match('/^HotJava/i', $ua))
        return false;

    /* load generic/libraries */
    $knownGenerics = client_getKnownGenerics();
    
    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownGenerics));
    $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match ( $detectionPattern, strtolower($ua), $result))
        return $knownGenerics[$result[0]];
    return false;
}

/**
 * Return given known web generic library list.
 * @return array
 */
function client_getKnownGenerics() {
    include_once('clientBots/Generics.php.inc');
    return _client_getKnownGenerics();
}

/*** hack type specific methods ***/

/**
 * Return hack index if hack.
 * @param string $ua
 * @return mixed
 */
function client_checkIsHack($ua=false) {
    /* get user agent */
    if (!$ua) $ua = client_getUserAgent();
    
    /* load known bots */
    $knownHacks = client_getKnownHacks();
    
    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownHacks));
    $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';
    
    /* start detection and return result */
    if (preg_match($detectionPattern, strtolower($ua), $result))
        return $result[0];
    return false;
}

/**
 * Return bot info if hack.
 * @param string $hack
 * @return mixed
 */
function client_getHackInfos($hack='') {
    $knownHacks = client_getKnownHacks();
    
    if (isset($knownHacks[$hack]))
        return $knownHacks[$hack];
    return array();
}

/**
 * Return hack info from user agent.
 * @param string $ua
 * @return mixed
 */
function client_getHackInfosFromUserAgent($ua='') {
    $knownHacks = client_getKnownHacks();
    
    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownHacks));
    $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match($detectionPattern, strtolower($ua), $result))
        return $knownHacks[$result[0]];
    return false;
}

/**
 * Return given known web hack or hack list.
 * @return array
 */
function client_getKnownHacks() {
    include_once('clientBots/Hacks.php.inc');
    return _client_getKnownHacks();
}

/**
 * Return fake visitor info from user agent.
 * @param string $ua
 * @return mixed
 */
function client_getFakeInfosFromUserAgent($ua='') {
    $fake = array('platform_type'     => 'fake');

    $ua = trim($ua);

    if ($ua == '')
        return $fake;

    if ($ua == 'null')
        return $fake;

    if (preg_match('#^Mozilla$#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla-1.1$#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/[0-9][.|,]0$#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/%2F[0-9][.|,]0$#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/[0-9][.|,]0 \(compatible;?\)?$#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/[0-9].0 \(compatible; MSIE[0-9].00; Windows 200[1-9]\)#i', $ua))
        return $fake;

    if (preg_match('#^mozilla/0.([0-9]+) beta \(windows\)#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/1.22 \(compatible; MSIE 2.0; Windows 95\)#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/4.0 \(compatible; MSIE 5.0; Windows 98\)#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/4.0 \(compatible; MSIE 999.1; Unknown\)#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/1.22 \(compatible; MSIE 10.0; Windows 3.1\)#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/3.0 \(x86 \[en\] Windows NT 5.1; Sun\)#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/2.02E \(Win95; U\)$#i', $ua))
        return $fake;

    if (preg_match('#^Mozilla/42.0 \(compatible; MSIE 28.0; Win128\)$#i', $ua))
        return $fake;

    if (preg_match('#Mozilla/2.0 \(compatible; MSIE 3.02; Windows CE; 240x320\)#i', $ua))
        return $fake;

    if (preg_match('#Mozilla/4.0 \(compatible; MSIE 6.0; MSIE 5.5; Windows NT 5.0\) Opera 7.02 Bork-edition \[en\]#i', $ua))
        return $fake;

    if (preg_match('#Mozilla/5.0 \(compatible; MSIE 10.0; Macintosh; Intel Mac OS X 10_7_3; Trident/6.0\)#i', $ua))
        return $fake;

    /* fake russian spammer */
    if (preg_match('#Mozilla/1.22 \(compatible; MSIE 2.0d; Windows NT\)#i', $ua))
        return $fake;

    /* fake russian spammer */
    if (preg_match('#Mozilla/4.0 \(compatible; MSIE 7.0b; Windows NT 6.0 ; .NET CLR 2.0.50215; SL Commerce Client v1.0; Tablet PC 2.0#i', $ua))
        return $fake;

    /* fake russian spammer */
    if (preg_match('#Mozilla/4.0 \(compatible; MSIE 5.0; Windows 3.1\)#i', $ua))
        return $fake;

    /* funwebproducts malware *
    if (preg_match('#FunWebProducts#i', $ua))
        return $fake;

    /* fake russian spammer */
    if (preg_match('#^Mozilla/5.0 \(Windows NT 6.1; WOW64; rv:41.0\) Gecko/20100101 Firefox/41.0$#i', $ua))
        return $fake;

    /* fake russian spammer */
    if (preg_match('#^Mozilla/5.0 \(Windows NT 6.1; WOW64\) AppleWebKit/537.36 \(KHTML, like Gecko\) Chrome/40.0.2214.111 Safari/537.36$#i', $ua))
        return $fake;

    /* fake russian spammer */
    if (preg_match('#Mozilla/4.0 \(compatible; MSIE 5.0; Windows NT; DigExt\)#i', $ua))
        return $fake;

    /* fake russian spammer */
    if (preg_match('#Mozilla/4.0 \(compatible; MSIE 6.0; AOL 9.0; Windows NT 5.1\)#i', $ua))
        return $fake;

    /* php default useragent passed as string intead of CONST */
    if (preg_match('#^_USERAGENT_$#i', $ua))
        return $fake;

    /* fake requests from Amazon AWS services */
    if (preg_match('#^Mozilla/5.0 \(Windows NT 6.1; rv:15.0\) Gecko/20120716 Firefox/15.0a2$#i', $ua))
        return $fake;
    if (preg_match('#^"Mozilla/5.0([^"]*)"$#i', $ua))
        return $fake;

    /* fake requests from Lituania */
    if (preg_match('#^Dalvik/2.1.0 \(Linux; U; Android 5.1.1; D5503 Build/14.6.A.1.236\)$#i', $ua))
        return $fake;

    /* fake requests with double user agent combined */
    if (preg_match_all('#Mozilla/[0-9].0#i', $ua, $matches) and count($matches[0]) > 1)
        return $fake;

    /* fake requests from China */
    if (preg_match('#^Mozilla/5.0 \(Windows; U; Windows NT 6.1; en-us; rv:1.9.2.3\) Gecko/20100401 YFF35 Firefox/3.6.3$#i', $ua))
        return $fake;

    /* fake requests from China */
    if (preg_match('#^MSDN SurfBear$#i', $ua))
        return $fake;

    /* fake request */
    if (preg_match('#\'Mozilla/5.0\(Macintosh;IntelMacOSX10_8_2\)AppleWebKit/537.36\(KHTML,likeGecko\)Chrome/27.0.1453.116Safari/537.36\'#i', $ua))
        return $fake;

    /* fake requests with uncomplete gecko firefox UA, same IP as Python requests */
    if (preg_match('#^\'Mozilla/5.0 Gecko Firefox\'$#i', $ua))
        return $fake;

    /* fake requests from 80.169.91.26 */
    if (preg_match('#-[0-9]{7}$#', $ua))
        return $fake;

    /* badly set user agent */
    if (preg_match('#^=#', $ua))
        return $fake;

    /* bad msie/msid request */
    if (preg_match('#^Mozilla/4.0 \(compatible; MSID [0-9\.]+; Windows NT [0-9\.]+\)$#i', $ua))
        return $fake;
        
    /* bad msie/msid request */
    if (preg_match('#^Mozilla/5.3$#i', $ua))
        return $fake;

    /* not a fake but Apple using a bad user agent */
    if (preg_match('#Mozilla/5.0 \(Macintosh; Intel Mac OS X 10_11_1\) AppleWebKit/601.2.4 \(KHTML, like Gecko\) Version/9.0.1 Safari/601.2.4 facebookexternalhit/1.1 Facebot Twitterbot/1.0#', $ua))
        return array(
            'platform_type'     => 'tool',
            'platform_format'   => 'desktop',
            'tool_title'        => 'Apple iMessages bot',
            'tool_url'          => '',
            'engine_title'      => 'Apple',
            'engine_url'        => 'http://www.apple.com',
        );
    
    /* badly set user agent */
    if (preg_match('#Connection: closern$#i', $ua))
        return $fake;

    /* default result */
    return false;
}

/*** private methods ***/

/**
 * Return merged informations.
 * @param array $req
 * @param array $infos
 * @return array
 * @private
 */
function _client_mergeUAInfos($req, $infos) {
    if ($req === true)
        $req = array(
            'platform_company', 'platform_model', 'platform_type', 'platform_format', 'platform_year',
            'system_title', 'system_version',
            'browser_title', 'browser_version'
        );
    $i = array();
    foreach($req as $r)
        if (isset($infos[$r]))
            $i[$r] = $infos[$r];
        else
            $i[$r] = '';
    return $i;
}

/**
 * Return some max property values to check.
 * @return array
 * @private
 */
function _client_getUAPropertiesMaxVersions() {
    return array(
        'system' => array(
            'Mac OS X'          => '10.15.0',               // current is 10.13.x
            'iOS'               => '13',                    // current is 11.x
            'Android'           => '10',                    // current is 8.x.x
        ),
        'browser' => array(
            'Firefox'           => '64',                    // current is 60
            'Chrome'            => '75',                    // current is 66
            'Chromium'          => '75',                    // current is 66
            'Internet Explorer' => '11.0.50',               // latest
            'Edge'              => '45',                    // current is 40
            'Opera'             => '56',                    // current is 52
            'Safari'            => '15',                    // current is 11
        ),
    );
}
?>
