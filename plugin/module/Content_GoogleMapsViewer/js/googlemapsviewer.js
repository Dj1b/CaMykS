/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Javascripts
 * Creation Date	: Jul 2008
 * Last Modif Date	: Jul 2008
 *
 * Content_GoogleMapsViewer scripts
 */

/*
 * window onload script
 * @return void
 * @access private
 */
function googlemapsviewer_initialise() {
   googlemapsviewer_updatelinkpanel();
   googlemapsviewer_updatelinkstylespanel(true);
}

/*
 * check for link settings
 * @return void
 * @access private
 */
function googlemapsviewer_updatelinkpanel() {
  if ( googlemapsviewer_form.link_enabled.checked ) {
    document.getElementById('itemlinkpanel').style.display='block';
  } else {
    document.getElementById('itemlinkpanel').style.display='none';
  }
}

/*
 * check for link styles settings
 * @return void
 * @access private
 */
function googlemapsviewer_updatelinkstylespanel(first) {
  linkclass=googlemapsviewer_form.link_class.options[googlemapsviewer_form.link_class.selectedIndex].value;

  if ( linkclass==0 ) {
    if (!first && typeof(ctransition) != 'undefined') {
     /* execute camyks build-in transition if available */
     transParams = {};
     transParams['panel_in'] = 'itemlinkstylespanel';
     transParams['steps'] = 10;
     transParams['speed'] = 30;
     ctransition.execute_transparentPanelFadeIn(transParams);
    } else {
      document.getElementById('itemlinkstylespanel').style.display='block';
    }
  } else {
    if (!first && typeof(ctransition) != 'undefined') {
     /* execute camyks build-in transition if available */
     transParams = {};
     transParams['panel_out'] = 'itemlinkstylespanel';
     transParams['steps'] = 10;
     transParams['speed'] = 30;
     ctransition.execute_transparentPanelFadeOut(transParams);
    } else {
      document.getElementById('itemlinkstylespanel').style.display='none';
    }
  }
}

/*
 * reset map values
 * @return void
 * @access private
 */
function googlemapsviewer_resetmap() {
  if (confirm(locales['googlemapsviewer_resetmap'])===true) {
    if (typeof(ctransition) != 'undefined') {
      /* execute camyks build-in transition if available */
      transParams = {};
      transParams['panel_out'] = 'itemmappanel';
      transParams['panel_in'] = 'itemmapimporterpanel';
      transParams['steps'] = 10;
      transParams['speed'] = 30;
      ctransition.execute_transparentPanelSwap(transParams);
    } else {
      /* execute simple swap */
      document.getElementById('itemmapimporterpanel').style.display = 'none';
      document.getElementById('itemmappanel').style.display = 'block';
    }
  }
}

/*
 * import google maps code
 * @return void
 * @access private
 */
function googlemapsviewer_importmap() {
  /* get map code */
  code = googlemapsviewer_form.mapimporter.value;
  googlemapsviewer_form.mapimporter.value = '';
  /* check map code */
  if ( code.indexOf('<iframe') == -1 || code.indexOf('</iframe>') == -1 ) {
    alert( locales['googlemapsviewer_invalidcode'] );
    return;
  }
  /* get width & height values */
  myReg = new RegExp(/width="(\d+)"/);
	myRegResult = myReg.exec(code);
	if ( myRegResult )
	  googlemapsviewer_form.map_width.value = myRegResult[1];
	    
	myReg = new RegExp(/height="(\d+)"/);
	myRegResult = myReg.exec(code);
	if ( myRegResult )
	  googlemapsviewer_form.map_height.value = myRegResult[1];
	  
	/* get url & params */
	myReg = new RegExp(/src="([^"]+)"/);
	myRegResult = myReg.exec(code);
	if ( myRegResult )
	  url = myRegResult[1];
	else {
	  alert( locales['googlemapsviewer_invalidcode'] );
	  return;
	}
	    
	 myReg = new RegExp(/([^\?]+)\?([^\?]+)/);
	 myRegResult = myReg.exec(url);
	 if ( !myRegResult ) {
	   alert( locales['googlemapsviewer_invalidcode'] );
	   return;
	 }
	 
	 baseUrl = myRegResult[1];
	 urlParams = myRegResult[2];
	 urlParams = urlParams.split('&amp;');
	 paramsList = {}
	 finalParams = new Array();
	 for (i in urlParams) {
	   p = urlParams[i].split('=', 2);
	   paramsList[p[0]] = p[1];
	   if ( p[0] != 's' && p[0] != 'z' && p[0] != 'output' )
	     finalParams[finalParams.length] = urlParams[i];
	 }
	 if ( paramsList['z'] )
	     googlemapsviewer_form.map_zoom.selectedIndex = parseInt(paramsList['z'])-1;
	 if ( paramsList['s'] )
	     googlemapsviewer_form.map_code.value = paramsList['s'];
	 googlemapsviewer_form.map_baseurl.value = baseUrl + '?' + finalParams.join('&amp;');

   /* update google link */
   link = document.getElementById('googleaccesslink');
   url = googlemapsviewer_form.map_baseurl.value+'&amp;z='+paramsList['z']+'&amp;source=embed';
   url = url.replace(/&amp;/gi, '&');
   link.setAttribute('href', url);
  
   if (typeof(ctransition) != 'undefined') {
     /* execute camyks build-in transition if available */
     transParams = {};
     transParams['panel_out'] = 'itemmapimporterpanel';
     transParams['panel_in'] = 'itemmappanel';
     transParams['steps'] = 10;
     transParams['speed'] = 30;
     ctransition.execute_transparentPanelSwap(transParams);
   } else {
     /* execute simple swap */
     document.getElementById('itemmapimporterpanel').style.display = 'none';
     document.getElementById('itemmappanel').style.display = 'block';
  }
}