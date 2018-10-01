/**
 * @brief Admin_ContentPage module modifying page scripts
 * @details Plugin / Module Scripts
 * @file plugin/module/Admin_ContentPage/js/contentpage_modify.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Jun 2005
 * @date Modification: Sep 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

contentpage_selTemplate = "";

/*
 * call by template selector
 */
function contentpage_updateTemplate ( ) {
  contentpage_updateTemplatePanel();
  contentpage_checkUsedModel();
}


/*
 * update template panel ( show active modules )
 */
function contentpage_updateTemplatePanel() {
    /* get form */
    myform = document.admin_contentpage_form;

    /* unselect actual template */
    if ( i = document.getElementById('template_'+contentpage_selTemplate) ) {
	i.style.display='none';
    }

    /* update selected template value */
    contentpage_selTemplate = myform.template.options[myform.template.selectedIndex].value;

    if ( contentpage_selTemplate == '' ) {
	contentpage_selTemplate = site_default_template;
    }
    /* select new template */
    if ( i = document.getElementById('template_'+contentpage_selTemplate) ) {
	i.style.display='block';
    }

    /* active modules */
    m = contentpage_countModules[ contentpage_selTemplate ];
    for ( var i=0; i<m; i++ ) {
      if ( document.getElementById('module'+i) )
	document.getElementById('module'+i).style.display = 'block';
    }

    /* unactive useless modules */
    m = contentpage_countModules[ contentpage_selTemplate ];
    for ( var i=m; i<contentpage_maxModules; i++ ) {
	document.getElementById('module'+i).style.display = 'none';
    }

    /* safari hack */
    if ( navigator.userAgent.toLowerCase().indexOf('applewebkit') != -1  ) {
	window.innerWidth++;
	window.innerWidth--;
    }
}

/*
 * call by module selectors
 */
function contentpage_updateModule ( idx ) {
  contentpage_updateModulePanel( idx );
  contentpage_checkUsedModel();
}

/*
 * update module available contents
 */
function contentpage_updateModulePanel( idx ) {
    /* get form */
    myform = document.admin_contentpage_form;

    /* get form element */
    myform_name = eval ( 'myform.m'+idx+'_name' );
    myform_content = eval ( 'myform.m'+idx+'_content');

    /* get module name value */
    module_name = myform_name.options[myform_name.selectedIndex].value;

    /* update module content select */
    myform_content.options.length = 0;

    if (  contentpage_contents[module_name] && contentpage_contents[module_name] != -1 ) {
	myform_content.options[myform_content.options.length] = new Option ( contentpage_new_content, 0 );
	myform_content.options[myform_content.options.length] = new Option ( '---------------------', 0 );
	for ( i in contentpage_contents[module_name] ) {
	    myform_content.options[myform_content.options.length] = new Option ( contentpage_contents[module_name][i], i);
	}
	/* show edit content button */
	document.getElementById('module_editbutton'+idx).style.display = 'block';
    } else {
	myform_content.options[myform_content.options.length] = new Option ( contentpage_no_content, '');
	/* hide edit content button */
	document.getElementById('module_editbutton'+idx).style.display = 'none';
    }
}

/*
 * update all modules
 */
function contentpage_updateModules ( ) {
  for ( var i=0; i<contentpage_maxModules; i++ ) {
    contentpage_updateModulePanel ( i );
    contentpage_updateContentSelection( i );
  }
  contentpage_checkUsedModel();
}

/*
 * call by module content selectors
 */
function contentpage_updateModuleContent() {
  contentpage_checkUsedModel();
}

/*
 * call by module theme selectors
 */
function contentpage_updateModuleTheme() {
  contentpage_checkUsedModel();
}

/*
 * update selected option into given module content selector
 */
function contentpage_updateContentSelection ( idx ) {
    /* get form */
    myform = document.admin_contentpage_form;

    /* get form element */
    myform_content = eval ( 'myform.m'+idx+'_content');

    /* get selectedIndex */
    for ( var i=0; i<myform_content.options.length; i++ ) {
	if ( myform_content.options[i].value == contentpage_selcontents[idx] ) {
	    myform_content.selectedIndex = i;
	    return;
	}
    }
}

/*
 * start page saving and go to the given item editor
 */
function contentpage_editModule ( i ) {
    /* get values */
    module_name = eval ( 'myform.m'+i+'_name' ).value;
    module_content = eval( 'myform.m'+i+'_content');
    /* check content */
    if ( module_name!= '' && module_content.disabled==false && contentpage_contents[module_name] != -1 ) {
	document.admin_contentpage_form.next.value= i;
	contentpage_submitPage();
    }
}

/*
 * call by model selector
 */
function contentpage_selectModel() {
  /* get form */
  myform = document.admin_contentpage_form;
  model = myform.model[myform.model.selectedIndex].value;

  /* check model value */
  if ( model > 0  && contentpage_models[model] )
    model = contentpage_models[model];
  else
    return contentpage_unlockContent();

  /* select template */
  contentpage_updateSelectedValue('template', model["template"] );
  contentpage_updateTemplatePanel();

  /* select theme */
  contentpage_updateSelectedValue('theme', model["theme"] );

  /* select modules */
  for (var i=0; i<contentpage_maxModules; i++) {
    if ( model["m"+i+"_name"] != '' ) {
      contentpage_updateSelectedValue('m'+i+'_name',  model["m"+i+"_name"] );
      contentpage_updateModulePanel ( i );
      if ( model["m"+i+"_content"] != "" && model["m"+i+"_content"] != "0" ) {
	contentpage_updateSelectedValue('m'+i+'_content',  model["m"+i+"_content"] );
      }
      if (contentpage_allowThemeChange)
	contentpage_updateSelectedValue('m'+i+'_theme',  model["m"+i+"_theme"] );
    }
  }
  contentpage_lockContent();
}

/*
 * tool method which update selected option in given selector
 */
function contentpage_updateSelectedValue( select, value ) {
  /* get form */
  myform = document.admin_contentpage_form;

  /* get select element */
  myselect = eval('myform.'+select);

  /* check select element */
  if ( !myselect )
    return;

  for ( var i=0; i<myselect.length; i++ ) {
    if ( myselect.options[i].value == value ) {
      myselect.selectedIndex = i;
      return;
    }
  }
}

/*
 * check if current content correspond to a model
 */
function contentpage_checkUsedModel() {
  if ( contentpage_models.length == 0 )
    return;

  /* get form */
  myform = document.admin_contentpage_form;
  selected = '';
  selsimvalue = 0;

  for ( var j in contentpage_models ) {
    simvalue = 0;
    model = contentpage_models[j];

    /* check template */
    if ( myform.template.options[myform.template.selectedIndex].value != model['template'] )
      continue;
    /* check theme */
    if ( myform.theme.options[myform.theme.selectedIndex].value != model['theme'] )
      continue;
    /* check modules and their contents */
    for (var i=0; i<contentpage_maxModules; i++) {
      if ( !model["m"+i+"_name"] || model["m"+i+"_name"] == '' )
	continue;

      /* check module name */
      myselect = eval('myform.m'+i+'_name');
      if ( myselect.options[myselect.selectedIndex].value == model['m'+i+'_name'] ) {
	simvalue++;
      } else {
	simvalue=-1;
	break;
      }

      /* check module content */
      if ( model["m"+i+"_content"] != "" && model["m"+i+"_content"] != "0" ) {
	myselect = eval('myform.m'+i+'_content');
	if (myselect.selectedIndex &&
	    myselect.selectedIndex>=0 &&
	    myselect.options[myselect.selectedIndex].value == model['m'+i+'_content'] ) {
	  simvalue++;
	} else {
	  simvalue=-1;
	  break;
	}
      }

      /* check module theme */
      if ( contentpage_allowThemeChange) {
	myselect = eval('myform.m'+i+'_theme');
	if ( myselect.options[myselect.selectedIndex].value == model['m'+i+'_theme'] ) {
	  simvalue++;
	} else {
	  simvalue=-1;
	  break;
	}
      }
    }

    /* update selected item */
    if ( simvalue == -1 )
      continue;
    else if ( simvalue > selsimvalue ) {
      selected = j;
      selsimvalue = simvalue;
    }
  }

  /* update model selector */
  for ( var i=0; i<myform.model.length; i++ ) {
    if ( myform.model.options[i].value == selected ) {
      myform.model.selectedIndex = i;
      return;
    }
  }
}

/*
 * call by theme selector
 */
function contentpage_updateTheme ( ) {
  contentpage_checkUsedModel();
}


/*
 * submit page
 */
function contentpage_submitPage() {
  contentpage_unlockContent();
  document.admin_contentpage_form.submit();
}

/*
 * lock model content
 */
function contentpage_lockContent() {
  /* check user mode */
  if ( contentpage_mode == 'admin' )
    return;

  /* check model value */
  model = myform.model[myform.model.selectedIndex].value;
  if ( model > 0  && contentpage_models[model] )
    model = contentpage_models[model];
  else
    return contentpage_unlockContent();

  /* lock item for non admin users */
  document.admin_contentpage_form.template.disabled=true;
  document.admin_contentpage_form.theme.disabled=true;
  for (var i=0; i<contentpage_maxModules; i++) {
    if ( model["m"+i+"_name"] != '' ) {
      eval( 'myform.m'+i+'_name').disabled=true;
      if (contentpage_allowThemeChange)
	eval( 'myform.m'+i+'_theme').disabled=true;
      if ( model["m"+i+"_content"] != "0" ) {
        eval( 'myform.m'+i+'_content').disabled=true;
      } else {
        eval( 'myform.m'+i+'_content').disabled=false;
      }
    } else {
      eval( 'myform.m'+i+'_name').disabled=false;
      if (contentpage_allowThemeChange)
	eval( 'myform.m'+i+'_theme').disabled=false;
      eval( 'myform.m'+i+'_content').disabled=false;
    }
  }
}

/*
 * unlock model content
 */
function contentpage_unlockContent() {
  myform = document.admin_contentpage_form;
  document.admin_contentpage_form.template.disabled=false;
  document.admin_contentpage_form.theme.disabled=false;
  for (var i=0; i<contentpage_maxModules; i++) {
    eval( 'myform.m'+i+'_name').disabled=false;
    eval( 'myform.m'+i+'_content').disabled=false;
    if (contentpage_allowThemeChange)
      eval( 'myform.m'+i+'_theme').disabled=false;
  }
}
