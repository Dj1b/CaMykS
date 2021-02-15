/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	        : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Create Date	    : Mar 2010
 * Last Modif Date  : Mar 2010
 *
 * Admin_GooglePoIMapManager point editor scripts
 */

function PointEditor(name) {
  this.name = name;
  this.loaded = false;
  this.params = {};
  this.locales = {};

  /* map variables */
  this.map = null;
  this.geocoder = null;

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
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function(form) {
    /* initialise google map */
    this.formName = form;
    this.form = document.getElementById(form);

    /* initialise map icon *
    icon = new GIcon();
    icon.iconSize = new GSize (18, 32);
    icon.shadowSize = new GSize(32, 32);
    icon.iconAnchor = new GPoint(3, 32);
    icon.image = this.params['GMapIcon'];
    icon.shadow = this.params['GMapIconShadow'];
    this.params['GMapIconObject'] = icon;
    */

    this.map = new GMap2(document.getElementById("GoogleMapBox"));
    this.map.setUIToDefault();

    /* initialise google map point */
    if (this.params['Point'].lat )
      this.add_point2Map();
    else {
      this.map.setCenter(new GLatLng(0,0), 0);
    }
  };

  /*
   * add given point to map
   * @return void
   * @access private
   */
  this.add_point2Map = function() {
    pos = new GLatLng(this.params['Point'].lat, this.params['Point'].lng);

    if( !this.params['SiteMarker'] )
      this.params['SiteMarker'] = new GMarker(pos, {title:this.params['Point'].title, draggable: true});
    else
      this.params['SiteMarker'].setPoint(pos);
    this.map.setCenter(this.params['SiteMarker'].getLatLng(), this.params['GMapDefZoom']);
    this.map.addOverlay(this.params['SiteMarker']);
    this.map.panTo(this.params['SiteMarker'].getLatLng());

    GEvent.addListener(this.params['SiteMarker'], "drag", function(){
	a = pe.params['SiteMarker'].getPoint();
	pe.form.latitude.value=a.lat();
	pe.form.longitude.value=a.lng();
      });

    this.loaded = true;
  };

  /*
   * init point position loading from its address
   * @param integer id
   * @return void
   * @access private
   */
  this.get_pointPositionFromAddress = function() {
    this.geocoder = new GClientGeocoder();
    a = this.form.address1.value + ' ' + this.form.address2.value + ' ' + this.form.address3.value;
    a += ' '+this.form.country.options[this.form.country.options.selectedIndex].text;
    this.geocoder.getLatLng(a, _receive_pointPositionFromAddress);
  };

  /*
   * receive point position from its address
   * @param GLngLat pos
   * @return void
   * @access private
   */
  this.receive_pointPositionFromAddress = function(pos) {
    if (pos == undefined) {
      alert(this.get_locale('address_undefined'));
      return;
    }
    this.params['Point'].lat = pos.lat();
    this.params['Point'].lng = pos.lng();
    this.form.latitude.value = pos.lat();
    this.form.longitude.value = pos.lng();
    this.add_point2Map();
  };

  this._receiveUpdateResult = function(result) {
    return;
  };

  /* devel methods */

  this.get_position = function() {
    alert('zoom : ' + this.map.getZoom());
    c = this.map.getCenter();
    alert('x : ' + c.x + ' - y : ' + c.y);
  };
}

function _receive_pointPositionFromAddress(pos) {
  pe.receive_pointPositionFromAddress(pos);
}
