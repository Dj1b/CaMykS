<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Engine / Tool Library
 * Creation Date	: Jun 2005
 * Last Modif Date	: Jun 2007
 *
 * Language static methods
 */

define("LANG_ICON_PATH", 	"");
define("LANG_ICON_EXTENSION",	".gif");
define("LANG_ICON_DEFAULT", 	"default");

global $languages;
$languages = array(
    'en'    => array(
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
	        'utf8'  => array('de_DE.utf8', 'de_DE.UTF8', 'de_DE.UTF-8' ),
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

/* 
 * send languages
 * @return array
 * @access public
 */
function language_getAvailableLanguages() {
  global $languages;
  return $languages;
}

/*
 * check if language is available
 * @param string $lg
 * @return boolean
 */
function language_isKnownlanguage($lg) {
  global $languages;
  return (isset($languages[$lg]));
}

/*
 * get language title
 * @param string $lg
 * @return string
 * @access public
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

/*
 * return html flag url
 * @param string $short
 * @param boolean $full
 * @return string
 * @access public
 */
function language_getIcon($short, $full=true) {
  global $camyks;
  
  $flag = $camyks->get_dataFileURL('img/flag/'.$short.LANG_ICON_EXTENSION);
  
  if ( $full )
    return '<img src="'.$flag.'" alt="'.$short.'" style="border:0" />';
  return $flag;
}


/************************ LOCALE *****************************/

/*
 * return locale value from given language/country
 * @param string $short_name
 * @param string $encodage
 * @return string
 * @access public
 */
function language_getLocale($short_name, $encodage='') {
  global $languages;
  if ( isset ( $languages[$short_name]['locale'][$encodage]) ) {
    return $languages[$short_name]['locale'][$encodage];
  } else if ( isset ($languages[$short_name]['locale']['']) ) {
    return $languages[$short_name]['locale'][''];
  }
  return '';
}

/************************ OTHERS *****************************/

/*
 * return file size unit
 * @return char
 * @access public
 */
function language_getFileUnit ( ) {
  global $camyks;
  switch ( $camyks->current_language ) {
  case 'fr':
    return 'o';
  case 'en':
  default:
    return 'b';
  }
}

/*
 * return number formatting case of current language
 * @param float $number
 * @param integer $floats
 * @return string
 * @access public
 */
function language_numberFormat($number, $floats=2) {
  global $camyks;
  return string_numberFormat($number, $floats, $camyks->current_language);
}
?>