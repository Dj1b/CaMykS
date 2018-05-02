<?php
/**
 * @brief Language specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/language.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2015 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $languages;

/**
 * @def LANG_ICON_PATH
 */
define("LANG_ICON_PATH",        "");

/**
 * @def LANG_ICON_EXTENSION
 */
define("LANG_ICON_EXTENSION",   ".gif");

/**
 * @def LANG_ICON_DEFAULT
 */
define("LANG_ICON_DEFAULT",     "default");

/**
 * @var array $languages
 */
$languages = array(
    'en' => array(
        'title'     => 'English',
        'locale'    => array(
            ''      => array('en_GB'),
       ),
   ),
    'fr'    => array(
        'title'     => 'Fran&ccedil;ais',
        'locale'    => array(
            ''          => array('fr_FR', 'french', 'france', 'fr_FR@euro'),
            'utf8'      => array('fr_FR.utf8', 'fr_FR.UTF-8', 'fr_FR.UTF8', 'fr_FR', 'french', 'france', 'fr_FR@euro'),
            'iso88591'  => array('fr_FR.iso88591', 'fr_FR.iso885915@euro', 'fr_FR.8859-1', 'fr_FR.88591', 'fr_FR.ISO8859-1', 'fr_FR', 'french', 'france', 'fr_FR@euro'),
       ),
   ),
    'de'    => array(
        'title'     => 'Deutsch', 
        'locale'    => array(
            ''      => array('de_DE'),
            'utf8'  => array('de_DE.utf8', 'de_DE.UTF8', 'de_DE.UTF-8'),
       ),
   ),
    'it'    => array(
        'title'     => 'Italiano',
        'locale'    => array(
            ''      => array('it_IT'),
       ),
   ),
    'es'    => array(
        'title'     => 'Espa&ntilde;ol', 
        'locale'    => array(
            ''      => array('es_ES'),
            'utf8'  => array('es_ES.utf8', 'es_ES.UTF8', 'es_ES.UTF-8'),
       ),
   ),
    'pt'    => array(
        'title'     => 'Portugu&ecirc;s', 
        'locale'    => array(
            ''      => array('pt_PT'),
           'utf8'   => array('pt_PT.utf8', 'pt_PT.UTF8', 'pt_PT.UTF-8'),
       ),
   ),
    'br'    => array(
        'title'     => 'Brasileiro',
        'locale'    => array(
            ''      => array('pt_BR'),
            'utf8'  => array('pt_BR.utf8', 'pt_BT.UTF8', 'pt_BR.UTF-8')
       ),
   ),
);

/**
 * Return available languages.
 * @return array
 */
function language_getAvailableLanguages() {
    global $languages;
    return $languages;
}

/**
 * Check if language is available.
 * @param string $lg
 * @return boolean
 */
function language_isKnownlanguage($lg) {
    global $languages;
    return (isset($languages[$lg]));
}

/**
 * Return language title.
 * @param string $lg
 * @return string
 */
function language_getTitle($lg) {
    global $languages;
    if (isset($languages[$lg])) {
        return $languages[$lg]['title'];
    } else {
        return '';
    }
}

/****************** ICONS *********************/

/**
 * Return html flag url.
 * @param string $short
 * @param boolean $full
 * @return string
 */
function language_getIcon($short, $full=true) {
    global $camyks;
    
    $flag = $camyks->get_dataFileURL('img/flag/'.$short.LANG_ICON_EXTENSION);
    
    if ($full)
        return '<img src="'.$flag.'" alt="'.$short.'" style="border:0" />';
    return $flag;
}


/************************ LOCALE *****************************/

/**
 * Return locale value from given language/country.
 * @param string $short_name
 * @param string $encodage
 * @return string
 */
function language_getLocale($short_name, $encodage='') {
    global $languages;
    if (isset ($languages[$short_name]['locale'][$encodage])) {
        return $languages[$short_name]['locale'][$encodage];
    } else if (isset ($languages[$short_name]['locale'][''])) {
        return $languages[$short_name]['locale'][''];
    }
    return '';
}

/************************ OTHERS *****************************/

/**
 * Return file size unit.
 * @return char
 */
function language_getFileUnit () {
    global $camyks;
    switch ($camyks->current_language) {
        case 'fr':
            return 'o';
        case 'en':
        default:
            return 'b';
    }
}

/**
 * Return number formatting case of current language.
 * @param float $number
 * @param integer $floats
 * @return string
 */
function language_numberFormat($number, $floats=2) {
    global $camyks;
    return string_numberFormat($number, $floats, $camyks->current_language);
}

/**
 * Return available dictionnaries for a given folder
 * @param string $folder
 * @return array
 */
function language_getDictionnaryList($folder='') {
    global $camyks;
    
    /* initialise result */
    $result = array();
    
    /* load files in folder */
    $files = folder_listFiles($folder);
    
    /* check files */
    foreach ($files as $file) {
        if (substr($file, 0, 12) == 'translation_' and substr($file , strlen($file) - strlen($camyks->file_extension), strlen($camyks->file_extension)) == $camyks->file_extension) {
            $result[] = substr($file, 12, strlen($file) - 12 - strlen($camyks->file_extension));
        }
    }
    return $result;
}
?>