/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Fev 2006
 * Last Modif Date	: Jul 2016
 *
 * String javascript methods
*/

/* 
 * prototype trim method to String object
 * @access public
 * return string
 */
String.prototype.trim = function () {
  return this.replace(/(^\s*)|(\s*$)/g,'');
}

/*
 * prototype untrim method to string object,
 * complete word to given length, with given char
 * @access public
 * @param int slen
 * @param chr schar
 * @param int sposition
 */

String.prototype.untrim = function(slen, schar, sposition) {
  v = this;
  while ( v.length < slen ) {
    if ( sposition == 0 ) {
      v = schar+this;
    } else if ( sposition == 1 ) {
      v += schar;
    } else {
      break;
    }
  }
  return v;
}

/*
 * prototype method to strip tags 
 * @param string string
 * @param string allowed
 * @return string
 */
String.prototype.strip_tags = function(allowed) {
  allowed = (((allowed || '') + '').toLowerCase().match(/<[a-z][a-z0-9]*>/g) || []).join('')

  var tags = /<\/?([a-z][a-z0-9]*)\b[^>]*>/gi
  var commentsAndPhpTags = /<!--[\s\S]*?-->|<\?(?:php)?[\s\S]*?\?>/gi

  return this.replace(commentsAndPhpTags, '').replace(tags, function ($0, $1) {
    return allowed.indexOf('<' + $1.toLowerCase() + '>') > -1 ? $0 : ''
  });
}


/* 
 * trim string 
 * @access public
 * @param string string
 * return string
 */
function string_trim(string) {
  return string.replace(/(^\s*)|(\s*$)/g,'');
}

/* 
 * complete word to given length, with given char
 * @access public
 * @param string string
 * @param int slen
 * @param chr schar
 * @param int sposition
 * return string
 */
function string_untrim( string, slen, schar, sposition ) {
  while ( string.length < slen ) {
    if ( sposition == 0 ) {
      string = schar+string;
    } else if ( sposition == 1 ) {
      string += schar;
    } else {
      break;
    }
  }
  return string;
}

/*
 * strip tags from given value
 * @param string string
 * @param string allowed
 * @return string
 */
function string_stripTags (string, allowed) {
  allowed = (((allowed || '') + '').toLowerCase().match(/<[a-z][a-z0-9]*>/g) || []).join('');

  var tags = /<\/?([a-z][a-z0-9]*)\b[^>]*>/gi
  var commentsAndPhpTags = /<!--[\s\S]*?-->|<\?(?:php)?[\s\S]*?\?>/gi

  return string.replace(commentsAndPhpTags, '').replace(tags, function ($0, $1) {
    return allowed.indexOf('<' + $1.toLowerCase() + '>') > -1 ? $0 : ''
  });
}