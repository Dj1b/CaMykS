/**
 * @brief Client side library to be extended on object libraries.
 * @details Engine / Javascript object library
 * @file engine/data/js/object/clibrary.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2011
 * @date Modification: Apr 2018
 * @copyright 2011 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Class constructor.
 * @param string name
 */
var CLibrary = Class.create({
    /**
     * @var string name
     * @brief The object occurence name.
     */
    name: arguments[0],
    
    /**
     * @var array params
     * @brief The object occurence parameters.
     */
    params: {},
    
    /**
     * @var array locales
     * @brief The object occurence locales.
     */
    locales: {},
    
    /**
     * @var boolean loaded
     * @brief Is the object loaded.
     */
    loaded: false,

    /**
     * Set parameter value.
     * @param string name
     * @param mixed value
     * @param mixed subvalue
     * @return void
     */
    set_param: function(param, value, subvalue) {
        if (subvalue != undefined && this.params[param])
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    },

    /**
     * Return parameter value from name.
     * @param mixed param
     * @parma mixed value
     * @return mixed
     */
    get_param: function(param, value) {
        if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
            return this.params[param][value];
        if (value == undefined && this.params[param] || this.params[param] === 0)
            return this.params[param]
        return false;
    },

    /**
     * Define locale value.
     * @param string name
     * @param string value
     * @return void
     */
    set_locale: function(name, value) {
        this.locales[name.toLowerCase()] = value;
    },

    /**
     * get locale value.
     * @param string name
     * @return void
     */
    get_locale: function(name) {
        if (this.locales[name.toLowerCase()])
            return this.locales[name.toLowerCase()];
        return name;
    },

    /**
     * Initialise object.
     * @return void
     */
    initialise: function() {
        this.loaded = true;
    }
});