<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Engine / Object
 * Creation Date    : Jun 2012
 * Last Modif Date  : Jun 2012
 *
 * E-mail generic object
 */

class CMail {
  /* variables */
  var $params;

  /*
   * object constructor
   * @return void
   * @access public
   */
  function CMail() {
    $this->initialise();
  }

  /* public methods */
  
  /*
   * initialise object 
   * @return void
   * @access public
   */
  function initialise() {   
    $this->params = array(
         /* initialise headers */
        'MIME-Version' => '1.0',
        'Content-Type' => '',
        'Return-Path'=>'',
        'ReplyTo'=>array(),
        'From' => array(),
        'To' => array(),
        'Cc' => array(),
        'Bcc' => array(),
        'Headers' => array(),
        /* initialise content */
        'Subject' => '',
        'HTMLBody' => '',
        'TextBody' => '',
        'Attachments' => array(),
        'EmbeddedImages' => array(),
        );
    $this->error = '';
  }
  
  /* public header management methods */
  
  /*
   * set mime version
   * @param string $mime
   * @return void
   * @access public
   */
  function set_mimeVersion($mime) {
    $this->params['MIME-Version'] = $mime;
  }
  
  /*
   * set content type
   * @param string $type
   * @return void
   * @access public
   */
  function set_contentType($type) {
    $this->params['Content-Type'] = $type;
  }
  
  /*
   * set return path
   * @param string $email
   * @return void
   * @access public
   */
  function set_returnPath($email) {
    $this->params['Return-Path'] = $email;
  }
  
  /*
   * add supp header
   * @param string $name
   * @param string $value
   * @return void
   * @access public
   */
  function add_header($name, $value) {
    $this->params['Headers'][$name] = $value;
  }
  
  /*
   * set sender
   * @param string $email
   * @param string $name
   * @return void
   * @access public
   */
  function set_sender($email, $name='') {
    $this->params['From'] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
  }
  
  /*
   * add reply-to
   * @param string $email
   * @param string $name
   * @return void
   * @access public
   */
  function add_replyTo($email, $name='') {
    $this->params['ReplyTo'][] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
  }
  
  /*
   * add normal recipient
   * @param string $email
   * @param string $name
   * @return void
   * @access public
   */
  function add_recipient($email, $name='') {
    $this->params['To'][] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
  }
  
  /*
   * add Cc recipient
   * @param string $email
   * @param string $name
   * @return void
   * @access public
   */
  function add_ccRecipient($email, $name='') {
    $this->params['Cc'][] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
  }
  
  /*
   * add Bcc recipient
   * @param string $email
   * @param string $name
   * @return void
   * @access public
   */
  function add_bccRecipient($email, $name='') {
    $this->params['Bcc'][] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
  }
  
  
  /* public body & subject management methods */
  
  /*
   * set subject value
   * @param string $subject
   * @return void
   * @access public
   */
  function set_subject($subject) {
    /* check for HTML subject */
    
    /* update subject value */
    $this->params['Subject'] = $this->_check_stringEncoding($subject);
  }
  
  /*
   * set text body
   * @param string $content
   * @return void
   * @access public
   */
  function set_textBody($content) {
    /* check for HTML content */
    
    /* update text body value */
    $this->params['TextBody'] = $this->_check_stringEncoding($content);
  }
  
  /*
   * set HTML body
   * @param string $content
   * @return void
   * @access public
   */
  function set_HTMLBody($content) {
    /* update HTML body value */
    $this->params['HTMLBody'] = $content;
  }
  
  /*
   * build HTML body
   * @param string $content
   * @param string $cssPath
   * @return void
   * @access public
   */
  function build_HTMLBody($content, $cssPath=false) {
    global $camyks;
        
    /* load CSS */
    if ($cssPath == false or !file_exists($cssPath))
      $cssPath = $camyks->themes[$camyks->get_confValue('site_default_theme')]->get_filePath('css/email.css');

    /* build HTML page */
    ob_start();
    $page = new HTMLPage();
    if ($cssPath != '')
        $page->add_styleIncludedFile($cssPath);
    $page->add_HTMLHeader();
    if (file_exists($content))
        include $content;
    else
        echo $content;
    $page->add_HTMLFooter();

    $c = ob_get_contents();
    ob_end_clean();
    $this->set_HTMLBody($c);
  }
  
  /*
   * add an attached file
   * @param string $file
   * @return void
   * @access public
   */
  function add_attachment($file) {
    $this->params['Attachments'][] = $file;
  }
  
  /*
   * alias to add_attachment
   * @param string $file
   * @return void
   * @access public
   */
  function attach_file($file) {
    return $this->add_attachment($file);
  }
  
  /*
   * add attached files
   * @param array $files
   * @return void
   * @access public
   */
  function add_attachments($files) {
    $this->params['Attachements'] += $files;
  }
  
  /*
   * alias to add_attachments
   * @param array $files
   * @return void
   * @access public
   */
  function attach_files($files) {
    return $this->add_attachments($files);
  }
  
  /* 
   * add an embed image
   * @param string $img
   * @return void
   * @access public
   */
  function add_embeddedImage($img) {
    $this->params['EmbeddedImages'][] = $img;
  }
  
  /* 
   * alias to add_embeddedImage
   * @param string $img
   * @return void
   * @access public
   */
  function embed_image($img) {
    return $this->add_embeddedImage($img);
  }
  
  /*
   * add embedded images
   * @param array $imgs
   * @return void
   * @access public
   */
  function add_embeddedImages($imgs) {
    $this->params['EmbeddedImages'] += $imgs;
  }
  
  /*
   * alias to add_embeddedImages
   * @param array $files
   * @return void
   * @access public
   */
  function embed_images($imgs) {
    return $this->add_embeddedImages($imgs);
  }
  
  /* public sending methods */
  
  /*
   * send email
   * @return boolean success
   * @access public
   */
  function send() {
    global $camyks;
    
    switch($camyks->get_confValue('email_defaultLibrary')) {
      /* use PHPMailer */
      case 'PHPMailer' : return $this->_send_PHPMailerMail();
      /* use PEAR/Mail */
      case 'PEAR/Mail' : 
      default : return $this->_send_PEARMimeMail();
    }
    
    /* default result */
    return false;
  }
  
  /* public tool methods */
  
  /*
   * return last error 
   * @return string
   * @access public
   */
  function get_lastError() {
    return $this->error;
  }
  
  
  /* private sending methods */
  
  /*
   * send email using PEAR Mime Mail library
   * @return boolean success
   * @access private
   */
  function _send_PEARMimeMail() {
    global $camyks;
    
    @include_once 'Mail.php';
    @include_once 'Mail/mime.php';
    
    /* check PEAR/Mail/Mime library availability */
    if (!class_exists('Mail_mime'))
      return false;
    
    /* build message object */
    $message = new Mail_mime();
    
    /* update message content type when a text body is defined */
    if (count($this->params['Attachments']) > 0 or count($this->params['EmbeddedImages']) > 0) {
      /* let auto content type */
      
    } elseif ($this->params['TextBody'] != '' and $this->params['HTMLBody'] != '')
      $message->setContentType('multipart/alternative');
    elseif ($this->params['HTMLBody'] != '')
      $message->setContentType('text/HTML; charset='.$camyks->get_HTMLencodingvalue());
    elseif ($this->params['TextBody'] != '')
      $message->setContentType('text/plain; charset='.$camyks->get_HTMLencodingvalue());
    
    /* build header list */
    $headers = $this->params['Headers'];
    $headers['MIME-Version'] = $this->params['MIME-Version'];
    if( $this->params['Return-Path'] != '' )
      $headers['Return-Path'] = $this->params['Return-Path'];
    $headers['Date'] = date('r');
    
    /* add sender */
    if ($this->params['From']['name'] != '')
      $headers['From'] = $this->params['From']['name'].' <'.$this->params['From']['email'].'>';
    else
      $headers['From'] = $this->params['From']['email'];
    
    /* add reply-to list to header */
    $rto = array();
    foreach ($this->params['ReplyTo'] as $contact) {
        if ($contact['email'] == '')
          continue;
          
        if ($contact['name'] != '')
            $rto[] = $contact['name']. ' <'.$contact['email'].'>';
        else
            $rto[] = $contact['email'];
    }
    $headers['Reply-To'] = implode(', ', $rto);

    /* add normal recipient list to header */
    $to = array();
    foreach ($this->params['To'] as $contact) {
        if ($contact['email'] == '')
          continue;
          
        if ($contact['name'] != '')
            $to[] = $contact['name']. ' <'.$contact['email'].'>';
        else
            $to[] = $contact['email'];
    }
    if (count($to) == 0) {
      $this->error = 'No valid recipient.';
      return false;
    }
    $headers['To'] = implode(', ', $to);
    
    /* add cc recipient list to header */
    $cc = array();
    foreach ($this->params['Cc'] as $contact) {
        if ($contact['email'] == '')
          continue;
          
        if ($contact['name'] != '')
            $cc[] = $contact['name'].' <'.$contact['email'].'>';
        else
            $cc[] = $contact['email'];
    }
    $headers['Cc'] = implode(', ', $cc);
    
    /* add cc recipient list to header */
    $bcc = array();
    foreach ($this->params['Bcc'] as $contact) {
        if ($contact['email'] == '')
          continue;
          
        if ($contact['name'] != '')
            $bcc[] = $contact['name'].' <'.$contact['email'].'>';
        else
            $bcc[] = $contact['email'];
    }
    $headers['Bcc'] = implode(', ', $bcc);
    
    /* add subject to header */
    $headers['Subject'] = $this->params['Subject'];
    
    /* build body */
    if ($this->params['HTMLBody'] != '') $message->setHTMLBody($this->params['HTMLBody']);
    if ($this->params['TextBody'] != '') $message->setTXTBody($this->params['TextBody']);
    
    /* add attachments */
	foreach($this->params['Attachments'] as $a)
	  $message->addAttachment($a);

    /* add embedded images */
    foreach($this->params['EmbeddedImages'] as $img)
	  $message->addHTMLImage($img);
    
    /* build recipient list */
    $recipients = array();
    foreach ($this->params['To'] as $contact)
      if ($contact['email'] != '') $recipients[] = $contact['email'];
    foreach ($this->params['Cc'] as $contact)
      if ($contact['email'] != '') $recipients[] = $contact['email'];
    foreach ($this->params['Bcc'] as $contact)
      if ($contact['email'] != '') $recipients[] = $contact['email'];
    $recipients = implode(', ', $recipients);
    
    /* send email with configured driver & settings */
    if ( $camyks->get_confValue('PEARMailDriver') !== '' ) {
      if ( is_array($camyks->get_confValue('PEARMailConfig')) ) {
        $myMail = Mail::Factory($camyks->get_confValue('PEARMailDriver'), $camyks->get_confValue('PEARMailConfig'));
      } else {
        $myMail = Mail::Factory($camyks->get_confValue('PEARMailDriver'));
      }
    } else {
      $myMail = Mail::Factory('mail');
    }
    
    /* send mail */
    $result = $myMail->send($recipients, $message->headers($headers), $message->get());
    if (PEAR::isError($result)) {
        $this->error = $result->getMessage();
        return false;
    }
    return true;
  }
  
  /*
   * send email using PHPMailler library
   * @return boolean success
   * @access private
   */
  function _send_PHPMailerMail() {
    global $camyks;
    
    @include_once 'PHPMailer/PHPMailerAutoload.php';
    
    /* check PEAR/Mail/Mime library availability */
    if (!class_exists('PHPMailer'))
      return false;
    
    /* build message object */
    $mail = new PHPMailer;
    
    /* check config */
    if ( $camyks->get_confValue('PEARMailDriver') == 'smtp' ) {
      $mail->isSMTP();
    
      if (is_array($camyks->get_confValue('PEARMailConfig'))) {
        $config = $camyks->get_confValue('PEARMailConfig');
        if (isset($config['host'])) $mail->Host = $config['host'];
        if (isset($config['port'])) $mail->Port = $config['port'];
        if (isset($config['secure'])) $mail->SMTPSecure = $config['secure'];
        if (isset($config['auth'])) $mail->SMTPAuth = $config['auth'];
        if (isset($config['username'])) $mail->Username = $config['username'];
        if (isset($config['password'])) $mail->Password = $config['password'];
      }
    }
    
    /* add sender */
     if ($this->params['From']['name'] != '')
      $mail->setFrom($this->params['From']['email'], $this->params['From']['name']);
    else
      $mail->setFrom($this->params['From']['email']);
    
    /* add recipients */    
    $to = array();
    foreach ($this->params['To'] as $contact) {
      if ($contact['email'] == '')
        continue;
          
      if ($contact['name'] != '')
        $mail->addAddress($contact['email'], $contact['name']);
      else
        $mail->addAddress($contact['email']);
    }
    
    /* add reply to */
    foreach ($this->params['ReplyTo'] as $contact) {
      if ($contact['email'] == '')
        continue;
          
      if ($contact['name'] != '')
        $mail->addReplyTo($contact['email'], $contact['name']);
      else
        $mail->addReplyTo($contact['email']);
    }
    
    /* add cc recipients */
    foreach ($this->params['Cc'] as $contact) {
      if ($contact['email'] == '')
        continue;
          
      if ($contact['name'] != '')
        $mail->addCC($contact['email'], $contact['name']);
      else
        $mail->addCC($contact['email']);
    }
    
    /* add bcc recipients */
    foreach ($this->params['Bcc'] as $contact) {
      if ($contact['email'] == '')
        continue;
          
      if ($contact['name'] != '')
        $mail->addBCC($contact['email'], $contact['name']);
      else
        $mail->addBCC($contact['email']);
    }
    
    /* define the subject line */
    $mail->Subject = $this->params['Subject'];
    
    /* add attachments */
	foreach($this->params['Attachments'] as $a) {
	  $mail->addAttachment($a);
	}

    /* add embedded images */
    $cnt = 0;
    foreach($this->params['EmbeddedImages'] as $img) {
	  $mail->AddEmbeddedImage($img, 'picture'.$cnt);
	  $this->params['HTMLBody'] = str_replace ($img, 'cid:picture'.$cnt, $this->params['HTMLBody']);
	  $cnt ++;
	}
    
    /* define content */
    $mail->msgHTML($this->params['HTMLBody'], dirname(__FILE__));
    
    /* send email */
    if (!$mail->send()) {
      $this->error = $mail->ErrorInfo;
      return false;
    }
    return true;
  }
  
  /* private tool methods */
  
  /*
   * check text encoding
   * @param string $string
   * @return string
   * @access private
   */
  function _check_stringEncoding($string) {
    if (string_isUTF8($string))
      return utf8_decode($string);
    return $string;
  }
}
?>