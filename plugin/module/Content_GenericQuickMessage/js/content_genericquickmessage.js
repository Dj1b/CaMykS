/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Scripts
 * Create Date		: Nov 2007
 * Last Modif Date	: Nov 2007
 *
 * Content_GenericQuickMessage scripts
 */

var cgqm_panels = new Array();

function content_genericquickmessage_swapPanels( show, gqm ) {
  if ( document.getElementById('gqm'+cgqm_panels[gqm]) ) {
    document.getElementById('gqm'+cgqm_panels[gqm]).style.display="none";
  }
  
  if ( document.getElementById('gqm'+show+gqm) ) {
    document.getElementById('gqm'+show+gqm).style.display="block";
  }
  
  cgqm_panels[gqm] = show+gqm;
}
