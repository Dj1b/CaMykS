/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Javascripts
 * Creation Date	: Apr 2008
 * Last Modif Date	: Apr 2008
 *
 * Admin_GenericBlogsManager scripts in viewcomments mode
 */

/*
 * delete comment with confirmation
 * @param integer commentid
 * @return void
 * @access private
 */
function genericblogsviewcomments_deleteComment(commentid) {
  if ( confirm(deleteCommentMessage) ) {
    document.location.href = deleteCommentLink+commentid;
  }
}

/*
 * change comment status
 * @param integer commentid
 * @return void
 * @access private
 */
function genericblogsviewcomments_updateCommentStatus(commentid) {
  if (! document.getElementById('comment_'+commentid+'_status') )
    return;

  select = document.getElementById('comment_'+commentid+'_status');
  value = select.options[select.options.selectedIndex].value;

  document.location.href = updateCommentStatusLink+commentid+'&status='+value;
}

