<?php
/**
 * @brief Inputs specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/input.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2015 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Load input.
 * @param string $name
 * @param string $path_type
 * @return Input object
 */
function input_get($name, $path_type=false) {
    if ($path_type !== false)
        return plugin_get('input', $name, $path_type);
    if (($p = plugin_get('input', $name, 'camyks')) !== false)
        return $p;
    return plugin_get('input', $name, 'site');
}

/**
 * Load complete input list from path.
 * @param string $path
 * @param string $path_type
 * @return array
 */
function input_getList($path, $path_type='camyks') {
    return plugin_getList($path.'/input', $path_type);
}
?>