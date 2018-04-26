/**
 * @brief Client side scripts related to XML
 * @details Engine / Javascript tool library
 * @file engine/data/js/tool/xml.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Dec 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * Return XML object as JS object (from xml_serializeToXML CaMykS function).
 * @access public
 * @param XMLDoc xmlObject 
 * @return mixed
 */
function xml_serializeToJS(xmlObject) {
    return xml_serializeValueToJS(xmlObject.firstChild);
}

/*
 * Return XML value as JS value.
 * @access private
 * @param XMLNode xmlNode
 * @return mixed
 */
function xml_serializeValueToJS(xmlNode) {
    if (xmlNode == null)
        return null;
    switch (xmlNode.nodeName) {
        case 'array' :
            var value = new Array();
            for (var child = xmlNode.firstChild; child != null; child = child.nextSibling) {
                if ((child.nodeName == 'item') && (child.firstChild != null))
                    value.push(xml_serializeValueToJS(child.firstChild));
                }
            return value;
        case 'map' :
            var value = {};
            for (var child = xmlNode.firstChild; child != null; child = child.nextSibling) {
                var key;
                if ((child.nodeName == 'item') 
                        && (child.firstChild != null) 
                        && (child.attributes.length > 0)
                        && (child.attributes[0].name=="key")
                        && ((key = child.attributes[0].value) != null))
                    value[key] = xml_serializeValueToJS(child.firstChild);
            }
            return value;
        case 'string' :
        case 'integer' :
        case 'double' :
            return ((xmlNode.firstChild != null) ? xmlNode.firstChild.nodeValue : null);
        case 'boolean' :
            return ((xmlNode.firstChild != null) && (xmlNode.firstChild.nodeValue == 'true'));
        case 'null' :
        default :
            return null;
    }
}


function xml_serializeObject(xmlObject) {
    if (xmlObject == null)
        return null;
    return xml_serializeItem(xmlObject.firstChild);
}

function xml_serializeItem(xmlNode) {

    if(xmlNode.hasChildNodes() == false) {
        return xml_serializeValue(xmlNode.getAttribute('type'), xmlNode);
    }
    
    nname = xmlNode.firstChild.nodeName;
    /* this node is a node value */
    if (nname == "#text" || nname == "#cdata-section")
        return xml_serializeValue(xmlNode.getAttribute('type'), xmlNode.firstChild);
        
    /* this is a list node, check array type */
    type = 'array';
    if (xmlNode.nodeName + 'item' == nname) {
        // nothing: keep as array
    } else if (xmlNode.childNodes.length == 1 && isNaN(parseInt(nname))) {
            type = 'object';
    } else {
        for (var child = xmlNode.firstChild; child != null; child = child.nextSibling) {
            if (child.nodeName != nname) {
                type = 'object';
                break;
            }
        }
    }
        
    if (type=='array') {
        var mynode = new Array();
        for (var child = xmlNode.firstChild; child != null; child = child.nextSibling) {
            mynode.push(xml_serializeItem(child));
        }
    } else {
        var mynode = {};
        for (var child = xmlNode.firstChild; child != null; child = child.nextSibling) {
            mynode[child.nodeName] = xml_serializeItem(child);
        }
    }
    return mynode;
}

function xml_serializeValue(type, xmlNode) {
    switch (type) {
    case 'integer':
    case 'boolean':
        return parseInt(xmlNode.nodeValue);
    case 'double':
        return parseFloat(xmlNode.nodeValue);
    case 'string':
    default:
        if (xmlNode.nodeValue == null)
            return '';
        return ''+xmlNode.nodeValue;
    }
}
