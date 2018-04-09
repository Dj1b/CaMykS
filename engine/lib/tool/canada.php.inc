<?php
/**
 * @brief Specific methods related to Canada
 * @details Engine / Tool Library
 * @file engine/lib/tool/canada.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2017
 * @date Modification: Apr 2018
 * @copyright 2017 - 2018 CaMykS Team
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
?>