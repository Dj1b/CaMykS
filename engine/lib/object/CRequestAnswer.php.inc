<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Engine / Object
 * Creation Date    : Jun 2011
 * Last Modif Date  : Nov 2017
 *
 * Request Answer generic object
 */

final class CRequestAnswer {
  /* define variables */
  private $params;

  /*
   * object constructor
   * @param array $params
   * @return void
   * @access public
   */
  public function __construct($params=array()) {
    /* build default param list */
    $defaultParams = array(
    	/* Answer status : success / failure ( / fail ) */
    	'status'=>'',
    	/* Parent module or module library */
    	'parent'=>'',
    	/* Executed action resulting this answer */
    	'action'=>'',
    	/* Result message, for success or failure */
    	'message'=>'',
    	/* Failure error code */
    	'error'=>'',
    	/* Request file */
    	'file'=>'',
    	/* Request line */
    	'line'=>0,
    	);
    	
    /* build object param list */
    $this->params = array_merge($defaultParams, $params);
  }

  /* public methods */
  
  /*
   * return param
   * @param string $param
   * @return mixed
   * @access public
   */
  public function get_param($param='') {
    if (isset($this->params[$param]))
      return $this->params[$param];
    return false;
  }
  
  /*
   * update params 
   * @param array $params
   * @return void
   * @access public
   */
  public function update_params($params=array()) {
  	$this->params = array_merge($this->params, $params);
  }
  
  /*
   * update param
   * @param string $name
   * @param mixed $value
   * @return void
   * @access public
   */
  public function update_param($name, $value) {
  	$this->params[$name] = $value;
  }
  
  /*
   * set answer as success
   * @param string $msg
   * @return void
   * @access public
   */
  public function set_asSuccess($msg='') {
  	$this->params['status'] = 'success';
  	if ($msg != '')
  	    $this->params['message'] = $msg;
  }
  
  /*
   * set answer as failure
   * @param string $msg
   * @param string $error
   * @return void
   * @access public
   */
  public function set_asFailure($msg='', $error='') {
  	$this->params['status'] = 'failure';
  	if ($msg != '')
  	    $this->params['message'] = $msg;
  	if ($error != '')
  	    $this->params['error'] = $error;
  }
  
  /*
   * return is request a success
   * @return boolean result
   * @access public
   */
  public function is_success() {
  	return ($this->params['status'] == 'success');
  }
  
  /*
   * return is request a failure
   * @return boolean result
   * @access public
   */
  public function is_failure() {
  	return (in_array($this->params['status'], array('failure', 'fail')));
  }
  
  /*
   * throw fatal error for failure
   * @return void
   * @access public
   */
  public function throw_fatalError() {
  	global $camyks;
  
  	/* check if answer is a failure */
  	if ($this->is_failure() === false)
  		return;
  		
  	/* build error */
    $error = array();
    
    /* check for error title */
    if ($this->params['parent'] != '') {
    	if (is_string($this->params['parent']))
    		$error['title'] = $this->params['parent'];
    	elseif (is_object($this->params['parent']) and isset($this->params['parent']->object_type)) {
    		if ($this->params['parent']->object_type == 'ModuleLibrary')
    			$error['title'] = $this->params['parent']->_libParent->title;
    		elseif (isset($this->params['parent']->title))
    			$error['title'] = $this->params['parent']->title;
    	}
    }

	/* check for description & content */
	if (is_string($this->params['message'])) {
		$error['description'] = $this->params['message'];
	} else {
		$error['description'] = $this->params['message'][0];
		for ($i=1; $i<count($this->params['message']); $i++)
			$error['content'.$i] = $this->params['message'][0];
	}
		
	/* throw fatal error */
    $camyks->throwFatalError($error);
  }
  
  /*
   * log error for failure
   * @return void
   * @access public
   */
  public function log_error() {
  	global $camyks;
  	
  	/* check parent */
  	if (!is_object($this->params['parent']))
  		return;
  	
  	/* check description & content */
	if (is_string($this->params['message'])) {
		$msg1 = $this->params['message'];
	} else {
		$msg1 = implode('<br />', $this->params['message']);
	}
		
	/* check error  */
  	if ( $this->params['error'] != '') {
  	    $msg2 = $msg1;
  		$msg1 = $this->params['error'];
  	} else {
  		$msg2 = '';
  	}
  	
  	/* send error */
  	$camyks->log_internalerror($this->params['parent'], $msg1, $msg2, $this->params['file'], $this->params['line']);
  }
  
  /*
   * send object data as XML (for ajax request)
   * @param array $params
   * @return void
   * @access public
   */
  public function send_asXML($params=array()) {
  	/* check for new params */
  	if (count($params) > 0)
  		$this->update_params($params);
  
  	/* unset private server-side vars */
  	unset($this->params['parent']);
  	unset($this->params['file']);
  	unset($this->params['line']);
  
  	/* send XML */
  	header("Content-type: text/xml");
    die(xml_serialize2XML($this->params));
  }
  
  /*
   * send object data as JSON (for ajax request)
   * @param array $params
   * @return void
   * @access public
   */
  public function send_asJSON($params=array()) {
  	/* check for new params */
  	if (count($params) > 0)
  		$this->update_params($params);
  
  	/* unset private server-side vars */
  	unset($this->params['parent']);
  	unset($this->params['file']);
  	unset($this->params['line']);
  
    /* ensure that data are correctly handled by PHP json method */
    setLocale(LC_NUMERIC, 'en_US.utf8');
  
  	/* send XML */
  	header("Content-Type: text/javascript; charset=utf8");
    die(json_encode($this->params));
  }
}
?>