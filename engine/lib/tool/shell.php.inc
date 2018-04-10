<?php
/**
 * @brief Some shell actions
 * @details Engine / Tool Library
 * @file engine/lib/tool/shell.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Execute mv shell command.
 * @param string $from
 * @param string $to
 * @return mixed
 */
function shell_mv($from, $to) {
    return shell_exec('mv '.$from.' '.$to);
}

/**
 * Execute cp shell command.
 * @param string $from
 * @param string $to
 * @return mixed
 */
function shell_cp($from, $to) {
    return shell_exec('cp -R '.$from.' '.$to);
}

/**
 * Execute chmod shell command.
 * @param string $file
 * @param string $rights
 * @return mixed
 */
function shell_chmod($file, $rights) {
    return shell_exec('chmod -R '.$rights.' '.$file);
}

/**
 * Execute chgrp shell command.
 * @param string $file
 * @param string $grp
 * @return mixed
 */
function shell_chgrp($file, $grp) {
    return shell_exec('chgrp -R '.$grp.' '.$file);
}

/**
 * Execute chown shell command.
 * @param string $file
 * @param string $user
 * @return mixed
 */
function shell_chown($file, $user) {
    return shell_exec('chown -R '.$user.' '.$file);
}

/**
 * Execute ln shell command.
 * @param string $link
 * @param string $file
 * @return mixed
 */
function shell_ln($link, $file) {
    return shell_exec('ln -s '.$link.' '.$file);
}
?>