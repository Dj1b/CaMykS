<?php
/**
 * @brief Password specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/password.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
/*
 * @def PWD_TYPE_MD5
 */
define("PWD_TYPE_MD5",     0);

/*
 * @def PWD_TYPE_DEFAULT
 */
define("PWD_TYPE_DEFAULT", PWD_TYPE_MD5);

/*
 * Encode password.
 * @param string $str
 * @param string $type
 * @return string
 */
function password_encode($str, $type="") {
    switch ($type) {
        case PWD_TYPE_MD5:
            return password_md5Encode($str);
        default :
            return password_encode($str, PWD_TYPE_DEFAULT);
    }
}

/*
 * Encode password with MD5.
 * @param string $str
 * @return string
 */
function password_md5Encode($str) {
    return md5($str);
}
?>