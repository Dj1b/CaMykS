<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Tool Library
 * Creation Date	: Jun 2005
 * Last Modif Date	: Jun 2005
 *
 * Password static methods
*/
define ("PWD_TYPE_MD5",		0 );
define ("PWD_TYPE_DEFAULT",	PWD_TYPE_MD5 );


/*
 * encode password
 * @param string $str
 * @param string $type
 * @return string
 * @access
 */
function password_encode( $str, $type = "" ) {
  switch ( $type ) {
  case PWD_TYPE_MD5:
    return password_md5Encode( $str );
  default :
    return password_encode( $str, PWD_TYPE_DEFAULT );
  }
}



/*
 * md5 encoding
 * @param string $str
 * @return string
 * @access public
 */
function password_md5Encode( $str ) {
  return md5( $str );
}
?>