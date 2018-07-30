<?php
/**
 * @brief ReCaptcha Input
 * <br /> Display and check Google's ReCaptcha captcha.
 * @details Plugin / Input Engine
 * @file plugin/input/ReCaptcha/ReCaptcha.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2016
 * @date Modification: Jul 2018
 * @copyright 2016 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ReCaptcha Input class.
 */
final class ReCaptcha extends Input {

    /**
     * var string $_lastError
     * @brief Plugin's last error.
     */
    private $_lastError;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('ReCaptcha', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* load configuration */
        $this->load_configuration();

        /* build default params */
        $dParams = array(
            'mode' => 'display',
        );

        /* define params */
        $this->params = array_merge($this->config->vars, $dParams, $params);

        /* add script */
        if ($this->params['publicKey'] != false and $this->params['publicKey'] != '' and $this->params['mode'] != 'verify')
            $this->add_JSExternFile('https://www.google.com/recaptcha/api.js');

        /* define variables */
        $this->_lastError = '';

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Display input.
     * @param string $layout
     * @return void
     */
    public function display($layout='captcha') {
        if ($layout == null) $layout = 'captcha';
        if ($layout != 'captcha')
            return;
        $this->set_selectedLayout('input_'.$layout.'.html.inc');
        if ($this->params['publicKey'] != false)
            parent::display();
    }

    /* specific tool methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        $this->load_library('ReCaptchaConfig');
        $this->config = new ReCaptchaConfig('config', $this);
        $this->config->get();
    }

    /**
     * Verify captcha.
     * @return boolean result
     */
    public function verify() {

        /* get captcha value */
        if (!isset($_POST['g-recaptcha-response'])) {
            $this->_lastError = 'error_captcha_missing';
            return false;
        }
        $captcha = $_POST['g-recaptcha-response'];

        /* send request to recaptcha */
        $result = json_decode(file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$this->params['privateKey'].'&response='.$captcha.'&remoteip='.client_getIp()), true);

        /* check result */
        if ($result['success'] === false) {
            /* save error */
            if (isset($result['error-codes'])) {
                foreach ($result['error-codes'] as $error) {
                    $this->_lastError = 'error_'.preg_replace('/-/', '_', $error);
                    break;
                }
            }
            return false;
        }
        return true;
    }

    /**
     * Return last error code.
     * @return string
     */
    public function get_lastErrorCode() {
        return $this->_lastError;
    }

    /**
     * Return last error as text.
     * @return string
     */
    public function get_lastError() {
        if ($this->_lastError == '')
            return '';
        return $this->get_translation($this->_lastError);
    }

    /* Admin_Site extension configuration methods */

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
        /* load plugin configuration */
        $this->load_configuration();

        /* update form */
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
