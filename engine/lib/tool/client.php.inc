<?php
/**
 * @brief Client specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/client.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.96
 * @date Creation: Jun 2007
 * @date Modification: Jan 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $softwareProperties;

/**
 * Return client IP address.
 * @return string
 */
function client_getIp() {
    if (!empty($_SERVER['HTTP_CLIENT_IP']))
        $ip = $_SERVER['HTTP_CLIENT_IP'];
    elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR']))
        $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
    elseif (!empty($_SERVER['HTTP_X_FORWARDED']))
        $ip = $_SERVER['HTTP_X_FORWARDED'];
    elseif (!empty($_SERVER['HTTP_FORWARDED_FOR']))
        $ip = $_SERVER['HTTP_FORWARDED_FOR'];
    elseif (!empty($_SERVER['HTTP_FORWARDED']))
        $ip = $_SERVER['HTTP_FORWARDED'];
    elseif (!empty($_SERVER['REMOTE_ADDR']))
        $ip = $_SERVER['REMOTE_ADDR'];
    else
        return '';

    if (string_isValidIPv4($ip))
        return $ip;
    return '';
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

    /*** check fake visitors */
    if (($c = client_getFakeInfosFromUserAgent($ua)) !== false)
        return $c;

    /*** check hacks */
    if (($c = client_getHackInfosFromUserAgent($ua)) !== false)
        return $c;

    /*** check unknown */
    if (($c = client_getUnknownInfosFromUserAgent($ua)) !== false)
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

    /* init result value */
    $infos = array();

    /* load max versions to check and default fake value */
    $fake = array('platform_type'     => 'fake');

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

    /* check Playstation 4 / Vita */
    if (preg_match('/\(PlayStation ([^ ]*) ([0-9\.]*)\)/i', $ua, $matches))
        $infos = array(
            'platform_company'  => 'Sony',
            'platform_model'    => 'Playstation '.$matches[1],
            'platform_type'     => 'computer',
            'platform_format'   => $matches[1] == 'Vita' ? 'handheld' : 'desktop',
            'system_title'      => 'Playstation '.$matches[1],
            'system_version'    => $matches[2],
            'browser_title'     => 'PS '.$matches[1].' Browser',
            'browser_version'   => '--',
        );

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
    if (preg_match('/BB([^\/;]{1,});/', $ua, $matches)) {
        if (preg_match('/ Version\/([0-9\.]*) /', $ua, $matches2))
            $version = $matches2[1];
        else
            $version = '--';
        return _client_mergeUAInfos($req, array(
            'platform_company'  => 'BlackBerry',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            'system_title'      => 'BlackBerry OS',
            'system_version'    => $matches[1],
            'browser_title'     => 'BB Browser',
            'browser_version'   => $version,
        ));
    }
    else if (preg_match('/ (BB|ST)([ ]?[A-Z][0-9\-]*)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/BlackBerry.php.inc');
        $device = $matches[1].$matches[2];
        $infos = array_merge($infos, get_BlackBerryClientDevice($device));
    }

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
    elseif (preg_match('/Nokia(?: |_|\-|\/|)([^_\-\/]+)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Nokia.php.inc');
        $infos = array_merge($infos, get_NokiaClientDevice(trim($matches[1])));
    } elseif (preg_match('/(Lumia [a-zA-Z0-9 ]*)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Nokia.php.inc');
        $infos = array_merge($infos, get_NokiaClientDevice($matches[1]));
    } elseif (preg_match('/(TA\-[0-9]{4})( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Nokia.php.inc');
        $infos = array_merge($infos, get_NokiaClientDevice($matches[1]));
    }

    /* check Accent devices : before Archos */
    elseif (preg_match('/ Accent ([^\)]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Accent.php.inc');
        $model = strtolower(trim($matches[1]));
        $infos = array_merge($infos, get_AccentClientDevice($model));
    }

    /* check Archos devices - before iOS */
    elseif (preg_match('/ Archos[;]? ([A-Za-z0-9\- ]{3,})( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Archos.php.inc');
        $infos = array_merge($infos, get_ArchosClientDevice(trim($matches[1])));
    } elseif (preg_match('/ (A[C]?[0-9][05]B?)(HE|TI)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Archos.php.inc');
        $device = trim($matches[1].$matches[2]);
        $infos = array_merge($infos, get_ArchosClientDevice($device));
    }

    /* check iphone / ipod / ipad */
    elseif (preg_match('/(iPod|iPhone|iPad);?.*; CPU ([A-Za-z\ ]*)? ([0-9_]*)/', $ua, $matches)) {
        /* check version */
        $version = str_replace('_', '.', $matches[3]);

        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => $matches[1],
            'platform_type'     => $matches[1]=='iPad'? 'tablet': 'handheld',
            'platform_format'   => $matches[1]=='iPad'? 'tablet': 'handheld',
            'system_title'      => 'iOS',
            'system_version'    => $version,
        ));

        /* check for safari mobile version */
        if (preg_match('/Version\/([0-9\.]*)/', $ua, $matches)) {
            $infos = array_merge($infos, array(
                'browser_title'     => 'Safari Mobile',
                'browser_version'   => $matches[1],
            ));
        }

        /* check for device model */
        if (preg_match('/(iPhone|iPod|iPad)([0-9_\,]{3,})/i', $ua, $matches)) {
            include_once('clientDevices/Apple.php.inc');
            $model = $matches[1].str_replace(array('_', ','), '.', $matches[2]);
            $infos = array_merge($infos, get_AppleClientDevice($model));
        }

    } elseif (preg_match('/(iPhone|iPod|iPad)\/([0-9\.]*) hw\/(iPhone|iPod|iPad)([0-9_]{3,})/i', $ua, $matches)) {
        /* check version */
        $version = str_replace('_', '.', $matches[2]);

        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => $matches[1],
            'platform_type'     => $matches[1]=='iPad'? 'tablet': 'handheld',
            'platform_format'   => $matches[1]=='iPad'? 'tablet': 'handheld',
            'system_title'      => 'iOS',
            'system_version'    => $version,
        ));
        include_once('clientDevices/Apple.php.inc');
        $model = $matches[3].str_replace(array('_', ','), '.', $matches[4]);
        $infos = array_merge($infos, get_AppleClientDevice($model));

    } elseif (preg_match('/(iPod|iPhone|iPad)([0-9_\,\.]{3,})?/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => $matches[1],
            'platform_type'     => $matches[1]=='iPad'? 'tablet': 'handheld',
            'platform_format'   => $matches[1]=='iPad'? 'tablet': 'handheld',
            'system_title'      => 'iOS',
        ));

        /* Check for device model */
        if (isset($matches[2])) {
            include_once('clientDevices/Apple.php.inc');
            $model = $matches[1].str_replace(array('_', ','), '.', $matches[2]);
            $infos = array_merge($infos, get_AppleClientDevice($model));
        }

        /* Check for iOS version */
        if (preg_match('/iOS ([0-9_\,\.]{3,})/', $ua, $matches)) {
            $infos['system_version'] = str_replace(array('_', ','), '.', $matches[1]);
        }
    } elseif (preg_match('/ Darwin\/([0-9\.]*)(?!.*\(x86_64\))/i', $ua, $matches)) {
        /* check version */
        $version = $matches[1];
        $version = explode('.', $version);
        $version = (int)$version[0]-7;

        /* build info */
        $infos = array_merge($infos, array(
            'platform_company'  => 'Apple',
            'platform_model'    => 'iPhone/iPad/iPod',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
            'system_title'      => 'iOS',
            'system_version'    => $version
        ));
    }

    /* check Google */
    elseif (preg_match('/ (Nexus|Pixel)( [^\/;]+)?( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Google.php.inc');
        $model = $matches[1].(isset($matches[2])?$matches[2]:'');
        $infos = array_merge($infos, get_GoogleClientDevice($model));
    }

    /* check HTC */
    elseif (preg_match('/HTC;([A-Za-z0-9 ]*)/', $ua, $matches)) {
        include_once('clientDevices/HTC.php.inc');
        $infos = array_merge($infos, get_HTCClientDevice($matches[1]));
    } elseif (preg_match('/HTC[ |_]([^\/]*)( Build|\-|\))/i', $ua, $matches)) {
        include_once('clientDevices/HTC.php.inc');
        $model = preg_replace('/_/', ' ', $matches[1]);
        $infos = array_merge($infos, get_HTCClientDevice($model));
    } elseif (preg_match('/HTC([A-Za-z0-9]+)/', $ua, $matches)) {
        include_once('clientDevices/HTC.php.inc');
        $model = preg_replace('/_/', ' ', $matches[1]);
        $infos = array_merge($infos, get_HTCClientDevice($model));
    } elseif (preg_match('/ (ADR6300|2PYB2|2PQ93)/', $ua, $matches)) {
        include_once('clientDevices/HTC.php.inc');
        $infos = array_merge($infos, get_HTCClientDevice($matches[1]));
    } elseif (preg_match('/ (dream)\)/', $ua, $matches)) {
        include_once('clientDevices/HTC.php.inc');
        $infos = array_merge($infos, get_HTCClientDevice($matches[1]));
    }

    /* check LG */
    elseif (preg_match('/^LG(?:E|)(?: |_|\-|\/)([^ _\-\/]+)/', $ua, $matches)) {
        include_once('clientDevices/LG.php.inc');
        $infos = array_merge($infos, get_LGClientDevice($matches[1]));
    } elseif (preg_match('/L[G|M]-?([A-Z]{1,2}[0-9]{3}[A-Z]{0,})/', $ua, $matches) or preg_match('/LG([A-Z]{1,2}[0-9]*[A-Z]{0,})/', $ua, $matches)) {
        include_once('clientDevices/LG.php.inc');
        $infos = array_merge($infos, get_LGClientDevice($matches[1]));
    } elseif (preg_match('/ (VS[0-9]{3}) Build/', $ua, $matches)) {
        include_once('clientDevices/LG.php.inc');
        $infos = array_merge($infos, get_LGClientDevice($matches[1]));
    }

    /* check Motorola */
    elseif (preg_match('/mot(?:-|orola|o|\-moto)([^\/;]+)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Motorola.php.inc');
        $infos = array_merge($infos, get_MotorolaClientDevice(trim($matches[1])));
    } elseif (preg_match('/ (Droid|MB200|RAZR HD|Milestone)/', $ua, $matches)) {
        include_once('clientDevices/Motorola.php.inc');
        $infos = array_merge($infos, get_MotorolaClientDevice($matches[1]));
    } elseif (preg_match('/XT([0-9]{3,})/', $ua, $matches)) {
        include_once('clientDevices/Motorola.php.inc');
        $infos = array_merge($infos, get_MotorolaClientDevice($matches[0]));
    }

    /* check Palm devices */
    elseif (preg_match('/(Pre|Pixi)\/[0-9\.]*$/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Palm',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check BQ devices, before Samsung */
    elseif (preg_match('/ (Aquaris [A-Za-z0-9 \.]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/BQ.php.inc');
        $infos = array_merge($infos, get_BQClientDevice($matches[1]));
    } elseif (preg_match('/ BQ(ru|S)?(-|\_| )?([0-9]{4}[A-Za-z]*|Aquaris [A-Z0-9 \.]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/BQ.php.inc');
        $infos = array_merge($infos, get_BQClientDevice($matches[3]));
    }

    /* check samsung devices */
    elseif (preg_match('/(GT|SM|SGH|SHV|SC)-([A-Z0-9]{3,})/', $ua, $matches)) {
        include_once('clientDevices/Samsung.php.inc');
        $infos = array_merge($infos, get_SamsungClientDevice($matches[0]));
    } elseif (preg_match('/; (SCV[0-9]{2})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Samsung.php.inc');
        $infos = array_merge($infos, get_SamsungClientDevice($matches[1]));
    } elseif (preg_match('/SAMSUNG\-(?:SGH\-|)([^\/]+)/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Samsung',
            'platform_model'    => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    } elseif (preg_match('/ (Galaxy|E[0-9]) Build/', $ua, $matches)) {
        include_once('clientDevices/Samsung.php.inc');
        $infos = array_merge($infos, get_SamsungClientDevice($matches[1]));
    } elseif (preg_match('/(klte)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Samsung',
            'platform_model'    => 'Galaxy S5',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Samsung PC */
    elseif (preg_match('/MASM|MASMJS|SMJB/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Samsung (PC)'
        ));

    /* check Lenovo devices - before Huawei */
    elseif (preg_match('/ (IdeaTab|Yoga|Lenovo|Zuk)[ |_]([A-Z0-9\- ]{2,})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Lenovo.php.inc');
        $infos = array_merge($infos, get_LenovoClientDevice(trim($matches[2])));
    }
    elseif (preg_match('/ (Z2 Plus|Tab2A710F)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Lenovo.php.inc');
        $infos = array_merge($infos, get_LenovoClientDevice(trim($matches[1])));
    }

    /* check Lenovo PCs */
    elseif (preg_match('/MALC|MALCJS|MALEJS|MALN|MALNJS|LCJB|LEN2|LCTE/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  =>'Lenovo (PC)',
        ));

    /* check Huawei - before Sony */
    elseif (($device = _client_isHuaweiDevice($ua)) !== false) {
        $infos = array_merge($infos, get_HuaweiClientDevice($device));
    }

    /* check Kyocera - before Sony */
    elseif (($device = _client_isKyoceraDevice($ua)) !== false) {
        $infos = array_merge($infos, get_KyoceraClientDevice($device));
    }

    /* check OnePlus - to be inserted before Sony */
    elseif (($device = _client_isOnePlusDevice($ua)) !== false) {
        $infos = array_merge($infos, get_OnePlusClientDevice($device));
    }

    /* check SonyEricsson */
    elseif (preg_match('/SonyEricsson([^ \/]+)/', $ua, $matches)) {
        include_once('clientDevices/SonyEricsson.php.inc');
        $infos = array_merge($infos, get_SonyEricssonClientDevice($matches[1]));
    }

    /* check Sony mobiles and tablets */
    elseif (preg_match('/ ([C-I][0-9]{4})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Sony.php.inc');
        $infos = array_merge($infos, get_SonyClientDevice($matches[1]));
    }
    elseif (preg_match('/SO(V3[0-9]|-[0-9]{2}[A-Z])/', $ua, $matches)) {
        include_once('clientDevices/Sony.php.inc');
        $infos = array_merge($infos, get_SonyClientDevice($matches[0]));
    }
    elseif (preg_match('/ (SGP[0-9a-zA-Z]{3,})( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Sony.php.inc');
        $infos = array_merge($infos, get_SonyClientDevice($matches[1]));
    }
    elseif (preg_match('/ (LT28i)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Sony.php.inc');
        $infos = array_merge($infos, get_SonyClientDevice($matches[1]));
    }

    /* check Sony PCs */
    elseif (preg_match('/MASE|MASEJS|MASP|MASPJS|MASA|MASAJS/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  =>'Sony (PC)',
        ));

    /* check Spice Mobility devices */
    elseif (preg_match('/Spice ([A-Z0-9\-]{4,})/i', $ua, $matches)) {
        include_once('clientDevices/SpiceMobility.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_SpiceMobilityClientDevice($model));
    }

    /* check Outikel mobiles */
    elseif (preg_match('/; (K[0-9]|K[0-9]{4,})( [A-zA-Z]*)?( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Oukitel.php.inc');
        $infos = array_merge($infos, get_OukitelClientDevice(trim($matches[1].$matches[2])));
    }

    /* check Energizer mobiles - before Asus */
    elseif (preg_match('/ (P[0-9]{3}S)( Build|\))/U', $ua, $matches)) {
        include_once('clientDevices/Energizer.php.inc');
        $infos = array_merge($infos, get_EnergizerClientDevice(trim($matches[1])));
    } elseif (preg_match('/ Energy[ \-_]?([A-Za-z0-9 ]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Energizer.php.inc');
        $infos = array_merge($infos, get_EnergizerClientDevice(trim($matches[1])));
    }

    /* check Asus mobiles and tablets */
    elseif (preg_match('/ (K|ME|P)([0-9]{2})([A-Z0-9]{1,2})( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Asus.php.inc');
        $infos = array_merge($infos, get_AsusClientDevice(trim($matches[1].$matches[2].$matches[3])));
    } elseif (preg_match('/ (Z?[A-Z][0-9]{3}[C|K|T]{1}L) Build/', $ua, $matches)) {
        include_once('clientDevices/Asus.php.inc');
        $infos = array_merge($infos, get_AsusClientDevice(trim($matches[1])));
    } elseif (preg_match('/ASUS_([A-Z0-9]+)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Asus.php.inc');
        $infos = array_merge($infos, get_AsusClientDevice(trim($matches[1])));
    }elseif (preg_match('/; Transformer ([A-Z0-9]+)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Asus.php.inc');
        $infos = array_merge($infos, get_AsusClientDevice(trim($matches[1])));
    }

    /* check Asus PCs */
    elseif (preg_match('/MAAU|ASJB|ASU2JS|ASU2|NP0[6789]|ASTE/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Asus (PC)',
        ));

    /* check Micromax */
    elseif (preg_match('/Micromax( |_)([^ \/\)]+)/', $ua, $matches)) {
        include_once('clientDevices/Micromax.php.inc');
        $infos = array_merge($infos, get_MicromaxClientDevice($matches[2]));
    }

    /* check ITel */
    elseif (preg_match('/ itel ([^\)\/]*)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Itel.php.inc');
        $infos = array_merge($infos, get_ItelClientDevice($matches[1]));
    }

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
    /* check Xbox One, icons loader */
    elseif (preg_match('/\(Windows Phone 10.0; Android 6.0.1\)/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'Microsoft',
            'platform_model'    => 'Xbox One',
            'platform_type'     => 'computer',
            'platform_format'   => 'desktop',
            'system_title'      => 'Windows',
            'system_version'    => '10',
        ));

    /* check Amazon Kindle */
    elseif (preg_match('/ Kindle\/?([0-9\.]*)/', $ua, $matches))
        /* build info */
        $infos = array_merge($infos, array(
            'platform_company'  => 'Amazon',
            'platform_model'    => 'Kindle',
            'platform_type'     => 'tablet',
            'platform_format'   => 'tablet',
            'browser_title'     => 'Kindle browser',
            'browser_version'   => $matches[1],
        ));
    elseif (preg_match('/ (KF[A-Z]{2,4})( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Amazon.php.inc');
        $infos = array_merge($infos, get_AmazonClientDevice($matches[1]));
    } elseif (preg_match('/ (SD4930UR)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Amazon.php.inc');
        $infos = array_merge($infos, get_AmazonClientDevice($matches[1]));
    }

    /* check HiSense devices : before Acer */
    elseif (preg_match('/( Hisense |HS-)([A-Z0-9a-z _]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/HiSense.php.inc');
        $model = preg_replace('/_/', ' ', $matches[2]);
        $infos = array_merge($infos, get_HiSenseClientDevice($model));
    }

    /* check Cubot devices : before Acer */
    elseif (preg_match('/ Cubot[ _\-]?([A-Za-z0-9\+ _]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Cubot.php.inc');
        $model = trim(preg_replace('/_/', ' ', $matches[1]));
        $infos = array_merge($infos, get_CubotClientDevice($model));
    } elseif (preg_match('/ (GT90) /', $ua, $matches)) {
        include_once('clientDevices/Cubot.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_CubotClientDevice($model));
    }

    /* check Caterpillar mobiles - before Wiko, Acer */
    elseif (preg_match('/ (S[36][0-9])( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Cat.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_CatClientDevice($model));
    } elseif (preg_match('/; CAT([^.]*)( Build|\)|;)/Ui', $ua, $matches)) {
        include_once('clientDevices/Cat.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_CatClientDevice($model));
    }

    /* check Acer devices : before blackview, wiko */
    elseif (preg_match('/ ([EISVZ][0-9]{3}|[EST][0-9]{2}|B[0-9]-[A0-9][0-9]0[A-Z]*)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Acer.php.inc');
        $infos = array_merge($infos, get_AcerClientDevice($matches[1]));
    } elseif (preg_match('/ acer[_| |-]([A-Z][0-9]{3})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Acer.php.inc');
        $infos = array_merge($infos, get_AcerClientDevice($matches[1]));
    } elseif (preg_match('/ (Z2_WVGA_QXH|Z6PLUS|Liquid)/', $ua, $matches)) {
        include_once('clientDevices/Acer.php.inc');
        $infos = array_merge($infos, get_AcerClientDevice($matches[1]));
    }

    /* check Nomu devices - before Wiko */
    elseif (preg_match('/ (s10 pro|s30mini)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Nomu.php.inc');
        $device = strtolower($matches[1]);
        $infos = array_merge($infos, get_NomuClientDevice($device));
    }

    /* check Doogee devices, to be inserted before Xiaomi/Wiko */
    elseif (preg_match('/; (MIX( Lite)?|MIX2|BL5000|S90|X70|X[0-9]0L|X5max_PRO)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Doogee.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_DoogeeClientDevice($model));
    }

    /* check SFR (France) mobiles - before Wiko */
    elseif (preg_match('/(STARTRAIL7) Build/', $ua, $matches)) {
        include_once('clientDevices/SFR.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_SFRClientDevice($model));
    }

    /* check Memup devices - before Wiko */
    elseif (preg_match('/; (SP|SlidePad )([^;\-\)]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Memup.php.inc');
        $model = $matches[2];
        $infos = array_merge($infos, get_MemupClientDevice($model));
    }

    /* check Altice devices - before Wiko */
    elseif (preg_match('/; (SX41|Star)([0-9 ]*)?( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Altice.php.inc');
        $model = $matches[1].trim($matches[2]);
        $infos = array_merge($infos, get_AlticeClientDevice($model));
    }

    /* check Advan devices - before Wiko */
    elseif (preg_match('/ (50[0-9]{2}|S5E_NXT|S50[A-Z])( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Advan.php.inc');
        $infos = array_merge($infos, get_AdvanClientDevice($matches[1]));
    }
    /* check SpreadTrum */
    elseif (preg_match('/SpreadTrum/', $ua, $matches))
        $infos = array_merge($infos, array(
            'platform_company'  => 'SpreadTrum',
            'platform_model'    => '',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));

    /* check Maximus devices */
    elseif (preg_match('/ (MAX908)( Build|\)|;)/', $ua, $matches)) {
        include_once('clientDevices/Maximus.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_MaximusClientDevice($model));
    }

    /* check Alcatel devices */
    elseif (preg_match('/ (Orange KLIF|A460G|[0-9]{4}[A-Z])( Build|\)|;)/', $ua, $matches)) {
        include_once('clientDevices/Alcatel.php.inc');
        $infos = array_merge($infos, get_AlcatelClientDevice($matches[1]));
    } elseif (preg_match('/; Alcatel_(.*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Alcatel.php.inc');
        $infos = array_merge($infos, get_AlcatelClientDevice($matches[1]));
    }

    /* check Lava Iris devices */
    elseif (preg_match('/ (Iris[A-Z0-9\+]+|Z50|A48_8GB|K1plus)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Lava.php.inc');
        $model = strtolower($matches[1]);
        $infos = array_merge($infos, get_LavaClientDevice($model));
    }

    /* check Tecno devices */
    elseif (preg_match('/ Tecno[ |-]?([^;\-\)]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Tecno.php.inc');
        $device = trim($matches[1]);
        $infos = array_merge($infos, get_TecnoClientDevice($device));
    }

    /* check Yezz Andy devices */
    elseif (preg_match('/ (Andy|Yezz)[_| |-]([A-Z0-9\._ ]{2,})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Yezz.php.inc');
        $device = preg_replace('/_/', ' ', $matches[2]);
        $infos = array_merge($infos, get_YezzClientDevice($device));
    }

    /* check Wing devices */
    elseif (preg_match('/ Wing_([A-Za-z0-9]{2,})( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Wing.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_WingClientDevice($model));
    }

    /* check Karbonn devices : before Leagoo */
    elseif (preg_match('/ Karbonn( |_)([A-Z][0-9]{2}) Build/i', $ua, $matches)) {
        include_once('clientDevices/Karbonn.php.inc');
        $infos = array_merge($infos, get_KarbonnClientDevice($matches[2]));
    } elseif (preg_match('/ (Aura|Alfa) ([A-Z][^\)\/]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Karbonn.php.inc');
        $infos = array_merge($infos, get_KarbonnClientDevice($matches[1].' '.$matches[2]));
    }

    /* check Leagoo devices */
    elseif (preg_match('/(Leagoo_| )(Elite|Alfa|Kiicaa|Lead)[ |_|-]?([^\)\/]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Leagoo.php.inc');
        $infos = array_merge($infos, get_LeagooClientDevice($matches[2].' '.$matches[3]));
    }

    /* check Wortmann devices */
    elseif (preg_match('/ (TERRA )?(PAD ?)(100[0-9])( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Wortmann.php.inc');
        $model = $matches[3];
        $infos = array_merge($infos, get_WortmannClientDevice($model));
    }

    /* check QMobile devices */
    elseif (preg_match('/; (A3|LT700)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/QMobile.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_QMobileClientDevice($model));
    }

    /* check Haier devices */
    elseif (preg_match('/ (CDP7TAB4C8|G30) /', $ua, $matches)) {
        include_once('clientDevices/Haier.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_HaierClientDevice($model));
    } elseif (preg_match('/ (HM-G552-FL)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Haier.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_HaierClientDevice($model));
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
    elseif (preg_match('/ (C[M|T][A-Z0-9]{3,4}[A-Z]?)( Build|\))/U', $ua, $matches)) {
        include_once('clientDevices/Carrefour.php.inc');
        $infos = array_merge($infos, get_CarrefourClientDevice($matches[1]));
    }

    /* check Orange */
    elseif (preg_match('/ (Nura|Dive) ([^.]*)( Build|\))/U', $ua, $matches)) {
        include_once('clientDevices/Orange.php.inc');
        $device = $matches[1].' '.$matches[2];
        $infos = array_merge($infos, get_OrangeClientDevice($device));
    } elseif (preg_match('/Orange[ |\-|_]([^.]*)( Build|\))/U', $ua, $matches)) {
        include_once('clientDevices/Orange.php.inc');
        $infos = array_merge($infos, get_OrangeClientDevice($matches[1]));
    }

    /* check Logicom */
    elseif (preg_match('/L-EMENT_?([^.]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Logicom.php.inc');
        $infos = array_merge($infos, get_LogicomClientDevice($matches[1]));
    } elseif (preg_match('/ (M bot Tab [0-9]{3})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Logicom.php.inc');
        $infos = array_merge($infos, get_LogicomClientDevice($matches[1]));
    } elseif (preg_match('/(; Le[_| ][^.]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Logicom.php.inc');
        $infos = array_merge($infos, get_LogicomClientDevice($matches[1]));
    }

    /* check Coolpad devices */
    elseif (preg_match('/; CP([0-9][A-Z0-9_\-]+)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Coolpad.php.inc');
        $infos = array_merge($infos, get_CoolpadClientDevice($matches[1]));
    } elseif (preg_match('/; Coolpad ([A-Z0-9_\-]+)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Coolpad.php.inc');
        $infos = array_merge($infos, get_CoolpadClientDevice($matches[1]));
    }

    /* check Vestel devices */
    elseif (preg_match('/ (Venus_V3_5570) /', $ua, $matches)) {
        include_once('clientDevices/Vestel.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_VestelClientDevice($model));
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
    elseif (preg_match('/MAFS|MAFSJS|FSJB/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  =>'Fujitsu (PC)',
        ));
    }

    /* check Hyrican OEM computers */
    elseif (preg_match('/MANM|MANMJS/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  =>'Hyrican (PC)',
        ));
    }

    /* check Compaq OEM computers */
    elseif (preg_match('/CPDTDF|CPNTDF|CMNTDF|CMNTDFJS|CMDTDF|CMDTDFJS/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  =>'Compaq (PC)',
        ));
    }

    /* check Polaroid devices, to be inserted before Xiaomi */
    elseif (preg_match('/ (MID[0-9A-Z]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Polaroid.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_PolaroidClientDevice($model));
    }

    /* check Umi devices, to be inserted before Xiaomi */
    elseif (preg_match('/ UMI([_ \-][0-9A-Za-z_ \-]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Umi.php.inc');
        $model = trim(preg_replace('/_|-/', ' ', $matches[1]));
        $infos = array_merge($infos, get_UmiClientDevice($model));
    } elseif (preg_match('/ (IRON|Rome|Hammer|eMax|Touch)([ |_])?(Pro|X|S|Mini|4G)?( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Umi.php.inc');
        $model = trim($matches[1].' '.$matches[3]);
        $infos = array_merge($infos, get_UmiClientDevice($model));
    }

    /* check VKWorld devices, to be inserted before Xiaomi */
    elseif (preg_match('/ (VK-?[A-Z0-9\- ]+)( Build|\)|\()/i', $ua, $matches)) {
        include_once('clientDevices/VKWorld.php.inc');
        $infos = array_merge($infos, get_VKWorldClientDevice($matches[1]));
    } elseif (preg_match('/ (Mix Plus)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/VKWorld.php.inc');
        $infos = array_merge($infos, get_VKWorldClientDevice($matches[1]));
    }

    /* check FNF devices, to be inserted before Xiaomi */
    elseif (preg_match('/ (iFive[A-Za-z0-9 _]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/FNF.php.inc');
        $model = trim(preg_replace('/_/', ' ', $matches[1]));
        $infos = array_merge($infos, get_FNFClientDevice($model));
    }

    /* check Xiaomi devices */
    elseif (preg_match('/ (Redmi|MI|Pocophone|Poco|SKR)( |-)?([A-Za-z0-9 ]{1,})( Build|\)| MIUI)/i', $ua, $matches)) {
        include_once('clientDevices/Xiaomi.php.inc');
        $infos = array_merge($infos, get_XiaomiClientDevice($matches[1].' '.$matches[3]));
    } elseif (preg_match('/(HM NOTE 1LTE|2014811)/', $ua, $matches)) {
        include_once('clientDevices/Xiaomi.php.inc');
        $infos = array_merge($infos, get_XiaomiClientDevice(strtolower($matches[1])));
    }

    /* check Iris Sat devices */
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

    /* check Kazam devices */
    elseif (preg_match('/KAZAM_(Trooper_450L)/', $ua, $matches)) {
        include_once('clientDevices/Kazam.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_KazamClientDevice($model));
    }

    /* check Condor devices */
    elseif (preg_match('/(PGN|PHQ|SP|PAM|PFS|TCV|TGW)\-?([0-9]{3}G?)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Condor.php.inc');
        $infos = array_merge($infos, get_CondorClientDevice($matches[1].$matches[2]));
    } elseif (preg_match('/(Griffe|Allure) ([A-Za-z0-9 ]{1,})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Condor.php.inc');
        $infos = array_merge($infos, get_CondorClientDevice($matches[1].' '.$matches[2]));
    }

    /* check Smartisan devices */
    elseif (preg_match('/ (OC|OD|OS|SM|YQ)([0-9]{3})( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Smartisan.php.inc');
        $model = $matches[1].$matches[2];
        $infos = array_merge($infos, get_SmartisanClientDevice($model));
    }

    /* check Gigabyte devices */
    elseif (preg_match('/(GSmart Rey R3)/', $ua, $matches)) {
        include_once('clientDevices/Gigabyte.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_GigabyteClientDevice($model));
    }

    /* check Lyf devices */
    elseif (preg_match('/(LYF\/F[0-9]{2,3}[A-Z])\//', $ua, $matches)) {
        include_once('clientDevices/Lyf.php.inc');
        $infos = array_merge($infos, get_LyfClientDevice($matches[1]));
    }

    /* check Infinix devices */
    elseif (preg_match('/ Infinix[ |-]([^\)]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Infinix.php.inc');
        $infos = array_merge($infos, get_InfinixClientDevice($matches[1]));
    }

    /* check Digital Alpha servers */
    elseif (preg_match('/ (Digital AlphaServer [A-Za-z0-9]*) /', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'Digital Equipment Corporation (PC)',
            'platform_model'    => $model,
        ));
    }

    /* check Vodafone devices */
    elseif (preg_match('/ Vodafone ([A-Za-z0-9]{3}N)( Build|\))/U', $ua, $matches)) {
        include_once('clientDevices/Vodafone.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_VodafoneClientDevice($model));
    } elseif (preg_match('/ (VF[0-9]{3})( Build|\))/U', $ua, $matches)) {
        include_once('clientDevices/Vodafone.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_VodafoneClientDevice($model));
    }

    /* check MobiWire devices */
    elseif (preg_match('/ (Taima) Build/', $ua, $matches)) {
        include_once('clientDevices/MobiWire.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_MobiWireClientDevice($model));
    }

    /* check Oppo devices */
    elseif (preg_match('/ (1201|A37f|A37fw|A1601|F1f|CPH[0-9]{4}|RMX[0-9]{4}|PAFM00)( Build|\))/U', $ua, $matches)) {
        include_once('clientDevices/Oppo.php.inc');
        $infos = array_merge($infos, get_OppoClientDevice($matches[1]));
    } elseif (preg_match('/OPPO ([^.]+) Build/', $ua, $matches)) {
        include_once('clientDevices/Oppo.php.inc');
        $infos = array_merge($infos, get_OppoClientDevice($matches[1]));
    }

    /* check Yotaphone devices */
    elseif (preg_match('/(YD20[0-9]) Build/', $ua, $matches)) {
        include_once('clientDevices/Yotaphone.php.inc');
        $infos = array_merge($infos, get_YotaphoneClientDevice($matches[1]));
    } elseif (preg_match('/ YotaPhone ([0-9]) Build/', $ua, $matches)) {
        include_once('clientDevices/Yotaphone.php.inc');
        $infos = array_merge($infos, get_YotaphoneClientDevice($matches[1]));
    }

    /* check eBest devices */
    elseif (preg_match('/EBEST ([^.]*) Build/', $ua, $matches)) {
        $model = trim($matches[1]);
        $infos = array_merge($infos, array(
            'platform_company'  => 'eBest',
            'platform_model'    => $model,
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
    }

    /* check Vivo devices */
    elseif (preg_match('/; ([0-9]{4})( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Vivo.php.inc');
        $infos = array_merge($infos, get_VivoClientDevice($matches[1]));
    } elseif (preg_match('/; vivo (.*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Vivo.php.inc');
        $infos = array_merge($infos, get_VivoClientDevice($matches[1]));
    } elseif (preg_match('/; (V1928a)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Vivo.php.inc');
        $infos = array_merge($infos, get_VivoClientDevice($matches[1]));
    }

    /* check Sharp devices */
    elseif (preg_match('/(SH\-[0-9]{2}[A-Z]|FS8002)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Sharp.php.inc');
        $infos = array_merge($infos, get_SharpClientDevice($matches[1]));
    }

    /* check Crosscall devices */
    elseif (preg_match('/(Action|Trekker|Odyssey|Core)(\-|_| )([0-9\ A-Z]+)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Crosscall.php.inc');
        $infos = array_merge($infos, get_CrosscallClientDevice(strtolower($matches[1].'-'.$matches[3])));
    }

    /* check SPC devices, before ZTE */
    elseif (preg_match('/; (Z2)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/SPC.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_SPCClientDevice($device));
    }

    /* check ZTE devices */
    elseif (preg_match('/; ?ZTE ([a-zA-Z0-9 ]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/ZTE.php.inc');
        $infos = array_merge($infos, get_ZTEClientDevice($matches[1]));
    } elseif (preg_match('/ (Z[0-9]{1,3}[A-Z]{2}?)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/ZTE.php.inc');
        $infos = array_merge($infos, get_ZTEClientDevice($matches[1]));
    }

    /* check Ampe devices */
    elseif (preg_match('/ (A[0-9]{2}[A-Z]?)([\-| ][0-9A-ZA-Z ]*)?( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Ampe.php.inc');
        $device = $matches[1].$matches[2];
        $infos = array_merge($infos, get_AmpeClientDevice($device));
    }

    /* check IMO devices */
    elseif (preg_match('/ IMO_([a-zA-Z0-9]*) Build/', $ua, $matches)) {
        include_once('clientDevices/IMO.php.inc');
        $infos = array_merge($infos, get_IMOClientDevice($matches[1]));
    }

    /* check Lemon devices */
    elseif (preg_match('/ Lemon ([a-zA-Z0-9\- ]*)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Lemon.php.inc');
        $infos = array_merge($infos, get_LemonClientDevice($matches[1]));
    }

    /* check Evertek devices */
    elseif (preg_match('/ (Ever[a-zA-Z0-9\- ]*)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Evertek.php.inc');
        $infos = array_merge($infos, get_EvertekClientDevice($matches[1]));
    }

    /* check Essential devices */
    elseif (preg_match('/ (PH-1) Build/', $ua, $matches)) {
        include_once('clientDevices/Essential.php.inc');
        $infos = array_merge($infos, get_EssentialClientDevice($matches[1]));
    }

    /* check Digicel devices */
    elseif (preg_match('/(DL[0-9A-Za-z ]+)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Digicel.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_DigicelClientDevice($model));
    }

    /* check Meizu devices */
    elseif (preg_match('/ (MZ-[A-Za-z0-9_ ]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Meizu.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_MeizuClientDevice($model));
    } elseif (preg_match('/ Meizu[ |_]([A-Za-z0-9_ ]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Meizu.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_MeizuClientDevice($model));
    } elseif (preg_match('/ (MX[0-9])( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Meizu.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_MeizuClientDevice($model));
    } elseif (preg_match('/ (M3s|Note9|m2 note)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Meizu.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_MeizuClientDevice($model));
    } elseif (preg_match('/ (PRO [0-9][.*]*)( Build|\))/U', $ua, $matches)) {
        include_once('clientDevices/Meizu.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_MeizuClientDevice($model));
    }

    /* check Symphony devices */
    elseif (preg_match('/ ([iEHG][0-9]{2,3}) Build/i', $ua, $matches)) {
        include_once('clientDevices/Symphony.php.inc');
        $model = trim($matches[1]);
        $infos = array_merge($infos, get_SymphonyClientDevice($model));
    }

    /* check Gionee devices */
    elseif (preg_match('/ (P8W|M5_lite|F103 Pro)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Gionee.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_GioneeClientDevice($model));
    }

    /* check Konrow devices */
    elseif (preg_match('/ (BIGCOOL|Just5)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Konrow.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_KonrowClientDevice($model));
    }

    /* check HomTom devices */
    elseif (preg_match('/ (HT[0-9]{2})( [A-Z]*) Build/i', $ua, $matches)) {
        include_once('clientDevices/HomTom.php.inc');
        $model = $matches[1].trim($matches[2]);
        $infos = array_merge($infos, get_HomTomClientDevice($model));
    }

    /* check Vernee devices */
    elseif (preg_match('/ (Apollo|Thor|Mars)( [A-Za-z0-9]*)?( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Vernee.php.inc');
        $model = $matches[1].$matches[2];
        $infos = array_merge($infos, get_VerneeClientDevice($model));
    } elseif (preg_match('/ vernee_([[A-Za-z0-9]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Vernee.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_VerneeClientDevice($model));
    }

    /* check Ken Xin Da devices */
    elseif (preg_match('/ (Three_Proofings_W9)/i', $ua, $matches)) {
        include_once('clientDevices/KenXinDa.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_KenXinDaClientDevice($model));
    }

    /* check Qilive devices */
    elseif (preg_match('/ (Q[0-9]+S[A-Za-z0-9]+)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Qilive.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_QiliveClientDevice($model));
    }

    /* check Quantum devices */
    elseif (preg_match('/ Quantum ([^\)]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Quantum.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_QuantumClientDevice($model));
    }

    /* check Verykool devices */
    elseif (preg_match('/ (LUNA_II)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Verykool.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_VerykoolClientDevice($model));
    }

    /* check Ulefone devices */
    elseif (preg_match('/ (s10_pro|Armor_6)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Ulefone.php.inc');
        $device = strtolower($matches[1]);
        $infos = array_merge($infos, get_UlefoneClientDevice($device));
    }

    /* check Neffos devices */
    elseif (preg_match('/ Neffos[ |_]([^\)]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Neffos.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_NeffosClientDevice($device));
    }

    /* check T-Mobile devices */
    elseif (preg_match('/ T-Mobile[ |_]([^\)]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/T-Mobile.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_TMobileClientDevice($device));
    }

    /* check i.safe devices */
    elseif (preg_match('/ (IS[0-9_]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Isafe.php.inc');
        $device = trim($matches[1]);
        $infos = array_merge($infos, get_IsafeClientDevice($device));
    }

    /* check It Works devices */
    elseif (preg_match('/ (TM[0-9]{3,4})([A-Z]{3})?( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/ItWorks.php.inc');
        $device = trim($matches[1].$matches[2]);
        $infos = array_merge($infos, get_ItWorksClientDevice($device));
    }

    /* check Torque devices */
    elseif (preg_match('/ (Edge)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Torque.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_TorqueClientDevice($model));
    }

    /* check Wieppo devices */
    elseif (preg_match('/ Wieppo ([^\)]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Wieppo.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_WieppoClientDevice($model));
    }

    /* check Umidigi devices */
    elseif (preg_match('/; (Umidigi )?(C Note[ ]{0,1}[0-9]*|[A|S|Z][0-9]*)[ |\-|_]?(Pro|Lite)?( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Umidigi.php.inc');
        $model = ucwords(strtolower($matches[2].($matches[3] != '' ? ' '.$matches[3] : '')));
        $infos = array_merge($infos, get_UmidigiClientDevice($model));
    } elseif (preg_match('/; (Power)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Umidigi.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_UmidigiClientDevice($model));
    }

    /* check Mecool devices */
    elseif (preg_match('/; (M8S PRO L)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Mecool.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_MecoolClientDevice($model));
    }

    /* check Cube devices */
    elseif (preg_match('/; (X1)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Cube.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_CubeClientDevice($model));
    }

    /* check Xtreamer mobiles */
    elseif (preg_match('/; (Xtreamer )?(Bang|Joyz|Aiki\-[0-9]S?)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Xtreamer.php.inc');
        $model = $matches[2];
        $infos = array_merge($infos, get_XtreamerClientDevice($model));
    /* check Xtreamer tablets */
    } elseif (preg_match('/; (X[0-9]\-[A-Z0-9]{2,4})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Xtreamer.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_XtreamerClientDevice($model));
    }

    /* check Wileyfox devices */
    elseif (preg_match('/; Wileyfox (.*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Wileyfox.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_WileyfoxClientDevice($model));
    }

    /* check American Network Solutions devices */
    elseif (preg_match('/; (UL40)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/AmericanNetworkSolutions.php.inc');
        $model = $matches[1];
        $infos = array_merge($infos, get_AmericanNetworkSolutionsClientDevice($model));
    }

    /* check Intex devices */
    elseif (preg_match('/; (Aqua 5.5 VR)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Intex.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_IntexClientDevice($device));
    }

    /* check Krüger & Matz devices */
    elseif (preg_match('/ (FLOW)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/KrugerMatz.php.inc');
        $device = strtolower($matches[1]);
        $infos = array_merge($infos, get_KrugerMatzClientDevice($device));
    }

    /* check Hyundai devices */
    elseif (preg_match('/; (G25524K)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Hyundai.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_HyundaiClientDevice($device));
    }

    /* check Dexp devices */
    elseif (preg_match('/; (Ixion [^.]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Dexp.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_DexpClientDevice($device));
    }

    /* check Vertex devices */
    elseif (preg_match('/; (Impress_[^.]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Vertex.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_VertexClientDevice($device));
    }

    /* check Danew devices */
    elseif (preg_match('/; (Dslide1013QC_v2|Konnect_[0-9]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Danew.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_DanewClientDevice($device));
    }

    /* check Chuwi devices */
    elseif (preg_match('/; (Hi10 pro)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Chuwi.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_ChuwiClientDevice($device));
    }

    /* check Xtouch devices */
    elseif (preg_match('/; Xtouch ([^.]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Xtouch.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_XtouchClientDevice($device));
    }

    /* check MPMan devices */
    elseif (preg_match('/; (MP[^.]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/MPMan.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_MPManClientDevice($device));
    }

    /* check Timmy devices */
    elseif (preg_match('/; (M12)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Timmy.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_TimmyClientDevice($device));
    }

    /* check Öwn devices */
    elseif (preg_match('/; (FUN_VALUE)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Own.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_OwnClientDevice($device));
    }

    /* check Nvidia devices */
    elseif (preg_match('/; (SHIELD .*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Nvidia.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_NvidiaClientDevice($device));
    }

    /* check Fairphone devices */
    elseif (preg_match('/; (FP[0-9]U?)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Fairphone.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_FairphoneClientDevice($device));
    }

    /* check Echo devices */
    elseif (preg_match('/; (Stellar 4G)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Echo.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_EchoClientDevice($device));
    }

    /* check LeEco devices */
    elseif (preg_match('/; (LE ?X[0-9]+)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/LeEco.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_LeEcoClientDevice($device));
    }

    /* check Orbic devices */
    elseif (preg_match('/; (RC5[0-9]{2}L)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Orbic.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_OrbicClientDevice($device));
    }

    /* check Palm devices */
    elseif (preg_match('/; (PVG100)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Palm.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_PalmClientDevice($device));
    }

    /* check Poptel devices */
    elseif (preg_match('/; (P9000_MAX)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Poptel.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_PoptelClientDevice($device));
    }

    /* check Philips devices */
    elseif (preg_match('/\(Philips\, (PFS5803)\,/Ui', $ua, $matches)) {
        include_once('clientDevices/Philips.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_PhilipsClientDevice($device));
    }

    /* check Artizlee devices */
    elseif (preg_match('/; (ATL-[0-9]{2}[A-Z]?)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Artizlee.php.inc');
        $device = $matches[1];
        $infos = array_merge($infos, get_ArtizleeClientDevice($device));
    }

    /* check Blackview devices */
    elseif (preg_match('/; (BV|P)([a-zA-Z0-9\-_]*)( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Blackview.php.inc');
        $device = preg_replace('/-|_/', ' ', $matches[2]);
        $infos = array_merge($infos, get_BlackviewClientDevice($device));
    }

    /* check Wiko */
    elseif (preg_match('/; (barry|birdy|bloom|cink|darkfull|darkmoon|darkside|fever|fizz|freddy|getaway|goa|harry|highway|iggy|jerry|jimmy|kenny|kite|lenny|ozzy|pulp|rainbow|ridge|robby|selfy|slide|stairway|star|sublim|sunny|sunset|tommy|u feel|u pulse|view|violet|wax|wim)([A-Za-z0-9 _]*)?( Build|\))/i', $ua, $matches)) {
        $model = trim(strtolower($matches[1].(isset($matches[2])?$matches[2]:'')));
        include_once('clientDevices/Wiko.php.inc');
        $infos = array_merge($infos, get_WikoClientDevice($model));
    } elseif (preg_match('/ (W[_\-][A-Z][0-9]{3}[A-Z]?)( Build|\))/i', $ua, $matches)) {
        $model = trim(strtolower($matches[1]));
        include_once('clientDevices/Wiko.php.inc');
        $infos = array_merge($infos, get_WikoClientDevice($model));
    } elseif (preg_match('/ (W\-[A-Z][0-9]{3}\-[A-Z]{3})( Build|\))/Ui', $ua, $matches)) {
        $model = trim(strtolower($matches[1]));
        include_once('clientDevices/Wiko.php.inc');
        $infos = array_merge($infos, get_WikoClientDevice($model));
    } elseif (preg_match('/ ([S|V][0-9]{2}[A-Za-z0-9\(\)]*)( Build|\))/i', $ua, $matches)) {
        $model = trim(strtolower($matches[1]));
        include_once('clientDevices/Wiko.php.inc');
        $infos = array_merge($infos, get_WikoClientDevice($model));
    }

    /* check Phh-Treble generic rom flashed device devices */
    elseif (preg_match('/ Phh-Treble(.*)( Build|\))/Ui', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'platform_company'  => 'Flashed mobile with Phh-Treble generic ROM.',
            'platform_model'    => '',
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ));
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

        /* check gen os with notified version (before Android/Macintosh) */
        elseif (preg_match('/(SymbianOS|webOS|KAIOS|Bada|Haiku|Tizen|NetCast|_TV_MT[0-9]{4})(?:\/| )?(R?[0-9][a-z0-9\._]*)?/i', $ua, $matches)) {
            $rep = array(
                'SymbianOS' => array('platform_type' => 'handheld', 'platform_format' => 'handheld',),
                'KAIOS'     => array('system_title' => 'KaiOS', 'platform_type' => 'handheld', 'platform_format' => 'handheld'),
                'Bada'      => array('platform_company' => 'Samsung', 'platform_type' => 'handheld', 'platform_format' => 'handheld',),
                'Haiku'     => array('platform_company' => 'PC', 'platform_type' => 'computer', 'platform_format' => 'desktop'),
                'Tizen'     => array('platform_company' => 'Samsung', 'platform_type' => 'tvset', 'platform_format' => 'desktop'),
                'NetCast'   => array('platform_company' => '',  'platform_type' => 'tvset', 'platform_format'   => 'desktop',),
                'Saphi'     => array('platform_company' => 'Philips', 'system_title' => 'Saphi', 'platform_type' => 'tvset', 'platform_format'   => 'desktop',),
            );
            if (preg_match('/^_TV_MT/i', $matches[1], $matches2))
                $system = 'Saphi';
            else
                $system = $matches[1];

            if (isset($matches[2]))
                $version = $matches[2];
            elseif (strtolower($system) == 'netcast' and preg_match('/ SmartTV\/([0-9\.]*)?/i', $ua, $matches2))
                $version = $matches2[1];
            else
                $version = '';
            $infos = array_merge($infos, array(
                    'system_title'      => $system,
                    'system_version'    =>  $version,
                ),
                isset($rep[$system]) ? $rep[$system] : array()
            );
        }

        /* check Android */
        elseif (preg_match('/(Android|Adr)[; \/]*([0-9\.]*)?/', $ua, $matches)) {
            /* check version */
            $version = isset($matches[2])?$matches[2]:'';

            $infos = array_merge(array(
                'platform_type'     => (preg_match('/tablet/i',$ua) ? 'tablet' : 'handheld'),
                'platform_format'   => (preg_match('/tablet/i',$ua) ? 'tablet' : 'handheld'),
                'system_title'      => 'Android',
                'system_version'    => $version,
                ),
                $infos
            );
        }

        /* check Macintosh */
        elseif (preg_match('/(?:Intel |PPC |)Mac OS X( Mach-O| [0-9\._]*|)/i', $ua, $matches)) {
            /* check version */
            $version = ($matches[1]!=' Mach-O')?substr(str_replace('_','.',$matches[1]), 1):'';

            /* build info */
            $infos = array_merge($infos, array(
                'platform_company'  => 'Apple',
                'platform_model'    => 'Macintosh',
                'platform_type'     => 'computer',
                'platform_format'   => 'desktop',
                'system_title'      => version_compare ($version, '10.12') >= 0 ? 'macOS' : 'Mac OS X',
                'system_version'    => $version,
            ));
        } elseif (preg_match('/ Darwin\/([0-9\.]*) \(x86_64\)/i', $ua, $matches)) {
            /* check version */
            $version = $matches[1];
            $version = explode('.', $version);
            $version = '10.'.((int)$version[0]-4); //.'.'.$version[1];

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

        /* check determined linux os */
        elseif (preg_match('/(Debian|Ubuntu|DragonFly|SUSE|Slackware|CentOS|Fedora|Kubuntu|Edubuntu|Xubuntu|Gentoo|Red Hat|Mint|Mandriva|CrOS|Arch ?Linux|Caldera Systems OpenLinux|Sailfish|Raspbian)/', $ua, $matches)) {
            $rep = array(
                'CrOS'      => array('system_title'     => 'Chrome OS (Linux)',),
                'Sailfish'  => array('platform_company' => '',  'system_title' => 'Sailfish OS (Linux)', 'platform_type' => 'handheld', 'platform_format' => 'handheld',),
            );
            $infos = array_merge(array(
                'platform_company'  => 'PC',
                'platform_model'    => '',
                'platform_type'     => 'computer',
                'platform_format'   => 'desktop',
                'system_title'      => ucwords($matches[1]).' (Linux)',
                'system_version'    => '',
                ),
                isset($rep[$matches[1]])?$rep[$matches[1]]:array()
            );
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
                'SymbOS'        => array('platform_company' => '',      'system_title' => 'SymbianOS',      'platform_type' => 'handheld', 'platform_format'   => 'handheld',),
                'PalmSource'    => array('platform_company' => 'Palm',  'system_title' => 'PalmOS',         'platform_type' => 'handheld', 'platform_format'   => 'handheld',),
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

            /* load version */
            $v = $matches[1];
            if (substr($v, 0, 1) == ' ') $v = trim(substr($v, 0, 7));
            $version = isset($w[$v])?$w[$v]:$v;

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

    /* check system and version */
    if (isset($infos['system_title']) and isset($infos['system_version']) and _client_checkSoftwareIsFake('system', $infos['system_title'], $infos['system_version']))
        return $fake;

    /*** check browser ***/

    /* check opera mini */
    if (preg_match('/Opera Mini\/([0-9]+\.[0-9]+)/', $ua, $matches))
        $infos = array_merge(array(
            'browser_title'     => 'Opera Mini',
            'browser_version'   => $matches[1],
            'platform_type'     => 'handheld',
            'platform_format'   => 'handheld',
        ), $infos);

    /* check opera */
    elseif (preg_match('/Opera(?:\/| )?([a-z0-9\._]*)?/i', $ua, $matches)) {
        if (preg_match('/Version\/([0-9\.]*)/', $ua, $matches2)) {
             $infos = array_merge(array(
                'browser_title'     => 'Opera',
                'browser_version'   => $matches2[1],
            ), $infos);
        } else {
            $infos = array_merge(array(
                'browser_title'     => 'Opera',
                'browser_version'   => $matches[1],
            ), $infos);
        }
    }

    /* check unsmartly written browser, case sensitive */
    elseif (preg_match('/ (SE )(?:\/| )?([a-z0-9\._]*)?/', $ua, $matches)) {
        $rep = array('SE '=>'Sogou Explorer');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => isset($matches[2])?$matches[2]:'',
        ));
    }

    /* check unsmartly written browser, non case sensitive */
    elseif (preg_match('/(Maxthon|Opera|webissimo|NintendoBrowser|Acoo ?Browser|Deepnet Explorer|Avant Browser|BrowseX|OffByOne|KKman|LBBROWSER|Maemo Browser|BIDUBrowser|UBrowser|Airmail|EmbeddedWB|DX-Browser|Links|Sputnik|Instagram|Microsoft Outlook|Chromeless|Lunascape|JuziBrowser|LinkedInApp|Brave|360SE)(?:\/| )?([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array('BIDUBrowser'=>'Baidu Brower', 'AcooBrowser' => 'Acoo Browser', 'EmbeddedWB'=>'Delphi Embedded Web Browser', 'LBBROWSER'=>'Liebao', 'LinkedInApp'=>'LinkedIn App', '360SE'=>'360Safe');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => isset($matches[2])?$matches[2]:'',
        ));
    }

    /* check L3 Chrome/Safari/Firefox/Explorer compatible browsers, to be tested before usual browsers */
    elseif (preg_match('/(MicroMessenger|ArcticFox)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array('MicroMessenger' => 'WeChat',);
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]]) ? $rep[$matches[1]] : $matches[1],
            'browser_version'   => isset($matches[2]) ? $matches[2] : '',
        ));
    }

    /* check L2 Chrome/Safari/Firefox/Explorer compatible browsers, to be tested before usual browsers */
    elseif (preg_match('/(Yowser|MQQBrowser|Goanna|DingTalk)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array('MQQBrowser'=>'Mobile QQBrowser');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => isset($matches[2])?$matches[2]:'',
        ));
    }

    /* check Firefox compatible browser, using Firefox version */
    elseif (preg_match('/ Waterfox\) Gecko\/([0-9]{8}) Firefox\/([0-9a-zA-z\.]+)/', $ua, $matches)) {
        $infos = array_merge($infos, array(
            'browser_title'     => 'Waterfox',
            'browser_version'   => isset($matches[2])?$matches[2]:'',
        ));
    }

    /* check Chrome compatible browser, using Chrome version */
    elseif (preg_match('/ Chrome\/([a-z0-9\.]*) (.*) (TwitterAndroid)/Ui', $ua, $matches)) {
        $rep = array('TwitterAndroid'=>'Twitter');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[3]]) ? $rep[$matches[3]] : $matches[3],
            'browser_version'   => $matches[1],
        ));
    }

    /* check Chrome/Safari/Firefox/Explorer compatible browsers, with specific Version */
    elseif (preg_match('/ Version\/([a-z0-9\._]*)(.*) (Epiphany)/i', $ua, $matches)) {
        $rep = array();
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[3]])?$rep[$matches[3]]:$matches[3],
            'browser_version'   => isset($matches[1])?$matches[1]:'',
        ));
    }

    /* check Chrome/Safari/Firefox/Explorer compatible browsers, with specific details */
    elseif (preg_match('/(Viera|WebView)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array(
            'Viera'   => array('browser_title'=>'Viera', 'platform_type'     => 'tvset'),
            'WebView' => array('browser_title'=>'Android WebView', 'system_title'=>'Android', 'system_version'=>'', 'platform_company'=> '', 'platform_model' => '', 'platform_type' => 'handheld', 'platform_format' => 'handheld'),
        );
        $infos = array_merge($infos, array(
            'browser_title'     => isset($matches[1])?$matches[1]:'',
            'browser_version'   => isset($matches[2])?$matches[2]:'',
            ), (isset($rep[$matches[1]])?$rep[$matches[1]]:array())
        );
    }

    /* check Facebook apps */
    elseif (preg_match('#(FBAN|FB_IAB)/([^;]*);([^.]*)(FBAV/[0-9\.]*)?;#i', $ua, $matches)) {
        $rep = array('FBIOS'=>'Facebook App', 'FB4A'=>'Facebook App', 'MessengerForiOS'=>'Facebook Messenger', 'Orca-Android'=>'Facebook Messenger');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[2]]) ? $rep[$matches[2]] : 'Unknown Facebook App ('.$matches[2].')',
            'browser_version'   => isset($matches[4]) ? substr($matches[4], 5) : '',
        ));
    }

    /* check Chrome/Safari/Firefox/Explorer compatible browsers, to be tested before usual browsers */
    elseif (preg_match('/(YaBrowser|OPR|IceDragon|Dragon|CriOS|Adventurer|Sleipnir|BoBrowser|Dolfin|ChromePlus|Phoenix|Shiretoko|NS8|MiuiBrowser|SamsungBrowser\/CrossApp|SamsungBrowser|Vivaldi|Qt|Iceweasel|Puffin|Firebird|FBAV|FBSV|app-ipad-CoteMaison|QQBrowser|PaleMoon|Arora|Edge|Cheshire|Getter|Dooble|amaya|Roccat|QupZilla|MMS|Iron|ACHEETAHI|OPiOS|Beonex|LibertyBrowser|LinkedIn|SeaMonkey|Cyberfox|Focus|Fennec|K-Meleon|CoolNovo|QuickLook|GSA|Electron|NG|FxiOS|FocusiOS|Lotus-Notes|Chimera|Epiphany|Iridium|HeadlessChrome|QwantiOS|QwantBrowser|QwantBrowser Firefox|QwantMobile|Blazer|TenFourFox|Silk|SailfishBrowser|coc_coc_browser|MZBrowser|2345Explorer|Kinza|WebPositive|Avast|VivoBrowser|Slimjet|Cornowser|baiduboxapp|Mint Browser|EdgA|Edg|EdgiOS|AVG|Station|OPT|Waterfox|OppoBrowser|chromeframe|UR|QtWebEngine|handyCafeCln|Thunderbird|MxBrowser|mCent|PureBrowser|Valve Steam GameOverlay|Midori|HistoryHound|TO-Browser|K-Ninja|Kapiko|Kazehakase|eM Client|Mb2345Browser|LieBaoFast|Whale|ADG|Light|jp.co.yahoo.ipn.appli|HeyTapBrowser)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
        $rep = array('OPR'=>'Opera', 'CriOS'=>'Chrome', 'Dragon'=>'IceDragon', 'NS8'=>'Netscape', 'Firebird'=>'Thunderbird', 'FBAV'=>'Facebook App', 'FBSV'=>'Facebook App', 'app-ipad-CoteMaison'=>'C&ocirc;t&eacute; Maison App', 'amaya'=>'Amaya', 'MMS'=>'Opera Neon', 'ACHEETAHI'=>'CM Browser', 'OPiOS'=>'Opera mini', 'Focus'=>'Firefox Focus', 'GSA'=>'Google Search App', 'NG'=>'Browser NG', 'FxiOS'=>'Firefox', 'FocusiOS'=>'Firefox Focus', 'Lotus-Notes'=>'Lotus Notes', 'QwantiOS'=>'Qwant', 'QwantBrowser'=>'Qwant', 'QwantBrowser Firefox'=>'Qwant', 'QwantMobile' => 'Qwant', 'Blazer'=> 'Palm Blazer', 'SailfishBrowser' => 'Sailfish Browser', 'coc_coc_browser'=>'C&ocirc;c c&ocirc;c', 'MZBrowser' => 'Meizu Browser', 'Avast' => 'Avast Browser', 'VivoBrowser' => 'Vivo Browser', 'baiduboxapp' => 'Baidu Search App', 'EdgA' => 'Edge', 'Edg' => 'Edge', 'EdgiOS'=>'Edge', 'AVG'=>'AVG Secure Browser', 'OPT'=>'Opera Touch', 'chromeframe'=>'Internet Explorer/Chrome Frame', 'UR'=>'UR Browser', 'handyCafeCln'=>'HandyCafe', 'TO-Browser'=>'t-online.de Browser', 'K-Ninja'=>'K-Ninja Samourai', 'Mb2345Browser'=>'2345 Browser', 'ADG'=>'AOL Desktop', 'jp.co.yahoo.ipn.appli'=>'Yahoo Japan App', 'HeyTapBrowser'=>'HeyTap Browser');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]]) ? $rep[$matches[1]] : $matches[1],
            'browser_version'   => isset($matches[2]) ? $matches[2] : '',
        ));
    }

    /* check no version written browser */
    elseif (preg_match('/(HeadlessChrome|Iron|Advanced Browser|Magic Browser|Pinterest|Sunrise|Keepsafe Browser)/', $ua, $matches)) {
        $rep = array();
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
        ));
    }

    /* check some other browsers */
    elseif (preg_match('/(TencentTraveler)/i', $ua, $matches)) {
        $rep = array('TencentTraveler'=>'TT Explorer');
        $infos = array_merge($infos, array(
            'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
            'browser_version'   => '',
        ));
    }

    /* check ecosia browser */
    elseif (preg_match('/\(Ecosia[^@]*@([0-9\.]*)\)/i', $ua, $matches)) {
        $rep = array('TencentTraveler'=>'TT Explorer');
        $infos = array_merge($infos, array(
            'browser_title'     => 'Ecosia',
            'browser_version'   => isset($matches[1]) ? $matches[1] : '',
        ));
    }

    /* check gen computer browsers */
    elseif (preg_match('/(Chromium|Netscape|Camino|Minefield|Fennec|Firefox|Galeon|iCab|Konqueror|IEMobile|Shiira|NetNewsWire|Symphony|Lynx|Crazy Browser|UCBrowser|GoBrowser|Cobra|ELinks|HotJava|Tor Browser|Dillo|FortiMail|VSE|MultiZilla|UCWEB|Otter|Netbox|AvantGo|NetFront|WhatsApp|Dalvik|Snapchat|ManicTime)(?:\/| )?([a-z0-9\._]*)/i', $ua, $matches)) {
        $rep = array('VSE'=>'VSE Link Tester', 'UCWEB' => 'UC Browser', 'NetFront' => 'Access NetFront');
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
    elseif (preg_match('/Version\/([a-z0-9\._]*)( Mobile[\/0-9A-Z]*)? Safari\//', $ua, $matches)) {
        if ($infos['system_title'] == 'Android')
            $infos = array_merge(array(
                'browser_title'     => 'Chrome'.(isset($matches[2]) ? ' Mobile' : ''),
                'browser_version'   => str_replace('_','.',$matches[1])
                ), $infos
            );
        else
            $infos = array_merge(array(
                'browser_title'     => 'Safari'.(isset($matches[2]) ? ' Mobile' : ''),
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

    /* check Apple software over CFNetwork */
    elseif (preg_match('/^([A-Za-z0-9%]*)\/[0-9\.]* CFNetwork\//', $ua, $matches)) {
        $app = array('MobileSafari' => 'Safari');
        $infos = array_merge(array(
            'browser_title'     => isset($app[$matches[1]]) ? $app[$matches[1]] : urldecode($matches[1]),
            'browser_version'   => '',
            ), $infos
        );
    }

    /* check undeterminated safari version */
    elseif (preg_match('/(Safari|AppleWebKit)/', $ua, $matches)) {
        if (isset($infos['system_title']) and $infos['system_title'] == 'Android') {
            /* Check for version */
            if (preg_match('/Version\/([0-9\.]*)/', $ua, $matches2))
                $version = $matches2[1];
            else
                $version = '';

            $infos = array_merge(array(
                'browser_title'     => 'Android browser',
                'browser_version'   => $version,
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
    elseif (preg_match('/MSIE ?([a-z0-9\._]*)( |;|\,|\-|\))/', $ua, $matches))
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
    if (isset($infos['browser_title']) and isset($infos['browser_version']) and _client_checkSoftwareIsFake('browser', $infos['browser_title'], $infos['browser_version']))
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
    $detectionPattern = string_escape4Regex($detectionPattern);
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
    $detectionPattern = string_escape4Regex($detectionPattern);
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

/* Tool methods */

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
    $detectionPattern = string_escape4Regex($detectionPattern);
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
    $detectionPattern = string_escape4Regex($detectionPattern);
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

/* Unknown bots methods */

/**
 * Return unknown index if unknown.
 * @param string $ua
 * @return mixed
 */
function client_checkIsUnknown($ua=false) {
    /* get user agent */
    if (!$ua) $ua = client_getUserAgent();

    /* load known unknowns */
    $knownUnknowns = client_getKnownUnknowns();

    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownUnknowns));
    $detectionPattern = string_escape4Regex($detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match($detectionPattern, strtolower($ua), $result))
        return $result[0];
    return false;
}

/**
 * Return unknown info if unknown.
 * @param string $unknown
 * @return mixed
 */
function client_getUnknownInfos($unknown='') {
    $knownUnknowns = client_getKnownUnknowns();

    if (isset($knownUnknowns[$unknown]))
        return $knownUnknowns[$unknown];
    return array();
}

/**
 * Return unknown info from user agent.
 * @param string $ua
 * @return mixed
 */
function client_getUnknownInfosFromUserAgent($ua='') {
    $knownUnknowns = client_getKnownUnknowns();

    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownUnknowns));
    $detectionPattern = string_escape4Regex($detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match($detectionPattern, strtolower($ua), $result))
        return $knownUnknowns[$result[0]];
    return false;
}

/**
 * Return given known unknown list.
 * @return array
 */
function client_getKnownUnknowns() {
    include_once('clientBots/Unknowns.php.inc');
    return _client_getKnownUnknowns();
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
    client_loadKnownGenerics();
    $knownGenerics = _client_getKnownGenericsL1();

    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownGenerics));
    $detectionPattern = string_escape4Regex($detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match ( $detectionPattern, strtolower($ua), $result))
        return $result[0];

    /* load known generic agents */
    $knownGenerics = _client_getKnownGenericsL2();

    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownGenerics));
    $detectionPattern = string_escape4Regex($detectionPattern);
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
    /* load known generic agents */
    client_loadKnownGenerics();
    $knownGenerics = _client_getKnownGenericsL1();

    if (isset($knownGenerics[$generic]))
        return $knownGenerics[$generic];

    /* load known generic agents */
    $knownGenerics = _client_getKnownGenericsL2();

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

    /* load known generic agents */
    client_loadKnownGenerics();
    $knownGenerics = _client_getKnownGenericsL1();

    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownGenerics));
    $detectionPattern = string_escape4Regex($detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match ( $detectionPattern, strtolower($ua), $result))
        return $knownGenerics[$result[0]];

    /* load known generic agents */
    $knownGenerics = _client_getKnownGenericsL2();

    /* build detection pattern */
    $detectionPattern = implode('|', array_keys($knownGenerics));
    $detectionPattern = string_escape4Regex($detectionPattern);
    $detectionPattern = '/'.$detectionPattern.'/i';

    /* start detection and return result */
    if (preg_match ( $detectionPattern, strtolower($ua), $result))
        return $knownGenerics[$result[0]];
    return false;
}

/**
 * Load known web generic library lists.
 * @return void
 */
function client_loadKnownGenerics() {
    include_once('clientBots/Generics.php.inc');
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
    $detectionPattern = string_escape4Regex($detectionPattern);
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
    $detectionPattern = string_escape4Regex($detectionPattern);
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

    if (preg_match('#^Mozilla[/| ][0-9][.|,][0-9]$#i', $ua))
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

    /* fake russian spammer */
    if (preg_match('#Mozilla/4.0 \(compatible; MSIE 5.0; Windows NT; DigExt\)#i', $ua))
        return $fake;

    /* fake russian spammer */
    if (preg_match('#Mozilla/4.0 \(compatible; MSIE 6.0; AOL 9.0; Windows NT 5.1\)#i', $ua))
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
    if (preg_match('#^MSDN SurfBear$#i', $ua))
        return $fake;

    /* fake request with ' around */
    if (preg_match('#^\'(.*)\'$#', $ua))
        return $fake;

    /* fake requests from 80.169.91.26 */
    if (preg_match('#-[0-9]{7}$#', $ua))
        return $fake;

    /* badly set user agent */
    if (preg_match('#^=#', $ua))
        return $fake;

    /* fake user agent */
    if (preg_match('#Firefox/2.0.0.[0-9]+ Navigator/9.0#', $ua))
        return $fake;

    /* badly set user agent */
    if (preg_match('#^User-Agent:#i', $ua))
        return $fake;

    /* php default useragent passed as string intead of CONST */
    if (preg_match('#^_USERAGENT_$#i', $ua))
        return $fake;

    /* bad msie/msid request */
    if (preg_match('#^Mozilla/4.0 \(compatible; MSID [0-9\.]+; Windows NT [0-9\.]+\)$#i', $ua))
        return $fake;

    /* bad msie/msid request */
    if (preg_match('#^Mozilla/5.[0-9](...)?$#i', $ua))
        return $fake;

    /* 2 letters UA like "lp" */
    if (preg_match('#^[a-zA-Z0-9]{2}$#i', $ua))
        return $fake;

    /* Bad chrome version */
    if (preg_match('#Chrome/0.A.B.C#i', $ua))
        return $fake;

    /* Fake chrome ua */
    if (preg_match('#^Chrome/71.0.3578.98$#i', $ua))
        return $fake;

    /* check for user agent where spaces are replaced by plus signs */
    if (($chars = count_chars($ua, 1)) and isset($chars[ord('+')]) and $chars[ord('+')] >= 10 and (!isset($chars[ord(' ')])))
        return $fake;

    /* fake google bot user agent */
    if (preg_match('#^Mozilla/6.0 \(compatible; Googlebot/2.1; \+http\://www.google.com/bot.html\)$#i', $ua))
        return $fake;

    /* badly set user agent */
    if (preg_match('#Connection: closern$#i', $ua))
        return $fake;

    /* Fake visits from AWS */
    if (preg_match('#^Mozilla/5.0 Firefox/33.0$#i', $ua))
        return $fake;
    if (preg_match('#^Mozilla/5.0 \(Macintosh; Intel Mac OS X x.y; rv:42.0\) #i', $ua))
        return $fake;
    if (preg_match('#^Mozilla/5.0 \(Windows NT 6.1; Win64; x64; rv:47.0\) #i', $ua))
        return $fake;
    if (preg_match('#^Mozilla/5.0 \(X11; Linux x86_64\) (.*)(Trident/5.0|Firefox/42.0|OPR/38.0.2220.41|Gecko/20100101 Safari/602.1|AppleWebKit/537.36 \(KHTML, like Gecko\) Safari/602.1)#i', $ua))
        return $fake;

    /* Mispelled Firefox user agent, exepting BrandVerity which is using a badly set user agent *
    if (preg_match('#^Mozilla/5.0 \(([^\)]*) rv:([0-9a-zA-Z\.]*)\) ([^\)]*) Firefox/([0-9a-zA-Z\.]*)((?!BrandVerity).)*$#i', $ua, $matches) and ($matches[2] != $matches[4]) and (version_compare($matches[4], 5, '>=')))
        return $fake;
    */
    /* Fake Firefox user agent, with strange version identifier */
    if (preg_match('#^Mozilla/5.0 (.*) (Firefox|Safari)/([0-9A-Z]{4,6})$#i', $ua))
        return $fake;

    /* Fake Firefox user agent with fake versions */
    if (preg_match('#^Mozilla/5.0 (.*) Firefox/(45.62.15|52.53.90)$#i', $ua))
        return $fake;

    /* Real Firefox user agent used for fake requests */
    if (preg_match('#^Mozilla/5.0 \(Windows NT 6.1; WOW64; rv:40.0\) Gecko/20100101 Firefox/40.1$#i', $ua))
        return $fake;

    /* Fake Firefox (Chrome) user agent */
    if (preg_match('#^Mozilla/5.0 \(X11; Linux x86_64; rv:10.0\) Gecko/20150101 Firefox/[0-9]{2}.0 \(Chrome\)$#i', $ua))
        return $fake;

    /* Spams */
    if (preg_match('#^Mozilla/5.0 \(X11; Linux x86_64; rv:109\)$#i', $ua))
        return $fake;

    /* fake visits */
    if (preg_match('#UserAgent-Cube$#i', $ua))
        return $fake;

    /* Fake googlebot */
    if (preg_match('#User-Agent=Mozilla/5.0 \(compatible;googlebot/2.1\)$#i', $ua))
        return $fake;

    /* Fake visits, sample : Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko RqIwg8izYw6xskukQQDh */
    if (preg_match('#([0-9a-zA-Z]{16,24})$#', $ua))
        return $fake;

    /* Fake visits, with strange Edge version */
    if (preg_match('#^Mozilla/5.0 \(Windows NT 10.0; Win64; x64\) AppleWebKit/537.36 \(KHTML, like Gecko\) Chrome/[0-9\.]* Safari/537.36 Edge/[A-Z0-9]{8}$#', $ua))
        return $fake;

    /* Fake visits, with dumb/single word ua */
    if (preg_match('#(Foo|default|Google)$#', $ua))
        return $fake;

    /* Fake visit, with dumb ua */
    if (preg_match('#^Mozilla/5.0 \(admin\)$#', $ua))
        return $fake;

    /* Fake visit, without any space at the beginning of Android5.1.1/Oppo A33 device | Opera/12 */
    if (preg_match('#^(Mozilla|Opera)/([0-9\.]*)\(#', $ua))
        return $fake;

    /* Fake visit, from switzerland */
    if (preg_match('#like Gecko 4tds562$#', $ua))
        return $fake;

    /* Fake visit, from finland */
    if (preg_match('#\- 111512\-1801120036\-1\.44$#', $ua))
        return $fake;

    /* Fake facebook external hit, from germany */
    if (preg_match('#^acebookexternalhit#', $ua))
        return $fake;

    /* Fake firefox/opera version */
    if (preg_match('#Firefox/4.0 Opera 12.14$#', $ua))
        return $fake;

    /* Fake IE with additional data */
    if (preg_match('#APCPMS=#', $ua))
        return $fake;

    /* Hack ua using HTML script tag */
    if (preg_match('#text/javascript#', $ua))
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
            'platform_company', 'platform_country', 'platform_model', 'platform_type', 'platform_format', 'platform_year',
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
 * Load some defined properties for softwares.
 * @return void
 * @private
 */
function _client_loadSoftwareProperties() {
    global $softwareProperties;

    if (isset($softwareProperties))
        return;

    /* Build main list */
    $softwareProperties = array(
        'system' => array(
            'Mac OS X'          => array(
                'MaxVersion'    => '10.12.6',               // final is 10.12.6
                'FakeVersions'  => array(),
            ),
            'macOS'          => array(
                'MaxVersion'    => '10.17.0',               // current is 10.15.x
                'FakeVersions'  => array(),
            ),
            'Windows'           => array(
                'MaxVersion'    => '',
                'FakeVersions'  => array('NT 7.0', 'NT 7.1', 'NT 8.0', 'NT 8.1', 'NT 9.0', 'NT 9.1', 'NT 10.1', 'NT 15.0', 'NT 10.0N', 'NT 6.2.9200.0'),
            ),
            'iOS'               => array(
                'MaxVersion'    => '15',                    // current is 13.x
                'FakeVersions'  => array(),
            ),
            'Android'           => array(
                'MaxVersion'    => '11',                    // current is 9.x.x
                'FakeVersions'  => array('7.8.9'),
            ),
        ),
        'browser' => array(
            'Firefox'           => array(
                'MaxVersion'    => '75',                    // current is 71
                'FakeVersions'  => array('27.3'),
            ),
            'Chrome'            => array(
                'MaxVersion'    => '83',                    // current is 79
                'FakeVersions'  => array(),
            ),
            'Internet Explorer' => array(
                'MaxVersion'    => '11.0.50',               // latest
                'FakeVersions'  => array('9.11'),
            ),
            'Opera'             => array(
                'MaxVersion'    => '70',                    // current is 66
                'FakeVersions'  => array(),
            ),
            'Safari'            => array(
                'MaxVersion'    => '17',                    // current is 13.0
                'FakeVersions'  => array(),
            ),
        ),
    );

    /* Add duplicate */
    $softwareProperties['browser']['Chromium'] = $softwareProperties['browser']['Chrome'];  // Chromium matches Chrome last and fake versions
    $softwareProperties['browser']['Edge'] = $softwareProperties['browser']['Chrome'];      // Edge now matches Chrome last and fake versions
}

/**
 * Check if sofware is fake.
 * @param string $type
 * @param string $software
 * @param string $version
 */
function _client_checkSoftwareIsFake($type, $software, $version) {
    global $softwareProperties;

    /* load properties */
    _client_loadSoftwareProperties();

    /* check type */
    if (!isset($softwareProperties[$type]))
        return false;

    /* check software */
    if (!isset($softwareProperties[$type][$software]))
        return false;

    /* check version */
    if ($version === '')
        return false;

    /* check max version */
    if ($softwareProperties[$type][$software]['MaxVersion'] != '' and version_compare($version, $softwareProperties[$type][$software]['MaxVersion'], '>=') > 0)
        return true;

    /* check fake versions */
    if (in_array($version, $softwareProperties[$type][$software]['FakeVersions']))
        return true;

    /* Return default result */
    return false;
}

/**
 * Check if given UA is a OnePlus device
 * @return boolean result
 * @private
 */
function _client_isOnePlusDevice($ua='') {
    if (preg_match('/ ONE(PLUS)? ?([0-9A-Za-z]+)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/OnePlus.php.inc');
        return trim($matches[2]);
    } elseif (preg_match('/ (A|E)([0-9]{4})( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/OnePlus.php.inc');
        if (is_OnePlusKnownDevice($matches[1].$matches[2]))
          return $matches[1].$matches[2];
    } elseif (preg_match('/; (GM|HD)([0-9]{4})( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/OnePlus.php.inc');
        if (is_OnePlusKnownDevice($matches[1].$matches[2]))
          return $matches[1].$matches[2];
    }
    return false;
}

/**
 * Check if given UA is a Huawei device
 * @return boolean result
 * @private
 */
function _client_isHuaweiDevice($ua='') {
    if (preg_match('/ ([A-Z][A-Z0-9]{2,3}\-[A-Z][a-zA-Z0-9]{2,3})( Build|\))/', $ua, $matches)) {
        include_once('clientDevices/Huawei.php.inc');
        return trim($matches[1]);
    } elseif (preg_match('/ (MediaPad [^\)]*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Huawei.php.inc');
        return trim($matches[1]);
    } elseif (preg_match('/Build\/(HONOR|HUAWEI)([A-Z0-9\-]{3,})/i', $ua, $matches)) {
        include_once('clientDevices/Huawei.php.inc');
        return trim($matches[2]);
    } elseif (preg_match('/; HUAWEI (.*)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Huawei.php.inc');
        return trim($matches[1]);
    } elseif (preg_match('/ (T1-A21L|hi6210sft)/i', $ua, $matches)) {
        include_once('clientDevices/Huawei.php.inc');
        return $matches[1];
    } elseif (preg_match('/ (H[0-9]{4})( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Huawei.php.inc');
        if (is_HuaweiKnownDevice($matches[1]))
          return $matches[1];
    }
    return false;
}

/**
 * Check if given UA is a Kyocera device
 * @return boolean result
 * @private
 */
function _client_isKyoceraDevice($ua='') {
    if (preg_match('/ (KC-[A-Za-z0-9]*)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Kyocera.php.inc');
        return trim($matches[1]);
    } elseif (preg_match('/ ([0-9]{3}KC)( Build|\))/i', $ua, $matches)) {
        include_once('clientDevices/Kyocera.php.inc');
        return trim($matches[1]);
    } elseif (preg_match('/; (E6[0-9]{3}[A-Z]?)( Build|\))/Ui', $ua, $matches)) {
        include_once('clientDevices/Kyocera.php.inc');
        if (is_KyoceraKnownDevice($matches[1]))
          return $matches[1];
    }
    return false;
}
?>
