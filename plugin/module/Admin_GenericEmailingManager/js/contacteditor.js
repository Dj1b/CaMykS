/**
 * @brief Admin_GenericEmailingManager Module client side script to edit contact
 * @details Plugin, Module Javascripts
 * @file plugin/module/Admin_GenericEmailingManager/js/contacteditor.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2013
 * @date Modification: Dec 2018
 * @copyright 2013 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
function ContactEditor(name) {
    this.name = name;
    this.params = {};
    this.locales = {};
    this.loaded = false;

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

    if (this.params[param] != undefined)
      return this.params[param];
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
    this.locales[name.toLowerCase()] = value;
  };

  /*
   * get locale value
   * @param string name
   * @param option args
   * @return void
   * @access public
   */
  this.get_locale = function(name) {
      name = name.toLowerCase();
    if (!this.locales[name])
        return name;

    locale = this.locales[name];
    for(i=1; i<arguments.length; i++)
        locale = locale.replace('__$'+i+'__', arguments[i]);

        return locale;
  };

  /*
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {

  };

  /*
   * check group value
   * @param Input s
   * @return void
   * @access public
   */
  this.check_groupValue = function(s) {
    if (s.options[s.options.selectedIndex].value == '_other_')
      this.display_groupAsText();
  };

  /*
   * display group as list
   * @return void
   * @access public
   */
  this.display_groupAsList = function() {
    /* hide text input */
    document.getElementById('groupTextBox').style.display = 'none';
    document.getElementById('groupText').disabled = 'disabled';
    /* show select input */
    document.getElementById('groupList').style.display = 'block';
    document.getElementById('groupList').disabled = '';
    document.getElementById('groupList').options.selectedIndex = 0;
  };

  /*
   * display group as text
   * @return void
   * @access public
   */
  this.display_groupAsText = function() {
    /* hide select input */
    document.getElementById('groupList').style.display = 'none';
    document.getElementById('groupList').disabled = 'disabled';
    /* show text input */
    document.getElementById('groupTextBox').style.display = 'block';
    document.getElementById('groupText').disabled = '';

  };
}
