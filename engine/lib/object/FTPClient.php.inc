<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Engine / Object
 * Creation Date    : Mar 2018
 * Last Modif Date  : Mar 2018
 *
 * FTP Client Object
 */

final class FTPClient {

  /* define variables */
  private $connection;

  /*
   * object constructor
   * @param array $params
   * @return void
   * @access public
   */
  public function __construct() {
    $this->connection = null;
  }
  
  /* 
   * object destructor
   * @return void
   * @access public
   */
  public function __destruct() {
    if ($this->connection !== null)
      $this->close();
  }
  
  /*
   * use of magic method to catch all ftp commands from php
   * @param string $method
   * @param array $arguments
   * @return mixed
   */
  public function __call($method, $arguments) {
    /* add php method prefix */
    $function = 'ftp_' . $method;
    if (function_exists($function)) {
      /* adds connection as first argument */
      array_unshift($arguments, $this->connection);
      
      /* execute function */
      return call_user_func_array($function, $arguments);
    }
    
    /* php function doesn't exist, return false */
    return false;
  }
  
  /*
   * explicitly define connect method to get connection object
   * @param string $host
   * @param boolean $ssl
   * @param integer $port
   * @param integer $timeout
   * @return boolean success
   */
  public function connect($host, $ssl=false, $port=21, $timeout=60) {
    /* check if ftp is available */
    if (!extension_loaded('ftp'))
      return false;
  
    if ($ssl) {
        $this->connection = ftp_ssl_connect($host, $port, $timeout);
    } else {
        $this->connection = ftp_connect($host, $port, $timeout);
    }
    return ($this->connection !== false);
  }
  
  /*
   * explicitly define ssl_connect method
   * @param string $host
   * @param integer $port
   * @param integer $timeout
   * @return boolean success
   */
  public function ssl_connect($host, $port=21, $timeout=60) {
    return $this->connect($host, true, $port, $timeout);
  }
    
  /* specific methods */
  
  /*
   * write a file to the server directly from given content
   * @param string $remoteFilePath
   * @param string $content
   * @return boolean success
   */
  public function write_content($remoteFilePath, $content) {
    $temp = fopen('php://temp', 'w');
    fwrite($temp, $content);
    rewind($temp);
    return $this->fput($remoteFilePath, $temp, FTP_BINARY);
  }
}
?>