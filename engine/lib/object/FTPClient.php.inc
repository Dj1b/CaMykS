<?php
/**
 * @brief FTP client object library.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Mar 2018
 * @date Modification: Jul 2025
 * @copyright 2018 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * FTPClient class.
 */
final class FTPClient {
    /**
     * @var Resource $connection
     * @brief Connection to server.
     */
    private $connection;

    /**
     * Class constructor.
     */
    public function __construct() {
        $this->connection = null;
    }

    /**
     * Class destructor.
     */
    public function __destruct() {
        if ($this->connection !== null)
            $this->close();
    }

    /**
     * Magic method to catch all FTP commands from PHP.
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

    /**
     * Explicitly define connect method to get connection object.
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

    /**
     * Explicitly define ssl_connect method.
     * @param string $host
     * @param integer $port
     * @param integer $timeout
     * @return boolean success
     */
    public function ssl_connect($host, $port=21, $timeout=60) {
        return $this->connect($host, true, $port, $timeout);
    }

    /* specific methods */

    /**
     * Write a file to the server directly from given content.
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
