/**
 * @brief PerpetualCalendar Input scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/PerpetualCalendar/js/PerpetualCalendar.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Apr 2010
 * @date Modification: Jul 2018
 * @copyright 2010 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* main object */
function PerpetualCalendar(name) {
  this.name = name;
  this.loaded = false;
  this.params = {};
  this.locales = {};
  this.items = {};

  /*
   * set parameter value
   * @param string name
   * @param mixed value
   * @param mixed subvalue
   * @return void
   * @access public
   */
  this.set_param = function(name, value, subvalue) {
    if (subvalue != undefined)
      this.params[name][value] = subvalue;
    else
      this.params[name] = value;
  };

  /*
   * get parameter value
   * @param string name
   * @param string subname
   * @return mixed
   * @access public
   */
  this.get_param = function(name, subname) {
    if (subname == undefined && this.params[name])
      return this.params[name];
    else if (this.params[name] && this.params[name][subname])
      return this.params[name][subname];
    return false;
  };

  /*
   * set locale value
   * @param string name
   * @param string value
   * @return void
   * @access public
   */
  this.set_locale = function(name, value) {
    this.locales[name] = value;
  };

  /*
   * get locale value
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
   * set item value
   * @param array params
   * @return void
   * @access public
   */
  this.set_item = function(item) {
    if (item['date']) {
      date = new Date(parseInt(item['date']));
      my = date.getFullYear()+'-'+date.getMonth();
      day = date.getDate();
    } else {/*
      my = params['year']+'-'+params['month'];
      day = parseInt(params['day']);*/
      return;
    }

    /* add item to item list */
    if (!this.items[my])
        this.items[my] = new Array();

    if (!this.items[my][day])
        this.items[my][day] = new Array();

    this.items[my][day][this.items[my][day].length] = item;

    /* check if master object is loaded */
    if (this.loaded == false)
      return;

    /* check if day is in displayed month */
    if (date.getMonth() != this.get_param('date').getMonth() || date.getFullYear() != this.get_param('date').getFullYear())
      return;

    /* update cell */
    cell = document.getElementById(this.name + 'Cell' + day);
    if (this.items[my][day].length > 1 && this.get_param('multiItem')['enabled'] == 1)
        this._set_cellProperties(cell, this.get_param('multiItem'), day);
    else
        this._set_cellProperties(cell, item, day);
  };

  /*
   * remove items from params
   * @param Date date
   * @param Integer day
   * @return boolean success
   * @access public
   */
  this.remove_items = function(date, day) {
      my = date.getFullYear()+'-'+date.getMonth();

      if (day == undefined)
          this.items[my] = new Array();
      else
          this.items[my][day] = new Array();
  }

  /*
   * get item value
   * @param Date date
   * @param Integer day
   * @return mixed
   * @access public
   */
  this.get_item = function(date, day) {
    my = date.getFullYear()+'-'+date.getMonth();
    if (day == undefined)
      day = date.getDate();

    if (this.items[my] && this.items[my][day])
      return this.items[my][day][0];
    return false;
  };

  /*
   * get items value
   * @param Date date
   * @param Integer day
   * @return mixed
   * @access public
   */
  this.get_items = function(date, day) {
    my = date.getFullYear()+'-'+date.getMonth();
    if (day == undefined)
      day = date.getDate();

    if (this.items[my] && this.items[my][day])
      return this.items[my][day];
    return false;
  };

  /*
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {

    /* check calendar DOM element */
    if (document.getElementById(this.name+'Object')) {
      this.set_param('calendarObject', document.getElementById(this.name+'Object'));
      this.set_param('calendarDate', document.getElementById(this.name+'Date'));
    } else
      return;

    /* save plateform */
    this.set_param('plateform', navigator.userAgent.toLowerCase().indexOf('msie')==-1 ? 'other':'ie');

    /* build month list */
    this.set_param('monthes', new Array('january', 'february', 'march', 'april', 'may', 'june', 'july', 'august', 'september', 'october', 'november', 'december'));

    /* build day list */
    this.set_param('days', new Array('monday', 'tuesday', 'wednesday', 'thurday', 'friday', 'saturday', 'sunday'));

    /* define default date */
    d = new Date();
    d.setDate(1);
    if (this.get_param('dateMonth') !== false)
      d.setMonth(this.get_param('dateMonth'));
    if (this.get_param('dateYear') !== false)
      d.setYear(this.get_param('dateYear'));
    this.set_param('date', d);

    /* set calendar as loaded */
    this.loaded = true;
  };

  /*
   * display next month
   * @return void
   * @access public
   */
  this.display_nextMonth = function() {
    /* update date */
    d = this.get_param('date');
    d.setMonth(d.getMonth()+1);
    this.set_param('date', d);

    /* update calendar display */
    this._update_calendarBody();
  };

  /*
   * display previous month
   * @return void
   * @access public
   */
  this.display_prevMonth = function() {
    /* update date */
    d = this.get_param('date');
    d.setMonth(d.getMonth()-1);
    this.set_param('date', d);

    /* update calendar display */
    this._update_calendarBody();
  };

  /*
   * display given month
   * @param int month
   * @param int year
   * @return void
   * @access public
   */
  this.display_month = function(month, year) {
    /* update date */
    d = this.get_param('date');
    if (month>=0) d.setMonth(month);
    if (year) d.setYear(year);
    this.set_param('date', d);

    /* update calendar display */
    this._update_calendarBody();
  };

  /*
   * return current display date
   * @return date
   * @access public
   */
  this.get_displayedDate = function() {
    return this.get_param('date');
  };

  /*
   * get item from day
   * @param integer day
   * @return item
   * @access private
   */
  this.get_itemFromDay = function(day) {
    date = this.get_param('date');
    return this.get_item(date, day);
  };

  /*
   * get item from day
   * @param integer day
   * @return item
   * @access private
   */
  this.get_itemsFromDay = function(day) {
    date = this.get_param('date');
    return this.get_items(date, day);
  };

  /*
   * update calendar body
   * @return void
   * @access private
   */
  this._update_calendarBody = function() {
    /* clear body */
    i=0;
    while (document.getElementById(this.name+'Line'+i)) {
      this.get_param('calendarObject').removeChild(document.getElementById(this.name+'Line'+(i++)));
    }

    /* get date to display */
    date = this.get_param('date');

    /* update month & year display */
    this.get_param('calendarDate').innerHTML = this.get_locale(this.get_param('monthes', date.getMonth()));
    this.get_param('calendarDate').innerHTML += ' '+date.getFullYear();

    /* build first line */
    line = 0;

    if ( date.getDay() > 0 ) {
      l = document.createElement('tr').cloneNode(true);
      l.id = this.name + 'Line' + (line++);
      this.get_param('calendarObject').appendChild(l);

      /* add empty days ending last month */
      for(var i=0; i< date.getDay(); i++) {
        c = document.createElement('td').cloneNode(true);
        c.className = 'cellOut';
        l.appendChild(c);
      }
    }

    /* add month days */
    while(date.getMonth() == this.get_param('date').getMonth()) {
      /* check for a new line */
      if (date.getDay() == 0) {
        l = document.createElement('tr').cloneNode(true);
        l.id = this.name + 'Line' + (line++);
        this.get_param('calendarObject').appendChild(l);
      }

      /* get day */
      day = date.getDate()

      /* build cell */
      c = document.createElement('td').cloneNode(true);
      c.id = this.name + 'Cell' + day;

      /* get day items */
      items = this.get_items(date);

      /* check item list */
      if (items != false ) {
          if (items.length > 1 && this.get_param('multiItem')['enabled'] == 1)
              this._set_cellProperties(c, this.get_param('multiItem'), day);
          else
            this._set_cellProperties(c, items[0], day);
      } else {
        this._set_cellProperties(c, this.get_param('defaultItem'), day);
      }
      c.innerHTML = day;
      l.appendChild(c);

      /* update date value */
      date = new Date(date.getFullYear(), date.getMonth(), day+1, 1, 0, 0);
    }

    /* add empty days start next month */
    if ( date.getDay() > 0 ) {
      for(var i=date.getDay(); i < 7; i++) {
        c = document.createElement('td').cloneNode(true);
        c.className = 'cellOut';
        l.appendChild(c);
      }
    }
  };

  /*
   * set cell properties
   * @param DOMElement cell
   * @param array item
   * @param integer day
   * @return void
   * @access private
   */
  this._set_cellProperties = function( cell, item, day ) {
    if (item['class'])
      cell.className = 'cell'+item['class'];
    else
      cell.className = 'cell0';

    if (item['hadEvents'] == 0)
      return;

    /* check mouse click event */
    if ( item['clickEvent'] && item['clickEvent'] != '')
      click = item['clickEvent']+'('+day+');';
    else if ( this.get_param('defaultEvents', 'clickEvent') != '' )
      click = this.get_param('defaultEvents', 'clickEvent')+'('+day+');';
    else if ( this.get_param('selectionCallBack') != '')
      click = this.get_param('selectionCallBack') + '('+this.get_param('date').getFullYear()+','+(this.get_param('date').getMonth()+1)+','+day+');';
    else
      click = '';

    /* check mouse over event */
    if ( item['overEvent'] && item['overEvent'] != '')
      over = item['overEvent']+'('+day+');';
    else if (this.get_param('defaultEvents', 'overEvent') != '' )
      over = this.get_param('defaultEvents', 'overEvent')+'('+day+');';
    else
      over = '';
    if ( this.get_param('enableHighlight') == 1 && over != '')
      over += 'this.className=\'cell'+item['class']+'Over\';';

    /* check mouse out event */
    if ( item['outEvent'] && item['outEvent'] != '')
      out = item['outEvent']+'('+day+');';
    else if (this.get_param('defaultEvents', 'outEvent') != '' )
      out = this.get_param('defaultEvents', 'outEvent')+'('+day+');';
    else
      out = '';
    if ( this.get_param('enableHighlight') == 1 && out != '')
      out += 'this.className=\'cell'+item['class']+'\';';

    if ( this.get_param('plateform') == 'ie' ) {
      /* add internet explorer events */
      if ( click != '')
        cell.onclick = new Function(click);
      if ( over != '')
        cell.onmouseover = new Function(over);
      if ( out != '')
        cell.onmouseout = new Function(out);

    } else {
      /* add real navigator events */
      if ( click != '' )
        cell.setAttribute('onclick', click);
      if ( over != '' )
        cell.setAttribute('onmouseover', over);
      if ( out != '')
        cell.setAttribute('onmouseout', out);
    }
  };
}
