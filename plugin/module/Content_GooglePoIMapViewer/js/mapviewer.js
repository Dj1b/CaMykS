/*
 * CaMykS Engine
 * Developed by	    : Ideogram Design
 * Author	    : JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Create Date	    : Mar 2010
 * Last Modif Date  : Mar 2010
 * 
 * Content_GooglePoIMapViewer scripts
 */
 
function PoIMapViewer(name) {
  this.name = name;
  this.loaded = false;
  this.params = {};
  this.loader = null;
  this.locales = {};
  
  /* map variables */
  this.map = null;
  this.mapPoints = new Array();
  this.mapIcons = new Array();
  this.markerManager = null;

  /*
   * add parameter
   * @param string name
   * @param mixed value
   * @return void
   * @access public
   */
  this.set_param = function(param, value, subvalue) {
    if ( subvalue != undefined && this.params[param] )
      this.params[param][value] = subvalue;
    else
      this.params[param] = value;
  };
   
  /*
   * return param value from name
   * @param mixed param
   * @return mixed
   * @access public
   */
  this.get_param = function(param, value) {
    if (value != undefined)
      if (this.params[param][value])
        return this.params[param][value];
    if (this.params[param])
      return this.params[param];
    return false;
  };
  
  /*
   * add locale
   * @param string name
   * @param mixed value
   * @return void
   * @access public
   */
  this.add_locale = function(name, value) {
    this.locales[name] = value;
  };
  
  /*
   * get locale
   * @param string name
   * @return void
   * @access public
   */
  this.get_locale = function(name) {
    if (this.locales[name])
      return this.locales[name];
    return name;
  };
  
  /*
   * add map point
   * @param integer id
   * @param array params
   * @return void
   * @access public
   */
  this.add_mapPoint = function(id, params) {
    this.mapPoints[id] = params;
  };

  /*
   * add icon
   * @param integer id
   * @param array params
   * @return void
   * @access public
   */
  this.add_mapIcon = function(id, params) {
    this.mapIcons[id] = params;
  };
  
  /* 
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {

    /* initialise default params */
    if ( this.get_param('GooglePoIMapClass') == false )
      this.set_param('GooglePoIMapClass', 'eTableHeader');
    if ( this.get_param('GooglePoIMapDescTitleClass') == false )
      this.set_param("GooglePoIMapDescTitleClass", "eTitle3");

    /* initialise ajax loader */
    this.loader = new CAjaxRequest(this.name+'.loader');
    this.loader._initialise(null, 'POST', this.name+'._receiveResult', 'xml', this.name+'._receiveError');
    
    /* initialise loader next point */
    this.set_param('nextPoint', 0);
    this.set_param('useManager', 0);
    
    /* initialise google map */     
    this.map = new GMap2(document.getElementById("GooglePoIMapBox"));
    this.map.setUIToDefault();
    GEvent.addListener(this.map, "tilesloaded", function(){pmv.update_selectedPointIcon();});
    GEvent.addListener(this.map, "zoomend", function(){pmv.update_selectedPointIcon();});
    
    /* initialise point manager */
    if ( this.params['useManager'] == 1 )
      this.markerManager = new MarkerManager(this.map);

    /* initialise selected point */
    this.set_param('selectedPoint', 0);
    
    /* initialise map icons */
    for (i in this.mapIcons) {
      icon = this.mapIcons[i];
      gicon = new GIcon();
      gicon.iconSize = new GSize (icon['mainWidth'], icon['mainHeight']);
      gicon.image = icon['mainImg'];
      gicon.iconAnchor = new GPoint(icon['anchorX'], icon['anchorY']);
      if ( icon['shdwImg'] != '' ) {
				gicon.shadowSize = new GSize(icon['shdwWidth'], icon['shdwHeight']);
				gicon.shadow = icon['shdwImg'];
      }
      this.mapIcons[i]['GIcon'] = gicon;
    }
    
    /* initialise google map points */
    for (i in this.mapPoints)
      this.add_point2Map(i);

    /* start google map engine */
    this.map.setCenter(new GLatLng(0,0) , this.get_param('GMapDefZoom'));
      
    /* check mobile params */
    if (this.get_param('hasTabs') == 1) {
    	/* check for tab management */
    	if (document.getElementById('GooglePoIListTab'))
    		this.set_param("GooglePoITabClass", document.getElementById('GooglePoIListTab').className);
    	else
    		this.set_param("GooglePoITabClass", 'eContent1');
    	if (document.getElementById('GooglePoIMapTab'))
    		this.set_param("GooglePoITabSelClass", document.getElementById('GooglePoIMapTab').className);
    	else
    		this.set_param("GooglePoITabSelClass", 'eContent2');
    }
    
    /* check geolocalisation params */
    if ( this.get_param('GooglePoIMapGeoStatus') == 1) {
    	this.set_param('GooglePoIMapGeoMarker', '');
    }
      
    /* set engine as loaded */
    this.loaded = true;
  };
  
  /*
   * update selected point
   * @param integer point
   * @return void
   * @access public
   */
  this.select_point = function(point, from) {
    
    if ( point == this.params['selectedPoint']) {
    	if (this.get_param('hasTabs') == 1 && from != 'map' )
    		this.select_mapTab();
    	if (this.get_param('hasTabs') == 1 && from == 'map' )
    		this.select_descTab();
    	else
      	return;
    }
    
    if ( this.loader._resultStatus != 'idle' ) {
      this.params['nextPoint'] = point;
      return;
    }
     
    pointObject = document.getElementById('GooglePoIMapItem'+point);
    
    /* unselect previous point */
    s = this.get_param('selectedPoint');
    if (s > 0 && document.getElementById('GooglePoIMapItem'+s)) {
      c = document.getElementById('GooglePoIMapItem'+s);
      if ( this.get_param('GooglePoIMapLastClass') !== false )
	c.className = this.get_param('GooglePoIMapLastClass');
      document.getElementById('GooglePoIPointDescription').innerHTML = '';
      this.update_pointImg(s, 'main');
    }
    
    /* select new point */
    if (document.getElementById('GooglePoIMapItem'+point)) {
      this.set_param('selectedPoint', point);
      this.set_param('GooglePoIMapLastClass', pointObject.className);
      if ( this.get_param('GooglePoIMapClass') !== false )
      pointObject.className = this.get_param('GooglePoIMapClass');
      
      /* add loading image */
      b = html_getDivElement();
      b.style.width = '32px';
      b.style.margin = '64px auto';
      img = html_getImgElement();
      img.setAttribute('src', this.params['loadingImageURL']);
      img.setAttribute('border', 0);
      img.setAttribute('alt', '');
      b.appendChild(img);
      document.getElementById('GooglePoIPointDescription').appendChild(b);
      
      /* center point in map */
      if ( from != 'map' || this.map.getZoom() < 8) {
				this.map.setCenter(this.mapPoints[point].marker.getLatLng(), Math.max(8, this.map.getZoom()));
      }
      
      /* update icon */
      this.update_selectedPointIcon();
      
      /* check mobile */
      if ( this.get_param('hasTabs') == 1 ) {
      	if (from == 'map')
      		this.select_descTab();
      	else
      		this.select_mapTab();
      }
      
      /* load point data */
      this.loader._execute(this.get_param('ajaxBaseURL')+'&action=loadpoint&point='+point);
    }
  };
  
  /*
   * update point on rollover
   * @param integer point
   * @return void
   * @access private
   */
  this.rollover_point = function(point) {
      this.update_pointImg(point, 'roll');
  };
  
  /*
   * update point on rollout
   * @param integer point
   * @return void
   * @access private
   */
  this.rollout_point = function(point) {
    if ( this.get_param('selectedPoint')==point)
      this.update_pointImg(point, 'slct');
    else
      this.update_pointImg(point, 'main');
  };
  
  /*
   * update selected point icon
   * @return void
   * @access private
   */
  this.update_selectedPointIcon = function() {
    point = this.get_param('selectedPoint');
    if (point < 1 || point === false)
      return;
    this.update_pointImg(point, 'slct');
  };
  
  /*
   * ajax loader callback
   * @param xml result
   * @return void
   * @access private
   */
  this._receiveResult = function(result) {
    result = xml_serializeObject(result);
    if ( result != null && result['status']=='success' ) {
     switch(result['action']) {
      case 'updateSelectedPoint':
        this._update_selectedPoint(result);
     }
    } else if (result == null)  {
      //alert('no result received');
    } else {
      //alert('result failed : '+result['error']);
    }
  };
  
  /*
   * ajax loader error callback
   * @return void
   * @access private
   */
  this._receiveError = function() {
    /* error : to do */
    //alert('reception error');
  };
  
  /*
   * update selected point display from given point data
   * @param array pointData
   * @return void
   * @access private
   */
  this._update_selectedPoint = function(pointData) {
  
    sd = document.getElementById('GooglePoIPointDescription');
    sd.innerHTML = '';
    
    /* add body */
    d = html_getDivElement();
    d.className = 'body';
    sd.appendChild(d);

    b = html_getDivElement();
    b.className = this.get_param('GooglePoIMapDescTitleClass');
    b.innerHTML = pointData['title'];
    d.appendChild(b);
    
    /* add desc */
    if ( pointData['desc'] != '') {
      b = html_getDivElement();
      b.innerHTML = pointData['desc'];
      d.appendChild(b);
    }
    
    /* check for next point to load */
    if ( this.params['nextPoint'] > 0 ) {
      a = this.params['nextPoint'];
      this.params['nextPoint'] = 0;
      this.select_point(a, 'queue');
    }
  };
  
  /*
   * add given point to map
   * @param integer id
   * @param GlatLng pos
   * @return void
   * @access private
   */
  this.add_point2Map = function(id, pos) {
    pos = pos || new GLatLng(this.mapPoints[id].lat, this.mapPoints[id].lng);
    
    if (this.mapPoints[id].icon == 0)
      this.mapPoints[id].marker = new GMarker(pos, {title:this.mapPoints[id].title});
    else
      this.mapPoints[id].marker = new GMarker(pos, {title:this.mapPoints[id].title, icon:new GIcon(this.mapIcons[this.mapPoints[id].icon]['GIcon'])});
    
    if ( this.params['useManager'] == 1)
      this.markerManager.addMarker(this.mapPoints[id].marker, 0);
    else
      this.map.addOverlay(this.mapPoints[id].marker);
      
    /* add events */
    GEvent.addListener(this.mapPoints[id].marker, "click", function(){pmv.select_point(id, 'map');});
    GEvent.addListener(this.mapPoints[id].marker, "mouseover", function(){pmv.rollover_point(id);});
    GEvent.addListener(this.mapPoints[id].marker, "mouseout", function(){pmv.rollout_point(id);});
  };

  /* 
   * update given point main img
   * @param integer point
   * @param string img
   * @return void
   * @access private
   */
  this.update_pointImg = function(point, img) {
    /* check point value */
    if (!this.mapPoints[point] || this.mapPoints[point].icon == 0)
      return;
    
    /* check img value */
    if (img != 'main' && img != 'roll' && img != 'slct')
      return;
    /* update point img */
    img = this.mapIcons[this.mapPoints[point].icon][img+'Img'];
    if ( img == '')
      img = this.mapIcons[this.mapPoints[point].icon]['mainImg']
    this.mapPoints[point].marker.setImage(img);
  }

  /*
   * reload page with selected category
   * @param Select select
   * @return void
   * @access private
   */
  this.update_category = function(select) {
    v = select.options[select.options.selectedIndex].value;
    if ( v == 0 )
      document.location.href = this.get_param('updateCategoryURL').replace('-category-_c_', '');
    else
      document.location.href = this.get_param('updateCategoryURL').replace(/_c_/, v);
  }

  /*
   * reload page with selected country
   * @param Select select
   * @return void
   * @access private
   */
  this.update_country = function(select) {
    v = select.options[select.options.selectedIndex].value;
    if ( v == '')
      document.location.href = this.get_param('updateCountryURL').replace('-country-_c_', '');
    else
      document.location.href = this.get_param('updateCountryURL').replace(/_c_/, v);
  }
  
  /*
   * select map tab
   * @return void
   * @access private
   */
  this.select_mapTab = function() {
  	if (this.get_param('hasTabs') == 0)
  		return;
  	if (document.getElementById('GooglePoIPointList'))
  		document.getElementById('GooglePoIPointList').style.display = 'none';
  	if (document.getElementById('GooglePoIListTab'))
  		document.getElementById('GooglePoIListTab').className = this.get_param("GooglePoITabClass");
  	if (document.getElementById('GooglePoIPointDescription'))
  		document.getElementById('GooglePoIPointDescription').style.display = 'none';
  	if (document.getElementById('GooglePoIMapTab'))
  		document.getElementById('GooglePoIMapTab').className = this.get_param("GooglePoITabSelClass");
  	if (document.getElementById('GooglePoIMap'))
  		document.getElementById('GooglePoIMap').style.display = 'block';
  }
  
  /*
   * select point tab
   * @return void
   * @access private
   */
  this.select_listTab = function() {
  	if (this.get_param('hasTabs') == 0)
  		return;
  	if (document.getElementById('GooglePoIMap'))
  		document.getElementById('GooglePoIMap').style.display = 'none';
  	if (document.getElementById('GooglePoIMapTab'))
  		document.getElementById('GooglePoIMapTab').className = this.get_param("GooglePoITabClass");
  	if (document.getElementById('GooglePoIPointDescription'))
  		document.getElementById('GooglePoIPointDescription').style.display = 'none';
  	if (document.getElementById('GooglePoIPointList'))
  		document.getElementById('GooglePoIPointList').style.display = 'block';
  	if (document.getElementById('GooglePoIListTab'))
  		document.getElementById('GooglePoIListTab').className = this.get_param("GooglePoITabSelClass");
  }
  
  /*
   * select desc tab
   * @return void
   * @access private
   */
  this.select_descTab = function() {
  	if (this.get_param('hasTabs') == 0)
  		return;
  	if (document.getElementById('GooglePoIPointList'))	
  		document.getElementById('GooglePoIPointList').style.display = 'none';
  	if (document.getElementById('GooglePoIListTab'))
  		document.getElementById('GooglePoIListTab').className = this.get_param("GooglePoITabClass");
  	if (document.getElementById('GooglePoIMap'))	
  		document.getElementById('GooglePoIMap').style.display = 'none';
  	if (document.getElementById('GooglePoIPointDescription'))	
  		document.getElementById('GooglePoIPointDescription').style.display = 'block';
  	if (document.getElementById('GooglePoIMapTab'))
  		document.getElementById('GooglePoIMapTab').className = this.get_param("GooglePoITabSelClass");
  }
  
  /*
   * update map with user location
   * @return void
   * @access private
   */
  this.load_userLocation = function() {
  	if ( this.get_param('GooglePoIMapGeoStatus') == 0)
  		return;
  		
  	/* get user location */
    navigator.geolocation.watchPosition(get_userLocation);
  }
  
  /*
   * add user position to map
   * @param Position position
   * @return void
   * @access private
   */
  this.add_userLocation2Map = function(position) {
  	pos = new GLatLng(position.coords.latitude, position.coords.longitude);

		if ( this.get_param('GooglePoIMapGeoMarker') == '' ) {
			/* add point */
    	if (this.get_param('GooglePoIMapGeoIcon') == 0 || !this.mapIcons[this.get_param('GooglePoIMapGeoIcon')] )
      	this.set_param('GooglePoIMapGeoMarker', new GMarker(pos, {title:this.get_locale('yourlocation')}));
    	else
      	this.set_param('GooglePoIMapGeoMarker', new GMarker(pos, {title:this.get_locale('yourlocation'), icon:new GIcon(this.mapIcons[this.get_param('GooglePoIMapGeoIcon')]['GIcon'])}));
    
    	if ( this.params['useManager'] == 1)
      	this.markerManager.addMarker(this.get_param('GooglePoIMapGeoMarker'), 0);
    	else
      	this.map.addOverlay(this.get_param('GooglePoIMapGeoMarker'));
    
    	/* center and zoom on user location */
    	this.map.setCenter(pos , this.get_param('GooglePoIMapGeoZoom'));
    	this.select_mapTab();
    } else {
    	/* update point location */
    	this.get_param('GooglePoIMapGeoMarker').setPoint(pos);
    	this.map.setCenter(pos);
    }
    
    /* add events 
    GEvent.addListener(this.mapPoints[id].marker, "click", function(){pmv.select_point(id, 'map');});
    GEvent.addListener(this.mapPoints[id].marker, "mouseover", function(){pmv.rollover_point(id);});
    GEvent.addListener(this.mapPoints[id].marker, "mouseout", function(){pmv.rollout_point(id);});
		*/
  }
}

/* tool methods */
function get_userLocation(position) {
	pmv.add_userLocation2Map(position);
}
