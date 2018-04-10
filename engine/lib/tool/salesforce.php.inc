<?php
/**
 * @brief Salesforce (http://www.salesforce.com) tools
 * @details Engine / Tool Library
 * @file engine/lib/tool/salesforce.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2010
 * @date Modification: Apr 2018
 * @copyright 2010 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Submit web-to-lead request.
 * @param array $params
 * @return boolean success
 */
function salesforce_submitWeb2Lead($params=array()) {
    /* check if request method exists */
    if (!function_exists('http_build_query'))
        return false;
    
    /* check if organization id is given */
    if (!isset($params['oid']))
        return false;
    
    /* compile params */
    if (version_compare(phpversion(), '5.1.2') == 1)
        $params = http_build_query($params, null, '&');
    else
        $params = http_build_query($params);    
    
    /* build headers */
    $headers = 'Content-Type: application/x-www-form-urlencoded'."\r\n";
    $headers .= 'Content-Length: '.strlen($params)."\r\n";
    
    /* build context */
    $options = array(
        'http'  =>array(
            'user_agent'    => $_SERVER['HTTP_USER_AGENT'],
            'method'        => 'POST',
            'content'       => $params,
            'header'        => $headers,
        )
    );
        
    /* init request */
    $context = stream_context_create($options);
    
    /* send request */
    return file_get_contents('http://www.salesforce.com/servlet/servlet.WebToLead', false, $context);  
}
?>