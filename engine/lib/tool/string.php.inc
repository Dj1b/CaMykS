<?php
/**
 * @brief String specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/string.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2007
 * @date Modification: Jun 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Check if given ip (v4) is valid.
 * @param string $ip the ip address to test
 * @param boolean $allow_mask allows ip groups like 192.168.*.*
 * @return boolean
 */
function string_isValidIPv4($ip, $allow_mask=false) {
    $check = '([0-9]{1,2}|[0-1][0-9]{2}|2[0-4][0-9]|25[0-5]'.($allow_mask?'|\*':'').')';
    $l = array();
    for ($i=0; $i<4;$i++) {
        $l[$i] = $check;
    }
    $check = '/\A'.implode('\.', $l).'\Z/';
    if (preg_match($check, $ip, $result)) {
        return true;
    }
    return false;
}

/**
 * Format number string with current language country format.
 * @param string $string
 * @param integer $decimal
 * @param string $country
 * @return string
 */
function string_numberFormat($string, $decimal=2, $country=null) {
    global $camyks;
    
    /* check decimal value */
    $decimal = (int)$decimal;
    
    /* check country value */
    if ($country == null) $country = $camyks->current_language;
    
    /* check formatting case of country */
    switch ($country) {
        /* special */
        case 'num' : return number_format($string, $decimal, '.', '');
        
        /* countries */
        case 'al':
        case 'at':
        case 'be':
        case 'br':
        case 'cr':
        case 'cz':
        case 'dk':
        case 'ee':
        case 'es':
        case 'fi':
        case 'fr':
        case 'gr':
        case 'hu':
        case 'hr':
        case 'it':
        case 'no':
        case 'pe': 
        case 'po': 
        case 'pt':
        case 'ro':
        case 'rs': 
        case 'ru': 
        case 'se':
        case 'sl': 
        case 'sk':
        case 'ua': 
        case 'xk':
        case 'za': 
            return number_format($string, $decimal, ',', ' ');  // 1 234 567,89
        case 'ie': 
        case 'mt': 
            return number_format($string, $decimal, '&#149;', ','); // 1,234,567·89
        case 'ar':
        case 'at':
        case 'ba':
        case 'cl':
        case 'hr':
        case 'id':
        case 'it':
        case 'gr':
        case 'tr':
            return number_format($string, $decimal, ',', '.');  // 1,234,567.89
        case 'li':
        case 'sw':
            return number_format($string, $decimal, '.', '\''); // 1'234'567.89
        case 'lk':
            return number_format($string, $decimal, ' ', '.');  // 1 234 567.89
        case 'in':
        case 'bd':
        case 'np':
        case 'pk':
            /* split number to remove decimals */
            $number = (string)string_numberFormat($string, $decimal, 'num');
            $number = explode('.', $number);
            
            /* split number to have the last 3 */
            $a = substr($number[0], -3);
            $b = substr($number[0], 0, -3);
            
            /* split rest of number in 2 */
            if (strlen($b) == 0) {
                /* do nothing */
            } elseif (strlen($b) < 2)
                $a = $b.','.$a;
            elseif (strlen($b) % 2 == 0) 
                $a = chunk_split($b, 2, ',').$a;
            else
                $a = substr($b, 0, 1).','.chunk_split(substr($b, 1), 2, ',').$a;
            /* add decimals */
            if (isset($number[1]))
                $a .= '.'.$number[1];
            /* return value */
            return $a;  // 12,34,567.89
        default:
        case 'au':
        case 'ca':
        case 'ca':
        case 'en': 
        case 'hk':
        case 'ir':
        case 'il':
        case 'jp':
        case 'kp':
        case 'kr':
        case 'mx':
        case 'my':
        case 'nz':
        case 'ph':
        case 'pk':
        case 'sg':
        case 'th':
        case 'tw':
        case 'uk':
        case 'us':
            return number_format($string, $decimal, '.', ',');  // 1,234,567.89
    }
}

/**
 * Decode string from html to text.
 * @param string $string
 * @param string $encoding
 * @return string
 */
function string_html2Text($string, $encoding=null) {
    global $camyks;
    
    /* check encoding */
    if (!isset($encoding))
        $encoding = $camyks->get_confValue('encoding');
    
    /* decode html */
    $string = html_entity_decode($string);
    
    /* encode text */
    switch ($encoding) {
        case 'utf8':
            if ($camyks->get_confValue('server_encoding') != 'utf8')
                return utf8_encode($string);
        default:
        case '':
            return $string;
    }
    return $string;
}

/**
 * Encode string from text to html.
 * @param string $string
 * @param string $encoding
 * @return string
 */
function string_text2Html($string, $encoding=null) {
    global $camyks;
    
    /* check encoding */
    if (!isset($encoding))
        $encoding = $camyks->get_confValue('encoding');
    
    /* encode text */
    switch ($encoding) {
        case 'utf8':
            return htmlentities($string, null, 'UTF-8');
        default:
        case '':
    }
    
    /* decode html */
    return htmlentities($string);
}

/**
 * Return unaccentued words list from html.
 * @param string $string
 * @param array $params 
 * @parblock - Available parameters are <br />
 * \e string changecase - \b void / \b lower / \b upper <br />
 * \e integer minlength <br />
 * \e string contenttype - \b text / \b html <br />
 * \e string accents - \b replace / \b keep <br />
 * @endparblock
 * @return array
 */
function string_text2Words($string, $params=array()) {
    /* default config */
    $config = array('contenttype'=>'html', 'accents'=>'replace', 'changecase'=>'', 'minlength'=>0);
    
    /* merge config & params */
    $params = array_merge($config, $params);
    
    /* remove html tags */
    $string = string_stripTags($string, ' ');
    
    /* update case */
    if ($params['changecase'] == 'lower')
        $string = strtolower($string);
    else if ($params['changecase'] == 'upper')
        $string = strtoupper($string);
    
    /* check text mode */
    if ($params['contenttype'] == 'text' and $params['accents'] == 'replace')
        $string = string_text2Html($string);
    
    /* check html mode */
    if ($params['contenttype'] == 'html' and $params['accents'] != 'replace')
        $string = string_html2Text($string);
    
    /* parse accents */
    if ($params['accents'] == 'replace') {
        $string = string_replaceEntityChars($string, array('lastreplace'=>' '));
        $accentChars = '';
    } else {
        $accentChars = string_getAccentuedChars(array('listmode'=>'string', 'charmode'=>'text'));
    }
    
    /* set min length word regexp modifier */  
    if ($params['minlength']>2)
        $length_modifier = '{'.$params['minlength'].',}';
    else
        $length_modifier = '+';  
    
    /* split on non-letter chars */  
    $count = preg_match_all('/\b[\w'.$accentChars.']'.$length_modifier.'\b/', $string, $array);
    $array = $array[0];
    
    /* check html mode */
    if ($params['contenttype'] == 'html' and $params['accents']!='replace')
        foreach ($array as $idx => $value) {
            $array[$idx] = htmlentities($value);
        }
    
    return $array;
}

/**
 * Return replace entity char by unaccentued chars.
 * @param string $string
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e string/array pattern - containing patterns to complete built-in list <br />
 * \e string/array replace - containing replacement values to complete built-in list<br />
 * \e string lastreplace - all last entities are replaced by this value (empty string for no replacement) <br />
 * @endparblock
 * @return string
 */
function string_replaceEntityChars($string, $params=array()) {
    /* default config */
    $config = array('pattern'=>null, 'replace'=>null, 'lastreplace'=>null);
    
    /* merge config & params */
    $params = array_merge($config, $params);
    
    /* init pattern array */
    $pattern = array(
        /* add html named entities */
        '/&([a-zA-Z])(?:acute|grave|cedil|tilde|circ|uml|ring|slash);/',
        /* add html number entities for capitalised letters */
        '/&#19[2-7];/', '/&#199;/', '/&#20[0-3];/', '/&#20[4-7];/', '/&#209;/', '/&#21[0-46];/', '/&#2(?:1[7-9]|20);/', '/&#221;/',
        /* add html number entities for small letters */
        '/&#22[4-9];/', '/&#231;/', '/&#23[2-5];/', '/&#20[6-9];/', '/&#241;/', '/&#24[2-68];/', '/&#2(?:49|5[0-2]);/', '/&#25[35];/',
        /* add html number entities for special letters */
        '/&(?:#198|AElig);/', '/&(?:#223|szlig);/', '/&(?:#230|aelig);/', '/&(?:#338|oelig);/', '/&(?:#339|OElig);/', '/&#352;/', '/&#353;/', '/&#376;/',
        /* add html number entities for special chars */
        '/&amp;/', '/&hellip;/',
    );
    
    /* init replacement array */
    $replace = array(
        /* add html named entities */
        '$1',
        /* add html number entities for capitalised letters */
        'A', 'C', 'E', 'I', 'N', 'O', 'U', 'Y',
        /* add html number entities for small letters */
        'a', 'c', 'e', 'i', 'n', 'o', 'u', 'y',
        /* add html number entities for special letters */
        'AE', 'ss', 'ae', 'OE', 'oe', 'S', 's', 'Y',
        /* add html number entities for special chars */
        '', '...',
    );
    
    /* add param patterns and replacements */
    if (isset($params['pattern']) and isset($params['replace'])) {
        if (is_string($params['pattern']) and is_string($params['replace'])) {
            $pattern[] = $params['pattern'];
            $replace[] = $params['replace'];
        } else if (is_array($params['pattern']) and is_array($params['replace']) and count($params['pattern']) == count($params['replace'])) {
            $pattern = array_merge($pattern, $params['pattern']);
            $replace = array_merge($replace, $params['replace']);
        }
    }
    
    /* all other entities */
    if (isset($params['lastreplace'])) {
        $pattern[] = '/&[#\w]+;/';
        $replace[] = $params['lastreplace'];
    }
    
    /* execute replacement */
    return preg_replace($pattern, $replace, $string);
}

/**
 * Return accentued chars list.
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e string listmode - \b array / \b string <br />
 * \e string charmode - \b text / \b html <br />
 * @endparblock
 * @return mixed
 */
function string_getAccentuedChars($params=array()) {
    /* default config */
    $config = array('listmode'=>'array', 'charmode'=>'text');
    
    /* merge config & params */
    $params = array_merge($config, $params);
    
    /* init list */
    $accentChars = array();
    
    /* special array/text optimisation */
    if ($params['listmode'] == 'array' and 'charmode' == 'text') {
        for ($i=192; $i<256; $i++)
            $accentChars[] = html_entity_decode('&#'.$i.';');
        foreach (array(338, 339, 352, 353) as $i)
            $accentChars[] = html_entity_decode('&#'.$i.';');
        return $accentChars;
    }
    
    /* generic  */
    for ($i=192; $i<256; $i++)
        $accentChars[] = '&#'.$i.';';
    foreach (array(338, 339, 352, 353) as $i)
        $accentChars[] = '&#'.$i.';';
    if ($params['listmode'] != 'array')
        $accentChars = implode('', $accentChars);
    if ($params['charmode'] == 'text')
        $accentChars = html_entity_decode($accentChars);
    return $accentChars;
}

/**
 * Return parsed string, accentued chars are replaced by their unaccentued equivalent.
 * @param string $string
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e string/array pattern <br />
 * \e string/array replace <br />
 * @endparblock
 * @return string
 */
function string_parseSpecialChars($string, $params=array()) {
    /* default config */
    $config = array('pattern'=>'/[^a-zA-Z]/', 'replace'=>'');
    
    /* merge config & params */
    $params = array_merge($config, $params);
    
    /* execute replacement */
    return string_replaceEntityChars(string_text2Html($string), array('pattern'=>$params['pattern'], 'replace'=>$params['replace'], 'lastreplace'=>''));
}

/**
 * Return limited version of given sentence.
 * @param string $string
 * @param integer $length
 * @return string
 */
function string_getShortenedSentence($string='', $length=64) {
    $length = max($length, 4);
    if (strlen($string) > $length) {
        if (preg_match('/(.) {1,'.($length-3).'} /', $string, $matches))
            return $matches[0].'...';
        return substr($string, 0, $length).'...';
    }
    return $string;
}

/**
 * Remove PHP tags from value.
 * @param string $value
 * @param string $replace
 * @return string
 */
function string_stripPHPTags($value, $replace='') {
    $tags = array();
    $tags[] = '/<\?[^\?'.'>]*\?'.'>/';
    $tags[] = '/<\?/';
    return preg_replace($tags, $replace, $value);
}

/**
 * Remove Script tags from value.
 * @param string $value
 * @param string $replace
 * @return string
 */
function string_stripScriptTags($value, $replace='') {
    return preg_replace('/<script.*?\/script>/s', $replace, $value);
}

/**
 * Evolved strip_tags method, may replace tags by another string
 * @param string $value
 * @param string $replace
 * @return string
 */
function string_stripTags($value, $replace='') {
    if ($replace=='')
        return strip_tags($value);
    return preg_replace('/<([^>]+)>/i', $replace, $value);
}

/**
 * Check if given string is UTF8.
 * @param string $string
 * @return boolean
 */
function string_isUTF8($string) {
    return preg_match('%(?:
        [\xC2-\xDF][\x80-\xBF]              # non-overlong 2-byte
        |\xE0[\xA0-\xBF][\x80-\xBF]         # excluding overlongs
        |[\xE1-\xEC\xEE\xEF][\x80-\xBF]{2}  # straight 3-byte
        |\xED[\x80-\x9F][\x80-\xBF]         # excluding surrogates
        |\xF0[\x90-\xBF][\x80-\xBF]{2}      # planes 1-3
        |[\xF1-\xF3][\x80-\xBF]{3}          # planes 4-15
        |\xF4[\x80-\x8F][\x80-\xBF]{2}      # plane 16
        )+%xs', $string
    );
}

/**
 * Check if given string is html.
 * @param string $string
 * @return boolean
 */
function string_isHTML($string) {
    return (strip_tags($string) != $string or preg_match('/&[^ ]+;/', $string));
}

/**
 * Check if given string is an URL.
 * @param string $string
 * @return boolean
 */
function string_isURL($string) {
    return preg_match('#^https?://#i', $string);
}

/**
 * Check if given string starts with other string.
 * @param string $haystack
 * @param mixed $needle
 * @param boolean $caseSensitive
 * @return boolean result
 */
function string_startsWith($haystack, $needle, $caseSensitive=false) {
    if (is_array($needle)) {
        foreach ($needle as $id => $value)
            $needle[$id] = preg_quote($value, '/');
        return preg_match('/^('.implode('|', $needle).')/'.($caseSensitive?'i':''), $haystack) > 0;
    } else {
        if ($caseSensitive) {
            $needle = strtolower ($needle);
            $haystack = strtolower ($haystack);
        }
        return $needle === "" || strpos($haystack, $needle) === 0;
    }
}

/**
 * Check if given string ends with other string.
 * @param string $haystack
 * @param mixed $needle
 * @param boolean $caseSensitive
 * @return boolean result
 */
function string_endsWith($haystack, $needle, $caseSensitive=false) {
    if (is_array($needle)) {
        foreach ($needle as $id => $value)
            $needle[$id] = preg_quote($value, '/');
        return preg_match('/('.implode('|', $needle).')$/'.($caseSensitive?'i':''), $haystack) > 0;
    } else {
        if ($caseSensitive) {
            $needle = strtolower ($needle);
            $haystack = strtolower ($haystack);
        }
        return $needle === "" || substr($haystack, -strlen($needle)) === $needle;
    }
}

/**
 * Return given string base url.
 * @param string $url
 * @return string
 */
function string_getBaseURL($url='') {
    if (($durl = parse_url($url)) == false)
        return '';
    $s = isset($durl['scheme'])?$durl['scheme'].'://':'';
    $s .= $durl['host'];
    return $s;
}

/**
 * Return symbolic name (url compliant) from given string.
 * @param string $text
 * @param array $params
 * @return string
 */
function string_getSymbolicName($text='', $params=array()) {
    /* check params */
    $dParams = array('replacement'=>'_', 'keepSpecialChars'=>false);
    $params = array_merge($dParams, $params);
    
    /* check special chars replacement */
    if ($params['keepSpecialChars']) {
        $pattern = array('/&#178;/', '/&#179;/', '/&rsquo;/', '/&#169;/', '/&#174;/');
        $replace = array('2', '3', '-', '(c)', '(r)', '');
    } else {
        $pattern = array();
        $replace = array();
    }
    
    /* replace all special chars */
    $text = string_text2html($text);
    $text = string_replaceEntityChars($text, array('pattern'=>$pattern, 'replace'=>$replace));
    
    /* replace all unwanted chars */
    $text = preg_replace(array('/([^a-zA-Z0-9()]) {1,}/'), array($params['replacement']), $text);
    
    /* check first & last chars to not be replacement */
    if (substr($text, 0, 1) == $params['replacement'])
        $text = substr($text, 1);
    if (substr($text, -1) == $params['replacement'])
        $text = substr($text, 0, -1);
    
    return $text;
}

/**
 * Encode string to html.
 * @param string $text
 * @param int $flags
 * @param string $encoding
 * @param boolean $double_encode
 * @return string
 */
function string_encodeToHTML($text, $flags=null, $encoding=null, $double_encode=null) {
    /* apply generic HTML encode method */
    $text = htmlentities($text, $flags, $encoding, $double_encode);
    
    /* build extra character list */
    $pattern = array(
        /* polish characters */
        '/Ą/', '/ą/', '/Ę/', '/ę/', '/Ó/', '/ó/', '/Ć/', '/ć/', '/Ł/', '/ł/', '/Ń/', '/ń/',
        '/Ś/', '/ś/', '/Ź/', '/ź/', '/Ż/', '/ż/',
    );
    
    $replace = array(
        /* polish characters */
        '&#x104;', '&#x105;', '&#x118;', '&#281;', '&#211;', '&#243;', '&#262;','&#263;', '&#321;','&#322;',
        '&#323;', '&#324;', '&#346;', '&#347;', '&#377;', '&#378;', '&#379;', '&#380;',
    );
    
    return preg_replace($pattern, $replace, $text);
}

/**
 * Format given phone number.
 * @param string $number
 * @param string $prefix
 * @return string
 */
function string_formatIntlPhoneNumber($number, $prefix='') {
    
    /* remove leading + from prefix */
    if (substr($prefix, 0, 1) == '+')
        $prefix = substr($prefix, 1);
    
    /* check for prefix from country */
    if (preg_match('/^[a-z]{2}$/', $prefix))
        $prefix = countries_getPhonePrefix($prefix);
    
    if (preg_match('/^\+([0-9]{2,5}) ?(\(0\))? ([0-9\- ]+)$/', $number, $matches)) {
        /* for intl formatted number */
        
        if ($matches[1] != $prefix) {
            /* given prefix different from existing one */
        }
        
        /* remove all unwanted characters */
        $number = preg_replace ('/[^0-9]/', '', $matches[3]);
    } else {
        /* for locale formatted number */
        if ($prefix == '') {
            $prefix == '33';
        }
        
        /* remove all unwanted */
        $number = preg_replace ('/[^0-9]/', '', $number);
        
        /* remove leading 0 */
        if (substr($number, 0, 1) == 0)
            $number = substr($number, 1);
    }
    /* build number */
    return '+'.$prefix.$number;
}

/**
 * Return string all lowercase, including accentuated characters.
 * @param string $string
 * @return string
 */
function string_toLower($string='') {
    if (string_isUTF8($string))
        return utf8_encode(mb_strtolower(utf8_decode($string)));
    return strtolower($string);
}

/**
 * Return string all uppercase, including accentuated characters.
 * @param string $string
 * @return string
 */
function string_toUpper($string='') {
    if (string_isUTF8($string))
        return utf8_encode(mb_strtoupper(utf8_decode($string)));
    return strtoupper($string);
}

/**
 * Return similar strings begining.
 * @param string $s1
 * @param string $s2
 * @return string
 */
function string_getSimilarBeginning($s1, $s2) {
    $result = '';
    $i = 0;
    while ($i < min(strlen($s1), strlen($s2))) {
        if ($s1[$i] == $s2[$i]) {
            $result .= $s1[$i];
            $i++;
        } else {
            return $result;
        }
    }
    
    /* text are identical */
    return $result;
}

/**
 * Return string escaped for regex
 * @param string $string
 * @return string
 */
function string_escape4Regex($string='') {
  return preg_replace('/(\/|\(|\)|\.|\?|\$|\^|\[|\]|\*|\+|\{|\}|\,)/', '\\\$1', $string);
}

/* deprecated methods */

/**
 * Return string without non-letter chars.
 * @see string_replaceEntityChars()
 * @param string $string
 * @return string
 * @deprecated string_replaceEntityChars is now and often more accurate.
 */
function string_parseNonLetterChars($string) {
    $parsed = '';
    for ($index=0; $index<strlen($string); $index++) {
        $char = $string[$index];
        switch ($char) {
            case 'a': case 'A': $parsed.='a'; break;
            case 'b': case 'B': $parsed.='b'; break;
            case 'c': case 'C': $parsed.='c'; break;
            case 'd': case 'D': $parsed.='d'; break;
            case 'e': case 'E': $parsed.='e'; break;
            case 'f': case 'F': $parsed.='f'; break;
            case 'g': case 'G': $parsed.='g'; break;
            case 'h': case 'H': $parsed.='h'; break;
            case 'i': case 'I': $parsed.='i'; break;
            case 'j': case 'J': $parsed.='j'; break;
            case 'k': case 'K': $parsed.='k'; break;
            case 'l': case 'L': $parsed.='l'; break;
            case 'm': case 'M': $parsed.='m'; break;
            case 'n': case 'N': $parsed.='n'; break;
            case 'o': case 'O': $parsed.='o'; break;
            case 'p': case 'P': $parsed.='p'; break;
            case 'q': case 'Q': $parsed.='q'; break;
            case 'r': case 'R': $parsed.='r'; break;
            case 's': case 'S': $parsed.='s'; break;
            case 't': case 'T': $parsed.='t'; break;
            case 'u': case 'U': $parsed.='u'; break;
            case 'v': case 'V': $parsed.='v'; break;
            case 'w': case 'W': $parsed.='w'; break;
            case 'x': case 'X': $parsed.='x'; break;
            case 'y': case 'Y': $parsed.='y'; break;
            case 'z': case 'Z': $parsed.='z'; break;
            default:break;
        }
    }
    return $parsed;
}

/**
 * Remove PHP tags from value.
 * @param string $value
 * @param string $replace
 * @return string
 * @deprecated Method renamed to string_stripPHPTags
 */
function string_parsePHPTags($value, $replace='') {
  return string_stripPHPTags($value, $replace='');
}

?>