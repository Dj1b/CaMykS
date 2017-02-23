/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Jun 2007
 * Last Modif Date	: Jun 2007
 *
 * Admin engine javascript methods
*/

adminengine_divs = new Array();

/* open modal popup 
 * @access public
 * @param string myobject
 * @return void
 */
function adminengine_modalPopupOpen( myobject ) {
  if ( !document.getElementById(myobject) )
    return;
  
  /* get DOM objects */
  popup = document.getElementById(myobject);
  popupbg = document.getElementById('adminengine_modalPopupBackground');
  body = document.getElementsByTagName('body')[0];
  
  /* disable all overflowed object in page */
  adminengine_divs = new Array();
  tags = document.getElementsByTagName('div');
  for ( var i=0; i<tags.length; i++ ) {
    if ( tags[i].style.overflow == 'auto' && tags[i].style.display == 'block' ) {
      tags[i].style.display = 'none';
      adminengine_divs[adminengine_divs.length] = tags[i]; 
    }
  }
  
  /* display background divs */
  popupbg.style.display='block';
  popupbg.style.width = Math.max(body.offsetWidth, document.documentElement.clientWidth) + 'px';
  popupbg.style.height = Math.max(body.offsetHeight, document.documentElement.clientHeight) + 'px';
    
  /*
  if ( document.getElementById('adminengine_main') ) {
    popupbg.style.width = document.getElementById('adminengine_main').offsetWidth + 'px';
    popupbg.style.height = document.getElementById('adminengine_main').offsetHeight + 'px';
    }*/

  popup.style.zIndex = popupbg.style.zIndex+1;
  popup.style.display = 'block';
  popup.style.left = (Math.min(body.offsetWidth, document.documentElement.clientWidth)-popup.offsetWidth)/2 + 'px';
  popup.style.top = (Math.min(body.offsetHeight, document.documentElement.clientHeight)-popup.offsetHeight)/2 + 'px';

  
  /*
  popup.style.top = ((body.offsetHeight-popup.offsetHeight)/2+document.body.scrollTop)+'px';
  popup.style.left = ((body.offsetWidth-popup.offsetWidth)/2+document.body.scrollLeft)+'px';
    
  
  if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
    /* M$ browser *
    popup.style.top = ((document.body.offsetHeight-popup.offsetHeight)/2+document.body.scrollTop)+'px';
    popup.style.left = ((document.body.offsetWidth-popup.offsetWidth)/2+document.body.scrollLeft)+'px';
  } else {
    /* Netscape, Safari, Opera, ... *
    popup.style.top = ((window.innerHeight-popup.offsetHeight)/2+document.body.scrollTop)+'px';
    popup.style.left = ((window.innerWidth-popup.offsetWidth)/2+document.body.scrollLeft)+'px';
  }*/
}

/* close modal popup
 * @access public
 * @param string myobject
 * @return void
 */ 
function adminengine_modalPopupClose( myobject ) {
  if ( !document.getElementById(myobject) )
    return;
  
  /* get div objects */
  popup = document.getElementById(myobject);
  popupbg = document.getElementById('adminengine_modalPopupBackground');
  
  /* hide objects */
  popup.style.display='none';
  popupbg.style.display='none';
  
  /* re-enable all overflowed object in page */
  for ( var i=0; i< adminengine_divs.length; i++ ) {
    adminengine_divs[i].style.display = 'block';
  }
}

/*
 * confirm link redirection
 * @param string link
 * @param string message
 * @return void
 * @access public
 */
function adminengine_confirmRedirect(link, message){
  if (confirm(message)===true)
    document.location.href=link;
}
