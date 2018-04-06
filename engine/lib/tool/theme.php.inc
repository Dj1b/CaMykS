<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Engine / Tool Library
 * Creation Date    : Jun 2005
 * Last Modif Date  : Mar 2018
 *
 * Theme static methods
 */

/*
 * load theme
 * @param string $name
 * @param string $path_type
 * @return Theme object
 */
function theme_get($name, $path_type=false) {
    if ($path_type !== false)
        return plugin_get('theme', $name, $path_type);
    if (($p = plugin_get('theme', $name, 'camyks')) !== false)
        return $p;
    return plugin_get('theme', $name, 'site');
}

/*
 * load complete theme list from path
 * @param string $path
 * @param string $path_type
 * @return array
 */
function theme_getList($path, $path_type='camyks') {
    return plugin_getList($path.'/theme', $path_type);
}
?>