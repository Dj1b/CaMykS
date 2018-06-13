/**
 * @brief Admin_SecurityTools Module client side scripts
 * @details Plugin / Module javascripts
 * @file plugin/module/Admin_SecurityTools/js/admin_securitytools.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Oct 2007
 * @date Modification: Jun 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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
