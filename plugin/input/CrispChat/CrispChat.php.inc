<?php
/**
 * @brief CrispChat Input
 * <br /> Adds Crisp.chat snippet on page
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jul 2020
 * @date Modification: Jul 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CrispChat Input class.
 */
final class CrispChat extends Input {
    /**
     * var Object $config
     * @brief Input configuration.
     */
    protected $config;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('CrispChat', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');

        /* Automatically insert it in the page */
        $this->register_asCaMykSEventHandler('onPageLoad');
    }

    /* Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* Load configuration */
        $this->load_configuration();

        /* Input generic initialization */
        parent::initialise();

        /* Add JS scripts to page */
        if ($this->get_configValue('websiteId') != '')
            $this->add_JSScript('window.$crisp=[];window.CRISP_WEBSITE_ID="'.$this->get_configValue('websiteId').'";(function(){ d=document;s=d.createElement("script"); s.src="https://client.crisp.chat/l.js"; s.async=1;d.getElementsByTagName("head")[0].appendChild(s);})();');
    }

    /* Specific tool methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        $this->load_library('CrispChatConfig');
        $this->config = new CrispChatConfig('config', $this);
        $this->config->get();
    }

    /**
     * Return configuration value.
     * @param string $name
     * @return mixed
     */
    protected function get_configValue($name='') {
        return $this->config->get_value($name);
    }

    /* CaMykS page event methods */

    /**
     * Execute handler on page loading.
     * @return void
     */
    public function execute_onCaMykSPageLoad() {
        $this->initialise();
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
