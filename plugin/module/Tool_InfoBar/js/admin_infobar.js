/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Scripts
 * Create Date	    : Oct 2005
 * Last Modif Date	: Mar 2007
 *
 * Admin_InfoBar Module Admin Javascripts
 */

infobar_basetime = new Date().getTime();
infobar_updatemode = 0;
infobar_timeInterval = null;
infobar_sessionInterval = null;
infobar_refreshObject = null;

function admin_infobarengine_start ( duration, refresh, url ) {
  if ( admin_infobarengine_updateTime() )
    infobar_timeInterval = setInterval('admin_infobarengine_updateTime()', 30000);

  if ( duration > 0 ) {
    infobar_refreshObject = new CAjaxRequest('infobar_refreshObject');
    infobar_refreshObject._initialise(url, 'GET', 
				      admin_infobarengine_refreshAdminSession_success,
				      'xml', 
				      admin_infobarengine_refreshAdminSession_failed );

    infobar_sessionInterval = setInterval('admin_infobarengine_refreshAdminSession()', refresh);
  }
}

function admin_infobarengine_updateTime ( ) {
  if ( infobar_updatemode == 0 ) {
    d = new Date();
    if ( document.getElementById('infobar_daytime') ) {
      document.getElementById('infobar_daytime').innerHTML = infobar_basedate + d.getHours()+':'+d.getMinutes();
    } else {
      return false;
    }
    
    if ( document.getElementById('infobar_pagetime') ) {
    v = parseInt(( d.getTime() - infobar_basetime )/60000)+'m.';
    document.getElementById('infobar_pagetime').innerHTML = v;
    } else {
      return false;
    }
    return true;
  }
  return true;
}

function admin_infobarengine_refreshAdminSession() {
  if ( infobar_updatemode == 0 ) {
    infobar_updatemode = 1;
    infobar_loadTime = new Date().getTime();
    document.getElementById('infobar_pagetime').innerHTML = '<img src="'+infobar_refreshImage+'" alt="" border="0" />';;
    infobar_refreshObject._execute();
  }
}

function admin_infobarengine_refreshAdminSession_success() {
  if ( new Date().getTime() - infobar_loadTime < 2000 ) 
    setTimeout(admin_infobarengine_refreshAdminSession_reset, 2000);
  else
    admin_infobarengine_refreshAdminSession_reset();
}

  
function admin_infobarengine_refreshAdminSession_failed() {
  admin_infobarengine_refreshAdminSession_reset();
}

function admin_infobarengine_refreshAdminSession_reset() {
  infobar_updatemode = 0;
  admin_infobarengine_updateTime();
}

