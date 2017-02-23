/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Mar 2005
 * Last Modif Date	: Mar 2005
 *
 * Client environment methods
 */

function tool_getClientBrowserType ( ) {
  if ( navigator.appName == 'Netscape' ) {
    return 'netscape';
  } else {
    return 'explorer';
  }
}

function tool_getClientBrowserName ( ) {
  app = navigator.userAgent.toLowerCase();
  
  if ( app.indexOf ('safari') ) {
    return 'safari';
  } else if ( app.indexOf ('firefox') ) {
    return 'firefox';
  } else if ( app.indexOf ('msie') ) {
    return 'explorer';
  } else if ( app.indexOf ('icab') ) {
    return 'icab';
  } else if ( app.indexOf ('opera') ) {
    return 'opera';
  }
  return 'unknown';
}

function tool_getClientBrowserFullName ( ) {
  app = navigator.userAgent.toLowerCase();
  
  if ( app.indexOf ('safari') ) {
    return 'Safari';
  } else if ( app.indexOf ('firefox') ) {
    return 'Firefox';
  } else if ( app.indexOf ('msie') ) {
    return 'Explorer';
  } else if ( app.indexOf ('icab') ) {
    return 'iCab';
  } else if ( app.indexOf ('opera') ) {
    return 'Opera';
  }
  return 'unknown';
}

