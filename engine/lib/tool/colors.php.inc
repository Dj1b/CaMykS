<?php
/*
 * CaMykS Engine
 * Developed by       : camyks.net
 * Author             : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version     : 1.0
 * Object Version     : 1.0
 * Object Type        : Engine / Tool Library
 * Creation Date      : Jul 2017
 * Last Modif Date    : Jul 2017
 *
 * Specific methods related to colors
 * /!\ This library is not loaded with CaMykS initialisation
 */
 
/*
 * load colors locales
 * @param string $language
 * @return void
 */
function colors_loadLocales($language='') {
  global $camyks;
  
  /* check lang value */
  if ($language=='') $language = $camyks->current_language;
  
  /* load locales */
  $camyks->add_generic_translation('colors', $language);
}

/*
 * return color title
 * @param string $color
 * @param string $language
 * @return string
 */
function color_getTitle($color='', $language='') {
  global $camyks;
  
  /* load locales */
  colors_loadLocales();
  
  /* check locale */
  if (isset($camyks->trads['color_'.$color]))
    return $camyks->get_translation('color_'.$color);
  return $color;
}

?>