<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Engine / Tool Library
 * Creation Date    : Jun 2005
 * Last Modif Date  : Mar 2018
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
function input_get($name, $path_type=false) {
  if ($path_type !== false)
    return plugin_get('input', $name, $path_type);
  if (($p = plugin_get('input', $name, 'camyks')) !== false)
    return $p;
  return plugin_get('input', $name, 'site');
}

/*
 * load complete input list from path
 * @param string $path
 * @param string $path_type
 * @return array
 * @access public
 */
function input_getList($path, $path_type='camyks') {
  return plugin_getList($path.'/input', $path_type);
}
?>