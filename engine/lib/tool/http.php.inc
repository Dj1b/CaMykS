<?php
/**
 * @brief HTTP specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4.2
 * @date Creation: Jul 2017
 * @date Modification: Feb 2022
 * @copyright 2017 - 2022 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Return HTTP response code list.
 * @return array
 */
function http_getResponseCodeList() {
    return array(
        /* 1xx - Information */
        100 => 'Continue',
        101 => 'Switching Protocols',
        102 => 'Processing',
        103 => 'Early Hints',

        /* 2xx - Success */
        200 => 'OK',
        201 => 'Created',
        202 => 'Accepted',
        203 => 'Non-Authoritative Information',
        204 => 'No Content',
        205 => 'Reset Content',
        206 => 'Partial Content',
        207 => 'Multi-Status',
        208 => 'Already Reported',
        210 => 'Content Different',
        226 => 'IM Used',

        /* 3xx - Redirection */
        300 => 'Multiple Choices',
        301 => 'Moved Permanently',
        302 => 'Found',
        303 => 'See Other',
        304 => 'Not Modified',
        305 => 'Use Proxy',
        306 => 'Switch Proxy',
        307 => 'Temporary Redirect',
        308 => 'Permanent Redirect',
        310 => 'Too many Redirects',

        /* 4xx - Request error */
        400 => 'Bad Request',
        401 => 'Unauthorized',
        402 => 'Payment Required',
        403 => 'Forbidden',
        404 => 'Not Found',
        405 => 'Method Not Allowed',
        406 => 'Not Acceptable',
        407 => 'Proxy Authentication Required',
        408 => 'Request Time-out',
        409 => 'Conflict',
        410 => 'Gone',
        411 => 'Length Required',
        412 => 'Precondition Failed',
        413 => 'Request Entity Too Large',
        414 => 'Request-URI Too Long',
        415 => 'Unsupported Media Type',
        416 => 'Requested range unsatisfiable',
        417 => 'Expectation failed',
        418 => 'I’m a teapot',
        421 => 'Bad mapping / Misdirected Request',
        422 => 'Unprocessable entity',
        423 => 'Locked',
        424 => 'Method failure',
        425 => 'Unordered Collection',
        426 => 'Upgrade Required',
        428 => 'Precondition Required',
        429 => 'Too Many Requests',
        431 => 'Request Header Fields Too Large',
        449 => 'Retry With',
        450 => 'Blocked by Windows Parental Controls',
        451 => 'Unavailable For Legal Reasons',
        456 => 'Unrecoverable Error',

        /* 5xx - Server/Application error */
        500 => 'Internal Server Error',
        501 => 'Not Implemented',
        502 => 'Bad Gateway ou Proxy Error',
        503 => 'Service Unavailable',
        504 => 'Gateway Time-out',
        505 => 'HTTP Version not supported',
        506 => 'Variant Also Negotiates',
        507 => 'Insufficient storage',
        508 => 'Loop detected',
        509 => 'Bandwidth Limit Exceeded',
        510 => 'Not extended',
        511 => 'Network authentication required',
    );
}

/**
 * Return contents over HTTP.
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e string url <br />
 * \e string engine - \b php / \b curl <br />
 * \e string method - \b GET / \b POST <br />
 * \e mixed values <br />
 * \e boolean SSL_VerifyPeer <br />
 * \e string user_agent <br />
 * \e string referer <br />
 * \e integer timeout <br />
 * \e mixed headers <br />
 * \e array ssl <br />
 * @endparblock
 * @return string
 */
function http_getContents($params=array()) {
    global $camyks;

    /* Build params list */
    $defaultParams = array(
        'url'               => '',
        'engine'            => 'php', // php | curl
        'method'            => 'GET', // GET | POST
        'values'            => array(), // fields
        'SSL_VerifyPeer'    => true,
        'user_agent'        => $camyks->get_confValue('UserAgent'),
        'referer'           => '',
        'timeout'           => 60,
        'headers'           => array('Content-type' => 'application/x-www-form-urlencoded'),
        'ssl'               => array(),
    );
    $params = array_merge($defaultParams, $params);

    /* Check cURL engine */
    if ($params['engine'] == 'curl' and !extension_loaded('curl'))
        $params['engine'] = 'php';

    /* Check engine to use */
    if ($params['engine'] == 'curl')
        return http_getContentsUsingCURL($params);
    return http_getContentsUsingPHP($params);
}

/**
 * Return contents over HTTP using php functions.
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e string url <br />
 * \e string method - \b GET / \b POST <br />
 * \e mixed values <br />
 * \e boolean SSLVerifyPeer <br />
 * \e string user_agent <br />
 * \e string referer <br />
 * \e integer timeout <br />
 * \e mixed headers <br />
 * \e array ssl <br />
 * @endparblock
 * @return false on failure, string on success
 */
function http_getContentsUsingPHP($params=array()) {
    global $camyks;

    /* Build params list */
    $defaultParams = array(
        'url'           => '',
        'method'        => 'GET', // GET | POST
        'values'        => array(), // fields
        'SSL_VerifyPeer'=> true,
        'user_agent'    => $camyks->get_confValue('UserAgent'),
        'referer'       => '',
        'timeout'       => 60,
        'headers'       => array('Content-type' => 'application/x-www-form-urlencoded'),
        'ssl'           => array(),
    );
    $params = array_merge($defaultParams, $params);

    /* Move referer to headers */
    if ($params['referer'] !== '')
        $params['headers']['Referer'] = $params['referer'];

    /* Build header */
    if (is_string($params['headers']))
        $header = $params['headers'];
    elseif (is_array($params['headers'])) {
        $header = '';
        foreach ($params['headers'] as $name => $value)
            $header = $name.":".$value."\r\n";
    }

    /* Build context */
    $opts = array(
        'http' => array(
            'header'        => $header,
            'method'        => $params['method'],
            'user_agent'    => $params['user_agent'],
            'timeout'       => $params['timeout'],
        ),
    );

    /* Check SSL peer verification */
    if ($params['SSL_VerifyPeer'] === false) {
        $opts['ssl'] = array(
            'verify_peer'       => false,
            'verify_peer_name'  => false,
        );
    }

    /* Check other SSL parameters */
    if (count($params['ssl']) > 0) {
        if (isset($opts['ssl']))
            $opts['ssl'] = array_merge($opts['ssl'], $params['ssl']);
        else
            $opts['ssl'] = $params['ssl'];
    }

    /* Add values to context */
    if (is_array($params['values']) and count($params['values']) > 0) {
        $data = http_build_query($params['values']);
        $opts['http']['content'] = $data;
    } elseif (is_string($params['values']) and $params['values'] !== '')
        $opts['http']['content'] = $params['values'];

    /* Create context */
    $context  = stream_context_create($opts);

    /* Execute request */
    return @file_get_contents($params['url'], false, $context);
}

/**
 * Return contents over HTTP using CURL functions.
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e string url <br />
 * \e string method - \b GET / \b POST <br />
 * \e mixed values <br />
 * \e boolean SSL_VerifyPeer <br />
 * \e string user_agent <br />
 * \e string referer <br />
 * \e integer timeout <br />
 * \e mixed headers <br />
 * \e array ssl <br />
 * @endparblock
 * @return false on failure, string on success
 */
function http_getContentsUsingCURL($params=array()) {
    global $camyks;

    /* Build params list */
    $defaultParams = array(
        'url'               => '',
        'method'            => 'GET', // GET | POST
        'values'            => array(), // fields
        'SSL_VerifyPeer'    => true,
        'user_agent'        => $camyks->get_confValue('UserAgent'),
        'referer'           => '',
        'timeout'           => 60,
        'headers'           => array('Content-type' => 'application/x-www-form-urlencoded'),
        'ssl'               => array(),
    );
    $params = array_merge($defaultParams, $params);

    /* Build header */
    $header = array();
    if (is_string($params['headers']))
        $header[] = array($params['headers']);
    elseif (is_array($params['headers'])) {
        foreach ($params['headers'] as $name => $value)
            $header[] = $name.":".$value;
    }

    /* Build request */
    $request = curl_init();
    curl_setopt($request, CURLOPT_URL, $params['url']);
    curl_setopt($request, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($request, CURLOPT_FOLLOWLOCATION, true);
    curl_setopt($request, CURLOPT_POST, $params['method']=='POST' ? 1 : 0);
    curl_setopt($request, CURLOPT_POSTFIELDS, $params['values']);
    curl_setopt($request, CURLOPT_SSL_VERIFYPEER, $params['SSL_VerifyPeer']);
    if (isset($params['ssl']['ciphers']))
        curl_setopt($request, CURLOPT_SSL_CIPHER_LIST, $params['ssl']['ciphers']);
    if ($params['timeout'] > 0)
        curl_setopt($request, CURLOPT_TIMEOUT, $params['timeout']);
    if ($params['user_agent'] != '')
        curl_setopt($request, CURLOPT_USERAGENT, $params['user_agent']);
    if ($params['referer'] === true)
        curl_setopt($request, CURLOPT_AUTOREFERER, true);
    elseif ($params['referer'] != '')
        curl_setopt($request, CURLOPT_REFERER, $params['referer']);
    if (count($header) > 0)
        curl_setopt($request, CURLOPT_HTTPHEADER, $header);

    /* Execute request */
    return @curl_exec($request);
}
?>
