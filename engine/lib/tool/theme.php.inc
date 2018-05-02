<?php
/**
 * @brief Themes specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/theme.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * Load theme.
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
 * Load complete theme list from path.
 * @param string $path
 * @param string $path_type
 * @return array
 */
function theme_getList($path, $path_type='camyks') {
    return plugin_getList($path.'/theme', $path_type);
}
?>