/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Sep 2005
 * Last Modif Date      : Sep 2007
 *
 * ContentPage object javascript : tree object
 */

/* main construtor */
function ContentPageTree ( levels ) {
  /* init */
  this.levels = levels;
  
  /* vars */
  this.openedsheet = -1;
  this.opened = new Array();
  this.lines = new Array();
  this.items = new Array();
  this.rollovercss = null;
  this.standartcss = null;
  this.selectedcss = null;
}

/* initialise ContentPageTree */
ContentPageTree.prototype.initialise = function ( first, overcss, stdcss, selcss ) {
  /* init first line */
  this.opened[0] = first;
  this.lines[0] = new Array();
  
  /* init all other lines */
  for ( var i=1; i<this.levels; i++ ) {
    this.opened[i] = -1;
    this.lines[i] = new Array();
  }

  /* set css */
  this.rollovercss = overcss;
  this.standartcss = stdcss;
  this.selectedcss = selcss;
}

/* add div item to line */
ContentPageTree.prototype.buildline = function ( line, id, path, name, url  ) {
  this.items[id] = new ContentPageTreeItem( id, path, name, url );
  l = this.lines[line].length;
  this.lines[line][l] = id;
}

/* close same level and children item and open selected one */
ContentPageTree.prototype.openitem = function ( line, path ) {
  
  index = -1;
  /* check if line line exists */
  if ( line >= this.lines.length ) {
    return;
  } 
  /* check if 'id' item exists in 'line' line */
  for ( var i = 0; i< this.lines[line].length; i++ ) {
    if ( this.items[this.lines[line][i]].path == path ) {
      index = i;
      break;
    }
  }
  if ( index == -1 ) {
    /* error : item not found or parent has no child */
    /* alert ( 'error : item not found' ); */
    return;
  }
  
  /* check if already open */
  if ( this.opened[line] == path ) {
    
  }
  
  /* close item and all children */
  for ( var i=line; i<this.levels; i++ ) {
    if ( this.opened[i] != -1 ) {
      document.getElementById ( this.opened[i] ).style.display = 'none';
      document.getElementById ( 'td_'+this.opened[i] ).className = this.standartcss;
      this.opened[i] = -1;
    }
  }
  /* open item */
  this.opened[line] = path;
  document.getElementById( path ).style.display = 'block';
  document.getElementById( 'td_'+path ).className = this.selectedcss;
}

/* rollover */
ContentPageTree.prototype.rolloveritem = function ( level, itemid ) {
  document.getElementById( 'td_'+itemid ).className = this.rollovercss;
}


/* rollover */
ContentPageTree.prototype.rolloutitem = function ( level, itemid ) {
  if ( this.opened[level] == itemid ) 
    document.getElementById ( 'td_'+itemid ).className = this.selectedcss;
  else
    document.getElementById ( 'td_'+itemid ).className = this.standartcss;
}


/*
 * ContentPageTreeItem object
 * @param integer id
 * @param string path
 * @param string name
 * @param string url
 * @access private
 */
function ContentPageTreeItem ( id, path, name, url ) {
  this.id = id;
  this.path = path;
  this.name = name;
  this.url = url;
}

/*
 * check if given page is a parent
 * @param integer page
 * @return boolean result
 * @access private
 */
ContentPageTreeItem.prototype.checkParent = function( page ) {
  path = this.path.split("-");
  for ( i in path )
    if ( path[i] == page )
      return false;
  return true;
}
