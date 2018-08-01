/**
 * @brief SmartGallery Input scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/SmartGallery/js/SmartGallery.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Jul 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * html object to clone
 */
var htmlDiv = document.createElement('div');
var htmlImg = document.createElement('img');


/*
 * Smart Gallery Main Object
 * str name : its own name
 */
function SmartGallery ( name ) {
  /* object name */
  this.name = name;
  /* selection size ( in item ) */
  this.selSize = 6;
  /* item list */
  this.items = new Array();
  /* item displayed */
  this.currentItem = 0;
  /* page of item displayed */
  this.currentPage = 0;
  /* page count */
  this.countPage = null;
  /* thumb size ( in pixel ) */
  this.thumbWidth = 80;
  this.thumbHeight = 60;
  /* main item */
  this.imageWidth = 0;
  this.imageHeight = 0;
  this.imageTitle = false;
  this.imageDesc = true;
  /* urls */
  this.imageURL='';
  this.thumbURL='';
  this.themeURL='';
  /* sliding method */
  this.slidingMethod = 'page'; /* one */
  /* sliding speed */
  this.slidingAccel = 1;
  this.slidingSpeed = 30;
  this.slidingInterval = 25;
  this.slidingRun = false;
  /* sliding temp value */
  this.sInterval = null;
  this.sTargetItem = null;
  this.sFirstItem = null;
  this.sTargetPage = null;
  this.sSpeed = null;
}

/*
 * Update Smart Gallery object config with urls values
 */
SmartGallery.prototype.set_urlsConfig = function ( theme, image, thumb ) {
  this.imageURL = image;
  this.thumbURL = thumb;
  this.themeURL = theme;
}

/*
 * Update Smart Gallery object config with main image values
 */
SmartGallery.prototype.set_imageConfig = function ( width, height, title, desc ) {
  this.imageWidth = width;
  this.imageHeight = height;
  this.imageTitle = title;
  this.imageDesc = desc;
}

/*
 * Update Smart Gallery object config with thumb values
 */
SmartGallery.prototype.set_thumbConfig = function ( width, height, count ) {
  this.selSize = count;
  this.thumbWidth = width;
  this.thumbHeight = height;
}

/*
 * Update Smart Gallery object config with sliding values
 */
SmartGallery.prototype.set_slidingConfig = function ( method, accel, speed, interval ) {
  this.slidingMethod = method;
  this.slidingAccel = accel;
  this.slidingSpeed = speed;
  this.slidingInterval = interval;
}

/*
 * Initialise Smart Gallery  object
 */
SmartGallery.prototype.initGallery = function () {
  /* set theme */
  this.initGalleryTheme();

  /* build HTML for each item */
  for ( var i=0; i<this.items.length; i++ ) {
    this.items[i].buildHTML();
  }

  /* get page count */
  this.countPage = Math.ceil(this.items.length/this.selSize);

  /* if not defined, randomly choose a currentItem */
  if ( this.currentItem == 0 ) {
    this.currentItem = parseInt(Math.random()*this.items.length);
  }
  /* set page from currentItem */
  this.currentPage = Math.floor(this.currentItem/this.selSize);

  /* complete last page */
  for ( var i=this.items.length; i<this.selSize*this.countPage; i++ ) {
    this.addItem({id:i});
    this.items[i].buildEmptyHTML();
  }

  /*  build gallery HTML and select item */
  if ( this.buildHTML() )
    this.selectItem( this.currentItem );
}

/*
 * Initialise Smart Gallery theme
 */
SmartGallery.prototype.initGalleryTheme = function() {
  /* theme elements */
  this.rightArrow = this.themeURL+'/rightarrow.gif';
  this.leftArrow = this.themeURL+'/leftarrow.gif';
  this.emptyDot = this.themeURL+'/emptydot.gif';
  this.coloredDot = this.themeURL+'/coloreddot.gif';
}

/*
 * Build Smart Gallery HTML
 */
SmartGallery.prototype.buildHTML = function () {

  if ( !document.getElementById('sg_div_root_'+this.name))
    return false;

  /* get root div item */
  var root = document.getElementById('sg_div_root_'+this.name);
  root.style.width = Math.max((this.thumbWidth+20)*this.selSize+100, this.imageWidth+40) + 'px';
  if ( this.imageHeight > 0 ) {
    root.style.height = (this.imageHeight+20)+'px';
  }

  /* add main div */
  var main = htmlDiv.cloneNode(true);
  main.setAttribute ('id', 'sg_main_'+this.name );
  main.setAttribute ('align', 'center' );
  main.className = 'sg_main';
  root.appendChild ( main );

  /* add title div */
  if ( this.imageTitle ) {
    var title = htmlDiv.cloneNode(true);
    title.setAttribute ('id', 'sg_title_'+this.name );
    title.className = 'sg_title';
    root.appendChild ( title );
  }

  /* add desc div */
  if ( this.imageDesc ) {
    var desc = htmlDiv.cloneNode(true);
    desc.setAttribute ('id', 'sg_desc_'+this.name );
    desc.className = 'sg_desc';
    root.appendChild ( desc );
  }

  /* add pager div */
  if ( this.countPage > 1 ) {
    var pager = htmlDiv.cloneNode(true);
    pager.setAttribute ('id', 'sg_pager_'+this.name );
    pager.className = 'sg_pager';
    pager.setAttribute('align', 'center');
    for ( var i=0; i<this.countPage; i++ ) {
      var page = htmlImg.cloneNode(true);
      if ( i == this.currentPage  ) {
	page.setAttribute('src', this.coloredDot );
	page.className = 'sg_pagerselected';
      } else {
	page.setAttribute('src', this.emptyDot );
	/* M$ IE bug specific code */
	if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
	  page.onclick = new Function (  this.name+'.moveToPage('+i+');' );
	} else {
	  page.setAttribute('onClick', this.name+'.moveToPage('+i+');');
	}
	page.className = 'sg_pagerfree';
      }
      page.setAttribute('border', 0 );
      pager.appendChild( page );
    }
    root.appendChild( pager );
  }

  /* add bottom div */
  var bottom = htmlDiv.cloneNode(true);
  bottom.className = 'sg_bottom';
  bottom.setAttribute('align', 'center');
  root.appendChild( bottom );

  /* add panel div */
  var panel = htmlDiv.cloneNode(true);
  panel.className = 'sg_panel';
  panel.style.width = ((this.thumbWidth+20)*this.selSize+100) + 'px';
  bottom.appendChild( panel );

  /* left arrow */
  var leftarrowdiv = htmlDiv.cloneNode(true);
  leftarrowdiv.className = 'sg_navarrow';
  leftarrowdiv.setAttribute('align', 'center');
  leftarrowdiv.style.height = (this.thumbHeight+10) + 'px';
  panel.appendChild ( leftarrowdiv );

  if ( this.countPage > 1 ) {
    var leftarrowimg = htmlImg.cloneNode(true);
    leftarrowimg.setAttribute('src', this.leftArrow );
    leftarrowimg.setAttribute('border', 0 );
    leftarrowimg.style.position = 'relative';
    leftarrowimg.style.top = this.thumbHeight/2 + 'px';

    if ( this.slidingMethod == 'one' ) {
      /* M$ IE bug specific code */
      if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
	leftarrowimg.onclick = new Function ( this.name+ '.movePreviousItem();' );
      } else {
	leftarrowimg.setAttribute('onClick', this.name+ '.movePreviousItem();');
      }
    } else if ( this.slidingMethod == 'page' ) {
      /* M$ IE bug specific code */
      if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
	leftarrowimg.onclick = new Function ( this.name+ '.movePreviousPage();' );
      } else {
	leftarrowimg.setAttribute('onClick', this.name+ '.movePreviousPage();');
      }
    }
    leftarrowimg.className='sg_arrow';
    leftarrowdiv.appendChild ( leftarrowimg );
  }
  /* add sel div */
  var sel = htmlDiv.cloneNode(true);
  sel.className = 'sg_sel';
  sel.setAttribute('id', 'sg_sel_'+this.name );
  sel.setAttribute('align', 'center');
  sel.style.height = (this.thumbHeight+10)+'px';
  sel.style.width = (this.thumbWidth+20)*this.selSize+'px';

  /* add all thumb */
  var begin = this.currentPage*this.selSize;
  var end = (this.currentPage+1)*this.selSize;

  for ( var i=begin; i<end; i++ ) {
    myitem = this.items[i].divObj;
    myitem.style.left = ( i-begin )*(this.thumbWidth+20)+'px';
    sel.appendChild ( myitem );
  }

  panel.appendChild( sel );
  /* right arrow  */
  var rightarrowdiv = htmlDiv.cloneNode(true);
  rightarrowdiv.className = 'sg_navarrow';
  rightarrowdiv.setAttribute('align', 'center');
  rightarrowdiv.style.height = (this.thumbHeight+10) + 'px';
  panel.appendChild ( rightarrowdiv );

  if ( this.countPage > 1 ) {
    var rightarrowimg = htmlImg.cloneNode(true);
    rightarrowimg.setAttribute('src', this.rightArrow );
    rightarrowimg.setAttribute('border', 0 );
    rightarrowimg.style.position = 'relative';
    rightarrowimg.style.top = this.thumbHeight/2 + 'px';

    if ( this.slidingMethod == 'one' ) {
      /* M$ IE bug specific code */
      if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
	rightarrowimg.onclick = new Function ( this.name+ '.moveNextItem();' );
      } else {
	rightarrowimg.setAttribute('onClick', this.name+ '.moveNextItem();');
      }
    } else if ( this.slidingMethod == 'page' ) {
      /* M$ IE bug specific code */
      if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
	rightarrowimg.onclick =  new Function ( this.name+ '.moveNextPage();' );
      } else {
	rightarrowimg.setAttribute('onClick', this.name+ '.moveNextPage();');
      }
    }
    rightarrowimg.className='sg_arrow';
    rightarrowdiv.appendChild ( rightarrowimg );
  }
  return true;
}

/*
 * Update Smart Gallery item list
 * param array attr : item attributes
*/
SmartGallery.prototype.addItem = function ( attr ) {
   var sgi = new SmartGalleryItem (this.name, this.items.length);
   for ( a in attr ) {
     sgi[a] = attr[a];
   }
   this.items[this.items.length] = sgi;
}

/*
 * Select Smart Gallery item
 * int : item id/index in item list
 */
SmartGallery.prototype.selectItem = function ( itemid ) {

  /* update current item */
  this.currentItem = itemid;

  main = document.getElementById('sg_main_'+this.name);
  img = main.getElementsByTagName('img');
  if ( img.length > 0 ) {
    img = img[0];
    img.src = this.imageURL+'/'+this.items[itemid].image;
  } else {
    /* select current item */
    img = htmlImg.cloneNode(true);
    img.setAttribute('src', this.imageURL+'/'+this.items[itemid].image );
    if ( this.imageWidth > 0 )
      img.setAttribute('width', this.imageWidth );
    if ( this.imageHeight > 0 )
      img.setAttribute('height', this.imageHeight );

    img.setAttribute('border', 0);
    /* add current item main image */
    document.getElementById('sg_main_'+this.name).appendChild ( img );
  }

  /* update title */
  if ( this.imageTitle ) {
    document.getElementById('sg_title_'+this.name).innerHTML = this.items[itemid].title;
  }

  /* update desc */
  if ( this.imageDesc ) {
    document.getElementById('sg_desc_'+this.name).innerHTML = this.items[itemid].desc;
  }
}

/*
 * Prepare Smart Gallery thumbs sliding to given page
 * int page : page to go
 */
SmartGallery.prototype.moveToPage = function ( page ) {
  /* check if function is already running */
  if ( this.slidingRun )
    return;
  this.slidingRun = true;
  /* set target values */
  this.sTargetPage = page;
  this.sTargetItem = ( this.sTargetPage )*this.selSize;
  /* set other values */
  this.sFirstItem = math_mod(this.currentPage*this.selSize+1, this.items.length );
  this.sSpeed = 0;
  /* add item */
  sel = document.getElementById('sg_sel_'+this.name);
  i = math_mod( (this.sFirstItem + this.selSize-1), this.items.length );
  myitem = this.items[i].divObj;
  myitem.style.left =  (this.thumbWidth+20)*this.selSize+'px';
  sel.appendChild ( myitem );
  /* create sliding interval */
  this.sInterval = window.setInterval( this.name+'.moveRight()', this.slidingInterval );
}

/*
 * Prepare Smart Gallery thumbs sliding to next page
 */
SmartGallery.prototype.moveNextPage = function ( ) {
  /* check if function is already running */
  if ( this.slidingRun )
    return;
  this.slidingRun = true;
  /* set target values */
  this.sTargetPage = math_mod ( this.currentPage+1, this.countPage );
  this.sTargetItem = ( this.sTargetPage )*this.selSize;
  /* set other values */
  this.sFirstItem = math_mod(this.currentPage*this.selSize+1, this.items.length );
  this.sSpeed = 0;
  /* add item */
  sel = document.getElementById('sg_sel_'+this.name);
  i = math_mod( (this.sFirstItem + this.selSize-1), this.items.length );
  myitem = this.items[i].divObj;
  myitem.style.left = (this.thumbWidth+20)*this.selSize+'px';
  sel.appendChild ( myitem );

  /* create sliding interval */
  this.sInterval = window.setInterval( this.name+'.moveRight()', this.slidingInterval );
}

/*
 * Prepare Smart Gallery thumbs sliding to next page
 */
SmartGallery.prototype.movePreviousPage = function ( ) {
  /* check if function is already running */
  if ( this.slidingRun )
    return;
  this.slidingRun = true;
  /* set target values */
  this.sTargetPage = math_mod ( this.currentPage-1, this.countPage );
  this.sTargetItem = ( this.sTargetPage )*this.selSize;

  /* set other values */
  this.sFirstItem = math_mod(this.currentPage*this.selSize-1, this.items.length );
  this.sSpeed = 0;
  /* add item*/
  sel = document.getElementById('sg_sel_'+this.name);
  i = this.sFirstItem;
  myitem = this.items[i].divObj;
  myitem.style.left = -(this.thumbWidth+20)+'px';
  sel.appendChild ( myitem );

  /* create sliding interval */
  this.sInterval = window.setInterval( this.name+'.moveLeft()', this.slidingInterval );
}

/*
 * Prepare Smart Gallery thumbs sliding to next item
 */
SmartGallery.prototype.moveNextItem = function ( ) {

}

/*
 * Prepare Smart Gallery thumbs sliding to previous item
 */
SmartGallery.prototype.movePreviousItem = function ( ) {

}

/*
 * Slide Smart Gallery thumbs to the right
 */
SmartGallery.prototype.moveRight = function () {
  /* get DIV element */
  var sel = document.getElementById('sg_sel_'+this.name);
  var ts = sel.getElementsByTagName('div');
  ts = this.sortDivs( ts );
  var firstItemPos = html_getLeftStylePosition(ts[0]);

  /* check sliding position */
  if ( this.sTargetItem == this.sFirstItem && firstItemPos-this.sSpeed <= -(this.thumbWidth+20) ) {
    /* slide finished */
    /* set all element to ending position */
    for ( var i = 0; i<ts.length; i++ ) {
      html_updateLeftStylePosition( ts[i], -(firstItemPos+this.thumbWidth+20));
    }
    /* delete useless item */
    sel.removeChild( ts[0] );

    /* generic stop */
    this.moveStop();
    return;
  } else if ( firstItemPos-this.sSpeed <= -(this.thumbWidth+20)  ) {
    /* sliding has reach first item */
    /* delete useless item */
    sel.removeChild( ts[0] );
    /* set first item to next item */
    this.sFirstItem = math_mod( ( this.sFirstItem+1 ), this.items.length );
    /* add new item */
    i = math_mod( (this.sFirstItem + this.selSize-1), this.items.length );
    myitem = this.items[i].divObj;
    myitem.style.left = (this.selSize*(this.thumbWidth+20)+firstItemPos+(this.thumbWidth+20))+'px';
    sel.appendChild ( myitem );
    /* update child array */
    ts = sel.getElementsByTagName('div');
    ts = this.sortDivs( ts );
    /* update pager */
    if ( this.slidingMethod == 'page' ) {
      p = Math.floor ( this.sFirstItem / this.selSize );
      if ( this.currentPage != p ) {
        this.currentPage = p;
        this.updatePager ( );
      }
    }
  }
  /* update speed */
  if ( this.sSpeed < this.slidingSpeed ) {
    this.sSpeed += this.slidingAccel;
  }

  /* move all items */
  for ( var i = 0; i<ts.length; i++ ) {
    html_updateLeftStylePosition( ts[i], -1*(this.sSpeed) );
  }


}

/*
 * Slide Smart Gallery thumbs to the left
 */
SmartGallery.prototype.moveLeft = function ( ) {
  /* get DIV element */
  var sel = document.getElementById('sg_sel_'+this.name);
  var ts = sel.getElementsByTagName('div');
  ts = this.sortDivs( ts );
  var firstItemPos = html_getLeftStylePosition(ts[0]);

  /* check sliding position */
  if ( this.sTargetItem == this.sFirstItem && firstItemPos+this.sSpeed >= 0 ) {
    /* slide finished */
    /* set all element to ending position */
    for ( var i = 0; i<ts.length; i++ ) {
      html_updateLeftStylePosition( ts[i], -firstItemPos );
    }
    /* delete useless item */
    sel.removeChild( ts[this.selSize] );

    /* generic stop */
    this.moveStop();
    return;
  } else if ( firstItemPos+this.sSpeed >= 0  ) {
    /* sliding has reach first item */
    /* delete useless item */
    sel.removeChild( ts[this.selSize] );
    /* set first item to next item */
    this.sFirstItem = math_mod( ( this.sFirstItem-1 ), this.items.length );
    /* add new item */
    i = this.sFirstItem;
    myitem = this.items[i].divObj;
    myitem.style.left = (-(this.thumbWidth+20)+firstItemPos)+'px';
    sel.appendChild ( myitem );
    /* update child array */
    ts = sel.getElementsByTagName('div');
    ts = this.sortDivs( ts );
    /* update pager */
    if ( this.slidingMethod == 'page' ) {
      p = Math.floor ( this.sFirstItem / this.selSize );
      if ( this.currentPage != p ) {
        this.currentPage = p;
        this.updatePager ( );
      }
    }
  }
  /* update speed */
  if ( this.sSpeed < this.slidingSpeed ) {
    this.sSpeed += this.slidingAccel;
  }

  /* move all items */
  for ( var i = 0; i<ts.length; i++ ) {
    html_updateLeftStylePosition( ts[i], this.sSpeed );
  }
}

/*
 * Stop Smart Gallery thumbs slide
*/
SmartGallery.prototype.moveStop = function ( ) {
  // garbage all sliding values
  this.sFirstItem = null;
  this.sTargetItem = null;
  this.sSpeed = null;
  clearInterval(this.sInterval);
  if ( this.slidingMethods == 'page' ) {
    this.currentPage = this.sTargetPage;
    // update pager
    this.updatePager ( );
  }
  this.slidingRun = false;
}

/*
 * Sort Smart gallery thumbs by left position
 */
SmartGallery.prototype.sortDivs = function ( divs ) {
  var ts = new Array();
  var pos = ts.length;
  var l = 0;

  for ( var i=0; i<divs.length; i++ ) {
    l = html_getLeftStylePosition( divs[i] );
    pos = ts.length;
    for ( var j=0; j<ts.length; j++ ) {
      if ( l < html_getLeftStylePosition (ts[j]) ){
        pos = j;
        break;
      }
    }
    for ( var j=ts.length-1; j>=pos; j-- ) {
      ts[j+1] = ts[j];
    }

    ts[pos] = divs[i];
  }
  return ts;
}

/*
 * Update SmartGallery gallery pager
 */
SmartGallery.prototype.updatePager = function ( ) {
  page = this.currentPage;
  /* get pager and pages items */
  pager = document.getElementById('sg_pager_'+this.name);
  pages = pager.getElementsByTagName('img');

  /* check page value validity */
  if ( page < 0 || page > pages.length )
    return;

  /* update all pages before selected one */
  for ( var i=0; i<page; i++ ) {
    pages[i].setAttribute('src', this.emptyDot );
    // M$ IE bug specific code
    if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
      pages[i].onclick =  new Function ( this.name+ '.moveToPage('+i+');' );
    } else {
      pages[i].setAttribute('onClick', this.name+'.moveToPage('+i+');');
    }
    pages[i].className = 'sg_pagerfree';
  }

  /* update selected page */
  pages[i].setAttribute('src', this.coloredDot );
  if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
    pages[i].onclick =  new Function ( 'void(0);' );
  } else {
    pages[i].setAttribute('onClick', 'void(0);');
  }
  pages[i].className = 'sg_pagerselected';

  /* update all pages after selected one */
  for ( var i=page+1; i<pages.length; i++ ) {
    pages[i].setAttribute('src', this.emptyDot );
    if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
      pages[i].onclick =  new Function ( this.name+ '.moveToPage('+i+');' );
    } else {
      pages[i].setAttribute('onClick', this.name+'.moveToPage('+i+');');
    }
    pages[i].className = 'sg_pagerfree';
  }
}

/*
 * Smart Gallery Item Object
 */
function SmartGalleryItem ( pName, idx ) {
  this.parentName = pName;
  this.index = idx;
  this.type = null;
  this.alt = null;
  this.image = null;
  this.width = null;
  this.height = null;
  this.thumb = null;
  this.title = null;
  this.desc = null;
  this.divObj = '';
}

/*
 * Build HTML for Smart Gallery Item thumb
 */
SmartGalleryItem.prototype.buildHTML = function () {
  var main = htmlDiv.cloneNode(true);
  main.setAttribute('id', this.index );
  main.style.height = (eval(this.parentName).thumbHeight+10) + 'px';
  main.className = 'sg_thumb';

  var thumb = htmlImg.cloneNode(true);
  thumb.setAttribute('src', eval(this.parentName).thumbURL+'/'+this.thumb );
  thumb.setAttribute('width', eval(this.parentName).thumbWidth );
  thumb.setAttribute('height', eval(this.parentName).thumbHeight );
  thumb.setAttribute('border', 0);
  /* M$ IE bug specific code */
  if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
    thumb.onclick =  new Function (  this.parentName+'.selectItem('+this.index+');' );
  } else {
    thumb.setAttribute('onClick', this.parentName+'.selectItem('+this.index+');');
  }
  thumb.className = 'sg_thumb';
  main.appendChild( thumb );
  this.divObj = main;
}

/*
 * Build Empty HTML for Smart Gallery Item thumb
 */
SmartGalleryItem.prototype.buildEmptyHTML = function () {
  var main = htmlDiv.cloneNode(true);
  main.setAttribute('id', this.index );
  main.style.height = (eval(this.parentName).thumbHeight+10) + 'px';
  main.className = 'sg_thumb';

  this.divObj = main;
}
