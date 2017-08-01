<?php
/*
 * CaMykS Engine
 * Developed by       : camyks.net
 * Author             : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version     : 1.0
 * Object Version     : 1.0
 * Object Type        : Engine / Tool Library
 * Creation Date      : Jul 2017
 * Last Modif Date    : Jul 2017
 *
 * HTTP methods
 */

/*
 * get contents over HTTP
 * @param array $params
 * @return string
 * @access public
 */
function http_getContents($params=array()) {
  global $camyks;
  
  /* build params list */
  $defaultParams = array(
  	'url'               => '', 
  	'engine'            => 'php', // php | curl 
  	'method'            => 'GET', // GET | POST
  	'values'            => array(), // fields 
  	'SSL_VerifyPeer'    => true, // curl
  	'user_agent'        => $camyks->get_confValue('UserAgent'),
    'referer'           => '',
    'timeout'           => 60,
  );
  $params = array_merge($defaultParams, $params);
  
  /* check curl engine */
  if ($params['engine'] == 'curl' and !function_exists('curl_init'))
    $params['engine'] = 'php';
  
  /* get context using the indicated engine */
  if ($params['engine'] == 'curl')
    return http_getContentsUsingCURL($params);
  return http_getContentsUsingPHP($params);
}

/*
 * get contents over HTTP using php functions
 * @param array $params
 * @return false on failure, string on success
 * @access public
 */
function http_getContentsUsingPHP($params=array()) {
  global $camyks;
  
  /* build params list */
  $defaultParams = array(
  	'url'           => '', 
  	'method'        => 'GET', // GET | POST
  	'values'        => array(), // fields
  	'user_agent'    => $camyks->get_confValue('UserAgent'),
    'referer'       => '',
    'timeout'       => 60,
  );
  $params = array_merge($defaultParams, $params);
  
  /* build context */
  $opts = array(
  		'http' => array(
    		'header'        => 'Content-type: application/x-www-form-urlencoded',
    		'method'        => $params['method'],
    		'user_agent'    => $params['user_agent'],
    		'referer'       => $params['referer'],
    		'timeout'       => $params['timeout'],
  		),
  );
  
  /* add fields values to context */
  if (count($params['values']) > 0) {
    $data = http_build_query($params['values']);
	$opts['http']['content'] = $data;
  }

  /* get contents */
  $context  = stream_context_create($opts);
  return @file_get_contents($params['url'], false, $context);
}

/* 
 * get contents over HTTP using CURL functions
 * @param array $params
 * @return false on failure, string on success
 * @access public
 */
function http_getContentsUsingCURL($params=array()) {
  global $camyks;
  
  /* build params list */
  $defaultParams = array(
  	'url'               => '', 
  	'method'            => 'GET', // GET | POST
  	'values'            => array(), // fields 
  	'SSL_VerifyPeer'    => true, // curl 
  	'user_agent'        => $camyks->get_confValue('UserAgent'),
    'referer'           => '',
    'timeout'           => 60,
  );
  $params = array_merge($defaultParams, $params);
  
  /* build request */
  $request = curl_init();
  curl_setopt($request, CURLOPT_URL, $params['url']);
  curl_setopt($request, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($request, CURLOPT_FOLLOWLOCATION, true);
  curl_setopt($request, CURLOPT_POST, $params['method']=='POST' ? 1 : 0);
  curl_setopt($request, CURLOPT_POSTFIELDS, $params['values']);
  curl_setopt($request, CURLOPT_SSL_VERIFYPEER, $params['SSL_VerifyPeer']);
  if ($params['timeout'] > 0)
    curl_setopt($request, CURLOPT_TIMEOUT, $params['timeout']);
  if ($params['user_agent'] != '')
    curl_setopt($request, CURLOPT_USERAGENT, $params['user_agent']);
  if ($params['referer'] === true)
    curl_setopt($request, CURLOPT_AUTOREFERER, true);
  elseif ($params['referer'] != '')
    curl_setopt($request, CURLOPT_REFERER, $params['referer']);
  
  /* execute request */
  return @curl_exec($request);
}
?>