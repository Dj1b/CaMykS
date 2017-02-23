/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team
 * Camyks Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Javascripts
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 *
 * Inline popup scripts
 */

/* 
 * open modal popup 
 * @param string myobject
 * @access private
 * @return void
 */
function popup_openModal(myobject, params) {
  if ( !document.getElementById(myobject))
    return;

  /* default params */
  dParams = {'opacity':0.75, 'bkgdColor':'black'};

  /* check and merge default params with params */
  if (!params)
    params = dParams;
  else {
    for (var i in dParams) {
      if (!params[i])
	params[i] = dParams[i];
    }
  }

  /* check navigator */
  if (navigator.appName.indexOf("Microsoft")!=-1)
    nav = 'msie';
  else
    nav = 'real';
    
  /* load document body */
  body = document.getElementsByTagName('body')[0];
  
  /* create div background if it doesn't exist */
  if (!document.getElementById('popup_modalBkgd')) {
    d = document.createElement('div').cloneNode(true);
    d.id = 'popup_modalBkgd';
    d.style.position = 'absolute';
    d.style.left = 0;
    d.style.top = 0;
    d.style.background = params['bkgdColor'];
    d.style.opacity = params['opacity'];
    if (nav == 'msie')
      d.style.filter = 'alpha(opacity='+(params['opacity']*100)+')';
    d.style.display = 'none';
    d.style.width = '100%';
    body.appendChild(d);
  }
  
  /* get divs objects */
  popup = document.getElementById(myobject);
  popupBkgd = document.getElementById('popup_modalBkgd');
  
  /* display background divs */
  popupBkgd.style.display = 'block';
  popupBkgd.style.width = '100%';
  popupBkgd.style.height = Math.max(body.offsetHeight, document.documentElement.clientHeight) + 'px';

  popup.style.position = 'absolute';
  popup.style.top = 0;
  popup.style.left = 0;  
  popup.style.zIndex = popupBkgd.style.zIndex+1;
  popup.style.display = 'block';
  if ( nav == 'msie' ) {
    popup.style.top = ((document.documentElement.clientHeight-popup.offsetHeight)/2+document.documentElement.scrollTop)+'px';
    popup.style.left = ((body.offsetWidth-popup.offsetWidth)/2+document.body.scrollLeft)+'px';
  } else {
    popup.style.top = ((window.innerHeight-popup.offsetHeight)/2+window.pageYOffset)+'px';
    popup.style.left = ((window.innerWidth-popup.offsetWidth)/2+body.scrollLeft)+'px';
  }
}
  
/* 
 * close modal popup
 * @param string myobject
 * @return void
 * @access private
 */ 
function popup_closeModal(myobject) {
  if (!document.getElementById(myobject))
    return;

  /* get div objects */
  popup = document.getElementById(myobject);
  popupBkgd = document.getElementById('popup_modalBkgd');

  /* hide objects */
  popup.style.display='none';
  popupBkgd.style.display='none';
}
