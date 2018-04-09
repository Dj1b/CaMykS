<?php
/**
 * @brief Cookie related methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/cookie.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Read a cookie.
 * @param string $name
 * @return mixed 
 */
function cookie_get($name) {
    return (isset($_COOKIE[$name])?$_COOKIE[$name]:null);
}

/**
 * Write a cookie.
 * @param string $name
 * @param mixed $value
 * @param int $ttl (in days)
 * @return boolean
 */
function cookie_save($name, $value, $ttl=0) {
    $date = time() + 60 * 60 * 24 * ((is_numeric($ttl) and $ttl >= 0) ? $ttl : 0);
    setcookie($name, $value, $date);
}

/**
 * Extend cookie time to live.
 * @param string $name
 * @param int $ttl (in days)
 * @return boolean 
 */
function cookie_extendTTL($name, $ttl=0) {
    $value = cookie_get($name);
    cookie_save($name, $value, $ttl);
}
?>