<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Tool library
 * Creation Date	: Jun 2005
 * Last Modif Date	: Jan 2002
 * History : 
 * * 05-06-xx : Initial File
 * * 08-01-07 : Rebuild theme methods with generic plugin methods
 *
 * Theme static methods
 */

/*
 * load theme
 * @param string $name
 * @param string $path_type
 * @return Theme object
 * @access public
 */
function theme_get( $name, $path_type='camyks' ) {
  return plugin_get( 'theme', $name, $path_type );
}

/*
 * load complete theme list from path
 * @param string $path
 * @param string $path_type
 * @return array
 * @access public
 */
function theme_getList( $path, $path_type='camyks' ) {
  return plugin_getList( $path.'/theme', $path_type );
}
?>