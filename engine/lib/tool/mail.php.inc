<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Tool Library
 * Creation Date	: Jul 2007
 * Last Modif Date	: Jul 2007
 *
 * mail relative
 * TO DO : add values for antispam from lists 
 * 
 */


/*
 * Encode email to be used with engine/data/js/tool/mail.js scripts
 * @param string $email the email to encode
 * @return string
 * @access public
 */
function mail_encode ( $email ) {

  $parts = explode('@', $email );
  if ( count( $parts ) == 2 ) {
    return  "javascript:mail_to('".$parts[1]."', 'contact', '".$parts[0]."', '@hotmail.com');";
  }
  return '';
}

/* 
 * Check if email is valid
 * @param string $email the email to check
 * @return boolean
 * @access public
 */
function  mail_isValidEmail ( $email='' ) {
  $regex = '/^((\"[^\"\f\n\r\t\v\b]+\")|([\w\!\#\$\%\&\'\*\+\-\~\/\^\`\|\{\}]+(\.[\w\!\#\$\%\&\'\*\+\-\~\/\^\`\|\{\}]+)*))@((\[(((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9])))\])|(((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9])))|((([A-Za-z0-9\-])+\.)+[A-Za-z\-]+))$/';
  if ( preg_match($regex, $email ) )
    return true;
  return false;
}

/* 
 * Alias to 'mail_isValidEmail' function
 * @param string $email The mail to check
 * @return boolean
 * @access public
 * @deprecated use mail_isValidEmail instead
 */
function email_isValidEmail ( $email='' ) {
  return mail_isValidEmail( $email );
}

/*
 * Send a mail
 * @param array $params email parameters
 * @return mixed
 * @access public
 */
function mail_send( $params ) {
  global $camyks;
    
  /* check header values */
  if (!isset($params['headers'])) 
    $params['headers'] = array();
  $headers = array('from', 'reply-to', 'return-path', 'MIME-Version', 'Content-type', 'return-receipt-to', 'Date');
  
  foreach ($headers as $h) {
    if ( isset($params[$h])) {
      $params['headers'][$h] = $params[$h];
      unset($params[$h]);
    }
  }
  
  /* check recipients */
  if (isset($params['recipients'])){
    $params['to'] = $params['recipients'];
    unset($params['recipients']);
  }
  
  /* check subject */
  if (!isset($params['subject']))
    $params['subject'] = '';
  
  /* if pear mail library is available, use this */
  if (file_exists( $camyks->camyks_engine_path.'/lib/external/PEAR/Mail.php')) {
    return mail_sendPEARMail( $params );
  } else {
    return mail_sendPHPMail( $params );
  }
}

/*
 * Send a html mail
 * @param array $params email parameters
 * @return mixed
 * @access public
 */
function mail_sendHTMLMail( $params ) {
  global $camyks;
  
  if (isset($params['headers'])) {
    /* check headers params */
    if ( !isset ( $params['headers']['MIME-Version'] ) )
      $params['headers']['MIME-Version'] = '1.0';
    if ( !isset ( $params['headers']['Content-type'] ) )
      $params['headers']['Content-type'] = 'text/html; charset='.$camyks->get_htmlencodingvalue();
  } else {
    /* set headers params */
    $params['headers'] = array();
    if ( !isset ( $params['MIME-Version']))
      $params['headers']['MIME-Version'] = '1.0';
    else {
      $params['headers']['MIME-Version'] = $params['MIME-Version'];
      unset($params['MIME-Version']);
    }
    if ( !isset ( $params['Content-type']))
      $params['headers']['Content-type'] = 'text/html; charset='.$camyks->get_htmlencodingvalue();
    else {
      $params['headers']['Content-type'] = $params['Content-type'];
      unset($params['Content-type']);
    }

    /* check To param */
    if (isset($params['To']))
      $params['headers']['To'] = $params['To'];
    elseif(isset($params['to']))
      $params['headers']['To'] = $params['to'];

    /* check from param */
    if (isset($params['From']))
      $params['headers']['From'] = $params['From'];
    elseif(isset($params['from']))
      $params['headers']['From'] = $params['from'];

    /* check Cc param */
    if (isset($params['Cc'])) {
      $params['headers']['Cc'] = $params['Cc'];
      unset($params['Cc']);
    }
  }
  return mail_send( $params );
}

/*
 * Send mail using built-in php mail engine
 * @param mixed $to email recipient(s)
 * @param mixed $headers email header(s)
 * @param mixed $body email body
 * @return mixed
 * @access private
 */
function mail_sendPHPMail ( $params ) {
  if (is_array($params['to'])) {
    $params['to'] = implode(', ', $params['to']);
  }

  $headers_ = array();
  foreach ( $params['headers'] as $name => $value ) {
    $headers_[] = $name. ': '.$value;
  }
  $headers_ = implode ( "\r\n", $headers_ );

  return mail($params['to'], $params['subject'], $params['content'], $headers_);
}

/*
 * Send mail using PEAR ( http://pear.php.net ) mail engine
 * @param mixed $to email recipient(s)
 * @param mixed $headers email header(s)
 * @param mixed $body email body
 * @return mixed
 * @access private
 */
function mail_sendPEARMail ( $params ) {
  global $camyks;
  include_once 'Mail.php';
  include_once 'Mail/mime.php';
  
  /* add subject to headers */
  $params['headers']['Subject'] = $params['subject'];
  $params['headers']['Date'] = date('r');
  
  if (class_exists('Mail_mime')) {
    /* build message data with Mail_mime */
    $message = new Mail_mime();
    if (isset($params['headers']['Content-type']))
      unset($params['headers']['Content-type']);
    
    /* add content */
    if (isset($params['HTMLcontent']) and isset($params['textcontent'])) {
      $message->setTXTBody($params['textcontent']);
      $message->setHTMLBody($params['HTMLcontent']);
    } else {
      $message->setHTMLBody($params['content']);
    }
    
    /* add attachments */
    if (isset($params['attachments'])) {
      if (is_string($params['attachments']))
	$message->addAttachment($params['attachments']);
      else
	foreach($params['attachments'] as $a)
	  $message->addAttachment($a);
    }

    /* add embedded images */
    if (isset($params['embeddedImages'])) {
      if (is_string($params['embeddedImages']))
	$message->addHTMLImage($params['embeddedImages']);
      else
	foreach($params['embeddedImages'] as $img)
	  $message->addHTMLImage($img);
    }
    
    /* get compiled values */
    $body = $message->get();
    $headers = $message->headers($params['headers']);
  } else {
    /* build message data with params */
    $body = $params['content'];
    $headers = $params['headers'];
  }
  
  /* send email with configured driver & settings */
  if ( isset( $camyks->_conf['PEARMailDriver'] ) ) {
    if ( isset( $camyks->_conf['PEARMailConfig'] ) ) {
      $myMail = Mail::Factory($camyks->_conf['PEARMailDriver'], $camyks->_conf['PEARMailConfig']);
    } else {
      $myMail = Mail::Factory($camyks->_conf['PEARMailDriver']);
    }
  } else {
    $myMail = Mail::Factory('mail');
  }

  /* check for CC values */
  $to = isset($params['to'])?$params['to']:$params['To'];
  if (isset($headers['Cc']))
    $to .= ', '.$headers['Cc'];
  $params['headers']['To'] = $to;

  /* send mail */
  return (PEAR::isError($myMail->send($to, $headers, $body ))===false);
}

?>