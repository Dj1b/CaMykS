<?php
/**
 * @brief CaMykS Static methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/statics.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Kill camyks.
 * @return void
 */
function camyks_kill() {
    global $camyks;
    $camyks->kill();
    $camyks = null;
}
?>