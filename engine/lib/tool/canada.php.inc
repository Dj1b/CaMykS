<?php
/**
 * @brief Canada related methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/canada.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jul 2017
 * @date Modification: Jul 2020
 * @copyright 2017 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Load canadian states locales.
 * @param string $language
 * @return void
 */
function canada_getStatesLocales($language='') {
    global $camyks;

    /* check lang value */
    if ($language=='') $language = $camyks->current_language;

    /* load locales */
    $camyks->add_generic_translation('canadianstates', $language);
}

/**
 * Return canadian states code list.
 * @return array
 */
function canada_getStatesCodeList() {
    return array('ab', 'bc', 'ipe', 'mb', 'nb', 'ns', 'on', 'qc', 'sk', 'nl', 'nu', 'nt', 'yt');
}

/**
 * Return canadian states list.
 * @param array $params
 * @return array
 */
function canada_getStatesList($params=array()) {
    global $camyks;

    /* build default params list */
    $defaultParams = array(
        'language'  => $camyks->current_language,
    );

    /* merge params */
    $params = array_merge($defaultParams, $params);

    /* load locales */
    canada_getStatesLocales($params['language']);

    /* load states code list */
    $statesCodes = canada_getStatesCodeList();

    /* initialise list */
    $list = array();

    /* build list */
    foreach ($statesCodes as $state)
        $list[$state] = $camyks->get_translation('canadianstate_'.$state);

    /* return list */
    return $list;
}

/**
 * Return canadian state title.
 * @param string $state
 * @param string $language
 * @return string
 */
function canada_getStateTitle($state='', $language='') {
    global $camyks;

    /* load locales */
    canada_getStatesLocales($language);

    /* check locale */
    if (isset($camyks->trads['canadianstate_'.$state]))
        return $camyks->trads['canadianstate_'.$state];
    return $state;
}

/**
 * Return Canada holiday list for given year.
 * @param integer $year
 * @param integer $state
 * @return array
 */
function canada_getHolidayList($year=null, $state='') {
    /* Check year */
    if (is_null($year)) $year = date('Y');

    /* Initialise list */
    $list = array();

    /* Adds New Year's day */
    $list[] = date_getNewYearsDay($year);

    /* Adds religeous days */
    $easter = date_getEasterDay($year);
    $list[] = mktime(0, 0, 0, date('n', $easter), date('j', $easter)-2, $year); /* Good Friday */
    $list[] = mktime(0, 0, 0, date('n', $easter), date('j', $easter)+1, $year); /* Easter Monday */
    $list[] = date_getChristmasDay($year);

    /* Adds national days */
    /* Canada day */
    $list[] = mktime(0, 0, 0, 7, 1, $year);

    /* Labour Day */
    $list[] = strtotime('first monday '.$year.'-9');

    /* Adds states related days */
    /* Aboriginal Day */
    if (!in_array($state, array('nt', 'yt')))
        $list[] = mktime(0, 0, 0, 6, 21, $year);

    /* St Jean Baptiste Day */
    if ($state == 'qc')
        $list[] = mktime(0, 0, 0, 6, 24, $year);

    /* Nunavut Day */
    if ($state == 'nu')
        $list[] = mktime(0, 0, 0, 7, 9, $year);

    if ($state == 'nl') {
        /* Orangemen's Day */
        $list[] = mktime(0, 0, 0, 7, 12, $year);

        /* Saint Patrick's Day */
        $list[] = mktime(0, 0, 0, 3, 17, $year);

        /* Saint George's Day */
        $list[] = mktime(0, 0, 0, 4, 23, $year);
    }

    /* Gold Cup Parade Day */
    if ($state == 'ipe')
        $list[] = strtotime('third friday '.$year.'-8');

    /* Discovery Day */
    if ($state == 'yt')
        $list[] = strtotime('third monday '.$year.'-8');

    /* Remembrance Day */
    if (in_array($state, array('ab', 'bc', 'ipe', 'nb', 'sk', 'nl', 'nu', 'nt', 'yt')))
        $list[] = mktime(0, 0, 0, 11, 11, $year);

    /* Boxing Day */
    if (in_array($state, array('nb', 'nt', 'nu', 'on', 'ipe')))
        $list[] = mktime(0, 0, 0, 12, 26, $year);

    /* Thanksgiving Day */
    if (in_array($state, array('ab', 'bc', 'ipe', 'mb', 'nb', 'on', 'qc', 'sk', 'nu', 'nt', 'yt')))
        $list[] = strtotime('second monday '.$year.'-10');

    /* Louis Riel / Islander / Family / Heritage Day */
    if (in_array($state, array('ab', 'bc', 'ipe', 'mb', 'nb', 'ns', 'on', 'sk')))
        $list[] = strtotime('third monday '.$year.'-2');

    /* Civic Holiday / Heritage / British Columbia / Saskatchewan / New Brunswick / Natal Day */
    if (in_array($state, array('ab', 'bc', 'mb', 'nb', 'ns', 'on', 'sk', 'nl', 'nu', 'nt', 'yt')))
        $list[] = strtotime('first monday '.$year.'-8');

    /* National Patriots / Victoria Day */
    if (in_array($state, array('ab', 'bc', 'ipe', 'mb', 'nb', 'ns', 'on', 'qc', 'sk', 'nu', 'nt', 'yt'))) {
        $day = date('N', mktime(0, 0, 0, 5, 25, $year));
        if ($day == 1) $day = 8;
        $list[] = mktime(0, 0, 0, 5, 26-$day, $year);
    }

    /* Sort list */
    sort($list);

    /* Return list */
    return $list;
}
?>
