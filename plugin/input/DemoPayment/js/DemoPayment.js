/**
 * @brief DemoPayment input, client side scripts.
 * @details Plugin / Module Javascripts
 * @author CaMykS Team
 * @version 1.0.0
 * @date Creation: Mar 2024
 * @date Modification: Mar 2024
 * @copyright 2024 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
var DemoPayment = {
    name: 'DemoPayment',
    params: {},
    locales: {},
    loaded: false,

    /**
     * Set parameter.
     * @param string name
     * @param mixed value
     * @return void
     */
    set_param: function(param, value, subvalue) {
        if (subvalue != undefined && this.params[param])
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    },

    /**
     * Return param value from name.
     * @param mixed param
     * @return mixed
     */
    get_param: function(param, value) {
        if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
                return this.params[param][value];
        if (this.params[param] || this.params[param] === 0)
            return this.params[param]
        return false;
    },

    /**
     * Set locale value.
     * @param string name
     * @param string value
     * @return void
     */
    set_locale: function(name, value) {
        this.locales[name.toLowerCase()] = value;
    },

    /**
     * Return locale value.
     * @param string name
     * @return string
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
        this.set_param('step', 0);
        this.engine = setInterval(this.name+'.runEngine();', 150);
    },

    /* Mark: Action methods */

    /**
     * Run object engine
     * @return void
     */
    runEngine: function() {
        switch(this.get_param('step')) {
            case 0: case 2: case 5: case 7:
            case 10: case 12: case 15: case 17:
                document.getElementById('CreditCard').innerHTML += '4';
                break;
            case 1: case 3: case 6: case 8:
            case 11: case 13: case 16: case 18:
                document.getElementById('CreditCard').innerHTML += '2';
                break;
            case 4: case 9: case 14:
                document.getElementById('CreditCard').innerHTML += '&nbsp;';
                break;
            case 19:
                document.getElementById('DateMonth').innerHTML += '1';
                break;
            case 20:
                document.getElementById('DateMonth').innerHTML += '2';
                break;
            case 21: case 22:
                 document.getElementById('DateYear').innerHTML += '2';
                break;
            case 23:
                clearInterval(this.engine);
                break;
        }
        this.set_param('step', this.get_param('step')+1);
    },
}
