/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   : 1.0a
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Javascripts
 * Creation Date    : Jun 2010
 * Last Modif Date  : Jun 2010
 *
 * Content_GenericGlossaryViewer scripts
 */

/*
 * check for selected mode
 * @return void
 * @access private
 */
function genericglossaryviewer_swapModePanels(select) {
  type = select.options[select.options.selectedIndex].value;

  if ( type==0 ) {
    if (typeof(ctransition) != 'undefined') {
      /* execute camyks build-in transition if available */
      transParams = {};
      transParams['panel_in'] = 'glossary_pagemodepage';
      transParams['steps'] = 10;
      transParams['speed'] = 30;
      ctransition.execute_transparentPanelFadeIn(transParams);
    } else {
      document.getElementById('glossary_pagemodepage').style.display = 'block';
    }
  } else {
    if (typeof(ctransition) != 'undefined') {
      /* execute camyks build-in transition if available */
      transParams = {};
      transParams['panel_out'] = 'glossary_pagemodepage';
      transParams['steps'] = 10;
      transParams['speed'] = 30;
      ctransition.execute_transparentPanelFadeOut(transParams);
    } else {
      document.getElementById('glossary_pagemodepage').style.display = 'none';
    }
  }
}

/*
 * check all authors checkbox value
 * @return void
 * @access private
 */
function genericglossaryviewer_checkAllCategories() {
  form = eval('document.'+formName);
  i = 0;
  if ( form.categoryall.checked == true ) {
    while ( eval('form.category'+i) ) {
      category = eval('form.category'+i);
      category.checked = true;
      category.disabled = true;
      i++;
    }
  } else {
    while ( eval('form.category'+i) ) {
      category = eval('form.category'+i);
      category.disabled = false;
      i++;
    }
  }
}
