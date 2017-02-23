<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Tool Library
 * Creation Date	: Oct 2007
 * Last Modif Date      : Oct 2007
 * 
 * cookie functions 
 */

/*
 * Read a cookie
 * 
 * @param string $name
 * @return mixed 
 * @access public
 */
function cookie_get( $name ) {
  return ( isset( $_COOKIE[$name] ) ? $_COOKIE[$name] : null );
}

/*
 * Write a cookie
 * 
 * @param string $name
 * @param mixed $value
 * @param int $ttl ( in days )
 * @return boolean
 * @access public
 */
function cookie_save( $name, $value, $ttl=0 ) {
  $date = time() + 60 * 60 * 24 * ( (is_numeric($ttl) and $ttl >= 0) ? $ttl : 0 );
  setcookie( $name, $value, $date );
}

/*
 * Extend cookie time to live 
 *
 * @param string $name
 * @param int $ttl ( in days )
 * @return boolean 
 * @access public
 */
function cookie_extendTTL( $name, $ttl=0 ) {
  $value = cookie_get( $name );
  cookie_save( $name, $value, $ttl );
}
?>