/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team
 * CaMykS Version   : 1.0a
 * Object Version   : 1.0
 * Object Type      : Engine / JS Lib
 * Creation Date    : Apr 2008
 * Last Modif Date  : Apr 2008
 *
 * Cookie relative methods
 */

/*
 * get the value of a cookie
 * @param string name
 * @return string
 * @access public
 */
function cookie_get( name ) {
  if ( document.cookie.length > 0 ) {
    pos = document.cookie.indexOf(name + '=');
    if ( pos != -1 ) { 
      pos = pos + name.length+1; 
      end = document.cookie.indexOf(';', pos);
      if ( end == -1 ) 
        end = document.cookie.length;
      return unescape(document.cookie.substring(pos, end));
    } 
  }
  return '';
}

/*
 * save cookie
 * @param string name
 * @param string value
 * @param int ttl
 * @return void
 * @access public
 */
function cookie_save( name, value, ttl ) {
  /* set time to live date */
  if ( ttl != null && parseInt(ttl)> 0 ) {
    var ttldate=new Date();
    ttldate.setDate(ttldate.getDate()+parseInt(ttl));
    ttl = ";expires="+ttldate.toGMTString();
  } else {
    ttl = '';
  }
  /* save cookie */
  document.cookie = name + "=" + escape(value) + ttl;
}

/*
 * update cookie ttl
 * @param string name
 * @param int ttl
 * @return void
 * @access private
 */
function cookie_extendTTL( name, ttl ) {
  value = cookie_get(name);
  cookie_save(name, value, ttl);
}
