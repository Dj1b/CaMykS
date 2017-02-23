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
 * Admin_GenericBlogsManager scripts in editnews mode
 */

var genericblogsmanager_tagInit = false;
var genericblogsmanager_tagTable = null;
var genericblogsmanager_tagMode = null;
var genericblogsmanager_tagEditor = null;
var genericblogsmanager_tagSelect = null;
var genericblogsmanager_tagInput = null;
var genericblogsmanager_tagCounter = null;

/*
 * initialise tag engine
 * @return void
 * @access private
 */
function genericblogsmanager_initialiseTagEngine( count) {
  /* get document form object */
  if (!(form=eval('document.'+genericblogsmanager_form+'')))
    return;

  /* get document main objects */
  if (!(genericblogsmanager_tagTable = document.getElementById('taglist')))
    return;

  if (!(genericblogsmanager_tagEditor = document.getElementById('tageditor')))
    return;

  if (!(genericblogsmanager_tagSelect = document.getElementById('tagselect')))
    return;

  if (!(genericblogsmanager_tagCounter = form.tagCounter))
    return;

  /* build other objects */
  genericblogsmanager_tagInput = html_getInputElement();
  genericblogsmanager_tagInput.name="tagInput";
  genericblogsmanager_tagInput.className="inputs";
  
  /* set engine mode */
  genericblogsmanager_tagMode = 'select';

  /* finalise tag initialisation */
  genericblogsmanager_tagInit = true;
}

/*
 * check tag selected item
 * @return void
 * @access private
 */
function genericblogsmanager_selectTag() {
  if ( genericblogsmanager_tagInit == false )
    return;

  if ( genericblogsmanager_tagSelect.options[genericblogsmanager_tagSelect.options.selectedIndex].value == '!other') {
    genericblogsmanager_tagEditor.removeChild(genericblogsmanager_tagSelect);
    genericblogsmanager_tagEditor.appendChild(genericblogsmanager_tagInput);
    genericblogsmanager_tagMode = 'input';
  }
}

/*
 * delete tag line
 * @param integet tagLine
 * @return void
 * @access private
 */
function genericblogsmanager_deleteTag(tagLine) {
  if ( genericblogsmanager_tagInit == false )
    return;
  if ( document.getElementById('tagline'+tagLine) )
    genericblogsmanager_tagTable.removeChild(document.getElementById('tagline'+tagLine));
}

/*
 * add tag
 * @return void
 * @access private
 */
function genericblogsmanager_addTag() {
  if ( genericblogsmanager_tagInit == false )
    return;

  /* get tag value */
  if ( genericblogsmanager_tagMode == 'select' ) {
    value = genericblogsmanager_tagSelect.options[genericblogsmanager_tagSelect.options.selectedIndex].value;
  } else {
    value = genericblogsmanager_tagInput.value;
  }

  /* check value */
  if ( value == '' )
    return;

  /* create tag line */
  line = html_getTrElement();
  line.id='tagline'+genericblogsmanager_tagCounter.value;

  textTD = html_getTdElement();
  textTD.className = 'content1';

  tagID = html_getInputElement();
  tagID.type = 'hidden';
  tagID.name = 'tag'+ genericblogsmanager_tagCounter.value + '_id';
  tagID.value = 0;

  tagValue = html_getInputElement();
  tagValue.type = 'hidden';
  tagValue.name = 'tag'+ genericblogsmanager_tagCounter.value + '_value';
  tagValue.value = value;

  textINPUT = html_getInputElement();
  textINPUT.type = 'text';
  textINPUT.className = 'inputs';
  textINPUT.disabled = true;
  textINPUT.value = value;
 
  textTD.appendChild(tagID);
  textTD.appendChild(tagValue);
  textTD.appendChild(textINPUT);

  buttonTD = html_getTdElement();
  buttonTD.className='content1';

  buttonIMG = html_getImgElement();
  buttonIMG.src = genericblogsmanager_minusImg;
  buttonIMG.alt = '';
  buttonIMG.border = 0;
  buttonIMG.setAttribute('onclick', 'genericblogsmanager_deleteTag('+genericblogsmanager_tagCounter.value+')');

  buttonTD.appendChild(buttonIMG);

  line.appendChild(textTD);
  line.appendChild(buttonTD);
  
  genericblogsmanager_tagTable.appendChild(line);

  /* reset engine */
  genericblogsmanager_tagCounter.value++;

  if ( genericblogsmanager_tagMode == 'input' ) {
    genericblogsmanager_tagInput.value = '';
    genericblogsmanager_tagEditor.removeChild(genericblogsmanager_tagInput);
    genericblogsmanager_tagEditor.appendChild(genericblogsmanager_tagSelect);
    genericblogsmanager_tagMode = 'select';
  }
  genericblogsmanager_tagSelect.options.selectedIndex = 0;
}
