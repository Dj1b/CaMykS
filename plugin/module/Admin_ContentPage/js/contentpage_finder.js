/**
 * @brief Admin_ContentPage module finder scripts
 * @details Plugin / Module Scripts
 * @file plugin/module/Admin_ContentPage/js/contentpage_finder.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Sep 2005
 * @date Modification: Sep 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

var contentPage_pageitem = null;
var contentPage_columnitem = null;
var contentPage_modelitem = null;

/*
 * open page action menu
 */
function contentPage_openPageActions( id ) {
  contentPage_pageitem = id;
  globalCMenu.updateParent('pageActionsMenu', 'pageActionsButton'+id );
  globalCMenu.select('pageActionsMenu');
}

/*
 * close page action menu
 */
function contentPage_closePageActions ( ) {
  globalCMenu.unselect('pageActionsMenu');
}

/*
 *
 */
function contentPage_pageActionModify ( ) {
  url = action_base_url+'&mode=modify&page_id='+ contentPage_pageitem;
  document.location.href = url;
}

/*
 *
 */
function contentPage_pageActionDuplicate( ) {

}

/*
 *
 */
function contentPage_pageActionDelete( ) {
  url = action_base_url+'&mode=delete&page_id='+ contentPage_pageitem;
  adminengine_confirmRedirect(url, deletePageMessage);
}

/*
 *
 */
function contentPage_pageActionPreview( ) {
  url = site_base_url+'/'+cpt.items[contentPage_pageitem].url+'?preview=forced';
  w = window.open( url, '', '');
}

/*
 *
 */
function contentPage_pageActionW3CValidation( ) {
  url = w3c_base_url+site_base_url+'/'+cpt.items[contentPage_pageitem].url;
  w = window.open( url, '', '');
}

/*
 *
 */
function contentPage_pageActionMove() {
  movedpage = contentPage_pageitem;
  if ( document.getElementById('action_paste_moved') ) {
    document.getElementById("action_paste_moved").style.display="block";
  }
  contentPage_closePageActions();
}

/*
 *
 */
function contentPage_pageActionMoveUp( ) {
  url = action_base_url+'&mode=moveup&page_id='+ contentPage_pageitem;
  document.location.href = url;
}

/*
 *
 */
function contentPage_pageActionMoveDown( ) {
  url = action_base_url+'&mode=movedown&page_id='+ contentPage_pageitem;
  document.location.href = url;
}

/*
 * open column action menu
 */
function contentPage_openColumnActions( id ) {
  contentPage_columnitem = id;
  globalCMenu.updateParent('columnActionsMenu', 'columnActionsButton'+id );
  globalCMenu.select('columnActionsMenu');
}

/*
 * close column action menu
 */
function contentPage_closeColumnActions( ) {
  globalCMenu.unselect('columnActionsMenu');
}

/*
 *
 */
function contentPage_columnActionNewPage() {
  url = action_base_url+'&mode=modify&page_id=0&parent_id='+ contentPage_columnitem;
  document.location.href = url;
}

/*
 *
 */
function contentPage_columnActionPasteMoved() {
  if ( cpt.items[contentPage_columnitem] && cpt.items[contentPage_columnitem].checkParent(movedpage)) {
    if ( movedpage > 0 && confirm( movePageMessage ) ) {
      url = action_base_url+'&mode=move&page_id='+movedpage+'&parent_id='+ contentPage_columnitem;
      document.location.href = url;
    }
  } else {
    alert(movePageFailedMessage);
  }
  contentPage_closeColumnActions();
}


/*
 * open model actions menu
 */
function contentPage_openModelActions( id ) {
  contentPage_modelitem = id;
  globalCMenu.updateParent('modelActionsMenu', 'model'+id );
  globalCMenu.select('modelActionsMenu');
}

/*
 * edit model link
 */
function contentPage_modelActionEdit() {
  url = action_base_url+'&mode=modify&page_id='+ contentPage_modelitem;
  document.location.href = url;
}

/*
 * delete model link
 */
function contentPage_modelActionDelete() {
  if ( confirm( deleteModelMessage ) ) {
    url = action_base_url+'&mode=delete&page_id='+ contentPage_modelitem;
    document.location.href = url;
  }
}

/*
 *
 */
function contentPage_requestSelectPage() {

  pc_item = 0;
  pc_value = 0;
  /* check if 'id' item exists */
  for ( i=0; i < cpt.opened.length; i++ ) {
    if ( cpt.opened[i] != -1 ) {
      pc_item = cpt.opened[i];
    }
  }

  for ( i in cpt.items ) {
    if ( cpt.items[i].path == pc_item ) {
      switch ( pc_mode ) {
      case 'pageid':
	    pc_value = cpt.items[i].id;
	    break;
      case 'pagename':
	    pc_value = cpt.items[i].name;
	    break;
      case 'pageidname':
	    pc_value = cpt.items[i].id + '","' + cpt.items[i].name;
	    break;
      case 'pagelink':
	    pc_value = cpt.items[i].url;
	    break;
      default:
	    return;
      }
      break;
    }
  }
  if ( pc_value != 0 ) {
    eval ('opener.'+pc_callback+'("'+pc_value+'");');
    window.close();
  }
  return;
}
