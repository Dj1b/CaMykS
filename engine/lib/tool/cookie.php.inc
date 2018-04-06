<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Engine / Tool Library
 * Creation Date    : Oct 2007
 * Last Modif Date  : Apr 2018
 * 
 * cookie related functions 
 */

/*
 * Read a cookie
 * @param string $name
 * @return mixed 
 */
function cookie_get($name) {
    return (isset($_COOKIE[$name])?$_COOKIE[$name]:null);
}

/*
 * Write a cookie
 * @param string $name
 * @param mixed $value
 * @param int $ttl (in days)
 * @return boolean
 */
function cookie_save($name, $value, $ttl=0) {
    $date = time() + 60 * 60 * 24 * ((is_numeric($ttl) and $ttl >= 0) ? $ttl : 0);
    setcookie($name, $value, $date);
}

/*
 * Extend cookie time to live 
 * @param string $name
 * @param int $ttl (in days)
 * @return boolean 
 */
function cookie_extendTTL($name, $ttl=0) {
    $value = cookie_get($name);
    cookie_save($name, $value, $ttl);
}
?>