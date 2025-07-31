<?php
/**
 * @brief CodeAuthenticator input
 * <br /> Handles 2-factor with code authenticator authentication.
 * <br /> Highly based on PHPGangsta / GoogleAuthenticator library (https://github.com/PHPGangsta/GoogleAuthenticator)
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2021
 * @date Modification: Jul 2025
 * @copyright 2021 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CodeAuthenticator Input class.
 */
final class CodeAuthenticator extends Input {
    /**
     * var Object $config
     * @brief Input configuration.
     */
    protected $config;

    /**
     * var boolean isConfigLoaded
     * @brief Stores if the configuration is loaded
     */
    protected $isConfigLoaded = false;

    /**
     * @var integer $lastError
     * @brief Last error.
     */
    private $lastError = 0;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('CodeAuthenticator', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as extension */
        $this->register_asExtension('Admin_Site');
        $this->register_asExtension('Admin_User');

        /* Automatically insert it in the page */
        $this->register_asCaMykSEventHandler('onPageLoad');
    }

    /* Mark: Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* Load configuration */
        $this->load_configuration();

        /* Build default params */
        $defaultParams = array('form'=>null, 'currentValue'=>null, 'accountName'=>'', 'accountIssuer'=>'', 'accountImage'=>'');

        /* Merge params with default params */
        $this->params = array_merge($defaultParams, $params);

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Load configuration */
        $this->load_configuration();

        /* Check action to execute */
        if (isset($_REQUEST['action'])) {
            switch($_REQUEST['action']) {
                case 'QRCodePicture':
                    return $this->execute_request_QRCodePicture();
            }
        }

        return false;
    }

    /* Mark: Override Plugin methods  */

    /**
     * Execute handler on page loading.
     * @return void
     */
    public function execute_onCaMykSPageLoad() {
        $this->initialise();
    }

    /* Mark: Request mode sub methods */

    /**
     * Write QR Code as picture.
     * @return void
     */
    private function execute_request_QRCodePicture() {
        global $camyks;

        /* Load current settings */
        $settings = $camyks->get_sessionValue('CodeAuthenticatorSettings', array());

        /* Check settings */
        if (!isset($settings['currentSecret']))
            die();

        /* Load configuration */
        $this->load_configuration();

        /* Build URL */
        $url = 'otpauth://totp/';
        if ($settings['accountIssuer'] != '')
            $url .= $settings['accountIssuer'].':';
        $url .= $settings['accountName'].'?secret='.$settings['currentSecret'];
        if ($settings['accountImage'] != '')
            $url .= '&icon='.urlencode($settings['accountImage']);

        /* Build QR Code picture */
        require_once 'Image/QRCode.php';

        $options = array(
            "image_type"    => 'png',
            "module_size"   => 7,
            "output_type"   => 'display',
        );
        $qr = new Image_QRCode();
        $qr->makeCode($url, $options);
    }

    /* Mark: User 2FA configuration */

    /**
     * Prepare 2FA configuration for user.
     * return void
     */
    public function prepare_userConfiguration($params) {
        global $camyks;

        /* Merge params with new params */
        $this->params = array_merge($this->params, $params);

        /* Load form object */
        $this->form = $this->params['form'];

        /* Load current settings */
        $settings = $camyks->get_sessionValue('CodeAuthenticatorSettings', array());

        /* Check settings */
        if (!isset($settings['currentSecret'])) {
            $settings['currentSecret'] = $this->params['currentValue'] !== '' ? $this->params['currentValue'] : $this->create_secret();
            $settings['accountName'] = $this->params['accountName'];
            $settings['accountImage'] = $this->params['accountImage'];
            $settings['accountIssuer'] = $this->params['accountIssuer'];
            $camyks->set_sessionValue('CodeAuthenticatorSettings', $settings);
        }

        /* Add script */
        $this->add_JSScript('function checkCodeInputValue(input) {');
        $this->add_JSScript('    input.value = input.value.replace(/[^0-9]/g, \'\');');
        $this->add_JSScript('}');
        $this->add_JSLoadScript('document.'.$this->form->name.'.code.focus();');
    }

    /**
     * Display 2FA configuration for user.
     * @return void
     */
    public function display_userConfiguration() {
        $this->load_file('html/input_userConfiguration.html.inc');
    }

    /**
     * Confirm 2FA configuration for user.
     * @return string
     */
    public function confirm_userConfiguration() {
        global $camyks;

        /* Load current settings */
        $settings = $camyks->get_sessionValue('CodeAuthenticatorSettings', array());

        /* Check settings */
        if (!isset($settings['currentSecret'])) {
            $this->set_lastError(1);
            return false;
        }

        /* Load user confirmation code */
        if (!isset($_REQUEST['code'])) {
            $this->set_lastError(2);
            return false;
        }
        $code = $_REQUEST['code'];

        /* Check code validity */
        if (!preg_match('/^[0-9]{6}$/', $code)) {
            $this->set_lastError(3);
            return false;
        }

        /* Confirm code */
        if (!$this->verify_code($settings['currentSecret'], $code)) {
            $this->set_lastError(4);
            return false;
        }

        /* Return confirmed secret */
        return $settings['currentSecret'];
    }

    /**
     * Reset 2FA configuration data for user.
     * @return string
     */
    public function reset_userConfigurationData() {
        global $camyks;

        /* Delete current settings */
        $camyks->set_sessionValue('CodeAuthenticatorSettings', array());
    }

    /* Mark: User 2FA login */

    /**
     * Prepare 2FA login for user.
     * return void
     */
    public function prepare_userLogin($params) {
        global $camyks;

        /* Merge params with new params */
        $this->params = array_merge($this->params, $params);

        /* Load form object */
        $this->form = $this->params['form'];

        /* Add script */
        $this->add_JSScript('function checkCodeInputValue(input) {');
        $this->add_JSScript('    input.value = input.value.replace(/[^0-9]/g, \'\');');
        $this->add_JSScript('}');
        $this->add_JSLoadScript('document.'.$this->form->name.'.code.focus();');
    }

    /**
     * Display 2FA login for user.
     * @return void
     */
    public function display_userLogin() {
        $this->load_file('html/input_userLogin.html.inc');
    }

    /**
     * Confirm 2FA login for user.
     * @return string
     */
    public function confirm_userLogin($params) {
        global $camyks;

        /* Merge params with new params */
        $this->params = array_merge($this->params, $params);

        /* Check settings */
        if (!isset($this->params['secret'])) {
            $this->set_lastError(1);
            return false;
        }

        /* Load user confirmation code */
        if (!isset($_REQUEST['code'])) {
            $this->set_lastError(2);
            return false;
        }
        $code = $_REQUEST['code'];

        /* Check code validity */
        if (!preg_match('/^[0-9]{6}$/', $code)) {
            $this->set_lastError(3);
            return false;
        }

        /* Confirm code */
        if (!$this->verify_code($this->params['secret'], $code)) {
            $this->set_lastError(4);
            return false;
        }

        /* Return confirmed login */
        return true;
    }

    /* Mark: Configuration methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        /* Check configuration is already loaded */
        if ($this->isConfigLoaded)
            return;

        /* Load configuration */
        $this->load_library('CodeAuthenticatorConfig');
        $this->config = new CodeAuthenticatorConfig('config', $this);
        $this->config->get();

        /* Save configuration is loaded */
        $this->isConfigLoaded = true;
    }

    /**
     * Return configuration value.
     * @param string $name
     * @return mixed
     */
    protected function get_configValue($name='') {
        return $this->config->get_value($name);
    }

    /* Mark: Authenticator related methods */

    /**
     * Create new secret.
     * @return string
     */
    public function create_secret() {
        /* Load secret length from configuration */
        $secretLength = $this->get_configValue('secret_length');

        /* Load valid chars */
        $validChars = $this->get_base32LookupTable();

        /* Get random value with available method */
        $rnd = false;
        if (function_exists('random_bytes')) {
            $rnd = random_bytes($secretLength);
        } elseif (function_exists('mcrypt_create_iv')) {
            $rnd = mcrypt_create_iv($secretLength, MCRYPT_DEV_URANDOM);
        } elseif (function_exists('openssl_random_pseudo_bytes')) {
            $rnd = openssl_random_pseudo_bytes($secretLength, $cryptoStrong);
            if (!$cryptoStrong)
                $rnd = false;
        }
        if ($rnd === false)
            return false;

        /* Compute secret */
        $secret = '';
        for ($i = 0; $i < $secretLength; ++$i)
            $secret .= $validChars[ord($rnd[$i]) & 31];

        /* Return result */
        return $secret;
    }

    /**
     * Calculate the code, with given secret and point in time.
     * @param string $secret
     * @param int|null $timeSlice
     * @return string
     */
    public function get_code($secret, $timeSlice = null) {
        if ($timeSlice === null)
            $timeSlice = floor(time() / 30);
            //$timeSlice = floor(time() / 30);

        $secretkey = $this->decode_base32($secret);

        // Pack time into binary string
        $time = chr(0).chr(0).chr(0).chr(0).pack('N*', $timeSlice);

        // Hash it with users secret key
        $hm = hash_hmac('SHA1', $time, $secretkey, true);

        // Use last nipple of result as index/offset
        $offset = ord(substr($hm, -1)) & 0x0F;

        // grab 4 bytes of the result
        $hashpart = substr($hm, $offset, 4);

        // Unpak binary value
        $value = unpack('N', $hashpart);
        $value = $value[1];

        // Only 32 bits
        $value = $value & 0x7FFFFFFF;

        $modulo = pow(10, $this->get_configValue('code_length'));

        return str_pad($value % $modulo, $this->get_configValue('code_length'), '0', STR_PAD_LEFT);
    }

    /**
     * Check if the given code is correct.
     * @param string $secret
     * @param string $code
     * @param int $discrepancy
     * @param int|null $currentTimeSlice time slice if we want use other that time()
     * @return boolean success
     */
    public function verify_code($secret, $code, $discrepancy = 1, $currentTimeSlice = null) {
        if ($currentTimeSlice === null)
            $currentTimeSlice = $this->get_timeSlice();
            // $currentTimeSlice = floor(time() / 30);

        if (strlen($code) != 6)
            return false;

        /* Verify code from $discrepancy x 30s before to $discrepancy x 30s after */
        for ($i = -$discrepancy; $i <= $discrepancy; ++$i) {
            $calculatedCode = $this->get_code($secret, $currentTimeSlice + $i);
            if ($this->is_timingSafeEqual($calculatedCode, $code))
                return true;
        }

        /* Verification failed, return failure */
        return false;
    }

    /**
     * Return QR Code URL.
     * @return string
     */
    public function get_QRCodeURL() {
        return $this->get_requestLink(array('action'=>'QRCodePicture'));
    }

    /**
     * Return decoded base32 secret.
     * @param $secret
     * @return bool|string
     */
    private function decode_base32($secret) {
        if (empty($secret))
            return '';

        $base32chars = $this->get_base32LookupTable();
        $base32charsFlipped = array_flip($base32chars);

        $paddingCharCount = substr_count($secret, $base32chars[32]);
        $allowedValues = array(6, 4, 3, 1, 0);
        if (!in_array($paddingCharCount, $allowedValues)) {
            return false;
        }
        for ($i = 0; $i < 4; ++$i) {
            if ($paddingCharCount == $allowedValues[$i] &&
                substr($secret, -($allowedValues[$i])) != str_repeat($base32chars[32], $allowedValues[$i])) {
                return false;
            }
        }
        $secret = str_replace('=', '', $secret);
        $secret = str_split($secret);
        $binaryString = '';
        for ($i = 0; $i < count($secret); $i = $i + 8) {
            $x = '';
            if (!in_array($secret[$i], $base32chars)) {
                return false;
            }
            for ($j = 0; $j < 8; ++$j) {
                $x .= str_pad(base_convert(@$base32charsFlipped[@$secret[$i + $j]], 10, 2), 5, '0', STR_PAD_LEFT);
            }
            $eightBits = str_split($x, 8);
            for ($z = 0; $z < count($eightBits); ++$z) {
                $binaryString .= (($y = chr(base_convert($eightBits[$z], 2, 10))) || ord($y) == 48) ? $y : '';
            }
        }

        return $binaryString;
    }

    /**
     * Get array with all 32 characters for decoding from/encoding to base32.
     * @return array
     */
    private function get_base32LookupTable() {
        return array(
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', //  7
            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', // 15
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', // 23
            'Y', 'Z', '2', '3', '4', '5', '6', '7', // 31
            '=',  // padding char
        );
    }

    /**
     * Return default time slice.
     * @return integer
     */
    private function get_timeSlice() {
        return floor(time() / 30);
    }

    /**
     * Check timings with a safe equal comparison
     * @param string $safeString
     * @param string $userString
     * @return boolean result
     */
    private function is_timingSafeEqual($safeString, $userString) {
        /* Perform PHP method if it exists */
        if (function_exists('hash_equals'))
            return hash_equals($safeString, $userString);

        /* Perform comparaison */
        $safeLen = strlen($safeString);
        $userLen = strlen($userString);

        if ($userLen != $safeLen)
            return false;

        $result = 0;

        for ($i = 0; $i < $userLen; ++$i)
            $result |= (ord($safeString[$i]) ^ ord($userString[$i]));

        /* Return differences, that should be equal to 0 for success */
        return ($result === 0);
    }

    /* Mark: Error management methods */

    /**
     * Return last error message.
     * @return string
     */
    public function get_lastError() {
        global $camyks;

        switch ($this->lastError) {
            case 0 : return $this->get_translation('error_none');
            case 1 : return $this->get_translation('error_secretisnomoreavailable');
            case 2 : return $this->get_translation('error_codenotfound');
            case 3 : return $this->get_translation('error_codenotvalid');
            case 4 : return $this->get_translation('error_codeincorrect');

        }
        return $this->get_translation('error_unknownerror');
    }

    /**
     * Define last error
     * @param integer $error
     * @return void
     */
    private function set_lastError($error) {
        $this->lastError = $error;
    }

    /* Mark: Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        /* load plugin configuration */
        $this->load_configuration();
    }

    /**
     * Display object in Admin_Site / view configuration mode.
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/configuration/view.html.inc');
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode.
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        /* Load plugin configuration */
        $this->load_configuration();

        /* Update form */
        $this->form = &$form;
        $this->form->set_object($this->config);
    }

    /**
     * Display object in Admin_Site / edit configuration mode.
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }

    /**
     * Execute object in Admin_Site / save configuration mode.
     * @return void
     */
    public function save_configuration() {
        $this->load_configuration();
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
