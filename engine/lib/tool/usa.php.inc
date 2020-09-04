<?php
/**
 * @brief USA related methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/usa.php.inc
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
 * Load USA states locales.
 * @param string $language
 * @return void
 */
function usa_getStatesLocales($language='') {
    global $camyks;

    /* check lang value */
    if ($language=='') $language = $camyks->current_language;

    /* load locales */
    $camyks->add_generic_translation('usastates', $language);
}

/**
 * Return USA states code list.
 * @return array
 */
function usa_getStatesCodeList() {
    return array('al', 'ak', 'az', 'ar', 'ca', 'nc', 'sc', 'co', 'ct', 'nd', 'sd', 'de', 'fl', 'ga',
        'hi', 'id', 'il', 'in', 'ia', 'ks', 'ky', 'la', 'me', 'md', 'ma', 'mi', 'mn', 'ms', 'mo',
        'mt', 'ne', 'nv', 'nh', 'nj', 'nm', 'ny', 'oh', 'ok', 'or', 'pa', 'ri', 'tn', 'tx', 'ut',
        'vt', 'va', 'wv', 'wa', 'wi', 'wy');
}

/**
 * Return USA states list.
 * @param array $params
 * @return array
 */
function usa_getStatesList($params=array()) {
    global $camyks;

    /* build default params list */
    $defaultParams = array(
        'language'  => $camyks->current_language,
    );

    /* merge params */
    $params = array_merge($defaultParams, $params);

    /* load locales */
    usa_getStatesLocales($params['language']);

    /* load states code list */
    $statesCodes = usa_getStatesCodeList();

    /* initialise list */
    $list = array();

    /* build list */
    foreach ($statesCodes as $state)
        $list[$state] = $camyks->get_translation('usastate_'.$state);

    /* return list */
    return $list;
}

/**
 * Return USA state title.
 * @param string $state
 * @param string $language
 * @return string
 */
function usa_getStateTitle($state='', $language='') {
    global $camyks;

    /* load locales */
    usa_getStatesLocales($language);

    /* check locale */
    if (isset($camyks->trads['usastate_'.$state]))
        return $camyks->trads['usastate_'.$state];
    return $state;
}

/**
 * Return USA holiday list for given year.
 * @param integer $year
 * @param integer $state
 * @return array
 * @todo Complete with states related holiday
 */
function usa_getHolidayList($year=null, $state='') {
    /* Check year */
    if (is_null($year)) $year = date('Y');

    /* Initialise list */
    $list = array();

    /* Adds New Year's day */
    $list[] = date_getNewYearsDay($year);

    /* Adds Christmas day */
    $list[] = date_getChristmasDay($year);

    /* Memorial Day */
    $list[] = strtotime('last monday '.$year.'-5');

    /* Independance Day */
    $list[] = mktime(0, 0, 0, 7, 4, $year);

    /* Labor Day */
    $list[] = strtotime('first monday '.$year.'-9');

    /* Thanksgiving Day */
    $list[] = strtotime('third thursday '.$year.'-11');

    /* Sort list */
    sort($list);

    /* Return list */
    return $list;
}
?>
