<?php
/**
 * @brief Encryption library.
 * @details Engine / Object Library
 * @file engine/lib/object/Cryptographer.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2019
 * @date Modification: Oct 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Cryptographer class.
 */
final class Cryptographer {
    /**
     * @var array $engines
     * @brief Available engines.
     */
    private $engines = array('OpenSSL', 'Mcrypt', 'Sodium');

    /**
     * @var array $params
     * @brief Engine parameters.
     */
    private $params = array(
        'engine'    => 'OpenSSL',
        'cipher'    => 'aes-256-cbc',
        'mode'      => '',              // specific to Mcrypt
        'key'       => '',
        'iv'        => '',
    );

    /**
     * @var integer $lastError
     * @brief Last error.
     */
    private $lastError = 0;

    /**
     * Class constructor.
     * @param array $params
     * @return void
     */
    public function __construct($params=array()) {
        $this->update_params($params);
    }

    /**
     * Update a parameter.
     * @param string $name
     * @param mixed $value
     * @return void
     */
    public function update_param($name, $value) {
        $this->params[$name] = $value;
    }

    /**
     * Update some parameters.
     * @param array $params
     * @return void
     */
    public function update_params($params) {
        $this->params = array_merge($this->params, $params);
    }

    /**
     * Check engine configuration.
     * @return boolean success
     */
    public function check_engineConfiguration() {
        switch($this->params['engine']) {
            case 'OpenSSL': return $this->_OpenSSL_check_configuration();
            case 'Mcrypt': return $this->_Mcrypt_check_configuration();
            case 'Sodium': return $this->_Sodium_check_configuration();
        }

        /* No known engine defined */
        $this->set_lastError(1);
        return false;
    }

    /**
     * Encrypt data.
     * @param string $data
     * @param integer $base64Encode
     * @return false on failure, string on success
     */
    public function encrypt($data, $base64Encode=true) {
        if (!$this->check_engineConfiguration())
            return false;
        switch($this->params['engine']) {
            case 'OpenSSL': $result = $this->_OpenSSL_encrypt($data); break;
            case 'Mcrypt': $result = $this->_Mcrypt_encrypt($data); break;
            case 'Sodium': $result = $this->_Sodium_encrypt($data); break;
        }

        if ($result === false)
            return false;
        if ($base64Encode)
            return base64_encode($result);
        return $result;
    }

    /**
     * Decrypt data.
     * @param string $data.
     * @param integer $base64Decode
     * @return false on failure, string on success
     */
    public function decrypt($data, $base64Decode=true) {
        if (!$this->check_engineConfiguration())
            return false;

        if ($base64Decode)
            $data = base64_decode($data);

        switch($this->params['engine']) {
            case 'OpenSSL': return $this->_OpenSSL_decrypt($data);
            case 'Mcrypt': return $this->_Mcrypt_decrypt($data);
            case 'Sodium': return $this->_Sodium_decrypt($data);
        }

        return false;
    }

    /**
     * Return last error code.
     * @return integer
     */
    public function get_lastErrorCode() {
        return $this->lastError;
    }

    /**
     * Return last error message.
     * @return string
     */
    public function get_lastErrorMessage() {
        global $camyks;

        /* Load dictionnary */
        $camyks->add_generic_translation('cryptographer');

        switch ($this->lastError) {
            case 0 : return $camyks->get_translation('cryptographer_error_none');
            /* Engine errors */
            case 1 : return $camyks->get_translation('cryptographer_error_unknownengine');
            case 2 : return $camyks->get_translation('cryptographer_error_enginenotavailable');

            /* Cipher errors */
            case 11 : return $camyks->get_translation('cryptographer_error_unknowncipher');

            /* Key / iv errors */
            case 21 : return $camyks->get_translation('cryptographer_error_keyisempty');
            case 22 : return $camyks->get_translation('cryptographer_error_ivisempty');

            /* Result errors */
            case 31 : return $camyks->get_translation('cryptographer_error_alteredmessage');

            /* Mcrypt specific errors */
            case 101 : return $camyks->get_translation('cryptographer_error_unknownmcryptmode');
        }
        return $camyks->get_translation('cryptographer_error_unknownerror');
    }

    /* Private methods */

    /**
     * Define last error
     * @param integer $error
     * @return void
     */
    private function set_lastError($error) {
        $this->lastError = $error;
    }

    /* Private OpenSSL methods */

    /**
     * Check OpenSSL configuration.
     * @return boolean result
     */
    private function _OpenSSL_check_configuration() {
        if (!function_exists('openssl_encrypt')) {
            $this->set_lastError(2);
            return false;
        }

        if (!in_array($this->params['cipher'], openssl_get_cipher_methods())) {
            $this->set_lastError(11);
            return false;
        }

        if ($this->params['key'] == '') {
            $this->set_lastError(21);
            return false;
        }

        if ($this->params['iv'] == '') {
            $this->set_lastError(22);
            return false;
        }

        return true;
    }

    /**
     * Encrypt data using OpenSSL engine.
     * @param string $data
     * @return string
     */
    private function _OpenSSL_encrypt($data) {
        /* Compute key and iv */
        $key = hash('sha256', $this->params['key']);
        $iv = substr(hash('sha256', $this->params['iv']), 0, openssl_cipher_iv_length($this->params['cipher']));

        /* Return encrypted data */
        return openssl_encrypt($data, $this->params['cipher'], $key, 0, $iv);
    }

    /**
     * Decrypt data using OpenSSL engine.
     * @param string $data.
     * @return string
     */
    private function _OpenSSL_decrypt($data) {
        /* Compute key and iv */
        $key = hash('sha256', $this->params['key']);
        $iv = substr(hash('sha256', $this->params['iv']), 0, openssl_cipher_iv_length($this->params['cipher']));

        /* Return decrypted data */
        return openssl_decrypt($data,$this->params['cipher'], $key, 0, $iv);
    }

    /* Private Mcrypt methods */

    /**
     * Check Mcrypt configuration.
     * @return boolean result
     */
    private function _Mcrypt_check_configuration() {
        if (!function_exists('mcrypt_encrypt')) {
            $this->set_lastError(2);
            return false;
        }

        if (!in_array($this->params['cipher'], mcrypt_list_algorithms())) {
            $this->set_lastError(11);
            return false;
        }

        if (!in_array($this->params['mode'], mcrypt_list_modes())) {
            $this->set_lastError(101);
            return false;
        }

        if ($this->params['key'] == '') {
            $this->set_lastError(21);
            return false;
        }

        return true;
    }

    /**
     * Encrypt data using Mcrypt engine.
     * @param string $data
     * @return string
     */
    private function _Mcrypt_encrypt($data) {
        /* Compute key and iv */
        $keyHash = hash('sha256', $this->params['key']);
        $key = substr($keyHash, 0,   mcrypt_get_key_size($this->params['cipher'], $this->params['mode']));
        $iv  = substr($keyHash, 0, mcrypt_get_block_size($this->params['cipher'], $this->params['mode']));

        /* Return encrypted data */
        return mcrypt_encrypt($this->params['cipher'], $key, $data, $this->params['mode'], $iv);
    }

    /**
     * Decrypt data using Mcrypt engine.
     * @param string $data.
     * @return string
     */
    private function _Mcrypt_decrypt($data) {
        /* Compute key and iv */
        $keyHash = hash('sha256', $this->params['key']);
        $key = substr($keyHash, 0,   mcrypt_get_key_size($this->params['cipher'], $this->params['mode']));
        $iv  = substr($keyHash, 0, mcrypt_get_block_size($this->params['cipher'], $this->params['mode']));

        /* Return decrypted data */
        return mcrypt_decrypt($this->params['cipher'], $key, $data, $this->params['mode'], $iv);
    }

    /* Private Sodium methods */

    /**
     * Check Sodium configuration.
     * @return boolean result
     */
    private function _Sodium_check_configuration() {
        if (!function_exists('sodium_crypto_secretbox')) {
            $this->set_lastError(2);
            return false;
        }

        if ($this->params['key'] == '') {
            $this->set_lastError(21);
            return false;
        }

        return true;
    }

    /**
     * Encrypt data using Sodium engine.
     * @param string $data
     * @return string
     */
    private function _Sodium_encrypt($data) {
        /* Compute key and iv */
        if ($this->params['iv'] != '') {
            $key = substr(hash('sha256', $this->params['key']), 0, SODIUM_CRYPTO_SECRETBOX_KEYBYTES);
            $iv  = substr(hash('sha256', $this->params['iv']), 0, SODIUM_CRYPTO_SECRETBOX_NONCEBYTES);
        } else {
            $keyHash = hash('sha256', $this->params['key']);
            $key = substr($keyHash, 0, SODIUM_CRYPTO_SECRETBOX_KEYBYTES);
            $iv = substr($keyHash, SODIUM_CRYPTO_SECRETBOX_KEYBYTES, SODIUM_CRYPTO_SECRETBOX_NONCEBYTES);
        }

        /* Get encrypted data */
        return sodium_crypto_secretbox($data, $iv, $key);
    }

    /**
     * Decrypt data using Sodium engine.
     * @param string $data.
     * @return string
     */
    private function _Sodium_decrypt($data) {
        /* Compute key and iv */
        if ($this->params['iv'] != '') {
            $key = substr(hash('sha256', $this->params['key']), 0, SODIUM_CRYPTO_SECRETBOX_KEYBYTES);
            $iv  = substr(hash('sha256', $this->params['iv']), 0, SODIUM_CRYPTO_SECRETBOX_NONCEBYTES);
        } else {
            $keyHash = hash('sha256', $this->params['key']);
            $key = substr($keyHash, 0, SODIUM_CRYPTO_SECRETBOX_KEYBYTES);
            $iv = substr($keyHash, SODIUM_CRYPTO_SECRETBOX_KEYBYTES, SODIUM_CRYPTO_SECRETBOX_NONCEBYTES);
        }

        /* Get decrypted data */
        if (($result = sodium_crypto_secretbox_open($data, $iv, $key)) === false) {
            $this->set_lastError(31);
        }

        /* Return result */
        return $result;
    }
}
?>
