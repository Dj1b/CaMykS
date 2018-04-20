/**
 * @brief Client side scripts used for admin section.
 * @details Engine / Javascript tool library
 * @file engine/data/js/tool/adminengine.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

adminengine_divs = new Array();

/**
 * Open modal popup.
 * @param string myobject
 * @return void
 */
function adminengine_modalPopupOpen(myobject) {
    if (!document.getElementById(myobject))
        return;

    /* get DOM objects */
    popup = document.getElementById(myobject);
    popupbg = document.getElementById('adminengine_modalPopupBackground');
    body = document.getElementsByTagName('body')[0];

    /* disable all overflowed object in page */
    adminengine_divs = new Array();
    tags = document.getElementsByTagName('div');
    for (var i=0; i<tags.length; i++) {
        if (tags[i].style.overflow == 'auto' && tags[i].style.display == 'block') {
            tags[i].style.display = 'none';
            adminengine_divs[adminengine_divs.length] = tags[i];
        }
    }

    /* display background divs */
    popupbg.style.display = 'block';
    popupbg.style.width = Math.max(body.offsetWidth, document.documentElement.clientWidth) + 'px';
    popupbg.style.height = Math.max(body.offsetHeight, document.documentElement.clientHeight) + 'px';

    /* display popup */
    popup.style.display = 'block';
    popup.style.zIndex = popupbg.style.zIndex+1;
    popup.style.left = (Math.min(body.offsetWidth, document.documentElement.clientWidth)-popup.offsetWidth)/2 + 'px';
    popup.style.top = (Math.min(body.offsetHeight, document.documentElement.clientHeight)-popup.offsetHeight)/2 + 'px';
}

/**
 * Close modal popup.
 * @param string myobject
 * @return void
 */
function adminengine_modalPopupClose(myobject) {
    if (!document.getElementById(myobject))
        return;

    /* get div objects */
    popup = document.getElementById(myobject);
    popupbg = document.getElementById('adminengine_modalPopupBackground');

    /* hide objects */
    popup.style.display = 'none';
    popupbg.style.display = 'none';

    /* re-enable all overflowed object in page */
    for (var i=0; i< adminengine_divs.length; i++) {
        adminengine_divs[i].style.display = 'block';
    }
}

/**
 * Confirm link redirection.
 * @param string link
 * @param string message
 * @return void
 */
function adminengine_confirmRedirect(link, message){
    if (confirm(message) === true)
        document.location.href = link;
}
