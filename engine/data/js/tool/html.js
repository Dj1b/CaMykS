/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / Javascript Lib
 * Creation Date	: Dec 2007
 * Last Modif Date	: Oct 2009
 *
 * HTML Javascript library
 */

var _htmlDivElement = document.createElement('div');
var _htmlImgElement = document.createElement('img');
var _htmlTableElement = document.createElement('table');
var _htmlTbodyElement = document.createElement('tbody');
var _htmlTrElement = document.createElement('tr');
var _htmlTdElement = document.createElement('td');
var _htmlTextareaElement = document.createElement('textarea');
var _htmlSelectElement = document.createElement('select');
var _htmlInputElement = document.createElement('input');
var _htmlSpanElement = document.createElement('span');
var _htmlAElement = document.createElement('a');

/*
 * return div element
 */
function html_getDivElement() {
  return _htmlDivElement.cloneNode(true);
}

/*
 * return img element
 */
function html_getImgElement() {
  return _htmlImgElement.cloneNode(true);
}

/*
 * return table element
 */
function html_getTableElement() {
  return _htmlTableElement.cloneNode(true);
}

/*
 * return tbody element
 */
function html_getTbodyElement() {
  return _htmlTbodyElement.cloneNode(true);
}

/*
 * return tr element
 */
function html_getTrElement() {
  return _htmlTrElement.cloneNode(true);
}

/*
 * return td element
 */
function html_getTdElement() {
  return _htmlTdElement.cloneNode(true);
}

/*
 * return textarea element
 */
function html_getTextareaElement() {
  return _htmlTextareaElement.cloneNode(true);
}

/*
 * return select element
 */
function html_getSelectElement() {
  return _htmlSelectElement.cloneNode(true);
}


/*
 * return input element
 */
function html_getInputElement() {
  return _htmlInputElement.cloneNode(true);
}

/*
 * return span element
 */
function html_getSpanElement() {
  return _htmlSpanElement.cloneNode(true);
}

/*
 * return a element
 */
function html_getAElement() {
  return _htmlAElement.cloneNode(true);
}
