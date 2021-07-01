/**
 * @brief GenericCaptcha Input scripts
 * @details Plugin / Input Javascripts
 * @author CaMykS Team
 * @version 1.0.0.1
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
var GenericCaptcha = {
    name: 'GenericCaptcha',
    params: {},

    /**
     * add parameter
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
     * Return param value from name
     * @param mixed param
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
     * Initialise object
     * @return void
     */
    initialise: function() {
        /* Load form as object */
        this.set_param('form', document.getElementById(this.get_param('form')));

        /* Add hidden input in form */
        controlInput = document.createElement('input');
        controlInput.setAttribute('type', 'hidden');
        controlInput.setAttribute('name', this.get_param('controlInput'));
        controlInput.setAttribute('value', 0);
        this.get_param('form').appendChild(controlInput);

        /* Add oninput event on each textarea in the form */
        textareas = this.get_param('form').getElementsByTagName('textarea');
        for (i in textareas) {
            if (textareas[i].nodeName == 'TEXTAREA')
                textareas[i].setAttribute('oninput', this.name+'.update_actionCount();'+ (textareas[i].getAttribute('oninput') !== null ? textareas[i].getAttribute('oninput') : ''));
        }

        /* Add oninput event on each input in the form */
        inputs = this.get_param('form').getElementsByTagName('input');
        for (i in inputs)
            if (inputs[i].type == 'text')
                inputs[i].setAttribute('oninput', this.name + '.update_actionCount();'+ (inputs[i].getAttribute('oninput') !== null ? inputs[i].getAttribute('oninput') : ''));
    },

    /**
     * Updates action count.
     * @return void
     */
    update_actionCount: function() {
        if (this.get_param('form')[this.get_param('controlInput')])
            this.get_param('form')[this.get_param('controlInput')].value ++;
    },
}
