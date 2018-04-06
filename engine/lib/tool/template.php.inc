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
 * Template static methods
 */

/*
 * load template
 * @param string $name
 * @param string $path_type
 * @return Template object
 */
function template_get($name, $path_type=false) {
    if ($path_type !== false)
        return plugin_get('template', $name, $path_type);
    if (($p = plugin_get('template', $name, 'camyks')) !== false)
        return $p;
    return plugin_get('template', $name, 'site');
}

/*
 * load complete template list from path
 * @param string $path
 * @param string $path_type
 * @return array
 */
function template_getList($path, $path_type='camyks') {
    return plugin_getList($path.'/template', $path_type);
}
?>