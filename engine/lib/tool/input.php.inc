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
 * * 08-01-07 : Rebuild input methods with generic plugin methods
 *
 * Inputs static methods
 */

/*
 * load input
 * @param string $name
 * @param string $path_type
 * @return Input object
 * @access public
 */
function input_get( $name, $path_type='camyks' ) {
  return plugin_get( 'input', $name, $path_type );
}

/*
 * load complete input list from path
 * @param string $path
 * @param string $path_type
 * @return array
 * @access public
 */
function input_getList( $path, $path_type='camyks' ) {
  return plugin_getList( $path.'/input', $path_type );
}
?>