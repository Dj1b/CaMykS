/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Scripts
 * Create Date	       	: Oct 2007
 * Last Modif Date	: Oct 2007
 * 
 * Admin_SecurityTools Module Javascripts
 */

/*
 * delete IP filter rule link with confirmation
 * @param integer id
 * @return void
 * @access private
 */
function admin_securitytools_deleteIPFilterRule( id ) {
  if ( deletefiprmessage && deletefiprurl) { 
    if ( confirm( deletefiprmessage ) ) {
      document.location.href = deletefiprurl+id;
    }
  }
}


/*
 * delete backup link with confirmation
 * @param integer id
 * @return void
 * @access private
 */
function admin_securitytools_deleteBackUp( id ) {
  if ( deletebackupmessage && deletebackupurl) { 
    if ( confirm( deletebackupmessage ) ) {
      document.location.href = deletebackupurl+id;
    }
  }
}
