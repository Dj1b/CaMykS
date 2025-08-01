<?php
/**
 * @brief GenericCaptcha Input
 * <br /> CaMykS generic captcha.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2021
 * @date Modification: Jul 2025
 * @copyright 2021 - 2025 CaMykS Team
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
    }

    /* Mark: Override input methods */

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
                $this->add_JSFile('GenericCaptcha.js?v=1.0.1');
                $this->add_JSLoadScript('GenericCaptcha.initialise("'.$this->params['form']->name.'", "'.$this->params['controlInputName'].'");');
            }
        }

        /* Input generic initialization */
        parent::initialise();
    }

    /* Mark: Specific methods. */

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
