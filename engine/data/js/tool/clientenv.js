/**
 * @brief Client side scripts related client environment.
 * @details Engine / Javascript tool library
 * @file engine/data/js/tool/clientenv.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Mar 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
 
function tool_getClientBrowserType() {
    if (navigator.appName == 'Netscape') {
        return 'netscape';
    } else {
        return 'explorer';
    }
}

function tool_getClientBrowserName() {
    app = navigator.userAgent.toLowerCase();
    
    if (app.indexOf('safari')) {
        return 'safari';
    } else if (app.indexOf('firefox')) {
        return 'firefox';
    } else if (app.indexOf('msie')) {
        return 'explorer';
    } else if (app.indexOf('icab')) {
        return 'icab';
    } else if (app.indexOf('opera')) {
        return 'opera';
    }
    return 'unknown';
}

function tool_getClientBrowserFullName() {
    app = navigator.userAgent.toLowerCase();
    
    if (app.indexOf('safari')) {
        return 'Safari';
    } else if (app.indexOf('firefox')) {
        return 'Firefox';
    } else if (app.indexOf('msie')) {
        return 'Explorer';
    } else if (app.indexOf('icab')) {
        return 'iCab';
    } else if (app.indexOf('opera')) {
        return 'Opera';
    }
    return 'unknown';
}

