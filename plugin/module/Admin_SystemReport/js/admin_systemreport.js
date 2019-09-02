/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Scripts
 * Create Date		: May 2007
 * Last Modif Date	: May 2007
 *
 * Admin_SystemReport javascript
*/

/*
 * delete log link with confirmation
 * @param integer id
 * @return void
 * @access private
 *
function admin_systemreport_deletelog ( id ) {
  if ( confirm(admin_systemreport_deletelogmessage) ) {
    document.location.href = admin_systemreport_deleteloglink+id;
  }
}
*/

/*
 * delete logs link width confirmation
 * @return void
 * @access private
 */
function admin_systemreport_deletelogs ( ) {
  if ( confirm(admin_systemreport_deletelogsmessage) ) {
    ids = reportList.get_checkedBoxes('selection');
    eval ('f=document.'+admin_systemreport_selectionform );
    f.mode.value="deletemulti";
    f.ids.value = ids.join(',');
    f.submit();
  }
}

/*
 * mark logs as read link
 * @return void
 * @access private
 */
function admin_systemreport_marklogsasread ( ) {
  if ( confirm(admin_systemreport_marklogsmessage) ) {
    ids = reportList.get_checkedBoxes('selection');
    eval ('f=document.'+admin_systemreport_selectionform );
    f.mode.value="markasreadmulti";
    f.ids.value = ids.join(',');
    f.submit();
  }
}
