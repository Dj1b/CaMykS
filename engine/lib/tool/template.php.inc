<?php
/**
 * @brief Templates specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/template.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Load template.
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

/**
 * Load complete template list from path.
 * @param string $path
 * @param string $path_type
 * @return array
 */
function template_getList($path, $path_type='camyks') {
    return plugin_getList($path.'/template', $path_type);
}
?>