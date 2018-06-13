/**
 * @brief Admin_SystemLogManager Module client side scripts
 * @details Plugin / Module javascripts
 * @file plugin/module/Admin_SystemLogManager/js/LogViewer.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Jun 2018
 * @date Modification: Jun 2018
 * @copyright 2018 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Class constructor.
 * @param string $name
 */
var LogViewer = {
    name: 'LogViewer',
    params: {},
    locales: {},
    loaded: false,

    /**
     * add parameter
     * @param string name
     * @param mixed value
     * @return void
     * @access public
     */
    set_param: function(param, value, subvalue) {
        if (subvalue != undefined && this.params[param])
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    },
     
    /**
     * return param value from name
     * @param mixed param
     * @return mixed
     * @access public
     */
    get_param: function(param, value) {
        if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
                return this.params[param][value];
        if (this.params[param] || this.params[param] === 0)
            return this.params[param]
        return false;
    },
    
    /**
     * set locale value 
     * @param string name
     * @param string value
     * @return void
     * @access public
     */
    set_locale: function(name, value) {
        this.locales[name.toLowerCase()] = value;
    },
    
    /**
     * get locale value 
     * @param string name
     * @return void
     * @access public
     */
    get_locale: function(name) {
        if (this.locales[name.toLowerCase()])
            return this.locales[name.toLowerCase()];
        return name;
    },
    
    /**
     * initialise object
     * @return void
     * @access public
     */
    initialise: function() {
        this.set_param('form', document.getElementById(this.get_param('form')));
    },
    
    /* action methods */
    
    /**
     * On log change handler.
     * @return void
     * @access public
     */
    onLogChange: function() {
        this.get_param('form').submit();
    },
    
    /**
     * On log file selection handler.
     * @param string $file
     * @return void
     * @access public
     */
    onLogFileSelect: function(file) {
        this.get_param('form')['file'].value = file;
        this.get_param('form').submit();
    },
    
    /**
     * On filter change handler.
     * @return void
     * @access public
     */
    onFilterChange: function() {
        this.get_param('form').submit();
    },
    
    /**
     * Reset filter.
     * @return void
     * @access public
     */
    resetFilter: function() {
        this.get_param('form')['filter'].value = '';
        this.get_param('form').submit();
    },
}