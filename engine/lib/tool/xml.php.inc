<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	        : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Engine / Tool library
 * Creation Date    : Oct 2007
 * Last Modif Date  : Jul 2010
 * 
 * XML methods
 */

/*
 * serialize PHP var to XML
 * @param mixed $data 
 * @return string
 * @access public
 */
function xml_serialize2XML( $data, $name='xml' ) {
  $xml = '';
  if ( is_array( $data ) ) {
    $xml.='<'.$name.'>';
    if ( $data == array_values($data) ) {
      /* indexed array */
      foreach( $data as $index => $value ) {
	$xml.= xml_serialize2XML( $value, $name.'item' );
      }
    } else {
      /* structured array */
      foreach( $data as $index => $value ) {
	$xml.= xml_serialize2XML( $value, $index );
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

/*
 * unserialize XML data to array object
 * @param string $data
 * @return array
 * @access public
 */
function xml_unserialize($data) {
  include_once('PEAR/XMLParser.php');
  if ( class_exists('PEAR_XMLParser')) {
    $parser = new PEAR_XMLParser();
    $parser->parse($data);
    return $parser->getdata();
  }
  return array();
}


/* ** DEPRECATED ** */


/*
 * [deprecated]serialize PHP var to XML
 * @param mixed $data 
 * @return string
 * @access public
 */
function xml_serializeToXML( $data ) {
  $type = gettype($data);
  switch ( $type ) {
  case 'array':
  case 'object':
    $xml = '';
    $i = 0;
    $array = true;
    foreach ( array_keys($data) as $k )
      if ( ($i++ . '') != $k ) {
	$array = false;
	break;
      }
    if ( $array ) {
      $xml = '<array>';
      foreach ( $data as $v )
	$xml .= '<item>' . xml_serializeToXML($v) . '</item>';
      $xml .= '</array>';
      return $xml;
    } else {
      $xml = '<map>';
      foreach ( $data as $k => $v )
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
    return '<boolean>' . ( $data ? 'true' : 'false' ) . '</boolean>';
  case 'unknown type':
  default:
    return '<null/>';
  }
}

?>