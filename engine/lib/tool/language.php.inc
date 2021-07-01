<?php
/**
 * @brief Language specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Jun 2005
 * @date Modification: Jun 2021
 * @copyright 2015 - 2021 CaMykS Team
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
    'en'    => array(
        'title'     => 'English',
        'extend'    => 'en-gb',
        'locale'    => array(
            ''      => array('en_GB'),
        ),
    ),
    'fr'    => array(
        'title'     => 'Fran&ccedil;ais',
        'extend'    => 'fr-fr',
        'locale'    => array(
            ''          => array('fr_FR', 'french', 'france', 'fr_FR@euro'),
            'utf8'      => array('fr_FR.utf8', 'fr_FR.UTF-8', 'fr_FR.UTF8', 'fr_FR', 'french', 'france', 'fr_FR@euro'),
            'iso88591'  => array('fr_FR.iso88591', 'fr_FR.iso885915@euro', 'fr_FR.8859-1', 'fr_FR.88591', 'fr_FR.ISO8859-1', 'fr_FR', 'french', 'france', 'fr_FR@euro'),
        ),
    ),
    'de'    => array(
        'title'     => 'Deutsch',
        'extend'    => 'de-de',
        'locale'    => array(
            ''      => array('de_DE'),
            'utf8'  => array('de_DE.utf8', 'de_DE.UTF8', 'de_DE.UTF-8'),
        ),
    ),
    'it'    => array(
        'title'     => 'Italiano',
        'extend'    => 'it-it',
        'locale'    => array(
            ''      => array('it_IT'),
        ),
    ),
    'es'    => array(
        'title'     => 'Espa&ntilde;ol',
        'extend'    => 'es-es',
        'locale'    => array(
            ''      => array('es_ES'),
            'utf8'  => array('es_ES.utf8', 'es_ES.UTF8', 'es_ES.UTF-8'),
        ),
    ),
    'pt'    => array(
        'title'     => 'Portugu&ecirc;s',
        'extend'    => 'pt-pt',
        'locale'    => array(
            ''      => array('pt_PT'),
           'utf8'   => array('pt_PT.utf8', 'pt_PT.UTF8', 'pt_PT.UTF-8'),
        ),
    ),
    'br'    => array(
        'title'     => 'Brasileiro',
        'extend'    => 'pt-br',
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

/**
 * Load language locales.
 * @param string $language
 * @return void
 */
function language_loadLocales($language=null) {
    global $camyks;
    $camyks->add_generic_translation('language', $language);
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

/************************ SCRIPT *****************************/

/**
 * Return language script list.
 * @return array
 */
function language_getScriptList() {
    return array(
       'Arabic', 'Armenian', 'Avestan', 'Balinese', 'Bamum',
       'Batak', 'Bengali', 'Bopomofo', 'Brahmi', 'Braille',
       'Buginese', 'Buhid', 'Canadian_Aboriginal', 'Carian', 'Chakma',
       'Cham', 'Cherokee', 'Common', 'Coptic', 'Cuneiform',
       'Cypriot', 'Cyrillic', 'Deseret', 'Devanagari', 'Egyptian_Hieroglyphs',
       'Ethiopic', 'Georgian', 'Glagolitic', 'Gothic', 'Greek',
       'Gujarati', 'Gurmukhi', 'Han', 'Hangul', 'Hanunoo',
       'Hebrew', 'Hiragana', 'Imperial_Aramaic', 'Inherited', 'Inscriptional_Pahlavi',
       'Inscriptional_Parthian', 'Javanese', 'Kaithi', 'Kannada', 'Katakana',
       'Kayah_Li', 'Kharoshthi', 'Khmer', 'Lao', 'Latin',
       'Lepcha', 'Limbu', 'Linear_B', 'Lisu', 'Lycian',
       'Lydian', 'Malayalam', 'Mandaic', 'Meetei_Mayek', 'Meroitic_Cursive',
       'Meroitic_Hieroglyphs', 'Miao', 'Mongolian', 'Myanmar', 'New_Tai_Lue',
       'Nko', 'Ogham', 'Old_Italic', 'Old_Persian', 'Old_South_Arabian',
       'Old_Turkic', 'Ol_Chiki', 'Oriya', 'Osmanya', 'Phags_Pa',
       'Phoenician', 'Rejang', 'Runic', 'Samaritan', 'Saurashtra',
       'Sharada', 'Shavian', 'Sinhala', 'Sora_Sompeng', 'Sundanese',
       'Syloti_Nagri', 'Syriac', 'Tagalog', 'Tagbanwa', 'Tai_Le',
       'Tai_Tham', 'Tai_Viet', 'Takri', 'Tamil', 'Telugu',
       'Thaana', 'Thai', 'Tibetan', 'Tifinagh', 'Ugaritic',
       'Vai', 'Yi',
    );
}

/**
 * Return language script title list.
 * @return array
 */
function language_getScriptTitleList() {
    global $camyks;

    /* Load languages locales */
    language_loadLocales();

    /* Initialise result list */
    $list = array();

    /* Load all script titles */
    foreach (language_getScriptList() as $script)
        $list[$script] = $camyks->get_translation('languagescript_'.strtolower($script));

    /* Return result list */
    return $list;
}

/**
 * Return language script title.
 * @param string $script
 * @return string
 */
function language_getScriptTitle($script) {
    global $camyks;
    return $camyks->get_translation('languagescript_'.strtolower($script));
}

/************************ OTHERS *****************************/

/**
 * Return file size unit.
 * @return char
 */
function language_getFileUnit() {
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
