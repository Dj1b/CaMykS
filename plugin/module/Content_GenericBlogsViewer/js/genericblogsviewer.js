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
 * Content_GenericBlogsViewer scripts
 */

/*
 * check all authors checkbox value
 * @return void
 * @access private
 */
function genericblogsviewer_checkAllAuthors() {
  form = eval('document.'+genericblogsviewerform);

  if ( form.authors_all.checked==true ) {
    i = 0;
    while ( eval('form.author'+i) ) {
      author = eval('form.author'+i);
      author.checked = true;
      author.disabled = true;
      i++;
    }
  } else {
    i = 0;
    while ( eval('form.author'+i) ) {
      author = eval('form.author'+i);
      author.disabled = false;
      i++;
    }
  }
}
