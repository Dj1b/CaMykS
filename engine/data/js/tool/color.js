/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Mar 2007
 * Last Modif Date	: Mar 2007
 *
 * Color relative methods
 */

/* 
 * compute a range of colors between two colors
 * @access public
 * @param string s : hexadecimal color
 * @param string e : hexadecimal color
 * @param string steps : range steps
 * @return array
 */
function color_getColorRange ( s, e, steps ) {
  /* init */
  result = new Array();
  
  scolor = color_hexa2rvb ( s );
  ecolor = color_hexa2rvb ( e );
  
  /* computation */
  for ( var i=0; i<= steps; i++ ) {
    color = new Array();
    color[0] = (scolor[0] + parseInt( (ecolor[0]-scolor[0])/steps*i)).toString(16).toUpperCase();
    color[1] = (scolor[1] + parseInt( (ecolor[1]-scolor[1])/steps*i)).toString(16).toUpperCase();
    color[2] = (scolor[2] + parseInt( (ecolor[2]-scolor[2])/steps*i)).toString(16).toUpperCase();
    result[i] = color_rvb2hexa ( color ); 
  }
  return result;
}

/*
 * return hexadecimal color in RGB
 * @access public
 * @param string color : hexadecimal color
 * @return array
 */
function color_hexa2rvb ( color ) {
  rvb = new Array();
  rvb[0] = parseInt ( color.substring(0, 2), 16);
  rvb[1] = parseInt ( color.substring(2, 4), 16);
  rvb[2] = parseInt ( color.substring(4, 6), 16);
  return rvb;
}

/*
 * return RGB color in hexadecimal
 * @access public
 * @param array rvb : RGB color
 * @return string
 */
function color_rvb2hexa ( rvb ) {
  return string_untrim ( rvb[0], 2, '0', 0 ) + string_untrim( rvb[1], 2, '0', 0 )+ string_untrim ( rvb[2], 2, '0', 0 );
}
