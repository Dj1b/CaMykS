<?php
/**
 * @brief GenericCaptcha Input
 * <br /> CaMykS generic captcha.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 22021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GenericCaptcha Input class.
 */
final class GenericCaptcha extends Input {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('GenericCaptcha', $path_type);

        /* Override Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension
        $this->register_asExtension('Admin_Site');
        $this->register_asExtension('CookieAgreementMessage');
        */
    }

    /* Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* Build default params */
        $dParams = array(
            'mode' => 'display',
        );

        /* Save params */
        $this->params = array_merge($dParams, $params);
        $this->params['controlInputName'] = 'checkActions';

        /* Display mode */
        if ($this->params['mode'] == 'display') {
            if (is_object($this->params['form']) and get_class($this->params['form']) === 'HTMLForm') {
                /* Adds scripts */
                $this->add_JSFile('GenericCaptcha.js?v=1.0.0.1');
                $this->add_JSLoadScript('GenericCaptcha.set_param("form", "'.$this->params['form']->name.'");');
                $this->add_JSLoadScript('GenericCaptcha.set_param("controlInput", "'.$this->params['controlInputName'].'");');
                $this->add_JSLoadScript('GenericCaptcha.initialise();');
            }
        }

        /* Input generic initialization */
        parent::initialise();
    }

    /* Specific methods. */

    /**
     * Verify captcha.
     * @return boolean result
     */
    public function verify() {
        if ($this->params['mode'] !== 'verify')
            return false;

        if (!isset($_REQUEST[$this->params['controlInputName']]))
            return false;

        if (!((int)$_REQUEST[$this->params['controlInputName']] > 0))
            return false;

        return true;
    }
}
?>
