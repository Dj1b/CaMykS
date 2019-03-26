<?php
/**
 * @brief Password specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/password.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jun 2005
 * @date Modification: Mar 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
/**
 * @def PWD_TYPE_MD5
 */
define("PWD_TYPE_MD5",     0);

/**
 * Encode password.
 * @param string $pwd
 * @param string $algo
 * @param string $salt
 * @return string
 */
function password_encode($pwd, $algo='', $salt='') {
    switch ($algo) {
        case 128:
        case 'sha512':
            return hash('sha512', $pwd.$salt);
        case 96:
        case 'sha384':
            return hash('sha384', $pwd.$salt);
        case 64:
        case 'sha256':
            return hash('sha256', $pwd.$salt);
        case 40:
        case 'sha1':
            return hash('sha1', $pwd.$salt);
        case PWD_TYPE_MD5:
        case 32:
        case 'md5':
        default :
            return hash('md5', $pwd.$salt);
    }
}

/**
 * Check password.
 * @param string $pwd
 * @param string $hash
 * @param string $algo
 * @param string $salt
 * @return boolean
 */
function password_check($pwd, $hash, $algo=null, $salt='') {
    if ($algo == null) $algo = strlen($hash);
    return ($hash == password_encode($pwd, $algo, $salt));
}

/**
 * Encode password with MD5.
 * @param string $str
 * @return string
 * @deprecated
 */
function password_md5Encode($str) {
    return md5($str);
}
?>
