/**
 * @brief Content_GenericPageRedirector module page redirector edition scripts
 * @details Plugin / Module Scripts
 * @file plugin/module/Content_GenericPageRedirector/js/pageredirector.js
 * @author CaMykS Team
 * @version 1.0.1
 * @date Creation: Sep 2009
 * @date Modification: Jan 2019
 * @copyright 2009 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Open page chooser with actual value.
 * @return void
 */
function open_pageChooser() {
    v = document.edit_form.url.value;
    pc2.openPageChooser(v);
}

/*
 * Update selected page value.
 * @return void
 */
function update_selectedPage(page) {
    document.edit_form.url.value = page;
}

/*
 * Update form item case of method value.
 * @return void
 */
function update_formFromMethod() {
  m = document.edit_form.method.options[document.edit_form.method.options.selectedIndex].value;
  if (m == 3)
    document.getElementById('delay_block').style.display = 'none';
  else
    document.getElementById('delay_block').style.display = 'block';
}
