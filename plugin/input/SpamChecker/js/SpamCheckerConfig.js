/**
 * @brief SpamChecker Input configuration scripts
 * @details Plugin / Input Javascripts
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
var SpamCheckerConfig = {
    params: {},

    /**
     * add parameter
     * @param string name
     * @param mixed value
     * @return void
     */
    set_param: function(param, value, subvalue) {
        if ( subvalue != undefined && this.params[param] )
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
        this.set_param('form', document.getElementById(this.get_param('form')));

        /* Check linear rules ae enabled */
        this.check_linearRuleIsEnabled('SimilarNames');
        this.check_linearRuleIsEnabled('HTML');
        this.check_linearRuleIsEnabled('Javascript');
        this.check_blockRuleIsEnabled('Email');
        this.check_blockRuleIsEnabled('Company');
        this.check_blockRuleIsEnabled('Link');
        this.check_blockRuleIsEnabled('LanguageScript');
        this.check_blockRuleIsEnabled('Word');
        this.check_blockRuleIsEnabled('Country');
        this.check_blockRuleIsEnabled('Hostname');
    },

    /**
     * Check linear rule is enabled.
     * @param string rule
     * @return void
     */
    check_linearRuleIsEnabled: function(rule) {
        if (this.get_param('form')['check'+rule+'Enabled'].checked)
            this.get_param('form')['check'+rule+'Score'].removeAttribute('disabled');
        else
            this.get_param('form')['check'+rule+'Score'].setAttribute('disabled', 'disabled');
    },

    /**
     * Check block rule is enabled.
     * @param string rule
     * @return void
     */
    check_blockRuleIsEnabled: function(rule) {
        console.log(rule);

        if (this.get_param('form')['check'+rule+'Enabled'].checked)
            document.getElementById('check'+rule+'RuleList').style.display = 'block';
        else
            document.getElementById('check'+rule+'RuleList').style.display = 'none';
    },

    /**
     * Check block rule insertion.
     * @param string rule
     * @param Object input
     * @return void
     */
    check_blockRuleInsert: function(rule, input) {
        block = document.getElementById('check'+rule+'RuleList');
        line = input.parentNode.parentNode;

        /* Check line is the last one */
        if (line.isSameNode(block.children[block.children.length-1])) {
            /* Add a new duplicated line */
            newLine = line.cloneNode(true);
            inputs = newLine.getElementsByTagName('input');
            inputs[0].value = '';
            inputs[1].value = 0;
            block.appendChild(newLine);
        }
    },

    /**
     * Check block rule removal.
     * @param string rule
     * @param Object input
     * @return void
     */
    check_blockRuleRemove: function(rule, input) {
        block = document.getElementById('check'+rule+'RuleList');

        /* Check rule is empty */
        if (input.value !== '')
            return;

        /* Check line is not the latest one remaining */
        if (block.children.length > 1) {
            /* Remove line */
            line = input.parentNode.parentNode;
            block.removeChild(line);
        }
    },

    /**
     * Check block rule change on a select.
     * @param string rule
     * @param Object input
     * @return void
     */
    check_blockRuleSelectChange: function(rule, input) {
        block = document.getElementById('check'+rule+'RuleList');
        line = input.parentNode.parentNode;
        value = input.options[input.options.selectedIndex].value;

        if (value === '') {
            /* Check line is not the latest one remaining */
            if (block.children.length > 1) {
                /* Remove line */
                block.removeChild(line);
            }
        } else {
            /* Check line is the last one */
            if (line.isSameNode(block.children[block.children.length-1])) {
                /* Add a new duplicated line */
                newLine = line.cloneNode(true);
                selects = newLine.getElementsByTagName('select');
                inputs = newLine.getElementsByTagName('input');
                selects[0].options.selectedIndex = 0;
                inputs[0].value = 0;
                block.appendChild(newLine);
            }
        }
    },
}
