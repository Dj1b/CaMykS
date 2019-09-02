/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Javascripts
 * Creation Date	: Sep 2008
 * Last Modif Date	: Sep 2008
 *
 * Content_GoogleSearchresultsViewer scripts
 */

/*
 * window onload script
 * @return void
 * @access private
 */
function googlesearchresultsviewer_initialise() {
}

/*
 * reset gsr values
 * @return void
 * @access private
 */
function googlesearchresultsviewer_resetgsr() {
  if (confirm(locales['googlesearchresultsviewer_resetgsr'])===true) {
    if (typeof(ctransition) != 'undefined') {
      /* execute camyks build-in transition if available */
      transParams = {};
      transParams['panel_out'] = 'itemgsrpanel';
      transParams['panel_in'] = 'itemgsrimporterpanel';
      transParams['steps'] = 10;
      transParams['speed'] = 30;
      ctransition.execute_transparentPanelSwap(transParams);
    } else {
      /* execute simple swap */
      document.getElementById('itemgsrimporterpanel').style.display = 'none';
      document.getElementById('itemgsrpanel').style.display = 'block';
    }
  }
}

/*
 * import google searchresults code
 * @return void
 * @access private
 */
function googlesearchresultsviewer_importgsr() {
  /* get gsr code */
  code = googlesearchresultsviewer_form.gsrimporter.value;
  googlesearchresultsviewer_form.gsrimporter.value = '';
  /* check gsr code *
  if ( code.indexOf('<script') == -1 || code.indexOf('</script>') == -1 ) {
    alert( locales['googlesearchresultsviewer_invalidcode'] );
    return;
  } */
  /* get width value */
  myReg = new RegExp(/googleSearchFrameWidth = (\d+);/);
  myRegResult = myReg.exec(code);
  if ( myRegResult )
    googlesearchresultsviewer_form.sr_width.value = myRegResult[1];
  else {
    alert( locales['googlesearchresultsviewer_invalidcode'] );
    return;
  }

  /* get search domain value */
  myReg = new RegExp(/googleSearchDomain = "([^"]+)";/);
	myRegResult = myReg.exec(code);
	if ( myRegResult )
	  googlesearchresultsviewer_form.sr_searchdomain.value = myRegResult[1];
	else {
	  alert( locales['googlesearchresultsviewer_invalidcode'] );
	  return;
	}

   if (typeof(ctransition) != 'undefined') {
     /* execute camyks build-in transition if available */
     transParams = {};
     transParams['panel_out'] = 'itemgsrimporterpanel';
     transParams['panel_in'] = 'itemgsrpanel';
     transParams['steps'] = 10;
     transParams['speed'] = 30;
     ctransition.execute_transparentPanelSwap(transParams);
   } else {
     /* execute simple swap */
     document.getElementById('itemgsrimporterpanel').style.display = 'none';
     document.getElementById('itemgsrpanel').style.display = 'block';
  }
}
