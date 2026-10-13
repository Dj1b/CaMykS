/**
 * @brief AdvancedSMTPSettings input, configuration editor scripts.
 * @details Plugin / Module Javascript
 * @author CaMykS Team
 * @version 1.0.0
 * @date Creation: Jan 2026
 * @date Modification: Jan 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
var AdvancedSMTPSettingsConfigurationEditor = {
    name: 'AdvancedSMTPSettingsConfigurationEditor',
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
        if (!document.getElementById(this.get_param('form')))
            return;
        this.set_param('form', document.getElementById(this.get_param('form')));
        this.loaded = true;
        this.check_SMTPAuthValue();
    },

    /* Mark: Action methods */

    /**
     * Check SMTP Auth Value.
     * @return void
     */
    check_SMTPAuthValue: function() {
        if (!this.loaded)
            return;
        v = this.get_param('form')['SMTP_Auth'].value;
        if (v == 'Basic') {
            document.getElementById('AuthBasic').style.display = 'block';
            document.getElementById('AuthXOAUTH2').style.display = 'none';

        } else if (v == 'XOAUTH2') {
            document.getElementById('AuthBasic').style.display = 'none';
            document.getElementById('AuthXOAUTH2').style.display = 'block';

        } else {
            document.getElementById('AuthBasic').style.display = 'none';
            document.getElementById('AuthXOAUTH2').style.display = 'none';
        }
    },
}
