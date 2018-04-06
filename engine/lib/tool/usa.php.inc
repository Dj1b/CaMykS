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
 * Specific methods related to USA
 * /!\ This library is not loaded with CaMykS initialisation
 */
 
/* 
 * load USA states locales
 * @param string language
 * @return void
 */
function usa_getStatesLocales($language='') {
    global $camyks;
    
    /* check lang value */
    if ($language=='') $language = $camyks->current_language;
    
    /* load locales */
    $camyks->add_generic_translation('usastates', $language);
}

/*
 * return USA states code list
 * @return array
 */
function usa_getStatesCodeList() {
    return array('al', 'ak', 'az', 'ar', 'ca', 'nc', 'sc', 'co', 'ct', 'nd', 'sd', 'de', 'fl', 'ga',
        'hi', 'id', 'il', 'in', 'ia', 'ks', 'ky', 'la', 'me', 'md', 'ma', 'mi', 'mn', 'ms', 'mo', 
        'mt', 'ne', 'nv', 'nh', 'nj', 'nm', 'ny', 'oh', 'ok', 'or', 'pa', 'ri', 'tn', 'tx', 'ut',
        'vt', 'va', 'wv', 'wa', 'wi', 'wy');
}

/*
 * return USA states list
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

/*
 * return USA state title
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
?>