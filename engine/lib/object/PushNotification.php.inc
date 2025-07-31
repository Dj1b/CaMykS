<?php
/**
 * @brief Push Notification library.
 * @details Engine / Object Library
 * @file engine/lib/object/PushNotification.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jun 2017
 * @date Modification: Jul 2025
 * @copyright 2017 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 * @warning Windows phone method currently not tested
 * @details Device plateforms
 * <br /> 0 : Unknown
 * <br /> 1 : Android
 * <br /> 2 : iOS
 * <br /> 3 : Windows Phone
 * <br />
 * <br /> Error codes
 * <br /> 1 : Unknown platform
 * <br /> 2 : Undefined identifier
 * <br /> 3 : Server connection failed
 * <br /> 4 : Message refused
 */

/**
 * PushNotification class.
 */
final class PushNotification {
    /**
     * @var array $params
     * @brief Notification parameters.
     */
    private $params = array(
        /* device data */
        'devicePlatform' => 0,
        'deviceIdentifier' => '',

        /* notification params */
        'title' => '',
        'message' => '',
        'badge' => 0,
        'sound' => 'default',
        'vibrate' => 1,
        'delay' => 2,
        'customActionButton' => '', // customised action button for iOS
        'privateAppData' => array(), // private data to send to the app iOS / Android

        /* Android security key */
        'APIAccessKey' => '',

        /* iOS certificate */
        'mode' => '', // sandbox or empty
        'certificateLocation' => '',
        'certificatePassphrase' => '',
    );

    /**
     * @var integer $_lastError
     * @brief Last error code.
     */
    private $_lastError = 0;

    /**
     * @var string $_lastErrorDetail
     * @brief Last error description.
     */
    private $_lastErrorDetail;

    /**
     * Class constructor.
     * @param array $params
     */
    public function __construct($params=array()) {
        /* compile params list */
        $this->params = array_merge($this->params, $params);
    }

    /**
     * Send notification.
     * @param array $params
     * @return boolean result
     */
    public function send($params=array()) {
        /* compile params */
        $this->params = array_merge($this->params, $params);

        /* auto detect platform */
        /* to do */

        /* send notification through the correct engine */
        switch ($this->params['devicePlatform']) {
            case 1 :
                return $this->send_toAndroidDevice();
            case 2 :
                return $this->send_toIOsDevice();
            case 3 :
                return $this->send_toWindowsPhoneDevice();
        }

        /* no platform found, send as error */
        $this->_define_error(0);
        return false;
    }

    /**
     * Send notification to iOS device.
     * @param array $params
     * @return boolean result
     */
    public function send_toIOsDevice($params=array()) {
        /* compile params */
        $this->params = array_merge($this->params, $params);

        /* create stream context with SSL and Apple certificate */
        $context = stream_context_create();
        stream_context_set_option($context, 'ssl', 'local_cert', $this->params['certificateLocation']);
        stream_context_set_option($context, 'ssl', 'passphrase', $this->params['certificatePassphrase']);

        /* open a connection to the APNS server */
        $connection = stream_socket_client(
            $this->params['mode'] == 'sandbox'?'ssl://gateway.sandbox.push.apple.com:2195':'ssl://gateway.push.apple.com:2195',
            $err,
            $errstr,
            60,
            STREAM_CLIENT_CONNECT|STREAM_CLIENT_PERSISTENT,
            $context
        );

        /* check connection error */
        if (!$connection) {
            $this->_define_error(3, "$err $errstr");
            return false;
        }

        /* build payload body */
        $payload = array_merge(array(
            'aps' => array(
                'alert' => array(
                    'title' => $this->params['title'],
                    'body'  => $this->params['message'],
                ),
                'badge' => $this->params['badge'],
                'sound' => $this->params['sound'],
            ),
        ), $this->params['privateAppData']);

        if ($this->params['customActionButton'] != '')
            $payload['aps']['alert']['action-loc-key'] = $this->params['customActionButton'];
        $payload = json_encode($payload);

        /* build binary notification */
        $notification = chr(0) . pack('n', 32) . pack('H*', $this->params['deviceIdentifier']) . pack('n', strlen($payload)) . $payload;

        /* send notification to the server */
        $success = fwrite($connection, $notification, strlen($notification));

        /* close connection */
        fclose($connection);

        /* return result */
        return $success;
    }

    /**
     * Send notification to Android device.
     * @param array $params
     * @return boolean result
     */
    public function send_toAndroidDevice($params=array()) {
        /* compile params */
        $this->params = array_merge($this->params, $params);

        /* create android connection URL */
        $url = 'https://android.googleapis.com/gcm/send';

        /* build message */
        $message = array(
            'title'         => $this->params['title'],
            'message'       => $this->params['message'],
            'subtitle'      => '',
            'tickerText'    => '',
            'msgcnt'        => 1,
            'vibrate'       => $this->params['vibrate'],
        );

        /* build requet header */
        $headers = array(
            'Authorization: key=' .$this->params['APIAccessKey'],
            'Content-Type: application/json',
        );

        /* build request fields */
        $fields = array(
            'to'    => $this->params['deviceIdentifier'],
        );

        if (count($this->params['privateAppData']) == 0) {
            $fields['data'] = $message;
        } else {
            $fields['notification'] = $message;
            $fields['data'] = $this->params['privateAppData'];
        }

        /* send request */
        $result = $this->_send_usingCurl($url, $headers, json_encode($fields));

        /* check result */
        $result = json_decode($result);
        if ($result->success > 0)
            return true;

        /* set error */
        if (isset($result->results[0]->error))
             $this->_define_error(4, $result->results[0]->error);
        else
            $this->_define_error(4, 'Unknown error');
        return false;
    }

    /**
     * send notification to Windows Phone device
     * @param array $params
     * @return boolean result
     */
    public function send_toWindowsPhoneDevice($params=array()) {
        /* compile params */
        $this->params = array_merge($this->params, $params);

        /* build message xml */
        $msg =  "<"."?xml version=\"1.0\" encoding=\"utf-8\"?".">" .
            "<wp:Notification xmlns:wp=\"WPNotification\">" .
                "<wp:Toast>" .
                    "<wp:Text1>".htmlspecialchars($this->params['title'])."</wp:Text1>" .
                    "<wp:Text2>".htmlspecialchars($this->params['message'])."</wp:Text2>" .
                "</wp:Toast>" .
            "</wp:Notification>";

        /* build headers */
        $headers =  array(
            'Content-Type: text/xml',
            'Accept: application/*',
            'X-WindowsPhone-Target: toast',
            'X-NotificationClass: '.$this->params['delay'],
        );

        /* get response from request */
        $response = $this->_send_usingCurl($this->params['deviceIdentifier'], $headers, $msg);

        /* compile result */
        $result = array();
        foreach (explode("\n", $response) as $line) {
            $tab = explode(":", $line, 2);
            if (count($tab) == 2)
                $result[$tab[0]] = trim($tab[1]);
        }

        /* send result */
        return $result;
    }

    /**
     * Return last error code.
     * @return integer
     */
    public function get_lastErrorCode() {
        return $this->_lastError;
    }

    /**
     * Return last error message.
     * @return string
     */
    public function get_lastErrorMessage() {
        switch ($this->_lastError) {
            case 1 : return 'Unknown platform';
            case 2 : return 'Undefined identifier';
            case 3 : return 'Apple server connection failed : '.$this->_lastErrorDetail;
            case 4 : return 'Message refused : '.$this->_lastErrorDetail;
        }
        return 'Unknown error';
    }

    /* private methods */

    /**
     * Send notification through curl
     * @param string $url
     * @param array $headers
     * @param array $fields
     * @return boolean result
     */
    private function _send_usingCurl($url, $headers, $fields) {
        /* open connection */
        $ch = curl_init();
        if ($url) {
            /* define curl data */
            curl_setopt($ch, CURLOPT_URL, $url);
            curl_setopt($ch, CURLOPT_POST, true);
            curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
            curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

            /*  Disabling SSL Certificate support temporarly */
            curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
            if ($fields) {
                curl_setopt($ch, CURLOPT_POSTFIELDS, $fields);
            }

            /* Execute post */
            $result = curl_exec($ch);
            if ($result === false) {
                $this->_define_error(3, curl_error($ch));
                return false;
            }

            /* Close connection */
            curl_close($ch);

            /* return result */
            return $result;
        }

        $this->_define_error(3, 'No URL defined');
        return false;
    }

    /**
     * Define last error.
     * @param integer $error
     * @param string $detail
     * @return void
     */
    private function _define_error($error=0, $detail='') {
        $this->_lastError = $error;
        $this->_lastErrorDetail = $detail;
    }
}
?>
