<?php
/**
 * @brief XML specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/xml.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Serialize PHP var to XML.
 * @param mixed $data
 * @param string $name
 * @return string
 */
function xml_serialize2XML($data, $name='xml') {
    $xml = '';
    if (is_array($data)) {
        $xml.='<'.$name.'>';
        if ($data == array_values($data)) {
            /* indexed array */
            foreach($data as $index => $value) {
                $xml.= xml_serialize2XML($value, $name.'item');
            }
        } else {
            /* structured array */
            foreach($data as $index => $value) {
                $xml.= xml_serialize2XML($value, $index);
            }
        }
        $xml.='</'.$name.'>';
    } else if (is_string($data)) {
        $xml.='<'.$name.' type="string"><![CDATA['.$data.']]></'.$name.'>';
    } else {
        $xml.='<'.$name.' type="'.gettype($data).'">'.$data.'</'.$name.'>';
    }
    return $xml;
}

/**
 * Unserialize XML data to array object.
 * @param string $data
 * @return array
 */
function xml_unserialize($data) {
    include_once('PEAR/XMLParser.php');
    if (class_exists('PEAR_XMLParser')) {
        $parser = new PEAR_XMLParser();
        $parser->parse($data);
        return $parser->getdata();
    }
    return array();
}

/*** DEPRECATED ***/

/**
 * Serialize PHP var to XML.*
 * @see xml_serialize2XML()
 * @param mixed $data 
 * @return string
 * @deprecated : Old fashion style, use xml_serialize2XML
 */
function xml_serializeToXML($data) {
    $type = gettype($data);
    switch ($type) {
        case 'array':
        case 'object':
            $xml = '';
            $i = 0;
            $array = true;
            foreach (array_keys($data) as $k)
                if (($i++ . '') != $k) {
                    $array = false;
                    break;
                }
            if ($array) {
                $xml = '<array>';
                foreach ($data as $v)
                    $xml .= '<item>' . xml_serializeToXML($v) . '</item>';
                $xml .= '</array>';
                return $xml;
            } else {
                $xml = '<map>';
                foreach ($data as $k => $v)
                    $xml .= '<item key="' . $k . '">' . xml_serializeToXML($v) . '</item>';
                $xml .= '</map>';
                return $xml;
            }
        case 'integer':
        case 'double':
            return '<' . $type . '>' . $data . '</' . $type . '>';
        case 'string':
            return '<string><![CDATA[' . $data . ']]></string>';
        case 'boolean':
            return '<boolean>' . ($data ? 'true' : 'false') . '</boolean>';
        case 'unknown type':
        default:
            return '<null/>';
    }
}
?>