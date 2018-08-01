<?php
/**
 * @brief PayBoxPayment Input configuration object
 * @details Plugin / Input Library
 * @file plugin/input/PayBoxPayment/lib/PayBoxPaymentConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2018
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PayBoxPaymentConfig PluginConfig class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class PayBoxPaymentConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* running mode */
        $this->add_newItem('mode', 'string', 'test');
        
        /* paybox keys */
        $this->add_newItem('bankKey_Test', 'string', '');
        $this->add_newItem('bankKey_Live', 'string', '');

        /* paybox config */
        $this->add_newItem('site', 'string', '');
        $this->add_newItem('rang', 'string', '');
        $this->add_newItem('identifiant', 'string', '');

        /* paybox fixed config */
        $this->add_newItem('hash', 'string', 'SHA512');

        /* generic initialisation */
        parent::init_config();
    }
    
    /* overwrite PluginConfig methods */

    /**
     * Load object items values from header.
     * @return void
     */
    public function get_fromHeader() {
        parent::get_fromHeader();
        
        $mode = $_REQUEST['mode_']?$_REQUEST['mode_']:'test';
        if (!in_array($mode, array('test', 'live')))
          $mode = 'test';
        $this->vars['mode'] = $mode;
    }

    /* specific tool methods */

    /**
     * Return mode value list.
     * @return array
     */
    public function get_modeList() {
        return array(
            'test' => $this->get_translation('mode_test'),
            'live' => $this->get_translation('mode_live'),
        );
    }

    /**
     * Return mode value title.
     * @return string
     */
    public function get_modeTitle() {
        $l = $this->get_modeList();
        return $l[$this->vars['mode']];
    }
}
?>