<?php
/*
 * CaMyks Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Engine / Tool Library
 * Creation Date    : Jun 2005
 * Last Modif Date  : Apr 2018
 * 
 * Shell methods
 */

/*
 * execute mv shell command
 * @param string $from
 * @param string $to
 * @return mixed
 */
function shell_mv($from, $to) {
    return shell_exec('mv '.$from.' '.$to);
}

/*
 * execute cp shell command
 * @param string $from
 * @param string $to
 * @return mixed
 */
function shell_cp($from, $to) {
    return shell_exec('cp -R '.$from.' '.$to);
}

/*
 * execute chmod shell command
 * @param string $file
 * @param string $rights
 * @return mixed
 */
function shell_chmod($file, $rights) {
    return shell_exec('chmod -R '.$rights.' '.$file);
}

/*
 * execute chgrp shell command
 * @param string $file
 * @param string $grp
 * @return mixed
 */
function shell_chgrp($file, $grp) {
    return shell_exec('chgrp -R '.$grp.' '.$file);
}

/*
 * execute chown shell command
 * @param string $file
 * @param string $user
 * @return mixed
 */
function shell_chown($file, $user) {
    return shell_exec('chown -R '.$user.' '.$file);
}

/*
 * execute ln shell command
 * @param string $link
 * @param string $file
 * @return mixed
 */
function shell_ln($link, $file) {
    return shell_exec('ln -s '.$link.' '.$file);
}
?>