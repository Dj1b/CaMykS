<?php
/**
 * @brief E-mail generic object
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2012
 * @date Modification: Oct 2021
 * @copyright 2012 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CMail class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class CMail {
    /**
     * @var array $params
     * @brief Parameters list.
     */
    public $params = array();

    /**
     * @var string $error
     * @brief Last error.
     */
    private $error = '';

    /**
     * Class constructor.
     * @return void
    */
    public function __construct() {
        $this->initialise();
    }

    /* public methods */

    /**
     * Initialise object.
     * @return void
     */
    public function initialise() {
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

    /**
     * Set mime version.
     * @param string $mime
     * @return void
     */
    public function set_mimeVersion($mime) {
        $this->params['MIME-Version'] = $mime;
    }

    /**
     * Set content type.
     * @param string $type
     * @return void
     */
    public function set_contentType($type) {
        $this->params['Content-Type'] = $type;
    }

    /**
     * Set return path.
     * @param string $email
     * @return void
     */
    public function set_returnPath($email) {
        $this->params['Return-Path'] = $email;
    }

    /**
     * Add suppl. header.
     * @param string $name
     * @param string $value
     * @return void
     */
    public function add_header($name, $value) {
        $this->params['Headers'][$name] = $value;
    }

    /**
     * Set sender.
     * @param string $email
     * @param string $name
     * @return void
     */
    public function set_sender($email, $name='') {
        $this->params['From'] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
    }

    /**
     * Add reply-to.
     * @param string $email
     * @param string $name
     * @return void
     */
    public function add_replyTo($email, $name='') {
        $this->params['ReplyTo'][] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
    }

    /**
     * Add normal recipient.
     * @param string $email
     * @param string $name
     * @return void
     */
    public function add_recipient($email, $name='') {
        $this->params['To'][] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
    }

    /**
     * Add Cc recipient.
     * @param string $email
     * @param string $name
     * @return void
     */
    public function add_ccRecipient($email, $name='') {
        $this->params['Cc'][] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
    }

    /**
     * Add Bcc recipient.
     * @param string $email
     * @param string $name
     * @return void
     */
    public function add_bccRecipient($email, $name='') {
        $this->params['Bcc'][] = array('email'=>$email, 'name'=>$this->_check_stringEncoding($name));
    }

    /* public body & subject management methods */

    /**
     * Set subject value.
     * @param string $subject
     * @return void
     */
    public function set_subject($subject) {
        /* update subject value */
        $this->params['Subject'] = $this->_check_stringEncoding($subject);
    }

    /**
     * Set text body.
     * @param string $content
     * @return void
     */
    function set_textBody($content) {
        /* update text body value */
        $this->params['TextBody'] = $this->_check_stringEncoding($content);
    }

    /**
     * Set HTML body.
     * @param string $content
     * @return void
     */
    public function set_HTMLBody($content) {
        /* update HTML body value */
        $this->params['HTMLBody'] = $content;
    }

    /**
     * Build HTML body.
     * @param string $content
     * @param string $cssPath
     * @return void
     */
    public function build_HTMLBody($content, $cssPath=false) {
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

    /**
     * Add an attached file.
     * @param string $file
     * @return void
     */
    public function add_attachment($file) {
        $this->params['Attachments'][] = $file;
    }

    /**
     * Alias to add_attachment.
     * @see add_attachment()
     * @param string $file
     * @return void
     */
    public function attach_file($file) {
        return $this->add_attachment($file);
    }

    /**
     * Add attached files.
     * @param array $files
     * @return void
     */
    public function add_attachments($files) {
        $this->params['Attachements'] += $files;
    }

    /**
     * Alias to add_attachments.
     * @see add_attachments()
     * @param array $files
     * @return void
     */
    public function attach_files($files) {
        return $this->add_attachments($files);
    }

    /**
     * Add an embed image.
     * @param string $img
     * @return void
     */
    public function add_embeddedImage($img) {
        $this->params['EmbeddedImages'][] = $img;
    }

    /**
     * Alias to add_embeddedImage.
     * @see add_embeddedImage()
     * @param string $img
     * @return void
     */
    public function embed_image($img) {
        return $this->add_embeddedImage($img);
    }

    /**
     * Add embedded images.
     * @param array $imgs
     * @return void
     */
    public function add_embeddedImages($imgs) {
        $this->params['EmbeddedImages'] += $imgs;
    }

    /**
     * Alias to add_embeddedImages.
     * @see add_embeddedImages()
     * @param array $imgs
     * @return void
     */
    public function embed_images($imgs) {
        return $this->add_embeddedImages($imgs);
    }

    /* public sending methods */

    /**
     * Send email.
     * @return boolean success
     */
    public function send() {
        global $camyks;

        switch ($camyks->get_confValue('email_defaultLibrary')) {
            /* use PHPMailer */
            case 'PHPMailer' :
                $success = $this->_send_PHPMailerMail();
                break;
            /* use PEAR/Mail */
            case 'PEAR/Mail' :
            default :
                $success = $this->_send_PEARMimeMail();
        }

        /* directly return result if logs are not available */
        if ($camyks->are_logsAvailable() === false)
          return $success;

        /* prepare recipients */
        $recipients = $this->get_contactListAsString('To', '(');

        /* log success */
        if ($success) {
            $camyks->log('Emails', 'Send to '.$recipients, 'Success');
            return true;
        }

        /* log failure */
        $camyks->log('Emails', 'Send to '.$recipients, 'Failure: '.$this->get_lastError());
        return false;
    }

    /* public tool methods */

    /**
     * Return last error.
     * @return string
     */
    public function get_lastError() {
        return $this->error;
    }

    /**
     * Return contact list as string
     * @param string $list
     * @param string $container
     * @param string $separator
     * @return string
     */
    public function get_contactListAsString($list='To', $container='<', $separator=', ') {
        /* build containers */
        $containers = array(
            '<' => '>',
            '(' => ')',
            '{' => '}',
            '[' => ']',
        );

        /* check list */
        if (!in_array($list, array('To', 'Cc', 'Bcc', 'ReplyTo')))
            return '';

        /* build contact list */
        $contacts = array();
        foreach ($this->params[$list] as $contact) {
            if ($contact['email'] == '')
                continue;

            if ($contact['name'] != '')
                $contacts[] = $contact['name'].' '.$container.$contact['email'].(isset($containers[$container])?$containers[$container]:$container);
            else
                $contacts[] = $contact['email'];
        }

        /* check contacts count */
        if (count($contacts) == 0)
            return '';

        /* return compiled result */
        return implode($separator, $contacts);
    }

    /* private sending methods */

    /**
     * send email using PEAR Mime Mail library
     * @return boolean success
     */
    private function _send_PEARMimeMail() {
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
            $message->setContentType('text/HTML; charset='.$camyks->get_HTMLEncodingValue());
        elseif ($this->params['TextBody'] != '')
            $message->setContentType('text/plain; charset='.$camyks->get_HTMLEncodingValue());

        /* build header list */
        $headers = $this->params['Headers'];
        $headers['MIME-Version'] = $this->params['MIME-Version'];
        if ($this->params['Return-Path'] != '')
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
                $rto[] = $contact['name'].' <'.$contact['email'].'>';
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
                $to[] = $contact['name'].' <'.$contact['email'].'>';
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
        if ($camyks->get_confValue('PEARMailDriver') !== '') {
            if (is_array($camyks->get_confValue('PEARMailConfig'))) {
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

    /**
     * send email using PHPMailler library
     * @return boolean success
     */
    private function _send_PHPMailerMail() {
        global $camyks;

        @include_once 'PHPMailer/PHPMailerAutoload.php';

        /* check PEAR/Mail/Mime library availability */
        if (!class_exists('PHPMailer'))
            return false;

        /* build message object */
        $mail = new PHPMailer;

        /* check config */
        if ($camyks->get_confValue('PEARMailDriver') == 'smtp') {
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

    /**
     * Check text encoding.
     * @param string $string
     * @return string
     */
    private function _check_stringEncoding($string) {
        if (string_isUTF8($string))
            return utf8_decode($string);
        return $string;
    }
}
?>
