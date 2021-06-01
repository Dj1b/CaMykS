/**
 * @brief Admin_ContentPage module page editor scripts
 * @details Plugin / Module Scripts
 * @file plugin/module/Admin_ContentPage/js/contentpage_editor.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Oct 2009
 * @date Modification: Sep 2018
 * @copyright 2009 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

function AdminContentPageEditor(name) {
    this._name = name;
    this._form = null;
    this._params = [];
    this._locales = [];

    this._isLoaded = false;

    /* pre-initialisation params */

    /*
     * add params
     * @param string name
     * @param string value
     * @return void
     * @access private
     */
    this.add_param = function(name, value) {
        this._params[name] = value;
    }

    /*
     * add array params
     * @param string name
     * @param string key
     * @param mixed value
     * @return void
     * @access private
     */
    this.add_arrayParam = function(name, key, value) {
        this._params[name][key] = value;
    }

    /*
     * add locale
     * @param string name
     * @param string value
     * @return void
     * @access private
     */
    this.add_locale = function(name, value) {
        this._locales[name] = value;
    }

    /* initialisation methods */

    /*
     * initialise module
     * @return void
     * @access private
     */
    this.initialise = function() {
        /* initialise values */
        this._form = eval('document.'+this._params['form']);

        this._isLoaded = true;

        /* execute actions */
        this.update_templatePanel();
        this.update_modulePanels();
        if (this._params['models'].length > 0)
            this.update_pageFromModel();
        else
            this.lock_content();
    }

    /* validation methods */

    /*
     * submit page
     * @return void
     * @access private
     */
    this.valid_page = function (){
        this.unlock_content();
        this._form.submit();
    }

    /* event methods */

    /*
     * template selector onchange event
     * @return void
     * @access public
     */
    this.onTemplateChange = function() {
        this.update_templatePanel();
        this.check_usedModel();
    }

    /*
     * main theme selector onchange event
     * @return void
     * @access public
     */
    this.onThemeChange = function() {
        this.check_usedModel();
    }

    /*
     * page model selector on change event
     * @return void
     * @access public
     */
    this.onModelChange = function() {
        this.update_pageFromModel();
    }


    /*
     * module selector onchange event
     * @param integer block
     * @return void
     * @access public
     */
    this.onBlockModuleChange = function(block) {
        this.update_modulePanel(block);
        this.check_usedModel();
    }

    /*
     * content selector onchange event
     * @param integer block
     * @return void
     * @access public
     */
    this.onBlockContentChange = function(block) {
        this.check_usedModel();
    }

    /*
     * block theme selector onchange event
     * @param integer block
     * @return void
     * @access public
     */
    this.onBlockThemeChange = function(block) {
        this.check_usedModel();
    }

    /* panel updating methods */

    /*
     * update page info from selected model
     * @return void
     * @access private
     */
    this.update_pageFromModel = function() {
        /* get model value */
        model = this._form.model[this._form.model.selectedIndex].value;

        /* check model value */
        if (model > 0    && this._params['models'][model])
            model = this._params['models'][model];
        else
            return this.unlock_content();

        /* select template */
        this.update_selectedValue('template', model["template"]);
        this.update_templatePanel();

        /* select theme */
        this.update_selectedValue('theme', model["theme"]);

        /* select modules */
        for (var i=0; i<this._params['maxModules']; i++) {
            if (model["m"+i+"_name"] != '') {
                this.update_selectedValue('m'+i+'_name', model["m"+i+"_name"]);
                this.update_modulePanel(i);

                if (model["m"+i+"_content"] != ""  && model["m"+i+"_content"] != "0") {
                    this.update_selectedValue('m'+i+'_content', model["m"+i+"_content"]);
                }

                if (this._params['allowThemeChange'])
                    this.update_selectedValue('m'+i+'_theme', model["m"+i+"_theme"]);
            }
        }
        this.lock_content();
    }

    /*
     * update template panel, show active modules
     * @return void
     * @access private
     */
    this.update_templatePanel = function() {
        /* unselect actual template */
        if (i = document.getElementById('template_'+this._params['selectedTemplate']))
            i.style.display='none';

        /* update selected template value */
        this._params['selectedTemplate'] = this._form.template.options[this._form.template.selectedIndex].value;

        if (this._params['selectedTemplate'] == '') {
            this._params['selectedTemplate'] = this._params['defaultTemplate'];
        }

        /* select new template */
        if (i = document.getElementById('template_'+this._params['selectedTemplate']))
            i.style.display='block';

        /* active modules */
        m = this._params['templateBlocks'][this._params['selectedTemplate']];
        for (var i=0; i<m; i++) {
            if (document.getElementById('module'+i))
                document.getElementById('module'+i).style.display = 'block';
        }

        /* unactive useless modules */
        for (var i=m; i<this._params['maxModules']; i++) {
            if (document.getElementById('module'+i))
                document.getElementById('module'+i).style.display = 'none';
        }

        /* safari hack */
        if (navigator.userAgent.toLowerCase().indexOf('applewebkit') != -1   ) {
            window.innerWidth++;
            window.innerWidth--;
        }
    }

    /*
     * update module panel
     * @param integer block
     * @return void
     * @access private
     */
    this.update_modulePanel = function(block) {
        /* get form values */
        myform_name = eval('this._form.m'+block+'_name');
        myform_content = eval('this._form.m'+block+'_content');

        /* get module name value */
        module_name = myform_name.options[myform_name.selectedIndex].value;

        /* update module content select */
        myform_content.options.length = 0;

        if (this._params['moduleContents'][module_name] && this._params['moduleContents'][module_name] != -1) {

            if (this._params['moduleEditable'][module_name] && this._params['moduleEditable'][module_name] == 1) {
                /* add "new content" item */
                myform_content.options[myform_content.options.length] = new Option (this._locales['new_content'], 0);

                /* add separator item */
                sep = new Option ('', '');
                sep.className = 'separator';
                sep.disabled = 'disabled';
                myform_content.options[myform_content.options.length] = sep;

                /* show edit content button */
                document.getElementById('module_editbutton'+block).style.display = 'block';
            } else if (this._params['moduleEditable'][module_name] && this._params['moduleEditable'][module_name] == 2) {
                /* show edit content button */
                document.getElementById('module_editbutton'+block).style.display = 'block';
            } else {
                /* hide edit content button */
                document.getElementById('module_editbutton'+block).style.display = 'none';
            }

            for (i in this._params['moduleContents'][module_name]) {
                myform_content.options[myform_content.options.length] = new Option (this._params['moduleContents'][module_name][i], i);
            }
        } else {
            myform_content.options[myform_content.options.length] = new Option (this._locales['no_content'], '');
            /* hide edit content button */
            document.getElementById('module_editbutton'+block).style.display = 'none';
        }
    }

    /*
     * update all module panels
     * @return void
     * @access private
     */
    this.update_modulePanels = function() {
        for (var i=0; i<this._params['maxModules']; i++) {
            this.update_modulePanel(i);
            this.update_contentSelection(i);
        }
        this.check_usedModel();
    }

    /*
     * update selected option into given block content selector
     * @param integer block
     * @return void
     * @access private
     */
    this.update_contentSelection = function (block) {
        /* get form values */
        myform_name = eval('this._form.m'+block+'_name');
        myform_content = eval('this._form.m'+block+'_content');

        /* get module name value */
        module_name = myform_name.options[myform_name.selectedIndex].value;

        /* get selectedIndex */
        for (var i=0; i<myform_content.options.length; i++) {
            if (myform_content.options[i].value === this._params['selectedContents'][block]) {
                myform_content.options.selectedIndex = i;
                return;
            }
        }
    }

    /*
     * start page saving and go to the given item editor
     * @param integer block
     * @return void
     * @access public
     */
    this.edit_moduleContent = function (block) {
        /* get values */
        module_name = eval ('this._form.m'+block+'_name').value;
        module_content = eval('this._form.m'+block+'_content');

        /* check content */
        if (module_name != '' && module_content.disabled == false && this._params['moduleContents'][module_name] != -1) {
            this._form.next.value = block;
            this.valid_page();
        }
    }

    /*
     * update select object with selected value
     * @param string select
     * @param mixed value
     * @return void
     * @access private
     */
    this.update_selectedValue = function(select, value){
        /* get select element */
        myselect = eval('this._form.' + select);

        /* check select element */
        if (!myselect)
            return;

        for (var i=0; i < myselect.length; i++) {
            if (myselect.options[i].value == value) {
                myselect.selectedIndex = i;
                return;
            }
        }
    }

    /*
     * check if current content correspond to a model
     * @return void
     * @access private
     */
    this.check_usedModel = function() {
        if (this._params['models'].length == 0)
            return;

        /* init vars */
        selected = '';
        selsimvalue = 0;

        for (var j in this._params['models']) {
            simvalue = 0;
            model = this._params['models'][j];

            /* check template */
            if (this._form.template.options[this._form.template.selectedIndex].value != model['template'])
                continue;

            /* check theme */
            if (this._form.theme.options[this._form.theme.selectedIndex].value != model['theme'])
                continue;

            /* check modules and their contents */
            for (var i=0; i<this._params['maxModules']; i++) {
                if (!model["m"+i+"_name"] || model["m"+i+"_name"] == '')
                    continue;

                /* check module name */
                myselect = eval('this._form.m'+i+'_name');
                if (myselect.options[myselect.selectedIndex].value == model['m'+i+'_name']) {
                    simvalue++;
                } else {
                    simvalue=-1;
                    break;
                }

                /* check module content */
                if (model["m"+i+"_content"] != "" && model["m"+i+"_content"] != "0") {
                    myselect = eval('this._form.m'+i+'_content');
                    if (myselect.selectedIndex && myselect.selectedIndex >= 0 && myselect.options[myselect.selectedIndex].value == model['m'+i+'_content']) {
                        simvalue++;
                    } else {
                        simvalue=-1;
                        break;
                    }
                }

                /* check module theme */
                if (this._params['allowThemeChange']) {
                    myselect = eval('this._form.m'+i+'_theme');
                    if (myselect.options[myselect.selectedIndex].value == model['m'+i+'_theme']) {
                        simvalue++;
                    } else {
                        simvalue=-1;
                        break;
                    }
                }
            }

            /* update selected item */
            if (simvalue == -1)
                continue;
            else if (simvalue > selsimvalue) {
                selected = j;
                selsimvalue = simvalue;
            }
        }

        /* update model selector */
        for (var i=0; i<this._form.model.length; i++) {
            if (this._form.model.options[i].value === selected) {
                this._form.model.selectedIndex = i;
                return;
            }
        }
    }

    /*
     * lock model content
     */
    this.lock_content = function() {
        /* check user mode */
        if (this._params['modelMode'] == 'admin')
            return;

        /* check model value */
        model = this._form.model[this._form.model.selectedIndex].value;
        if (model > 0    && this._params['models'][model])
            model = this._params['models'][model];
        else
            return this.unlock_content();

        /* lock item for non admin users */
        this._form.template.disabled=true;
        this._form.theme.disabled=true;
        for (var i=0; i<this._params['maxModules']; i++) {
            if (model["m"+i+"_name"] != '') {
        eval('this._form.m'+i+'_name').disabled=true;
        if (this._params['allowThemeChange'])
            eval('this._form.m'+i+'_theme').disabled=true;
        if (model["m"+i+"_content"] != "0") {
            eval('this._form.m'+i+'_content').disabled=true;
        } else {
            eval('this._form.m'+i+'_content').disabled=false;
        }
            } else {
        eval('this._form.m'+i+'_name').disabled=false;
        if (this._params['allowThemeChange'])
            eval('this._form.m'+i+'_theme').disabled=false;
            eval('this._form.m'+i+'_content').disabled=false;
            }
        }
    }

    /*
     * unlock model content
     * @return void
     * @access private
     */
    this.unlock_content = function() {
        this._form.template.disabled=false;
        this._form.theme.disabled=false;
        for (var i=0; i<this._params['maxModules']; i++) {
            eval('this._form.m'+i+'_name').disabled=false;
            eval('this._form.m'+i+'_content').disabled=false;
            if (this._params['allowThemeChange'])
                eval('this._form.m'+i+'_theme').disabled=false;
        }
    }
}
