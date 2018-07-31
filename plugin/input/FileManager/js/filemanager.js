/**
 * @brief FileManager Input scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/FileManager/js/filemanager.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Jun 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* link opener object */
function FileManager ( popurl ) {
  this.popurl = popurl;
  this.params = new Array();
}

FileManager.prototype.addParam = function ( name, value ) {
  this.params[name] = value;
}


FileManager.prototype.openFileManager = function ( file ) {
  this.popurl += '&fm_browser_path='+file;
  for ( name in this.params ) {
    this.popurl += '&'+name+'='+this.params[name];
  }

  fmw = window.open( this.popurl,
		     '',
		     'width=750,height=520,scrollbars=auto,resize=no,toolbar=no,menubar=no,personalbar=no');
  if ( fmw ) {
    fmw.focus();
  }
}



/* generic methods */

/* get last selected object */
function filemanager_getLastSelectedObject() {
  folder='';
  for ( i=0; i<filemanager_selectedobjects.length; i++ ) {
    if ( filemanager_selectedobjects[i] == '' )
      break;
    folder = filemanager_selectedobjects[i];
  }
  return folder;
}


/* get last selected folder */
function filemanager_getLastSelectedFolder() {
  return filemanager_selectedfolder;
}

/* action methods */
/* select */
function filemanager_select_file ( ) {
  /* get selected file */
  file = filemanager_getLastSelectedObject();
  /* send value to callback */
  eval ('opener.'+callback_function+'("'+folderurl + '/' + file+'")');
  /* close window */
  window.close();
}



/* reload */
function filemanager_action_reload( ) {
  document.input_filemanager.fm_engine_action.value='reload';
  document.input_filemanager.fm_browser_path.value = filemanager_getLastSelectedObject();
  document.input_filemanager.submit();
}

/* upload a file */
function filemanager_action_file() {
  folder = filemanager_getLastSelectedFolder();
  document.input_filemanager.fm_engine_action.value='file';
  document.input_filemanager.fm_browser_path.value = folder;
  document.getElementById('filemanager_filepopuptxt').innerHTML='/'+folder;
  adminengine_modalPopupOpen('filemanager_filepopup');
}

/* uploading a file */
function filemanager_action_fileLoading() {
  adminengine_modalPopupClose('filemanager_filepopup');
  adminengine_modalPopupOpen('filemanager_fileloadingpopup');
  document.input_filemanager.submit();
}

/* create new folder */
function filemanager_action_folder() {
  folder = filemanager_getLastSelectedFolder();
  document.input_filemanager.fm_engine_action.value='folder';
  document.input_filemanager.fm_browser_path.value = folder;
  document.getElementById('filemanager_folderpopuptxt').innerHTML='/'+folder;
  adminengine_modalPopupOpen('filemanager_folderpopup');
}

/* trash object */
function filemanager_action_trash() {
  folder = filemanager_getLastSelectedObject();
  document.input_filemanager.fm_engine_action.value='trash';
  document.input_filemanager.fm_browser_path.value = folder;
  document.getElementById('filemanager_trashpopuptxt').innerHTML='/'+folder;
  adminengine_modalPopupOpen('filemanager_trashpopup');
}

/* change view */
function filemanager_action_change_view ( view ) {
  folder = filemanager_getLastSelectedObject();
  document.input_filemanager.fm_engine_action.value = 'change_view';
  document.input_filemanager.fm_browser_path.value = folder;
  document.input_filemanager.fm_browser_view.value = view;
  document.input_filemanager.submit();
}

/*
 *
 */
function filemanager_action_download ( ) {
  file = filemanager_getLastSelectedObject();
  folder = filemanager_getLastSelectedFolder();
  /*
  if ( file != folder ) {
    window.open(filemanager_rooturl+'/'+file);
  }
  */
  if ( file != '' && file != folder ) {
    document.input_filemanager.fm_engine_action.value = 'download';
    document.input_filemanager.fm_browser_path.value = file;
    document.input_filemanager.submit();
  }
  return;
}

/*
 *
 */
function filemanager_action_rename( ) {
  folder = filemanager_getLastSelectedObject();
  if ( folder != '' ) {
    /* get item name */
    item_name = folder.substring(folder.lastIndexOf('/')+1);
    /* update form values */
    document.input_filemanager.fm_engine_action.value = 'rename';
    document.input_filemanager.fm_browser_path.value = folder;
    document.input_filemanager.fm_newname.value = item_name;
    document.getElementById('filemanager_renamepopuptxt').innerHTML='/'+folder;
    adminengine_modalPopupOpen('filemanager_renamepopup');
  }
  return;
}


/* column view specific */

/* column tree main navigation method */
function filemanager_columnSelectObject( object, level, type ) {
  /* get real action to execute */
  if ( filemanager_selectedobjects[level] == object
       && ( filemanager_selectedobjects.length == level+1
	    || filemanager_selectedobjects[level+1] == '' )) {
    action = 'unselect';
  } else {
    action = 'select';
  }

  /* disable all object from this level and all child levels */
  for (var i=level; i<filemanager_maxlevel; i++ ) {
    if ( filemanager_selectedobjects[i] ) {
      fmitem = filemanager_selectedobjects[i];
      document.getElementById('obj'+fmitem).style.display = 'none';
      document.getElementById('line'+fmitem).className = 'unselectable eTableLine0';
      filemanager_selectedobjects[i] = '';
      filemanager_selectedfolder = '';
    }
  }

  /* enable object */
  if ( action == 'select' && object!= '' && document.getElementById('obj'+object) ) {
    document.getElementById('obj'+object).style.display='block';
    document.getElementById('line'+object).className = 'unselectable eTableSubHeader';
    filemanager_selectedobjects[level] = object;
    if ( type == 1 )
      filemanager_selectedfolder = object;
    else if ( level == 0 )
      filemanager_selectedfolder = '';
    else
      filemanager_selectedfolder = filemanager_selectedobjects[level-1];
  }
}

/* column tree line selection */
function filemanager_columnSwapLine( object, level, swap ) {
  if ( filemanager_selectedobjects[level] != object ) {
    document.getElementById('line'+object).className = 'unselectable eTableLine'+ swap;
  }
}

/* list view specific */

/**/
function filemanager_listSelectObject( object, level, type ) {

  /* disable previous element */
  o = filemanager_selectedobjects[0];

  if ( document.getElementById('object'+o) ) {
    filemanager_selectedobjects[0] = '';
    document.getElementById('object'+o).style.background = '#FFFFFF';
  }


  /* select new element */
  if ( o != object && document.getElementById('object'+object) ) {
    filemanager_selectedobjects[0] = object;
    document.getElementById('object'+object).style.background = '#DEDEDE';

    if ( type == 1 )
      filemanager_selectedfolder = object;
    else if ( level == 0 )
      filemanager_selectedfolder = '';
    else {
      filemanager_selectedfolder = object.substring(0, object.lastIndexOf('/'));
    }
  }
}

function filemanager_listOpenObject( object ) {
  if ( document.getElementById('children'+object ) && document.getElementById('arrow'+object ) ) {
    elmt = document.getElementById('children'+object );
    arrow = document.getElementById('arrow'+object );
    if ( elmt.style.display == "none" ) {
      elmt.style.display = 'block';
      arrow.src = image_url + 'arrow_opened.gif';
    } else {
      elmt.style.display = 'none';
      arrow.src = image_url + 'arrow_closed.gif';
    }
  }
}

/* column tree line selection */
function filemanager_listSwapLine( object, level, swap ) {
    if ( filemanager_selectedobjects[0] != object ) {
	document.getElementById('object'+object).style.background = (swap==1?'#DEDEDE':'white');
    }
}
