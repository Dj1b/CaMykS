<?php
/**
 * @brief URL specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/url.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Check if provided urls are in the same domain
 * @param array $urls
 * @param boolean $strict check also subdomain if true
 * @return boolean result
 */
function url_areInSameDomain($urls=array(), $strict=false) {
    if (!is_array($urls))
      return false;

    $domain = '';
    foreach ($urls as $url) {
        /* Load hostname from url */
        $v = strToLower(parse_url($url, PHP_URL_HOST));
        
        if ($domain == '') {
            /* Initialise first value. */
            if ($strict)
                $domain = $v;
            else {
                $v = explode('.', $v);
                if (count($v) < 2)
                    return false;
                $domain = $v[count($v)-2].'.'.$v[count($v)-1];
            }
        } elseif ($strict) {
            /* Check domain in strict mode. */
            if ($domain != $v)
                return false;
        } else {
            /* Check domain in non-strict mode. */
            $v = explode('.', $v);
            if (count($v) < 2)
                return false;
            if ($domain != $v[count($v)-2].'.'.$v[count($v)-1])
                return false;
        }
    }
    return true;
}
?>