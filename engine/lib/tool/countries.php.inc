<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Engine / Tool Library
 * Creation Date    : Sep 2007
 * Last Modif Date  : Apr 2018
 *
 * Countries static methods
 * Country codes define by ISO 3166-2 list
 */
 
/*
 * return countries code list
 * @param array $params
 * @return array
 */
function countries_getCodeList($params=array()) {
    $dParams = array('countries'=>1, 'territories'=>1, 'ex-countries'=>0, 'shortlist'=>array());
    $params = array_merge($dParams, $params); 
    $list = array();
    
    /* add countries to the list */
    if ($params['countries']==1)
        $list = array_merge($list, array(
            'ad', 'ae', 'af', 'ag', 'al', 'am', 'ao', 'ar', 'at', 'au',
            'az', 'ba', 'bb', 'bd', 'be', 'bf', 'bg', 'bh', 'bi', 'bj', 
            'bn', 'bo', 'br', 'bs', 'bt', 'bw', 'by', 'bz', 'ca', 'cd', 
            'cf', 'cg', 'ch', 'ci', 'ck', 'cl', 'cm', 'cn', 'co', 'cr', 
            'cu', 'cv', 'cw', 'cy', 'cz', 'de', 'dj', 'dk', 'dm', 'do', 
            'dz', 'ec', 'ee', 'eg', 'er', 'es', 'et', 'fi', 'fj', 'fr', 
            'ga', 'gb', 'gd', 'ge', 'gg', 'gh', 'gm', 'gn', 'gq', 'gr', 
            'gt', 'gw', 'gy', 'hn', 'hr', 'ht', 'hu', 'id', 'ie', 'il', 
            'im', 'in', 'iq', 'ir', 'is', 'it', 'je', 'jm', 'jo', 'jp', 
            'ke', 'kg', 'kh', 'ki', 'km', 'kn', 'kp', 'kr', 'kw', 'kz', 
            'la', 'lb', 'lc', 'li', 'lk', 'lr', 'ls', 'lt', 'lu', 'lv', 
            'ly', 'ma', 'mc', 'md', 'me', 'mg', 'mh', 'mk', 'ml', 'mn', 
            'mm', 'mr', 'mt', 'mu', 'mv', 'mw', 'mx', 'my', 'mz', 'na', 
            'ne', 'nf', 'ng', 'ni', 'nl', 'no', 'np', 'nr', 'nz', 'om', 
            'pa', 'pe', 'pg', 'ph', 'pk', 'pl', 'pt', 'pw', 'py', 'qa', 
            'ro', 'rs', 'ru', 'rw', 'sa', 'sb', 'sc', 'sd', 'se', 'sg', 
            'si', 'sk', 'sl', 'sm', 'sn', 'so', 'sr', 'ss', 'st', 'sv', 
            'sy', 'sz', 'td', 'tg', 'th', 'tj', 'tl', 'tm', 'tn', 'to', 
            'tr', 'tt', 'tv', 'tz', 'ua', 'ug', 'um', 'us', 'uy', 'uz', 
            'va', 'vc', 've', 'vn', 'vu', 'ws', 'xk', 'ye', 'za', 'zm', 
            'zw',
        ));
    
    /* add territories to the list */
    if ($params['territories']==1)
        $list = array_merge($list, array(
            'ai', 'an', 'aq', 'as', 'aw', 'ax', 'bl', 'bm', 'bv', 'bq', 
            'cc', 'cx', 'eh', 'fk', 'fo', 'gf', 'gi', 'gl', 'gp', 'gs', 
            'gu', 'hk', 'hm', 'io', 'ky', 'mf', 'mo', 'mp', 'mq', 'ms', 
            'nc', 'nu', 'pf', 'pm', 'pn', 'pr', 'ps', 'qc', 're', 'sh', 
            'sj', 'sx', 'td', 'tf', 'tk', 'tw', 'um', 'vg', 'vi', 'wf', 
            'yt',
        ));
    
    /* add old countries to the list */
    if ($params['ex-countries']==1)
        $list = array_merge($list, array('cs', 'su', 'yu'));
    
    /* check for a short list of countries */
    if (count($params['shortlist']) > 0) {
        $t = array();
        foreach ($params['shortlist'] as $c)
            if (in_array($c, $list))
                $t[] = $c;
        $list = $t;
    }
    
    /* sort list */
    sort($list);
    
    /* return final code list */
    return $list;
}

/*
 * return generic country list
 * @return array
 */
function countries_getList() {
    static $list;
    if (isset($list)) 
        return $list;
    $list = countries_getTitleList();
    return $list;
}

/*
 * return custom country list
 * @param array $params
 * @return array
 */
function countries_getTitleList($params=array()) {
    /* load countries translation */
    countries_loadLocales();
    
    /* build complete list */
    $list = array();
    foreach ( countries_getCodeList($params) as $v )
        $list[$v] = countries_getTranslation($v);
    
    /* sort countries */
    asort($list);
  
    /* return list */
    return $list;
}

/*
 * load countries locales
 * @param string $language
 * @return void
 */
function countries_loadLocales($language=null) {
    global $camyks;
    $camyks->add_generic_translation('countries', $language);
}

/*
 * return country localised name
 * @params string $c
 * @return string
 */
function countries_getTranslation($c) {
    global $camyks;
    if ($c == '') return '';
    return $camyks->get_translation('country_'.$c);
}

/*
 * get country code from name
 * @param unknown $c
 * @return string on success, false on error
 * @access public
 */
function countries_getCode($lang='', $key=''){
    global $camyks;
    
    /* check language */
    if ($lang != null && $lang != '')
        $camyks->add_generic_translation('countries', $lang);
    
    /* search country */
    foreach ($camyks->trads as $tradK=>$tradV) {
        if (substr($tradK, 0, strlen('country_')) === 'country_' && strtolower($tradV) == strtolower($key))
            return $tradK;
    }
    
    /* no country found */
    return false;
}

/*
 * return country phone prefixes list
 * @return array
 */
function countries_getPhonePrefixes() {
    global $__phonePrefixes;
    require_once ('countries_phonePrefixes.php.inc');
    return $__phonePrefixes;
}

/*
 * return phone prefix value for given country
 * @return string
 */
function countries_getPhonePrefix($country) {
    global $__phonePrefixes;  
    require_once ('countries_phonePrefixes.php.inc');
    if (isset($__phonePrefixes[$country]))
        return $__phonePrefixes[$country];
    return '';
}
?>