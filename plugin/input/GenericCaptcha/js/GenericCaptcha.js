/**
 * @brief GenericCaptcha Input scripts
 * @details Plugin / Input Javascripts
 * @author CaMykS Team
 * @version 1.0.1
 * @date Creation: Jun 2021
 * @date Modification: Jul 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
var GenericCaptcha = {
    name: 'GenericCaptcha',
    params: {
        'controlInput':{},
    },

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
     * @param string form
     * @param string controlInputName
     * @return void
     */
    initialise: function(form, controlInputName) {
        /* Check form exists */
        if (!document.getElementById(form))
            return;

        /* Load form as object */
        form = document.getElementById(form);

        /* Add hidden input in form */
        controlInput = document.createElement('input');
        controlInput.setAttribute('type', 'hidden');
        controlInput.setAttribute('name', controlInputName);
        controlInput.setAttribute('value', 0);
        form.appendChild(controlInput);

        /* Save controlInput for form */
        this.set_param('controlInput', form.name, controlInputName);

        /* Add oninput event on each textarea in the form */
        textareas = form.getElementsByTagName('textarea');
        for (i in textareas) {
            if (textareas[i].nodeName == 'TEXTAREA')
                textareas[i].setAttribute('oninput', this.name+'.update_actionCount(this);'+ (textareas[i].getAttribute('oninput') !== null ? textareas[i].getAttribute('oninput') : ''));
        }

        /* Add oninput event on each input in the form */
        inputs = form.getElementsByTagName('input');
        for (i in inputs)
            if (inputs[i].type == 'text')
                inputs[i].setAttribute('oninput', this.name + '.update_actionCount(this);'+ (inputs[i].getAttribute('oninput') !== null ? inputs[i].getAttribute('oninput') : ''));
    },

    /**
     * Updates action count.
     * @param Object input
     * @return void
     */
    update_actionCount: function(input) {
        input.form[this.get_param('controlInput', input.form.name)].value ++;
    },
}
