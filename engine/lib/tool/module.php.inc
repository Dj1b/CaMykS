<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Engine / Tool Library
 * Creation Date    : Jun 2005
 * Last Modif Date  : Apr 2018
 *
 * Module static methods
 */

/*
 * load module
 * @param string $name
 * @param string $path_type
 * @return mixed
 */
function module_get($name, $path_type=false) {
    if ($path_type !== false)
        return plugin_get('module', $name, $path_type);
    if (($p = plugin_get('module', $name, 'camyks')) !== false)
        return $p;
    return plugin_get('module', $name, 'site');
}

/*
 * load complete module list from path
 * @param string $path
 * @param string $path_type
 * @return array
 */
function module_getList($path, $path_type='camyks') {
    return plugin_getList($path.'/module', $path_type);
}
?>