/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Jul 2007
 * Last Modif Date	: Jul 2007
 *
 * Mail relative javascript library
 */

/*
 * simulate mailto link
 * @acces private
 * @param string a : 2nd part of the email
 * @param string b : fake value
 * @param string c : 1st part of the email
 * @param string d : fake value
 * @return null
 */
function mail_to(a, b, c, d) {
  document.location.href="mailto:"+c+"@"+a;
}

/*
 * return email value from mail_to params
 * @param string a : 2nd part of the email
 * @param string b : fake value
 * @param string c : 1st part of the email
 * @param string d : fake value
 * @return string
 */
function mail_get(a, b, c, d) {
  return c+"@"+a;
}


/*
 * return email value from javascript link
 * @param string link
 * return string email
 */
function mail_decodeLink(link) {
  if ( link.indexOf('javascript:mail_to') == -1 )
    return '';

  b = link.indexOf('(')+1;
  e = link.lastIndexOf(')');
  params = link.substring( b, e );
  eval ('email = mail_get('+params+')');
  return email;
}

/*
 * generate mail_to javascript link from email
 * @param string email
 * @return string
 */
function mail_encodeLink(email) {
  
  a = email.indexOf('@');
  if ( a == -1 ) {
    return '';
  }

  bpart = email.substring(0, a);
  epart = email.substring(a+1, email.length);

  link = "javascript:mail_to('"+epart+"', 'contact', '"+bpart+"', '@hotmail.com');";
  return link;
}

/*
 * check if email is valid
 * @param string email
 * @return boolean result
 */
function mail_isValid(email) {
  regex = /^((\"[^\"\f\n\r\t\v\b]+\")|([\w\!\#\$\%\&\'\*\+\-\~\/\^\`\|\{\}]+(\.[\w\!\#\$\%\&\'\*\+\-\~\/\^\`\|\{\}]+)*))@((\[(((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9])))\])|(((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9])))|((([A-Za-z0-9\-])+\.)+[A-Za-z\-]+))$/;
  return (email.match(regex) != null);
}
