<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Tool Library
 * Creation Date        : Jun 2005
 * Last Modif Date      : Jan 2008
 * History :
 * * 05-06-XX : Initial File
 * * 08-01-07 : Rebuild module methods with generic plugin methods
 *
 * Module static methods
 */

/*
 * load module
 * @param string $name
 * @param string $path_type
 * @return mixed
 * @access public
 */
function module_get( $name, $path_type='camyks' ) {
  return plugin_get('module', $name, $path_type );
}

/*
 * load complete module list from path
 * @param string $path
 * @param string $path_type
 * @return array
 * @access public
 */
function module_getList( $path, $path_type='camyks' ) {
  return plugin_getList( $path.'/module', $path_type );
}
?>