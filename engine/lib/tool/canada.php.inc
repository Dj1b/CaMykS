<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Engine / Tool Library
 * Creation Date    : Jul 2017
 * Last Modif Date  : Apr 2018
 *
 * Specific methods related to Canada
 * /!\ This library is not loaded with CaMykS initialisation
 */
 
/* 
 * load canadian states locales
 * @param string language
 * @return void
 */
function canada_getStatesLocales($language='') {
    global $camyks;
    
    /* check lang value */
    if ($language=='') $language = $camyks->current_language;
    
    /* load locales */
    $camyks->add_generic_translation('canadianstates', $language);
}

/*
 * return canadian states code list
 * @return array
 */
function canada_getStatesCodeList() {
    return array('ab', 'bc', 'ipe', 'mb', 'nb', 'ns', 'on', 'qc', 'sk', 'nl', 'nu', 'nt', 'yt');
}
 
/*
 * return canadian states list
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

/*
 * return canadian state title
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