/**
 * @brief Client side scripts related to cookies.
 * @details Engine / Javascript tool library
 * @file engine/data/js/tool/cookies.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Apr 2008
 * @date Modification: Apr 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
 
/**
 * Return cookie value.
 * @param string name
 * @return string
 */
function cookie_get(name) {
    if (document.cookie.length > 0) {
        pos = document.cookie.indexOf(name + '=');
        if (pos != -1) { 
            pos = pos + name.length+1; 
            end = document.cookie.indexOf(';', pos);
            if (end == -1) 
                end = document.cookie.length;
            return unescape(document.cookie.substring(pos, end));
        } 
    }
    return '';
}

/**
 * Save cookie.
 * @param string name
 * @param string value
 * @param int ttl
 * @return void
 */
function cookie_save(name, value, ttl) {
    /* set time to live date */
    if (ttl != null && parseInt(ttl)> 0) {
        var ttldate=new Date();
        ttldate.setDate(ttldate.getDate()+parseInt(ttl));
        ttl = ";expires="+ttldate.toGMTString();
    } else {
        ttl = '';
    }
    /* save cookie */
    document.cookie = name + "=" + escape(value) + ttl;
}

/**
 * Update cookie ttl.
 * @param string name
 * @param int ttl
 * @return void
 */
function cookie_extendTTL(name, ttl) {
    value = cookie_get(name);
    cookie_save(name, value, ttl);
}
