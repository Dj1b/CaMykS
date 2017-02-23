<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Tool Library
 * Creation Date	: Jun 2005
 * Last Modif Date      : Jan 2008
 * History :
 * * 05-06-xx : Initial File
 * * 08-01-07 : Rebuild template methods with generic plugin methods
 *
 * Template static methods
 */

/*
 * load template
 * @param string $name
 * @param string $path_type
 * @return Template object
 * @access public
 */
function template_get( $name, $path_type='camyks' ) {
  return plugin_get( 'template', $name, $path_type );
}

/*
 * load complete template list from path
 * @param string $path
 * @param string $path_type
 * @return array
 * @access public
 */
function template_getList( $path, $path_type='camyks' ) {
  return plugin_getList( $path.'/template', $path_type );
}
?>