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
 * Admin_GenericBlogsManager scripts
 */

/* variables */
var genericblogsmanager_currentTag = null;

/*
 * delete link with confirmation
 * @param integer linkid
 * @return void
 * @access private
 */
function genericblogsmanager_deleteLink(linkid) {
  if ( confirm(deleteLinkMessage) ) {
    document.location.href = deleteLinkLink+linkid;
  }
}

/*
 * delete news with confirmation
 * @param integer newsid
 * @return void
 * @access private
 */
function genericblogsmanager_deleteNews(newsid) {
  if ( confirm(deleteNewsMessage) ) {
    document.location.href = deleteNewsLink+newsid;
  }
}

/*
 * set tag name editable
 * @param integer tag
 * @return void
 * @access private
 */
function genericblogsmanager_editTag(tag) {
  /* check if given tag exists */
  if ( ! document.getElementById('tagPlus'+tag) )
    return;

  /* revert current tag objects */
  genericblogsmanager_revertTagObjects();

  /* save given tag objects */
  genericblogsmanager_saveTagObjects(tag);

  /* add tag editor */
  genericblogsmanager_buildTagEditor(tag);
}

/*
 * save tag
 * @return void
 * @access private
 */
function genericblogsmanager_saveTag() {
  /* check if current tag exists */
  if ( genericblogsmanager_currentTag == null )
    return;

  /* get tag value */
  form = eval('document.'+genericblogsmanager_tagEditorForm);
  if ( genericblogsmanager_currentTag['index'] == 0 )
    form.tag.value = '';
  else
    form.tag.value = genericblogsmanager_currentTag['tagName'];
  
  /* execute form submission */
  form.submit();
}

/*
 * cancel tag edition
 * @return void
 * @access private
 */
function genericblogsmanager_cancelTagEdition() {
  /* revert current tag objects */
  genericblogsmanager_revertTagObjects();
}

/*
 * delete tag with confirmation
 * @param string tag
 * @return void
 * @access private
 */
function genericblogsmanager_deleteTag(tag) {
  if ( deleteTagMessage && confirm(deleteTagMessage) ) {
    document.location.href = deleteTagLink+tag;
  }
}

/*
 * revert tag line objects 
 * @return void
 * @access private
 */
function genericblogsmanager_revertTagObjects() {
  if ( genericblogsmanager_currentTag == null )
    return;

  /* revert tag line */
  index = genericblogsmanager_currentTag['index'];
  document.getElementById('tagName'+index).innerHTML = genericblogsmanager_currentTag['tagName'];
  document.getElementById('tagPlus'+index).innerHTML = genericblogsmanager_currentTag['tagPlus'];
  document.getElementById('tagMinus'+index).innerHTML = genericblogsmanager_currentTag['tagMinus'];

  /* reset current tag value */
  genericblogsmanager_currentTag = null;
}

/* 
 * save tag line objects
 * @param integer tag
 * @return void
 * @access private
 */
function genericblogsmanager_saveTagObjects(tag) {
  /* check if current tag already exists */
  if ( genericblogsmanager_currentTag != null )
    return;

  /* check if given tag exists */
  if ( !document.getElementById('tagPlus'+tag) )
    return;

  /* save line as current tag */
  genericblogsmanager_currentTag = {'index':tag,
				    'content':document.getElementById('tagName'+tag).textContent,
				    'tagName':document.getElementById('tagName'+tag).innerHTML,
				    'tagPlus':document.getElementById('tagPlus'+tag).innerHTML,
				    'tagMinus':document.getElementById('tagMinus'+tag).innerHTML};
}

/*
 * build tag editor line objects 
 * @param integer tag
 * @return void
 * @access private
 */
function genericblogsmanager_buildTagEditor(tag) {
  /* build text input */
  input = html_getInputElement();
  input.type = 'text';
  input.className = 'inputs';
  input.maxLength = 32;
  input.name = 'tagvalue';

  if ( genericblogsmanager_currentTag['index'] > 0 ) {
    input.value = genericblogsmanager_currentTag['content'];
  }
  document.getElementById('tagName'+tag).innerHTML = '';
  document.getElementById('tagName'+tag).appendChild(input);

  /* build save button */
  save = document.getElementById('tagPlusButton').cloneNode(true);
  document.getElementById('tagPlus'+tag).innerHTML = '';
  document.getElementById('tagPlus'+tag).appendChild(save);

  /* build cancel button */
  cancel = document.getElementById('tagMinusButton').cloneNode(true);
  document.getElementById('tagMinus'+tag).innerHTML = '';
  document.getElementById('tagMinus'+tag).appendChild(cancel);
}
