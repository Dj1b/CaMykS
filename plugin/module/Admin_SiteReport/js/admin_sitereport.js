/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Scripts
 * Create Date		: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Admin_SiteReport javascripts
 */

/*
 * on date check, enable or disable comment textarea
 * @return void
 * @access private 
 */
function admin_sitereport_anwsercheck ( ) {
  if ( !admin_sitereport_formName ) {
    return;
  }
  
  myform = eval('document.'+ admin_sitereport_formName );
  
  if ( myform.answer_date.checked ) 
    myform.answer_comment.disabled = false;
  else
    myform.answer_comment.disabled = true;
}

/*
 * enable/disable configuration file size case
 * @return void
 * @access private
 */
function admin_sitereport_checkallowedfiles() {
  if ( !admin_sitereport_configFormName ) {
    return;
  }
  myform = eval('document.'+ admin_sitereport_configFormName );
  myform.file_maxsize.disabled = !myform.file_allowed.checked;
}
